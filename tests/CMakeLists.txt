#
#  CMakeLists.txt
#  streams
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 16.01.2021.
#  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
#

project(tests)

#

function(add name)
    add_executable(${name} ${name}.cpp)

    target_link_libraries(${name} streams)

    set_target_properties(${name} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

    add_test(NAME ${name} COMMAND ${name})
endfunction()

#

add("test_b")

if (STREAMS_AES)
    add("test_a")
endif ()

if (STREAMS_ZLIB)
    add("test_zl")
endif ()

if (STREAMS_ZSTD)
    add("test_zs")
endif ()

if (STREAMS_AES AND STREAMS_ZLIB)
    add("test_zl_a")
endif ()

if (STREAMS_ZLIB AND STREAMS_ZSTD)
    FetchContent_Declare(
            when
            GIT_REPOSITORY https://github.com/ondesly/when.git
            GIT_TAG v1.1.0
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE)

    FetchContent_MakeAvailable(when)

    add("test_z_comparison")

    target_link_libraries(test_z_comparison when)
endif ()