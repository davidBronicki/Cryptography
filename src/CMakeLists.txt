cmake_minimum_required(VERSION 3.0)
project(Cryptography_Class_Project)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pedantic -O0 -g -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -pedantic -O3")

file(GLOB Executable_Code_Pile
	"*.cpp")

add_executable(crypto_executable ${Executable_Code_Pile})
set_target_properties(crypto_executable PROPERTIES
	CXX_STANDARD 11)
