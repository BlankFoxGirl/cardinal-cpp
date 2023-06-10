#include "UnitTest++/UnitTest++.h"
#include "Cardinal/Global/Physics/Vector3.hpp"
#include <iostream>

using namespace Cardinal::Global::Physics;

SUITE(Vector3Test)
{
    TEST(CanCreateVector3)
    {
        auto entity = Vector3();
        CHECK(true);
    }

    TEST(CanConvertVector3ToString)
    {
        auto entity = Vector3(1, 1, 1);
        CHECK_EQUAL("1.000000,1.000000,1.000000", entity.ToString());
    }

    TEST(CanCreateVectorFromString)
    {
        auto entity = Vector3::FromString("1.000000,1.000000,1.000000");
        CHECK_EQUAL("1.000000,1.000000,1.000000", entity.ToString());
    }

    TEST(CanCalculateTheCorrectDistanceFromAnotherVector3)
    {
        // ToDo: Might be flakey due to float inaccuracies.
        auto entity = Vector3(1, 1, 1);
        auto entity2 = Vector3(10, 10, 10);
        CHECK_EQUAL("15.588457", std::to_string(Vector3::Distance(entity, entity2)));
    }

    TEST(CanGetVectorForwards)
    {
        auto entity = Vector3::Forward();
        auto entity2 = Vector3(0, 0, 1);
        CHECK_EQUAL(entity2.ToString(), entity.ToString());
    }

    TEST(CanGetVectorBackwards)
    {
        auto entity = Vector3::Backward();
        auto entity2 = Vector3(0, 0, -1);
        CHECK_EQUAL(entity2.ToString(), entity.ToString());
    }

    TEST(CanGetVectorUp)
    {
        auto entity = Vector3::Up();
        auto entity2 = Vector3(0, 1, 0);
        CHECK_EQUAL(entity2.ToString(), entity.ToString());
    }

    TEST(CanGetVectorDown)
    {
        auto entity = Vector3::Down();
        auto entity2 = Vector3(0, -1, 0);
        CHECK_EQUAL(entity2.ToString(), entity.ToString());
    }

    TEST(CanGetVectorLeft)
    {
        auto entity = Vector3::Left();
        auto entity2 = Vector3(-1, 0, 0);
        CHECK_EQUAL(entity2.ToString(), entity.ToString());
    }

    TEST(CanGetVectorRight)
    {
        auto entity = Vector3::Right();
        auto entity2 = Vector3(1, 0, 0);
        CHECK_EQUAL(entity2.ToString(), entity.ToString());
    }

    TEST(CanGetVectorZero)
    {
        auto entity = Vector3::Zero();
        auto entity2 = Vector3(0, 0, 0);
        CHECK_EQUAL(entity2.ToString(), entity.ToString());
    }

    TEST(CanGetVectorOne)
    {
        auto entity = Vector3::One();
        auto entity2 = Vector3(1, 1, 1);
        CHECK_EQUAL(entity2.ToString(), entity.ToString());
    }

    TEST(CanDetectIntersectingVectors)
    {
        auto entity = Vector3(1, 1, 1);
        auto entity2 = Vector3(1.5F, 1.5F, 1.5F);
        CHECK(entity.IsIntersecting(entity2, 2));
    }

    TEST(CanDetectNonIntersectingVectors)
    {
        auto entity = Vector3(1, 1, 1);
        auto entity2 = Vector3(10.5F, 10.5F, 10.5F);
        CHECK(entity.IsIntersecting(entity2, 2) == false);
    }

    TEST(CanDetectIntersectingVectorsWithNegativeValues)
    {
        auto entity = Vector3(-1, -1, -1);
        auto entity2 = Vector3(-1.5F, -1.5F, -1.5F);
        CHECK(entity.IsIntersecting(entity2, 2));
    }

    TEST(CanDetectNonIntersectingVectorsWithNegativeValues)
    {
        auto entity = Vector3(-1, -1, -1);
        auto entity2 = Vector3(-10.5F, -10.5F, -10.5F);
        CHECK(entity.IsIntersecting(entity2, 2) == false);
    }

    TEST(CanDetectIntersectingVectorsWithMixedValues)
    {
        auto entity = Vector3(-1, -1, -1);
        auto entity2 = Vector3(1.5F, 1.5F, 1.5F);
        CHECK(entity.IsIntersecting(entity2, 5));
    }

    TEST(CanDetectNonIntersectingVectorsWithMixedValues)
    {
        auto entity = Vector3(-1, -1, -1);
        auto entity2 = Vector3(10.5F, 10.5F, 10.5F);
        CHECK(entity.IsIntersecting(entity2, 2) == false);
    }

    TEST(CanDetectIntersectingVectorsWithMixedValues2)
    {
        auto entity = Vector3(1, 1, 1);
        auto entity2 = Vector3(-1.5F, -1.5F, -1.5F);
        CHECK(entity.IsIntersecting(entity2, 5));
    }

    TEST(CanDetectNonIntersectingVectorsWithMixedValues2)
    {
        auto entity = Vector3(1, 1, 1);
        auto entity2 = Vector3(-10.5F, -10.5F, -10.5F);
        CHECK(entity.IsIntersecting(entity2, 2) == false);
    }

    TEST(CanNormalizeVector)
    {
        auto entity = Vector3(1, 1, 1);
        auto entity2 = Vector3(0.577350F, 0.577350F, 0.577350F);
        CHECK_EQUAL(entity2.ToString(), entity.Normalize().ToString());
    }

    TEST(CanGetMagnitudeOfVector)
    {
        auto entity = Vector3(1, 1, 1);
        CHECK_EQUAL("1.732051", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithNegativeValues)
    {
        auto entity = Vector3(-1, -1, -1);
        CHECK_EQUAL("1.732051", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues)
    {
        auto entity = Vector3(-1, 1, -1);
        CHECK_EQUAL("1.732051", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues2)
    {
        auto entity = Vector3(1, -1, 1);
        CHECK_EQUAL("1.732051", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues3)
    {
        auto entity = Vector3(1, 1, -1);
        CHECK_EQUAL("1.732051", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues4)
    {
        auto entity = Vector3(-1, -1, 1);
        CHECK_EQUAL("1.732051", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues5)
    {
        auto entity = Vector3(1, -1, -1);
        CHECK_EQUAL("1.732051", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues6)
    {
        auto entity = Vector3(-1, 1, 1);
        CHECK_EQUAL("1.732051", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues7)
    {
        auto entity = Vector3(1, 0, 0);
        CHECK_EQUAL("1.000000", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues8)
    {
        auto entity = Vector3(0, 1, 0);
        CHECK_EQUAL("1.000000", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues9)
    {
        auto entity = Vector3(0, 0, 1);
        CHECK_EQUAL("1.000000", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues10)
    {
        auto entity = Vector3(0, 0, 0);
        CHECK_EQUAL("0.000000", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues11)
    {
        auto entity = Vector3(1, 1, 0);
        CHECK_EQUAL("1.414214", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues12)
    {
        auto entity = Vector3(1, 0, 1);
        CHECK_EQUAL("1.414214", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues13)
    {
        auto entity = Vector3(0, 1, 1);
        CHECK_EQUAL("1.414214", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues14)
    {
        auto entity = Vector3(-1, -1, 0);
        CHECK_EQUAL("1.414214", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues15)
    {
        auto entity = Vector3(-1, 0, -1);
        CHECK_EQUAL("1.414214", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues16)
    {
        auto entity = Vector3(0, -1, -1);
        CHECK_EQUAL("1.414214", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues17)
    {
        auto entity = Vector3(1, -1, 0);
        CHECK_EQUAL("1.414214", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues18)
    {
        auto entity = Vector3(1, 0, -1);
        CHECK_EQUAL("1.414214", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues19)
    {
        auto entity = Vector3(0, 1, -1);
        CHECK_EQUAL("1.414214", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues20)
    {
        auto entity = Vector3(-1, 1, 0);
        CHECK_EQUAL("1.414214", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues21)
    {
        auto entity = Vector3(-1, 0, 1);
        CHECK_EQUAL("1.414214", std::to_string(entity.Magnitude()));
    }

    TEST(CanGetMagnitudeOfVectorWithMixedValues22)
    {
        auto entity = Vector3(0, -1, 1);
        CHECK_EQUAL("1.414214", std::to_string(entity.Magnitude()));
    }

    TEST(CanMultiplyVectorByScalar)
    {
        auto entity = Vector3(1, 1, 1);
        auto entity2 = Vector3(2, 2, 2);
        CHECK_EQUAL(entity2.ToString(), (entity * 2).ToString());
    }

    TEST(CanDivideVectorByScalar)
    {
        auto entity = Vector3(1, 1, 1);
        auto entity2 = Vector3(0.5F, 0.5F, 0.5F);
        CHECK_EQUAL(entity2.ToString(), (entity / 2).ToString());
    }

    TEST(CanAddVectorToVector)
    {
        auto entity = Vector3(1, 1, 1);
        auto entity2 = Vector3(2, 2, 2);
        auto entity3 = Vector3(3, 3, 3);
        CHECK_EQUAL(entity3.ToString(), (entity + entity2).ToString());
    }

    TEST(CanSubtractVectorFromVector)
    {
        auto entity = Vector3(1, 1, 1);
        auto entity2 = Vector3(2, 2, 2);
        auto entity3 = Vector3(1, 1, 1);
        CHECK_EQUAL(entity3.ToString(), (entity2 - entity).ToString());
    }

    TEST(CanGetDotProductOfTwoVectors)
    {
        auto entity = Vector3(1, 1, 1);
        auto entity2 = Vector3(2, 2, 2);
        CHECK_EQUAL("6.000000", std::to_string(entity.Dot(entity2)));
    }

    TEST(CanGetCrossProductOfTwoVectors)
    {
        auto entity = Vector3(1, 1, 1);
        auto entity2 = Vector3(2, 2, 2);
        auto entity3 = Vector3(0, 0, 0);
        CHECK_EQUAL(entity3.ToString(), entity.Cross(entity2).ToString());
    }

    TEST(CanGetCrossProductOfTwoVectors2)
    {
        auto entity = Vector3(1, 0, 0);
        auto entity2 = Vector3(0, 1, 0);
        auto entity3 = Vector3(0, 0, 1);
        CHECK_EQUAL(entity3.ToString(), entity.Cross(entity2).ToString());
    }

    TEST(TwoVectorsAreEqual)
    {
        auto entity = Vector3(1, 1, 1);
        auto entity2 = Vector3(1, 1, 1);
        CHECK(entity == entity2);
    }

    TEST(TwoVectorsAreNotEqual)
    {
        auto entity = Vector3(1, 1, 1);
        auto entity2 = Vector3(2, 2, 2);
        CHECK(entity != entity2);
    }

    TEST(VectorCanBeSetToOne)
    {
        auto entity = Vector3(2, 2, 2);
        entity = 1;
        CHECK(entity == Vector3(1, 1, 1));
    }

    TEST(VectorCanBeInverted)
    {
        auto entity = Vector3(2, 2, 2);
        entity = -entity;
        CHECK(entity == Vector3(-2, -2, -2));
    }

    TEST(CanProjectVectorOntoVector)
    {
        auto entity = Vector3(1, 1, 1);
        auto entity2 = Vector3(2, 2, 2);
        CHECK_EQUAL(entity2.ToString(), entity2.Project(entity).ToString());
    }

    TEST(CanReflectVector) {
        auto entity = Vector3(1, 1, 1);
        auto entity2 = Vector3(2, 2, 2);
        CHECK_EQUAL((-entity2).ToString(), entity2.Reflect(entity).ToString());
    }
}
