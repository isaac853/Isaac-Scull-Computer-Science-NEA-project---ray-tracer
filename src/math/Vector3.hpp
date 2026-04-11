#pragma once

#include <cstddef>  //allows std functions
#include <iostream> //allows cout

#include "mathtypes.hpp"
#include "Matrix4x3.hpp"

namespace isaac::math
{
    class Vector3
    {
    public:
        floating v[3]; // attribute definition, put in public for ease of use

        /// @brief Default constructor initializes to zero vector
        Vector3()
        {
            v[0] = 0.0;
            v[1] = 0.0;
            v[2] = 0.0;
        }

        /// @brief Constructor with specified components
        Vector3(floating x, floating y, floating z)
        {
            v[0] = x;
            v[1] = y;
            v[2] = z;
        }

        /// @brief multiply vector with another vector
        /// @param vec Other vector
        /// @param result Resulting Vector3
        Vector3 &mul(Vector3 &vec, Vector3 &result)
        {
            // multiplication
            const floating v0 = v[0] * vec.v[0];
            const floating v1 = v[1] * vec.v[1];
            const floating v2 = v[2] * vec.v[2];

            // Set result at the end to allow in-place multiplication
            result.v[0] = v0;
            result.v[1] = v1;
            result.v[2] = v2;

            return result;
        }

        /// @brief multiply vector with a scalar
        /// @param vec Other vector
        /// @param result Resulting Vector3
        Vector3 &mul(floating scalar, Vector3 &result)
        {
            // multiplication
            const floating v0 = v[0] * scalar;
            const floating v1 = v[1] * scalar;
            const floating v2 = v[2] * scalar;

            // Set result at the end to allow in-place multiplication
            result.v[0] = v0;
            result.v[1] = v1;
            result.v[2] = v2;

            return result;
        }

        floating lengthSquared(){
            return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
        }

        // TODO check me
        /// @brief Cross product with another vector
        /// @param vec Other vector
        /// @param result Resulting Vector3
        Vector3 &cross(Vector3 &vec, Vector3 &result)
        {
            const floating v0 = (v[1] * vec.v[2]) - (v[2] * vec.v[1]);
            const floating v1 = (v[2] * vec.v[0]) - (v[0] * vec.v[2]);
            const floating v2 = (v[0] * vec.v[1]) - (v[1] * vec.v[0]);

            // Set result at the end to allow in-place multiplication
            result.v[0] = v0;
            result.v[1] = v1;
            result.v[2] = v2;

            return result;
        }

        /// @brief add vector with another vector
        /// @param vec Other vector
        /// @param result Resulting Vector3
        Vector3 &add(Vector3 &vec, Vector3 &result)
        {
            // addition
            const floating v0 = v[0] + vec.v[0];
            const floating v1 = v[1] + vec.v[1];
            const floating v2 = v[2] + vec.v[2];

            // Set result at the end to allow in-place addition
            result.v[0] = v0;
            result.v[1] = v1;
            result.v[2] = v2;

            return result;
        }

        /// @brief add vector with another vector
        /// @param vec Other vector
        /// @param result Resulting Vector3
        Vector3 &add(Vector3 &vec)
        {
            return add(vec, *this);
        }        

        Vector3 &sub(Vector3 &vec, Vector3 &result)
        {
            // subtraction
            const floating v0 = v[0] - vec.v[0];
            const floating v1 = v[1] - vec.v[1];
            const floating v2 = v[2] - vec.v[2];

            // Set result at the end to allow in-place subtraction
            result.v[0] = v0;
            result.v[1] = v1;
            result.v[2] = v2;

            return result;
        }

        Vector3 &sub(Vector3 &vec)
        {
            return sub(vec, *this);
        }  
        
        
        /// @brief Multiply this vector by a 4x3 matrix (affine transform)
        /// @param m Matrix4x3 to multiply by
        /// @param result Resulting Vector3
        Vector3 &mul(Matrix4x3 &m, Vector3 &result)
        {
            const floating(&r)[4][3] = m.v; //r copies v's values

            const floating v0 =
                r[0][0] * v[0] +
                r[1][0] * v[1] +
                r[2][0] * v[2] +
                r[3][0];

            const floating v1 =
                r[0][1] * v[0] +
                r[1][1] * v[1] +
                r[2][1] * v[2] +
                r[3][1];

            const floating v2 =
                r[0][2] * v[0] +
                r[1][2] * v[1] +
                r[2][2] * v[2] +
                r[3][2];

            // Set result at the end to allow in-place multiplication
            result.v[0] = v0;
            result.v[1] = v1;
            result.v[2] = v2;

            return result;
        }

        /// @brief Translate this vector by a 4x3 matrix (affine transform)
        /// @param m Matrix4x3 to multiply by
        /// @param result Resulting Vector3
        Vector3 &trans(Matrix4x3 &m, Vector3 &result)
        {
            const floating(&r)[4][3] = m.v;

            const floating v0 =
                r[3][0];

            const floating v1 =
                r[3][1];

            const floating v2 =
                r[3][2];

            // Set result at the end to allow in-place multiplication
            result.v[0] = v0 + v[0];
            result.v[1] = v1 + v[1];
            result.v[2] = v2 + v[2];

            return result;
        }



        /// @brief dot vector with another vector
        /// @param vec Other vector
        /// @param result Resulting scalar
        floating dot(Vector3 &vec)
        {
            // multiplication
            const floating v0 = v[0] * vec.v[0];
            const floating v1 = v[1] * vec.v[1];
            const floating v2 = v[2] * vec.v[2];

            // addition
            const floating result = v0 + v1 + v2;
            
            return result;
        }        

        
        /// @brief make vector into unit vector
        /// @param result Resulting Vector3
        Vector3 &normalise(Vector3 &result, bool &error)
        {   //asigned to existing memory locations for faster performance

            const floating length = sqrt((v[0]*v[0]) + (v[1]*v[1]) + (v[2]*v[2]));
            const floating length_reciprocal = 1.0/length;
            
            // multiplication
            const floating v0 = v[0] * length_reciprocal;
            const floating v1 = v[1] * length_reciprocal;
            const floating v2 = v[2] * length_reciprocal;

            // Set result at the end to allow in-place multiplication
            result.v[0] = v0;
            result.v[1] = v1;
            result.v[2] = v2;

            error = length == 0.0;


            return result;
        }

        /// @brief make vector into unit vector
        /// @param result Resulting Vector3
        Vector3 &normalise(Vector3 &result){
            bool error;
            return normalise(result, error);
        }


        Vector3 &normalise() {
            return normalise(*this);
        }

        // =
        inline Vector3& operator=(const Vector3& other){
            v[0] = other.v[0];
            v[1] = other.v[1];
            v[2] = other.v[2];            
            return *this;
        }

        /// @brief square vector
        /// @param result Resulting Vector3
        Vector3 &squared(Vector3 &result)
        {   //asigned to existing memory locations for faster performance
            return mul(*this, result);
        }

        /// @brief square vector
        Vector3 &squared()
        {   //asigned to existing memory locations for faster performance
            return squared(*this);
        }

        // Just do the vector rotation (not translation)
        // Useful for transforming direction vectors
        Vector3 rot( Matrix4x3& m, Vector3& result )
        {
            const floating(&r)[4][3] = m.v;

            floating v0 =
            r[ 0 ][ 0 ] * v[ 0 ] +
            r[ 1 ][ 0 ] * v[ 1 ] +
            r[ 2 ][ 0 ] * v[ 2 ];

            floating v1 =
            r[ 0 ][ 1 ] * v[ 0 ] +
            r[ 1 ][ 1 ] * v[ 1 ] +
            r[ 2 ][ 1 ] * v[ 2 ];

            floating v2 =
            r[ 0 ][ 2 ] * v[ 0 ] +
            r[ 1 ][ 2 ] * v[ 1 ] +
            r[ 2 ][ 2 ] * v[ 2 ];

            result.v[ 0 ] = v0;
            result.v[ 1 ] = v1;
            result.v[ 2 ] = v2;

            return result;
        }

        inline void set(floating num1, floating num2, floating num3){
            v[0] = num1;
            v[1] = num2;
            v[2] = num3;
        }

    // ---------------------------------------------------------------------------------------------------------
    }; //end of Vector3

    inline std::ostream& operator<<(std::ostream& os, const Vector3& v) {
        os 
            << "(" 
            << v.v[0] << ","
            << v.v[1] << ","
            << v.v[2]
            << ")";
        return os;
    }


} // namespace isaac::math
