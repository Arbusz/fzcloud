cmake_minimum_required(VERSION 3.5)

#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/test)

#include_directories(gtest)
#add_library(gtest SHARED gtest/gmock_main.cc gtest/gmock-gtest-all.cc)

#FIND_PACKAGE(Threads REQUIRED)
#target_link_libraries(gtest ${CMAKE_THREAD_LIBS_INIT})

# gtest

# enable_testing()
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

# end gtest

#link_directories(${PROJECT_SOURCE_DIR}/src/fzrpc/rpcop/lib)

#add_executable(servertest server.cc)

#add_executable(clienttest client.cc)

#target_link_libraries(servertest fzrpc)

#target_link_libraries(clienttest fzrpc)


set(SERVER_SOURCE_FILES
        ServerTest.cc
        )
set(CLIENT_SOURCE_FILES
        AsyncClient.cc
        )

add_executable(serverTest ${SERVER_SOURCE_FILES})
add_executable(asyncClientTest ${CLIENT_SOURCE_FILES})

target_link_libraries(asyncClientTest fzrpc)

target_link_libraries(serverTest fzrpc)
