/***************************************
	Auteur : Pierre Aubert
	Mail : pierre.aubert@lapp.in2p3.fr
	Licence : CeCILL-C
****************************************/


//Warning : this file has been generated automatically by the phoenix_hdf5 program
//You can find it at https://gitlab.in2p3.fr/CTA-LAPP/PHOENIX_LIBS/PhoenixHDF5
//Do NOT modify it


#ifndef __CONFIGTABLE_H__
#define __CONFIGTABLE_H__

#include <iostream>
#include "H5Cpp.h"

///Table of types
class TableEvent{
	public:
		TableEvent();
		TableEvent(const TableEvent & other);
		virtual ~TableEvent();

		TableEvent & operator = (const TableEvent & other);
		void setTableName(const std::string & name);
		size_t getNbEntries() const;
		void resize(size_t nbRow);
		void clear();

		void read(const std::string & fileName);
		void read(const H5::H5File & file);
		void read(const H5::Group & group);

		void read(const std::string & fileName, size_t offset, size_t nbRow);
		void read(const H5::H5File & file, size_t offset, size_t nbRow);
		void read(const H5::Group & group, size_t offset, size_t nbRow);

		void write(const std::string & fileName) const;
		void write(H5::H5File & file) const;
		void write(H5::Group & group) const;

		H5::DataSet createDataSet(const std::string & fileName, size_t nbRow) const;
		H5::DataSet createDataSet(H5::H5File & file, size_t nbRow) const;
		H5::DataSet createDataSet(H5::Group & group, size_t nbRow) const;

		H5::DataSet openDataSet(const std::string & fileName) const;
		H5::DataSet openDataSet(const H5::H5File & file) const;
		H5::DataSet openDataSet(const H5::Group & group) const;

		void openDataSetBlock(const std::string & fileName, size_t nbMaxRowPerBlock);
		void openDataSetBlock(const H5::H5File & file, size_t nbMaxRowPerBlock);
		void openDataSetBlock(const H5::Group & group, size_t nbMaxRowPerBlock);

		void setRow(size_t i, float Imax, float alpha, float energy, float hfirstint, size_t eventId, float impact, float * sv, float x, float y);
		void getRow(size_t i, float & Imax, float & alpha, float & energy, float & hfirstint, size_t & eventId, float & impact, float *& sv, float & x, float & y);
		void getRow(size_t i, float & Imax, float & alpha, float & energy, float & hfirstint, size_t & eventId, float & impact, const float *& sv, float & x, float & y) const;
		void setImax(size_t i, float val);
		void setAlpha(size_t i, float val);
		void setEnergy(size_t i, float val);
		void setHfirstint(size_t i, float val);
		void setEventId(size_t i, size_t val);
		void setImpact(size_t i, float val);
		void setSv(size_t i, const float * tabVal);
		void setX(size_t i, float val);
		void setY(size_t i, float val);
		const float * getImaxFull() const;
		float * getImaxFull();
		float getImax(size_t i) const;
		float & getImax(size_t i);
		const float * getAlphaFull() const;
		float * getAlphaFull();
		float getAlpha(size_t i) const;
		float & getAlpha(size_t i);
		const float * getEnergyFull() const;
		float * getEnergyFull();
		float getEnergy(size_t i) const;
		float & getEnergy(size_t i);
		const float * getHfirstintFull() const;
		float * getHfirstintFull();
		float getHfirstint(size_t i) const;
		float & getHfirstint(size_t i);
		const size_t * getEventIdFull() const;
		size_t * getEventIdFull();
		size_t getEventId(size_t i) const;
		size_t & getEventId(size_t i);
		const float * getImpactFull() const;
		float * getImpactFull();
		float getImpact(size_t i) const;
		float & getImpact(size_t i);
		const float * getSvFull() const;
		float * getSvFull();
		const float * getSv(size_t i) const;
		float * getSv(size_t i);
		const float * getXFull() const;
		float * getXFull();
		float getX(size_t i) const;
		float & getX(size_t i);
		const float * getYFull() const;
		float * getYFull();
		float getY(size_t i) const;
		float & getY(size_t i);

		size_t getOffsetImax() const;
		size_t getOffsetAlpha() const;
		size_t getOffsetEnergy() const;
		size_t getOffsetHfirstint() const;
		size_t getOffsetEventId() const;
		size_t getOffsetImpact() const;
		size_t getOffsetSv() const;
		size_t getOffsetX() const;
		size_t getOffsetY() const;
		H5::CompType getCompTypeAll() const;
		H5::CompType getCompTypeImax() const;
		H5::CompType getCompTypeAlpha() const;
		H5::CompType getCompTypeEnergy() const;
		H5::CompType getCompTypeHfirstint() const;
		H5::CompType getCompTypeEventId() const;
		H5::CompType getCompTypeImpact() const;
		H5::CompType getCompTypeSv() const;
		H5::CompType getCompTypeX() const;
		H5::CompType getCompTypeY() const;
		H5::DataType getTypeImax() const;
		H5::DataType getTypeAlpha() const;
		H5::DataType getTypeEnergy() const;
		H5::DataType getTypeHfirstint() const;
		H5::DataType getTypeEventId() const;
		H5::DataType getTypeImpact() const;
		H5::DataType getTypeSv() const;
		H5::DataType getTypeX() const;
		H5::DataType getTypeY() const;

		void setAllDim(size_t nb_vs);
		void setNb_vs(size_t val);
		size_t getNb_vs() const;

		void readDataSet(const H5::DataSet & dataset);
		void readDataSet(const H5::DataSet & dataset, size_t offset, size_t nbRow);
		void writeDataSet(H5::DataSet & dataset) const;
		void openDataSetBlock(const H5::DataSet & dataset, size_t nbMaxRowPerBlock);
		bool iterateBlock();
		size_t getFullDataSetSize() const;
		size_t getBlockSize() const;
		size_t getBlockOffset() const;

	private:
		void initialisationTableEvent();
		void allocate(size_t nbRow);
		void copyTableEvent(const TableEvent & other);
		void readDimSv(const H5::CompType & compType);

		///Number of rows in the table TableEvent
		size_t p__nbRow;

		///HDF5 name of the table TableEvent
		std::string p__tableName;

		///DataSet we have to use (only with openDataSetBlock)
		H5::DataSet p__dataset;
		///Total number of rows in the DataSet we have to use (only with openDataSetBlock)
		size_t p__totalDataSetRow;
		///Size of the block to be used (only with openDataSetBlock)
		size_t p__blockSize;
		///Offset of the current block (only with openDataSetBlock)
		size_t p__blockOffset;

		///Tensor dimension nb_vs
		size_t p_nb_vs;

		float * p_Imax;
		float * p_alpha;
		float * p_energy;
		float * p_hfirstint;
		///Event id
		size_t * p_eventId;
		float * p_impact;
		float * p_sv;
		float * p_x;
		float * p_y;
};

class space{
	public:
		space();
		space(const space & other);
		virtual ~space();

		space & operator = (const space & other);
		void setTableName(const std::string & name);
		size_t getNbEntries() const;
		void resize(size_t nbRow);
		void clear();

		void read(const std::string & fileName);
		void read(const H5::H5File & file);
		void read(const H5::Group & group);

		void read(const std::string & fileName, size_t offset, size_t nbRow);
		void read(const H5::H5File & file, size_t offset, size_t nbRow);
		void read(const H5::Group & group, size_t offset, size_t nbRow);

		void write(const std::string & fileName) const;
		void write(H5::H5File & file) const;
		void write(H5::Group & group) const;

		H5::DataSet createDataSet(const std::string & fileName, size_t nbRow) const;
		H5::DataSet createDataSet(H5::H5File & file, size_t nbRow) const;
		H5::DataSet createDataSet(H5::Group & group, size_t nbRow) const;

		H5::DataSet openDataSet(const std::string & fileName) const;
		H5::DataSet openDataSet(const H5::H5File & file) const;
		H5::DataSet openDataSet(const H5::Group & group) const;

		void openDataSetBlock(const std::string & fileName, size_t nbMaxRowPerBlock);
		void openDataSetBlock(const H5::H5File & file, size_t nbMaxRowPerBlock);
		void openDataSetBlock(const H5::Group & group, size_t nbMaxRowPerBlock);

		void setRow(size_t i, float * images);
		void getRow(size_t i, float *& images);
		void getRow(size_t i, const float *& images) const;
		void setImages(size_t i, const float * tabVal);
		const float * getImagesFull() const;
		float * getImagesFull();
		const float * getImages(size_t i) const;
		float * getImages(size_t i);

		size_t getOffsetImages() const;
		H5::CompType getCompTypeAll() const;
		H5::CompType getCompTypeImages() const;
		H5::DataType getTypeImages() const;

		void setAllDim(size_t nb_pixels);
		void setNb_pixels(size_t val);
		size_t getNb_pixels() const;

		void readDataSet(const H5::DataSet & dataset);
		void readDataSet(const H5::DataSet & dataset, size_t offset, size_t nbRow);
		void writeDataSet(H5::DataSet & dataset) const;
		void openDataSetBlock(const H5::DataSet & dataset, size_t nbMaxRowPerBlock);
		bool iterateBlock();
		size_t getFullDataSetSize() const;
		size_t getBlockSize() const;
		size_t getBlockOffset() const;

	private:
		void initialisationspace();
		void allocate(size_t nbRow);
		void copyspace(const space & other);
		void readDimImages(const H5::CompType & compType);

		///Number of rows in the table space
		size_t p__nbRow;

		///HDF5 name of the table space
		std::string p__tableName;

		///DataSet we have to use (only with openDataSetBlock)
		H5::DataSet p__dataset;
		///Total number of rows in the DataSet we have to use (only with openDataSetBlock)
		size_t p__totalDataSetRow;
		///Size of the block to be used (only with openDataSetBlock)
		size_t p__blockSize;
		///Offset of the current block (only with openDataSetBlock)
		size_t p__blockOffset;

		///Tensor dimension nb_pixels
		size_t p_nb_pixels;

		float * p_images;
};

class componentsPrincipal{
	public:
		componentsPrincipal();
		componentsPrincipal(const componentsPrincipal & other);
		virtual ~componentsPrincipal();

		componentsPrincipal & operator = (const componentsPrincipal & other);
		void setTableName(const std::string & name);
		size_t getNbEntries() const;
		void resize(size_t nbRow);
		void clear();

		void read(const std::string & fileName);
		void read(const H5::H5File & file);
		void read(const H5::Group & group);

		void read(const std::string & fileName, size_t offset, size_t nbRow);
		void read(const H5::H5File & file, size_t offset, size_t nbRow);
		void read(const H5::Group & group, size_t offset, size_t nbRow);

		void write(const std::string & fileName) const;
		void write(H5::H5File & file) const;
		void write(H5::Group & group) const;

		H5::DataSet createDataSet(const std::string & fileName, size_t nbRow) const;
		H5::DataSet createDataSet(H5::H5File & file, size_t nbRow) const;
		H5::DataSet createDataSet(H5::Group & group, size_t nbRow) const;

		H5::DataSet openDataSet(const std::string & fileName) const;
		H5::DataSet openDataSet(const H5::H5File & file) const;
		H5::DataSet openDataSet(const H5::Group & group) const;

		void openDataSetBlock(const std::string & fileName, size_t nbMaxRowPerBlock);
		void openDataSetBlock(const H5::H5File & file, size_t nbMaxRowPerBlock);
		void openDataSetBlock(const H5::Group & group, size_t nbMaxRowPerBlock);

		void setRow(size_t i, float * pc, float sv, float psv);
		void getRow(size_t i, float *& pc, float & sv, float & psv);
		void getRow(size_t i, const float *& pc, float & sv, float & psv) const;
		void setPc(size_t i, const float * tabVal);
		void setSv(size_t i, float val);
		void setPsv(size_t i, float val);
		const float * getPcFull() const;
		float * getPcFull();
		const float * getPc(size_t i) const;
		float * getPc(size_t i);
		const float * getSvFull() const;
		float * getSvFull();
		float getSv(size_t i) const;
		float & getSv(size_t i);
		const float * getPsvFull() const;
		float * getPsvFull();
		float getPsv(size_t i) const;
		float & getPsv(size_t i);

		size_t getOffsetPc() const;
		size_t getOffsetSv() const;
		size_t getOffsetPsv() const;
		H5::CompType getCompTypeAll() const;
		H5::CompType getCompTypePc() const;
		H5::CompType getCompTypeSv() const;
		H5::CompType getCompTypePsv() const;
		H5::DataType getTypePc() const;
		H5::DataType getTypeSv() const;
		H5::DataType getTypePsv() const;

		void setAllDim(size_t nb_pc);
		void setNb_pc(size_t val);
		size_t getNb_pc() const;

		void readDataSet(const H5::DataSet & dataset);
		void readDataSet(const H5::DataSet & dataset, size_t offset, size_t nbRow);
		void writeDataSet(H5::DataSet & dataset) const;
		void openDataSetBlock(const H5::DataSet & dataset, size_t nbMaxRowPerBlock);
		bool iterateBlock();
		size_t getFullDataSetSize() const;
		size_t getBlockSize() const;
		size_t getBlockOffset() const;

	private:
		void initialisationcomponentsPrincipal();
		void allocate(size_t nbRow);
		void copycomponentsPrincipal(const componentsPrincipal & other);
		void readDimPc(const H5::CompType & compType);

		///Number of rows in the table componentsPrincipal
		size_t p__nbRow;

		///HDF5 name of the table componentsPrincipal
		std::string p__tableName;

		///DataSet we have to use (only with openDataSetBlock)
		H5::DataSet p__dataset;
		///Total number of rows in the DataSet we have to use (only with openDataSetBlock)
		size_t p__totalDataSetRow;
		///Size of the block to be used (only with openDataSetBlock)
		size_t p__blockSize;
		///Offset of the current block (only with openDataSetBlock)
		size_t p__blockOffset;

		///Tensor dimension nb_pc
		size_t p_nb_pc;

		float * p_pc;
		float * p_sv;
		float * p_psv;
};

#endif

