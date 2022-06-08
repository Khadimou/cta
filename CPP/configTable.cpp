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
	if(p_eventId != NULL){delete [] p_eventId;p_eventId = NULL;}
	if(p_file_id != NULL){delete [] p_file_id;p_file_id = NULL;}
	if(p_energy != NULL){delete [] p_energy;p_energy = NULL;}
	if(p_hfirstint != NULL){delete [] p_hfirstint;p_hfirstint = NULL;}
	if(p_Imax != NULL){delete [] p_Imax;p_Imax = NULL;}
	if(p_impact != NULL){delete [] p_impact;p_impact = NULL;}
	if(p_x != NULL){delete [] p_x;p_x = NULL;}
	if(p_y != NULL){delete [] p_y;p_y = NULL;}
	if(p_hash != NULL){delete [] p_hash;p_hash = NULL;}
	if(p_sv != NULL){delete [] p_sv;p_sv = NULL;}
	if(p_alpha != NULL){delete [] p_alpha;p_alpha = NULL;}
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
 * 	@param eventId : attribute to be set
 * 	@param file_id : attribute to be set
 * 	@param energy : attribute to be set
 * 	@param hfirstint : attribute to be set
 * 	@param Imax : attribute to be set
 * 	@param impact : attribute to be set
 * 	@param x : attribute to be set
 * 	@param y : attribute to be set
 * 	@param hash : attribute to be set
 * 	@param sv : attribute to be set
 * 	@param alpha : attribute to be set
*/
void TableEvent::setRow(size_t i, size_t eventId, size_t file_id, float energy, float hfirstint, float Imax, float impact, float x, float y, char * hash, float * sv, float alpha){
	setEventId(i, eventId);
	setFile_id(i, file_id);
	setEnergy(i, energy);
	setHfirstint(i, hfirstint);
	setImax(i, Imax);
	setImpact(i, impact);
	setX(i, x);
	setY(i, y);
	setHash(i, hash);
	setSv(i, sv);
	setAlpha(i, alpha);
}

///Get a full row of the table TableEvent (without tensor copy, only with pointer)
/**	@param i : index of the row to get its values
 * 	@param[out] eventId : attribute to be get
 * 	@param[out] file_id : attribute to be get
 * 	@param[out] energy : attribute to be get
 * 	@param[out] hfirstint : attribute to be get
 * 	@param[out] Imax : attribute to be get
 * 	@param[out] impact : attribute to be get
 * 	@param[out] x : attribute to be get
 * 	@param[out] y : attribute to be get
 * 	@param[out] hash : attribute to be get
 * 	@param[out] sv : attribute to be get
 * 	@param[out] alpha : attribute to be get
*/
void TableEvent::getRow(size_t i, size_t & eventId, size_t & file_id, float & energy, float & hfirstint, float & Imax, float & impact, float & x, float & y, char *& hash, float *& sv, float & alpha){
	eventId = getEventId(i);
	file_id = getFile_id(i);
	energy = getEnergy(i);
	hfirstint = getHfirstint(i);
	Imax = getImax(i);
	impact = getImpact(i);
	x = getX(i);
	y = getY(i);
	hash = getHash(i);
	sv = getSv(i);
	alpha = getAlpha(i);
}

///Get a full row of the table TableEvent (without tensor copy, only with pointer)
/**	@param i : index of the row to get its values
 * 	@param[out] eventId : attribute to be get
 * 	@param[out] file_id : attribute to be get
 * 	@param[out] energy : attribute to be get
 * 	@param[out] hfirstint : attribute to be get
 * 	@param[out] Imax : attribute to be get
 * 	@param[out] impact : attribute to be get
 * 	@param[out] x : attribute to be get
 * 	@param[out] y : attribute to be get
 * 	@param[out] hash : attribute to be get
 * 	@param[out] sv : attribute to be get
 * 	@param[out] alpha : attribute to be get
*/
void TableEvent::getRow(size_t i, size_t & eventId, size_t & file_id, float & energy, float & hfirstint, float & Imax, float & impact, float & x, float & y, const char *& hash, const float *& sv, float & alpha) const{
	eventId = getEventId(i);
	file_id = getFile_id(i);
	energy = getEnergy(i);
	hfirstint = getHfirstint(i);
	Imax = getImax(i);
	impact = getImpact(i);
	x = getX(i);
	y = getY(i);
	hash = getHash(i);
	sv = getSv(i);
	alpha = getAlpha(i);
}

///Set the attribute eventId (column eventId)
/**	@param i : index of the row to be used
 * 	@param val : value to be copied
*/
void TableEvent::setEventId(size_t i, size_t val){
	p_eventId[i] = val;
}

///Set the attribute file_id (column file_id)
/**	@param i : index of the row to be used
 * 	@param val : value to be copied
*/
void TableEvent::setFile_id(size_t i, size_t val){
	p_file_id[i] = val;
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

///Set the attribute Imax (column Imax)
/**	@param i : index of the row to be used
 * 	@param val : value to be copied
*/
void TableEvent::setImax(size_t i, float val){
	p_Imax[i] = val;
}

///Set the attribute impact (column impact)
/**	@param i : index of the row to be used
 * 	@param val : value to be copied
*/
void TableEvent::setImpact(size_t i, float val){
	p_impact[i] = val;
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

///Set the attribute hash (column hash)
/**	@param i : index of the row to be used
 * 	@param tabVal : table of value to be copied
*/
void TableEvent::setHash(size_t i, const char * tabVal){
	size_t sizeRow(TABLEEVENT_HASH_0);
	memcpy(p_hash + i*sizeRow, tabVal, sizeRow*sizeof(char));
}

///Set the attribute sv (column sv)
/**	@param i : index of the row to be used
 * 	@param tabVal : table of value to be copied
*/
void TableEvent::setSv(size_t i, const float * tabVal){
	size_t sizeRow(p_nb_vs);
	memcpy(p_sv + i*sizeRow, tabVal, sizeRow*sizeof(float));
}

///Set the attribute alpha (column alpha)
/**	@param i : index of the row to be used
 * 	@param val : value to be copied
*/
void TableEvent::setAlpha(size_t i, float val){
	p_alpha[i] = val;
}

///Get the full column of the attribute eventId (column eventId)
/**	@return pointer of the full column
*/
const size_t * TableEvent::getEventIdFull() const{
	return p_eventId;
}

///Get the full column of the attribute eventId (column eventId)
/**	@return pointer of the full column
*/
size_t * TableEvent::getEventIdFull(){
	return p_eventId;
}

///Get the value i of the attribute eventId (column eventId)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
size_t TableEvent::getEventId(size_t i) const{
	return p_eventId[i];
}

///Get the value i of the attribute eventId (column eventId)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
size_t & TableEvent::getEventId(size_t i){
	return p_eventId[i];
}

///Get the full column of the attribute file_id (column file_id)
/**	@return pointer of the full column
*/
const size_t * TableEvent::getFile_idFull() const{
	return p_file_id;
}

///Get the full column of the attribute file_id (column file_id)
/**	@return pointer of the full column
*/
size_t * TableEvent::getFile_idFull(){
	return p_file_id;
}

///Get the value i of the attribute file_id (column file_id)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
size_t TableEvent::getFile_id(size_t i) const{
	return p_file_id[i];
}

///Get the value i of the attribute file_id (column file_id)
/**	@param i : index of the row to be used
 * 	@return corresponding value
*/
size_t & TableEvent::getFile_id(size_t i){
	return p_file_id[i];
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

///Get the full column of the attribute hash (column hash)
/**	@return pointer of the full column
*/
const char * TableEvent::getHashFull() const{
	return p_hash;
}

///Get the full column of the attribute hash (column hash)
/**	@return pointer of the full column
*/
char * TableEvent::getHashFull(){
	return p_hash;
}

///Get the tensor i of the attribute hash (column hash)
/**	@param i : index of the row to be used
 * 	@return pointer to the corresponding tensor
*/
const char * TableEvent::getHash(size_t i) const{
	return p_hash + i*TABLEEVENT_HASH_0;
}

///Get the tensor i of the attribute hash (column hash)
/**	@param i : index of the row to be used
 * 	@return pointer to the corresponding tensor
*/
char * TableEvent::getHash(size_t i){
	return p_hash + i*TABLEEVENT_HASH_0;
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

///Get the offset of the attribute eventId
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetEventId() const{
	return 0lu;
}

///Get the offset of the attribute file_id
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetFile_id() const{
	return getOffsetEventId() + sizeof(size_t);
}

///Get the offset of the attribute energy
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetEnergy() const{
	return getOffsetFile_id() + sizeof(size_t);
}

///Get the offset of the attribute hfirstint
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetHfirstint() const{
	return getOffsetEnergy() + sizeof(float);
}

///Get the offset of the attribute Imax
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetImax() const{
	return getOffsetHfirstint() + sizeof(float);
}

///Get the offset of the attribute impact
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetImpact() const{
	return getOffsetImax() + sizeof(float);
}

///Get the offset of the attribute x
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetX() const{
	return getOffsetImpact() + sizeof(float);
}

///Get the offset of the attribute y
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetY() const{
	return getOffsetX() + sizeof(float);
}

///Get the offset of the attribute hash
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetHash() const{
	return getOffsetY() + sizeof(float);
}

///Get the offset of the attribute sv
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetSv() const{
	return getOffsetHash() + sizeof(char)*TABLEEVENT_HASH_0;
}

///Get the offset of the attribute alpha
/**	@return offset of the attribute in bytes
*/
size_t TableEvent::getOffsetAlpha() const{
	return getOffsetSv() + sizeof(float)*p_nb_vs;
}

H5::CompType TableEvent::getCompTypeAll() const{
	size_t sizeAll(sizeof(size_t) + sizeof(size_t) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(char)*TABLEEVENT_HASH_0 + sizeof(float)*p_nb_vs + sizeof(float));
	H5::CompType typeCol(sizeAll);
	typeCol.insertMember("eventId", getOffsetEventId(), getTypeEventId());
	typeCol.insertMember("file_id", getOffsetFile_id(), getTypeFile_id());
	typeCol.insertMember("energy", getOffsetEnergy(), getTypeEnergy());
	typeCol.insertMember("hfirstint", getOffsetHfirstint(), getTypeHfirstint());
	typeCol.insertMember("Imax", getOffsetImax(), getTypeImax());
	typeCol.insertMember("impact", getOffsetImpact(), getTypeImpact());
	typeCol.insertMember("x", getOffsetX(), getTypeX());
	typeCol.insertMember("y", getOffsetY(), getTypeY());
	typeCol.insertMember("hash", getOffsetHash(), getTypeHash());
	typeCol.insertMember("sv", getOffsetSv(), getTypeSv());
	typeCol.insertMember("alpha", getOffsetAlpha(), getTypeAlpha());
	return typeCol;
}

///Get DataType of attribute eventId (column eventId)
/**	@return DataType of the attribute eventId
*/
H5::CompType TableEvent::getCompTypeEventId() const{
	H5::CompType typeCol(sizeof(size_t));
	typeCol.insertMember("eventId", 0, getTypeEventId());
	return typeCol;
}

///Get DataType of attribute file_id (column file_id)
/**	@return DataType of the attribute file_id
*/
H5::CompType TableEvent::getCompTypeFile_id() const{
	H5::CompType typeCol(sizeof(size_t));
	typeCol.insertMember("file_id", 0, getTypeFile_id());
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

///Get DataType of attribute Imax (column Imax)
/**	@return DataType of the attribute Imax
*/
H5::CompType TableEvent::getCompTypeImax() const{
	H5::CompType typeCol(sizeof(float));
	typeCol.insertMember("Imax", 0, getTypeImax());
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

///Get DataType of attribute hash (column hash)
/**	@return DataType of the attribute hash
*/
H5::CompType TableEvent::getCompTypeHash() const{
	H5::CompType typeCol(sizeof(char)*TABLEEVENT_HASH_0);
	typeCol.insertMember("hash", 0, getTypeHash());
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

///Get DataType of attribute alpha (column alpha)
/**	@return DataType of the attribute alpha
*/
H5::CompType TableEvent::getCompTypeAlpha() const{
	H5::CompType typeCol(sizeof(float));
	typeCol.insertMember("alpha", 0, getTypeAlpha());
	return typeCol;
}

///Get DataType of attribute eventId (column eventId)
/**	@return DataType of the attribute eventId
*/
H5::DataType TableEvent::getTypeEventId() const{
	return H5::PredType::NATIVE_UINT64;
}

///Get DataType of attribute file_id (column file_id)
/**	@return DataType of the attribute file_id
*/
H5::DataType TableEvent::getTypeFile_id() const{
	return H5::PredType::NATIVE_UINT64;
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

///Get DataType of attribute Imax (column Imax)
/**	@return DataType of the attribute Imax
*/
H5::DataType TableEvent::getTypeImax() const{
	return H5::PredType::NATIVE_FLOAT;
}

///Get DataType of attribute impact (column impact)
/**	@return DataType of the attribute impact
*/
H5::DataType TableEvent::getTypeImpact() const{
	return H5::PredType::NATIVE_FLOAT;
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

///Get DataType of attribute hash (column hash)
/**	@return DataType of the attribute hash
*/
H5::DataType TableEvent::getTypeHash() const{
	hsize_t dims[1];
	dims[0] = TABLEEVENT_HASH_0;
	H5::ArrayType arrayType(H5::PredType::NATIVE_INT8, 1, dims);
	return arrayType;
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

///Get DataType of attribute alpha (column alpha)
/**	@return DataType of the attribute alpha
*/
H5::DataType TableEvent::getTypeAlpha() const{
	return H5::PredType::NATIVE_FLOAT;
}

///Read the given DataSet and fill the Table with it
/**	@param dataset : dataset to be used
*/
void TableEvent::readDataSet(const H5::DataSet & dataset){
	H5::CompType compType = dataset.getCompType();
	readDimHash(compType);
	readDimSv(compType);
	H5::DataSpace dataSpace = dataset.getSpace();
	size_t nbEntries(dataSpace.getSimpleExtentNpoints());
	resize(nbEntries);
	dataset.read(p_eventId, getCompTypeEventId());
	dataset.read(p_file_id, getCompTypeFile_id());
	dataset.read(p_energy, getCompTypeEnergy());
	dataset.read(p_hfirstint, getCompTypeHfirstint());
	dataset.read(p_Imax, getCompTypeImax());
	dataset.read(p_impact, getCompTypeImpact());
	dataset.read(p_x, getCompTypeX());
	dataset.read(p_y, getCompTypeY());
	dataset.read(p_hash, getCompTypeHash());
	dataset.read(p_sv, getCompTypeSv());
	dataset.read(p_alpha, getCompTypeAlpha());
}

///Read the given DataSet and fill the Table with it
/**	@param dataset : dataset to be used
 * 	@param offset : index of the first row the TableEvent class needs to load
 * 	@param nbRow : number of rows the TableEvent class needs to load (Will reallocate the TableEvent is the number of rows is greater than the number off already allocated rows)
*/
void TableEvent::readDataSet(const H5::DataSet & dataset, size_t offset, size_t nbRow){
	H5::CompType compType = dataset.getCompType();
	readDimHash(compType);
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
	dataset.read(p_eventId, getCompTypeEventId(), blockMem, spaceBlockFile);
	dataset.read(p_file_id, getCompTypeFile_id(), blockMem, spaceBlockFile);
	dataset.read(p_energy, getCompTypeEnergy(), blockMem, spaceBlockFile);
	dataset.read(p_hfirstint, getCompTypeHfirstint(), blockMem, spaceBlockFile);
	dataset.read(p_Imax, getCompTypeImax(), blockMem, spaceBlockFile);
	dataset.read(p_impact, getCompTypeImpact(), blockMem, spaceBlockFile);
	dataset.read(p_x, getCompTypeX(), blockMem, spaceBlockFile);
	dataset.read(p_y, getCompTypeY(), blockMem, spaceBlockFile);
	dataset.read(p_hash, getCompTypeHash(), blockMem, spaceBlockFile);
	dataset.read(p_sv, getCompTypeSv(), blockMem, spaceBlockFile);
	dataset.read(p_alpha, getCompTypeAlpha(), blockMem, spaceBlockFile);
}

///Write the given DataSet and fill the Table with it
/**	@param[out] dataset : dataset to be modified
*/
void TableEvent::writeDataSet(H5::DataSet & dataset) const{
	dataset.write(p_eventId, getCompTypeEventId());
	dataset.write(p_file_id, getCompTypeFile_id());
	dataset.write(p_energy, getCompTypeEnergy());
	dataset.write(p_hfirstint, getCompTypeHfirstint());
	dataset.write(p_Imax, getCompTypeImax());
	dataset.write(p_impact, getCompTypeImpact());
	dataset.write(p_x, getCompTypeX());
	dataset.write(p_y, getCompTypeY());
	dataset.write(p_hash, getCompTypeHash());
	dataset.write(p_sv, getCompTypeSv());
	dataset.write(p_alpha, getCompTypeAlpha());
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
	p__tableName = "TableEvent";
	p_nb_vs = 0lu;
	p_eventId = NULL;
	p_file_id = NULL;
	p_energy = NULL;
	p_hfirstint = NULL;
	p_Imax = NULL;
	p_impact = NULL;
	p_x = NULL;
	p_y = NULL;
	p_hash = NULL;
	p_sv = NULL;
	p_alpha = NULL;
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
	p_eventId = new size_t[p__nbRow];
	p_file_id = new size_t[p__nbRow];
	p_energy = new float[p__nbRow];
	p_hfirstint = new float[p__nbRow];
	p_Imax = new float[p__nbRow];
	p_impact = new float[p__nbRow];
	p_x = new float[p__nbRow];
	p_y = new float[p__nbRow];
	p_hash = new char[p__nbRow*TABLEEVENT_HASH_0];
	p_sv = new float[p__nbRow*p_nb_vs];
	p_alpha = new float[p__nbRow];
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
	memcpy(p_eventId, other.p_eventId, sizeof(size_t)*p__nbRow);
	memcpy(p_file_id, other.p_file_id, sizeof(size_t)*p__nbRow);
	memcpy(p_energy, other.p_energy, sizeof(float)*p__nbRow);
	memcpy(p_hfirstint, other.p_hfirstint, sizeof(float)*p__nbRow);
	memcpy(p_Imax, other.p_Imax, sizeof(float)*p__nbRow);
	memcpy(p_impact, other.p_impact, sizeof(float)*p__nbRow);
	memcpy(p_x, other.p_x, sizeof(float)*p__nbRow);
	memcpy(p_y, other.p_y, sizeof(float)*p__nbRow);
	memcpy(p_hash, other.p_hash, sizeof(char)*p__nbRow*TABLEEVENT_HASH_0);
	memcpy(p_sv, other.p_sv, sizeof(float)*p__nbRow*p_nb_vs);
	memcpy(p_alpha, other.p_alpha, sizeof(float)*p__nbRow);
}

///Update the dimentions of the tensor hash (column 'hash')
/**	@param compType : main type to be used to update the tensor dimentions*/
void TableEvent::readDimHash(const H5::CompType & compType){
	int indexCol = compType.getMemberIndex("hash");
	H5::ArrayType arrayType = compType.getMemberArrayType(indexCol);
	//Check if the number of dientions matches
	if(arrayType.getArrayNDims() != 1){
		std::stringstream strError;
		strError << "TableEvent::readDimHash wrong number of dimentions : expect 1 but "<< arrayType.getArrayNDims() <<" provided from the file" << std::endl;
		throw std::runtime_error(strError.str());
	}
	hsize_t dims[1];
	arrayType.getArrayDims(dims);
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

