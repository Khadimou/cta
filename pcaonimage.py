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

#retrieve params from our files
def read_files(inputfile):

    # read 1 column using field= parameter:
    with open_file(inputfile, "r", driver="H5FD_CORE") as h5f:
        idevent = h5f.root.Shower.gerbe.read(field='idevent')
        #retrieving some parameters of the simulated images
        E = h5f.root.Shower.gerbe.read("mc_energy")
        h = h5f.root.Shower.gerbe.read("mc_h_first_int")
        Imax = h5f.root.Shower.gerbe.read("mc_x_max")
        impact = h5f.root.Shower.gerbe.read("impact")
        alpha = h5f.root.Shower.gerbe.read("alpha")
        sv = h5f.root.Shower.gerbe.read("sv")

    return idevent, E, h, Imax, impact, alpha, sv

#creating tables for datasets
class space(IsDescription):
    pc = Float16Col()
    sv = Float32Col()
    variance = Float16Col()

class Gerbe(IsDescription):
    idevent = UInt64Col()
    energy = Float32Col()
    hfirstint = Float32Col()
    Imax = Float32Col()
    impact = Float32Col()
    sv = Float32Col(shape=55)
    alpha = Float32Col()

def process_file(outputfile,images,inputfile):
    
    h5file = open_file(outputfile,mode ="w", title="Projection images file")
    #create a group
    group = h5file.create_group("/",'Projection','Projection Info')
    #create a table
    table = h5file.create_table(group,"ACP",space,"ACP")
    #now let's fill the table with its values
   
    projection = table.row #write data rows into the table
    for i,image in enumerate(zip(*images)):
        pc, variance, sv = pca(image)
        projection["pc"] = pc
        projection["variance"] = variance
        projection["sv"] = sv
        
        #insert a new projection record

        projection.append()

    table.flush()

    #create a group
    group1 = h5file.create_group("/",'Shower','Shower Info')
    #create a table
    table1 = h5file.create_table(group1,"gerbe",Gerbe,"gerbe")
    #now let's fill the table with its values
    # Read the records from table "/Events/TEvent3" and select some
    gerbe = table1.row #write data rows into the table
    params = read_files(inputfile)
    for i,par in enumerate(zip(*params)):
        idevent = par[0]
        E = par[1]
        h = par[2]
        Imax = par[3]
        impact = par[4]
        alpha = par[5]
        val = par[6]
        gerbe['idevent'] = idevent
        gerbe['energy'] = E
        gerbe['hfirstint'] = h
        gerbe['Imax'] = Imax
        gerbe['impact'] = impact
        gerbe['sv'] = val
        gerbe['alpha'] = alpha
        #insert a new projection record
        gerbe.append()
    
    table1.flush()

    h5file.close()

def process_listfile(inputfiles,outputdir,images):
    os.makedirs(outputdir,exist_ok=True)
    for inputfile in tqdm.tqdm(inputfiles):
        outputfile = outputdir+"/config_"+os.path.basename(inputfile)
        process_file(outputfile,images,inputfile)

# principal component analysis on images
def pca(img):

    #Scale data before applying PCA
    scaling = StandardScaler()
    data = img.data

    #use fit and transform method
    scaling.fit(data)
    Scaled_data = scaling.transform(data)

    #set the n_components
    principal = PCA(n_components=0.85)
    principal.fit(Scaled_data)
    x = principal.transform(Scaled_data)
    # Check the values of eigen vectors
    # prodeced by principal components
    print("Principal components \n",principal.components_)
    # check how much variance is explained by each principal component
    explained_variance = principal.explained_variance_ratio_
    #print("variance : ",explained_variance)
    explained_variance = np.insert(explained_variance,0,0) #setting x=0 ; y=0 to make the scree plot

    #preparing the cumulative variance data
    cumulative_variance = np.cumsum(np.round(explained_variance, decimals=3))
    explained_variance_df = pd.DataFrame(explained_variance, columns=['Explained Variance'])
    cumulative_variance_df = pd.DataFrame(cumulative_variance, columns=['Cumulative Variance'])

    scores = pd.DataFrame(data=x)
    names = []
    for r in range(5):
        names.append( 'PC'+str(r) )
    scores.columns = [names]
    #print(scores)
    pc_df = pd.DataFrame(['','PC0', 'PC1', 'PC2', 'PC3', 'PC4', 'PC5', 'PC6', 'PC7', 'PC8', 'PC9', 'PC10', 'PC11', 'PC12', 'PC13', 'PC14', 'PC15', 'PC16', 'PC17', 'PC18', 'PC19', 'PC20', 'PC21', 'PC22', 'PC23', 'PC24', 'PC25', 'PC26', 'PC27', 'PC28', 'PC29', 'PC30', 'PC31', 'PC32', 'PC33', 'PC34', 'PC35', 'PC36', 'PC37', 'PC38', 'PC39', 'PC40', 'PC41', 'PC42', 'PC43', 'PC44', 'PC45', 'PC46', 'PC47', 'PC48', 'PC49', 'PC50', 'PC51', 'PC52', 'PC53', 'PC54', 'PC55', 'PC56', 'PC57', 'PC58', 'PC59', 'PC60', 'PC61', 'PC62', 'PC63', 'PC64', 'PC65', 'PC66', 'PC67', 'PC68', 'PC69', 'PC70', 'PC71', 'PC72', 'PC73', 'PC74', 'PC75', 'PC76', 'PC77', 'PC78', 'PC79', 'PC80', 'PC81', 'PC82', 'PC83', 'PC84', 'PC85', 'PC86', 'PC87', 'PC88', 'PC89', 'PC90', 'PC91', 'PC92', 'PC93', 'PC94', 'PC95', 'PC96', 'PC97', 'PC98', 'PC99', 'PC100', 'PC101', 'PC102', 'PC103', 'PC104', 'PC105', 'PC106', 'PC107', 'PC108', 'PC109', 'PC110', 'PC111', 'PC112', 'PC113', 'PC114', 'PC115', 'PC116', 'PC117', 'PC118', 'PC119', 'PC120', 'PC121', 'PC122', 'PC123', 'PC124', 'PC125', 'PC126', 'PC127', 'PC128', 'PC129', 'PC130', 'PC131', 'PC132', 'PC133', 'PC134', 'PC135', 'PC136', 'PC137', 'PC138', 'PC139', 'PC140', 'PC141', 'PC142', 'PC143', 'PC144', 'PC145', 'PC146', 'PC147', 'PC148', 'PC149', 'PC150', 'PC151', 'PC152', 'PC153', 'PC154', 'PC155', 'PC156', 'PC157', 'PC158', 'PC159', 'PC160', 'PC161', 'PC162', 'PC163', 'PC164', 'PC165', 'PC166', 'PC167', 'PC168', 'PC169', 'PC170', 'PC171', 'PC172', 'PC173', 'PC174', 'PC175', 'PC176', 'PC177', 'PC178', 'PC179', 'PC180', 'PC181', 'PC182', 'PC183', 'PC184', 'PC185', 'PC186', 'PC187', 'PC188', 'PC189', 'PC190', 'PC191', 'PC192', 'PC193', 'PC194', 'PC195', 'PC196', 'PC197', 'PC198', 'PC199', 'PC200', 'PC201', 'PC202', 'PC203', 'PC204', 'PC205', 'PC206', 'PC207', 'PC208', 'PC209', 'PC210', 'PC211', 'PC212', 'PC213', 'PC214', 'PC215', 'PC216', 'PC217', 'PC218', 'PC219', 'PC220', 'PC221', 'PC222', 'PC223', 'PC224', 'PC225', 'PC226', 'PC227', 'PC228', 'PC229', 'PC230', 'PC231', 'PC232', 'PC233', 'PC234', 'PC235', 'PC236', 'PC237', 'PC238', 'PC239', 'PC240', 'PC241', 'PC242', 'PC243', 'PC244', 'PC245', 'PC246', 'PC247', 'PC248', 'PC249', 'PC250', 'PC251', 'PC252', 'PC253', 'PC254', 'PC255', 'PC256', 'PC257', 'PC258', 'PC259', 'PC260', 'PC261', 'PC262', 'PC263', 'PC264', 'PC265', 'PC266', 'PC267', 'PC268', 'PC269', 'PC270', 'PC271', 'PC272', 'PC273', 'PC274', 'PC275', 'PC276', 'PC277', 'PC278', 'PC279', 'PC280', 'PC281', 'PC282', 'PC283', 'PC284', 'PC285', 'PC286', 'PC287', 'PC288', 'PC289', 'PC290', 'PC291', 'PC292', 'PC293', 'PC294', 'PC295', 'PC296', 'PC297', 'PC298', 'PC299', 'PC300', 'PC301', 'PC302', 'PC303', 'PC304', 'PC305', 'PC306', 'PC307', 'PC308', 'PC309', 'PC310', 'PC311', 'PC312', 'PC313', 'PC314', 'PC315', 'PC316', 'PC317', 'PC318', 'PC319', 'PC320', 'PC321', 'PC322', 'PC323', 'PC324', 'PC325', 'PC326', 'PC327', 'PC328', 'PC329', 'PC330', 'PC331', 'PC332', 'PC333', 'PC334', 'PC335', 'PC336', 'PC337', 'PC338', 'PC339', 'PC340', 'PC341', 'PC342', 'PC343', 'PC344', 'PC345', 'PC346', 'PC347', 'PC348', 'PC349', 'PC350', 'PC351', 'PC352', 'PC353', 'PC354', 'PC355', 'PC356', 'PC357', 'PC358', 'PC359', 'PC360', 'PC361', 'PC362', 'PC363', 'PC364', 'PC365', 'PC366', 'PC367', 'PC368', 'PC369', 'PC370', 'PC371', 'PC372', 'PC373', 'PC374', 'PC375', 'PC376', 'PC377', 'PC378', 'PC379', 'PC380', 'PC381', 'PC382', 'PC383', 'PC384', 'PC385', 'PC386', 'PC387', 'PC388', 'PC389', 'PC390', 'PC391', 'PC392', 'PC393', 'PC394', 'PC395', 'PC396', 'PC397', 'PC398', 'PC399', 'PC400', 'PC401', 'PC402', 'PC403', 'PC404', 'PC405', 'PC406', 'PC407', 'PC408', 'PC409', 'PC410', 'PC411', 'PC412', 'PC413', 'PC414', 'PC415', 'PC416', 'PC417', 'PC418', 'PC419', 'PC420', 'PC421', 'PC422', 'PC423', 'PC424', 'PC425', 'PC426', 'PC427', 'PC428', 'PC429', 'PC430', 'PC431', 'PC432', 'PC433', 'PC434', 'PC435', 'PC436', 'PC437', 'PC438', 'PC439', 'PC440', 'PC441', 'PC442', 'PC443', 'PC444', 'PC445', 'PC446', 'PC447', 'PC448', 'PC449', 'PC450', 'PC451', 'PC452', 'PC453', 'PC454', 'PC455', 'PC456', 'PC457', 'PC458', 'PC459', 'PC460', 'PC461', 'PC462', 'PC463', 'PC464', 'PC465', 'PC466', 'PC467', 'PC468', 'PC469', 'PC470', 'PC471', 'PC472', 'PC473', 'PC474', 'PC475', 'PC476', 'PC477', 'PC478', 'PC479', 'PC480', 'PC481', 'PC482', 'PC483', 'PC484', 'PC485', 'PC486', 'PC487', 'PC488', 'PC489', 'PC490', 'PC491', 'PC492', 'PC493', 'PC494', 'PC495', 'PC496', 'PC497', 'PC498', 'PC499'], columns=['PC'])
    df_explainedvariance = pd.concat([pc_df,explained_variance_df,cumulative_variance_df], axis=1).dropna()
    print("tables of variance ",df_explainedvariance)

    # max value for multiple columns
    max_val = df_explainedvariance[['Explained Variance']].max()
    print("Max Variance ",max_val)
    #max value and sum of the explained variance
    print("somme totale variance ",df_explainedvariance[['Explained Variance']].sum())

     # explained variance + cumulative variance (separate plot)
    fig = make_subplots(rows=3, cols=1)

    fig.add_trace(
        go.Scatter(
            x=df_explainedvariance['PC'],
            y=df_explainedvariance['Cumulative Variance'],
            marker=dict(size=15, color="LightSeaGreen")
        ), row=1, col=1
        )

    fig.add_trace(
        go.Bar(
            x=df_explainedvariance['PC'],
            y=df_explainedvariance['Explained Variance'],
            marker=dict(color="RoyalBlue"),
        ), row=3, col=1
        )
    fig.show()

    return principal.components_, explained_variance, principal.singular_values_


#check which image has the least n_components if we retain 85% of the variance
def number_pc(img):
    # principal component analysis on images

    #Scale data before applying PCA
    scaling = StandardScaler()
    data = img.data

    #use fit and transform method
    scaling.fit(data)
    Scaled_data = scaling.transform(data)

    #set the n_components
    principal = PCA(n_components=0.85)
    principal.fit(Scaled_data)
    x = principal.transform(Scaled_data)
    # Check the values of eigen vectors
    # prodeced by principal components
    #print("Principal components \n",len(principal.components_))

    return len(principal.components_)

#function to retrieve parameter values from cta dataset
def get_img(fname):
    file = tables.open_file(fname,"r")
    #visualize images from the telescope
    img = file.root.dl1.event.telescope.images.LST_LSTCam.col("image")
    #number of images in fname
    nb_img = img.shape[0]

    return  img, nb_img

def get_img_matrix(img, nb_img):
    htable = np.fromfile("injunction_table_lst.pny", offset=8, dtype=np.uint16)
    matrix = np.zeros(55*55)

    mat = np.zeros((nb_img,55,55),dtype=np.float32)

    for i in range(nb_img):
        matrix[htable] = img[i]
        res = matrix.reshape(55,55)
        mat[i] = res

    return mat

#retrieve all the files from our dataset
train_fnames = glob.glob('Data/training/*.h5',recursive=True)
test_fnames = glob.glob('Data/testing/*.h5',recursive=True)
images = np.zeros((0,1855))
#mat_val = []

for inputfile in tqdm.tqdm(train_fnames + test_fnames):
    image, size = get_img(inputfile)
    images = np.concatenate((images,image))
    #mat_val.append( get_img_matrix(image,size))

#pc, variance, sv = pca(images)


#find the image which requires the least number of principal components 

# val = number_pc(images)

# print("least number of PC is from image ", min(val, key=val.get))

if __name__ == '__main__':
    
    #retrieve all the files from our dataset
    test_fnames = glob.glob('Data/testing/*.h5',recursive=True) #500 files
    train_fnames = glob.glob('Data/training/*.h5',recursive=True) #500 files

    process_listfile(test_fnames+train_fnames,"./configTestFiles", images)