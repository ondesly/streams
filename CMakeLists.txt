#
#  CMakeLists.txt
#  streams
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 07.11.2020.
#  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
#

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(streams
        VERSION 1.1
        LANGUAGES C CXX)

set(CMAKE_XCODE_ATTRIBUTE_EXCLUDED_ARCHS[sdk=iphonesimulator*] "arm64") # Fix for Xcode project

################
# Dependencies #
################

include(FetchContent)

#

FetchContent_Declare(
        miniz
        URL https://github.com/richgel999/miniz/releases/download/2.1.0/miniz-2.1.0.zip)

FetchContent_Declare(
        tiny-aes-c
        GIT_REPOSITORY https://github.com/kokke/tiny-AES-c.git
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

#

FetchContent_MakeAvailable(miniz tiny-aes-c)

#########
# Build #
#########

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

find_package(Miniz REQUIRED)
find_package(TinyAES REQUIRED)

#

add_subdirectory(src)

###########
# Testing #
###########

enable_testing()

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif ()