//
//  test_a.cpp
//  streams
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 16.01.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <streams/astream.h>

namespace {

    const uint8_t key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                           0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    const uint8_t iv[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                          0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

    const char c_text[] = "abcdefghijklmnopqrstuvwxyz";
    const uint8_t c_u8 = 234;
    const uint64_t c_u64 = 1000000000000000;
    const uint8_t c_data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
    const int16_t c_s16 = 32100;
    const int32_t c_s32 = 1234567890;
    const float c_f = 1.23456;

}

int main() {
    oo::oastream o(key, iv);

    o << std::vector<uint8_t>(c_text, c_text + 26);
    o << c_u8;
    o << c_u64;
    o << std::vector<uint8_t>(c_data, c_data + 10);
    o << c_s16;
    o << c_s32;
    o << c_f;

    std::vector<uint8_t> encoded;
    o >> encoded;

    //

    oo::iastream i(key, iv);
    i << encoded;

    std::vector<uint8_t> text;
    uint8_t u8;
    uint64_t u64;
    std::vector<uint8_t> data;
    int16_t s16;
    int32_t s32;
    float f;

    i >> text;
    i >> u8;
    i >> u64;
    i >> data;
    i >> s16;
    i >> s32;
    i >> f;

    return std::equal(c_text, c_text + 26, text.data()) && c_u8 == u8 && c_u64 == u64 &&
           std::equal(c_data, c_data + 10, data.data()) && c_s16 == s16 && c_s32 == s32 &&
           c_f == f ? 0 : 1;
}