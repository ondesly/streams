#
#  FindMiniz.cmake
#  zstream
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 07.11.2020.
#  Copyright © 2020 Dmitrii Torkhov. All rights reserved.
#

add_library(miniz STATIC
	${miniz_SOURCE_DIR}/miniz.c)

add_library(richgel999::miniz ALIAS miniz)

target_include_directories(miniz PUBLIC
	$<BUILD_INTERFACE:${miniz_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>)