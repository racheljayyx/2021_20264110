
# calc_cmake/CMakeLists.txt

cmake_minimum_required( VERSION 2.8 )
project( calc )

include(CTest)

# This project contains a library
add_library( maths adder.cpp )
# Note: you could force CMake to always build a static/shared library:
#add_library( maths STATIC adder.cpp )
#add_library( maths SHARED adder.cpp )

if( NOT BUILD_SHARED_LIBS )
    # if static libs are compiled we need
    # to somehow communicate that to the
    # source code. The definition will be
    # used to determine how MATHSLIB_API
        # is defined in adder.h
    add_definitions( -Dmaths_STATIC )
endif()

# It also contains an executable
add_executable( calc calc.cpp )



# The executable uses the library
target_link_libraries( calc maths )

add_executable(test1 test1.cpp)
target_link_libraries(test1 maths) #"maths" is the name of your library from Worksheet 4
add_test(test1 test1)

# /calc_cmake/CMakeLists.txt
