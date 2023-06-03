#ifndef CARDINAL_GLOBAL_PHYSICS_QUATERNION_HPP
#define CARDINAL_GLOBAL_PHYSICS_QUATERNION_HPP

#include "Vector3.hpp"
namespace Cardinal::Global::Physics
{
    struct Quaternion
    {
        int x;
        int y;
        int z;
        int w;

        Quaternion() = default;

        Quaternion(int x, int y, int z, int w)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        static Quaternion FromEuler(float x, float y, float z)
        {
            auto V1 = Vector3(x, y, z);

            return FromEuler(V1);
        }

        static Quaternion FromEulerString(std::string euler)
        {
            auto V1 = Vector3::FromString(euler);

            return FromEuler(V1);
        }

        static Quaternion FromEuler(Vector3 euler)
        {
            float x = euler.x;
            float y = euler.y;
            float z = euler.z;

            float cy = cosf(z * 0.5f);
            float sy = sinf(z * 0.5f);
            float cp = cosf(y * 0.5f);
            float sp = sinf(y * 0.5f);
            float cr = cosf(x * 0.5f);
            float sr = sinf(x * 0.5f);

            Quaternion returnQuaternion;
            returnQuaternion.w = cr * cp * cy + sr * sp * sy;
            returnQuaternion.x = sr * cp * cy - cr * sp * sy;
            returnQuaternion.y = cr * sp * cy + sr * cp * sy;
            returnQuaternion.z = cr * cp * sy - sr * sp * cy;

            return returnQuaternion;
        }

        Vector3 ToEuler()
        {
            float sqw = w * w;
            float sqx = x * x;
            float sqy = y * y;
            float sqz = z * z;

            float unit = sqx + sqy + sqz + sqw;
            float test = x * y + z * w;

            Vector3 returnVector;

            if (test > 0.499f * unit)
            {
                returnVector.y = 2.0f * atan2f(x, w);
                returnVector.x = M_PI / 2.0f;
                returnVector.z = 0.0f;
                return returnVector;
            }

            if (test < -0.499f * unit)
            {
                returnVector.y = -2.0f * atan2f(x, w);
                returnVector.x = -M_PI / 2.0f;
                returnVector.z = 0.0f;
                return returnVector;
            }

            returnVector.y = atan2f(2.0f * y * w - 2.0f * x * z, sqx - sqy - sqz + sqw);
            returnVector.x = asinf(2.0f * test / unit);
            returnVector.z = atan2f(2.0f * x * w - 2.0f * y * z, -sqx + sqy - sqz + sqw);

            return returnVector;
        }

        std::string ToEulerString()
        {
            Vector3 euler = ToEuler();

            return euler.ToString();
        }

        bool IsLookingAt(Vector3 target)
        {
            Vector3 forward = Vector3::Forward();
            Vector3 direction = target - forward;

            Vector3 euler = ToEuler();

            float yaw = euler.y;
            float pitch = euler.x;

            float x = cosf(yaw) * cosf(pitch);
            float y = sinf(yaw) * cosf(pitch);
            float z = sinf(pitch);

            Vector3 forwardVector = Vector3(x, y, z);

            return forwardVector.DistanceFrom(direction) < 0.1f;
        }

        static Quaternion Slerp(Quaternion q1, Quaternion q2, float t)
        {
            float cosHalfTheta = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;

            if (abs(cosHalfTheta) >= 1.0f)
            {
                return q1;
            }

            float halfTheta = acosf(cosHalfTheta);
            float sinHalfTheta = sqrtf(1.0f - cosHalfTheta * cosHalfTheta);

            if (fabsf(sinHalfTheta) < 0.001f)
            {
                Quaternion returnQuaternion;
                returnQuaternion.w = (q1.w * 0.5f + q2.w * 0.5f);
                returnQuaternion.x = (q1.x * 0.5f + q2.x * 0.5f);
                returnQuaternion.y = (q1.y * 0.5f + q2.y * 0.5f);
                returnQuaternion.z = (q1.z * 0.5f + q2.z * 0.5f);
                return returnQuaternion;
            }

            float ratioA = sinf((1.0f - t) * halfTheta) / sinHalfTheta;
            float ratioB = sinf(t * halfTheta) / sinHalfTheta;

            Quaternion returnQuaternion;
            returnQuaternion.w = (q1.w * ratioA + q2.w * ratioB);
            returnQuaternion.x = (q1.x * ratioA + q2.x * ratioB);
            returnQuaternion.y = (q1.y * ratioA + q2.y * ratioB);
            returnQuaternion.z = (q1.z * ratioA + q2.z * ratioB);
            return returnQuaternion;
        }

        static Quaternion Lerp(Quaternion q1, Quaternion q2, float t)
        {
            float cosHalfTheta = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;

            if (abs(cosHalfTheta) >= 1.0f)
            {
                return q1;
            }

            float halfTheta = acosf(cosHalfTheta);
            float sinHalfTheta = sqrtf(1.0f - cosHalfTheta * cosHalfTheta);

            if (fabsf(sinHalfTheta) < 0.001f)
            {
                Quaternion returnQuaternion;
                returnQuaternion.w = (q1.w * 0.5f + q2.w * 0.5f);
                returnQuaternion.x = (q1.x * 0.5f + q2.x * 0.5f);
                returnQuaternion.y = (q1.y * 0.5f + q2.y * 0.5f);
                returnQuaternion.z = (q1.z * 0.5f + q2.z * 0.5f);
                return returnQuaternion;
            }

            float ratioA = sinf((1.0f - t) * halfTheta) / sinHalfTheta;
            float ratioB = sinf(t * halfTheta) / sinHalfTheta;

            Quaternion returnQuaternion;
            returnQuaternion.w = (q1.w * ratioA + q2.w * ratioB);
            returnQuaternion.x = (q1.x * ratioA + q2.x * ratioB);
            returnQuaternion.y = (q1.y * ratioA + q2.y * ratioB);
            returnQuaternion.z = (q1.z * ratioA + q2.z * ratioB);
            return returnQuaternion;
        }

        static Quaternion FromToRotation(Vector3 from, Vector3 to)
        {
            float dot = from.Dot(to);
            float w = sqrtf(from.LengthSquared() * to.LengthSquared()) + dot;

            Quaternion returnQuaternion;
            returnQuaternion.w = w;
            returnQuaternion.x = from.y * to.z - from.z * to.y;
            returnQuaternion.y = from.z * to.x - from.x * to.z;
            returnQuaternion.z = from.x * to.y - from.y * to.x;
            return returnQuaternion;
        }
    };
}

#endif