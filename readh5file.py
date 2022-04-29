#import libraries
import tables
from tables import *
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
import imagehash
import glob

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

    #retrieve all the files from our dataset
test_fnames = glob.glob('Data/testing/*.h5',recursive=True) #500 files
train_fnames = glob.glob('Data/training/*.h5',recursive=True) #500 files

for test in test_fnames:
    xtest, ytest, pos_xtest, pos_ytest, Etest, htest, Imaxtest, eventIdtest, imgtest, px_rowtest, px_coltest, tab_good_eventtest, hashtest, restest = values_from_h5file(test)
for train in train_fnames:
    xtrain, ytrain, pos_xtrain, pos_ytrain, Etrain, htrain, Imaxtrain, eventIdtrain, imgtrain, px_rowtrain, px_coltrain, tab_good_eventtrain, hashtrain, restrain = values_from_h5file(train)

print(xtest)