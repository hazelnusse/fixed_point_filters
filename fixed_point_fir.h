#ifndef FIXED_POINT_FIR_H
#define FIXED_POINT_FIR_H

#include <algorithm>
#include <array>
#include <cstdint>

#include "circular_buffer.h"
#include "scaled_double_as_int.h"

template <std::uint16_t scale_factor,
          std::size_t feedforward_order,
          typename InOutType = std::int16_t,
          typename UpScaledType = std::int32_t>
class fixed_point_fir {
public:
    using scaled_int = scaled_double_as_int<scale_factor, UpScaledType>;
    using ff_coeff_array_t = std::array<scaled_int, feedforward_order + 1>;
    using input_buffer_t = circular_buffer<InOutType, feedforward_order + 1>;

    constexpr fixed_point_fir(const ff_coeff_array_t& b) : m_b(b), m_x{} {}

    void reset() {
        m_x.fill(0);
    }

    InOutType filter(const InOutType x_n) {
        m_x.push_front(x_n);
        return std::inner_product(m_x.cbegin(), m_x.cend(), m_b.cbegin(), 0)
            / scale_factor;
    }

private:
    const ff_coeff_array_t m_b;
    input_buffer_t m_x;
};

#endif

