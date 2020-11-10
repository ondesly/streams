#
#  CMakeLists.txt
#  zstream
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 07.11.2020.
#  Copyright © 2020 Dmitrii Torkhov. All rights reserved.
#

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(zstream 
    VERSION 1.0
    LANGUAGES C CXX)

################
# Dependencies #
################

include(FetchContent)

set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_LIST_DIR}/extern)

#

FetchContent_Declare(
    miniz
    URL		https://github.com/richgel999/miniz/releases/download/2.1.0/miniz-2.1.0.zip)

#

FetchContent_MakeAvailable(miniz)

#########
# Build #
#########

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

find_package(Miniz REQUIRED)

#

add_subdirectory(src)