from sklearn.neighbors import KDTree
import tables
from tables import *
import numpy as np
import glob
import tqdm 
import os
import matplotlib.pyplot as plt


def getTrainProjectedData(fname):
    with open_file(fname,"r", driver="H5FD_CORE") as h5f:
        axeX = h5f.root.Train.projection.read(field="firstCol")
        axeY = h5f.root.Train.projection.read(field="secondCol")
        axeZ = h5f.root.Train.projection.read(field="thirdCol")
    Data = np.array([axeX,axeY,axeZ]).T
    print("data shape ",Data.shape)

    return Data

def getTestProjectedData(fname):
    with open_file(fname,"r", driver="H5FD_CORE") as h5f:
        axeX = h5f.root.Test.projection.read(field="firstCol")
        axeY = h5f.root.Test.projection.read(field="secondCol")
        axeZ = h5f.root.Test.projection.read(field="thirdCol")
    Data = np.array([axeX,axeY,axeZ]).T
    print("data shape ",Data.shape)

    return Data

# retrieve some parameter values from train data
def get_param_values(fnames):
    #read 1 column
    with open_file(fnames, "r", driver="H5FD_CORE") as f:
        idevent = f.root.Shower.gerbe.read(field="idevent")
        energy = f.root.Shower.gerbe.read(field="energy")
        #print("idevent ",idevent)

    return idevent, energy

# write data into a binary file
def writeToFile(fname, param):
    param.tofile(open(fname, "bw"))

# retrieve data from binary file
def readFromFile(fname, dt):
    myData = np.fromfile(open(fname, "rb"),dtype=dt)
    return myData

if __name__=='__main__':

    TrainData = getTrainProjectedData("TrainDataProjection.h5")
    TestData = getTestProjectedData("TestDataProjection.h5")

    # create tree
    tree = KDTree(TrainData+TestData, leaf_size=530000)
    dist, ind = tree.query(TrainData+TestData, k=3) # interroger l'arbre pour les 3 plus proches voisins

    # write index and distance to file then retrieve them
    writeToFile("indTrain.txt", ind)
    train_index = readFromFile("indTrain.txt",np.int64)
    writeToFile("distTrain.txt", dist)
    train_dist = readFromFile("distTrain.txt",np.float32)

    # get gerbe parameters values
    train_fnames = glob.glob('hash_training/*.h5', recursive=True)
    test_fnames = glob.glob('hash_testing/*.h5', recursive=True)
    # get events id and energies values from files
    events = []
    energies = []
    for input in train_fnames+test_fnames:
        eventId, energy = get_param_values(input)
        events.append(eventId)
        energies.append(energy)

    # for s,data in enumerate(TrainData):
    #     if train_index[s] == my_events[s]:
    #         print("event ",train_index[s],"energy ",energies[s], "distance ", train_dist[s])
    