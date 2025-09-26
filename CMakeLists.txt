cmake_minimum_required (VERSION 3.10)
project ("C_Utils")

file ( GLOB SOURCES "*.c" "*.h" )
add_library ( C_Utils ${SOURCES} )
include_directories(${CMAKE_CURRENT_LIST_DIR})
