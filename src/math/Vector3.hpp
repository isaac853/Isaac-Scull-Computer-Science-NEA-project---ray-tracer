#pragma once

#include <cstddef>
#include "mathtypes.hpp"
#include "Matrix4x3.hpp"

namespace isaac::math
{
    class Vector3
    {
    public:
        floating v[3];

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

        /// @brief Dot product with another vector
        /// @param vec Other vector
        /// @param result Resulting Vector3
        Vector3 &dot(Vector3 &vec, Vector3 &result)
        {
            // Dot product
            const floating v0 = v[0] * vec.v[0];
            const floating v1 = v[1] * vec.v[1];
            const floating v2 = v[2] * vec.v[2];

            // Set result at the end to allow in-place multiplication
            result.v[0] = v0;
            result.v[1] = v1;
            result.v[2] = v2;

            return result;
        }

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

        /// @brief Multiply this vector by a 4x3 matrix (affine transform)
        /// @param m Matrix4x3 to multiply by
        /// @param result Resulting Vector3
        Vector3 &mul(Matrix4x3 &m, Vector3 &result)
        {
            const floating(&r)[4][3] = m.v;

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
    };

} // namespace isaac::math
