/***************************************
	Auteur : Pierre Aubert
	Mail : pierre.aubert@lapp.in2p3.fr
	Licence : CeCILL-C
****************************************/

#include "configTable.h"
#include "/home/khadimou/usr/include/StringUtils/string_utils.h"

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
		float impact = table.getImpact(i);
		//std::cout << "alpha = " << angle(x,y,x,y) << std::endl;
 		float alpha = table.getAlpha(i);
		for(size_t j(0lu); j < nb_vs; ++j){
			
			sv[j] = 29lu*(i*nbRow +j*nb_vs ) % 19lu;
			
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
	table.read(file.openGroup("Shower"));
	//Now we can close the file and use the Table directly
	file.close();
	
	//Get the number of rows and number of columns
	size_t nbRow = table.getNbEntries(), nb_vs = table.getNb_vs();
	std::cout << "nbevent " << nbRow << "\n";
	bool b(true);
	for(size_t i(0); i < nbRow; ++i){
		size_t eventId(table.getEventId(i));
		
		float *sv = table.getSv(i);
	 	table.getRow(i,table.getImax(i),table.getAlpha(i),table.getEnergy(i),table.getHfirstint(i),eventId,table.getImpact(i),sv,table.getX(i),table.getY(i));
	
	}
	return b;
}

int main(int argc, char** argv){
	// open file
	// H5::H5File fid("/home/khadimou/Stage/hash_training/hash_train8.h5",H5F_ACC_RDONLY);

	// //Let's create our table
	// TableEvent tab;
	// tab.read(fid.openGroup("Shower"));
	
	// size_t nbEvent(tab.getNbEntries());
	// std::cout << "nbevent " << nbEvent << "\n";
	// size_t nb_vs(55lu);
	// tab.setAllDim(nb_vs);
	// tab.resize(nbEvent);
	

	// for(size_t i(0lu); i<nbEvent; i++){
	
	// 	float *sv = tab.getSv(i);
	// 	tab.setRow(i,tab.getImax(i),tab.getAlpha(i),tab.getEnergy(i),tab.getHfirstint(i),tab.getEventId(i),tab.getImpact(i),sv,tab.getX(i),tab.getY(i));
	// }

	// //Now let's open a file
	// H5::H5File output("montest.h5", H5F_ACC_TRUNC);
	// //And write our table directly in it
	// tab.write(output);
	
	// fid.close();
	// output.close();

	// std::string fileName("configTable_full.h5");
	bool b(true);
	
	// b &= testWriteData(fileName);
	b &= testReadData("/home/khadimou/Stage/hash_training/hash_train8.h5");
	std::cout << "b = " << b << std::endl;
	return b - 1;
}

