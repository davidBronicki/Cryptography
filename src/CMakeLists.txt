
cmake_minimum_required(VERSION 3.0)
project(Cryptography_Class_Project)

file(GLOB Executable_Code_Pile
	"*.cpp")

add_executable(crypto_executable ${Executable_Code_Pile})
set_property(TARGET crypto_executable PROPERTY CXX_STANDARD 20)
