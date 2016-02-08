# <Copyright Holder>. Copyright (C) <Copyright Year(s)>. <License>.

#
# Project Properties
#
CMAKE_MINIMUM_REQUIRED (VERSION 2.6.2)
PROJECT (npcv)
SET (APPLICATION_NAME "NPCV")
SET (APPLICATION_CODENAME "${PROJECT_NAME}")
SET (APPLICATION_COPYRIGHT_YEARS "2009")
SET (APPLICATION_VERSION_MAJOR 1)
SET (APPLICATION_VERSION_MINOR 0)
SET (APPLICATION_VERSION_PATCH 0)
SET (APPLICATION_VERSION_TYPE SNAPSHOT)
SET (APPLICATION_VERSION_STRING "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}-${APPLICATION_VERSION_TYPE}")
SET (APPLICATION_VENDOR_ID "com.yourcompany")
SET (APPLICATION_VENDOR_NAME "Your Company")
SET (APPLICATION_VENDOR_URL "yourcompany.com")
SET (APPLICATION_ID "${APPLICATION_VENDOR_ID}.${PROJECT_NAME}")


#
# Debugging Options
#
SET (CMAKE_VERBOSE_MAKEFILE 0) # Use 1 for debugging, 0 for release

#aaaa
# Project Output Paths
#
SET (MAINFOLDER ${PROJECT_SOURCE_DIR})
SET (LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")
SET (EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")
SET (NPCV_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/npcv/")
SET (NPCV_SRC_DIR "${CMAKE_SOURCE_DIR}/src/")


########
# 
# COMPILER
#
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


#############################################################
#
#
#		OPTIONS
#
###################################

###########################
#
# REQUIRED
#
#############
#include(tools/share/cmake/NPMacros.cmake)
#
# Add extern library First 
#
### Macro usage ##### REQUIRED_THIRD ###
#
# Add extern project and make variables:
#	THIRD_<Name>_SRC
#	THIRD_<Name>_DEV
#	THIRD_<Name>_NAME
#
#######################################
#REQUIRED_THIRD(NCPPCORE "Ncpp core library" NCPPCORE)

# Samples project
option(TESTAPP "Make npcv test" YES)

# npcv GUI
option(NpcvGUI "Make npcvGUI project" YES)
#paths
set(SFML_DIR "${CMAKE_SOURCE_DIR}/thirdparty/SFML-2.3.2/Win64" CACHE PATH "If downloading is disable this will be used. The path to the GooglTest cloned repository.")
set(SFGUI_DIR "${CMAKE_SOURCE_DIR}/thirdparty/SFGUI-0.3.0/" CACHE PATH "If downloading is disable this will be used. The path to the GooglTest cloned repository.")

# Google Tests
option(GTEST "Add GTest to project" NO)
option(GTEST_DOWNLOAD_GTEST_AND_GMOCK "Download GTest." NO)
#paths
set(GTEST_DIR "${CMAKE_SOURCE_DIR}/test/gtest/gtest-1.7.0" CACHE PATH "If downloading is disable this will be used. The path to the GooglTest cloned repository.")
set(GTEST_GMOCK_DIR "${CMAKE_SOURCE_DIR}/test/gtest/gmock-1.7.0" CACHE PATH "If downloading is disable this will be used. The path to the GooglMock cloned repository.")
# This is understanding now
#option(BUILD_GTEST "Builds the googletest subproject" OFF)
#option(BUILD_GMOCK "Builds the googlemock subproject" ON) #Note that googlemock target already builds googletest

############################
#
# OPTIONAL
#
#############

###################################
#
#		END OPTIONS
#
#############################################################

##########################
#
# Project Search Paths
#
LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}")
LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}/tools")
LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}/thirdparty")
SET (CMAKE_MODULE_PATH "${MAINFOLDER}/tools/share/cmake")

# Include
#INCLUDE_DIRECTORIES("${MAINFOLDER}/include")

#
# Locate Project Prerequisites 
#
#SET (Boost_ADDITIONAL_VERSIONS "1.39" "1.39.0" "1.40" "1.40.0" "1.41" "1.41.0" "1.42" "1.42.0" "1.43" "1.43.0" "1.44" "1.44.0" "1.45" "1.45.0" "1.46" "1.46.0" "1.47" "1.47.0" "1.48" "1.48.0" "1.49" "1.49.0" "1.50" "1.50.0")
#FIND_PACKAGE (Boost 1.37 COMPONENTS "date_time" "filesystem" "graph" "iostreams" "program_options" "regex" "serialization" "signals" "system" "thread" "wserialization" REQUIRED)
#INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
#LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
#FIND_PACKAGE (Qt4 REQUIRED)
#INCLUDE(UseQt4)
#FIND_PACKAGE (Log4Cxx REQUIRED)
#INCLUDE_DIRECTORIES(${Log4Cxx_INCLUDE_DIRS})
#LINK_DIRECTORIES(${Log4Cxx_LIBRARY_DIRS})
#FIND_PACKAGE (UnitTestPlusPlus REQUIRED)
#INCLUDE_DIRECTORIES(${UnitTestPlusPlus_INCLUDE_DIRS})
#LINK_DIRECTORIES(${UnitTestPlusPlus_LIBRARY_DIRS})


#
# Configure Files
#
FILE (GLOB_RECURSE CONFIGINPUTS1 include/*.in.h.cmake)
FILE (GLOB_RECURSE CONFIGINPUTS2 include/*.h.in.cmake)
FILE (GLOB_RECURSE CONFIGINPUTS3 src/*.in.h.cmake)
FILE (GLOB_RECURSE CONFIGINPUTS4 src/*.h.in.cmake)
#FILE (GLOB_RECURSE CONFIGINPUTS5 test/*.in.h.cmake)
#FILE (GLOB_RECURSE CONFIGINPUTS6 test/*.h.in.cmake)
LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS1}")
LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS2}")
LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS3}")
LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS4}")
#LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS5}")
#LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS6}")
FOREACH (CONFIGINPUT ${CONFIGINPUTS})
    STRING (REPLACE ".in.h.cmake" ".h" CONFIGOUTPUT1 "${CONFIGINPUT}")
    STRING (REPLACE ".h.in.cmake" ".h" CONFIGOUTPUT2 "${CONFIGOUTPUT1}")
    CONFIGURE_FILE ("${CONFIGINPUT}" "${CONFIGOUTPUT2}")
ENDFOREACH (CONFIGINPUT ${CONFIGINPUTS})

#
# Add Build Targets
#
ADD_SUBDIRECTORY(src)
#ADD_SUBDIRECTORY(thirdparty)

# Samples project target
if(TESTAPP)
	add_subdirectory(test)
endif()

# NpcvGUI
if(NpcvGUI)
	add_subdirectory(src/npcvgui)
endif()

# GTest project targets
if(GTEST)
	#add_subdirectory(test)
endif()

#
# Add Install Targets
#
#IF (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")
#    INSTALL(DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}" DESTINATION "include")
#ENDIF (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")

#
# Add Documentation Targets
#
#INCLUDE (DocumentationTargets)
