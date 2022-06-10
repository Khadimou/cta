/***************************************
	Auteur : Pierre Aubert
	Mail : pierre.aubert@lapp.in2p3.fr
	Licence : CeCILL-C
****************************************/

#include "configTable.h"
#include <cmath>

constexpr double pi = std::acos(-1);

//compute impact parameter
float cip(float x,float y,float pos_x,float pos_y){
	return std::sqrt(std::pow((x-pos_x),2) + std::pow((y-pos_y),2));
}
    

//compute alpha angle at position j
float angle(float x,float y,float pos_x,float pos_y){
	return atan2(y-pos_y,x-pos_x) *  180 / pi;
}

///Test to write data
/**	@param fileName : name of the file to be written
 * 	@return true on success, false otherwise
*/
bool testWriteData(const std::string & fileName){
	TableEvent table;
	size_t nbRow(10lu),  nb_vs(55lu);
	table.setAllDim(nb_vs);
	table.resize(nbRow);
	
	//Let's set some values in the Table
	for(size_t i(0lu); i < nbRow; ++i){
		table.setEventId(i, i);
		float *sv = table.getSv(i);
		float energy = table.getEnergy(i);
 		float hfirstint = table.getHfirstint(i);
		float Imax = table.getImax(i);
 		float x = table.getX(i);
		float y = table.getY(i);
		float impact = table.getImpact(cip(x,y,x,y));
		//std::cout << "alpha = " << angle(x,y,x,y) << std::endl;
 		float alpha = table.getAlpha(angle(x,y,x,y));
		for(size_t j(0lu); j < nb_vs; ++j){
			
			sv[j] = 29lu*(i*nbRow +j*nb_vs ) % 19lu;
			
		}
		char *hash= table.getHash(i);
		for(size_t k(0lu); k < TABLEEVENT_HASH_0; ++k){
			hash[k] = 43lu*(i*nbRow + k) % 17lu;
		}
	}
	
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
	table.read(file);
	//Now we can close the file and use the Table directly
	file.close();
	
	//Get the number of rows and number of columns
	size_t nbRow = table.getNbEntries(), nb_vs = table.getNb_vs();
	bool b(true);
	for(size_t i(0lu); i < nbRow; ++i){
		size_t eventId(0lu);
		size_t fileId(0lu);
		
		float *sv = NULL;
		char *hash= NULL;
		float energy(0.0), hfirstint(0.0), impact(0.0), alpha(0.0), x(0.0), y(0.0), Imax(0.0);
		table.getRow(i, eventId, fileId,energy, hfirstint, Imax, impact, x, y, hash, sv, alpha);
		
		for(size_t j(0lu); j < nb_vs; ++j){
			
			b &= sv[i*nb_vs +j] == 29lu*(i*nbRow +j*nb_vs ) % 19lu;
			
		}
		for(size_t k(0lu); k < TABLEEVENT_HASH_0; ++k){
			b &= hash[k] == 43lu*(i*nbRow + k) % 17lu;
		}
	}
	return b;
}

#include <vector>
#include <cassert>

int main(int argc, char** argv){
	// open file
	H5::H5File fid("/home/khadimou/Stage/hash_training/hash_train4.h5",H5F_ACC_RDONLY);

	//Let's create our table
	TableEvent tab;
	tab.openDataSetBlock(fid.openGroup("Shower/"), 5000lu);
	H5::DataSet ds = tab.openDataSet(fid.openGroup("Shower/"));
	size_t nbEvent(tab.getFullDataSetSize());
	std::cout << "nbevent " << nbEvent << "\n";
	size_t nb_vs(55lu);
	tab.setAllDim(nb_vs);
	tab.resize(nbEvent);


	/*
	* Get dataspace of the dataset.
	*/
	H5::DataSpace dataspace = ds.getSpace();

	int ndims = dataspace.getSimpleExtentNdims();
    assert(ndims == 1);
    hsize_t dim;
    dataspace.getSimpleExtentDims(&dim);

    H5::DataSpace memspace (ndims, &dim);

    std::vector<double> res (dim);

    ds.read(res.data(), H5::PredType::NATIVE_DOUBLE, memspace, dataspace);

    dataspace.close();
    memspace.close();
    ds.close();

	for(size_t i(0lu); i<nbEvent; i++){
		char *hash= tab.getHash(i);
		float *sv = tab.getSv(i);
		tab.setRow(i,tab.getEventId(i),tab.getFile_id(i),tab.getEnergy(i),tab.getHfirstint(i),
		tab.getImax(i),tab.getImpact(i),tab.getX(i),tab.getY(i),hash,sv,tab.getAlpha(i));
	}

	//Now let's open a file
	H5::H5File output("montest.h5", H5F_ACC_TRUNC);
	//And write our table directly in it
	tab.write(output);
	
	fid.close();
	output.close();

	// std::string fileName("configTable_full.h5");
	// bool b(true);
	
	// b &= testWriteData(fileName);
	// b &= testReadData(fileName);
	// std::cout << "b = " << b << std::endl;
	// return b - 1;
}

