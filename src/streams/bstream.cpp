//
//  bstream.cpp
//  streams
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 14.01.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include "streams/bstream.h"

// -- obstream --

size_t oo::obstream::get_size() const {
    return m_buffer.size();
}

oo::obstream &oo::obstream::operator<<(const std::vector<u_int8_t> &value) {
    *this << value.size();

    m_buffer.insert(m_buffer.end(), value.begin(), value.end());

    return *this;
}

oo::obstream &oo::obstream::operator<<(const uint8_t *value) {
    const size_t size = *reinterpret_cast<size_t *>(m_buffer.data() + m_buffer.size() - sizeof(size_t));

    m_buffer.insert(m_buffer.end(), value, value + size);

    return *this;
}

void oo::obstream::operator>>(oo::obstream &stream) {
    *this >> stream.m_buffer;
}

void oo::obstream::operator>>(std::vector<u_int8_t> &value) {
    value = m_buffer;
}

// -- ibstream --

size_t oo::ibstream::get_size() const {
    return m_buffer.size();
}

bool oo::ibstream::operator>>(std::vector<u_int8_t> &value) {
    size_t size;
    if (!(*this >> size)) {
        return false;
    }

    value.assign(m_buffer.begin() + m_index, m_buffer.begin() + m_index + size);
    m_index += size;

    return true;
}

bool oo::ibstream::operator>>(uint8_t *value) {
    if (m_index == m_buffer.size()) {
        return false;
    }

    const size_t size = *reinterpret_cast<size_t *>(m_buffer.data() + m_index - sizeof(size_t));
    std::copy(m_buffer.begin() + m_index, m_buffer.begin() + m_index + size, value);
    m_index += size;

    return true;
}

void oo::ibstream::operator<<(oo::ibstream &stream) {
    *this << stream.m_buffer;
}

void oo::ibstream::operator<<(const std::vector<u_int8_t> &value) {
    m_buffer = value;
    m_index = 0;
}