import tables
from tables import *
import numpy as np
from sklearn.preprocessing import StandardScaler
import pandas as pd
from sklearn.decomposition import PCA
import glob

#retrieve hashes from our files
def read_files(inputfile):

    # read 1 column using field= parameter:
    with open_file(inputfile, "r", driver="H5FD_CORE") as h5f:
        ro_arr = h5f.root.Shower.gerbe.read(field='impact')
        hash_arr = h5f.root.Shower.gerbe.read(field='hash')
        sv_arr = h5f.root.Shower.gerbe.read(field='sv')
        alpha = h5f.root.Shower.gerbe.read(field='alpha')

    return hash_arr, ro_arr, sv_arr, alpha

# applying pca
def pca(ro, hash, sv, alpha):
    
    #Scale data before applying PCA
    scaling = StandardScaler()
    d1 = {'ro': ro, 'hash': hash}
    d2 = {'sv': sv, 'alpha': alpha}

    df = pd.DataFrame(data=d1)
    other = pd.DataFrame(data=d2)
    data = df.join(other,how="left",  lsuffix = '_left', rsuffix = '_right')
    #print("data ", data.head())
    #use fit and transform method
    scaling.fit(data)
    Scaled_data = scaling.transform(data)

    #set the n_components=3
    principal = PCA(n_components=3)
    principal.fit(Scaled_data)
    x=principal.transform(Scaled_data)

    #check the dimensions of data after PCA
    print(x.shape)

if __name__ == "__main__":

    #retrieve all the files from our dataset
    test_fnames = glob.glob('hash_testing/*.h5',recursive=True) #500 files
    train_fnames = glob.glob('hash_training/*.h5',recursive=True) #500 files

    #
    hashtrain = []
    hashtest = []
    rotrain = []
    rotest = []
    svtrain = []
    svtest = []
    alphatrain = []
    alphatest = []

    for input in train_fnames:
        hash1, ro1, sv1, alpha1 = read_files(input)
        # pca(ro1,hash1,sv1,alpha1)
        hashtrain.append(hash1) #retrieve hash from training dataset
        rotrain.append(ro1)
        svtrain.append(sv1)
        alphatrain.append(alpha1)

    pca(rotrain,hashtrain,svtrain,alphatrain)
    for input in test_fnames:
        hash2, ro2, sv2, alpha2 = read_files(input)
