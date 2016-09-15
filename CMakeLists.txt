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

list(APPEND UCDN_TEST_SOURCE
	"${CMAKE_CURRENT_SOURCE_DIR}/ucdn-test.c")

# ------------------------------
# Configuration
#

include(WhatEver-Config-C)

we_config_require_standard(C 99)

if(NOT MSVC)
	option(BUILD_ALLOW_SHLIB_UNDEFINED "Enable if you have an old janky binutils." OFF)

	we_config_has_cflags(UCDN_CFLAGS -Wall -Werror -pedantic -march=native)
	we_config_has_ldflags(UCDN_LDFLAGS -Wl,--as-needed -Wl,--no-undefined)

	if(NOT BUILD_ALLOW_SHLIB_UNDEFINED)
		we_config_has_ldflags(UCDN_LDFLAGS -Wl,--no-allow-shlib-undefined)
	endif()

	if(WIN32)
		we_config_has_ldflags(UCDN_LDFLAGS -Wl,--nxcompat -Wl,--dynamicbase -Wl,--high-entropy-va)
	endif()
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

add_executable(ucdn-test ${UCDN_TEST_SOURCE})
target_link_libraries(ucdn-test ucdn)

we_target_add_cflags(ucdn ucdn-test
	PRIVATE ${UCDN_CFLAGS})
we_target_add_ldflags(ucdn ucdn-test
	PRIVATE ${UCDN_LDFLAGS})

# ------------------------------
# Install Targets
#

install(TARGETS ucdn
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)

