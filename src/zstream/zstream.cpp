//
//  zstream.cpp
//  zstream
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 30.10.2020.
//  Copyright © 2020 Dmitrii Torkhov. All rights reserved.
//

#define MINIZ_NO_STDIO
#define MINIZ_NO_TIME
#define MINIZ_NO_ARCHIVE_APIS
#define MINIZ_NO_ARCHIVE_WRITING_APIS

#include "miniz.h"

#include "zstream.h"

// -- ozstream --

size_t rkhv::ozstream::get_size() const {

    return m_buffer.size();
}

std::vector<unsigned char> rkhv::ozstream::get_compressed() const {
    auto cmp_len = compressBound(m_buffer.size());
    std::vector<unsigned char> cmp_buf(cmp_len);

    if (compress(cmp_buf.data(), &cmp_len, m_buffer.data(), m_buffer.size()) != Z_OK) {
        return {};
    }

    cmp_buf.resize(cmp_len);
    return cmp_buf;
}

void rkhv::ozstream::append(unsigned char byte) {
    m_buffer.push_back(byte);
}

// -- izstream --

namespace {

    const mz_uint32 c_default_buf_len = 1024;

}

rkhv::izstream::izstream(const std::vector<unsigned char> &compressed) {
    decompress(compressed.data(), uint32_t(compressed.size()));
}

rkhv::izstream::izstream(const std::string &compressed) {
    decompress(reinterpret_cast<const unsigned char *>(compressed.c_str()), uint32_t(compressed.length()));
}

void rkhv::izstream::decompress(const unsigned char *next_in, unsigned int avail_in) {
    mz_stream stream;
    memset(&stream, 0, sizeof(stream));

    stream.next_in = next_in;
    stream.avail_in = avail_in;

    if (mz_inflateInit(&stream) != MZ_OK) {
        return;
    }

    const mz_uint32 buf_len = c_default_buf_len;
    unsigned char buf[buf_len];

    int status;
    do {
        stream.next_out = buf;
        stream.avail_out = buf_len;

        status = mz_inflate(&stream, 0);

        m_buffer.insert(m_buffer.end(), buf, buf + (buf_len - stream.avail_out));
    } while (status == MZ_OK);

    mz_inflateEnd(&stream);
}

size_t rkhv::izstream::get_size() const {
    return m_buffer.size();
}

unsigned char rkhv::izstream::remove() {
    return m_buffer[m_index++];
}
