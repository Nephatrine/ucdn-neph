cmake_minimum_required(VERSION 3.2)
if(POLICY CMP0063)
	cmake_policy(SET CMP0063 NEW)
endif()

# ------------------------------
# Project Header
#

project(ucdn
	VERSION 1.0.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/config/CMake")

set(UCDN_SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
set(UCDN_TAG_NAME "-neph")

# ------------------------------
# Source Code
#

list(APPEND UCDN_SOURCE
	"${CMAKE_CURRENT_SOURCE_DIR}/ucdn.c")

list(APPEND UCDN_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/include/ucdn.h")

# ------------------------------
# Configuration
#

if(NOT MSVC)
	add_definitions(-O2 -Wall -Werror -pedantic -std=c89)
endif()

# ------------------------------
# Define Targets
#

include(WhatEver-Targets)

add_library(ucdn ${UCDN_SOURCE} ${UCDN_HEADERS})

we_target_add_paths(ucdn
	PUBLIC include
	INSTALL_TAG ${UCDN_TAG_NAME})

if(BUILD_SHARED_LIBS)
	set_target_properties(ucdn PROPERTIES VERSION ${PROJECT_VERSION})
	set_target_properties(ucdn PROPERTIES SOVERSION ${UCDN_SOVERSION})
endif()

add_executable(ucdn-test ucdn-test.c)
target_link_libraries(ucdn-test ucdn)

# ------------------------------
# Install Targets
#

install(TARGETS ucdn
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)

