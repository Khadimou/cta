cmake_minimum_required(VERSION 3.16)

project(fileconfig)
find_package(HDF5 COMPONENTS C CXX HL REQUIRED)
link_directories( ${HDF5_LIBRARY_DIRS} )
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${HDF5_INCLUDE_DIRS})
add_executable(test_table_config configTable.cpp main.cpp)
target_link_libraries(test_table_config ${HDF5_CXX_LIBRARIES})

add_test(NAME TestTableConfig
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_table_config
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_definitions(-g -O3 )
add_executable(test_table_config_full configTable.cpp main_full.cpp)
target_link_libraries(test_table_config_full ${HDF5_CXX_LIBRARIES} )

add_test(NAME TestTableConfigFull
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_table_config_full
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})


