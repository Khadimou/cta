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

    #number of images in fname
    nb_img = img.shape[0]
    #print(nb_img)

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
    hash = event[7]
    res = event[8]

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

    #     # appliquer une méthode d'adressage ouvert ou de chainage (double hachage, hachage linéaire)
    #     # fonctions: ajout, recherche et delete
