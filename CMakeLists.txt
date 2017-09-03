cmake_minimum_required (VERSION 2.6)
project (human_traffic_detector)

#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR/lib})
set(GTEST_PATH "/media/chanaka/Chanaka2/software/googletest-master/googletest/")
set(LOG_PATH "/media/chanaka/Chanaka2/software/easyloggingpp_v9.95.0")
set(CONFIG_LIB_PATH "/media/chanaka/Chanaka2/software/tinyxml")
#set(OPENCV_PATH "usr/local/include/opencv2")

SET(CMAKE_CXX_FLAGS "-std=c++0x")
#SET(CMAKE_BUILD_TYPE Debug)

FIND_PACKAGE( OpenCV REQUIRED )
#FIND_PACKAGE( Poco REQUIRED )
find_library(POCO_FOUNDATION PocoFoundation)


add_definitions(-DELPP_NO_DEFAULT_LOG_FILE)
add_definitions(-DTIXML_USE_STL)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${GTEST_PATH}")
include_directories("${GTEST_PATH}/include")
include_directories("${LOG_PATH}")
include_directories("${CONFIG_LIB_PATH}")
#include_directories("${OPENCV_PATH}")

add_library(googletest ${GTEST_PATH}/src/gtest-all.cc ${GTEST_PATH}/src/gtest_main.cc)
add_library(logger ${LOG_PATH}/easylogging++.cc)
add_library(tinyxml ${CONFIG_LIB_PATH}/tinyxml.cpp  ${CONFIG_LIB_PATH}/tinystr.cpp ${CONFIG_LIB_PATH}/tinyxmlerror.cpp ${CONFIG_LIB_PATH}/tinyxmlparser.cpp)
#add_library(opencv2 ${OPENCV_PATH}/)


file(GLOB SOURCES "src/c_*.cpp")

ADD_SUBDIRECTORY(src)
#ADD_SUBDIRECTORY(test)

#enable_testing()
#add_test(test1   ${CMAKE_BINARY_DIR}/test1)
