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
import plotly.express as px
import plotly.graph_objects as go
from plotly.subplots import make_subplots
import tqdm
from multiprocessing import Pool

hfile = tables.open_file("Data/training/train2.h5", "r")
#function to retrieve parameter values from cta dataset
def get_img(fname):
    file = tables.open_file(fname,"r")
    #visualize images from the telescope
    img = file.root.dl1.event.telescope.images.LST_LSTCam.col("image")

    return  img

def retrieve_img(file_offset):
    images = get_img(file_offset[0])

    file_offset[1][file_offset[2]:file_offset[3], :] = images

train_fnames = glob.glob('Data/training/*.h5',recursive=True) #500 files
nbevent = 0
file_offset = []
file_view = []

for file in train_fnames:
    hfile = tables.open_file(file, "r")
    nrows = hfile.root.dl1.event.telescope.images.LST_LSTCam.nrows
    file_offset.append((file,nbevent, nbevent+nrows))
    nbevent = nbevent + nrows
    hfile.close()
#file_offset
tab_event_img =  np.zeros((nbevent,1855), dtype=np.float32)


for tab in file_offset:
    file_view.append((tab[0], tab_event_img.view(), tab[1], tab[2]))
with Pool(96) as p:
    p.map(retrieve_img, file_view)

tab_event_img.tofile("event_img_1058742_1855.npy")