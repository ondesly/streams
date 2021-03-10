#
#  CMakeLists.txt
#  streams
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 07.11.2020.
#  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
#

find_package(Miniz REQUIRED)
find_package(TinyAES REQUIRED)

add_library(streams STATIC
        streams/astream.cpp
        streams/bstream.cpp
        streams/zstream.cpp)

set(PUBLIC_HEADERS
        include/streams/astream.h
        include/streams/bstream.h
        include/streams/zstream.h)

set_target_properties(streams PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS}")

target_link_libraries(streams PRIVATE miniz tiny_aes)

target_include_directories(streams PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../include>
        $<INSTALL_INTERFACE:include>)

set_target_properties(streams PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)