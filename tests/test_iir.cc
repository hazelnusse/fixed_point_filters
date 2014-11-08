#include <gtest/gtest.h>

#include "fixed_point_iir.h"

TEST(TestIIR, Basic16IIR) {
    constexpr std::uint16_t sf = 1024u;
    constexpr std::size_t Q = 1u;
    constexpr std::size_t P = 0u;
    // a_0 = 1.0, a_1 = 0.5
    // b_0 = 3.0
    fixed_point_iir<sf, Q, P> iir16bit{{1.0, 0.5}, {3.}};
    auto y_0 = iir16bit.filter(123);
    EXPECT_EQ(3*123, y_0);
    auto y_1 = iir16bit.filter(0);
    EXPECT_EQ(-y_0/2, y_1);
    auto y_2 = iir16bit.filter(0);
    EXPECT_EQ(-y_1/2, y_2);
    auto y_3 = iir16bit.filter(0);
    EXPECT_EQ(-y_2/2, y_3);
}
