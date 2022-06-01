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
import pandas as pd
import tqdm
from list2chain import listedoublementchainee

#function to retrieve parameter values from cta dataset
def get_img(fname):
    file = tables.open_file(fname,"r")
    #visualize images from the telescope
    img = file.root.dl1.event.telescope.images.LST_LSTCam.col("image")

    #number of images in fname
    nb_img = img.shape[0]

    return  img, nb_img


#retrieve hashes from our files
def read_files(inputfile):

    # read 1 column using field= parameter:
    with open_file(inputfile, "r", driver="H5FD_CORE") as h5f:
        hash_arr = h5f.root.Shower.gerbe.read(field='hash')

    return hash_arr

def get_hashtable(fnames):
    hashtab = {}
    iter = 0
    print("Put images values with corresponding key into hashtable \n")
    for inputfile in tqdm.tqdm(fnames):
        image, size = get_img(inputfile)
        img = image[iter]
        hash = imagehash.hex_to_hash(hash1[iter][iter])
        iter = iter + 1
        hashtab[hash] = img
    #print(hashtab)
    return hashtab

def search_in_hashtable(hashtab, hash_test):
    # search matching hashes with hash_testing
    iter = 0
    keys = list(hashtab.keys())
    
    img_vector = []
    print("Looking for a match between testing images hashes and training images hashes \n")
    for h1 in keys:
        for h2 in hash_test[iter]:
            hashdiff = imagehash.hex_to_hash(h2)-h1
            #print("hashdiff ", hashdiff)
        iter = iter + 1
    
        if(hashdiff<=6):
            print("MATCH FOUUUUUNNNDDDD !!!!! between keys: ", h1, imagehash.hex_to_hash(h2))
            print("img values ", get_img_val(hashtab,h1))
            img_vector.append( get_img_val(hashtab,h1))
        
    print("DONE SEARCHING ")
    # return img values of matching hashes
    return img_vector

# return value of corresponding key
def get_img_val(hashtab, key):
    res = 0
    for h in list(hashtab.keys()):
        if h==key:
            res=(hashtab[h])
            #print("val ", res)
    return res

if __name__ == "__main__":

    #retrieve all the files from our dataset
    test_fnames = glob.glob('hash_testing/*.h5',recursive=True) #500 files
    train_fnames = glob.glob('hash_training/*.h5',recursive=True) #500 files

    hash1 = []
    hash2 = []

    print("Get training hash values \n")
    for input in tqdm.tqdm(train_fnames):
        hash1.append(read_files(input)) #retrieve hash from training dataset

    print("Get testing hash values \n")
    for input in tqdm.tqdm(test_fnames):
        hash2.append(read_files(input)) # retrieve hash from testing dataset

    #retrieve all the files from our dataset
    test_fnames = glob.glob('Data/testing/*.h5',recursive=True) #500 files
    train_fnames = glob.glob('Data/training/*.h5',recursive=True) #500 files
   
    hashtab = get_hashtable(train_fnames)
    #for input in test_fnames:
    search_in_hashtable(hashtab,hash2)

    # store hashtable
    #chainage = listedoublementchainee()
    
    tri = pd.DataFrame(hashtab)
    # plt.figure()
    # tri.plot(kind="hist")
    # plt.show()
    print("tableau trie ",tri)
    #chainage.affiche_liste()