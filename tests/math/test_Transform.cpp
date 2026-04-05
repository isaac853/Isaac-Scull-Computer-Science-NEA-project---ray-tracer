#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "math/Transform.hpp"
#include "math/Matrix4x3.hpp"
#include "math/Vector3.hpp"
#include <iostream>
#include <stdio.h>

//note to self, to make ninja include new test file in debug, mess around in cmake, to force a rebuild

using namespace isaac::math;
// name and group of test
TEST_CASE("Test transform constructor", "[Transform]") {
    //contstruct t1
    Transform t1;

    //required values in t1 to pass
    //needs to be with 10^-6 of the given values
    REQUIRE_THAT(t1.qx, Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(t1.qy, Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(t1.qz, Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(t1.qw, Catch::Matchers::WithinAbs(1.0, 1e-6)); 
    REQUIRE_THAT(t1.tx, Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(t1.ty, Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(t1.tz, Catch::Matchers::WithinAbs(0.0, 1e-6)); 
}

TEST_CASE("Test transform constructor w params", "[Transform]") {
    Transform t1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0);

    REQUIRE_THAT(t1.qx, Catch::Matchers::WithinAbs(1.0, 1e-6)); 
    REQUIRE_THAT(t1.qy, Catch::Matchers::WithinAbs(2.0, 1e-6)); 
    REQUIRE_THAT(t1.qz, Catch::Matchers::WithinAbs(3.0, 1e-6)); 
    REQUIRE_THAT(t1.qw, Catch::Matchers::WithinAbs(4.0, 1e-6)); 
    REQUIRE_THAT(t1.tx, Catch::Matchers::WithinAbs(5.0, 1e-6)); 
    REQUIRE_THAT(t1.ty, Catch::Matchers::WithinAbs(6.0, 1e-6)); 
    REQUIRE_THAT(t1.tz, Catch::Matchers::WithinAbs(7.0, 1e-6)); 
}


TEST_CASE("Test transform =", "[Transform]") {
    Transform t1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0), t2(2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);

    t1 = t2;

    REQUIRE_THAT(t1.qx, Catch::Matchers::WithinAbs(2.0, 1e-6)); 
    REQUIRE_THAT(t1.qy, Catch::Matchers::WithinAbs(3.0, 1e-6)); 
    REQUIRE_THAT(t1.qz, Catch::Matchers::WithinAbs(4.0, 1e-6)); 
    REQUIRE_THAT(t1.qw, Catch::Matchers::WithinAbs(5.0, 1e-6)); 
    REQUIRE_THAT(t1.tx, Catch::Matchers::WithinAbs(6.0, 1e-6)); 
    REQUIRE_THAT(t1.ty, Catch::Matchers::WithinAbs(7.0, 1e-6)); 
    REQUIRE_THAT(t1.tz, Catch::Matchers::WithinAbs(8.0, 1e-6)); 
}

TEST_CASE("Test inverse transform", "[Transform]") {
    
    Transform t1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0);

    t1.inverse();

    REQUIRE_THAT(t1.qx, Catch::Matchers::WithinAbs(-1.0, 1e-6)); 
    REQUIRE_THAT(t1.qy, Catch::Matchers::WithinAbs(-2.0, 1e-6)); 
    REQUIRE_THAT(t1.qz, Catch::Matchers::WithinAbs(-3.0, 1e-6)); 
    REQUIRE_THAT(t1.qw, Catch::Matchers::WithinAbs(4.0, 1e-6)); 
    REQUIRE_THAT(t1.tx, Catch::Matchers::WithinAbs(-118.0, 1e-6)); 
    REQUIRE_THAT(t1.ty, Catch::Matchers::WithinAbs(-100.0, 1e-6)); 
    REQUIRE_THAT(t1.tz, Catch::Matchers::WithinAbs(-274.0, 1e-6)); 
}

TEST_CASE("Test matrix constructor", "[Matrix4x3]") {
    Matrix4x3 m1;

    REQUIRE_THAT(m1.v[0][0], Catch::Matchers::WithinAbs(1.0, 1e-6)); 
    REQUIRE_THAT(m1.v[0][1], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(m1.v[0][2], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(m1.v[1][0], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(m1.v[1][1], Catch::Matchers::WithinAbs(1.0, 1e-6)); 
    REQUIRE_THAT(m1.v[1][2], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(m1.v[2][0], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(m1.v[2][1], Catch::Matchers::WithinAbs(0.0, 1e-6));
    REQUIRE_THAT(m1.v[2][2], Catch::Matchers::WithinAbs(1.0, 1e-6)); 
    REQUIRE_THAT(m1.v[3][0], Catch::Matchers::WithinAbs(0.0, 1e-6));     
    REQUIRE_THAT(m1.v[3][1], Catch::Matchers::WithinAbs(0.0, 1e-6));     
    REQUIRE_THAT(m1.v[3][2], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
}

TEST_CASE("Test matrix =", "[Matrix4x3]") {
    Matrix4x3 m1, m2;
    m2.v[0][0] = 2.0; m2.v[1][1] = 2.0; m2.v[2][2] = 2.0;

    m1 = m2;
    REQUIRE_THAT(m1.v[0][0], Catch::Matchers::WithinAbs(2.0, 1e-6)); 
    REQUIRE_THAT(m1.v[0][1], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(m1.v[0][2], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(m1.v[1][0], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(m1.v[1][1], Catch::Matchers::WithinAbs(2.0, 1e-6)); 
    REQUIRE_THAT(m1.v[1][2], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(m1.v[2][0], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(m1.v[2][1], Catch::Matchers::WithinAbs(0.0, 1e-6));
    REQUIRE_THAT(m1.v[2][2], Catch::Matchers::WithinAbs(2.0, 1e-6)); 
    REQUIRE_THAT(m1.v[3][0], Catch::Matchers::WithinAbs(0.0, 1e-6));     
    REQUIRE_THAT(m1.v[3][1], Catch::Matchers::WithinAbs(0.0, 1e-6));     
    REQUIRE_THAT(m1.v[3][2], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
}


TEST_CASE("Test matrix = constructor", "[Matrix4x3]") {
    Matrix4x3 m2;
    m2.v[0][0] = 2.0; m2.v[1][1] = 2.0; m2.v[2][2] = 2.0;

    Matrix4x3 m1 = m2;
    REQUIRE_THAT(m1.v[0][0], Catch::Matchers::WithinAbs(2.0, 1e-6)); 
    REQUIRE_THAT(m1.v[0][1], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(m1.v[0][2], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(m1.v[1][0], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(m1.v[1][1], Catch::Matchers::WithinAbs(2.0, 1e-6)); 
    REQUIRE_THAT(m1.v[1][2], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(m1.v[2][0], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
    REQUIRE_THAT(m1.v[2][1], Catch::Matchers::WithinAbs(0.0, 1e-6));
    REQUIRE_THAT(m1.v[2][2], Catch::Matchers::WithinAbs(2.0, 1e-6)); 
    REQUIRE_THAT(m1.v[3][0], Catch::Matchers::WithinAbs(0.0, 1e-6));     
    REQUIRE_THAT(m1.v[3][1], Catch::Matchers::WithinAbs(0.0, 1e-6));     
    REQUIRE_THAT(m1.v[3][2], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
}

TEST_CASE("Test matrix set method", "[Matrix4x3]") {
    Matrix4x3 m1;
    Transform t1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0);
    m1.set(t1);

    REQUIRE_THAT(m1.v[0][0], Catch::Matchers::WithinAbs(4.0, 1e-6)); 
    REQUIRE_THAT(m1.v[0][1], Catch::Matchers::WithinAbs(28.0, 1e-6)); 
    REQUIRE_THAT(m1.v[0][2], Catch::Matchers::WithinAbs(-10.0, 1e-6)); 
    REQUIRE_THAT(m1.v[1][0], Catch::Matchers::WithinAbs(-20.0, 1e-6)); 
    REQUIRE_THAT(m1.v[1][1], Catch::Matchers::WithinAbs(10.0, 1e-6)); 
    REQUIRE_THAT(m1.v[1][2], Catch::Matchers::WithinAbs(20.0, 1e-6)); 
    REQUIRE_THAT(m1.v[2][0], Catch::Matchers::WithinAbs(22.0, 1e-6)); 
    REQUIRE_THAT(m1.v[2][1], Catch::Matchers::WithinAbs(4.0, 1e-6));
    REQUIRE_THAT(m1.v[2][2], Catch::Matchers::WithinAbs(20.0, 1e-6)); 
    REQUIRE_THAT(m1.v[3][0], Catch::Matchers::WithinAbs(5.0, 1e-6));     
    REQUIRE_THAT(m1.v[3][1], Catch::Matchers::WithinAbs(6.0, 1e-6));     
    REQUIRE_THAT(m1.v[3][2], Catch::Matchers::WithinAbs(7.0, 1e-6)); 
}

TEST_CASE("Test matrix set method constructor", "[Matrix4x3]") {
    Transform t1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0);
    Matrix4x3 m1(t1);

    REQUIRE_THAT(m1.v[0][0], Catch::Matchers::WithinAbs(4.0, 1e-6)); 
    REQUIRE_THAT(m1.v[0][1], Catch::Matchers::WithinAbs(28.0, 1e-6)); 
    REQUIRE_THAT(m1.v[0][2], Catch::Matchers::WithinAbs(-10.0, 1e-6)); 
    REQUIRE_THAT(m1.v[1][0], Catch::Matchers::WithinAbs(-20.0, 1e-6)); 
    REQUIRE_THAT(m1.v[1][1], Catch::Matchers::WithinAbs(10.0, 1e-6)); 
    REQUIRE_THAT(m1.v[1][2], Catch::Matchers::WithinAbs(20.0, 1e-6)); 
    REQUIRE_THAT(m1.v[2][0], Catch::Matchers::WithinAbs(22.0, 1e-6)); 
    REQUIRE_THAT(m1.v[2][1], Catch::Matchers::WithinAbs(4.0, 1e-6));
    REQUIRE_THAT(m1.v[2][2], Catch::Matchers::WithinAbs(20.0, 1e-6)); 
    REQUIRE_THAT(m1.v[3][0], Catch::Matchers::WithinAbs(5.0, 1e-6));     
    REQUIRE_THAT(m1.v[3][1], Catch::Matchers::WithinAbs(6.0, 1e-6));     
    REQUIRE_THAT(m1.v[3][2], Catch::Matchers::WithinAbs(7.0, 1e-6)); 
}

TEST_CASE("Test vector matrix mul", "[Vector3]") {
    Matrix4x3 m1;
    m1.v[1][1] = 2.0; m1.v[2][2] = 3.0;

    Vector3 v1(1.0, 2.0, 3.0), result;

    v1.mul(m1, result);

    REQUIRE_THAT(result.v[0], Catch::Matchers::WithinAbs(1.0, 1e-6)); 
    REQUIRE_THAT(result.v[1], Catch::Matchers::WithinAbs(4.0, 1e-6)); 
    REQUIRE_THAT(result.v[2], Catch::Matchers::WithinAbs(9.0, 1e-6)); 

}

TEST_CASE("Test vector translate", "[Vector3]") {
    Matrix4x3 m1;
    m1.v[3][0] = 3.0; m1.v[3][1] = 2.0; m1.v[3][2] = 1.0;

    Vector3 v1(1.0, 2.0, 3.0), result;

    v1.trans(m1, result);

    REQUIRE_THAT(result.v[0], Catch::Matchers::WithinAbs(4.0, 1e-6)); 
    REQUIRE_THAT(result.v[1], Catch::Matchers::WithinAbs(4.0, 1e-6)); 
    REQUIRE_THAT(result.v[2], Catch::Matchers::WithinAbs(4.0, 1e-6)); 

}


TEST_CASE("Test vector rotate", "[Vector3]") {
    Matrix4x3 m1;
    m1.v[0][0] = 3.0; m1.v[1][1] = 2.0; m1.v[2][2] = 1.0;

    Vector3 v1(1.0, 2.0, 3.0), result;

    v1.rot(m1, result);

    REQUIRE_THAT(result.v[0], Catch::Matchers::WithinAbs(3.0, 1e-6)); 
    REQUIRE_THAT(result.v[1], Catch::Matchers::WithinAbs(4.0, 1e-6)); 
    REQUIRE_THAT(result.v[2], Catch::Matchers::WithinAbs(3.0, 1e-6)); 

}




























