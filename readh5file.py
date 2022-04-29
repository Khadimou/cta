#import libraries
from json.tool import main
import tables
from tables import *
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
import imagehash
import glob

#compute impact parameter
def cip(j,x,y,pos_x,pos_y):
    impact = []
    for i in range(x.size):
        dist2 = np.square(x[i]-pos_x[j]) + np.square(y[i]-pos_y[j])
        impact.append(np.sqrt(dist2))

    return impact

#compute alpha angle at position j
def angle(j,x,y,pos_x,pos_y):
    alpha = []
    for i in range(x.size):
        tmp = np.math.atan2(y[i]-pos_y[j],x[i]-pos_x[j]) *  180 / np.pi
        alpha.append(tmp)

    return alpha

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

    for i in range(nb_img):
        matrix[htable] = img[i]
        res = matrix.reshape(55,55)
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

    return x, y, pos_x, pos_y, E, h, Imax, eventId, img, px_row, px_col, tab_good_event, hash, res
    
if __name__ == "__main__":

    #retrieve all the files from our dataset
    test_fnames = glob.glob('Data/testing/*.h5',recursive=True) #500 files
    train_fnames = glob.glob('Data/training/*.h5',recursive=True) #500 files

    #retrieve file names
    testname = []
    trainname = []
    for test in test_fnames:
        testname.append(test)
    for train in train_fnames:
        trainname.append(train)

    #file train
    for iter in range(len(testname)):
        test_data = values_from_h5file(testname[iter])
        train_data = values_from_h5file(trainname[iter])

        #retrieving some values from training and testing folder of the simulated images
        E1 = train_data[4]
        h1 = train_data[5]
        x1 = train_data[0]
        y1 = train_data[1]
        Imax1 = train_data[6]
        eventId1 = train_data[7]
        img1 = train_data[8]
        px_row1 = train_data[9]
        px_col1 = train_data[10]
        tab_good_event1 = train_data[11]
        hash1 = train_data[12]
        pos_x1 = train_data[2]
        pos_y1 = train_data[3]
        res1 = train_data[13]

        E2 = test_data[4]
        h2 = test_data[5]
        x2 = test_data[0]
        y2 = test_data[1]
        Imax2 = test_data[6]
        eventId2 = test_data[7]
        img2 = test_data[8]
        px_row2 = test_data[9]
        px_col2 = test_data[10]
        tab_good_event2 = test_data[11]
        hash2 = test_data[12]
        pos_x2 = test_data[2]
        pos_y2 = test_data[3]
        res2 = test_data[13]


        alpha1 = angle(0,x1,y1,pos_x1,pos_y1)
        alpha2 = angle(0,x2,y2,pos_x2,pos_y2)

        # Applying SVD
        sv2 = svd(res2)
        sv1 = svd(res1)

        ro1 = cip(0,x1,y1,pos_x1,pos_y1) #impact parameter at position 0
        ro2 = cip(0,x2,y2,pos_x2,pos_y2) #impact parameter at position 0

        #creating tables for datasets
        class Mc_shower(IsDescription):
            name = StringCol(100)
            idevent = UInt64Col()
            energy = Float32Col()
            hfirstint = Float32Col()
            Imax = Float32Col()
            impact = Float32Col()
            x = Float32Col()
            y = Float32Col()
            hash1 = StringCol(64, shape=img1.shape[0]) 
            hash2 = StringCol(64, shape=img2.shape[0]) 
            sv = Float64Col(shape=55)
            alpha = Float64Col()

        h5file = open_file("database.h5",mode ="w", title="Simulated image file")
        #create a group
        group = h5file.create_group("/",'Shower','Shower Info')

        #create tables
        for tablename in ('gerbe1','gerbe2'):
            #create a table
            table = h5file.create_table(group,tablename,Mc_shower,"mc_shower: "+tablename)
            #now let's fill the table with its values
            gerbe = table.row #write data rows into the table

            if tablename=='gerbe1':
                for i in range(len(trainname)):
                    gerbe['name'] = trainname[i]
                    gerbe['idevent'] = eventId1[i]
                    gerbe['energy'] = E1[i]
                    gerbe['hfirstint'] = h1[i]
                    gerbe['x'] = x1[i]
                    gerbe['y'] = y1[i]
                    gerbe['Imax'] = Imax1[i]
                    gerbe['impact'] = ro1[i]
                    gerbe['hash1'] = hash1
                    gerbe['sv'] = sv1
                    gerbe['alpha'] = alpha1[i]
                    #insert a new gerbe record

                    gerbe.append()

            if tablename=='gerbe2':
                for i in range(len(testname)):
                    gerbe['name'] = testname[i]
                    gerbe['idevent'] = eventId2[i]
                    gerbe['energy'] = E2[i]
                    gerbe['hfirstint'] = h2[i]
                    gerbe['x'] = x2[i]
                    gerbe['y'] = y2[i]
                    gerbe['Imax'] = Imax2[i]
                    gerbe['impact'] = ro2[i]
                    gerbe['hash2'] = hash2
                    gerbe['sv'] = sv2
                    gerbe['alpha'] = alpha2[i]
                    #insert a new gerbe record

                    gerbe.append()

            table.flush()

            #We have our data on disk, and now we need to access it and select from specific columns the values we are interested in
            # table1 = h5file.root.Shower.gerbe1
            # table2 = h5file.root.Shower.gerbe2

    h5file.close()