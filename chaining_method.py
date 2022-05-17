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
from list2chain import listedoublementchainee

# convert string hash to int
def compute_hash(s):
    p = 31
    m = 1*np.exp(9) + 9
    hash_value = 0
    p_pow = 1
    #print("hash is ", s)
    str = s.translate({ord(i): None for i in 'b'}).replace("'", "")
    str.replace("'", "")
    #print(str)
    for c in str:
        hash_value = (hash_value + (int(c, 16) -ord('a') +1)* p_pow) % m 
        p_pow = (p_pow ** p) % m 

    return hash_value

#function to retrieve parameter values from cta dataset
def get_img(fname):
    file = tables.open_file(fname,"r")
    #visualize images from the telescope
    img = file.root.dl1.event.telescope.images.LST_LSTCam.col("image")

    #number of images in fname
    nb_img = img.shape[0]

    return  img, nb_img

#
def process_hashing(hash,img):
    
    #build hash table
    ht = HashTable()
    result = []; key = []; val = []
    
    ht.insert(str(hash),str(img))
         
    key.append(str(hash))
    val.append(ht.find(str(hash))) #renvoie le hash de l'image à la position indiquée dans le fichier

    table = {'key': key, 'value': val}
    result = pd.DataFrame(table)
    #print(result)
    return result

#retrieve hashes from our files
def read_files(inputfile):

    # read 1 column using field= parameter:
    with open_file(inputfile, "r", driver="H5FD_CORE") as h5f:
        hash_arr = h5f.root.Shower.gerbe.read(field='hash')

    return hash_arr

def get_hashtable(fnames):
    hashtab = []
    iter = 0
    for inputfile in tqdm.tqdm(fnames):
        image, size = get_img(inputfile)
        img = image[iter]
        hash = hash1[iter][iter]
        iter = iter + 1
        hashtab.append( process_hashing(hash,img))
    #print(hashtab)
    return hashtab

def search_in_hashtable(hashtab, hash_test):
    # search matching hashes with hash_testing
    iter = 0
    keys = []
    for h in hashtab:
        #print("key ",h.iat[0,0])
        keys.append(h.iat[0,0])
        #print("key ",compute_hash(h.iat[0,0]))
    
    img_vector = []
    while iter < len(keys)-1:
        for l in range(len(keys)):
            if hash_test[l][iter] == keys[l]:
                print("Matching found !!!!!")
            #print("hashes equal? : ",hash_test[l][iter] == keys[l])
            hash_diff = int(compute_hash(hash_test[l][iter].decode())-compute_hash(keys[l]))
            #print("Manhattan distance : ", hash_diff)
            if(hash_diff==0):
                print("MATCH FOUUUUUNNNDDDD !!!!! between keys: ", keys[l], hash_test[l][iter])
                print("img values ", get_img_val(hashtab,keys[l]))
                img_vector.append( get_img_val(hashtab,keys[l]))
            
        iter = iter + 1
        
    print("DONE SEARCHING ")
    # return img values of matching hashes
    return img_vector

# return value of corresponding key
def get_img_val(hashtab, key):
    res = 0
    for h in hashtab:
        if h.iat[0,0]==key:
            res=(h.iat[0,1])
            #print(h.iat[0,1])
    return res

if __name__ == "__main__":

    #retrieve all the files from our dataset
    test_fnames = glob.glob('hash_testing/*.h5',recursive=True) #500 files
    train_fnames = glob.glob('hash_training/*.h5',recursive=True) #500 files

    hash1 = []
    hash2 = []

    for input in train_fnames:
        hash1.append(read_files(input)) #retrieve hash from training dataset

    for input in test_fnames:
        hash2.append(read_files(input)) # retrieve hash from testing dataset

    #retrieve all the files from our dataset
    test_fnames = glob.glob('Data/testing/*.h5',recursive=True) #500 files
    train_fnames = glob.glob('Data/training/*.h5',recursive=True) #500 files
    all_files = train_fnames+test_fnames
    hashes = hash2 + hash1
    hashtab = get_hashtable(train_fnames)
    search_in_hashtable(hashtab,hashes)

    # store hashtable
    # chainage = listedoublementchainee()
    # for i in range(len(hashtab)):
    #     chainage.insertion_debut(hashtab[i])
    #chainage.affiche_liste()