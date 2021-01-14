//
//  astream.h
//  zstream
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 01.13.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

struct AES_ctx;

namespace oo {

    class oastream {
    public:

        oastream(const u_int8_t *key, const u_int8_t *iv);

    public:

        size_t get_size() const;

        std::vector<u_int8_t> get_encoded() const;

        template<class T>
        oastream &operator<<(T value) {
            auto ptr = reinterpret_cast<u_int8_t *>(&value);
            for (size_t i = 0; i < sizeof(T); ++i) {
                append(ptr[i]);
            }

            return *this;
        }

        oastream &operator<<(const std::string &value);

    private:

        std::unique_ptr<AES_ctx> m_aes_context;

        std::vector<u_int8_t> m_buffer;

    private:

        void append(u_int8_t byte);

    };

}

namespace oo {

    class iastream {
    public:

        iastream(const u_int8_t *key, const u_int8_t *iv, const std::vector<u_int8_t> &compressed);

        iastream(const u_int8_t *key, const u_int8_t *iv, const std::string &compressed);

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

        bool operator>>(std::string &value);

    private:

        std::unique_ptr<AES_ctx> m_aes_context;

        size_t m_index = 0;
        std::vector<u_int8_t> m_buffer;

    private:

        void decode(const u_int8_t *next_in, unsigned int avail_in);

        u_int8_t remove();

    };

}