#pragma once
#include <cinttypes>
#include <iostream>

struct uint2022_t {
    static const int BASE = 1000000000; // основание 10^9
    static const int DIGITS_PER_ELEMENT = 9; // цифр на элемент
    static const int MAX_ELEMENTS = 68; // 68 * 4 байта = 272 байта < 300
    uint32_t digits[MAX_ELEMENTS]; // массив для хранения цифр

    uint2022_t() {
        for (int i = 0; i < MAX_ELEMENTS; i++) {
            digits[i] = 0;
        }
    }
};

static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");

uint2022_t from_uint(uint32_t i);

uint2022_t from_string(const char* buff);

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator<=(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs);

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value);