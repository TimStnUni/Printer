cmake_minimum_required(VERSION 3.9)
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


#find doxygen
find_package(Doxygen
            REQUIRED dot)

doxygen_add_docs(doxygen_doc ALL
        ${CMAKE_CURRENT_SOURCE_DIR}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Docs/doxydocs/
        COMMENT "maybe this works")
#set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Docs/Doxyfile)
#set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

#configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
#message("doxygen build started")


#add_custom_target(doc_doxygen ALL
#    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
#    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#    COMMENT "Generating doxygen documentation"
#    COMMENT ${CMAKE_CURRENT_BINARY_DIR}
#    VERBATIM)

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