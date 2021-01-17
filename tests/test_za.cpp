//
//  test_za.cpp
//  streams
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 17.01.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <streams/astream.h>
#include <streams/zstream.h>

namespace {

    const uint8_t key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                           0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    const uint8_t iv[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                          0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

    const char c_text[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
    const uint8_t c_u8 = 234;
    const uint64_t c_u64 = 1000000000000000;
    const uint8_t c_data[] = {0x1, 0x1, 0x1, 0x1, 0x1, 0x2, 0x2, 0x2, 0x2, 0x2, 0x1, 0x1, 0x1, 0x1, 0x1};
    const int16_t c_s16 = 32100;
    const int32_t c_s32 = 1234567890;
    const float c_f = 1.23456;

}

int main() {
    oo::ozstream oz;
    oo::oastream oa(key, iv);

    oz << std::vector<uint8_t>(c_text, c_text + 78);
    oz << c_u8;
    oz << c_u64;
    oz << std::vector<uint8_t>(c_data, c_data + 15);
    oz << c_s16;
    oz << c_s32;
    oz << c_f;

    oz >> oa;
    std::vector<uint8_t> encoded;
    oa >> encoded;

    //

    oo::iastream ia(key, iv);
    oo::izstream iz;

    ia << encoded;
    iz << ia;

    std::vector<uint8_t> text;
    uint8_t u8;
    uint64_t u64;
    std::vector<uint8_t> data;
    int16_t s16;
    int32_t s32;
    float f;

    iz >> text;
    iz >> u8;
    iz >> u64;
    iz >> data;
    iz >> s16;
    iz >> s32;
    iz >> f;

    return std::equal(c_text, c_text + 78, text.data()) && c_u8 == u8 && c_u64 == u64 &&
           std::equal(c_data, c_data + 15, data.data()) && c_s16 == s16 && c_s32 == s32 &&
           c_f == f ? 0 : 1;
}