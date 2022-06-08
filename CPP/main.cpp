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
	
	std::cout << "checkGeneratedTable : get event id" << tab.getTimestamp(0) << std::endl;
	b &= tab.getTimestampFull() != NULL;
	
	b &= tab.getCalibSignal(0) != NULL;
	b &= tab.getCalibSignalFull() != NULL;
	
	b &= tab.getWaveform(0) != NULL;
	b &= tab.getWaveformFull() != NULL;
	
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
	
	std::cout << "checkGeneratedTable : get event id" << tab.getTimestamp(0) << std::endl;
	b &= tab.getTimestampFull() != NULL;
	
	b &= tab.getCalibSignal(0) != NULL;
	b &= tab.getCalibSignalFull() != NULL;
	
	b &= tab.getWaveform(0) != NULL;
	b &= tab.getWaveformFull() != NULL;
	
	return b;
}

///Test to write data
/**	@param fileName : name of the file to be written
 * 	@return true on success, false otherwise
*/
bool testWriteData(const std::string & fileName){
	TableEvent table;
	size_t nbRow(10lu), nbSlice(40lu), nbPixel(1855lu);
	table.setAllDim(nbPixel, nbSlice);
	table.resize(nbRow);
	
	bool b(true);
	b &= checkGeneratedTableConst(table);
	b &= checkGeneratedTable(table);
	
	//Let's set some values in the Table
	for(size_t i(0lu); i < nbRow; ++i){
		table.setEventId(i, i);
		table.setTimestamp(i, 2lu*i);
		unsigned short * waveform = table.getWaveform(i);
		for(size_t j(0lu); j < nbSlice; ++j){
			for(size_t k(0lu); k < nbPixel; ++k){
				waveform[j*nbPixel + k] = 29lu*(i*nbRow +j*nbPixel + k) % 19lu;
			}
		}
		float * tabSignal = table.getCalibSignal(i);
		for(size_t k(0lu); k < nbPixel; ++k){
			tabSignal[k] = 43lu*(i*nbRow + k) % 17lu;
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
	size_t nbRow = table.getNbEntries(), nbPixel = table.getNbPixel(), nbSlice = table.getNbSlice();
	std::cout << "testReadData : nbRow = " << nbRow << ", nbPixel = " << nbPixel << ", nbSlice = " << nbSlice << std::endl;
	bool b(true);
	for(size_t i(0lu); i < nbRow; ++i){
		b &= table.getEventId(i) == i;
		b &= table.getTimestamp(i) == 2lu*i;
		
		unsigned short * waveform = table.getWaveform(i);
		for(size_t j(0lu); j < nbSlice; ++j){
			for(size_t k(0lu); k < nbPixel; ++k){
				b &= waveform[j*nbPixel + k] == 29lu*(i*nbRow +j*nbPixel + k) % 19lu;
			}
		}
		float * tabSignal = table.getCalibSignal(i);
		for(size_t k(0lu); k < nbPixel; ++k){
			b &= tabSignal[k] == 43lu*(i*nbRow + k) % 17lu;
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
	size_t nbPixel = table.getNbPixel(), nbSlice = table.getNbSlice();
	std::cout << "testReadBlockData : nbRow = " << nbRow << ", nbPixel = " << nbPixel << ", nbSlice = " << nbSlice << std::endl;
	bool b(true);
	for(size_t i(0lu); i < nbRow; ++i){
		b &= table.getEventId(i) == (i + offset);
		b &= table.getTimestamp(i) == 2lu*(i + offset);
		
		unsigned short * waveform = table.getWaveform(i);
		for(size_t j(0lu); j < nbSlice; ++j){
			for(size_t k(0lu); k < nbPixel; ++k){
				b &= waveform[j*nbPixel + k] == 29lu*((i + offset)*nbTotalRow +j*nbPixel + k) % 19lu;
			}
		}
		float * tabSignal = table.getCalibSignal(i);
		for(size_t k(0lu); k < nbPixel; ++k){
			b &= tabSignal[k] == 43lu*((i + offset)*nbTotalRow + k) % 17lu;
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

