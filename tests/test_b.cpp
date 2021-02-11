//
//  test_b.cpp
//  streams
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 16.01.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <streams/bstream.h>

namespace {

    const char c_text[] = "abcdefghijklmnopqrstuvwxyz";
    const uint8_t c_u8 = 234;
    const uint64_t c_u64 = 1000000000000000;
    const uint8_t c_data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
    const int16_t c_s16 = 32100;
    const int32_t c_s32 = 1234567890;
    const float c_f = 1.23456;
    const size_t c_array_size = 10;
    const uint8_t c_array[c_array_size] = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19};

}

int main() {
    oo::obstream o;

    o << std::vector<uint8_t>(c_text, c_text + 26);
    o << c_u8;
    o << c_u64;
    o << std::vector<uint8_t>(c_data, c_data + 10);
    o << c_s16;
    o << c_s32;
    o << c_f;
    o << c_array_size;
    o << c_array;

    std::vector<uint8_t> encoded;
    o >> encoded;

    //

    oo::ibstream i;
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

    size_t array_size;
    i >> array_size;
    uint8_t array[array_size];
    i >> array;

    return std::equal(c_text, c_text + 26, text.data()) && c_u8 == u8 && c_u64 == u64 &&
           std::equal(c_data, c_data + 10, data.data()) && c_s16 == s16 && c_s32 == s32 &&
           c_f == f && std::equal(c_array, c_array + c_array_size, array) ? 0 : 1;
}