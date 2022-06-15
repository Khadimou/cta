/***************************************
	Auteur : Pierre Aubert
	Mail : pierre.aubert@lapp.in2p3.fr
	Licence : CeCILL-C
****************************************/

#include "configTable.h"

///Check the generated table of data
/**	@param tab : table of data
 * 	@return true on success, false otherwise
*/
bool checkGeneratedTableConst(const TableEvent & tab){
	bool b(true);
	
	std::cout << "checkGeneratedTable : get event id" << tab.getEventId(0) << std::endl;
	b &= tab.getEventIdFull() != NULL;

	b &= tab.getImax(0) != NULL;
	b &= tab.getImaxFull() != NULL;

	b &= tab.getAlpha(0) != NULL;
	b &= tab.getAlphaFull() != NULL;

	b &= tab.getEnergy(0) != NULL;
	b &= tab.getEnergyFull() != NULL;
	
	b &= tab.getHfirstint(0) != NULL;
	b &= tab.getHfirstintFull() != NULL;

	b &= tab.getImpact(0) != NULL;
	b &= tab.getImpactFull() != NULL;

	b &= tab.getSv(0) != NULL;
	b &= tab.getSvFull() != NULL;

	b &= tab.getX(0) != NULL;
	b &= tab.getXFull() != NULL;

	b &= tab.getY(0) != NULL;
	b &= tab.getYFull() != NULL;
	
	return b;
}

///Check the generated table of data
/**	@param tab : table of data
 * 	@return true on success, false otherwise
*/
bool checkGeneratedTable(TableEvent & tab){
	bool b(true);
	
	std::cout << "checkGeneratedTable : get event id" << tab.getEventId(0) << std::endl;
	b &= tab.getEventIdFull() != NULL;
	
	b &= tab.getImax(0) != NULL;
	b &= tab.getImaxFull() != NULL;

	b &= tab.getAlpha(0) != NULL;
	b &= tab.getAlphaFull() != NULL;

	b &= tab.getEnergy(0) != NULL;
	b &= tab.getEnergyFull() != NULL;
	
	b &= tab.getHfirstint(0) != NULL;
	b &= tab.getHfirstintFull() != NULL;

	b &= tab.getImpact(0) != NULL;
	b &= tab.getImpactFull() != NULL;

	b &= tab.getSv(0) != NULL;
	b &= tab.getSvFull() != NULL;

	b &= tab.getX(0) != NULL;
	b &= tab.getXFull() != NULL;

	b &= tab.getY(0) != NULL;
	b &= tab.getYFull() != NULL;
	
	return b;
}

///Test to write data
/**	@param fileName : name of the file to be written
 * 	@return true on success, false otherwise
*/
bool testWriteData(const std::string & fileName){
	TableEvent table;
	size_t nbRow(10lu), nb_vs(55lu);
	table.setAllDim(nb_vs);
	table.resize(nbRow);
	
	bool b(true);
	b &= checkGeneratedTableConst(table);
	b &= checkGeneratedTable(table);
	
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
	
	
	//And write our table directly in it
	table.write(fileName);
	return b;
}

///Test to read data
/**	@param fileName : name of the file to be read
 * 	@return true on success, false otherwise
*/
bool testReadData(const std::string & fileName){
	//Let's create our table
	TableEvent table;
	//Add read the file
	table.read(fileName);
	
	//Get the number of rows and number of columns
	size_t nbRow = table.getNbEntries(), nb_vs = table.getNb_vs();
	std::cout << "testReadData : nbRow = " << nbRow << ", nb_vs = " << nb_vs << std::endl;
	bool b(true);
	for(size_t i(0lu); i < nbRow; ++i){
		size_t eventId(0lu);
		size_t fileId(0lu);
		
		float *sv = NULL;
		
		float energy(0.0), hfirstint(0.0), impact(0.0), alpha(0.0), x(0.0), y(0.0), Imax(0.0);
		table.getRow(i, Imax, alpha, energy, hfirstint, eventId, impact, sv, x, y);
		
		for(size_t j(0lu); j < nb_vs; ++j){
			
			b &= sv[i*nb_vs +j] == 29lu*(i*nbRow +j*nb_vs ) % 19lu;
			
		}
		
	}
	std::cout << "testReadBlockData : b = " << b << std::endl;
	return b;
}

///Test to read block data
/**	@param fileName : name of the file to be read
 * 	@param nbTotalRow : total number of rows in the dataset
 * 	@param offset : offset of the first row to be read
 * 	@param nbRow : number of rows to be read
 * 	@return true on success, false otherwise
*/
bool testReadBlockData(const std::string & fileName, size_t nbTotalRow, size_t offset, size_t nbRow){
	//Let's create our table
	TableEvent table;
	//Add read the file
	table.read(fileName, offset, nbRow);
	
	//Get the number of rows and number of columns
	size_t nb_vs = table.getNb_vs();
	std::cout << "testReadBlockData : nbRow = " << nbRow << ", nb_vs = " << nb_vs << std::endl;
	bool b(true);
	for(size_t i(0lu); i < nbRow; ++i){
		size_t eventId(0lu);
		size_t fileId(0lu);
		
		float *sv = NULL;
	
		float energy(0.0), hfirstint(0.0), impact(0.0), alpha(0.0), x(0.0), y(0.0), Imax(0.0);
		table.getRow(i, Imax, alpha, energy,  hfirstint, eventId, impact, sv, x, y);
		
		for(size_t j(0lu); j < nb_vs; ++j){
			
			b &= sv[i*nb_vs +j] == 29lu*(i*nbRow +j*nb_vs ) % 19lu;
			
		}
	
	}
	std::cout << "testReadBlockData : b = " << b << std::endl;
	return b;
}

int main(int argc, char** argv){
	std::string fileName("configTable.h5");
	bool b(true);
	b &= testWriteData(fileName);
	b &= testReadData(fileName);
	b &= testReadBlockData(fileName, 10lu, 0lu, 10lu);
	b &= testReadBlockData(fileName, 10lu, 1lu, 5lu);
	b &= testReadBlockData(fileName, 10lu, 3lu, 4lu);
	b &= testReadBlockData(fileName, 10lu, 5lu, 5lu);
	b &= testReadBlockData(fileName, 10lu, 2lu, 8lu);
	return b - 1;
}

