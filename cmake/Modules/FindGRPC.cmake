# - Try to find LibGRPC headers and libraries.
#
# Usage of this module as follows:
#
#     find_package(GRPC)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
#  GPRC_ROOT_DIR  Set this variable to the root installation of
#                    GRPC if the module has problems finding
#                    the proper installation path.
#
# Variables defined by this module:
#
#  GRPC_FOUND              System has GRPC libs/headers
#  GRPC_LIBRARIES          The GRPC libraries
#  GRPC_INCLUDE_DIR        The location of GPRC headers

find_path(GRPC_ROOT_DIR
        NAMES include/grpc++/grpc++.h
)

find_path(GRPC_C_ROOT_DIR
        NAMES include/grpc/grpc.h
        )

find_library(GRPC_LIBRARIES
        NAMES libgrpc++.so
        HINTS ${GRPC_ROOT_DIR}/lib
)

find_library(GRPC_C_LIBRARIES
        NAMES libgrpc.so
        HINTS ${GRPC_C_ROOT_DIR}/lib
)

find_path(GRPC_INCLUDE_DIR
        NAMES grpc++/grpc++.h
        HINTS ${GRPC_ROOT_DIR}/include
)

find_path(GRPC_C_INCLUDE_DIR
        NAMES grpc/grpc.h
        HINTS ${GRPC_C_ROOT_DIR}/include
        )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GRPC DEFAULT_MSG
        GRPC_LIBRARIES
        GRPC_C_LIBRARIES
        GRPC_INCLUDE_DIR
        GRPC_C_INCLUDE_DIR
)

mark_as_advanced(
        GRPC_ROOT_DIR
        GRPC_LIBRARIES
        GRPC_C_LIBRARIES
        GRPC_INCLUDE_DIR
        GRPC_C_INCLUDE_DIR
)

if (GRPC_FOUND)
    message(STATUS "GRPC_ROOT_DIR: ${GRPC_ROOT_DIR}")
    message(STATUS "GRPC_C_ROOT_DIR: ${GRPC_C_ROOT_DIR}")
    message(STATUS "GRPC_INCLUDE_DIR: ${GRPC_INCLUDE_DIR}")
    message(STATUS "GRPC_LIBRARIES: ${GRPC_LIBRARIES}")
    message(STATUS "GRPC_C_INCLUDE_DIR: ${GRPC_C_INCLUDE_DIR}")
    message(STATUS "GPRC_C_LIBRARIES: ${GRPC_C_LIBRARIES}")
endif ()