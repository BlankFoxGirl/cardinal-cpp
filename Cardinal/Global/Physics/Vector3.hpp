#ifndef CARDINAL_GLOBAL_PHYSICS_VECTOR3_HPP
#define CARDINAL_GLOBAL_PHYSICS_VECTOR3_HPP
#include <math.h>
#include "Cardinal/Global/Utility.hpp"

namespace Cardinal::Global::Physics {
    struct Vector3 {
        float x;
        float y;
        float z;

        Vector3() = default;

        Vector3(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        Vector3(int x, int y, int z) {
            this->x = (float)x;
            this->y = (float)y;
            this->z = (float)z;
        }

        /* Static Helpers */
        static float Distance(Vector3 V1, Vector3 V2) {
            return V1.DistanceFrom(V2);
        }

        static Vector3 Forward() {
            return Vector3(0, 0, 1);
        }

        static Vector3 Backward() {
            return Vector3(0, 0, -1);
        }

        static Vector3 Up() {
            return Vector3(0, 1, 0);
        }

        static Vector3 Down() {
            return Vector3(0, -1, 0);
        }

        static Vector3 Left() {
            return Vector3(-1, 0, 0);
        }

        static Vector3 Right() {
            return Vector3(1, 0, 0);
        }

        static Vector3 Zero() {
            return Vector3(0, 0, 0);
        }

        static Vector3 One() {
            return Vector3(1, 1, 1);
        }

        static Vector3 Clone(Vector3 Vector) {
            return Vector3(Vector.x, Vector.y, Vector.z);
        }

        /* Helpers */
        Vector3 Clone() {
            return Vector3(this->x, this->y, this->z);
        }

        float DistanceFrom(Vector3 Vector) {
            return sqrtf(powf(Vector.x - this->x, 2) + powf(Vector.y - this->y, 2) + powf(Vector.z - this->z, 2));
        }

        Vector3 Lerp(Vector3 V2, float t) {
            return Vector3(this->x + (V2.x - this->x) * t, this->y + (V2.y - this->y) * t, this->z + (V2.z - this->z) * t);
        }

        Vector3 LerpUnclamped(Vector3 V2, float t) {
            return Vector3(this->x + (V2.x - this->x) * t, this->y + (V2.y - this->y) * t, this->z + (V2.z - this->z) * t);
        }

        Vector3 MoveTowards(Vector3 V2, float t) {
            return Vector3(this->x + (V2.x - this->x) * t, this->y + (V2.y - this->y) * t, this->z + (V2.z - this->z) * t);
        }

        Vector3 Scale(Vector3 V2) {
            return Vector3(this->x * V2.x, this->y * V2.y, this->z * V2.z);
        }

        Vector3 Cross(Vector3 V2) {
            return Vector3(this->y * V2.z - this->z * V2.y, this->z * V2.x - this->x * V2.z, this->x * V2.y - this->y * V2.x);
        }

        float Dot(Vector3 V2) {
            return this->x * V2.x + this->y * V2.y + this->z * V2.z;
        }

        Vector3 Project(Vector3 V2) {
            return V2 * (this->Dot(V2) / V2.Dot(V2));
        }

        Vector3 Reflect(Vector3 V2) {
            auto V1 = this->Clone();
            return V1 - (V2 * (2 * this->Dot(V2) / V2.Dot(V2)));
        }

        Vector3 Normalize() {
            auto V1 = this->Clone();
            return V1 / this->DistanceFrom(Vector3::Zero());
        }

        Vector3 ClampMagnitude(float MaxLength) {
            auto V1 = this->Clone();
            if (this->DistanceFrom(Vector3::Zero()) > MaxLength) {
                return V1 / this->DistanceFrom(Vector3::Zero()) * MaxLength;
            }

            return V1;
        }

        float Magnitude() {
            return this->DistanceFrom(Vector3::Zero());
        }

        float SqrMagnitude() {
            return powf(this->DistanceFrom(Vector3::Zero()), 2);
        }

        float LengthSquared() {
            return this->SqrMagnitude();
        }

        /* Operators */

        Vector3 operator-(const Vector3 V2) const {
            return Vector3(this->x - V2.x, this->y - V2.y, this->z - V2.z);
        }

        Vector3 operator+(const Vector3 V2) {
            return Vector3(this->x + V2.x, this->y + V2.y, this->z + V2.z);
        }

        Vector3 operator*(const Vector3 V2) {
            return Vector3(this->x * V2.x, this->y * V2.y, this->z * V2.z);
        }

        Vector3 operator*(const float floatValue) {
            return Vector3(this->x * floatValue, this->y * floatValue, this->z * floatValue);
        }

        Vector3 operator/(const Vector3 V2) {
            return Vector3(this->x / V2.x, this->y / V2.y, this->z / V2.z);
        }

        Vector3 operator/(const float floatValue) {
            return Vector3(this->x / floatValue, this->y / floatValue, this->z / floatValue);
        }

        Vector3 operator+=(const Vector3 V2) {
            return Vector3(this->x += V2.x, this->y += V2.y, this->z += V2.z);
        }

        Vector3 operator-=(const Vector3 V2) {
            return Vector3(this->x -= V2.x, this->y -= V2.y, this->z -= V2.z);
        }

        Vector3 operator*=(const Vector3 V2) {
            return Vector3(this->x *= V2.x, this->y *= V2.y, this->z *= V2.z);
        }

        Vector3 operator*=(const float floatValue) {
            return Vector3(this->x *= floatValue, this->y *= floatValue, this->z *= floatValue);
        }

        Vector3 operator/=(const Vector3 V2) {
            return Vector3(this->x /= V2.x, this->y /= V2.y, this->z /= V2.z);
        }

        Vector3 operator/=(const float floatValue) {
            return Vector3(this->x /= floatValue, this->y /= floatValue, this->z /= floatValue);
        }

        bool operator==(const Vector3 V2) {
            return this->x == V2.x && this->y == V2.y && this->z == V2.z;
        }

        bool operator!=(const Vector3 V2) {
            return this->x != V2.x || this->y != V2.y || this->z != V2.z;
        }

        Vector3 operator-() {
            return Vector3(-this->x, -this->y, -this->z);
        }

        Vector3 operator-(const Vector3 V2) {
            return Vector3(this->x - V2.x, this->y - V2.y, this->z - V2.z);
        }

        Vector3 operator=(const Vector3 V2) {
            return Vector3(this->x = V2.x, this->y = V2.y, this->z = V2.z);
        }

        Vector3 operator=(const float floatValue) {
            return Vector3(this->x = floatValue, this->y = floatValue, this->z = floatValue);
        }

        Vector3 operator=(const int intValue) {
            return Vector3(this->x = intValue, this->y = intValue, this->z = intValue);
        }

        Vector3 operator=(const double doubleValue) {
            return Vector3(this->x = doubleValue, this->y = doubleValue, this->z = doubleValue);
        }

        std::string ToString() {
            return std::to_string(this->x) + ","
                + std::to_string(this->y) + ","
                + std::to_string(this->z);
        }

        Vector3 static FromString(std::string String) {
            auto Values = Cardinal::Global::Utility::Split(String, ",");
            return Vector3(std::stof(Values[0]), std::stof(Values[1]), std::stof(Values[2]));
        }
    };
}

#endif