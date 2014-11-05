#include <gtest/gtest.h>

#include "fixed_point_fir.h"

TEST(TestFIR, Basic16FIR) {
    constexpr std::uint16_t sf = 1024u;     // scale factor for integer math
    constexpr std::size_t N = 2u;           // filter depth
    // b_0 = 1, b_1 = 2, b_2 = 4
    fixed_point_fir<sf, N, std::int16_t, std::int32_t> fir16bit{{1., 2., 4.}};
    auto result = fir16bit.filter(123);
    EXPECT_EQ(123, result);
    result = fir16bit.filter(0);
    EXPECT_EQ(246, result);
    result = fir16bit.filter(0);
    EXPECT_EQ(492, result);
    result = fir16bit.filter(0);
    EXPECT_EQ(0, result);
}

TEST(TestFIR, Basic8BitFIR) {
    constexpr std::uint16_t sf = 256u;      // scale factor for integer math
    constexpr std::size_t N = 2u;           // filter depth
    // b_0 = 1, b_1 = 2, b_2 = 4
    fixed_point_fir<sf, N, std::int8_t, std::int16_t> fir8bit{{1., 2., 4.}};
    auto result = fir8bit.filter(12);
    EXPECT_EQ(12, result);
    result = fir8bit.filter(0);
    EXPECT_EQ(24, result);
    result = fir8bit.filter(0);
    EXPECT_EQ(48, result);
    result = fir8bit.filter(0);
    EXPECT_EQ(0, result);
}

