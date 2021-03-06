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
        streams/zstream.cpp)

target_link_libraries(streams PRIVATE miniz tiny_aes)

#

set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/../include)

set(PUBLIC_HEADERS
        ${INCLUDE_DIR}/streams/astream.h
        ${INCLUDE_DIR}/streams/bstream.h
        ${INCLUDE_DIR}/streams/zstream.h)

set_target_properties(streams PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS}")

target_include_directories(streams PUBLIC $<BUILD_INTERFACE:${INCLUDE_DIR}> $<INSTALL_INTERFACE:include>)

#

set_target_properties(streams PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)