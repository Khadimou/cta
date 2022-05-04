#import libraries
from json.tool import main
from re import M
import tables
from tables import *
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
import imagehash
import glob
from hashtable import HashTable
import pandas as pd
import tqdm
   
# importing os.path module
import os.path

#compute impact parameter
def cip(x,y,pos_x,pos_y):
    return np.sqrt(np.square(x-pos_x) + np.square(y-pos_y))
    

#compute alpha angle at position j
def angle(x,y,pos_x,pos_y):
    
    return np.math.atan2(y-pos_y,x-pos_x) *  180 / np.pi
        

#return the singular values
def svd(res):
    # Applying SVD
    U, S, VT = np.linalg.svd(res,full_matrices=False,# It's not necessary to compute the full matrix of U or V
        compute_uv=True) # Deterministic SVD

    S = np.diag(S) #singular value matrix
    sv = []
    for i in range(55):
        sv.append(S[i][i])
    return sv

# scaling image array
def scale_array(arr):
    max = arr.max()
    min = arr.min()
    scale=255/(max-min)
    arr = (arr - min )*scale
    return arr

#function to retrieve parameter values from cta dataset
def values_from_h5file(fname):
    file = tables.open_file(fname,"r")
    #visualize images from the telescope
    img = file.root.dl1.event.telescope.images.LST_LSTCam.col("image")
    px_row = file.root.instrument.telescope.camera.LSTCam.col("pix_x")
    px_col = file.root.instrument.telescope.camera.LSTCam.col("pix_y")

    #number of images in fname
    nb_img = img.shape[0]
    #print(nb_img)

    # retrieve most interesting events
    tab_good_event = [event for event in img if event.std()>30]
    #print(len(tab_good_event))

    htable = np.fromfile("injunction_table_lst.pny", offset=8, dtype=np.uint16)
    matrix = np.zeros(55*55)

    #compute image hash with average hash
    hash = []
    mat = np.zeros((nb_img,55,55),dtype=np.float32)

    for i in range(nb_img):
        matrix[htable] = img[i]
        res = matrix.reshape(55,55)
        mat[i] = res
        hash.append(imagehash.phash(Image.fromarray(res)))
     
    #for l in range(len(hash)):
        #print("image hash",hash[l])
        
    #retrieving some parameters of the simulated images
    E = file.root.dl1.event.telescope.parameters.LST_LSTCam.col("mc_energy")
    h = file.root.dl1.event.telescope.parameters.LST_LSTCam.col("mc_h_first_int")
    x = file.root.dl1.event.telescope.parameters.LST_LSTCam.col("mc_core_x")
    y = file.root.dl1.event.telescope.parameters.LST_LSTCam.col("mc_core_y")
    Imax = file.root.dl1.event.telescope.parameters.LST_LSTCam.col("mc_x_max")
    eventId = file.root.dl1.event.telescope.parameters.LST_LSTCam.col("event_id")
    #retrieving parameters of the telescope
    pos_x = file.root.instrument.subarray.layout.col("pos_x")
    pos_y = file.root.instrument.subarray.layout.col("pos_y")

    return (x, y,  E, h, Imax, eventId, img, hash, mat), pos_x, pos_y

#def read_file(filename):
    #"Select data from all the tables in filename"
    #fileh = tables.open_file(filename, mode = "r")
    #result = []
    #for table in fileh("/", 'Table'):
        #result = [p['var3'] for p in table if p['var2'] <= 20]
    #fileh.close()
    #return result

# function to look up and compare a hash table
def compare_hashes(h):
    res = []
    #print("nombre de hash ", len(h))

    for i in range(len(h)-1):
        #comparison using a hamming distance
        if(h[i] == h[i+1]):
            res.append(h[i])
        if i==len(h)-1:
            break

    if(len(res) == 0):
        print("NO MATCHING FOUND between hashes xxx")
    
    return res

#creating tables for datasets
class Mc_shower(IsDescription):
    name = StringCol(20)
    idevent = UInt64Col()
    energy = Float32Col()
    hfirstint = Float32Col()
    Imax = Float32Col()
    impact = Float32Col()
    x = Float32Col()
    y = Float32Col() 
    hash = StringCol(64) 
    sv = Float32Col(shape=55)
    alpha = Float32Col()

def process_event(event,telescope_x, telescope_y):
  
    x = event[0]
    y = event[1]
    
    img = event[6]
   
    hash = event[7]

    res = event[8]

    #build hash table
    ht = HashTable()
    result = []; key = []; val = []
    
    #for k in range(img.shape[0]):
    ht.insert(str(hash),str(img))
        
    #for i in range(img.shape[0]):
        #print("key ",str(all_files[i]))
        #print("value ",ht.find(all_files[i])) #renvoie le hash de l'image à la position indiquée dans le fichier
    key.append(str(hash))
    val.append(ht.find(str(hash)))

    table = {'key': key, 'value': val}
    result = pd.DataFrame(table)
    #print(result)
    alpha = angle(x,y,telescope_x,telescope_y)

    # Applying SVD
    sv = svd(res)

    ro = cip(x,y,telescope_x,telescope_y) #impact parameter at position 0

    return ro,hash,sv,alpha

def process_file(outputfile,inputfile):
    test_data, pos_x, pos_y = values_from_h5file(inputfile)
    h5file = open_file(outputfile,mode ="w", title="Simulated image file")
    #create a group
    group = h5file.create_group("/",'Shower','Shower Info')
    #create a table
    table = h5file.create_table(group,"gerbe",Mc_shower,"mc_shower: gerbe")
    #now let's fill the table with its values
    telescope_x = pos_x[0]
    telescope_y = pos_y[0]
   
    gerbe = table.row #write data rows into the table
    for i,event in enumerate(zip(*test_data)):
        ro,hash,sv,alpha = process_event(event,telescope_x,telescope_y)
        E = event[2]
        h = event[3]
        x = event[0]
        y = event[1]
        Imax = event[4]
        eventId = event[5]
        img = event[6]
        hash = event[7]
        res = event[8]
 
        gerbe['name'] = inputfile
        gerbe['idevent'] = eventId
        gerbe['energy'] = E
        gerbe['hfirstint'] = h
        gerbe['x'] = x
        gerbe['y'] = y
        gerbe['Imax'] = Imax
        gerbe['impact'] = ro
        gerbe['hash'] = hash
        gerbe['sv'] = sv
        gerbe['alpha'] = alpha
        #insert a new gerbe record

        gerbe.append()

    table.flush()

    h5file.close()

def process_listfile(inputfiles,outputdir):
    os.makedirs(outputdir,exist_ok=True)
    for inputfile in tqdm.tqdm(inputfiles):
        outputfile = outputdir+"/hash_"+os.path.basename(inputfile)
        process_file(outputfile,inputfile)
    
if __name__ == "__main__":

    #retrieve all the files from our dataset
    test_fnames = glob.glob('Data/testing/*.h5',recursive=True) #500 files
    train_fnames = glob.glob('Data/training/*.h5',recursive=True) #500 files

    process_listfile(test_fnames,"./hash_testing")
    process_listfile(train_fnames,"./hash_training")

    #retrieve file names
    # testname = []
    # trainname = []
    # for test in test_fnames:
    #     testname.append(test)
    # for train in train_fnames:
    #     trainname.append(train)
    # all_files = trainname + testname

    # #compute hashing
    # for iter in range(len(testname)):
    #     test_data = values_from_h5file(testname[iter])
        
    #     E = test_data[4]
    #     h = test_data[5]
    #     x = test_data[0]
    #     y = test_data[1]
    #     Imax = test_data[6]
    #     eventId = test_data[7]
    #     img = test_data[8]
    #     px_row = test_data[9]
    #     px_col2 = test_data[10]
    #     tab_good_event = test_data[11]
    #     hash = test_data[12]
    #     pos_x = test_data[2]
    #     pos_y = test_data[3]
    #     res = test_data[13]
        
    #     #match = compare_hashes(both_hash)
    #     #for j in range(len(match)):
    #         #print("Matching training + testing files hashes", match[j]) #we notice some collisions

    #     #build hash table
    #     ht = HashTable()
    #     result = []; key = []; val = []
       
    #     for k in range(img.shape[0]):
    #         ht.insert(str(hash[k]),str(img[k]))
            
    #     for i in range(img.shape[0]):
    #         #print("key ",str(all_files[i]))
    #         #print("value ",ht.find(all_files[i])) #renvoie le hash de l'image à la position indiquée dans le fichier
    #         key.append(str(hash[i]))
    #         val.append(ht.find(str(hash[i])))
    
    #     table = {'key': key, 'value': val}
    #     result = pd.DataFrame(table)
    #     #print(result)
        
    #     #chaining = listedoublementchainee()
        
    #     #chaining.insert_listevide(hash1)
    #     #chaining.affiche_liste()
    #     # appliquer une méthode d'adressage ouvert ou de chainage (double hachage, hachage linéaire)
    #     # fonctions: ajout, recherche et delete

    #     alpha = angle(0,x,y,pos_x,pos_y)

    #     # Applying SVD
    #     sv = svd(res)

    #     ro = cip(0,x,y,pos_x,pos_y) #impact parameter at position 0
