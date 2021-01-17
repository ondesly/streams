//
//  astream.h
//  streams
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 01.13.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <memory>
#include <vector>

#include "streams/bstream.h"

struct AES_ctx;

namespace oo {

    class oastream : public obstream {
    public:

        oastream(const u_int8_t *key, const u_int8_t *iv);

        ~oastream();

    public:

        using obstream::operator>>;

        void operator>>(std::vector<u_int8_t> &value) override;

    private:

        std::unique_ptr<AES_ctx> m_aes_context;

    };

}

namespace oo {

    class iastream : public ibstream {
    public:

        iastream(const u_int8_t *key, const u_int8_t *iv);

        ~iastream();

    public:

        void operator<<(const std::vector<u_int8_t> &value) override;

    private:

        std::unique_ptr<AES_ctx> m_aes_context;

    };

}