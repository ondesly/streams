# streams

This is a tiny implementation of streams in C++ for:
 * Byte serialization
 * Zlib compression (based on richgel999's miniz)
 * Zstandard compression (based on facebook's zstd)
 * AES encryption (based on kokke's tiny-AES-c)

## Examples
Beside the examples below, you may want to check test files in the tests directory.

### Byte serialization

```cpp
oo::obstream o;
o << int32_t(1234567890);
o << uint64_t(1000000000000000);

std::vector<uint8_t> encoded;
o >> encoded;

oo::ibstream i;
i << encoded;

int32_t i32;
i >> i32;

uint64_t u64;
i >> u64;
```

### Zlib compression

```cpp
oo::ozlstream o;
o << int32_t(1234567890);
o << uint64_t(1000000000000000);

std::vector<uint8_t> encoded;
o >> encoded;

oo::izlstream i;
i << encoded;

int32_t i32;
i >> i32;

uint64_t u64;
i >> u64;
```

### Zstdandard compression

```cpp
oo::ozsstream o;
o << int32_t(1234567890);
o << uint64_t(1000000000000000);

std::vector<uint8_t> encoded;
o >> encoded;

oo::izsstream i;
i << encoded;

int32_t i32;
i >> i32;

uint64_t u64;
i >> u64;
```

### AES encryption

```cpp
const uint8_t key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
const uint8_t iv[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
                          
oo::oastream o(key, iv);
o << int32_t(1234567890);
o << uint64_t(1000000000000000);

std::vector<uint8_t> encoded;
o >> encoded;

oo::iastream i(key, iv);
i << encoded;

int32_t i32;
i >> i32;

uint64_t u64;
i >> u64;
```

## Requirements

This library requires a C++17 compiler and standard library.
