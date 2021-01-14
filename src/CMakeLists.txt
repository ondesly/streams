#
#  CMakeLists.txt
#  zstream
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 07.11.2020.
#  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
#

add_library(zstream STATIC
        zstream/astream.cpp
        zstream/bstream.cpp
        zstream/zstream.cpp)

add_library(oo::zstream ALIAS zstream)

set_target_properties(zstream PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)

target_include_directories(zstream PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../include>
        $<INSTALL_INTERFACE:include>)

target_link_libraries(zstream PRIVATE miniz tiny_aes)

#

set(PUBLIC_HEADERS ../include/zstream/zstream.h)

install(TARGETS zstream miniz tiny_aes
        EXPORT zstream-config
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include)

install(FILES ${PUBLIC_HEADERS} DESTINATION include/zstream)

install(EXPORT zstream-config DESTINATION lib/cmake/zstream)