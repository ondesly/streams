#
#  CMakeLists.txt
#  streams
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 16.01.2021.
#  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
#

project(tests)

# TestB

add_executable(test_b test_b.cpp)

set_target_properties(test_b PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)

target_link_libraries(test_b oo::streams)

add_test(NAME TestB COMMAND test_b)

# TestA

add_executable(test_a test_a.cpp)

set_target_properties(test_a PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)

target_link_libraries(test_a oo::streams)

add_test(NAME TestA COMMAND test_a)