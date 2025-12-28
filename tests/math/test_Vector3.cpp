#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "math/Vector3.hpp"

TEST_CASE("Test 3d vector mul", "[unit]") {
    isaac::math::Vector3 v1(1.0, 2.0, 3.0), v2(4.0, 5.0, 6.0), result;

    v1.mul(v2, result);

    REQUIRE_THAT(result.v[0], Catch::Matchers::WithinAbs(4.0, 1e-6));
    REQUIRE_THAT(result.v[1], Catch::Matchers::WithinAbs(10.0, 1e-6));
    REQUIRE_THAT(result.v[2], Catch::Matchers::WithinAbs(18.0, 1e-6));
}

// TODO write tests for the cross product