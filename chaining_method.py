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

#build hash table
def hash_table(h1,h2,img):

    hachage = h1 + h2
    #build hash table
    ht = HashTable()
    result = []; key = []; val = []
    
    #for k in range(img.shape[0]):
    ht.insert(str(hachage),str(img))
        
    #for i in range(img.shape[0]):
        #print("key ",str(all_files[i]))
        #print("value ",ht.find(all_files[i])) #renvoie le hash de l'image à la position indiquée dans le fichier
    key.append(str(hachage))
    val.append(ht.find(str(hachage)))

    table = {'key': key, 'value': val}
    result = pd.DataFrame(table)
    #print(result)


# function to compute collisions between hash vectors
def compute_collisions(h1,h2):
    res = []
    df = pd.DataFrame(data={'hash1':h1})
    other = pd.DataFrame(data={'hash2':h2})
    hachage =h1+h2
    for j in range(len(h1)-1):
        if(list(set(str(h1[j])) - set(str(h2[j]))) + list(set(str(h1[j])) - set(str(h2[j])))==None):
            res.append(h1[j])

    if(len(res) == 0):
        print("NO MATCHING FOUND between hashes xxx")

    print("collisions",res)
    
    return res

def read_files(inputfile):

    # read 1 column using field= parameter:
    with open_file(inputfile, "r", driver="H5FD_CORE") as h5f:
        hash_arr = h5f.root.Shower.gerbe.read(field='hash')

    return hash_arr
        


if __name__ == "__main__":

    #retrieve all the files from our dataset
    test_fnames = glob.glob('hash_testing/*.h5',recursive=True) #500 files
    train_fnames = glob.glob('hash_training/*.h5',recursive=True) #500 files

    hash1 = []
    hash2 = []

    for input in train_fnames:
        hash1.append(read_files(input))

    for input in test_fnames:
        hash2.append(read_files(input))
        
    match = compute_collisions(hash1,hash2)
    for j in range(len(match)):
        print("Matching training + testing files hashes", match[j]) #we do not notice any collisions

    # ht = HashTable()
    # ht.insert((str(hash1+hash2),str(img)))
    # print(ht.find(str(hash1+hash2)))