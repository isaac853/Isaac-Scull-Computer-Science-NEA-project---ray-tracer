#include <catch2/catch_test_macros.hpp>
#include "ray_tracer/Camera.hpp"
#include <iostream>

TEST_CASE("sanity checks", "[unit]") {
    REQUIRE(1 + 1 == 2);
}

using namespace isaac::math;
using namespace isaac::ray_tracer;

TEST_CASE("not a real test", "[blah]") {
    Camera c(3.0, 1.0, 2.0);
    PixelCanvas p(2, 3);
    const int32_t samplesPerPixel = 1;

    c.render(
        p,
        samplesPerPixel,
        [&](Vector3& dir, Vector3& colour, int x, int y){
            std::cout << "(" << x << "," << y << ") " << dir << "\n";
        }
    );

    REQUIRE(1 == 1);
}
