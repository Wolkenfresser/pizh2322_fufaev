#include "number.h"
#include <string>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <iomanip>

// Вспомогательная функция для нормализации числа
void normalize(uint2022_t& num) {
    uint64_t carry = 0;
    for (size_t i = 0; i < uint2022_t::MAX_ELEMENTS; ++i) {
        uint64_t value = (uint64_t)num.digits[i] + carry;
        num.digits[i] = value % uint2022_t::BASE;
        carry = value / uint2022_t::BASE;
    }
    if (carry != 0) {
        throw std::overflow_error("Переполнение при нормализации uint2022_t");
    }
}

uint2022_t from_uint(uint32_t i) {
    uint2022_t result;
    result.digits[0] = i;
    normalize(result);
    return result;
}

uint2022_t from_string(const char* buff) {
    uint2022_t result;

    while (*buff == '0') buff++; // пропуск ведущих нулей
    if (*buff == '\0') return result;

    int len = static_cast<int>(strlen(buff));
    int pos = 0;

    while (len > 0 && pos < uint2022_t::MAX_ELEMENTS) {
        int chunk_size = std::min(9, len);
        const char* chunk_start = buff + len - chunk_size;

        char chunk[10] = { 0 };
        memcpy(chunk, chunk_start, chunk_size);  // безопасная альтернатива strncpy
        uint32_t value = static_cast<uint32_t>(std::stoul(chunk));

        result.digits[pos++] = value;
        len -= chunk_size;
    }

    normalize(result);
    return result;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    uint64_t carry = 0;
    for (size_t i = 0; i < uint2022_t::MAX_ELEMENTS; ++i) {
        uint64_t sum = static_cast<uint64_t>(lhs.digits[i]) + rhs.digits[i] + carry;
        result.digits[i] = static_cast<uint32_t>(sum % uint2022_t::BASE);
        carry = sum / uint2022_t::BASE;
    }
    if (carry != 0) {
        throw std::overflow_error("Переполнение при сложении uint2022_t");
    }
    return result;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    int64_t borrow = 0;
    for (size_t i = 0; i < uint2022_t::MAX_ELEMENTS; ++i) {
        int64_t diff = static_cast<int64_t>(lhs.digits[i]) - rhs.digits[i] - borrow;
        if (diff < 0) {
            diff += uint2022_t::BASE;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        result.digits[i] = static_cast<uint32_t>(diff);
    }
    if (borrow != 0) {
        throw std::overflow_error("Недопустимое вычитание: результат меньше 0 для uint2022_t");
    }
    return result;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    for (size_t i = 0; i < uint2022_t::MAX_ELEMENTS; ++i) {
        uint64_t carry = 0;
        for (size_t j = 0; j + i < uint2022_t::MAX_ELEMENTS; ++j) {
            uint64_t mul = static_cast<uint64_t>(lhs.digits[i]) * rhs.digits[j] + result.digits[i + j] + carry;
            result.digits[i + j] = static_cast<uint32_t>(mul % uint2022_t::BASE);
            carry = mul / uint2022_t::BASE;
        }
        if (carry != 0) {
            throw std::overflow_error("Переполнение при умножении uint2022_t");
        }
    }
    return result;
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (size_t i = 0; i < uint2022_t::MAX_ELEMENTS; ++i) {
        if (lhs.digits[i] != rhs.digits[i]) return false;
    }
    return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return !(lhs == rhs);
}

bool operator<=(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (int i = uint2022_t::MAX_ELEMENTS - 1; i >= 0; --i) {
        if (lhs.digits[i] < rhs.digits[i]) return true;
        if (lhs.digits[i] > rhs.digits[i]) return false;
    }
    return true;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    if (rhs == from_uint(0)) throw std::runtime_error("Division by zero");

    uint2022_t quotient;
    uint2022_t remainder;

    for (int i = uint2022_t::MAX_ELEMENTS - 1; i >= 0; i--) {
        for (int j = uint2022_t::MAX_ELEMENTS - 1; j > 0; j--) {
            remainder.digits[j] = remainder.digits[j - 1];
        }
        remainder.digits[0] = lhs.digits[i];

        uint32_t low = 0, high = uint2022_t::BASE - 1, mid;
        uint32_t q_digit = 0;

        while (low <= high) {
            mid = (low + high) / 2;

            uint2022_t temp = rhs * from_uint(mid);
            if (temp <= remainder) {
                q_digit = mid;
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }

        remainder = remainder - (rhs * from_uint(q_digit));
        quotient.digits[i] = q_digit;
    }

    return quotient;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    int i = uint2022_t::MAX_ELEMENTS - 1;
    while (i > 0 && value.digits[i] == 0) i--;

    stream << value.digits[i--];
    for (; i >= 0; --i) {
        stream << std::setw(uint2022_t::DIGITS_PER_ELEMENT)
            << std::setfill('0')
            << value.digits[i];
    }
    return stream;
}