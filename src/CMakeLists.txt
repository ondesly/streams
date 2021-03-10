#
#  CMakeLists.txt
#  streams
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 07.11.2020.
#  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
#

add_library(streams STATIC
        streams/astream.cpp
        streams/bstream.cpp
        streams/zstream.cpp)


set_target_properties(streams PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)

target_include_directories(streams PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../include>
        $<INSTALL_INTERFACE:include>)

target_link_libraries(streams PRIVATE miniz tiny_aes)

#

set(PUBLIC_HEADERS
        ../include/streams/astream.h
        ../include/streams/bstream.h
        ../include/streams/zstream.h)

install(TARGETS streams miniz tiny_aes
        EXPORT streams-config
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include)

install(FILES ${PUBLIC_HEADERS} DESTINATION include/streams)

install(EXPORT streams-config DESTINATION lib/cmake/streams)