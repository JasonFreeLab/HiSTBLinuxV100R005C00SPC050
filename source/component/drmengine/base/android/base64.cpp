/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "base64.h"

#include "ABuffer.h"

namespace android {

sp<ABuffer> decodeBase64(const AString &s) {
    size_t n = s.size();
    if ((n % 4) != 0) {
        return NULL;
    }

    size_t padding = 0;
    if (n >= 1 && s.c_str()[n - 1] == '=') {
        padding = 1;

        if (n >= 2 && s.c_str()[n - 2] == '=') {
            padding = 2;

            if (n >= 3 && s.c_str()[n - 3] == '=') {
                padding = 3;
            }
        }
    }

    // We divide first to avoid overflow. It's OK to do this because we
    // already made sure that n % 4 == 0.
    size_t outLen = (n / 4) * 3 - padding;

    sp<ABuffer> buffer = new ABuffer(outLen);

    uint8_t *out = buffer->data();
    if (out == NULL || buffer->size() < outLen) {
        return NULL;
    }
    size_t j = 0;
    uint32_t accum = 0;
    for (size_t i = 0; i < n; ++i) {
        char c = s.c_str()[i];
        unsigned value;
        if (c >= 'A' && c <= 'Z') {
            value = c - 'A';
        } else if (c >= 'a' && c <= 'z') {
            value = 26 + c - 'a';
        } else if (c >= '0' && c <= '9') {
            value = 52 + c - '0';
        } else if (c == '+') {
            value = 62;
        } else if (c == '/') {
            value = 63;
        } else if (c != '=') {
            return NULL;
        } else {
            if (i < n - padding) {
                return NULL;
            }

            value = 0;
        }

        accum = (accum << 6) | value;

        if (((i + 1) % 4) == 0) {
            out[j++] = (accum >> 16);

            if (j < outLen) { out[j++] = (accum >> 8) & 0xff; }
            if (j < outLen) { out[j++] = accum & 0xff; }

            accum = 0;
        }
    }

    return buffer;
}

static char encode6Bit(unsigned x) {
    if (x <= 25) {
        return 'A' + x;
    } else if (x <= 51) {
        return 'a' + x - 26;
    } else if (x <= 61) {
        return '0' + x - 52;
    } else if (x == 62) {
        return '+';
    } else {
        return '/';
    }
}

void encodeBase64(
        const void *_data, size_t size, AString *out) {
    out->clear();

    const uint8_t *data = (const uint8_t *)_data;

    size_t i;
    for (i = 0; i < (size / 3) * 3; i += 3) {
        uint8_t x1 = data[i];
        uint8_t x2 = data[i + 1];
        uint8_t x3 = data[i + 2];

        out->append(encode6Bit(x1 >> 2));
        out->append(encode6Bit((x1 << 4 | x2 >> 4) & 0x3f));
        out->append(encode6Bit((x2 << 2 | x3 >> 6) & 0x3f));
        out->append(encode6Bit(x3 & 0x3f));
    }
    switch (size % 3) {
        case 0:
            break;
        case 2:
        {
            uint8_t x1 = data[i];
            uint8_t x2 = data[i + 1];
            out->append(encode6Bit(x1 >> 2));
            out->append(encode6Bit((x1 << 4 | x2 >> 4) & 0x3f));
            out->append(encode6Bit((x2 << 2) & 0x3f));
            out->append('=');
            break;
        }
        default:
        {
            uint8_t x1 = data[i];
            out->append(encode6Bit(x1 >> 2));
            out->append(encode6Bit((x1 << 4) & 0x3f));
            out->append("==");
            break;
        }
    }
}

}  // namespace android
