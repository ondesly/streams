//
//  astream.cpp
//  streams
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 01.13.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <cstddef>

#define ECB 0
#define CTR 0

#include <aes.hpp>

#include "streams/astream.h"

namespace {

    const uint8_t c_block_size = 16;

}

// -- oastream --

oo::oastream::oastream(const u_int8_t *key, const u_int8_t *iv) {
    m_aes_context = std::make_unique<AES_ctx>();
    AES_init_ctx_iv(m_aes_context.get(), key, iv);
}

void oo::oastream::operator>>(std::vector<u_int8_t> &value) {
    value = m_buffer;

    // Padding

    const auto padding = uint8_t((c_block_size - (value.size() % c_block_size)) % c_block_size);
    const auto last = value.back();
    if (padding == 0 && last < c_block_size &&
        std::all_of(value.end() - last, value.end(), [last](u_int8_t v) {
            return v == last;
        })) {
        value.resize(value.size() + c_block_size, c_block_size);
    } else {
        value.resize(value.size() + padding, padding);
    }

    //

    AES_CBC_encrypt_buffer(m_aes_context.get(), value.data(), value.size());
}

// -- iastream --

oo::iastream::iastream(const u_int8_t *key, const u_int8_t *iv) {
    m_aes_context = std::make_unique<AES_ctx>();
    AES_init_ctx_iv(m_aes_context.get(), key, iv);
}

void oo::iastream::operator<<(const std::vector<u_int8_t> &value) {
    m_buffer = value;

    //

    AES_CBC_decrypt_buffer(m_aes_context.get(), m_buffer.data(), m_buffer.size());

    // Padding

    const auto last = m_buffer.back();
    if (last <= c_block_size &&
        std::all_of(m_buffer.end() - last, m_buffer.end(), [last](u_int8_t value) {
            return value == last;
        })) {
        m_buffer.resize(m_buffer.size() - last);
    }
}