#ifndef SCALED_DOUBLE_AS_INT
#define SCALED_DOUBLE_AS_INT

#include <cstdint>

template <std::uint16_t scale_factor, typename T = std::int32_t>
struct scaled_double_as_int {
    constexpr scaled_double_as_int(const double value = 0.0)
        : m_value{static_cast<T>(value * scale_factor)} {
        static_assert(std::is_integral<T>::value, "T must be integral");
    }

    constexpr operator T() { return m_value; };

    T m_value;
};

#endif

