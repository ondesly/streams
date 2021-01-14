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

namespace rkhv {

    class oastream {
    public:

        oastream(const u_int8_t *key, const u_int8_t *iv);

    public:

        size_t get_size() const;

        std::vector<unsigned char> get_encoded() const;

        template<class T>
        oastream &operator<<(T value) {
            auto ptr = reinterpret_cast<unsigned char *>(&value);
            for (size_t i = 0; i < sizeof(T); ++i) {
                append(ptr[i]);
            }

            return *this;
        }

        oastream &operator<<(const std::string &value);

    private:

        std::unique_ptr<AES_ctx> m_aes_context;

        std::vector<unsigned char> m_buffer;

    private:

        void append(unsigned char byte);

    };

}

namespace rkhv {

    class iastream {
    public:

        iastream(const u_int8_t *key, const u_int8_t *iv, const std::vector<unsigned char> &compressed);

        iastream(const u_int8_t *key, const u_int8_t *iv, const std::string &compressed);

    public:

        size_t get_size() const;

        template<class T>
        bool operator>>(T &value) {
            if (m_index == m_buffer.size()) {
                return false;
            }

            auto ptr = reinterpret_cast<unsigned char *>(&value);
            for (size_t i = 0; i < sizeof(T); ++i) {
                ptr[i] = remove();
            }

            return true;
        }

        bool operator>>(std::string &value);

    private:

        std::unique_ptr<AES_ctx> m_aes_context;

        size_t m_index = 0;
        std::vector<unsigned char> m_buffer;

    private:

        void decode(const unsigned char *next_in, unsigned int avail_in);

        unsigned char remove();

    };

}