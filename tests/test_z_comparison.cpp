//
//  test_z_comparison.cpp
//  streams
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 29.08.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <iostream>

#include <when/stamp.h>

#include <streams/zlstream.h>
#include <streams/zsstream.h>

namespace {

    const char c_data[] = "----------------------------------------44444444----------------------------------------------------------------------------444----4444----------3333333--------------------------------------------------------44---------444------3334444333------------------------------------------------------44-------------4---3344444444433----------------------------------------------------44----------------3322244443444433--------------------------------------------------44--------------3444444224443344433-------------------------------------------------44--------------334444444222443344333------------------------------------------------4--------------3344224434344243334333-----------------------------------------------44-------------33444422433334444333333-----------------------------------------------4-------------334444442243133344313333----------------------------------------------44-----------33322224444243311334311333----------------------------------------------4--222------334222222444444331134311133---------------------------------------------44-222222---3344222222244444433133311133---------------------------------------------4224444424433422022222244444333113311333-------------------------------------------2442244--444233420022222444443331111111333------------------------------------------224422244--4243400022222444443311111111133------------------------------------------2234344224422443400022224444443311111111133-----------------------------------------2234433444442444444002244444443311111111133-----------------------------------------23344---334444444444400444444433111111131133-------------4--------------------------233-4-----3324444443444044444433111111131113--------------44------------------------233--4-------4442444333444444443311111131113----------------4---------------44444433311-334444---4402224444334444433311111131133-----------------44-----------444442224443331134344444-0022224443333333331111113131--------------------4----------444222444444443314--3344-002222224443333333311111333343-------------------4----------42222244444433333411-34-00022222244443113331111133-33442------------------4---------44444444444443333341114--0022222224444331111111133---34222-----------------4-------2244333333443333333411114-0022222222444433311111133433--2224----------------44------22224433333333333331411134-00222222444444333111113344444--244--------------444-------20224443133333333314411334-00222224444443331111133333422-4444444444444444444--------220222443111333111134111334-40022444444433331111111---2244444------------------------2002224431-11111111341133444444444444443333111131111-4444-434------------------------2-02224331-----333-33-3300043344444444433311113331144-224333------------------------22-02244331-----33---333304444333444443333311114444411-24433-------------------------20-02244331------3---33334444433344433333111444433331124433-------------------------22-002244311-----------333344333333333331114443334433314433--------------------------22-022444311----------443333433333331111444433344443331443---------------------------2--022443311--------443333-444-------444443334444443333443---------------------------2-022444311------4444--33-444------44444331444224444333444---------------------------2-022444311-----44----33--3344----44443---1422224444333-44--------------------------220024443111---------433----3334444433-----1420224444333-44--------------------------200244433111--------44---------3333--------1400244444333-44-------------------------2200244331111-------------------------------1440244443333-44-------------------------2202443313331------------------33333333333331140044443331--4-------------------------200244314433---444444444444444333444444444444314044443311--44------------------------2022443144333-44------------44334422224444444433444433313--44------------------------2024441444433442222242222224433344--000022444443334333113---4------------------------2022441424433444444444444224413344-----000444444431331133---44----------------------22022441124433333333343334444313440-------022444444111113----------------------------20022443124433------333-33443114400--000--022224444331111----------------------------20022443124433-------33--333113440--002000222444444331111----------------------------2-02244312443344-------------4444--0002222222444443331131----------------------------2-0224431244334444------44--444--000222222224444443311131----------------------------2-0222431244334---444444444444--0022222224444444433311131----------------------------2-002243124433300------------002222224444444444433311133-----------------------------2--02243124433322000000000000022222444444444333333111131-----------------------------20-0224312433-34422220000000022222444444333333333111111-------------------------------2--024312433-3444222222222222222444443333333333111111--------------------------------20-024314433-33344422222222244444444333331113311111----------------------------------22-024433433---3344444444444444444433331111111111-------------------------------------2--24433433----33344444444444444333331111111111--------------------------------------22-04433333------333444444443333333311111111------------------------------------------2-0443-33---------33333333333333111111------------------------------------------------20443-33------------------------------------------------------------------------------20433-3-------------------------------------------------------------------------------2243-3--------------------------------------------------------------------------------223-----------------------------------------------------------------------------------223-----------------------------------------------------------------------------------22--------------------------------------------------------------------------";

    const size_t n = 1000;

}

int main() {
    std::cout << "compression:" << std::endl;

    //

    std::vector<uint8_t> encoded_zstd_20;
    {
        oo::stamp stamp{"cmp zstd 20"};
        for (size_t i = 0; i < n; ++i) {
            encoded_zstd_20.clear();
            oo::ozsstream os{20};
            os << std::vector<uint8_t>(c_data, c_data + strlen(c_data));
            os >> encoded_zstd_20;
        }
    }

    std::vector<uint8_t> encoded_zstd_10;
    {
        oo::stamp stamp{"cmp zstd 10"};
        for (size_t i = 0; i < n; ++i) {
            encoded_zstd_10.clear();
            oo::ozsstream os{10};
            os << std::vector<uint8_t>(c_data, c_data + strlen(c_data));
            os >> encoded_zstd_10;
        }
    }

    std::vector<uint8_t> encoded_zstd_5;
    {
        oo::stamp stamp{"cmp zstd 5 "};
        for (size_t i = 0; i < n; ++i) {
            encoded_zstd_5.clear();
            oo::ozsstream os{5};
            os << std::vector<uint8_t>(c_data, c_data + strlen(c_data));
            os >> encoded_zstd_5;
        }
    }

    std::vector<uint8_t> encoded_zstd_1;
    {
        oo::stamp stamp{"cmp zstd 1 "};
        for (size_t i = 0; i < n; ++i) {
            encoded_zstd_1.clear();
            oo::ozsstream os{1};
            os << std::vector<uint8_t>(c_data, c_data + strlen(c_data));
            os >> encoded_zstd_1;
        }
    }

    std::vector<uint8_t> encoded_zlib;
    {
        oo::stamp stamp{"cmp zlib   "};
        for (size_t i = 0; i < n; ++i) {
            encoded_zlib.clear();
            oo::ozlstream os;
            os << std::vector<uint8_t>(c_data, c_data + strlen(c_data));
            os >> encoded_zlib;
        }
    }

    //

    std::cout << "decompression:" << std::endl;

    //

    std::vector<uint8_t> data_zstd_20;
    {
        oo::stamp stamp{"dcm zstd 20"};
        for (size_t i = 0; i < n; ++i) {
            data_zstd_20.clear();
            oo::izsstream is;
            is << encoded_zstd_20;
            is >> data_zstd_20;
        }
    }

    std::vector<uint8_t> data_zstd_10;
    {
        oo::stamp stamp{"dcm zstd 10"};
        for (size_t i = 0; i < n; ++i) {
            data_zstd_10.clear();
            oo::izsstream is;
            is << encoded_zstd_10;
            is >> data_zstd_10;
        }
    }

    std::vector<uint8_t> data_zstd_5;
    {
        oo::stamp stamp{"dcm zstd 5 "};
        for (size_t i = 0; i < n; ++i) {
            data_zstd_5.clear();
            oo::izsstream is;
            is << encoded_zstd_5;
            is >> data_zstd_5;
        }
    }

    std::vector<uint8_t> data_zstd_1;
    {
        oo::stamp stamp{"dcm zstd 1 "};
        for (size_t i = 0; i < n; ++i) {
            data_zstd_1.clear();
            oo::izsstream is;
            is << encoded_zstd_1;
            is >> data_zstd_1;
        }
    }

    std::vector<uint8_t> data_zlib;
    {
        oo::stamp stamp{"dcm zlib   "};
        for (size_t i = 0; i < n; ++i) {
            data_zlib.clear();
            oo::izlstream is;
            is << encoded_zlib;
            is >> data_zlib;
        }
    }

    //

    std::cout << "length:" << std::endl;

    //

    std::cout << "len original: " << strlen(c_data) << std::endl;
    std::cout << "len zstd 20 : " << encoded_zstd_20.size() << std::endl;
    std::cout << "len zstd 10 : " << encoded_zstd_10.size() << std::endl;
    std::cout << "len zstd 5  : " << encoded_zstd_5.size() << std::endl;
    std::cout << "len zstd 1  : " << encoded_zstd_1.size() << std::endl;
    std::cout << "len zlib    : " << encoded_zlib.size() << std::endl;

    //

    return data_zstd_1 == data_zstd_5 && data_zstd_5 == data_zstd_10 && data_zstd_20 == data_zlib ? 0 : 1;
}