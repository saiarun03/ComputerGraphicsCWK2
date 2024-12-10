#ifndef MAT44_HPP_E7187A26_469E_48AD_A3D2_63150F05A4CA
#define MAT44_HPP_E7187A26_469E_48AD_A3D2_63150F05A4CA
// SOLUTION_TAGS: gl-(ex-[^12]|cw-2)

#include <cmath>
#include <cassert>
#include <cstdlib>

#include "vec3.hpp"
#include "vec4.hpp"

/** Mat44f: 4x4 matrix with floats
 *
 * See vec2f.hpp for discussion. Similar to the implementation, the Mat44f is
 * intentionally kept simple and somewhat bare bones.
 *
 * The matrix is stored in row-major order (careful when passing it to OpenGL).
 *
 * The overloaded operator () allows access to individual elements. Example:
 *    Mat44f m = ...;
 *    float m12 = m(1,2);
 *    m(0,3) = 3.f;
 *
 * The matrix is arranged as:
 *
 *   ⎛ 0,0  0,1  0,2  0,3 ⎞
 *   ⎜ 1,0  1,1  1,2  1,3 ⎟
 *   ⎜ 2,0  2,1  2,2  2,3 ⎟
 *   ⎝ 3,0  3,1  3,2  3,3 ⎠
 */
struct Mat44f
{
	float v[16];

	constexpr
	float& operator() (std::size_t aI, std::size_t aJ) noexcept
	{
		assert( aI < 4 && aJ < 4 );
		return v[aI*4 + aJ];
	}
	constexpr
	float const& operator() (std::size_t aI, std::size_t aJ) const noexcept
	{
		assert( aI < 4 && aJ < 4 );
		return v[aI*4 + aJ];
	}
};

// Identity matrix
constexpr Mat44f kIdentity44f = { {
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f
} };

// Common operators for Mat44f.
// Note that you will need to implement these yourself.

constexpr
Mat44f operator*( Mat44f const& aLeft, Mat44f const& aRight ) noexcept
{
	//TODO: your implementation goes here
	//TODO: remove the following when you start your implementation
    Mat44f result = kIdentity44f; // Copy the original matrix structure

    for (std::size_t i = 0; i < 4; ++i) {
        for (std::size_t j = 0; j < 4; ++j) {
            result(i, j) = 0.f; // Ensure initialization for sum
            for (std::size_t k = 0; k < 4; ++k) {
                result(i, j) += aLeft(i, k) * aRight(k, j);
            }
        }
    }

    return result; // Return the newly computed matrix

	// (void)aLeft;   // Avoid warnings about unused arguments until the function
	// (void)aRight;  // is properly implemented.
	// return kIdentity44f;
}

constexpr
Vec4f operator*( Mat44f const& aLeft, Vec4f const& aRight ) noexcept
{
	//TODO: your implementation goes here
	//TODO: remove the following when you start your implementation
    Vec4f result = { 0.f, 0.f, 0.f, 0.f }; // Initialize result vector to zero

    for (std::size_t i = 0; i < 4; ++i) {
        for (std::size_t j = 0; j < 4; ++j) {
            result[i] += aLeft(i, j) * aRight[j];
        }
    }

    return result; // Return the resultant vector

	// (void)aLeft;   // Avoid warnings about unused arguments until the function
	// (void)aRight;  // is properly implemented.
	// return { 0.f, 0.f, 0.f, 0.f };
}


// Functions:


inline
Mat44f make_rotation_x( float aAngle ) noexcept
{
	//TODO: your implementation goes here
	//TODO: remove the following when you start your implementation
    Mat44f result = kIdentity44f; // Copy original identity matrix

    float ca = std::cos(aAngle);
    float sa = std::sin(aAngle);

    result(1, 1) = ca;
    result(1, 2) = -sa;
    result(2, 1) = sa;
    result(2, 2) = ca;

    return result; // Return the modified matrix

	// (void)aAngle; // Avoid warnings about unused arguments until the function
	//               // is properly implemented.
	// return kIdentity44f;
}


inline
Mat44f make_rotation_y( float aAngle ) noexcept
{
	//TODO: your implementation goes here
	//TODO: remove the following when you start your implementation
    Mat44f result = kIdentity44f; // Copy original identity matrix

    float ca = std::cos(aAngle);
    float sa = std::sin(aAngle);

    result(0, 0) = ca;
    result(0, 2) = sa;
    result(2, 0) = -sa;
    result(2, 2) = ca;

    return result; // Return the modified matrix

	// (void)aAngle; // Avoid warnings about unused arguments until the function
	//               // is properly implemented.
	// return kIdentity44f;
}

inline
Mat44f make_rotation_z( float aAngle ) noexcept
{
	//TODO: your implementation goes here
	//TODO: remove the following when you start your implementation
    Mat44f result = kIdentity44f; // Copy original identity matrix

    float ca = std::cos(aAngle);
    float sa = std::sin(aAngle);

    result(0, 0) = ca;
    result(0, 1) = -sa;
    result(1, 0) = sa;
    result(1, 1) = ca;

    return result; // Return the modified matrix

	// (void)aAngle; // Avoid warnings about unused arguments until the function
	//               // is properly implemented.
	// return kIdentity44f;
}

inline
Mat44f make_translation( Vec3f aTranslation ) noexcept
{
	//TODO: your implementation goes here
	//TODO: remove the following when you start your implementation
    Mat44f result = kIdentity44f; // Copy original identity matrix

    result(0, 3) = aTranslation.x;
    result(1, 3) = aTranslation.y;
    result(2, 3) = aTranslation.z;

    return result; // Return the modified translation matrix

	// (void)aTranslation; // Avoid warnings about unused arguments until the function
	//                     // is properly implemented.
	// return kIdentity44f;
}
inline
Mat44f make_scaling( float aSX, float aSY, float aSZ ) noexcept
{
	//TODO: your implementation goes here
	//TODO: remove the following when you start your implementation
	(void)aSX;  // Avoid warnings about unused arguments until the function
	(void)aSY;  // is properly implemented.
	(void)aSZ;
	return kIdentity44f;
}

inline
Mat44f make_perspective_projection( float aFovInRadians, float aAspect, float aNear, float aFar ) noexcept
{
	//TODO: your implementation goes here
	//TODO: remove the following when you start your implementation
    Mat44f result = {}; // Start with a zero matrix to explicitly fill all fields

    float s = 1.f / std::tan(aFovInRadians / 2.f); // Scale factor for FOV
    float a = -(aFar + aNear) / (aFar - aNear);
    float b = -(2.f * aFar * aNear) / (aFar - aNear);

    result(0, 0) = s / aAspect; // Scale along the x-axis
    result(1, 1) = s;          // Scale along the y-axis
    result(2, 2) = a;          // Depth scale
    result(2, 3) = b;          // Depth translation
    result(3, 2) = -1.f;       // Perspective division term

    return result; // Return the perspective projection matrix


	// (void)aFovInRadians; // Avoid warnings about unused arguments until the function
	// (void)aAspect;       // is properly implemented.
	// (void)aNear;
	// (void)aFar;
	// return kIdentity44f;
}

#endif // MAT44_HPP_E7187A26_469E_48AD_A3D2_63150F05A4CA
