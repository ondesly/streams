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
            for (size_t i = 0; i < sizeof(T); ++i) {
                append(ptr[i]);
            }

            return *this;
        }

        obstream &operator<<(const std::vector<u_int8_t> &value);

    public:

        void operator>>(std::vector<u_int8_t> &value);

    private:

        std::vector<u_int8_t> m_buffer;

    private:

        void append(u_int8_t byte);

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
            for (size_t i = 0; i < sizeof(T); ++i) {
                ptr[i] = remove();
            }

            return true;
        }

        bool operator>>(std::vector<u_int8_t> &value);

    public:

        void operator<<(const std::vector<u_int8_t> &value);

    private:

        size_t m_index = 0;
        std::vector<u_int8_t> m_buffer;

    private:

        u_int8_t remove();

    };

}