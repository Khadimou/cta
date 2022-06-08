/***************************************
	Auteur : Pierre Aubert
	Mail : pierre.aubert@lapp.in2p3.fr
	Licence : CeCILL-C
****************************************/

#include "configTable.h"

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
		float *w = table.getSv(i);
		for(size_t j(0lu); j < nb_vs; ++j){
			
			w[j] = 29lu*(i*nbRow +j*nb_vs ) % 19lu;
			
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
		
		//table.getRow(i, eventId);
		const float *w = table.getSv(i);
		const char *hash= table.getHash(i);
		
		for(size_t j(0lu); j < nb_vs; ++j){
			
			b &= w[i*nb_vs +j] == 29lu*(i*nbRow +j*nb_vs ) % 19lu;
			
		}
		for(size_t k(0lu); k < TABLEEVENT_HASH_0; ++k){
			b &= hash[k] == 43lu*(i*nbRow + k) % 17lu;
		}
	}
	return b;
}

int main(int argc, char** argv){
	std::string fileName("configTable_full.h5");
	bool b(true);
	
	b &= testWriteData(fileName);
	b &= testReadData(fileName);
	std::cout << "b = " << b << std::endl;
	return b - 1;
}

