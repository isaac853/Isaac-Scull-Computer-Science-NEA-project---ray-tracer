#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "math/Vector3.hpp"
#include <iostream>
#include <stdio.h>

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
 

TEST_CASE("Test squared vector method","[vector3]") {
    Vector3 v1(1.0, 2.0, 3.0);

    v1.squared();

    REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(1.0, 1e-6));
    REQUIRE_THAT(v1.v[1], Catch::Matchers::WithinAbs(4.0, 1e-6));
    REQUIRE_THAT(v1.v[2], Catch::Matchers::WithinAbs(9.0, 1e-6));
}

TEST_CASE("Test squared vector method w result","[vector3]") {
    Vector3 v1(1.0, 2.0, 3.0), result;

    v1.squared(result);

    REQUIRE_THAT(result.v[0], Catch::Matchers::WithinAbs(1.0, 1e-6));
    REQUIRE_THAT(result.v[1], Catch::Matchers::WithinAbs(4.0, 1e-6));
    REQUIRE_THAT(result.v[2], Catch::Matchers::WithinAbs(9.0, 1e-6));
}

TEST_CASE("Test lengthsquared vector method","[vector3]") {
    Vector3 v1(1.0, 2.0, 3.0);
    floating length;
    length = v1.lengthSquared();
    REQUIRE_THAT(length, Catch::Matchers::WithinAbs(14.0, 1e-6));
}

// //erroneous tests, should cause error so comment when not using



// TEST_CASE("Test 3d vector constructor fail", "[vector3]") {
//     //erroneous constructor
//     isaac::math::Vector3 v1("a","b","c"); 

//     //should always return true, but error should occur before this runs
//     REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(v1.v[0], 1e-6)); 
//}

// TEST_CASE("erroneous test", "[vector3]") {
//     isaac::math::Vector3 v1(1.0, 2.0, 3.0,4.0); 

//     REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(v1.v[0], 1e-6)); 
// }

// TEST_CASE("erroneous test", "[vector3]") {
//     isaac::math::Vector3 v1(1.0); 

//     REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(v1.v[0], 1e-6)); 
// }

// TEST_CASE("erroneous test", "[vector3]") {
//     isaac::math::Vector3 v1(1.0, 2.0, 3.0), v2(1.0, 2.0, 3.0);
//     floating result;
//     v1.add(v2, result);

//     REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(v1.v[0], 1e-6)); 
// }

// TEST_CASE("erroneous test", "[vector3]") {
//     isaac::math::Vector3 v1(1.0, 2.0, 3.0), result;
//     floating v2
//     v1.add(v2, result);

//     REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(v1.v[0], 1e-6)); 
// }

// TEST_CASE("erroneous test", "[vector3]") {
//     isaac::math::Vector3 v1(1.0, 2.0, 3.0), v2(1.0, 2.0, 3.0);
//     floating result;
//     v1.sub(v2, result);

//     REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(v1.v[0], 1e-6)); 
// }

// TEST_CASE("erroneous test", "[vector3]") {
//     isaac::math::Vector3 v1(1.0, 2.0, 3.0), result;
//     floating v2
//     v1.sub(v2, result);

//     REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(v1.v[0], 1e-6)); 
// }

// TEST_CASE("erroneous test", "[vector3]") {
//     isaac::math::Vector3 v1(1.0, 2.0, 3.0), v2(1.0, 2.0, 3.0);
//     floating result;
//     v1.mul(v2, result);

//     REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(v1.v[0], 1e-6)); 
// }

// TEST_CASE("erroneous test", "[vector3]") {
//     isaac::math::Vector3 v1(1.0, 2.0, 3.0);
//     isaac::math::floating scal(3.0);
//     v1.mul(scal);

// //     REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(v1.v[0], 1e-6)); 
// // }

// TEST_CASE("erroneous test", "[vector3]") {
//     isaac::math::Vector3 v1(1.0, 2.0, 3.0), v2(1.0, 2.0, 3.0), result;

//     v1.dot(v2, result);

//     REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(v1.v[0], 1e-6)); 
// }

// TEST_CASE("erroneous test", "[vector3]") {
//     isaac::math::Vector3 v1(1.0, 2.0, 3.0);
//     floating v2;
//     v1.dot(v2, result);

//     REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(v1.v[0], 1e-6)); 
// }

// TEST_CASE("erroneous test", "[vector3]") {
//     isaac::math::Vector3 v1(1.0, 2.0, 3.0), v2(1.0, 2.0, 3.0);
//     floating result;
//     v1.crossv2, result);

//     REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(v1.v[0], 1e-6)); 
// }

// TEST_CASE("erroneous test", "[vector3]") {
//     isaac::math::Vector3 v1(1.0, 2.0, 3.0), result;
//     floating v2;
//     v1.cross(v2, result);

//     REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(v1.v[0], 1e-6)); 
// }



TEST_CASE("erroneous test", "[vector3]") {

    isaac::math::Vector3 v1;
    
    bool error;
    v1.normalise(v1, error);

    REQUIRE(true == error); 


}

TEST_CASE("new normalise test", "[vector3]") {
    isaac::math::Vector3 v1(0.0, 0.0, 5.0);
    
    bool error;
    v1.normalise(v1, error);

    REQUIRE(false == error); 


}

// TEST_CASE("erroneous test", "[vector3]") {
//     isaac::math::Vector3 v1(1.0, 2.0, 3.0);
//     floating v2(1.0);

//     v1 = v2

//     REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(v1.v[0], 1e-6)); 
// }

// TEST_CASE("Test erroneous squared vector method","[vector3]") {
//     Vector3 v1(a);

//     v1.squared();

//     REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(1.0, 1e-6));
//     REQUIRE_THAT(v1.v[1], Catch::Matchers::WithinAbs(4.0, 1e-6));
//     REQUIRE_THAT(v1.v[2], Catch::Matchers::WithinAbs(9.0, 1e-6));
// }

// TEST_CASE("Test erroneous squared vector method w result","[vector3]") {
//     Vector3 v1(1.0, 2.0, 3.0);
//     floating result = 1.0;

//     v1.squared(result);

//     REQUIRE_THAT(v1.v[0], Catch::Matchers::WithinAbs(1.0, 1e-6));
//     REQUIRE_THAT(v1.v[1], Catch::Matchers::WithinAbs(4.0, 1e-6));
//     REQUIRE_THAT(v1.v[2], Catch::Matchers::WithinAbs(9.0, 1e-6));
// }

// TEST_CASE("Test erroneous lengthsquared vector method","[vector3]") {
//     Vector3 v1(a);
//     floating length;
//     length = v1.lengthSquared();
//     REQUIRE_THAT(length, Catch::Matchers::WithinAbs(14.0, 1e-6));
// }