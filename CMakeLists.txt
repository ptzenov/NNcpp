cmake_minimum_required(VERSION 2.8) 
project(NN)
 
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
set(CMAKE_CXX "g++")

#Bring the headers, such as Student.h into the project
include_directories(
	include
	)

#Can manually add the sources using the set command as follows:
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB_RECURSE SOURCES "src/*.cpp")
 
add_executable(NN ${SOURCES})


