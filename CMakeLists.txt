cmake_minimum_required(VERSION 3.5)
project(fzcloud)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

# for dependenciess and customized git modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules/)
#set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /root/local)
# end path variable

# default include dir for all modules
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src/fzrpc)

# add the modules you want to build
add_subdirectory(src/fzc)
add_subdirectory(src/fzcurl)
add_subdirectory(src/fzrpc)