#
#  CMakeLists.txt
#  streams
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 07.11.2020.
#  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
#

find_package(Miniz REQUIRED)
find_package(TinyAES REQUIRED)

#

add_library(streams STATIC
        streams/astream.cpp
        streams/bstream.cpp
        streams/zlstream.cpp
        streams/zsstream.cpp)

target_link_libraries(streams PRIVATE miniz tiny_aes libzstd_static)

#

set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/../include)

set(PUBLIC_HEADERS
        ${INCLUDE_DIR}/streams/astream.h
        ${INCLUDE_DIR}/streams/bstream.h
        ${INCLUDE_DIR}/streams/zlstream.h
        ${INCLUDE_DIR}/streams/zsstream.h)

set_target_properties(streams PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS}")

target_include_directories(streams PUBLIC
        $<BUILD_INTERFACE:${zstd_SOURCE_DIR}/lib>
        $<BUILD_INTERFACE:${INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>)

#

set_target_properties(streams PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)