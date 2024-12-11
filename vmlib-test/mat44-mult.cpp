#include <catch2/catch_amalgamated.hpp>

#include <numbers>

#include "../vmlib/mat44.hpp"

TEST_CASE("4x4 matrix by matrix multiplication", "[mat44]")
{
    static constexpr float kEps_ = 1e-6f;

    using namespace Catch::Matchers;

    // Test identity matrix multiplication
    SECTION("Identity matrix multiplication")
    {
        auto const matA = kIdentity44f;
        auto const matB = kIdentity44f;
        auto const result = matA * matB;

        for (std::size_t i = 0; i < 4; ++i)
        {
            for (std::size_t j = 0; j < 4; ++j)
            {
                REQUIRE_THAT(result(i, j), WithinAbs(kIdentity44f(i, j), kEps_));
            }
        }
    }

    // Test multiplication of a rotation and scaling matrix
    SECTION("Rotation and scaling matrix multiplication")
    {
        auto const rotation = make_rotation_z(std::numbers::pi_v<float> / 4.f); // 45-degree rotation
        auto const scaling = make_scaling(2.f, 2.f, 2.f); // Scaling by 2 on all axes
        auto const result = rotation * scaling;

        REQUIRE_THAT(result(0, 0), WithinAbs(std::sqrt(2.f), kEps_));
        REQUIRE_THAT(result(0, 1), WithinAbs(-std::sqrt(2.f), kEps_));
        REQUIRE_THAT(result(1, 0), WithinAbs(std::sqrt(2.f), kEps_));
        REQUIRE_THAT(result(1, 1), WithinAbs(std::sqrt(2.f), kEps_));
        REQUIRE_THAT(result(2, 2), WithinAbs(2.f, kEps_));
        REQUIRE_THAT(result(3, 3), WithinAbs(1.f, kEps_));
    }

    // Test multiplication of a translation and rotation matrix
    SECTION("Translation and rotation matrix multiplication")
    {
        auto const rotation = make_rotation_x(std::numbers::pi_v<float> / 2.f); // 90-degree rotation around X-axis
        auto const translation = make_translation({1.f, 2.f, 3.f});
        auto const result = rotation * translation;

        REQUIRE_THAT(result(0, 3), WithinAbs(1.f, kEps_));
        REQUIRE_THAT(result(1, 3), WithinAbs(-3.f, kEps_));
        REQUIRE_THAT(result(2, 3), WithinAbs(2.f, kEps_));
        REQUIRE_THAT(result(3, 3), WithinAbs(1.f, kEps_));
    }
}

TEST_CASE("4x4 matrix by vector multiplication", "[mat44][vec4]")
{
    static constexpr float kEps_ = 1e-6f;

    using namespace Catch::Matchers;

    // Test multiplication by the identity matrix
    SECTION("Identity matrix multiplication")
    {
        Vec4f vec = {1.f, 2.f, 3.f, 1.f};
        auto const result = kIdentity44f * vec;

        REQUIRE_THAT(result.x, WithinAbs(vec.x, kEps_));
        REQUIRE_THAT(result.y, WithinAbs(vec.y, kEps_));
        REQUIRE_THAT(result.z, WithinAbs(vec.z, kEps_));
        REQUIRE_THAT(result.w, WithinAbs(vec.w, kEps_));
    }

    // Test multiplication by a translation matrix
    SECTION("Translation matrix multiplication")
    {
        Vec4f vec = {1.f, 1.f, 1.f, 1.f};
        auto const translation = make_translation({2.f, 3.f, 4.f});
        auto const result = translation * vec;

        REQUIRE_THAT(result.x, WithinAbs(3.f, kEps_));
        REQUIRE_THAT(result.y, WithinAbs(4.f, kEps_));
        REQUIRE_THAT(result.z, WithinAbs(5.f, kEps_));
        REQUIRE_THAT(result.w, WithinAbs(1.f, kEps_));
    }

    // Test multiplication by a scaling matrix
    SECTION("Scaling matrix multiplication")
    {
        Vec4f vec = {1.f, 1.f, 1.f, 1.f};
        auto const scaling = make_scaling(2.f, 3.f, 4.f);
        auto const result = scaling * vec;

        REQUIRE_THAT(result.x, WithinAbs(2.f, kEps_));
        REQUIRE_THAT(result.y, WithinAbs(3.f, kEps_));
        REQUIRE_THAT(result.z, WithinAbs(4.f, kEps_));
        REQUIRE_THAT(result.w, WithinAbs(1.f, kEps_));
    }

    // Test multiplication by a rotation matrix
    SECTION("Rotation matrix multiplication")
    {
        Vec4f vec = {1.f, 0.f, 0.f, 1.f};
        auto const rotation = make_rotation_z(std::numbers::pi_v<float> / 2.f); // 90-degree rotation
        auto const result = rotation * vec;

        REQUIRE_THAT(result.x, WithinAbs(0.f, kEps_));
        REQUIRE_THAT(result.y, WithinAbs(1.f, kEps_));
        REQUIRE_THAT(result.z, WithinAbs(0.f, kEps_));
        REQUIRE_THAT(result.w, WithinAbs(1.f, kEps_));
    }
}
