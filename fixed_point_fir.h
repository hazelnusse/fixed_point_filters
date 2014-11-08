#ifndef FIXED_POINT_FIR_H
#define FIXED_POINT_FIR_H

#include <algorithm>
#include <array>
#include <cstdint>

#include "scaled_double_as_int.h"

template <std::uint16_t scale_factor,
          std::size_t FilterOrder,
          typename InOutType = std::int16_t,
          typename UpScaledType = std::int32_t>
class fixed_point_fir {
public:
    using fir_coeff_array_t = std::array<
        scaled_double_as_int<scale_factor, UpScaledType>, FilterOrder + 1>;

    using input_array_t = std::array<UpScaledType, FilterOrder>;

    constexpr fixed_point_fir(const fir_coeff_array_t& b) : m_b(b), m_x{0} { }

    void reset() { m_x.fill(0); }

    InOutType filter(const InOutType x_n) {
        // compute \sum_{i = 0}^{FilterOrder} (b_i * x[n - i]) / scale_factor
        //
        // GOTCHA: scale_factor is typically a power of two. However, right
        // bit-shift on a signed integer has implementation defined (aka,
        // reasonable, should not kill your cat) behavior as per the C/C++
        // standard. See:
        //
        // http://stackoverflow.com/questions/12692111/why-is-such-complex-code-emitted-for-dividing-a-signed-integer-by-a-power-of-two
        //
        // To ensure consistency across platforms, divide by scale_factor and
        // allow compiler to optimize it in the case when
        //
        // * scale_factor is a power of two
        // * result of std::inner_product is non-negative
        // * target machine has efficient right bit shift instructions
        //
        // The difference between power of 2 integer division and right bit
        // shift is in the way rounding works: integer division rounds towards
        // zero while bit shifting rounds towards negative infinity. If this
        // consistency is not of primary importance, scale_factor could be
        // changed to be the exponent of the power of two and the division
        // changed to a right bit-shift.
        //
        // TODO: Check assembly when scale_factor is a power of two
        InOutType result = std::inner_product(m_x.cbegin(),
            m_x.cend(), m_b.cbegin() + 1, m_b[0] * x_n) / scale_factor;

        // shift stored input
        for (std::size_t i = m_x.size() - 1; i != 0; --i) {
            m_x[i] = m_x[i - 1];
        }

        // save latest input
        m_x[0] = x_n;

        return result;
    }

private:
    const fir_coeff_array_t m_b;  // FIR coefficients
    input_array_t m_x;            // Previous inputs
};

#endif

