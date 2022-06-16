/***************************************
	Auteur : Pierre Aubert
	Mail : pierre.aubert@lapp.in2p3.fr
	Licence : CeCILL-C
****************************************/

#include "configTable.h"
#include <list>
#include <string_system.h>

///Test to write data
/**	@param fileName : name of the file to be written
 * 	@return true on success, false otherwise
*/
bool testWriteData(const std::string & fileName){
	TableEvent table;
	size_t nbRow(table.getNbEntries()),  nb_vs(55lu);
	table.setAllDim(nb_vs);
	table.resize(nbRow);
	
	//Let's set some values in the Table
	for(size_t i(0lu); i < nbRow; ++i){
		table.setEventId(i, table.getEventId(i));
		float *sv = table.setSv(i,table.getSv(i));
		float energy = table.setEnergy(i,table.getEnergy(i));
 		float hfirstint = table.setHfirstint(i, table.getHfirstint(i));
		float Imax = table.setImax(i, table.getImax(i));
 		float x = table.setX(i, table.getX(i));
		float y = table.setY(i, table.getY(i));
		float impact = table.setImpact(i, table.getImpact(i));
		
 		float alpha = table.setAlpha(i, table.getAlpha(i));
		
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
	table.read(file.openGroup("Shower"));
	//Now we can close the file and use the Table directly
	file.close();
	
	//Get the number of rows and number of columns
	size_t nbRow = table.getNbEntries(), nb_vs = table.getNb_vs();
	std::cout << "nbevent " << nbRow << "\n";
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

int main(int argc, char** argv){
	
	std::list<std::string> output;
	bool b(true);

	getListAllFileInDir(output, "/home/khadimou/Stage/hash_training");
	for(std::string fname: output){
		std::cout << fname << std::endl;
		std::string param = "/home/khadimou/Stage/hash_training/";
		param.append(fname);
		b &= testReadData(param);
	}

	return b-1;
}

