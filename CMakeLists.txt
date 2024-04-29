cmake_minimum_required(VERSION 3.6)
project(ProjSoftEng)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)
# Remove the "-O2" flag if you have problems with the debugger.
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall  -O2")
set(CMAKE_EXE_LINKER_FLAGS -pthread)
# I'm not sure if this is allowed
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

# Set include dir
include_directories(./gtest/include)
include_directories(./gtest/include/gtest/internal)
include_directories(./Libs)



#Doxygen stuff

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN /home/tim/UniCS/SoftEng/ProjSoftEng/Docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

# Set Library dir
link_directories(./gtest/lib)

# Set source files for RELEASE target
# Only add cpp files, no h files!
# Only add files with functionality here, no test files!
set(RELEASE_SOURCE_FILES
        main.cpp
        ./Libs/tinystr.cpp
        ./Libs/tinyxml.cpp
        ./Libs/tinyxmlparser.cpp
        ./Libs/tinyxmlerror.cpp
        Printer.cpp
        Printer.h
        Device.cpp
        Device.h
        Job.cpp
        Job.h
        XMLParser.cpp
        XMLParser.h
        PrinterSystem.cpp
        PrinterSystem.h
        InfoPrinter.cpp
        InfoPrinter.h
        Scheduler.cpp
        Scheduler.h

)

# Set source files for DEBUG target
# Only add cpp files, no h files!
set(DEBUG_SOURCE_FILES
        tests.cpp
        ./Libs/tinystr.cpp
        ./Libs/tinyxml.cpp
        ./Libs/tinyxmlparser.cpp
        ./Libs/tinyxmlerror.cpp
        Printer.cpp
        TicTacToeUtils.cpp
        Device.cpp
        Job.cpp
        XMLParser.cpp
        Alletesten/alloutputtests.cpp
        Alletesten/alldomaintests.cpp
        PrinterSystem.cpp
        PrinterSystem.h
        InfoPrinter.cpp
        InfoPrinter.h
        Scheduler.cpp
        Scheduler.h
)

        # Create RELEASE target
add_executable(release_target ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(debug_target ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(debug_target gtest)