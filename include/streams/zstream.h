//
//  zstream.h
//  streams
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 30.10.2020.
//  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <vector>

#include "streams/bstream.h"

namespace oo {

    class ozstream : public obstream {
    public:

        using obstream::operator>>;

        void operator>>(std::vector<u_int8_t> &value) override;

    };

}

namespace oo {

    class izstream : public ibstream {
    public:

        using ibstream::operator<<;

        void operator<<(const std::vector<u_int8_t> &value) override;

    };

}