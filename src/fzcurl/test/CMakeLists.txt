cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)

add_executable(downloadTest downloadtest.cc)

target_link_libraries(downloadTest curlop)