#Created with help from https://ecrafter.wordpress.com/2012/06/16/cmake-tutorial-part-5/
#username: ecrafter

# Try to find Lily library if it exists
# Once done this will define
#  LILY_FOUND - if system found Lily library
#  LILY_INCLUDE_DIRS - The Lily include directories
#  LILY_LIBRARIES - The libraries needed to use Lily
#  LILY_DEFINITIONS - Compiler switches required for using Lily

if (NOT $ENV{WORKSPACE_ROOT} OR $ENV{WORKSPACE_ROOT} STREQUAL " ")
    set(LILY_ROOT_DIR /usr/local/include)
else()
    set(LILY_ROOT_DIR $ENV{WORKSPACE_ROOT}/lily)
endif()

# set(LILY_ROOT_DIR $ENV{WORKSPACE_ROOT}/lily)
# set(LILY_ROOT_DIR /usr/local/include)

MESSAGE(STATUS "LILY_ROOT_DIR: " ${LILY_ROOT_DIR})

find_path(LILY_INCLUDE_DIR
    NAMES lily/lily.h
    PATHS ${LILY_ROOT_DIR}
    DOC "The lily include directory"
)

find_library(LILY_LIBRARY
    NAMES liblily.so
    PATHS /lib64 /lib
    DOC "The lily library"
)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LOGGING_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LILY DEFAULT_MSG LILY_INCLUDE_DIR LILY_LIBRARY)

if (PART4_FOUND)
    set(LILY_LIBRARIES ${LILY_LIBRARY} )
    set(LILY_INCLUDE_DIRS ${LILY_INCLUDE_DIR} )
    set(LILY_DEFINITIONS)
endif()

# Tell cmake GUIs to ignore the "local" variables.
mark_as_advanced(PART4_ROOT_DIR PART4_INCLUDE_DIR PART4_LIBRARY)

