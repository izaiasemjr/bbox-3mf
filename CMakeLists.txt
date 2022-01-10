cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(BoundingBox)


# ------------ Add 3MF -------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Extern/lib3mf/Cpp)
if (WIN32)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/Lib)
	link_libraries(lib3mf)
else()
	# Unix prefixes the name of the library with "lib" anyway
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/Extern/lib3mf/Bin)
	link_libraries(3mf)
	link_directories(${CMAKE_CURRENT_BINARY_DIR})
endif()
#-----------------------------------------------------------------


include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (${PROJECT_NAME} ./src/boundingbox.cpp)
target_link_libraries (${PROJECT_NAME})

