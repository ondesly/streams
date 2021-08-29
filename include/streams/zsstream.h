//
//  zsstream.h
//  streams
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 29.08.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <vector>

#include "streams/bstream.h"

namespace oo {

    class ozsstream : public obstream {
    public:

        explicit ozsstream(int compression_level = 5);

    public:

        using obstream::operator>>;

        void operator>>(std::vector<uint8_t> &value) override;

    private:

        int m_compression_level;

    };

}

namespace oo {

    class izsstream : public ibstream {
    public:

        using ibstream::operator<<;

        void operator<<(const std::vector<uint8_t> &value) override;

    };

}