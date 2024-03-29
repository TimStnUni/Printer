cmake_minimum_required(VERSION 3.6)
project(ProjSoftEng)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 11)
# Remove the "-O2" flag if you have problems with the debugger.
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall  -O2")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(./gtest/include)
include_directories(./gtest/include/gtest/internal)
include_directories(./Libs)

# Set Library dir
link_directories(./gtest/lib)

# Set source files for RELEASE target
# Only add cpp files, no h files!
# Only add files with functionality here, no test files!
set(RELEASE_SOURCE_FILES main.cpp
        ./Libs/tinystr.cpp
        ./Libs/tinyxml.cpp
        ./Libs/tinyxmlparser.cpp
        ./Libs/tinyxmlerror.cpp
        Printer.cpp
        Printer.h

)

# Set source files for DEBUG target
# Only add cpp files, no h files!
set(DEBUG_SOURCE_FILES tests.cpp
        ./Libs/tinystr.cpp
        ./Libs/tinyxml.cpp
        ./Libs/tinyxmlparser.cpp
        ./Libs/tinyxmlerror.cpp
        Printer.cpp
        Printer.h

)

        # Create RELEASE target
add_executable(release_target ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(debug_target ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(debug_target gtest)