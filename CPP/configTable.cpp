/***************************************
	Auteur : Pierre Aubert
	Mail : pierre.aubert@lapp.in2p3.fr
	Licence : CeCILL-C
****************************************/


//Warning : this file has been generated automatically by the phoenix_hdf5 program
//You can find it at https://gitlab.in2p3.fr/CTA-LAPP/PHOENIX_LIBS/PhoenixHDF5
//Do NOT modify it


#include <string.h>
#include <sstream>
#include "configTable.h"

///Constructor of the class TableEvent
TableEvent::TableEvent(){
	initialisationTableEvent();
}

///Copy constructor of the class TableEvent
/**	@param other : TableEvent to be copied
*/
TableEvent::TableEvent(const TableEvent & other){
	initialisationTableEvent();
	copyTableEvent(other);
}

///Destructor of the class TableEvent
TableEvent::~TableEvent(){
	clear();
}

///Equal operator of the class TableEvent
/**	@param other : TableEvent to be copied
 * 	@return copied TableEvent
*/
TableEvent & TableEvent::operator = (const TableEvent & other){
	copyTableEvent(other);
	return *this;
}

///Set the HDF5 name of the Table TableEvent
/**	@param name : name of the table to be saved
*/
void TableEvent::setTableName(const std::string & name){
	p__tableName = name;
}

///Get the total number of rows in the current Table TableEvent
/**	@return total number of rows
*/
size_t TableEvent::getNbEntries() const{
	return p__nbRow;
}

///Resize the table TableEvent
/*	@param nbRow : new number of rows of the Table
*/
void TableEvent::resize(size_t nbRow){
	if(nbRow == p__nbRow){return;}	//Nothing to do
	clear();
	allocate(nbRow);
}

///Clear the table TableEvent (delete all column)
void TableEvent::clear(){
	if(p_Imax != NULL){delete [] p_Imax;p_Imax = NULL;}
	if(p_alpha != NULL){delete [] p_alpha;p_alpha = NULL;}
	if(p_energy != NULL){delete [] p_energy;p_energy = NULL;}
	if(p_hfirstint != NULL){delete [] p_hfirstint;p_hfirstint = NULL;}
	if(p_eventId != NULL){delete [] p_eventId;p_eventId = NULL;}
	if(p_impact != NULL){delete [] p_impact;p_impact = NULL;}
	if(p_sv != NULL){delete [] p_sv;p_sv = NULL;}
	if(p_x != NULL){delete [] p_x;p_x = NULL;}
	if(p_y != NULL){delete [] p_y;p_y = NULL;}
}

///Read the table TableEvent from given file
/**	@param fileName : name of the HDF5 file to be used
*/
void TableEvent::read(const std::string & fileName){
	H5::H5File file(fileName, H5F_ACC_RDONLY);
	read(file);
}

///Read the table TableEvent from given file
/**	@param file : HDF5 file to be used
*/
void TableEvent::read(const H5::H5File & file){
	H5::DataSet dataset = openDataSet(file);
	readDataSet(dataset);
}

///Read the table TableEvent from given group
/**	@param group : HDF5 group to be used
*/
void TableEvent::read(const H5::Group & group){
	H5::DataSet dataset = openDataSet(group);
	readDataSet(dataset);
}

///Read the table TableEvent from given file
/**	@param fileName : name of the HDF5 file to be used
 * 	@param offset : index of the first row the TableEvent class needs to load
 * 	@param nbRow : number of rows the TableEvent class needs to load (Will reallocate the TableEvent is the number of rows is greater than the number off already allocated rows)
*/
void TableEvent::read(const std::string & fileName, size_t offset, size_t nbRow){
	H5::H5File file(fileName, H5F_ACC_RDONLY);
	read(file, offset, nbRow);
}

///Read the table TableEvent from given file
/**	@param file : HDF5 file to be used
 * 	@param offset : index of the first row the TableEvent class needs to load
 * 	@param nbRow : number of rows the TableEvent class needs to load (Will reallocate the TableEvent is the number of rows is greater than the number off already allocated rows)
*/
void TableEvent::read(const H5::H5File & file, size_t offset, size_t nbRow){
	H5::DataSet dataset = openDataSet(file);
	readDataSet(dataset, offset, nbRow);
}

///Read the table TableEvent from given group
/**	@param group : HDF5 group to be used
 * 	@param offset : index of the first row the TableEvent class needs to load
 * 	@param nbRow : number of rows the TableEvent class needs to load (Will reallocate the TableEvent is the number of rows is greater than the number off already allocated rows)
*/
void TableEvent::read(const H5::Group & group, size_t offset, size_t nbRow){
	H5::DataSet dataset = openDataSet(group);
	readDataSet(dataset, offset, nbRow);
}

///Create and write the table TableEvent in given file
/**	@param fileName : name of the HDF5 file to be used
*/
void TableEvent::write(const std::string & fileName) const{
	H5::H5File file(fileName, H5F_ACC_TRUNC);
	write(file);
}

///Create and write the table TableEvent in given file
/**	@param file : HDF5 file to be used
*/
void TableEvent::write(H5::H5File & file) const{
	H5::DataSet dataset = createDataSet(file, p__nbRow);
	writeDataSet(dataset);
}

///Create and write the table TableEvent in given file
/**	@param group : HDF5 group to be used
*/
void TableEvent::write(H5::Group & group) const{
	H5::DataSet dataset = createDataSet(group, p__nbRow);
	writeDataSet(dataset);
}

///Create and write the table TableEvent in given file
/**	@param fileName : name of the HDF5 file to be used
 * 	@param nbRow : full number of rows in the DataSet
 * 	@return created DataSet
*/
H5::DataSet TableEvent::createDataSet(const std::string & fileName, size_t nbRow) const{
	H5::H5File file(fileName, H5F_ACC_TRUNC);
	return createDataSet(file, nbRow);
}

///Create the DataSet of the table TableEvent in given file
/**	@param file : HDF5 file to be used
 * 	@param nbRow : full number of rows in the DataSet
 * 	@return created DataSet
*/
H5::DataSet TableEvent::createDataSet(H5::H5File & file, size_t nbRow) const{
	hsize_t dim[1];
	dim[0] = nbRow;
	H5::DataSpace space(1, dim);
	H5::DataSet dataset = file.createDataSet(p__tableName, getCompTypeAll(), space);
	return dataset;
}

///Create the DataSet of the table TableEvent in given group
/**	@param group : HDF5 group to be used
 * 	@param nbRow : full number of rows in the DataSet
 * 	@return created DataSet
*/
H5::DataSet TableEvent::createDataSet(H5::Group & group, size_t nbRow) const{
	hsize_t dim[1];
	dim[0] = nbRow;
	H5::DataSpace space(1, dim);
	H5::DataSet dataset = group.createDataSet(p__tableName, getCompTypeAll(), space);
	return dataset;
}

///Open and write the table TableEvent in given file
/**	@param fileName : name of the HDF5 file to be used
 * 	@return opened DataSet
*/
H5::DataSet TableEvent::openDataSet(const std::string & fileName) const{
	H5::H5File file(fileName, H5F_ACC_RDONLY);
	return openDataSet(file);
}

///Open the DataSet of the table TableEvent in given file
/**	@param file : HDF5 file to be used
 * 	@return opened DataSet
*/
H5::DataSet TableEvent::openDataSet(const H5::H5File & file) const{
	H5::DataSet dataset = file.openDataSet(p__tableName);
	return dataset;
}

///Open the DataSet of the table TableEvent in given group
/**	@param group : HDF5 group to be used
 * 	@return opened DataSet
*/
H5::DataSet TableEvent::openDataSet(const H5::Group & group) const{
	H5::DataSet dataset = group.openDataSet(p__tableName);
	return dataset;
}

///Open the DataSet of the table TableEvent in given file (for block usage)
/**	@param fileName : name of the HDF5 file to be used
 * 	@param nbMaxRowPerBlock : maximum number of rows in the block
*/
void TableEvent::openDataSetBlock(const std::string & fileName, size_t nbMaxRowPerBlock){
	H5::H5File file(fileName, H5F_ACC_RDONLY);
	openDataSetBlock(file, nbMaxRowPerBlock);
}

///Open the DataSet of the table TableEvent in given file (for block usage)
/**	@param file : HDF5 file to be used
 * 	@param nbMaxRowPerBlock : maximum number of rows in the block
*/
void TableEvent::openDataSetBlock(const H5::H5File & file, size_t nbMaxRowPerBlock){
	H5::DataSet dataset = file.openDataSet(p__tableName);
	openDataSetBlock(dataset, nbMaxRowPerBlock);
}

///Open the DataSet of the table TableEvent in given group (for block usage)
/**	@param group : HDF5 group to be used
 * 	@param nbMaxRowPerBlock : maximum number of rows in the block
*/
void TableEvent::openDataSetBlock(const H5::Group & group, size_t nbMaxRowPerBlock){
	H5::DataSet dataset = group.openDataSet(p__tableName);
	openDataSetBlock(dataset, nbMaxRowPerBlock);
}

///Set a full row of the table TableEvent
/**	@param i : index of the row to be set
 * 	@param Imax : attribute to be set
 * 	@param alpha : attribute to be set
 * 	@param energy : attribute to be set
 * 	@param hfirstint : attribute to be set
 * 	@param eventId : attribute to be set
 * 	@param impact : attribute to be set
 * 	@param sv : attribute to be set
 * 	@param x : attribute to be set
 * 	@param y : attribute to be set
*/
void TableEvent::setRow(size_t i, float Imax, float alpha, float energy, float hfirstint, size_t eventId, float impact, float * sv, float x, float y){
	setImax(i, Imax);
	setAlpha(i, alpha);
	setEnergy(i, energy);
	setHfirstint(i, hfirstint);
	setEventId(i, eventId);
	setImpact(i, impact);
	setSv(i, sv);
	setX(i, x);
	setY(i, y);
}

///Get a full row of the table TableEvent (without tensor copy, only with pointer)
/**	@param i : index of the row to get its values
 * 	@param[out] Imax : attribute to be get
 * 	@param[out] alpha : attribute to be get
 * 	@param[out] energy : attribute to be get
 * 	@param[out] hfirstint : attribute to be get
 * 	@param[out] eventId : attribute to be get
 * 	@param[out] impact : attribute to be get
 * 	@param[out] sv : attribute to be get
 * 	@param[out] x : attribute to be get
 * 	@param[out] y : attribute to be get
*/
void TableEvent::getRow(size_t i, float & Imax, float & alpha, float & energy, float & hfirstint, size_t & eventId, float & impact, float *& sv, float & x, float & y){
	Imax = getImax(i);
	alpha = getAlpha(i);
	energy = getEnergy(i);
	hfirstint = getHfirstint(i);
	eventId = getEventId(i);
	impact = getImpact(i);
	sv = getSv(i);
	x = getX(i);
	y = getY(i);
}

///Get a full row of the table TableEvent (without tensor copy, only with pointer)
/**	@param i : index of the row to get its values
 * 	@param[out] Imax : attribute to be get
 * 	@param[out] alpha : attribute to be get
 * 	@param[out] energy : attribute to be get
 * 	@param[out] hfirstint : attribute to be get
 * 	@param[out] eventId : attribute to be get
 * 	@param[out] impact : attribute to be get
 * 	@param[out] sv : attribute to be get
 * 	@param[out] x : attribute to be get
 * 	@param[out] y : attribute to be get
*/
void TableEvent::getRow(size_t i, float & Imax, float & alpha, float & energy, float & hfirstint, size_t & eventId, float & impact, const float *& sv, float & x, float & y) const{
	Imax = getImax(i);
	alpha = getAlpha(i);
	energy = getEnergy(i);
	hfirstint = getHfirstint(i);
	eventId = getEventId(i);
	impact = getImpact(i);
	sv = getSv(i);
	x = getX(i);
	y = getY(i);
}

///Set the attribute Imax (column Imax)
/**	@param i : index of the row to be used
 * 	@param val : value to be copied
*/
void TableEvent::setImax(size_t i, float val){
	p_Imax[i] = val;
}

///Set the attribute alpha (column alpha)
/**	@param i : index of the row to be used
 * 	@param val : value to be copied
*/
void TableEvent::setAlpha(size_t i, float val){
	p_alpha[i] = val;
}

///Set the attribute energy (column energy)
/**	@param i : index of the row to be used
 * 	@param val : value to be copied
*/
void TableEvent::setEnergy(size_t i, float val){
	p_energy[i] = val;
}

///Set the attribute hfirstint (column hfirstint)
/**	@param i : index of the row to be used
 * 	@param val : value to be copied
*/
void TableEvent::setHfirstint(size_t i, float val){
	p_hfirstint[i] = val;
}

///Set the attribute eventId (column idevent)
/**	@param i : index of the row to be used
 * 	@param val : value to be copied
*/
void TableEvent::setEventId(size_t i, size_t val){
	p_eventId[i] = val;
}

///Set the attribute impact (column impact)
/**	@param i : index of the row to be used
 * 	@param val : value to be copied
*/
void TableEvent::setImpact(size_t i, float val){
	p_impact[i] = val;
}

///Set the attribute sv (column sv)
/**	@param i : index of the row to be used
 * 	@param tabVal : table of value to be copied
*/
void TableEvent::setSv(size_t i, const float * tabVal){
	size_t sizeRow(p_nb_vs);
	memcpy(p_sv + i*sizeRow, tabVal, sizeRow*sizeof(float));
}

///Set the attribute x (column x)
/**	@param i : index of the row to be used
 * 	@param val : value to be copied
*/
void TableEvent::setX(size_t i, float val){
	p_x[i] = val;
}

///Set the attribute y (column y)
/**	@param i : index of the row to be used
 * 	@param val : value to be copied
*/
void TableEvent::setY(size_t i, float val){
	p_y[i] = val;
}

///Get the full column of the attribute Imax (column Imax)
/**	@return pointer of the full column
*/
const float * TableEvent::getImaxFull() const{
	return p_Imax;
}

///Get the full column of the attribute Imax (column Imax)
/**	@return pointer of the full column
*/
float * TableEvent::getImaxFull(){
	return p_Imax;
}

///Get the value i of the attribute Imax (column Imax)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
float TableEvent::getImax(size_t i) const{
	return p_Imax[i];
}

///Get the value i of the attribute Imax (column Imax)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
float & TableEvent::getImax(size_t i){
	return p_Imax[i];
}

///Get the full column of the attribute alpha (column alpha)
/**	@return pointer of the full column
*/
const float * TableEvent::getAlphaFull() const{
	return p_alpha;
}

///Get the full column of the attribute alpha (column alpha)
/**	@return pointer of the full column
*/
float * TableEvent::getAlphaFull(){
	return p_alpha;
}

///Get the value i of the attribute alpha (column alpha)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
float TableEvent::getAlpha(size_t i) const{
	return p_alpha[i];
}

///Get the value i of the attribute alpha (column alpha)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
float & TableEvent::getAlpha(size_t i){
	return p_alpha[i];
}

///Get the full column of the attribute energy (column energy)
/**	@return pointer of the full column
*/
const float * TableEvent::getEnergyFull() const{
	return p_energy;
}

///Get the full column of the attribute energy (column energy)
/**	@return pointer of the full column
*/
float * TableEvent::getEnergyFull(){
	return p_energy;
}

///Get the value i of the attribute energy (column energy)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
float TableEvent::getEnergy(size_t i) const{
	return p_energy[i];
}

///Get the value i of the attribute energy (column energy)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
float & TableEvent::getEnergy(size_t i){
	return p_energy[i];
}

///Get the full column of the attribute hfirstint (column hfirstint)
/**	@return pointer of the full column
*/
const float * TableEvent::getHfirstintFull() const{
	return p_hfirstint;
}

///Get the full column of the attribute hfirstint (column hfirstint)
/**	@return pointer of the full column
*/
float * TableEvent::getHfirstintFull(){
	return p_hfirstint;
}

///Get the value i of the attribute hfirstint (column hfirstint)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
float TableEvent::getHfirstint(size_t i) const{
	return p_hfirstint[i];
}

///Get the value i of the attribute hfirstint (column hfirstint)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
float & TableEvent::getHfirstint(size_t i){
	return p_hfirstint[i];
}

///Get the full column of the attribute eventId (column idevent)
/**	@return pointer of the full column
*/
const size_t * TableEvent::getEventIdFull() const{
	return p_eventId;
}

///Get the full column of the attribute eventId (column idevent)
/**	@return pointer of the full column
*/
size_t * TableEvent::getEventIdFull(){
	return p_eventId;
}

///Get the value i of the attribute eventId (column idevent)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
size_t TableEvent::getEventId(size_t i) const{
	return p_eventId[i];
}

///Get the value i of the attribute eventId (column idevent)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
size_t & TableEvent::getEventId(size_t i){
	return p_eventId[i];
}

///Get the full column of the attribute impact (column impact)
/**	@return pointer of the full column
*/
const float * TableEvent::getImpactFull() const{
	return p_impact;
}

///Get the full column of the attribute impact (column impact)
/**	@return pointer of the full column
*/
float * TableEvent::getImpactFull(){
	return p_impact;
}

///Get the value i of the attribute impact (column impact)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
float TableEvent::getImpact(size_t i) const{
	return p_impact[i];
}

///Get the value i of the attribute impact (column impact)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
float & TableEvent::getImpact(size_t i){
	return p_impact[i];
}

///Get the full column of the attribute sv (column sv)
/**	@return pointer of the full column
*/
const float * TableEvent::getSvFull() const{
	return p_sv;
}

///Get the full column of the attribute sv (column sv)
/**	@return pointer of the full column
*/
float * TableEvent::getSvFull(){
	return p_sv;
}

///Get the tensor i of the attribute sv (column sv)
/**	@param i : index of the row to be used
 * 	@return pointer to the corresponding tensor
*/
const float * TableEvent::getSv(size_t i) const{
	return p_sv + i*p_nb_vs;
}

///Get the tensor i of the attribute sv (column sv)
/**	@param i : index of the row to be used
 * 	@return pointer to the corresponding tensor
*/
float * TableEvent::getSv(size_t i){
	return p_sv + i*p_nb_vs;
}

///Get the full column of the attribute x (column x)
/**	@return pointer of the full column
*/
const float * TableEvent::getXFull() const{
	return p_x;
}

///Get the full column of the attribute x (column x)
/**	@return pointer of the full column
*/
float * TableEvent::getXFull(){
	return p_x;
}

///Get the value i of the attribute x (column x)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
float TableEvent::getX(size_t i) const{
	return p_x[i];
}

///Get the value i of the attribute x (column x)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
float & TableEvent::getX(size_t i){
	return p_x[i];
}

///Get the full column of the attribute y (column y)
/**	@return pointer of the full column
*/
const float * TableEvent::getYFull() const{
	return p_y;
}

///Get the full column of the attribute y (column y)
/**	@return pointer of the full column
*/
float * TableEvent::getYFull(){
	return p_y;
}

///Get the value i of the attribute y (column y)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
float TableEvent::getY(size_t i) const{
	return p_y[i];
}

///Get the value i of the attribute y (column y)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
float & TableEvent::getY(size_t i){
	return p_y[i];
}

///Set all the dimentions of the Tensor in the table
/**	@param nb_vs : set the tensor dimention nb_vs
*/
void TableEvent::setAllDim(size_t nb_vs){
	setNb_vs(nb_vs);
}

///Set the Tensor dimention nb_vs
/**	@param val : set the tensor dimention nb_vs
*/
void TableEvent::setNb_vs(size_t val){
	 p_nb_vs = val;
}

///Get the Tensor dimention nb_vs
/**	@return the tensor dimention nb_vs
*/
size_t TableEvent::getNb_vs() const{
	return p_nb_vs;
}

///Get the offset of the attribute Imax
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetImax() const{
	return 0lu;
}

///Get the offset of the attribute alpha
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetAlpha() const{
	return getOffsetImax() + sizeof(float);
}

///Get the offset of the attribute energy
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetEnergy() const{
	return getOffsetAlpha() + sizeof(float);
}

///Get the offset of the attribute hfirstint
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetHfirstint() const{
	return getOffsetEnergy() + sizeof(float);
}

///Get the offset of the attribute eventId
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetEventId() const{
	return getOffsetHfirstint() + sizeof(float);
}

///Get the offset of the attribute impact
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetImpact() const{
	return getOffsetEventId() + sizeof(size_t);
}

///Get the offset of the attribute sv
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetSv() const{
	return getOffsetImpact() + sizeof(float);
}

///Get the offset of the attribute x
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetX() const{
	return getOffsetSv() + sizeof(float)*p_nb_vs;
}

///Get the offset of the attribute y
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetY() const{
	return getOffsetX() + sizeof(float);
}

H5::CompType TableEvent::getCompTypeAll() const{
	size_t sizeAll(sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(size_t) + sizeof(float) + sizeof(float)*p_nb_vs + sizeof(float) + sizeof(float));
	H5::CompType typeCol(sizeAll);
	typeCol.insertMember("Imax", getOffsetImax(), getTypeImax());
	typeCol.insertMember("alpha", getOffsetAlpha(), getTypeAlpha());
	typeCol.insertMember("energy", getOffsetEnergy(), getTypeEnergy());
	typeCol.insertMember("hfirstint", getOffsetHfirstint(), getTypeHfirstint());
	typeCol.insertMember("idevent", getOffsetEventId(), getTypeEventId());
	typeCol.insertMember("impact", getOffsetImpact(), getTypeImpact());
	typeCol.insertMember("sv", getOffsetSv(), getTypeSv());
	typeCol.insertMember("x", getOffsetX(), getTypeX());
	typeCol.insertMember("y", getOffsetY(), getTypeY());
	return typeCol;
}

///Get DataType of attribute Imax (column Imax)
/**	@return DataType of the attribute Imax
*/
H5::CompType TableEvent::getCompTypeImax() const{
	H5::CompType typeCol(sizeof(float));
	typeCol.insertMember("Imax", 0, getTypeImax());
	return typeCol;
}

///Get DataType of attribute alpha (column alpha)
/**	@return DataType of the attribute alpha
*/
H5::CompType TableEvent::getCompTypeAlpha() const{
	H5::CompType typeCol(sizeof(float));
	typeCol.insertMember("alpha", 0, getTypeAlpha());
	return typeCol;
}

///Get DataType of attribute energy (column energy)
/**	@return DataType of the attribute energy
*/
H5::CompType TableEvent::getCompTypeEnergy() const{
	H5::CompType typeCol(sizeof(float));
	typeCol.insertMember("energy", 0, getTypeEnergy());
	return typeCol;
}

///Get DataType of attribute hfirstint (column hfirstint)
/**	@return DataType of the attribute hfirstint
*/
H5::CompType TableEvent::getCompTypeHfirstint() const{
	H5::CompType typeCol(sizeof(float));
	typeCol.insertMember("hfirstint", 0, getTypeHfirstint());
	return typeCol;
}

///Get DataType of attribute eventId (column idevent)
/**	@return DataType of the attribute eventId
*/
H5::CompType TableEvent::getCompTypeEventId() const{
	H5::CompType typeCol(sizeof(size_t));
	typeCol.insertMember("idevent", 0, getTypeEventId());
	return typeCol;
}

///Get DataType of attribute impact (column impact)
/**	@return DataType of the attribute impact
*/
H5::CompType TableEvent::getCompTypeImpact() const{
	H5::CompType typeCol(sizeof(float));
	typeCol.insertMember("impact", 0, getTypeImpact());
	return typeCol;
}

///Get DataType of attribute sv (column sv)
/**	@return DataType of the attribute sv
*/
H5::CompType TableEvent::getCompTypeSv() const{
	H5::CompType typeCol(sizeof(float)*p_nb_vs);
	typeCol.insertMember("sv", 0, getTypeSv());
	return typeCol;
}

///Get DataType of attribute x (column x)
/**	@return DataType of the attribute x
*/
H5::CompType TableEvent::getCompTypeX() const{
	H5::CompType typeCol(sizeof(float));
	typeCol.insertMember("x", 0, getTypeX());
	return typeCol;
}

///Get DataType of attribute y (column y)
/**	@return DataType of the attribute y
*/
H5::CompType TableEvent::getCompTypeY() const{
	H5::CompType typeCol(sizeof(float));
	typeCol.insertMember("y", 0, getTypeY());
	return typeCol;
}

///Get DataType of attribute Imax (column Imax)
/**	@return DataType of the attribute Imax
*/
H5::DataType TableEvent::getTypeImax() const{
	return H5::PredType::NATIVE_FLOAT;
}

///Get DataType of attribute alpha (column alpha)
/**	@return DataType of the attribute alpha
*/
H5::DataType TableEvent::getTypeAlpha() const{
	return H5::PredType::NATIVE_FLOAT;
}

///Get DataType of attribute energy (column energy)
/**	@return DataType of the attribute energy
*/
H5::DataType TableEvent::getTypeEnergy() const{
	return H5::PredType::NATIVE_FLOAT;
}

///Get DataType of attribute hfirstint (column hfirstint)
/**	@return DataType of the attribute hfirstint
*/
H5::DataType TableEvent::getTypeHfirstint() const{
	return H5::PredType::NATIVE_FLOAT;
}

///Get DataType of attribute eventId (column idevent)
/**	@return DataType of the attribute eventId
*/
H5::DataType TableEvent::getTypeEventId() const{
	return H5::PredType::NATIVE_UINT64;
}

///Get DataType of attribute impact (column impact)
/**	@return DataType of the attribute impact
*/
H5::DataType TableEvent::getTypeImpact() const{
	return H5::PredType::NATIVE_FLOAT;
}

///Get DataType of attribute sv (column sv)
/**	@return DataType of the attribute sv
*/
H5::DataType TableEvent::getTypeSv() const{
	hsize_t dims[1];
	dims[0] = p_nb_vs;
	H5::ArrayType arrayType(H5::PredType::NATIVE_FLOAT, 1, dims);
	return arrayType;
}

///Get DataType of attribute x (column x)
/**	@return DataType of the attribute x
*/
H5::DataType TableEvent::getTypeX() const{
	return H5::PredType::NATIVE_FLOAT;
}

///Get DataType of attribute y (column y)
/**	@return DataType of the attribute y
*/
H5::DataType TableEvent::getTypeY() const{
	return H5::PredType::NATIVE_FLOAT;
}

///Read the given DataSet and fill the Table with it
/**	@param dataset : dataset to be used
*/
void TableEvent::readDataSet(const H5::DataSet & dataset){
	H5::CompType compType = dataset.getCompType();
	readDimSv(compType);
	H5::DataSpace dataSpace = dataset.getSpace();
	size_t nbEntries(dataSpace.getSimpleExtentNpoints());
	resize(nbEntries);
	dataset.read(p_Imax, getCompTypeImax());
	dataset.read(p_alpha, getCompTypeAlpha());
	dataset.read(p_energy, getCompTypeEnergy());
	dataset.read(p_hfirstint, getCompTypeHfirstint());
	dataset.read(p_eventId, getCompTypeEventId());
	dataset.read(p_impact, getCompTypeImpact());
	dataset.read(p_sv, getCompTypeSv());
	dataset.read(p_x, getCompTypeX());
	dataset.read(p_y, getCompTypeY());
}

///Read the given DataSet and fill the Table with it
/**	@param dataset : dataset to be used
 * 	@param offset : index of the first row the TableEvent class needs to load
 * 	@param nbRow : number of rows the TableEvent class needs to load (Will reallocate the TableEvent is the number of rows is greater than the number off already allocated rows)
*/
void TableEvent::readDataSet(const H5::DataSet & dataset, size_t offset, size_t nbRow){
	H5::CompType compType = dataset.getCompType();
	readDimSv(compType);
	H5::DataSpace dataSpace = dataset.getSpace();
	size_t nbEntries(dataSpace.getSimpleExtentNpoints());
	resize(nbRow);
	hsize_t dimBlockFile[1];
	dimBlockFile[0] = nbEntries;
	hsize_t offsetBlockBase[1];
	offsetBlockBase[0] = offset;
	hsize_t countFile[1];
	countFile[0] = nbRow;
	H5::DataSpace spaceBlockFile(1, dimBlockFile);
	spaceBlockFile.selectHyperslab(H5S_SELECT_SET, countFile, offsetBlockBase);
	hsize_t dimBlockMem[1];
	dimBlockMem[0] = nbRow;
	H5::DataSpace blockMem(1, dimBlockMem);
	dataset.read(p_Imax, getCompTypeImax(), blockMem, spaceBlockFile);
	dataset.read(p_alpha, getCompTypeAlpha(), blockMem, spaceBlockFile);
	dataset.read(p_energy, getCompTypeEnergy(), blockMem, spaceBlockFile);
	dataset.read(p_hfirstint, getCompTypeHfirstint(), blockMem, spaceBlockFile);
	dataset.read(p_eventId, getCompTypeEventId(), blockMem, spaceBlockFile);
	dataset.read(p_impact, getCompTypeImpact(), blockMem, spaceBlockFile);
	dataset.read(p_sv, getCompTypeSv(), blockMem, spaceBlockFile);
	dataset.read(p_x, getCompTypeX(), blockMem, spaceBlockFile);
	dataset.read(p_y, getCompTypeY(), blockMem, spaceBlockFile);
}

///Write the given DataSet and fill the Table with it
/**	@param[out] dataset : dataset to be modified
*/
void TableEvent::writeDataSet(H5::DataSet & dataset) const{
	dataset.write(p_Imax, getCompTypeImax());
	dataset.write(p_alpha, getCompTypeAlpha());
	dataset.write(p_energy, getCompTypeEnergy());
	dataset.write(p_hfirstint, getCompTypeHfirstint());
	dataset.write(p_eventId, getCompTypeEventId());
	dataset.write(p_impact, getCompTypeImpact());
	dataset.write(p_sv, getCompTypeSv());
	dataset.write(p_x, getCompTypeX());
	dataset.write(p_y, getCompTypeY());
}

///Open the given DataSet and prepare the block usage (do not load data)
/**	@param dataset : dataset to be loaded
 * 	@param nbMaxRowPerBlock : maximum number of rows in the block
 * 	You have to use this method with iterateBlock() and getBlockSize() methods
*/
void TableEvent::openDataSetBlock(const H5::DataSet & dataset, size_t nbMaxRowPerBlock){
	p__blockOffset = 0lu;
	H5::DataSpace spaceEvent = dataset.getSpace();
	p__totalDataSetRow = spaceEvent.getSelectNpoints();
	p__dataset = dataset;
	if(p__totalDataSetRow > nbMaxRowPerBlock){	//If there are more rows than block's size
		p__blockSize = nbMaxRowPerBlock;
	}else{	//Otherwise we get all rows
		p__blockSize = p__totalDataSetRow;
	}
}

///Iterate over the blocks and load the current block
/**	@return true if the current block has been loaded, false if we reach the end of the blocks
*/
bool TableEvent::iterateBlock(){
	if(p__blockOffset >= p__totalDataSetRow){p__blockOffset = 0lu;return false;}	//We reach the end of the DataSet
	if(p__blockOffset + p__blockSize > p__totalDataSetRow){
		p__blockSize = p__totalDataSetRow - p__blockOffset;
	}
	readDataSet(p__dataset, p__blockOffset, p__blockSize);	//Let's read the current block
	p__blockOffset += p__blockSize;				//Let's increment the offset
	return true;
}

///Get the full size of the loaded DataSet
/**	@return full size of the loaded DataSet
*/
size_t TableEvent::getFullDataSetSize() const{
	return p__totalDataSetRow;
}

///Get the size of the current block
/**	@return size of the currently loaded block
*/
size_t TableEvent::getBlockSize() const{
	return p__blockSize;
}

///Get the offset of the current block
/**	@return offset of the currently loaded block
*/
size_t TableEvent::getBlockOffset() const{
	return p__blockOffset;
}

///Initialises the table TableEvent
void TableEvent::initialisationTableEvent(){
	p__nbRow = 0lu;
	p__tableName = "gerbe";
	p_nb_vs = 0lu;
	p_Imax = NULL;
	p_alpha = NULL;
	p_energy = NULL;
	p_hfirstint = NULL;
	p_eventId = NULL;
	p_impact = NULL;
	p_sv = NULL;
	p_x = NULL;
	p_y = NULL;
}

///Allocate the table TableEvent (delete all column)
/**	@param nbRow : new number of rows of the Table
*/
void TableEvent::allocate(size_t nbRow){
	p__nbRow = nbRow;
	if(p__nbRow == 0lu){
		initialisationTableEvent();
		return;
	}
	p_Imax = new float[p__nbRow];
	p_alpha = new float[p__nbRow];
	p_energy = new float[p__nbRow];
	p_hfirstint = new float[p__nbRow];
	p_eventId = new size_t[p__nbRow];
	p_impact = new float[p__nbRow];
	p_sv = new float[p__nbRow*p_nb_vs];
	p_x = new float[p__nbRow];
	p_y = new float[p__nbRow];
}

///Copy function of the class TableEvent
/**	@param other : TableEvent to be copied
*/
void TableEvent::copyTableEvent(const TableEvent & other){
	//Let's copy proper attributes of the TableEvent
	p__tableName = other.p__tableName;
	p__totalDataSetRow = other.p__totalDataSetRow;
	p__blockSize = other.p__blockSize;
	p__blockOffset = other.p__blockOffset;
	//Let's copy extra dimension of the TableEvent
	p_nb_vs = other.p_nb_vs;
	//Let's allocate columns of TableEvent
	allocate(other.p__nbRow);	//Let's allocate properly everything
	//Let's copy columns of TableEvent
	memcpy(p_Imax, other.p_Imax, sizeof(float)*p__nbRow);
	memcpy(p_alpha, other.p_alpha, sizeof(float)*p__nbRow);
	memcpy(p_energy, other.p_energy, sizeof(float)*p__nbRow);
	memcpy(p_hfirstint, other.p_hfirstint, sizeof(float)*p__nbRow);
	memcpy(p_eventId, other.p_eventId, sizeof(size_t)*p__nbRow);
	memcpy(p_impact, other.p_impact, sizeof(float)*p__nbRow);
	memcpy(p_sv, other.p_sv, sizeof(float)*p__nbRow*p_nb_vs);
	memcpy(p_x, other.p_x, sizeof(float)*p__nbRow);
	memcpy(p_y, other.p_y, sizeof(float)*p__nbRow);
}

///Update the dimentions of the tensor sv (column 'sv')
/**	@param compType : main type to be used to update the tensor dimentions*/
void TableEvent::readDimSv(const H5::CompType & compType){
	int indexCol = compType.getMemberIndex("sv");
	H5::ArrayType arrayType = compType.getMemberArrayType(indexCol);
	//Check if the number of dientions matches
	if(arrayType.getArrayNDims() != 1){
		std::stringstream strError;
		strError << "TableEvent::readDimSv wrong number of dimentions : expect 1 but "<< arrayType.getArrayNDims() <<" provided from the file" << std::endl;
		throw std::runtime_error(strError.str());
	}
	hsize_t dims[1];
	arrayType.getArrayDims(dims);
	p_nb_vs = dims[0];
}

///Constructor of the class space
space::space(){
	initialisationspace();
}

///Copy constructor of the class space
/**	@param other : space to be copied
*/
space::space(const space & other){
	initialisationspace();
	copyspace(other);
}

///Destructor of the class space
space::~space(){
	clear();
}

///Equal operator of the class space
/**	@param other : space to be copied
 * 	@return copied space
*/
space & space::operator = (const space & other){
	copyspace(other);
	return *this;
}

///Set the HDF5 name of the Table space
/**	@param name : name of the table to be saved
*/
void space::setTableName(const std::string & name){
	p__tableName = name;
}

///Get the total number of rows in the current Table space
/**	@return total number of rows
*/
size_t space::getNbEntries() const{
	return p__nbRow;
}

///Resize the table space
/*	@param nbRow : new number of rows of the Table
*/
void space::resize(size_t nbRow){
	if(nbRow == p__nbRow){return;}	//Nothing to do
	clear();
	allocate(nbRow);
}

///Clear the table space (delete all column)
void space::clear(){
	if(p_images != NULL){delete [] p_images;p_images = NULL;}
}

///Read the table space from given file
/**	@param fileName : name of the HDF5 file to be used
*/
void space::read(const std::string & fileName){
	H5::H5File file(fileName, H5F_ACC_RDONLY);
	read(file);
}

///Read the table space from given file
/**	@param file : HDF5 file to be used
*/
void space::read(const H5::H5File & file){
	H5::DataSet dataset = openDataSet(file);
	readDataSet(dataset);
}

///Read the table space from given group
/**	@param group : HDF5 group to be used
*/
void space::read(const H5::Group & group){
	H5::DataSet dataset = openDataSet(group);
	readDataSet(dataset);
}

///Read the table space from given file
/**	@param fileName : name of the HDF5 file to be used
 * 	@param offset : index of the first row the space class needs to load
 * 	@param nbRow : number of rows the space class needs to load (Will reallocate the space is the number of rows is greater than the number off already allocated rows)
*/
void space::read(const std::string & fileName, size_t offset, size_t nbRow){
	H5::H5File file(fileName, H5F_ACC_RDONLY);
	read(file, offset, nbRow);
}

///Read the table space from given file
/**	@param file : HDF5 file to be used
 * 	@param offset : index of the first row the space class needs to load
 * 	@param nbRow : number of rows the space class needs to load (Will reallocate the space is the number of rows is greater than the number off already allocated rows)
*/
void space::read(const H5::H5File & file, size_t offset, size_t nbRow){
	H5::DataSet dataset = openDataSet(file);
	readDataSet(dataset, offset, nbRow);
}

///Read the table space from given group
/**	@param group : HDF5 group to be used
 * 	@param offset : index of the first row the space class needs to load
 * 	@param nbRow : number of rows the space class needs to load (Will reallocate the space is the number of rows is greater than the number off already allocated rows)
*/
void space::read(const H5::Group & group, size_t offset, size_t nbRow){
	H5::DataSet dataset = openDataSet(group);
	readDataSet(dataset, offset, nbRow);
}

///Create and write the table space in given file
/**	@param fileName : name of the HDF5 file to be used
*/
void space::write(const std::string & fileName) const{
	H5::H5File file(fileName, H5F_ACC_TRUNC);
	write(file);
}

///Create and write the table space in given file
/**	@param file : HDF5 file to be used
*/
void space::write(H5::H5File & file) const{
	H5::DataSet dataset = createDataSet(file, p__nbRow);
	writeDataSet(dataset);
}

///Create and write the table space in given file
/**	@param group : HDF5 group to be used
*/
void space::write(H5::Group & group) const{
	H5::DataSet dataset = createDataSet(group, p__nbRow);
	writeDataSet(dataset);
}

///Create and write the table space in given file
/**	@param fileName : name of the HDF5 file to be used
 * 	@param nbRow : full number of rows in the DataSet
 * 	@return created DataSet
*/
H5::DataSet space::createDataSet(const std::string & fileName, size_t nbRow) const{
	H5::H5File file(fileName, H5F_ACC_TRUNC);
	return createDataSet(file, nbRow);
}

///Create the DataSet of the table space in given file
/**	@param file : HDF5 file to be used
 * 	@param nbRow : full number of rows in the DataSet
 * 	@return created DataSet
*/
H5::DataSet space::createDataSet(H5::H5File & file, size_t nbRow) const{
	hsize_t dim[1];
	dim[0] = nbRow;
	H5::DataSpace space(1, dim);
	H5::DataSet dataset = file.createDataSet(p__tableName, getCompTypeAll(), space);
	return dataset;
}

///Create the DataSet of the table space in given group
/**	@param group : HDF5 group to be used
 * 	@param nbRow : full number of rows in the DataSet
 * 	@return created DataSet
*/
H5::DataSet space::createDataSet(H5::Group & group, size_t nbRow) const{
	hsize_t dim[1];
	dim[0] = nbRow;
	H5::DataSpace space(1, dim);
	H5::DataSet dataset = group.createDataSet(p__tableName, getCompTypeAll(), space);
	return dataset;
}

///Open and write the table space in given file
/**	@param fileName : name of the HDF5 file to be used
 * 	@return opened DataSet
*/
H5::DataSet space::openDataSet(const std::string & fileName) const{
	H5::H5File file(fileName, H5F_ACC_RDONLY);
	return openDataSet(file);
}

///Open the DataSet of the table space in given file
/**	@param file : HDF5 file to be used
 * 	@return opened DataSet
*/
H5::DataSet space::openDataSet(const H5::H5File & file) const{
	H5::DataSet dataset = file.openDataSet(p__tableName);
	return dataset;
}

///Open the DataSet of the table space in given group
/**	@param group : HDF5 group to be used
 * 	@return opened DataSet
*/
H5::DataSet space::openDataSet(const H5::Group & group) const{
	H5::DataSet dataset = group.openDataSet(p__tableName);
	return dataset;
}

///Open the DataSet of the table space in given file (for block usage)
/**	@param fileName : name of the HDF5 file to be used
 * 	@param nbMaxRowPerBlock : maximum number of rows in the block
*/
void space::openDataSetBlock(const std::string & fileName, size_t nbMaxRowPerBlock){
	H5::H5File file(fileName, H5F_ACC_RDONLY);
	openDataSetBlock(file, nbMaxRowPerBlock);
}

///Open the DataSet of the table space in given file (for block usage)
/**	@param file : HDF5 file to be used
 * 	@param nbMaxRowPerBlock : maximum number of rows in the block
*/
void space::openDataSetBlock(const H5::H5File & file, size_t nbMaxRowPerBlock){
	H5::DataSet dataset = file.openDataSet(p__tableName);
	openDataSetBlock(dataset, nbMaxRowPerBlock);
}

///Open the DataSet of the table space in given group (for block usage)
/**	@param group : HDF5 group to be used
 * 	@param nbMaxRowPerBlock : maximum number of rows in the block
*/
void space::openDataSetBlock(const H5::Group & group, size_t nbMaxRowPerBlock){
	H5::DataSet dataset = group.openDataSet(p__tableName);
	openDataSetBlock(dataset, nbMaxRowPerBlock);
}

///Set a full row of the table space
/**	@param i : index of the row to be set
 * 	@param images : attribute to be set
*/
void space::setRow(size_t i, float * images){
	setImages(i, images);
}

///Get a full row of the table space (without tensor copy, only with pointer)
/**	@param i : index of the row to get its values
 * 	@param[out] images : attribute to be get
*/
void space::getRow(size_t i, float *& images){
	images = getImages(i);
}

///Get a full row of the table space (without tensor copy, only with pointer)
/**	@param i : index of the row to get its values
 * 	@param[out] images : attribute to be get
*/
void space::getRow(size_t i, const float *& images) const{
	images = getImages(i);
}

///Set the attribute images (column image)
/**	@param i : index of the row to be used
 * 	@param tabVal : table of value to be copied
*/
void space::setImages(size_t i, const float * tabVal){
	size_t sizeRow(p_nb_pixels);
	memcpy(p_images + i*sizeRow, tabVal, sizeRow*sizeof(float));
}

///Get the full column of the attribute images (column image)
/**	@return pointer of the full column
*/
const float * space::getImagesFull() const{
	return p_images;
}

///Get the full column of the attribute images (column image)
/**	@return pointer of the full column
*/
float * space::getImagesFull(){
	return p_images;
}

///Get the tensor i of the attribute images (column image)
/**	@param i : index of the row to be used
 * 	@return pointer to the corresponding tensor
*/
const float * space::getImages(size_t i) const{
	return p_images + i*p_nb_pixels;
}

///Get the tensor i of the attribute images (column image)
/**	@param i : index of the row to be used
 * 	@return pointer to the corresponding tensor
*/
float * space::getImages(size_t i){
	return p_images + i*p_nb_pixels;
}

///Set all the dimentions of the Tensor in the table
/**	@param nb_pixels : set the tensor dimention nb_pixels
*/
void space::setAllDim(size_t nb_pixels){
	setNb_pixels(nb_pixels);
}

///Set the Tensor dimention nb_pixels
/**	@param val : set the tensor dimention nb_pixels
*/
void space::setNb_pixels(size_t val){
	 p_nb_pixels = val;
}

///Get the Tensor dimention nb_pixels
/**	@return the tensor dimention nb_pixels
*/
size_t space::getNb_pixels() const{
	return p_nb_pixels;
}

///Get the offset of the attribute images
/**	@return offset of the attribute in bytes
*/
size_t space::getOffsetImages() const{
	return 0lu;
}

H5::CompType space::getCompTypeAll() const{
	size_t sizeAll(sizeof(float)*p_nb_pixels);
	H5::CompType typeCol(sizeAll);
	typeCol.insertMember("image", getOffsetImages(), getTypeImages());
	return typeCol;
}

///Get DataType of attribute images (column image)
/**	@return DataType of the attribute images
*/
H5::CompType space::getCompTypeImages() const{
	H5::CompType typeCol(sizeof(float)*p_nb_pixels);
	typeCol.insertMember("image", 0, getTypeImages());
	return typeCol;
}

///Get DataType of attribute images (column image)
/**	@return DataType of the attribute images
*/
H5::DataType space::getTypeImages() const{
	hsize_t dims[1];
	dims[0] = p_nb_pixels;
	H5::ArrayType arrayType(H5::PredType::NATIVE_FLOAT, 1, dims);
	return arrayType;
}

///Read the given DataSet and fill the Table with it
/**	@param dataset : dataset to be used
*/
void space::readDataSet(const H5::DataSet & dataset){
	H5::CompType compType = dataset.getCompType();
	readDimImages(compType);
	H5::DataSpace dataSpace = dataset.getSpace();
	size_t nbEntries(dataSpace.getSimpleExtentNpoints());
	resize(nbEntries);
	dataset.read(p_images, getCompTypeImages());
}

///Read the given DataSet and fill the Table with it
/**	@param dataset : dataset to be used
 * 	@param offset : index of the first row the space class needs to load
 * 	@param nbRow : number of rows the space class needs to load (Will reallocate the space is the number of rows is greater than the number off already allocated rows)
*/
void space::readDataSet(const H5::DataSet & dataset, size_t offset, size_t nbRow){
	H5::CompType compType = dataset.getCompType();
	readDimImages(compType);
	H5::DataSpace dataSpace = dataset.getSpace();
	size_t nbEntries(dataSpace.getSimpleExtentNpoints());
	resize(nbRow);
	hsize_t dimBlockFile[1];
	dimBlockFile[0] = nbEntries;
	hsize_t offsetBlockBase[1];
	offsetBlockBase[0] = offset;
	hsize_t countFile[1];
	countFile[0] = nbRow;
	H5::DataSpace spaceBlockFile(1, dimBlockFile);
	spaceBlockFile.selectHyperslab(H5S_SELECT_SET, countFile, offsetBlockBase);
	hsize_t dimBlockMem[1];
	dimBlockMem[0] = nbRow;
	H5::DataSpace blockMem(1, dimBlockMem);
	dataset.read(p_images, getCompTypeImages(), blockMem, spaceBlockFile);
}

///Write the given DataSet and fill the Table with it
/**	@param[out] dataset : dataset to be modified
*/
void space::writeDataSet(H5::DataSet & dataset) const{
	dataset.write(p_images, getCompTypeImages());
}

///Open the given DataSet and prepare the block usage (do not load data)
/**	@param dataset : dataset to be loaded
 * 	@param nbMaxRowPerBlock : maximum number of rows in the block
 * 	You have to use this method with iterateBlock() and getBlockSize() methods
*/
void space::openDataSetBlock(const H5::DataSet & dataset, size_t nbMaxRowPerBlock){
	p__blockOffset = 0lu;
	H5::DataSpace spaceEvent = dataset.getSpace();
	p__totalDataSetRow = spaceEvent.getSelectNpoints();
	p__dataset = dataset;
	if(p__totalDataSetRow > nbMaxRowPerBlock){	//If there are more rows than block's size
		p__blockSize = nbMaxRowPerBlock;
	}else{	//Otherwise we get all rows
		p__blockSize = p__totalDataSetRow;
	}
}

///Iterate over the blocks and load the current block
/**	@return true if the current block has been loaded, false if we reach the end of the blocks
*/
bool space::iterateBlock(){
	if(p__blockOffset >= p__totalDataSetRow){p__blockOffset = 0lu;return false;}	//We reach the end of the DataSet
	if(p__blockOffset + p__blockSize > p__totalDataSetRow){
		p__blockSize = p__totalDataSetRow - p__blockOffset;
	}
	readDataSet(p__dataset, p__blockOffset, p__blockSize);	//Let's read the current block
	p__blockOffset += p__blockSize;				//Let's increment the offset
	return true;
}

///Get the full size of the loaded DataSet
/**	@return full size of the loaded DataSet
*/
size_t space::getFullDataSetSize() const{
	return p__totalDataSetRow;
}

///Get the size of the current block
/**	@return size of the currently loaded block
*/
size_t space::getBlockSize() const{
	return p__blockSize;
}

///Get the offset of the current block
/**	@return offset of the currently loaded block
*/
size_t space::getBlockOffset() const{
	return p__blockOffset;
}

///Initialises the table space
void space::initialisationspace(){
	p__nbRow = 0lu;
	p__tableName = "event/telescope/images/LST_LSTCam";
	p_nb_pixels = 0lu;
	p_images = NULL;
}

///Allocate the table space (delete all column)
/**	@param nbRow : new number of rows of the Table
*/
void space::allocate(size_t nbRow){
	p__nbRow = nbRow;
	if(p__nbRow == 0lu){
		initialisationspace();
		return;
	}
	p_images = new float[p__nbRow*p_nb_pixels];
}

///Copy function of the class space
/**	@param other : space to be copied
*/
void space::copyspace(const space & other){
	//Let's copy proper attributes of the space
	p__tableName = other.p__tableName;
	p__totalDataSetRow = other.p__totalDataSetRow;
	p__blockSize = other.p__blockSize;
	p__blockOffset = other.p__blockOffset;
	//Let's copy extra dimension of the space
	p_nb_pixels = other.p_nb_pixels;
	//Let's allocate columns of space
	allocate(other.p__nbRow);	//Let's allocate properly everything
	//Let's copy columns of space
	memcpy(p_images, other.p_images, sizeof(float)*p__nbRow*p_nb_pixels);
}

///Update the dimentions of the tensor images (column 'image')
/**	@param compType : main type to be used to update the tensor dimentions*/
void space::readDimImages(const H5::CompType & compType){
	int indexCol = compType.getMemberIndex("image");
	H5::ArrayType arrayType = compType.getMemberArrayType(indexCol);
	//Check if the number of dientions matches
	if(arrayType.getArrayNDims() != 1){
		std::stringstream strError;
		strError << "space::readDimImages wrong number of dimentions : expect 1 but "<< arrayType.getArrayNDims() <<" provided from the file" << std::endl;
		throw std::runtime_error(strError.str());
	}
	hsize_t dims[1];
	arrayType.getArrayDims(dims);
	p_nb_pixels = dims[0];
}

///Constructor of the class componentsPrincipal
componentsPrincipal::componentsPrincipal(){
	initialisationcomponentsPrincipal();
}

///Copy constructor of the class componentsPrincipal
/**	@param other : componentsPrincipal to be copied
*/
componentsPrincipal::componentsPrincipal(const componentsPrincipal & other){
	initialisationcomponentsPrincipal();
	copycomponentsPrincipal(other);
}

///Destructor of the class componentsPrincipal
componentsPrincipal::~componentsPrincipal(){
	clear();
}

///Equal operator of the class componentsPrincipal
/**	@param other : componentsPrincipal to be copied
 * 	@return copied componentsPrincipal
*/
componentsPrincipal & componentsPrincipal::operator = (const componentsPrincipal & other){
	copycomponentsPrincipal(other);
	return *this;
}

///Set the HDF5 name of the Table componentsPrincipal
/**	@param name : name of the table to be saved
*/
void componentsPrincipal::setTableName(const std::string & name){
	p__tableName = name;
}

///Get the total number of rows in the current Table componentsPrincipal
/**	@return total number of rows
*/
size_t componentsPrincipal::getNbEntries() const{
	return p__nbRow;
}

///Resize the table componentsPrincipal
/*	@param nbRow : new number of rows of the Table
*/
void componentsPrincipal::resize(size_t nbRow){
	if(nbRow == p__nbRow){return;}	//Nothing to do
	clear();
	allocate(nbRow);
}

///Clear the table componentsPrincipal (delete all column)
void componentsPrincipal::clear(){
	if(p_pc != NULL){delete [] p_pc;p_pc = NULL;}
	if(p_sv != NULL){delete [] p_sv;p_sv = NULL;}
	if(p_psv != NULL){delete [] p_psv;p_psv = NULL;}
}

///Read the table componentsPrincipal from given file
/**	@param fileName : name of the HDF5 file to be used
*/
void componentsPrincipal::read(const std::string & fileName){
	H5::H5File file(fileName, H5F_ACC_RDONLY);
	read(file);
}

///Read the table componentsPrincipal from given file
/**	@param file : HDF5 file to be used
*/
void componentsPrincipal::read(const H5::H5File & file){
	H5::DataSet dataset = openDataSet(file);
	readDataSet(dataset);
}

///Read the table componentsPrincipal from given group
/**	@param group : HDF5 group to be used
*/
void componentsPrincipal::read(const H5::Group & group){
	H5::DataSet dataset = openDataSet(group);
	readDataSet(dataset);
}

///Read the table componentsPrincipal from given file
/**	@param fileName : name of the HDF5 file to be used
 * 	@param offset : index of the first row the componentsPrincipal class needs to load
 * 	@param nbRow : number of rows the componentsPrincipal class needs to load (Will reallocate the componentsPrincipal is the number of rows is greater than the number off already allocated rows)
*/
void componentsPrincipal::read(const std::string & fileName, size_t offset, size_t nbRow){
	H5::H5File file(fileName, H5F_ACC_RDONLY);
	read(file, offset, nbRow);
}

///Read the table componentsPrincipal from given file
/**	@param file : HDF5 file to be used
 * 	@param offset : index of the first row the componentsPrincipal class needs to load
 * 	@param nbRow : number of rows the componentsPrincipal class needs to load (Will reallocate the componentsPrincipal is the number of rows is greater than the number off already allocated rows)
*/
void componentsPrincipal::read(const H5::H5File & file, size_t offset, size_t nbRow){
	H5::DataSet dataset = openDataSet(file);
	readDataSet(dataset, offset, nbRow);
}

///Read the table componentsPrincipal from given group
/**	@param group : HDF5 group to be used
 * 	@param offset : index of the first row the componentsPrincipal class needs to load
 * 	@param nbRow : number of rows the componentsPrincipal class needs to load (Will reallocate the componentsPrincipal is the number of rows is greater than the number off already allocated rows)
*/
void componentsPrincipal::read(const H5::Group & group, size_t offset, size_t nbRow){
	H5::DataSet dataset = openDataSet(group);
	readDataSet(dataset, offset, nbRow);
}

///Create and write the table componentsPrincipal in given file
/**	@param fileName : name of the HDF5 file to be used
*/
void componentsPrincipal::write(const std::string & fileName) const{
	H5::H5File file(fileName, H5F_ACC_TRUNC);
	write(file);
}

///Create and write the table componentsPrincipal in given file
/**	@param file : HDF5 file to be used
*/
void componentsPrincipal::write(H5::H5File & file) const{
	H5::DataSet dataset = createDataSet(file, p__nbRow);
	writeDataSet(dataset);
}

///Create and write the table componentsPrincipal in given file
/**	@param group : HDF5 group to be used
*/
void componentsPrincipal::write(H5::Group & group) const{
	H5::DataSet dataset = createDataSet(group, p__nbRow);
	writeDataSet(dataset);
}

///Create and write the table componentsPrincipal in given file
/**	@param fileName : name of the HDF5 file to be used
 * 	@param nbRow : full number of rows in the DataSet
 * 	@return created DataSet
*/
H5::DataSet componentsPrincipal::createDataSet(const std::string & fileName, size_t nbRow) const{
	H5::H5File file(fileName, H5F_ACC_TRUNC);
	return createDataSet(file, nbRow);
}

///Create the DataSet of the table componentsPrincipal in given file
/**	@param file : HDF5 file to be used
 * 	@param nbRow : full number of rows in the DataSet
 * 	@return created DataSet
*/
H5::DataSet componentsPrincipal::createDataSet(H5::H5File & file, size_t nbRow) const{
	hsize_t dim[1];
	dim[0] = nbRow;
	H5::DataSpace space(1, dim);
	H5::DataSet dataset = file.createDataSet(p__tableName, getCompTypeAll(), space);
	return dataset;
}

///Create the DataSet of the table componentsPrincipal in given group
/**	@param group : HDF5 group to be used
 * 	@param nbRow : full number of rows in the DataSet
 * 	@return created DataSet
*/
H5::DataSet componentsPrincipal::createDataSet(H5::Group & group, size_t nbRow) const{
	hsize_t dim[1];
	dim[0] = nbRow;
	H5::DataSpace space(1, dim);
	H5::DataSet dataset = group.createDataSet(p__tableName, getCompTypeAll(), space);
	return dataset;
}

///Open and write the table componentsPrincipal in given file
/**	@param fileName : name of the HDF5 file to be used
 * 	@return opened DataSet
*/
H5::DataSet componentsPrincipal::openDataSet(const std::string & fileName) const{
	H5::H5File file(fileName, H5F_ACC_RDONLY);
	return openDataSet(file);
}

///Open the DataSet of the table componentsPrincipal in given file
/**	@param file : HDF5 file to be used
 * 	@return opened DataSet
*/
H5::DataSet componentsPrincipal::openDataSet(const H5::H5File & file) const{
	H5::DataSet dataset = file.openDataSet(p__tableName);
	return dataset;
}

///Open the DataSet of the table componentsPrincipal in given group
/**	@param group : HDF5 group to be used
 * 	@return opened DataSet
*/
H5::DataSet componentsPrincipal::openDataSet(const H5::Group & group) const{
	H5::DataSet dataset = group.openDataSet(p__tableName);
	return dataset;
}

///Open the DataSet of the table componentsPrincipal in given file (for block usage)
/**	@param fileName : name of the HDF5 file to be used
 * 	@param nbMaxRowPerBlock : maximum number of rows in the block
*/
void componentsPrincipal::openDataSetBlock(const std::string & fileName, size_t nbMaxRowPerBlock){
	H5::H5File file(fileName, H5F_ACC_RDONLY);
	openDataSetBlock(file, nbMaxRowPerBlock);
}

///Open the DataSet of the table componentsPrincipal in given file (for block usage)
/**	@param file : HDF5 file to be used
 * 	@param nbMaxRowPerBlock : maximum number of rows in the block
*/
void componentsPrincipal::openDataSetBlock(const H5::H5File & file, size_t nbMaxRowPerBlock){
	H5::DataSet dataset = file.openDataSet(p__tableName);
	openDataSetBlock(dataset, nbMaxRowPerBlock);
}

///Open the DataSet of the table componentsPrincipal in given group (for block usage)
/**	@param group : HDF5 group to be used
 * 	@param nbMaxRowPerBlock : maximum number of rows in the block
*/
void componentsPrincipal::openDataSetBlock(const H5::Group & group, size_t nbMaxRowPerBlock){
	H5::DataSet dataset = group.openDataSet(p__tableName);
	openDataSetBlock(dataset, nbMaxRowPerBlock);
}

///Set a full row of the table componentsPrincipal
/**	@param i : index of the row to be set
 * 	@param pc : attribute to be set
 * 	@param sv : attribute to be set
 * 	@param psv : attribute to be set
*/
void componentsPrincipal::setRow(size_t i, float * pc, float sv, float psv){
	setPc(i, pc);
	setSv(i, sv);
	setPsv(i, psv);
}

///Get a full row of the table componentsPrincipal (without tensor copy, only with pointer)
/**	@param i : index of the row to get its values
 * 	@param[out] pc : attribute to be get
 * 	@param[out] sv : attribute to be get
 * 	@param[out] psv : attribute to be get
*/
void componentsPrincipal::getRow(size_t i, float *& pc, float & sv, float & psv){
	pc = getPc(i);
	sv = getSv(i);
	psv = getPsv(i);
}

///Get a full row of the table componentsPrincipal (without tensor copy, only with pointer)
/**	@param i : index of the row to get its values
 * 	@param[out] pc : attribute to be get
 * 	@param[out] sv : attribute to be get
 * 	@param[out] psv : attribute to be get
*/
void componentsPrincipal::getRow(size_t i, const float *& pc, float & sv, float & psv) const{
	pc = getPc(i);
	sv = getSv(i);
	psv = getPsv(i);
}

///Set the attribute pc (column pc)
/**	@param i : index of the row to be used
 * 	@param tabVal : table of value to be copied
*/
void componentsPrincipal::setPc(size_t i, const float * tabVal){
	size_t sizeRow(p_nb_pc);
	memcpy(p_pc + i*sizeRow, tabVal, sizeRow*sizeof(float));
}

///Set the attribute sv (column sv)
/**	@param i : index of the row to be used
 * 	@param val : value to be copied
*/
void componentsPrincipal::setSv(size_t i, float val){
	p_sv[i] = val;
}

///Set the attribute psv (column psv)
/**	@param i : index of the row to be used
 * 	@param val : value to be copied
*/
void componentsPrincipal::setPsv(size_t i, float val){
	p_psv[i] = val;
}

///Get the full column of the attribute pc (column pc)
/**	@return pointer of the full column
*/
const float * componentsPrincipal::getPcFull() const{
	return p_pc;
}

///Get the full column of the attribute pc (column pc)
/**	@return pointer of the full column
*/
float * componentsPrincipal::getPcFull(){
	return p_pc;
}

///Get the tensor i of the attribute pc (column pc)
/**	@param i : index of the row to be used
 * 	@return pointer to the corresponding tensor
*/
const float * componentsPrincipal::getPc(size_t i) const{
	return p_pc + i*p_nb_pc;
}

///Get the tensor i of the attribute pc (column pc)
/**	@param i : index of the row to be used
 * 	@return pointer to the corresponding tensor
*/
float * componentsPrincipal::getPc(size_t i){
	return p_pc + i*p_nb_pc;
}

///Get the full column of the attribute sv (column sv)
/**	@return pointer of the full column
*/
const float * componentsPrincipal::getSvFull() const{
	return p_sv;
}

///Get the full column of the attribute sv (column sv)
/**	@return pointer of the full column
*/
float * componentsPrincipal::getSvFull(){
	return p_sv;
}

///Get the value i of the attribute sv (column sv)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
float componentsPrincipal::getSv(size_t i) const{
	return p_sv[i];
}

///Get the value i of the attribute sv (column sv)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
float & componentsPrincipal::getSv(size_t i){
	return p_sv[i];
}

///Get the full column of the attribute psv (column psv)
/**	@return pointer of the full column
*/
const float * componentsPrincipal::getPsvFull() const{
	return p_psv;
}

///Get the full column of the attribute psv (column psv)
/**	@return pointer of the full column
*/
float * componentsPrincipal::getPsvFull(){
	return p_psv;
}

///Get the value i of the attribute psv (column psv)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
float componentsPrincipal::getPsv(size_t i) const{
	return p_psv[i];
}

///Get the value i of the attribute psv (column psv)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
float & componentsPrincipal::getPsv(size_t i){
	return p_psv[i];
}

///Set all the dimentions of the Tensor in the table
/**	@param nb_pc : set the tensor dimention nb_pc
*/
void componentsPrincipal::setAllDim(size_t nb_pc){
	setNb_pc(nb_pc);
}

///Set the Tensor dimention nb_pc
/**	@param val : set the tensor dimention nb_pc
*/
void componentsPrincipal::setNb_pc(size_t val){
	 p_nb_pc = val;
}

///Get the Tensor dimention nb_pc
/**	@return the tensor dimention nb_pc
*/
size_t componentsPrincipal::getNb_pc() const{
	return p_nb_pc;
}

///Get the offset of the attribute pc
/**	@return offset of the attribute in bytes
*/
size_t componentsPrincipal::getOffsetPc() const{
	return 0lu;
}

///Get the offset of the attribute sv
/**	@return offset of the attribute in bytes
*/
size_t componentsPrincipal::getOffsetSv() const{
	return getOffsetPc() + sizeof(float)*p_nb_pc;
}

///Get the offset of the attribute psv
/**	@return offset of the attribute in bytes
*/
size_t componentsPrincipal::getOffsetPsv() const{
	return getOffsetSv() + sizeof(float);
}

H5::CompType componentsPrincipal::getCompTypeAll() const{
	size_t sizeAll(sizeof(float)*p_nb_pc + sizeof(float) + sizeof(float));
	H5::CompType typeCol(sizeAll);
	typeCol.insertMember("pc", getOffsetPc(), getTypePc());
	typeCol.insertMember("sv", getOffsetSv(), getTypeSv());
	typeCol.insertMember("psv", getOffsetPsv(), getTypePsv());
	return typeCol;
}

///Get DataType of attribute pc (column pc)
/**	@return DataType of the attribute pc
*/
H5::CompType componentsPrincipal::getCompTypePc() const{
	H5::CompType typeCol(sizeof(float)*p_nb_pc);
	typeCol.insertMember("pc", 0, getTypePc());
	return typeCol;
}

///Get DataType of attribute sv (column sv)
/**	@return DataType of the attribute sv
*/
H5::CompType componentsPrincipal::getCompTypeSv() const{
	H5::CompType typeCol(sizeof(float));
	typeCol.insertMember("sv", 0, getTypeSv());
	return typeCol;
}

///Get DataType of attribute psv (column psv)
/**	@return DataType of the attribute psv
*/
H5::CompType componentsPrincipal::getCompTypePsv() const{
	H5::CompType typeCol(sizeof(float));
	typeCol.insertMember("psv", 0, getTypePsv());
	return typeCol;
}

///Get DataType of attribute pc (column pc)
/**	@return DataType of the attribute pc
*/
H5::DataType componentsPrincipal::getTypePc() const{
	hsize_t dims[1];
	dims[0] = p_nb_pc;
	H5::ArrayType arrayType(H5::PredType::NATIVE_FLOAT, 1, dims);
	return arrayType;
}

///Get DataType of attribute sv (column sv)
/**	@return DataType of the attribute sv
*/
H5::DataType componentsPrincipal::getTypeSv() const{
	return H5::PredType::NATIVE_FLOAT;
}

///Get DataType of attribute psv (column psv)
/**	@return DataType of the attribute psv
*/
H5::DataType componentsPrincipal::getTypePsv() const{
	return H5::PredType::NATIVE_FLOAT;
}

///Read the given DataSet and fill the Table with it
/**	@param dataset : dataset to be used
*/
void componentsPrincipal::readDataSet(const H5::DataSet & dataset){
	H5::CompType compType = dataset.getCompType();
	readDimPc(compType);
	H5::DataSpace dataSpace = dataset.getSpace();
	size_t nbEntries(dataSpace.getSimpleExtentNpoints());
	resize(nbEntries);
	dataset.read(p_pc, getCompTypePc());
	dataset.read(p_sv, getCompTypeSv());
	dataset.read(p_psv, getCompTypePsv());
}

///Read the given DataSet and fill the Table with it
/**	@param dataset : dataset to be used
 * 	@param offset : index of the first row the componentsPrincipal class needs to load
 * 	@param nbRow : number of rows the componentsPrincipal class needs to load (Will reallocate the componentsPrincipal is the number of rows is greater than the number off already allocated rows)
*/
void componentsPrincipal::readDataSet(const H5::DataSet & dataset, size_t offset, size_t nbRow){
	H5::CompType compType = dataset.getCompType();
	readDimPc(compType);
	H5::DataSpace dataSpace = dataset.getSpace();
	size_t nbEntries(dataSpace.getSimpleExtentNpoints());
	resize(nbRow);
	hsize_t dimBlockFile[1];
	dimBlockFile[0] = nbEntries;
	hsize_t offsetBlockBase[1];
	offsetBlockBase[0] = offset;
	hsize_t countFile[1];
	countFile[0] = nbRow;
	H5::DataSpace spaceBlockFile(1, dimBlockFile);
	spaceBlockFile.selectHyperslab(H5S_SELECT_SET, countFile, offsetBlockBase);
	hsize_t dimBlockMem[1];
	dimBlockMem[0] = nbRow;
	H5::DataSpace blockMem(1, dimBlockMem);
	dataset.read(p_pc, getCompTypePc(), blockMem, spaceBlockFile);
	dataset.read(p_sv, getCompTypeSv(), blockMem, spaceBlockFile);
	dataset.read(p_psv, getCompTypePsv(), blockMem, spaceBlockFile);
}

///Write the given DataSet and fill the Table with it
/**	@param[out] dataset : dataset to be modified
*/
void componentsPrincipal::writeDataSet(H5::DataSet & dataset) const{
	dataset.write(p_pc, getCompTypePc());
	dataset.write(p_sv, getCompTypeSv());
	dataset.write(p_psv, getCompTypePsv());
}

///Open the given DataSet and prepare the block usage (do not load data)
/**	@param dataset : dataset to be loaded
 * 	@param nbMaxRowPerBlock : maximum number of rows in the block
 * 	You have to use this method with iterateBlock() and getBlockSize() methods
*/
void componentsPrincipal::openDataSetBlock(const H5::DataSet & dataset, size_t nbMaxRowPerBlock){
	p__blockOffset = 0lu;
	H5::DataSpace spaceEvent = dataset.getSpace();
	p__totalDataSetRow = spaceEvent.getSelectNpoints();
	p__dataset = dataset;
	if(p__totalDataSetRow > nbMaxRowPerBlock){	//If there are more rows than block's size
		p__blockSize = nbMaxRowPerBlock;
	}else{	//Otherwise we get all rows
		p__blockSize = p__totalDataSetRow;
	}
}

///Iterate over the blocks and load the current block
/**	@return true if the current block has been loaded, false if we reach the end of the blocks
*/
bool componentsPrincipal::iterateBlock(){
	if(p__blockOffset >= p__totalDataSetRow){p__blockOffset = 0lu;return false;}	//We reach the end of the DataSet
	if(p__blockOffset + p__blockSize > p__totalDataSetRow){
		p__blockSize = p__totalDataSetRow - p__blockOffset;
	}
	readDataSet(p__dataset, p__blockOffset, p__blockSize);	//Let's read the current block
	p__blockOffset += p__blockSize;				//Let's increment the offset
	return true;
}

///Get the full size of the loaded DataSet
/**	@return full size of the loaded DataSet
*/
size_t componentsPrincipal::getFullDataSetSize() const{
	return p__totalDataSetRow;
}

///Get the size of the current block
/**	@return size of the currently loaded block
*/
size_t componentsPrincipal::getBlockSize() const{
	return p__blockSize;
}

///Get the offset of the current block
/**	@return offset of the currently loaded block
*/
size_t componentsPrincipal::getBlockOffset() const{
	return p__blockOffset;
}

///Initialises the table componentsPrincipal
void componentsPrincipal::initialisationcomponentsPrincipal(){
	p__nbRow = 0lu;
	p__tableName = "componentsPrincipal";
	p_nb_pc = 0lu;
	p_pc = NULL;
	p_sv = NULL;
	p_psv = NULL;
}

///Allocate the table componentsPrincipal (delete all column)
/**	@param nbRow : new number of rows of the Table
*/
void componentsPrincipal::allocate(size_t nbRow){
	p__nbRow = nbRow;
	if(p__nbRow == 0lu){
		initialisationcomponentsPrincipal();
		return;
	}
	p_pc = new float[p__nbRow*p_nb_pc];
	p_sv = new float[p__nbRow];
	p_psv = new float[p__nbRow];
}

///Copy function of the class componentsPrincipal
/**	@param other : componentsPrincipal to be copied
*/
void componentsPrincipal::copycomponentsPrincipal(const componentsPrincipal & other){
	//Let's copy proper attributes of the componentsPrincipal
	p__tableName = other.p__tableName;
	p__totalDataSetRow = other.p__totalDataSetRow;
	p__blockSize = other.p__blockSize;
	p__blockOffset = other.p__blockOffset;
	//Let's copy extra dimension of the componentsPrincipal
	p_nb_pc = other.p_nb_pc;
	//Let's allocate columns of componentsPrincipal
	allocate(other.p__nbRow);	//Let's allocate properly everything
	//Let's copy columns of componentsPrincipal
	memcpy(p_pc, other.p_pc, sizeof(float)*p__nbRow*p_nb_pc);
	memcpy(p_sv, other.p_sv, sizeof(float)*p__nbRow);
	memcpy(p_psv, other.p_psv, sizeof(float)*p__nbRow);
}

///Update the dimentions of the tensor pc (column 'pc')
/**	@param compType : main type to be used to update the tensor dimentions*/
void componentsPrincipal::readDimPc(const H5::CompType & compType){
	int indexCol = compType.getMemberIndex("pc");
	H5::ArrayType arrayType = compType.getMemberArrayType(indexCol);
	//Check if the number of dientions matches
	if(arrayType.getArrayNDims() != 1){
		std::stringstream strError;
		strError << "componentsPrincipal::readDimPc wrong number of dimentions : expect 1 but "<< arrayType.getArrayNDims() <<" provided from the file" << std::endl;
		throw std::runtime_error(strError.str());
	}
	hsize_t dims[1];
	arrayType.getArrayDims(dims);
	p_nb_pc = dims[0];
}

