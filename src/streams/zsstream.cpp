//
//  zsstream.cpp
//  streams
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 29.08.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <zstd.h>

#include "streams/zsstream.h"

// -- ozsstream --

oo::ozsstream::ozsstream(int compression_level) : m_compression_level(compression_level) {

}

void oo::ozsstream::operator>>(std::vector<uint8_t> &value) {
    const auto buf_len = ZSTD_compressBound(m_buffer.size());
    value.resize(buf_len);

    const auto cmp_len = ZSTD_compress(value.data(), buf_len,
                                       m_buffer.data(), m_buffer.size(), m_compression_level);
    if (ZSTD_isError(cmp_len)) {
        value.resize(0);
        return;
    }

    value.resize(cmp_len);
}

// -- izsstream --

void oo::izsstream::operator<<(const std::vector<uint8_t> &value) {
    const auto buf_len = ZSTD_getFrameContentSize(value.data(), value.size());

    if (ZSTD_isError(buf_len)) {
        return;
    }

    m_buffer.resize(buf_len);

    const auto dcm_len = ZSTD_decompress(m_buffer.data(), m_buffer.size(),
                                         value.data(), value.size());
    if (ZSTD_isError(dcm_len)) {
        m_buffer.resize(0);
        return;
    }

    m_buffer.resize(dcm_len);
}