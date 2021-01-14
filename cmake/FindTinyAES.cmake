#
#  FindTinyAES.cmake
#  zstream
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 13.01.2021.
#  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
#

add_library(tiny_aes STATIC
	${tiny-aes-c_SOURCE_DIR}/aes.c)

target_include_directories(tiny_aes PUBLIC
	$<BUILD_INTERFACE:${tiny-aes-c_SOURCE_DIR}>)