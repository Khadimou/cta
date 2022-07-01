from sklearn.neighbors import KDTree
import tables
from tables import *
import numpy as np
import glob
import tqdm 
import os
import matplotlib.pyplot as plt
import re


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

#get energies for id events of projected data
def getEnergy(eventId, fnames):
    energies = []
    with open_file(fnames, "r", driver="H5FD_CORE") as f:
        table = f.root.Shower.gerbe
        for events in eventId:  
            energies.append([x['energy'] for x in table.iterrows() if x['idevent'] == events])
    for new_energy in energies:
        print(new_energy,end='[]')
        
    return energies

if __name__=='__main__':

    TrainData = getTrainProjectedData("TrainDataProjection.h5")
    TestData = getTestProjectedData("TestDataProjection.h5")

    # create tree
    #tree = KDTree(TrainData+TestData, leaf_size=530000)
    #dist, ind = tree.query(TrainData+TestData, k=3) # interroger l'arbre pour les 3 plus proches voisins

    # write index and distance to file then retrieve them
    #writeToFile("indTrain.txt", ind)
    train_index = readFromFile("indTrain.txt",np.int64)
    #writeToFile("distTrain.txt", dist)
    train_dist = readFromFile("distTrain.txt",np.float32)

    # get gerbe parameters values
    train_fnames = glob.glob('hash_training/*.h5', recursive=True)
    test_fnames = glob.glob('hash_testing/*.h5', recursive=True)
    # get events id and energies values from files
    events = np.zeros((TrainData.shape[0]+TestData.shape[0]))
    energies = np.zeros((TrainData.shape[0]+TestData.shape[0]))
    for input in train_fnames+test_fnames:
        eventId, energy = get_param_values(input)
        events = np.concatenate((events, eventId))
        energies = np.concatenate((energies, energy))

    #events id in common between projected data index in the tree and id of gerbe parameters
    res = set(events) & set(train_index)
    #print("number of id events in common for all files between projected data and original data ",len(list(res)))

    #get energies for id events of projected data
    for input in train_fnames:
        ProjEnergy = getEnergy(list(res), input)
    print(ProjEnergy)

    # for s,data in enumerate(TrainData):
    #     if train_index[s] == my_events[s]:
    #         print("event ",train_index[s],"energy ",energies[s], "distance ", train_dist[s])
    