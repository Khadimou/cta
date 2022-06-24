/***************************************
	Auteur : Pierre Aubert
	Mail : pierre.aubert@lapp.in2p3.fr
	Licence : CeCILL-C
****************************************/

#include "configTable.h"
#include <list>
#include <string_system.h>
#include <algorithm>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>

using namespace cv;

PCA compressPCA(const Mat& pcaset, int maxComponents)
{
    PCA pca(pcaset, // pass the data
            Mat(), // we do not have a pre-computed mean vector,
                   // so let the PCA engine to compute it
            PCA::DATA_AS_ROW, // indicate that the vectors
                                // are stored as matrix rows
                                // (use PCA::DATA_AS_COL if the vectors are
                                // the matrix columns)
            maxComponents // specify, how many principal components to retain
            );
    
    return pca;
}

Mat get_val(const std::string &fname){
	H5::H5File file(fname, H5F_ACC_RDONLY);
	space tab_projection;

	tab_projection.read(file.openGroup("dl1"));
	file.close();
	size_t nbrow(tab_projection.getNbEntries()), nb_pixels(1855lu);
	//std::cout << "nbrow " << nbrow << "\n";

	tab_projection.setAllDim(nb_pixels);
	tab_projection.resize(nbrow);
	Mat m;
	float *img;

	for(size_t i(0lu); i<nbrow; ++i){
		img = tab_projection.getImages(i);
		m = Mat(55,55,CV_32F, img); 
	}

	return m;
}

size_t get_nrows(const std::string &fname){
	H5::H5File file(fname, H5F_ACC_RDONLY);
	space tab_projection;

	tab_projection.read(file.openGroup("dl1"));
	file.close();
	size_t nbrow(tab_projection.getNbEntries());
	return nbrow;
}

///Test to write data
/**	@param fileName : name of the file to be written
 * 	@return true on success, false otherwise
*/
bool testWriteData(const std::string & fileName){
	TableEvent table;
	size_t nbRow(table.getNbEntries()),  nb_vs(55lu);
	table.setAllDim(nb_vs);
	table.resize(nbRow);
	
	//Now let's open a file
	H5::H5File file(fileName, H5F_ACC_TRUNC);
	//And write our table directly in it
	table.write(file);
	//We can also explicitly cloase the file, otherwise it will do it automatically
	file.close();
	return true;
}

///Test to read data
/**	@param fileName : name of the file to be read
 * 	@return true on success, false otherwise
*/
bool testReadData(const std::string & fileName){
	//First let's open a file in read only mode (better for concurencial access)
	H5::H5File file(fileName, H5F_ACC_RDONLY);
	//Let's create our table
	TableEvent table;
	//Add read the file
	table.read(file.openGroup("Shower"));
	//Now we can close the file and use the Table directly
	file.close();
	
	//Get the number of rows and number of columns
	size_t nbRow = table.getNbEntries(), nb_vs = table.getNb_vs();
	//std::cout << "nbevent " << nbRow << "\n";
	table.setAllDim(nb_vs);
	table.resize(nbRow);
	bool b(true);
	for(size_t i(0); i < nbRow; ++i){
		size_t eventId(table.getEventId(i));
		
		float *sv = table.getSv(i);
	 	table.getRow(i,table.getImax(i),table.getAlpha(i),table.getEnergy(i),table.getHfirstint(i),eventId,table.getImpact(i),sv,table.getX(i),table.getY(i));
	
	}
	return b;
}

std::vector<std::tuple<std::string, int, int>> getFileOffset(size_t nbevent, size_t nbrow, const std::string &fname)
{
	std::vector<std::tuple<std::string, int, int>> all_files;

	all_files.push_back(std::make_tuple(fname,nbevent,nbrow));

	return all_files;
}

int main(int argc, char** argv){
	
	std::list<std::string> output;
	bool b(true);

	getListAllFileInDir(output, "/home/khadimou/Stage/hash_training");
	for(std::string fname: output){
		//std::cout << fname << std::endl;
		std::string param = "/home/khadimou/Stage/hash_training/";
		param.append(fname);
		//b &= testReadData(param);
	}

	std::list<std::string> dir;
	size_t nbevent{0}, nbrow;
	Mat img_matrix, sv;
	std::vector<std::tuple<std::string, int, int>> file_offset;
	std::vector<std::vector<std::tuple<std::string, int, int>>> all_files;
	getListAllFileInDir(dir, "/home/khadimou/Stage/Data/training");
	for(std::string fname: dir){
		std::string param = "/home/khadimou/Stage/Data/training/";
		param.append(fname);
		//std::cout << param << std::endl;
		img_matrix = get_val(param);
		nbrow = get_nrows(param);
		nbevent += nbrow;
		file_offset = getFileOffset(nbevent,nbrow,param);
		all_files.push_back(file_offset);
	}
	
	// for(int k=0; k<dir.size();k++){
	// 	std::cout << "file offset " << std::get<1>(all_files[k][0]) << "\n";
	// }

	PCA pc = compressPCA(img_matrix,55);
	SVD::compute(img_matrix, sv, SVD::NO_UV);
	std::cout << "singular values " << sv << "\n";
	std::cout << "pca singular values " << pc.eigenvalues << "\n";

	return b-1;
}

