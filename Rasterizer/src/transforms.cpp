#include "transforms.h"

#include "CGL/matrix3x3.h"
#include "CGL/vector2D.h"
#include "CGL/vector3D.h"

namespace CGL {

Vector2D operator*(const Matrix3x3 &m, const Vector2D &v) {
	Vector3D mv = m * Vector3D(v.x, v.y, 1);
	return Vector2D(mv.x / mv.z, mv.y / mv.z);
}

Matrix3x3 translate(float dx, float dy) {
	// Part 3: Fill this in.
    Matrix3x3 translation = Matrix3x3::identity();
    translation(0, 2) = dx;
    translation(1, 2) = dy;

    return translation;
}

Matrix3x3 scale(float sx, float sy) {
	// Part 3: Fill this in.
    Matrix3x3 scaleM = Matrix3x3::identity();
    scaleM(0, 0) = sx;
    scaleM(1, 1) = sy;

	return scaleM;
}

// The input argument is in degrees counterclockwise
Matrix3x3 rotate(float deg) {
	// Part 3: Fill this in.
    Matrix3x3 rotation = Matrix3x3::identity();
    rotation(0, 0) = cos(radians(deg));
    rotation(0, 1) = -sin(radians(deg));
    rotation(1, 0) = sin(radians(deg));
    rotation(1, 1) = cos(radians(deg));

	return rotation;
}

}
