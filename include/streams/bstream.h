//
//  bstream.h
//  streams
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 14.01.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <vector>

namespace oo {

    class obstream {
    public:

        size_t get_size() const;

    public:

        template<class T>
        obstream &operator<<(T value) {
            const auto ptr = reinterpret_cast<u_int8_t *>(&value);
            m_buffer.insert(m_buffer.end(), ptr, ptr + sizeof(T));

            return *this;
        }

        obstream &operator<<(const std::vector<u_int8_t> &value);

    public:

        void operator>>(obstream &stream);

        virtual void operator>>(std::vector<u_int8_t> &value);

    protected:

        std::vector<u_int8_t> m_buffer;

    };

}

namespace oo {

    class ibstream {
    public:

        size_t get_size() const;

    public:

        template<class T>
        bool operator>>(T &value) {
            if (m_index == m_buffer.size()) {
                return false;
            }

            const auto ptr = reinterpret_cast<u_int8_t *>(&value);
            std::copy(m_buffer.begin() + m_index, m_buffer.begin() + m_index + sizeof(T), ptr);
            m_index += sizeof(T);

            return true;
        }

        bool operator>>(std::vector<u_int8_t> &value);

    public:

        void operator<<(ibstream &stream);

        virtual void operator<<(const std::vector<u_int8_t> &value);

    protected:

        size_t m_index = 0;
        std::vector<u_int8_t> m_buffer;

    };

}