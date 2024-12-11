// You will need to define your own tests. Refer to CW1 or Exercise G.3 for
// examples.

#include <catch2/catch_amalgamated.hpp>

#include <numbers>

#include "../vmlib/mat44.hpp"

// https://github.com/catchorg/Catch2/blob/devel/docs/comparing-floating-point-numbers.md#top


TEST_CASE("4x4 rotation matrices", "[rotation][mat44]") {
    static constexpr float kEps_ = 1e-6f;
    using namespace Catch::Matchers;

    // Helper to validate if a matrix is close to identity
    auto is_identity = [&](Mat44f const& mat) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                float expected = (i == j) ? 1.f : 0.f;
                REQUIRE_THAT(mat(i, j), WithinAbs(expected, kEps_));
            }
        }
    };

    SECTION("Rotation around Z-axis") {
        SECTION("Identity") {
            auto identity = make_rotation_z(0.f);
            is_identity(identity);
        }

        SECTION("90 degrees") {
            auto rot90 = make_rotation_z(std::numbers::pi_v<float> / 2.f);

            REQUIRE_THAT(rot90(0, 0), WithinAbs(0.f, kEps_));
            REQUIRE_THAT(rot90(0, 1), WithinAbs(-1.f, kEps_));
            REQUIRE_THAT(rot90(1, 0), WithinAbs(1.f, kEps_));
            REQUIRE_THAT(rot90(1, 1), WithinAbs(0.f, kEps_));
        }

        SECTION("-90 degrees") {
            auto rotMinus90 = make_rotation_z(-std::numbers::pi_v<float> / 2.f);

            REQUIRE_THAT(rotMinus90(0, 0), WithinAbs(0.f, kEps_));
            REQUIRE_THAT(rotMinus90(0, 1), WithinAbs(1.f, kEps_));
            REQUIRE_THAT(rotMinus90(1, 0), WithinAbs(-1.f, kEps_));
            REQUIRE_THAT(rotMinus90(1, 1), WithinAbs(0.f, kEps_));
        }

        SECTION("180 degrees") {
            auto rot180 = make_rotation_z(std::numbers::pi_v<float>);

            REQUIRE_THAT(rot180(0, 0), WithinAbs(-1.f, kEps_));
            REQUIRE_THAT(rot180(0, 1), WithinAbs(0.f, kEps_));
            REQUIRE_THAT(rot180(1, 0), WithinAbs(0.f, kEps_));
            REQUIRE_THAT(rot180(1, 1), WithinAbs(-1.f, kEps_));
        }

        SECTION("Full rotation (360 degrees)") {
            auto rot360 = make_rotation_z(2.f * std::numbers::pi_v<float>);
            is_identity(rot360);
        }
    }

    SECTION("Rotation around X-axis") {
        SECTION("Identity") {
            auto identity = make_rotation_x(0.f);
            is_identity(identity);
        }

        SECTION("90 degrees") {
            auto rot90 = make_rotation_x(std::numbers::pi_v<float> / 2.f);

            REQUIRE_THAT(rot90(1, 1), WithinAbs(0.f, kEps_));
            REQUIRE_THAT(rot90(1, 2), WithinAbs(-1.f, kEps_));
            REQUIRE_THAT(rot90(2, 1), WithinAbs(1.f, kEps_));
            REQUIRE_THAT(rot90(2, 2), WithinAbs(0.f, kEps_));
        }

        SECTION("180 degrees") {
            auto rot180 = make_rotation_x(std::numbers::pi_v<float>);

            REQUIRE_THAT(rot180(1, 1), WithinAbs(-1.f, kEps_));
            REQUIRE_THAT(rot180(1, 2), WithinAbs(0.f, kEps_));
            REQUIRE_THAT(rot180(2, 1), WithinAbs(0.f, kEps_));
            REQUIRE_THAT(rot180(2, 2), WithinAbs(-1.f, kEps_));
        }

        SECTION("Full rotation (360 degrees)") {
            auto rot360 = make_rotation_x(2.f * std::numbers::pi_v<float>);
            is_identity(rot360);
        }
    }

    SECTION("Rotation around Y-axis") {
        SECTION("Identity") {
            auto identity = make_rotation_y(0.f);
            is_identity(identity);
        }

        SECTION("90 degrees") {
            auto rot90 = make_rotation_y(std::numbers::pi_v<float> / 2.f);

            REQUIRE_THAT(rot90(0, 0), WithinAbs(0.f, kEps_));
            REQUIRE_THAT(rot90(0, 2), WithinAbs(1.f, kEps_));
            REQUIRE_THAT(rot90(2, 0), WithinAbs(-1.f, kEps_));
            REQUIRE_THAT(rot90(2, 2), WithinAbs(0.f, kEps_));
        }

        SECTION("180 degrees") {
            auto rot180 = make_rotation_y(std::numbers::pi_v<float>);

            REQUIRE_THAT(rot180(0, 0), WithinAbs(-1.f, kEps_));
            REQUIRE_THAT(rot180(0, 2), WithinAbs(0.f, kEps_));
            REQUIRE_THAT(rot180(2, 0), WithinAbs(0.f, kEps_));
            REQUIRE_THAT(rot180(2, 2), WithinAbs(-1.f, kEps_));
        }

        SECTION("Full rotation (360 degrees)") {
            auto rot360 = make_rotation_y(2.f * std::numbers::pi_v<float>);
            is_identity(rot360);
        }
    }

}

