//
//  bstream.cpp
//  zstream
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 14.01.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include "zstream/bstream.h"

// -- obstream --

size_t oo::obstream::get_size() const {
    return m_buffer.size();
}

oo::obstream &oo::obstream::operator<<(const std::vector<u_int8_t> &value) {
    *this << value.size();

    auto ptr = value.data();
    for (size_t i = 0; i < value.size(); ++i) {
        append(ptr[i]);
    }

    return *this;
}

oo::obstream &oo::obstream::operator<<(const std::string &value) {
    *this << value.length();

    auto ptr = value.c_str();
    for (size_t i = 0; i < value.length(); ++i) {
        append(ptr[i]);
    }

    return *this;
}

void oo::obstream::operator>>(std::vector<u_int8_t> &value) {
    value.assign(m_buffer.begin(), m_buffer.end());
}

void oo::obstream::operator>>(std::string &value) {
    value.assign(m_buffer.begin(), m_buffer.end());
}

void oo::obstream::append(u_int8_t byte) {
    m_buffer.push_back(byte);
}

// -- ibstream --

size_t oo::ibstream::get_size() const {
    return m_buffer.size();
}

bool oo::ibstream::operator>>(std::vector<u_int8_t> &value) {
    size_t size;
    if (!(*this >> size) || size == 0) {
        return false;
    }

    for (size_t i = 0; i < size; ++i) {
        value.push_back(remove());
    }

    return true;
}

bool oo::ibstream::operator>>(std::string &value) {
    size_t len;
    if (!(*this >> len) || len == 0) {
        return false;
    }

    for (size_t i = 0; i < len; ++i) {
        value += remove();
    }

    return true;
}

void oo::ibstream::operator<<(const std::vector<u_int8_t> &value) {
    m_buffer.assign(value.begin(), value.end());
}

void oo::ibstream::operator<<(const std::string &value) {
    m_buffer.assign(value.begin(), value.end());
}

u_int8_t oo::ibstream::remove() {
    return m_buffer[m_index++];
}
