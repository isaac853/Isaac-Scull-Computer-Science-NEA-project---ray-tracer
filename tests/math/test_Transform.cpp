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



//erroneous tests
//------------------------------------------------------------------

// TEST_CASE("Test erroneous transform constructor w char params", "[Transform]") {
//     Transform t1(a, b, c, d, e, f, g);

//     REQUIRE_THAT(t1.qx, Catch::Matchers::WithinAbs(1.0, 1e-6)); 
//     REQUIRE_THAT(t1.qy, Catch::Matchers::WithinAbs(2.0, 1e-6)); 
//     REQUIRE_THAT(t1.qz, Catch::Matchers::WithinAbs(3.0, 1e-6)); 
//     REQUIRE_THAT(t1.qw, Catch::Matchers::WithinAbs(4.0, 1e-6)); 
//     REQUIRE_THAT(t1.tx, Catch::Matchers::WithinAbs(5.0, 1e-6)); 
//     REQUIRE_THAT(t1.ty, Catch::Matchers::WithinAbs(6.0, 1e-6)); 
//     REQUIRE_THAT(t1.tz, Catch::Matchers::WithinAbs(7.0, 1e-6)); 
// }

// TEST_CASE("Test erroneous transform constructor w too many params", "[Transform]") {
//     Transform t1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);

//     REQUIRE_THAT(t1.qx, Catch::Matchers::WithinAbs(1.0, 1e-6)); 
//     REQUIRE_THAT(t1.qy, Catch::Matchers::WithinAbs(2.0, 1e-6)); 
//     REQUIRE_THAT(t1.qz, Catch::Matchers::WithinAbs(3.0, 1e-6)); 
//     REQUIRE_THAT(t1.qw, Catch::Matchers::WithinAbs(4.0, 1e-6)); 
//     REQUIRE_THAT(t1.tx, Catch::Matchers::WithinAbs(5.0, 1e-6)); 
//     REQUIRE_THAT(t1.ty, Catch::Matchers::WithinAbs(6.0, 1e-6)); 
//     REQUIRE_THAT(t1.tz, Catch::Matchers::WithinAbs(7.0, 1e-6)); 
// }

// TEST_CASE("Test erroneous transform constructor w too few params", "[Transform]") {
//     Transform t1(1.0);

//     REQUIRE_THAT(t1.qx, Catch::Matchers::WithinAbs(1.0, 1e-6)); 
//     REQUIRE_THAT(t1.qy, Catch::Matchers::WithinAbs(2.0, 1e-6)); 
//     REQUIRE_THAT(t1.qz, Catch::Matchers::WithinAbs(3.0, 1e-6)); 
//     REQUIRE_THAT(t1.qw, Catch::Matchers::WithinAbs(4.0, 1e-6)); 
//     REQUIRE_THAT(t1.tx, Catch::Matchers::WithinAbs(5.0, 1e-6)); 
//     REQUIRE_THAT(t1.ty, Catch::Matchers::WithinAbs(6.0, 1e-6)); 
//     REQUIRE_THAT(t1.tz, Catch::Matchers::WithinAbs(7.0, 1e-6)); 
// }

// TEST_CASE("Test erroneous transform =", "[Transform]") {
//     Transform t1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0);
//     floating t2 = 1.0;

//     t1 = t2;

//     REQUIRE_THAT(t1.qx, Catch::Matchers::WithinAbs(2.0, 1e-6)); 
//     REQUIRE_THAT(t1.qy, Catch::Matchers::WithinAbs(3.0, 1e-6)); 
//     REQUIRE_THAT(t1.qz, Catch::Matchers::WithinAbs(4.0, 1e-6)); 
//     REQUIRE_THAT(t1.qw, Catch::Matchers::WithinAbs(5.0, 1e-6)); 
//     REQUIRE_THAT(t1.tx, Catch::Matchers::WithinAbs(6.0, 1e-6)); 
//     REQUIRE_THAT(t1.ty, Catch::Matchers::WithinAbs(7.0, 1e-6)); 
//     REQUIRE_THAT(t1.tz, Catch::Matchers::WithinAbs(8.0, 1e-6)); 
// }

// TEST_CASE("Test erroneous inverse transform", "[Transform]") {
    
//     Transform t1(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

//     t1.inverse();

//     printf("\n %lf \n", t1.qx);
//     printf("%lf \n", t1.qy);
//     printf("%lf \n", t1.qz);
//     printf("%lf \n", t1.qw);
//     printf("%lf \n", t1.tx);
//     printf("%lf \n", t1.ty);
//     printf("%lf \n", t1.tz);


//     REQUIRE_THAT(t1.qx, Catch::Matchers::WithinAbs(-1.0, 1e-6)); 
//     REQUIRE_THAT(t1.qy, Catch::Matchers::WithinAbs(-2.0, 1e-6)); 
//     REQUIRE_THAT(t1.qz, Catch::Matchers::WithinAbs(-3.0, 1e-6)); 
//     REQUIRE_THAT(t1.qw, Catch::Matchers::WithinAbs(4.0, 1e-6)); 
//     REQUIRE_THAT(t1.tx, Catch::Matchers::WithinAbs(-118.0, 1e-6)); 
//     REQUIRE_THAT(t1.ty, Catch::Matchers::WithinAbs(-100.0, 1e-6)); 
//     REQUIRE_THAT(t1.tz, Catch::Matchers::WithinAbs(-274.0, 1e-6)); 
// }

// TEST_CASE("Test erroneous transform constructor w params", "[Transform]") {
//     Transform t1(1.0);

//     REQUIRE_THAT(t1.qx, Catch::Matchers::WithinAbs(1.0, 1e-6)); 
//     REQUIRE_THAT(t1.qy, Catch::Matchers::WithinAbs(2.0, 1e-6)); 
//     REQUIRE_THAT(t1.qz, Catch::Matchers::WithinAbs(3.0, 1e-6)); 
//     REQUIRE_THAT(t1.qw, Catch::Matchers::WithinAbs(4.0, 1e-6)); 
//     REQUIRE_THAT(t1.tx, Catch::Matchers::WithinAbs(5.0, 1e-6)); 
//     REQUIRE_THAT(t1.ty, Catch::Matchers::WithinAbs(6.0, 1e-6)); 
//     REQUIRE_THAT(t1.tz, Catch::Matchers::WithinAbs(7.0, 1e-6)); 
// }

// TEST_CASE("Test erroneous matrix =", "[Matrix4x3]") {
//     Matrix4x3 m1;
//     floating m2 = 1.0;
//     m1 = m2;
//     REQUIRE_THAT(m1.v[0][0], Catch::Matchers::WithinAbs(2.0, 1e-6)); 
//     REQUIRE_THAT(m1.v[0][1], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
//     REQUIRE_THAT(m1.v[0][2], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
//     REQUIRE_THAT(m1.v[1][0], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
//     REQUIRE_THAT(m1.v[1][1], Catch::Matchers::WithinAbs(2.0, 1e-6)); 
//     REQUIRE_THAT(m1.v[1][2], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
//     REQUIRE_THAT(m1.v[2][0], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
//     REQUIRE_THAT(m1.v[2][1], Catch::Matchers::WithinAbs(0.0, 1e-6));
//     REQUIRE_THAT(m1.v[2][2], Catch::Matchers::WithinAbs(2.0, 1e-6)); 
//     REQUIRE_THAT(m1.v[3][0], Catch::Matchers::WithinAbs(0.0, 1e-6));     
//     REQUIRE_THAT(m1.v[3][1], Catch::Matchers::WithinAbs(0.0, 1e-6));     
//     REQUIRE_THAT(m1.v[3][2], Catch::Matchers::WithinAbs(0.0, 1e-6)); 
// }

// TEST_CASE("Test erroneous vector matrix mul with bad result", "[Vector3]") {
//     Matrix4x3 m1;

//     Vector3 v1(1.0, 2.0, 3.0);
//     floating result = 0.0;

//     v1.mul(m1, result);

//     REQUIRE_THAT(result.v[0], Catch::Matchers::WithinAbs(1.0, 1e-6)); 
//     REQUIRE_THAT(result.v[1], Catch::Matchers::WithinAbs(4.0, 1e-6)); 
//     REQUIRE_THAT(result.v[2], Catch::Matchers::WithinAbs(9.0, 1e-6)); 

// }

// TEST_CASE("Test vector translate", "[Vector3]") {
  

//     Vector3 v1(1.0, 2.0, 3.0), result, m1;

//     v1.trans(m1, result);

//     REQUIRE_THAT(result.v[0], Catch::Matchers::WithinAbs(4.0, 1e-6)); 
//     REQUIRE_THAT(result.v[1], Catch::Matchers::WithinAbs(4.0, 1e-6)); 
//     REQUIRE_THAT(result.v[2], Catch::Matchers::WithinAbs(4.0, 1e-6)); 

// }

TEST_CASE("Test erroneous vector translate", "[Vector3]") {
    Matrix4x3 m1;

    Vector3 v1(1.0, 2.0, 3.0);
    floating result = 0.0;
    printf("\n %lf \n", result);

    //v1.trans(m1, result);

    // REQUIRE_THAT(result.v[0], Catch::Matchers::WithinAbs(4.0, 1e-6)); 
    // REQUIRE_THAT(result.v[1], Catch::Matchers::WithinAbs(4.0, 1e-6)); 
    // REQUIRE_THAT(result.v[2], Catch::Matchers::WithinAbs(4.0, 1e-6)); 
    REQUIRE(false);
}


