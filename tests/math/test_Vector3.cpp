#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "math/Vector3.hpp"


using namespace isaac::math;
// name and group of test
TEST_CASE("Test 3d vector constructor w params", "[vector3]") {
    //construct v1
    isaac::math::Vector3 v1(1.0, 2.0, 3.0); 

    //required values in v1 to pass
    //needs to be with 10^-6 of the given values
    REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(1.0, 1e-6)); 
    REQUIRE_THAT(v1.v[1], Catch::Matchers::WithinAbs(2.0, 1e-6)); 
    REQUIRE_THAT(v1.v[2], Catch::Matchers::WithinAbs(3.0, 1e-6));
}

TEST_CASE("Test 3d vector constructor", "[vector3]") {
    isaac::math::Vector3 v1;

    REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(0.0, 1e-6));
    REQUIRE_THAT(v1.v[1], Catch::Matchers::WithinAbs(0.0, 1e-6));
    REQUIRE_THAT(v1.v[2], Catch::Matchers::WithinAbs(0.0, 1e-6));
}

TEST_CASE("Test 3d vector add w result", "[vector3]") {
    isaac::math::Vector3 v1(1.0, 2.0, 3.0), v2(1.0, 2.0, 3.0), result;

    v1.add(v2, result);

    REQUIRE_THAT(result.v[0], Catch::Matchers::WithinAbs(2.0, 1e-6));
    REQUIRE_THAT(result.v[1], Catch::Matchers::WithinAbs(4.0, 1e-6));
    REQUIRE_THAT(result.v[2], Catch::Matchers::WithinAbs(6.0, 1e-6));
}

TEST_CASE("Test 3d vector add", "[vector3]") {
    isaac::math::Vector3 v1(1.0, 2.0, 3.0), v2(1.0, 2.0, 3.0);

    v1.add(v2);

    REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(2.0, 1e-6));
    REQUIRE_THAT(v1.v[1], Catch::Matchers::WithinAbs(4.0, 1e-6));
    REQUIRE_THAT(v1.v[2], Catch::Matchers::WithinAbs(6.0, 1e-6));
}

TEST_CASE("Test 3d vector sub w result", "[vector3]") {
    isaac::math::Vector3 v1(1.0, 2.0, 3.0), v2(4.0, 4.0, 6.0), result;

    v1.sub(v2, result);

    REQUIRE_THAT(result.v[0], Catch::Matchers::WithinAbs(-3.0, 1e-6));
    REQUIRE_THAT(result.v[1], Catch::Matchers::WithinAbs(-2.0, 1e-6));
    REQUIRE_THAT(result.v[2], Catch::Matchers::WithinAbs(-3.0, 1e-6));
}

TEST_CASE("Test 3d vector sub", "[vector3]") {
    isaac::math::Vector3 v1(1.0, 2.0, 3.0), v2(4.0, 4.0, 6.0);

    v1.sub(v2);

    REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(-3.0, 1e-6));
    REQUIRE_THAT(v1.v[1], Catch::Matchers::WithinAbs(-2.0, 1e-6));
    REQUIRE_THAT(v1.v[2], Catch::Matchers::WithinAbs(-3.0, 1e-6));
}



TEST_CASE("Test 3d vector mul", "[vector3]") {
    isaac::math::Vector3 v1(1.0, 2.0, 3.0), v2(4.0, 5.0, 6.0), result;

    v1.mul(v2, result);

    REQUIRE_THAT(result.v[0], Catch::Matchers::WithinAbs(4.0, 1e-6));
    REQUIRE_THAT(result.v[1], Catch::Matchers::WithinAbs(10.0, 1e-6));
    REQUIRE_THAT(result.v[2], Catch::Matchers::WithinAbs(18.0, 1e-6));
}

TEST_CASE("Test 3d vector mul w scalar", "[vector3]") {
    isaac::math::Vector3 v1(1.0, 2.0, 3.0), result;
    isaac::math::floating scal(3.0);
    v1.mul(scal, result);

    REQUIRE_THAT(result.v[0], Catch::Matchers::WithinAbs(3.0, 1e-6));
    REQUIRE_THAT(result.v[1], Catch::Matchers::WithinAbs(6.0, 1e-6));
    REQUIRE_THAT(result.v[2], Catch::Matchers::WithinAbs(9.0, 1e-6));
}

TEST_CASE("Test 3d vector dot", "[vector3]") {
    isaac::math::Vector3 v1(1.0, 2.0, 3.0), v2(1.0, 2.0, 3.0);
    isaac::math::floating result = v1.dot(v2);

    REQUIRE_THAT(result, Catch::Matchers::WithinAbs(14.0, 1e-6));
}


TEST_CASE("Test 3d vector cross", "[vector3]") {
    isaac::math::Vector3 v1(1.0, 2.0, 3.0), v2(4.0, 5.0, 6.0), result;
    
    v1.cross(v2, result);
    
    REQUIRE_THAT(result.v[0], Catch::Matchers::WithinAbs(-3.0, 1e-6));
    REQUIRE_THAT(result.v[1], Catch::Matchers::WithinAbs(6.0, 1e-6));
    REQUIRE_THAT(result.v[2], Catch::Matchers::WithinAbs(-3.0, 1e-6));
}

TEST_CASE("Test normalise vector method w result","[vector3]") {
    Vector3 v1(1.0, 2.0, 3.0), result;

    v1.normalise(result);

    REQUIRE_THAT(result.v[0], Catch::Matchers::WithinAbs(1.0/sqrt(14.0), 1e-6));
    REQUIRE_THAT(result.v[1], Catch::Matchers::WithinAbs(2.0/sqrt(14.0), 1e-6));
    REQUIRE_THAT(result.v[2], Catch::Matchers::WithinAbs(3.0/sqrt(14.0), 1e-6));
}

TEST_CASE("Test normalise vector method","[vector3]") {
    Vector3 v1(1.0, 2.0, 3.0);

    v1.normalise();

    REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(1.0/sqrt(14.0), 1e-6));
    REQUIRE_THAT(v1.v[1], Catch::Matchers::WithinAbs(2.0/sqrt(14.0), 1e-6));
    REQUIRE_THAT(v1.v[2], Catch::Matchers::WithinAbs(3.0/sqrt(14.0), 1e-6));
}

TEST_CASE("Test 3d vector =", "[vector3]") {
    isaac::math::Vector3 v1(1.0, 2.0, 3.0), v2(4.0, 5.0, 6.0);
    
    v1 = v2;
    
    REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(4.0, 1e-6));
    REQUIRE_THAT(v1.v[1], Catch::Matchers::WithinAbs(5.0, 1e-6));
    REQUIRE_THAT(v1.v[2], Catch::Matchers::WithinAbs(6.0, 1e-6));
}

