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
    principal = PCA(n_components=4)
    principal.fit(Scaled_data)
    x=principal.transform(Scaled_data)

    # Check the values of eigen vectors
    # prodeced by principal components
    #print("composants principaux ",principal.components_)
    # check how much variance is explained by each principal component
    explained_variance = principal.explained_variance_ratio_
    #print("variance : ",explained_variance)
    explained_variance = np.insert(explained_variance,0,0) #setting x=0 ; y=0 to make the scree plot

    #preparing the cumulative variance data
    cumulative_variance = np.cumsum(np.round(explained_variance, decimals=3))

    #combining the dataframe
    pc_df = pd.DataFrame(['','PC1','PC2','PC3','PC4'], columns=['PC'])
    explained_variance_df = pd.DataFrame(explained_variance, columns=['Explained Variance'])
    cumulative_variance_df = pd.DataFrame(cumulative_variance, columns=['Cumulative Variance'])
    df_explainedvariance = pd.concat([pc_df,explained_variance_df,cumulative_variance_df], axis=1)
    #print(df_explainedvariance)

    #making the scree plot
    fig = px.bar(df_explainedvariance,
    x='PC', y='Explained Variance',
    text='Explained Variance',
    width=800)
    fig.update_traces(texttemplate='%{text:.3f}', textposition='outside')
    
    # https://plotly.com/python/creating-and-updating-figures/

    fig = go.Figure()

    fig.add_trace(
        go.Scatter(
            x=df_explainedvariance['PC'],
            y=df_explainedvariance['Cumulative Variance'],
            marker=dict(size=15, color="LightSeaGreen")
        ))

    fig.add_trace(
        go.Bar(
            x=df_explainedvariance['PC'],
            y=df_explainedvariance['Explained Variance'],
            marker=dict(color="RoyalBlue")
        ))

    #fig.show()

    #check the dimensions of data after PCA
    #print(x.shape)
    return x

if __name__ == "__main__":

    #retrieve all the files from our dataset
    test_fnames = glob.glob('hash_testing/*.h5',recursive=True) #500 files
    train_fnames = glob.glob('hash_training/*.h5',recursive=True) #500 files

    scores1 = []
    scores2 = []

    for input in train_fnames:
        energy, ro1, hfirstint, alpha1, Imax = read_files(input)
        scores1.append( pd.DataFrame(pca(energy, ro1, hfirstint, alpha1, Imax), columns=['PC1','PC2','PC3','PC4']))
    #print(scores1)
     
    for input in test_fnames:
        energy, ro2, hfirstint, alpha2, Imax = read_files(input)
        scores2.append( pd.DataFrame(pca(energy, ro2, hfirstint, alpha2, Imax), columns=['PC1','PC2','PC3','PC4']))
    #print(scores2)

    Y_label = []
    Y = {'ro', 'energy', 'hfirstint', 'Imax', 'alpha'}

    for i in Y:
        if i == 0:
            Y_label.append('ro')
        elif i == 1:
            Y_label.append('energy')
        elif i == 2:
            Y_label.append('hfirstint')
        elif i == 3:
            Y_label.append('Imax')
        else:
            Y_label.append('alpha')

    Params = pd.DataFrame(Y_label, columns=['Params'])

    # scores_df = pd.DataFrame(scores1[0], columns=['PC1', 'PC2', 'PC3'])
    # df_scores = pd.concat([scores_df, Params], axis=1)
    # fig = px.scatter_3d(df_scores, x='PC1', y='PC2', z='PC3',
    #           color='Params')

    #fig.show()


    fig = plt.figure(figsize=(10,10))
    #choose projection 3d for creating a 3d graph
    axis = fig.add_subplot(111,projection='3d')

    for i in range(len(scores1)):
        axis.scatter(scores1[i].PC1,scores1[i].PC2,scores1[i].PC3)

    for i in range(len(scores2)):
        axis.scatter(scores2[i].PC1,scores2[i].PC2,scores2[i].PC3)
    #axis.set_xlabel("PC1", fontsize=10)
    #axis.set_ylabel("PC2", fontsize=10)
    #axis.set_zlabel("PC3", fontsize=10)
    #plt.show()
