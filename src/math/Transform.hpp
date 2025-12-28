#pragma once

#include <cstddef>
#include "mathtypes.hpp"
#include <cmath>

namespace isaac::math
{
    // 3D Transform class: rotation (quaternion) + translation
    class Transform
    {
    public:
        /// @brief Quaternion (x, y, z, w) and translation (x, y, z) components
        // Quaternion for ratation should be normalized
        // Rotation represented as (qx, qy, qz, qw)
        // Translation represented as (tx, ty, tz)
        // The values are public for easy access as I see no reason to hide them.
        floating qx, qy, qz, qw; // Quaternion rotation
        floating tx, ty, tz;     // Translation

        /// @brief Set to identity transform
        void setIdentity()
        {
            // Identity rotation (no rotation)
            qx = 0.0;
            qy = 0.0;
            qz = 0.0;
            qw = 1.0;
            // Zero translation
            tx = 0.0;
            ty = 0.0;
            tz = 0.0;
        }

        /// @brief Default constructor initializes to identity transform
        Transform()
        {
            setIdentity();
        }

        /// @brief Constructor with specified quaternion and translation
        Transform(floating qx_, floating qy_, floating qz_, floating qw_,
                  floating tx_, floating ty_, floating tz_)
            : qx(qx_), qy(qy_), qz(qz_), qw(qw_), tx(tx_), ty(ty_), tz(tz_)
        {
        }

        /// @brief Set rotation from axis-angle representation
        /// @param ux X component of rotation axis (should be normalized)
        /// @param uy Y component of rotation axis (should be normalized)
        /// @param uz Z component of rotation axis (should be normalized)
        /// @param theta Rotation angle in radians
        void rotate(floating ux, floating uy, floating uz, floating theta)
        {
            const floating sinTheta = std::sin(theta / 2);
            const floating cosTheta = std::cos(theta / 2);

            qx = ux * sinTheta;
            qy = uy * sinTheta;
            qz = uz * sinTheta;
            qw = cosTheta;
            tx = 0;
            ty = 0;
            tz = 0;
        }

        /// @brief Compute the inverse of this transform
        /// @param result Output parameter to store the inverse transform
        /// @return Reference to the result transform
        Transform &inverse(Transform &result)
        {
            // Invert quaternion (rotation)
            const floating qxn = -qx;
            const floating qyn = -qy;
            const floating qzn = -qz;
            const floating qwn = qw;

            // Apply inverted rotation to inverted translation
            const floating xx = qxn * qxn;
            const floating yy = qyn * qyn;
            const floating zz = qzn * qzn;
            const floating xy = qxn * qyn;
            const floating xz = qxn * qzn;
            const floating yz = qyn * qzn;
            const floating wx = qwn * qxn;
            const floating wy = qwn * qyn;
            const floating wz = qwn * qzn;
            const floating ww = qwn * qwn;

            const floating v00 = ww + xx - yy - zz;
            const floating v10 = 2 * (xy - wz);
            const floating v20 = 2 * (xz + wy);
            const floating v01 = 2 * (xy + wz);
            const floating v11 = ww - xx + yy - zz;
            const floating v21 = 2 * (yz - wx);

            const floating v02 = 2 * (xz - wy);
            const floating v12 = 2 * (yz + wx);
            const floating v22 = ww - xx - yy + zz;
            const floating v0 =
                v00 * tx +
                v10 * ty +
                v20 * tz;

            const floating v1 =
                v01 * tx +
                v11 * ty +
                v21 * tz;

            const floating v2 =
                v02 * tx +
                v12 * ty +
                v22 * tz;

            const floating txn = -v0;
            const floating tyn = -v1;
            const floating tzn = -v2;

            // Set result at the end to allow in-place inversion
            result.qx = qxn;
            result.qy = qyn;
            result.qz = qzn;
            result.qw = qwn;
            result.tx = txn;
            result.ty = tyn;
            result.tz = tzn;

            return result;
        }

        /// @brief In-place inversion of this transform
        void inverse()
        {
            inverse(*this);
        }

        /// @brief Set rotation and translation from Euler angles and translation
        /// @param a Rotation angle around X axis in radians
        /// @param b Rotation angle around Y axis in radians
        /// @param c Rotation angle around Z axis in radians
        /// @param x Translation along X axis
        /// @param y Translation along Y axis
        /// @param z Translation along Z axis
        void rotateTranslate(
            const floating a,
            const floating b,
            const floating c,
            const floating x,
            const floating y,
            const floating z)
        {
            const floating sa = std::sin(a / 2);
            const floating ca = std::cos(a / 2);
            const floating sb = std::sin(b / 2);
            const floating cb = std::cos(b / 2);
            const floating sc = std::sin(c / 2);
            const floating cc = std::cos(c / 2);

            qx = (sa * cb * cc) - (ca * sb * sc);
            qy = (ca * sb * cc) + (sa * cb * sc);
            qz = (ca * cb * sc) - (sa * sb * cc);
            qw = (ca * cb * cc) + (sa * sb * sc);

            tx = x;
            ty = y;
            tz = z;
        }

        /// @brief Set rotation from axis-angle and translation
        /// @param ux X component of rotation axis (should be normalized)
        /// @param uy Y component of rotation axis (should be normalized)
        /// @param uz Z component of rotation axis (should be normalized)
        /// @param theta Rotation angle in radians
        /// @param tx_ Translation along X axis
        /// @param ty_ Translation along Y axis
        /// @param tz_ Translation along Z axis
        void rotateTranslate(
            const floating ux,
            const floating uy,
            const floating uz,
            const floating theta,
            const floating tx_,
            const floating ty_,
            const floating tz_)
        {
            const floating sinTheta = std::sin(theta / 2);
            const floating cosTheta = std::cos(theta / 2);

            qx = ux * sinTheta;
            qy = uy * sinTheta;
            qz = uz * sinTheta;
            qw = cosTheta;
            tx = tx_;
            ty = ty_;
            tz = tz_;
        }

        /**
         * Premultiply by t: result := t * this
         */
        Transform &mul(const Transform &t, Transform &result)
        {
            // Quaternion multiplication
            const floating qwn = (t.qw * qw) - (t.qx * qx) - (t.qy * qy) - (t.qz * qz);
            const floating qxn = (t.qw * qx) + (t.qx * qw) + (t.qy * qz) - (t.qz * qy);
            const floating qyn = (t.qw * qy) - (t.qx * qz) + (t.qy * qw) + (t.qz * qx);
            const floating qzn = (t.qw * qz) + (t.qx * qy) - (t.qy * qx) + (t.qz * qw);

            // Apply rotation t to translation of this transform
            const floating w = t.qw;
            const floating x = t.qx;
            const floating y = t.qy;
            const floating z = t.qz;

            const floating xx = x * x;
            const floating yy = y * y;
            const floating zz = z * z;
            const floating ww = w * w;
            const floating xy = x * y;
            const floating xz = x * z;
            const floating yz = y * z;
            const floating wx = w * x;
            const floating wy = w * y;
            const floating wz = w * z;

            const floating v00 = ww + xx - yy - zz;
            const floating v10 = 2 * (xy - wz);
            const floating v20 = 2 * (xz + wy);

            const floating v01 = 2 * (xy + wz);
            const floating v11 = ww - xx + yy - zz;
            const floating v21 = 2 * (yz - wx);

            const floating v02 = 2 * (xz - wy);
            const floating v12 = 2 * (yz + wx);
            const floating v22 = ww - xx - yy + zz;

            const floating v0 =
                v00 * tx +
                v10 * ty +
                v20 * tz;

            const floating v1 =
                v01 * tx +
                v11 * ty +
                v21 * tz;

            const floating v2 =
                v02 * tx +
                v12 * ty +
                v22 * tz;

            const floating txn = t.tx + v0;
            const floating tyn = t.ty + v1;
            const floating tzn = t.tz + v2;

            // Set result at the end to allow in-place multiplication
            result.qx = qxn;
            result.qy = qyn;
            result.qz = qzn;
            result.qw = qwn;
            result.tx = txn;
            result.ty = tyn;
            result.tz = tzn;

            return result;
        }

        // @brief Normalize the quaternion part of the transform
        // Used to ensure valid rotation representation in face of accumulated numerical errors
        void mop()
        {
            // Normalize quaternion
            if ((qw < 1) && (qw > -1))
            {
                const floating theta = std::acos(qw);
                const floating oldSinTheta = std::sin(theta);

                const floating ux = qx / oldSinTheta;
                const floating uy = qy / oldSinTheta;
                const floating uz = qz / oldSinTheta;

                const floating l = std::sqrt((ux * ux) + (uy * uy) + (uz * uz));
                const floating uxn = ux / l;
                const floating uyn = uy / l;
                const floating uzn = uz / l;

                const floating sinTheta = std::sin(theta);
                const floating cosTheta = std::cos(theta);

                qx = uxn * sinTheta;
                qy = uyn * sinTheta;
                qz = uzn * sinTheta;
                qw = cosTheta;
            }
            else
            {
                qw = 1;
                qx = 0;
                qy = 0;
                qz = 0;
            }
        }
    };
} // namespace isaac::math
