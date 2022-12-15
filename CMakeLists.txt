#
#  CMakeLists.txt
#  streams
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 07.11.2020.
#  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
#

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(streams
        VERSION 1.2.1
        LANGUAGES C CXX)

###########
# Options #
###########

option(STREAMS_AES "Enable AES stream" ON)
option(STREAMS_ZLIB "Enable zlib stream" ON)
option(STREAMS_ZSTD "Enable Zstandard stream" ON)

################
# Dependencies #
################

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

#

include(FetchContent)

#

if (STREAMS_AES)
    FetchContent_Declare(
            tiny-aes-c
            GIT_REPOSITORY https://github.com/kokke/tiny-AES-c.git
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE)

    FetchContent_MakeAvailable(tiny-aes-c)
endif ()

#

if (STREAMS_ZLIB)
    FetchContent_Declare(
            miniz
            URL https://github.com/richgel999/miniz/releases/download/2.1.0/miniz-2.1.0.zip)

    FetchContent_MakeAvailable(miniz)
endif ()

#

if (STREAMS_ZSTD)
    FetchContent_Declare(
            zstd
            GIT_REPOSITORY https://github.com/facebook/zstd.git
            GIT_TAG v1.5.0
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE)

    option(ZSTD_MULTITHREAD_SUPPORT "MULTITHREADING SUPPORT" OFF)
    option(ZSTD_BUILD_PROGRAMS "BUILD PROGRAMS" OFF)
    option(ZSTD_BUILD_TESTS "BUILD TESTS" OFF)
    option(ZSTD_BUILD_SHARED "BUILD SHARED LIBRARIES" OFF)

    FetchContent_GetProperties(zstd)
    if (NOT zstd_POPULATED)
        FetchContent_Populate(zstd)
        add_subdirectory(${zstd_SOURCE_DIR}/build/cmake ${zstd_BINARY_DIR})
    endif ()
endif ()

#########
# Build #
#########

add_subdirectory(src)

###########
# Install #
###########

include(GNUInstallDirs)

#

set(INSTALL_DEPENDENCIES)

if (STREAMS_AES)
    list(APPEND INSTALL_DEPENDENCIES
            tiny_aes)
endif ()

if (STREAMS_ZLIB)
    list(APPEND INSTALL_DEPENDENCIES
            miniz)
endif ()

if (STREAMS_ZSTD)
    list(APPEND INSTALL_DEPENDENCIES
            libzstd_static)
endif ()

install(TARGETS ${PROJECT_NAME} ${INSTALL_DEPENDENCIES}
        EXPORT ${PROJECT_NAME}-config
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}${INSTALL_SUFFIX}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}${INSTALL_SUFFIX}/${PROJECT_NAME})

install(EXPORT ${PROJECT_NAME}-config DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

###########
# Testing #
###########

enable_testing()

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif ()