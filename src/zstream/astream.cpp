//
//  astream.cpp
//  zstream
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 01.13.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <cstddef>

#include <aes.hpp>

#include "zstream/astream.h"

namespace {

    const uint8_t c_block_size = 16;

}

// -- oastream --

oo::oastream::oastream(const u_int8_t *key, const u_int8_t *iv) {
    m_aes_context = std::make_unique<AES_ctx>();
    AES_init_ctx_iv(m_aes_context.get(), key, iv);
}

size_t oo::oastream::get_size() const {

    return m_buffer.size();
}

std::vector<u_int8_t> oo::oastream::get_encoded() const {
    std::vector<u_int8_t> result(m_buffer.begin(), m_buffer.end());

    // Padding

    const auto padding = uint8_t(c_block_size - (m_buffer.size() % c_block_size));
    const auto last = result.back();
    if (padding == 0 && last < c_block_size &&
        std::all_of(result.end() - last, result.end(), [last](u_int8_t value) {
            return value == last;
        })) {
        result.resize(result.size() + c_block_size, c_block_size);
    } else {
        result.resize(result.size() + padding, padding);
    }

    //

    AES_CBC_encrypt_buffer(m_aes_context.get(), result.data(), result.size());

    return result;
}

oo::oastream &oo::oastream::operator<<(const std::string &value) {
    *this << value.length();

    auto ptr = value.c_str();
    for (size_t i = 0; i < value.length(); ++i) {
        append(ptr[i]);
    }

    return *this;
}

void oo::oastream::append(u_int8_t byte) {
    m_buffer.push_back(byte);
}

// -- iastream --

oo::iastream::iastream(const u_int8_t *key, const u_int8_t *iv, const std::vector<u_int8_t> &compressed) {
    m_aes_context = std::make_unique<AES_ctx>();
    AES_init_ctx_iv(m_aes_context.get(), key, iv);

    decode(compressed.data(), uint32_t(compressed.size()));
}

oo::iastream::iastream(const u_int8_t *key, const u_int8_t *iv, const std::string &compressed) {
    m_aes_context = std::make_unique<AES_ctx>();
    AES_init_ctx_iv(m_aes_context.get(), key, iv);

    decode(reinterpret_cast<const u_int8_t *>(compressed.c_str()), uint32_t(compressed.length()));
}

void oo::iastream::decode(const u_int8_t *next_in, unsigned int avail_in) {
    m_buffer.assign(next_in, next_in + avail_in);

    AES_CBC_decrypt_buffer(m_aes_context.get(), m_buffer.data(), m_buffer.size());

    // Padding

    const auto last = m_buffer.back();
    if (last < c_block_size &&
        std::all_of(m_buffer.end() - last, m_buffer.end(), [last](u_int8_t value) {
            return value == last;
        })) {
        m_buffer.resize(m_buffer.size() - last);
    }
}

size_t oo::iastream::get_size() const {
    return m_buffer.size();
}

bool oo::iastream::operator>>(std::string &value) {
    size_t len;
    if (!(*this >> len) || len == 0) {
        return false;
    }

    for (size_t i = 0; i < len; ++i) {
        value += remove();
    }

    return true;
}

u_int8_t oo::iastream::remove() {
    return m_buffer[m_index++];
}
