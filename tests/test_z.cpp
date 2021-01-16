//
//  test_z.cpp
//  streams
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 16.01.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <streams/zstream.h>

namespace {

    const char c_text[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
    const uint8_t c_u8 = 234;
    const uint64_t c_u64 = 1000000000000000;
    const uint8_t c_data[] = {0x1, 0x1, 0x1, 0x1, 0x1, 0x2, 0x2, 0x2, 0x2, 0x2, 0x1, 0x1, 0x1, 0x1, 0x1};
    const int16_t c_s16 = 32100;
    const int32_t c_s32 = 1234567890;
    const float c_f = 1.23456;

}

int main() {
    oo::ozstream o;

    o << std::vector<uint8_t>(c_text, c_text + 78);
    o << c_u8;
    o << c_u64;
    o << std::vector<uint8_t>(c_data, c_data + 15);
    o << c_s16;
    o << c_s32;
    o << c_f;

    std::vector<uint8_t> encoded;
    o >> encoded;

    //

    oo::izstream i;
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

    return std::equal(c_text, c_text + 78, text.data()) && c_u8 == u8 && c_u64 == u64 &&
           std::equal(c_data, c_data + 15, data.data()) && c_s16 == s16 && c_s32 == s32 &&
           c_f == f ? 0 : 1;
}