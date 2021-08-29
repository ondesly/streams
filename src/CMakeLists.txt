#
#  CMakeLists.txt
#  streams
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 07.11.2020.
#  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
#

if (STREAMS_AES)
    find_package(TinyAES REQUIRED)
endif ()

if (STREAMS_ZLIB)
    find_package(Miniz REQUIRED)
endif ()


#

set(SRC
        streams/bstream.cpp)

if (STREAMS_AES)
    list(APPEND SRC
            streams/astream.cpp)
endif ()

if (STREAMS_ZLIB)
    list(APPEND SRC
            streams/zlstream.cpp)
endif ()

if (STREAMS_ZSTD)
    list(APPEND SRC
            streams/zsstream.cpp)
endif ()

add_library(streams STATIC ${SRC})

#

if (STREAMS_AES)
    target_link_libraries(streams PRIVATE tiny_aes)
endif ()

if (STREAMS_ZLIB)
    target_link_libraries(streams PRIVATE miniz)
endif ()

if (STREAMS_ZSTD)
    target_link_libraries(streams PRIVATE libzstd_static)
endif ()

#

set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/../include)

set(PUBLIC_HEADERS
        ${INCLUDE_DIR}/streams/bstream.h)

if (STREAMS_AES)
    list(APPEND PUBLIC_HEADERS
            ${INCLUDE_DIR}/streams/astream.h)
endif ()

if (STREAMS_ZLIB)
    list(APPEND PUBLIC_HEADERS
            ${INCLUDE_DIR}/streams/zlstream.h)
endif ()

if (STREAMS_ZSTD)
    list(APPEND PUBLIC_HEADERS
            ${INCLUDE_DIR}/streams/zsstream.h)
endif ()

set_target_properties(streams PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS}")

target_include_directories(streams PUBLIC
        $<BUILD_INTERFACE:${INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>)

if (STREAMS_ZSTD)
    target_include_directories(streams PUBLIC
            $<BUILD_INTERFACE:${zstd_SOURCE_DIR}/lib>)
endif ()

#

set_target_properties(streams PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)