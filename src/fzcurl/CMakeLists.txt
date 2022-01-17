cmake_minimum_required( VERSION 3.5 )
project( libcurlop )

find_package(CURL REQUIRED)
if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
else(CURL_FOUND)
    message(FATAL_ERROR "curl not found!")
endif(CURL_FOUND)

#set files should be contain
set(SOURCE_FILES
        CurlBaseOp.cc
        CurlUp.cc
        CurlDown.cc
        CurlList.cc
        CurlDel.cc
        )

#add shared libraries
add_library( curlop SHARED ${SOURCE_FILES})

target_link_libraries(curlop ${CURL_LIBRARY})

add_subdirectory(test)