cmake_minimum_required(VERSION 3.16)

project(fileconfig)
find_package(OpenCV REQUIRED)
find_package(HDF5 COMPONENTS C CXX HL REQUIRED)
link_directories( ${HDF5_LIBRARY_DIRS} ${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${HDF5_INCLUDE_DIRS})

add_definitions(-g -O3 -I/home/khadimou/usr/include/StringUtils)
add_executable(test_table_config_full configTable.cpp main_full.cpp /home/khadimou/PhoenixHDF5/tmp_project/StringUtils/src/string_system.cpp
/home/khadimou/PhoenixHDF5/tmp_project/StringUtils/src/string_function.cpp /home/khadimou/PhoenixHDF5/tmp_project/StringUtils/src/string_filename.cpp)
target_link_libraries(test_table_config_full ${HDF5_CXX_LIBRARIES} ${OpenCV_LIBS})

add_test(NAME TestTableConfigFull
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_table_config_full
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})


