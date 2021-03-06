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

oo::obstream &oo::obstream::operator<<(const std::vector<uint8_t> &value) {
    *this << array_size(value.size());

    m_buffer.insert(m_buffer.end(), value.begin(), value.end());

    return *this;
}

oo::obstream &oo::obstream::operator<<(const uint8_t *value) {
    const auto size = *reinterpret_cast<array_size *>(m_buffer.data() + m_buffer.size() - sizeof(array_size));

    m_buffer.insert(m_buffer.end(), value, value + size);

    return *this;
}

void oo::obstream::operator>>(oo::obstream &stream) {
    *this >> stream.m_buffer;
}

void oo::obstream::operator>>(std::vector<uint8_t> &value) {
    value = m_buffer;
}

// -- ibstream --

size_t oo::ibstream::get_size() const {
    return m_buffer.size();
}

bool oo::ibstream::operator>>(std::vector<uint8_t> &value) {
    array_size size;
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

    const auto size = *reinterpret_cast<array_size *>(m_buffer.data() + m_index - sizeof(array_size));
    std::copy(m_buffer.begin() + m_index, m_buffer.begin() + m_index + size, value);
    m_index += size;

    return true;
}

void oo::ibstream::operator<<(oo::ibstream &stream) {
    *this << stream.m_buffer;
}

void oo::ibstream::operator<<(const std::vector<uint8_t> &value) {
    m_buffer = value;
    m_index = 0;
}