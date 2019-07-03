#define IUTEST_USE_MAIN 1
#include <iutest.hpp>
#include <parseRGB.h>
#include <tuple>
#include <optional>
#include <cstdint>
std::optional<std::tuple<std::uint8_t, std::uint8_t, std::uint8_t>> parseRGB(const char* src)
{
    std::uint8_t r, g, b;
    const bool re = parseRGB(src, &r, &g, &b);
    if (re) return std::make_tuple(r, g, b);
    return {};
}
IUTEST(parseRGB, parseRGB)
{
    using T = std::tuple<std::uint8_t, std::uint8_t, std::uint8_t>;
    IUTEST_ASSERT_EQ((T{222, 173, 190}), parseRGB("DEADBE"));
    IUTEST_ASSERT_EQ(std::nullopt, parseRGB("GHIJKL"));
    IUTEST_ASSERT_EQ((T{165, 165, 165}), parseRGB("A5A5A5"));
    IUTEST_ASSERT_EQ(std::nullopt, parseRGB("0FH00A"));
}
