#ifndef FIXED_POINT_IIR_H
#define FIXED_POINT_IIR_H

#include <algorithm>
#include <array>
#include <cstdint>

#include "circular_buffer.h"
#include "scaled_double_as_int.h"

template <std::uint16_t scale_factor,
          std::size_t feedback_order,
          std::size_t feedforward_order,
          typename InOutType = std::int16_t,
          typename UpScaledType = std::int32_t>
class fixed_point_iir {
public:
    using scaled_int = scaled_double_as_int<scale_factor, UpScaledType>;
    using ff_coeff_array_t = std::array<scaled_int, feedforward_order + 1>;
    using fb_coeff_array_t = std::array<scaled_int, feedback_order + 1>;
    using input_buffer_t = circular_buffer<InOutType, feedforward_order + 1>;
    using output_buffer_t = circular_buffer<InOutType, feedback_order + 1>;

    constexpr fixed_point_iir(const fb_coeff_array_t& a,
                              const ff_coeff_array_t& b)
        : m_a(a), m_b(b), m_x{}, m_y{} { }

    void reset() {
        m_x.fill(0);
        m_y.fill(0);
    }

    InOutType filter(const InOutType x_n) {
        m_x.push_front(x_n);
        m_y.push_front(0);
        m_y.front() = (
            std::inner_product(m_x.cbegin(), m_x.cend(), m_b.cbegin(), 0) -
            std::inner_product(m_y.cbegin() + 1, m_y.cend(), m_a.cbegin() + 1,
                               0)) / m_a[0];

        return m_y.front();
    }

private:
    const fb_coeff_array_t m_a;
    const ff_coeff_array_t m_b;
    input_buffer_t m_x;
    output_buffer_t m_y;
};

#endif

