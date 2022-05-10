from turtle import color
import tables
from tables import *
import numpy as np
from sklearn.preprocessing import StandardScaler
import pandas as pd
from sklearn.decomposition import PCA
import glob
import matplotlib.pyplot as plt
#import relevant libraries for 3d graph
from mpl_toolkits.mplot3d import Axes3D

#retrieve hashes from our files
def read_files(inputfile):

    # read 1 column using field= parameter:
    with open_file(inputfile, "r", driver="H5FD_CORE") as h5f:
        ro_arr = h5f.root.Shower.gerbe.read(field='impact')
        hash_arr = h5f.root.Shower.gerbe.read(field='hash')
        sv_arr = h5f.root.Shower.gerbe.read(field='sv')
        alpha = h5f.root.Shower.gerbe.read(field='alpha')
        Imax = h5f.root.Shower.gerbe.read(field='Imax')
        energy = h5f.root.Shower.gerbe.read(field='energy')
        hfirstint = h5f.root.Shower.gerbe.read(field='hfirstint')

    return energy, ro_arr, hfirstint, alpha, Imax

# applying pca
def pca(energy, ro, hfirstint, alpha, Imax):
    
    #Scale data before applying PCA
    scaling = StandardScaler()
    d1 = {'ro': ro, 'energy': energy, 'hfirstint': hfirstint} 
    d2 = {'Imax': Imax, 'alpha': alpha}

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

    # Check the values of eigen vectors
    # prodeced by principal components
    print("composants principaux ",principal.components_)
    # check how much variance is explained by each principal component
    print("variance : ",principal.explained_variance_ratio_)

    #check the dimensions of data after PCA
    #print(x.shape)
    return x

if __name__ == "__main__":

    #retrieve all the files from our dataset
    test_fnames = glob.glob('hash_testing/*.h5',recursive=True) #500 files
    train_fnames = glob.glob('hash_training/*.h5',recursive=True) #500 files

    res1 = []
    res2 = []

    for input in train_fnames:
        energy, ro1, hfirstint, alpha1, Imax = read_files(input)
        res1.append(pca(energy, ro1, hfirstint, alpha1, Imax))
     
    for input in test_fnames:
        energy, ro2, hfirstint, alpha2, Imax = read_files(input)
        res2.append(pca(energy, ro2, hfirstint, alpha2, Imax))

    fig = plt.figure(figsize=(10,10))
    #choose projection 3d for creating a 3d graph
    axis = fig.add_subplot(111,projection='3d')

    for i in range(len(res1)):
        axis.scatter(res1[i][:,0],res1[i][:,1],res1[i][:,2])

    for i in range(len(res2)):
        axis.scatter(res2[i][:,0],res2[i][:,1],res2[i][:,2])
    #axis.set_xlabel("PC1", fontsize=10)
    #axis.set_ylabel("PC2", fontsize=10)
    #axis.set_zlabel("PC3", fontsize=10)
    plt.show()
