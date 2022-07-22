from sklearn.neighbors import KDTree
import tables
from tables import *
import numpy as np
import glob
import tqdm 
import os
import matplotlib.pyplot as plt
import re
import pandas as pd

# store common events (between tree id and event id) parameters values in h5 file
class commonEvents(IsDescription):
    idevent = UInt64Col()
    energy = Float32Col()
    hfirstint = Float32Col()
    Imax = Float32Col()
    impact = Float32Col()
    alpha = Float32Col()
    distances = Float32Col()

def write_file(frame, events, distances, outputfile, frameTest, distancesTest, eventsTest):
    h5file = open_file(outputfile, mode="w", title = "Common events parameters with the tree")
    #create a group
    group1 = h5file.create_group("/","Train","Train Data Tree Info")
    #create a table
    table1 = h5file.create_table(group1, "common", commonEvents, "common parameters")
    params = table1.row # write data rows into the table
    for i in events:
        params["idevent"] = i
        params["hfirstint"] = frame.iloc[i].at["hfirstint"]
        params["Imax"] = frame.iloc[i].at["Imax"]
        params["impact"] = frame.iloc[i].at["impact"]
        params["alpha"] = frame.iloc[i].at["alpha"]
        params["energy"] = frame.iloc[i].at["energy"]
        params["distances"] = distances[i]

        params.append()
    table1.flush()

     #create a group
    group2 = h5file.create_group("/","Test","Test Data Tree Info")
    #create a table
    table2 = h5file.create_table(group2, "common", commonEvents, "common parameters")
    param = table2.row # write data rows into the table
    for i in eventsTest:
        param["idevent"] = i
        param["hfirstint"] = frameTest.iloc[i].at["hfirstint"]
        param["Imax"] = frameTest.iloc[i].at["Imax"]
        param["impact"] = frameTest.iloc[i].at["impact"]
        param["alpha"] = frameTest.iloc[i].at["alpha"]
        param["energy"] = frameTest.iloc[i].at["energy"]
        param["distances"] = distancesTest[i]

        param.append()
    table2.flush()


    h5file.close()


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

# retrieve some parameter values from dataset
def get_param_values(fnames):
    #read 1 column
    with open_file(fnames, "r", driver="H5FD_CORE") as f:
        idevent = f.root.Shower.gerbe.read(field="idevent")
        E = f.root.Shower.gerbe.read(field="energy")
        h = f.root.Shower.gerbe.read(field="hfirstint")
        Imax = f.root.Shower.gerbe.read(field="Imax")
        alpha = f.root.Shower.gerbe.read(field="alpha")
        impact = f.root.Shower.gerbe.read(field="impact")
    d = {"idevent":idevent, "energy": E, "hfirstint":h, "Imax":Imax, "alpha":alpha, "impact":impact}

    return d

if __name__=='__main__':

    TrainData = getTrainProjectedData("TrainDataProjection.h5")
    TestData = getTestProjectedData("TestDataProjection.h5")

    # create tree train
    tree = KDTree(TrainData)
    dist, ind = tree.query(TestData, k=3) # interroger l'arbre pour les 3 plus proches voisins
    d = {'idevent': [*ind.T[1], *ind.T[2]], 'distance': [*dist.T[1], *dist.T[2]]}
    df = pd.DataFrame(d)

    # get gerbe parameters values
    train_fnames = glob.glob('hash_training/*.h5', recursive=True)
    test_fnames = glob.glob('hash_testing/*.h5', recursive=True)

    #distance associated for each event
    distances = []
    for it in df["idevent"]:
        distances.append(df.loc[it].at["distance"])

    frame = []
    #get parameter values associated for id events we have in common
    for input in train_fnames:
        my_dataframe = get_param_values(input)
        frame.append(pd.DataFrame(my_dataframe))
    frame = pd.concat([df.set_index('idevent') for df in frame], axis=0)
    #print(frame)
    print(tree.get_tree_stats())

    #distance associated for each event
    distancesTest = []
    for it in df["idevent"]:
        distancesTest.append(df.loc[it].at["distance"])

    frameTest = []
    #get parameter values associated for id events we have in common
    for input in test_fnames:
        my_dataframe = get_param_values(input)
        frameTest.append(pd.DataFrame(my_dataframe))
    frameTest = pd.concat([df.set_index('idevent') for df in frameTest], axis=0)
    #print(frameTest)

    frame["idevent"] = frame.index
    frameTest["idevent"] = frameTest.index

    write_file(frame, frame["idevent"], distances, "tree.h5", frameTest, distancesTest, frameTest["idevent"])