#pragma once

#include <cstddef>
#include "mathtypes.hpp"
#include "Transform.hpp"

namespace isaac::math
{
    /// @brief 4x3 Matrix class for affine transformations (linear)
    // just for rotation and translation
    class Matrix4x3
    {
    public:
        floating v[4][3]; //2d array with floating type values set to v short for values
   
        /// @brief Default constructor initializes to identity matrix
        Matrix4x3()
        {
            // Initialize to identity matrix
            v[0][0] = 1.0; v[0][1] = 0.0; v[0][2] = 0.0; // top 3 rows are rotation
            v[1][0] = 0.0; v[1][1] = 1.0; v[1][2] = 0.0;
            v[2][0] = 0.0; v[2][1] = 0.0; v[2][2] = 1.0;
            v[3][0] = 0.0; v[3][1] = 0.0; v[3][2] = 0.0; //bottom row is translation
        }

        /// @brief Assignment operator
        Matrix4x3 &operator=(const Matrix4x3 &other)
        {
            for (std::size_t i = 0; i < 4; ++i)
            {
                for (std::size_t j = 0; j < 3; ++j)
                {
                    v[i][j] = other.v[i][j];
                }
            }
            return *this;
        }

        /// @brief Copy constructor
        /// @param other Matrix4x3 to copy from
        Matrix4x3(const Matrix4x3 &other)
        {
            *this = other;
        }
        
        
        /// @brief Set matrix from a Transform object
        /// @param t Transform to set from  
        void set(Transform &t)
        {
            const floating x = t.qx;
            const floating y = t.qy;
            const floating z = t.qz;
            const floating w = t.qw;
            
            const floating xx = x * x;
            const floating yy = y * y;
            const floating zz = z * z;
            const floating xy = x * y;
            const floating xz = x * z;
            const floating yz = y * z;
            const floating wx = w * x;
            const floating wy = w * y;
            const floating wz = w * z;
            const floating ww = w * w;
            
            v[0][0] = ww + xx - yy - zz;
            v[1][0] = 2 * (xy - wz);
            v[2][0] = 2 * (xz + wy);
            v[3][0] = t.tx;
            
            v[0][1] = 2 * (xy + wz);
            v[1][1] = ww - xx + yy - zz;
            v[2][1] = 2 * (yz - wx);
            v[3][1] = t.ty;
            
            v[0][2] = 2 * (xz - wy);
            v[1][2] = 2 * (yz + wx);
            v[2][2] = ww - xx - yy + zz;
            v[3][2] = t.tz;
        }
        
        /// @brief Constructor from a Transform object
        /// @param t Transform to construct from
        Matrix4x3(Transform &t)
        {
            set(t);
        }
    };
    
} // namespace isaac::math
