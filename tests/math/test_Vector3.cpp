#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "math/Vector3.hpp"


using namespace isaac::math;
TEST_CASE("Test 3d vector mul", "[vector3]") {
    isaac::math::Vector3 v1(1.0, 2.0, 3.0), v2(4.0, 5.0, 6.0), result;

    v1.mul(v2, result);

    REQUIRE_THAT(result.v[0], Catch::Matchers::WithinAbs(4.0, 1e-6));
    REQUIRE_THAT(result.v[1], Catch::Matchers::WithinAbs(10.0, 1e-6));
    REQUIRE_THAT(result.v[2], Catch::Matchers::WithinAbs(18.0, 1e-6));
}

TEST_CASE("Test 3d vector dot", "[vector3]") {
    isaac::math::Vector3 v1(1.0, 2.0, 3.0), v2(4.0, 5.0, 6.0);
    isaac::math::floating result = v1.dot(v2);

    REQUIRE_THAT(result, Catch::Matchers::WithinAbs(32.0, 1e-6));
}
TEST_CASE("Test normalise vector method","[vector3]") {
    Vector3 v1(1.0, 2.0, 3.0), result;

    v1.normalise(result);

    REQUIRE_THAT(result.v[0], Catch::Matchers::WithinAbs(1.0/sqrt(14.0), 1e-6));
    REQUIRE_THAT(result.v[1], Catch::Matchers::WithinAbs(2.0/sqrt(14.0), 1e-6));
    REQUIRE_THAT(result.v[2], Catch::Matchers::WithinAbs(3.0/sqrt(14.0), 1e-6));
}
// TODO write tests for the cross product

