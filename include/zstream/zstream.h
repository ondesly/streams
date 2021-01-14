//
//  zstream.h
//  zstream
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 30.10.2020.
//  Copyright © 2020 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <cstddef>
#include <stdint.h>
#include <string>
#include <vector>

namespace oo {

    class ozstream {
    public:

        size_t get_size() const;

        std::vector<u_int8_t> get_compressed() const;

        template<class T>
        ozstream &operator<<(T value) {
            auto ptr = reinterpret_cast<u_int8_t *>(&value);
            for (size_t i = 0; i < sizeof(T); ++i) {
                append(ptr[i]);
            }

            return *this;
        }

    private:

        std::vector<u_int8_t> m_buffer;

    private:

        void append(u_int8_t byte);

    };

}

namespace oo {

    class izstream {
    public:

        izstream(const std::vector<u_int8_t> &compressed);

        izstream(const std::string &compressed);

    public:

        size_t get_size() const;

        template<class T>
        bool operator>>(T &value) {
            if (m_index == m_buffer.size()) {
                return false;
            }

            auto ptr = reinterpret_cast<u_int8_t *>(&value);
            for (size_t i = 0; i < sizeof(T); ++i) {
                ptr[i] = remove();
            }

            return true;
        }

    private:

        size_t m_index = 0;
        std::vector<u_int8_t> m_buffer;

    private:

        void decompress(const u_int8_t *next_in, unsigned int avail_in);

        u_int8_t remove();

    };

}