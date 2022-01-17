cmake_minimum_required(VERSION 3.5)
project(fzrpc)

set(CMAKE_CXX_STANDARD 11)

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})

find_package(gRPC CONFIG REQUIRED)
include_directories(${GRPC_INCLUDE_DIRS})
include_directories(${GRPC_C_INCLUDE_DIRS})

#set source files
set(SOURCE_FILES
        ClientCallMethod.cc
        RpcClient.cc
        protos/fzrpc.grpc.pb.cc
        protos/fzrpc.pb.cc
        protos/fzrpc.grpc.pb.h
        protos/fzrpc.pb.h
        )

#create a lib for fzrpc
add_library(fzrpc SHARED ${SOURCE_FILES})

#set rpc library path

target_link_libraries(fzrpc ${gRPC_LIBRARIES}  ${gRPC_C_LIBRARIES} ${PROTOBUF_LIBRARIES})

#add subdir
add_subdirectory(test)
