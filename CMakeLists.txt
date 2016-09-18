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

set(UCDN_SOVERSION "${PROJECT_VERSION_MAJOR}")
set(UCDN_TAG_NAME "_neph")

# ------------------------------
# Source Code
#

list(APPEND UCDN_SOURCE
	"${CMAKE_CURRENT_SOURCE_DIR}/src/ucdn.c")

list(APPEND UCDN_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/include/ucdn.h")

list(APPEND UCDN_TEST_SOURCE
	"${CMAKE_CURRENT_SOURCE_DIR}/src/ucdn-test.c")

# ------------------------------
# Configuration
#

include(WhatEver-Config-C)

we_config_require_standard(C 99)

if(NOT MSVC)
	option(BUILD_ALLOW_SHLIB_UNDEFINED "enable if your system spits out linker errors" OFF)

	we_config_has_cflags(UCDN_CFLAGS -Wall -Werror -pedantic -march=native)
	we_config_has_ldflags(UCDN_LDFLAGS -Wl,--as-needed -Wl,--no-undefined)

	if(NOT BUILD_ALLOW_SHLIB_UNDEFINED)
		we_config_has_ldflags(UCDN_LDFLAGS -Wl,--no-allow-shlib-undefined)
	endif()

	if(WIN32)
		we_config_has_ldflags(UCDN_LDFLAGS -Wl,--nxcompat -Wl,--dynamicbase -Wl,--high-entropy-va)
	endif()
endif()

#
# Generated Data
#

include(WhatEver-Generate)
find_package(PythonInterp 2.7 REQUIRED)

set(UCDN_UNICODE_VERSION "9.0.0" CACHE STRING "Unicode Data Version")

we_download_unicode(UCDN_UNICODE_FILES ${UCDN_UNICODE_VERSION}
	BidiBrackets.txt
	BidiMirroring.txt
	CaseFolding.txt
	CompositionExclusions.txt
	DerivedCoreProperties.txt
	DerivedNormalizationProps.txt
	EastAsianWidth.txt
	LineBreak.txt
	NameAliases.txt
	NamedSequences.txt
	Scripts.txt
	SpecialCasing.txt
	UnicodeData.txt
	Unihan.zip)

we_generate_from_script(UCDN_GENERATED makeunicodedata.py
	include/internal/unicodedata_db.h ${WHATEVER_CACHE_DIR} ${UCDN_UNICODE_VERSION}
	DEPENDS ${UCDN_UNICODE_FILES})

# ------------------------------
# Define Targets
#

include(WhatEver-Targets)

option(BUILD_UCDN_SHARED "Build UCDN Shared Library" ON)
option(BUILD_UCDN_STATIC "Build UCDN Static Library" ON)
	
we_target_build_library(UCDN_TARGET ${PROJECT_NAME} ${UCDN_SOVERSION}
	${UCDN_SOURCE} ${UCDN_HEADERS} ${UCDN_GENERATED}
	EXPORT include
	TAG ${UCDN_TAG_NAME})
we_target_build_executable(UCDN_TARGET "${PROJECT_NAME}-test"
	${UCDN_TEST_SOURCE}
	LIBS ${UCDN_TARGET_SHARED})
we_target_build_executable(UCDN_TARGET "${PROJECT_NAME}-test-static"
	${UCDN_TEST_SOURCE}
	LIBS ${UCDN_TARGET_STATIC})

we_target_add_cflags(${UCDN_TARGET}
	PRIVATE ${UCDN_CFLAGS})
we_target_add_ldflags(${UCDN_TARGET}
	PRIVATE ${UCDN_LDFLAGS})

we_target_export(${UCDN_TAG_NAME})

# ------------------------------
# Package Targets
#

include(WhatEver-Package)
we_package(${UCDN_TAG_NAME}
	CATEGORY devel DESC "Unicode Database & Normalization"
	VENDOR Nephatrine CONTACT nephatrine@gmail.com
	HOME https://github.com/Nephatrine/ucdn-neph)

