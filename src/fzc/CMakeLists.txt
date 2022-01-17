cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)

set(SLAVE_SRC
        util.cc
        SyncFile.cc
        DockerHandler.cc
        Slave.cc
        )

set(MASTER_SRC
        util.cc
        Master.cc)

add_executable(master ${MASTER_SRC})
add_executable(slave ${SLAVE_SRC})

target_link_libraries(slave curlop fzrpc)
target_link_libraries(master curlop fzrpc)

add_subdirectory(test)