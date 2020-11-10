#
#  CMakeLists.txt
#  zstream
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 07.11.2020.
#  Copyright © 2020 Dmitrii Torkhov. All rights reserved.
#

add_library(zstream STATIC
    zstream/zstream.cpp)

add_library(rkhv::zstream ALIAS zstream)

set_target_properties(zstream PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

target_include_directories(zstream PRIVATE
    ../include/zstream)

target_link_libraries(zstream PRIVATE richgel999::miniz)

#

set(PUBLIC_HEADERS ../include/zstream/zstream.h)

install(TARGETS zstream miniz
        EXPORT zstream-config
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include)

install(FILES ${PUBLIC_HEADERS} DESTINATION include/zstream)

install(EXPORT zstream-config DESTINATION lib/cmake/zstream)