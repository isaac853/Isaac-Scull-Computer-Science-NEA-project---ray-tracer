#include <catch2/catch_test_macros.hpp>
#include "ray_tracer/Camera.hpp"

TEST_CASE("sanity checks", "[unit]") {
    REQUIRE(1 + 1 == 2);
}

using namespace isaac::math;
using namespace isaac::ray_tracer;

TEST_CASE("not a real test", "[blah]") {
    Camera c(7.0, 1.0, 1.0);
    REQUIRE(1 == 1);
}
