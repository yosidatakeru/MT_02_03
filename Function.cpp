﻿#include "Function.h"
#include <cassert>
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include  <math.h>

#include <Vector2.h>
#include <imgui.h>

Vector3 Add(const Vector3 m1, const Vector3 m2) {
	Vector3 result = {

		m1.x + m2.x,
		m1.y + m2.y,
		m1.z + m2.z,
	};

	return result;
}

Vector3 Subtract(const Vector3 m1, const Vector3 m2) {
	Vector3 result = {};

	result.x = m1.x - m2.x;
	result.y = m1.y - m2.y;
	result.z = m1.z - m2.z;

	return result;

}

Vector3 Vector3Multiply(const Vector3 v1, const Vector3 v2) {
	Vector3 result = { v1.x * v2.x,v1.y * v2.y,v1.z * v2.z };
	return result;
}

//Scale
Matrix4x4 MakeScaleMatrix(const Vector3 scale) {
	Matrix4x4 result = {};
	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;


	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;


	return result;
}

//Rotate
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result = {};

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = -(std::sin(radian));
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result = {};

	result.m[0][0] = std::cos(radian);
	result.m[0][1] = 0.0f;
	result.m[0][2] = -(std::sin(radian));
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = std::sin(radian);
	result.m[2][1] = 0.0f;
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result = {};

	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = -(std::sin(radian));
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

//AllRotate
Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ) {
	Matrix4x4 result;

	Matrix4x4 rotateMatrixX = MakeRotateXMatrix(radianX);
	Matrix4x4 rotateMatrixY = MakeRotateYMatrix(radianY);
	Matrix4x4 rotateMatrixZ = MakeRotateZMatrix(radianZ);



	result = Multiply(rotateMatrixX, Multiply(rotateMatrixY, rotateMatrixZ));

	return result;

}



Matrix4x4 Multiply(const Matrix4x4 m1, const Matrix4x4 m2) {
	Matrix4x4 result = {};
	result.m[0][0] = (m1.m[0][0] * m2.m[0][0]) + (m1.m[0][1] * m2.m[1][0]) + (m1.m[0][2] * m2.m[2][0]) + (m1.m[0][3] * m2.m[3][0]);
	result.m[0][1] = (m1.m[0][0] * m2.m[0][1]) + (m1.m[0][1] * m2.m[1][1]) + (m1.m[0][2] * m2.m[2][1]) + (m1.m[0][3] * m2.m[3][1]);
	result.m[0][2] = (m1.m[0][0] * m2.m[0][2]) + (m1.m[0][1] * m2.m[1][2]) + (m1.m[0][2] * m2.m[2][2]) + (m1.m[0][3] * m2.m[3][2]);
	result.m[0][3] = (m1.m[0][0] * m2.m[0][3]) + (m1.m[0][1] * m2.m[1][3]) + (m1.m[0][2] * m2.m[2][3]) + (m1.m[0][3] * m2.m[3][3]);

	result.m[1][0] = (m1.m[1][0] * m2.m[0][0]) + (m1.m[1][1] * m2.m[1][0]) + (m1.m[1][2] * m2.m[2][0]) + (m1.m[1][3] * m2.m[3][0]);
	result.m[1][1] = (m1.m[1][0] * m2.m[0][1]) + (m1.m[1][1] * m2.m[1][1]) + (m1.m[1][2] * m2.m[2][1]) + (m1.m[1][3] * m2.m[3][1]);
	result.m[1][2] = (m1.m[1][0] * m2.m[0][2]) + (m1.m[1][1] * m2.m[1][2]) + (m1.m[1][2] * m2.m[2][2]) + (m1.m[1][3] * m2.m[3][2]);
	result.m[1][3] = (m1.m[1][0] * m2.m[0][3]) + (m1.m[1][1] * m2.m[1][3]) + (m1.m[1][2] * m2.m[2][3]) + (m1.m[1][3] * m2.m[3][3]);

	result.m[2][0] = (m1.m[2][0] * m2.m[0][0]) + (m1.m[2][1] * m2.m[1][0]) + (m1.m[2][2] * m2.m[2][0]) + (m1.m[2][3] * m2.m[3][0]);
	result.m[2][1] = (m1.m[2][0] * m2.m[0][1]) + (m1.m[2][1] * m2.m[1][1]) + (m1.m[2][2] * m2.m[2][1]) + (m1.m[2][3] * m2.m[3][1]);
	result.m[2][2] = (m1.m[2][0] * m2.m[0][2]) + (m1.m[2][1] * m2.m[1][2]) + (m1.m[2][2] * m2.m[2][2]) + (m1.m[2][3] * m2.m[3][2]);
	result.m[2][3] = (m1.m[2][0] * m2.m[0][3]) + (m1.m[2][1] * m2.m[1][3]) + (m1.m[2][2] * m2.m[2][3]) + (m1.m[2][3] * m2.m[3][3]);

	result.m[3][0] = (m1.m[3][0] * m2.m[0][0]) + (m1.m[3][1] * m2.m[1][0]) + (m1.m[3][2] * m2.m[2][0]) + (m1.m[3][3] * m2.m[3][0]);
	result.m[3][1] = (m1.m[3][0] * m2.m[0][1]) + (m1.m[3][1] * m2.m[1][1]) + (m1.m[3][2] * m2.m[2][1]) + (m1.m[3][3] * m2.m[3][1]);
	result.m[3][2] = (m1.m[3][0] * m2.m[0][2]) + (m1.m[3][1] * m2.m[1][2]) + (m1.m[3][2] * m2.m[2][2]) + (m1.m[3][3] * m2.m[3][2]);
	result.m[3][3] = (m1.m[3][0] * m2.m[0][3]) + (m1.m[3][1] * m2.m[1][3]) + (m1.m[3][2] * m2.m[2][3]) + (m1.m[3][3] * m2.m[3][3]);


	return result;


}



//Translate
Matrix4x4 MakeTranslateMatrix(Vector3 translate) {
	Matrix4x4 result = {};
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;


	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;


	return result;
}


//Transform
Vector3 Transform(const Vector3 vector, const Matrix4x4 matrix) {
	Vector3 result = {};

	result.x = (vector.x * matrix.m[0][0]) + (vector.y * matrix.m[1][0]) + (vector.z * matrix.m[2][0]) + (1.0f * matrix.m[3][0]);
	result.y = (vector.x * matrix.m[0][1]) + (vector.y * matrix.m[1][1]) + (vector.z * matrix.m[2][1]) + (1.0f * matrix.m[3][1]);
	result.z = (vector.x * matrix.m[0][2]) + (vector.y * matrix.m[1][2]) + (vector.z * matrix.m[2][2]) + (1.0f * matrix.m[3][2]);

	float w = (vector.x * matrix.m[0][3]) + (vector.y * matrix.m[1][3]) + (vector.z * matrix.m[2][3]) + (1.0f * matrix.m[3][3]);


	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;


}

Matrix4x4 Inverse(const Matrix4x4 m) {
	float MatrixFormula;
	MatrixFormula =
		+(m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3])
		+ (m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1])
		+ (m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2])

		- (m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1])
		- (m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3])
		- (m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2])

		- (m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3])
		- (m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1])
		- (m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2])

		+ (m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1])
		+ (m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3])
		+ (m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2])

		+ (m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3])
		+ (m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1])
		+ (m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2])


		- (m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1])
		- (m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3])
		- (m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2])

		- (m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0])
		- (m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0])
		- (m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0])

		+ (m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0])
		+ (m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0])
		+ (m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]);

	Matrix4x4 result = {};



	result.m[0][0] = (1 / MatrixFormula) * (
		+(m.m[1][1] * m.m[2][2] * m.m[3][3])
		+ (m.m[1][2] * m.m[2][3] * m.m[3][1])
		+ (m.m[1][3] * m.m[2][1] * m.m[3][2])
		- (m.m[1][3] * m.m[2][2] * m.m[3][1])
		- (m.m[1][2] * m.m[2][1] * m.m[3][3])
		- (m.m[1][1] * m.m[2][3] * m.m[3][2]));

	result.m[0][1] = (1 / MatrixFormula) * (
		-(m.m[0][2] * m.m[2][3] * m.m[3][3])
		- (m.m[0][2] * m.m[2][3] * m.m[3][1])
		- (m.m[0][3] * m.m[2][1] * m.m[3][2])
		+ (m.m[0][3] * m.m[2][2] * m.m[0][2])
		+ (m.m[0][2] * m.m[2][1] * m.m[3][3])
		+ (m.m[0][1] * m.m[2][3] * m.m[3][2]));


	result.m[0][2] = (1 / MatrixFormula) * (
		+(m.m[0][1] * m.m[1][2] * m.m[3][3])
		+ (m.m[0][2] * m.m[1][3] * m.m[3][1])
		+ (m.m[0][3] * m.m[1][1] * m.m[3][2])
		- (m.m[0][3] * m.m[1][2] * m.m[3][1])
		- (m.m[0][2] * m.m[1][1] * m.m[3][3])
		- (m.m[0][1] * m.m[1][3] * m.m[3][2]));

	result.m[0][3] = (1 / MatrixFormula) * (
		-(m.m[0][1] * m.m[1][2] * m.m[2][3])
		- (m.m[0][2] * m.m[1][3] * m.m[2][1])
		- (m.m[0][3] * m.m[1][1] * m.m[2][2])
		+ (m.m[0][3] * m.m[1][2] * m.m[2][1])
		+ (m.m[0][2] * m.m[1][1] * m.m[2][3])
		+ (m.m[0][1] * m.m[1][3] * m.m[2][2]));



	result.m[1][0] = (1 / MatrixFormula) * (
		-(m.m[1][0] * m.m[2][2] * m.m[3][3])
		- (m.m[1][2] * m.m[2][3] * m.m[3][0])
		- (m.m[1][3] * m.m[2][0] * m.m[3][2])
		+ (m.m[1][3] * m.m[2][2] * m.m[3][0])
		+ (m.m[1][2] * m.m[2][0] * m.m[3][3])
		+ (m.m[1][0] * m.m[2][3] * m.m[3][2]));

	result.m[1][1] = (1 / MatrixFormula) * (
		+(m.m[0][0] * m.m[2][2] * m.m[3][3])
		+ (m.m[0][2] * m.m[2][3] * m.m[3][0])
		+ (m.m[0][3] * m.m[2][0] * m.m[3][2])
		- (m.m[0][3] * m.m[2][2] * m.m[3][0])
		- (m.m[0][2] * m.m[2][0] * m.m[3][3])
		- (m.m[0][0] * m.m[2][3] * m.m[3][2]));

	result.m[1][2] = (1 / MatrixFormula) * (
		-(m.m[0][0] * m.m[1][2] * m.m[3][3])
		- (m.m[0][2] * m.m[1][3] * m.m[3][0])
		- (m.m[0][3] * m.m[1][0] * m.m[3][2])
		+ (m.m[0][3] * m.m[1][2] * m.m[3][0])
		+ (m.m[0][2] * m.m[1][0] * m.m[3][3])
		+ (m.m[0][0] * m.m[1][3] * m.m[3][2]));

	result.m[1][3] = (1 / MatrixFormula) * (
		+(m.m[0][0] * m.m[1][2] * m.m[2][3])
		+ (m.m[0][2] * m.m[1][3] * m.m[2][0])
		+ (m.m[0][3] * m.m[1][0] * m.m[2][2])
		- (m.m[0][3] * m.m[1][2] * m.m[2][0])
		- (m.m[0][2] * m.m[1][0] * m.m[2][3])
		- (m.m[0][0] * m.m[1][3] * m.m[2][2]));



	result.m[2][0] = (1 / MatrixFormula) * (
		+(m.m[1][0] * m.m[2][1] * m.m[3][3])
		+ (m.m[1][1] * m.m[2][3] * m.m[3][0])
		+ (m.m[1][3] * m.m[2][0] * m.m[3][1])
		- (m.m[1][3] * m.m[2][1] * m.m[3][0])
		- (m.m[1][1] * m.m[2][0] * m.m[3][3])
		- (m.m[1][0] * m.m[2][3] * m.m[3][1]));

	result.m[2][1] = (1 / MatrixFormula) * (
		-(m.m[0][0] * m.m[2][1] * m.m[3][3])
		- (m.m[0][1] * m.m[2][3] * m.m[3][0])
		- (m.m[0][3] * m.m[2][0] * m.m[3][1])
		+ (m.m[0][3] * m.m[2][1] * m.m[3][0])
		+ (m.m[0][1] * m.m[2][0] * m.m[3][3])
		+ (m.m[0][0] * m.m[2][3] * m.m[3][1]));

	result.m[2][2] = (1 / MatrixFormula) * (
		+(m.m[0][0] * m.m[1][1] * m.m[3][3])
		+ (m.m[0][1] * m.m[1][3] * m.m[3][0])
		+ (m.m[0][3] * m.m[1][0] * m.m[3][1])
		- (m.m[0][3] * m.m[1][1] * m.m[3][0])
		- (m.m[0][1] * m.m[1][0] * m.m[3][3])
		- (m.m[0][0] * m.m[1][3] * m.m[3][1]));

	result.m[2][3] = (1 / MatrixFormula) * (
		-(m.m[0][0] * m.m[1][1] * m.m[2][3])
		- (m.m[0][1] * m.m[1][3] * m.m[2][0])
		- (m.m[0][3] * m.m[1][0] * m.m[2][1])
		+ (m.m[0][3] * m.m[1][1] * m.m[2][0])
		+ (m.m[0][1] * m.m[1][0] * m.m[2][3])
		+ (m.m[0][0] * m.m[1][3] * m.m[2][1]));


	result.m[3][0] = (1 / MatrixFormula) * (
		-(m.m[1][0] * m.m[2][1] * m.m[3][2])
		- (m.m[1][1] * m.m[2][2] * m.m[3][0])
		- (m.m[1][2] * m.m[2][0] * m.m[3][1])
		+ (m.m[1][2] * m.m[2][1] * m.m[3][0])
		+ (m.m[1][1] * m.m[2][0] * m.m[3][2])
		+ (m.m[1][0] * m.m[2][2] * m.m[3][1]));


	result.m[3][1] = (1 / MatrixFormula) * (
		+(m.m[0][0] * m.m[2][1] * m.m[3][2])
		+ (m.m[0][1] * m.m[2][2] * m.m[3][0])
		+ (m.m[0][2] * m.m[2][0] * m.m[3][1])
		- (m.m[0][2] * m.m[2][1] * m.m[3][0])
		- (m.m[0][1] * m.m[2][0] * m.m[3][2])
		- (m.m[0][0] * m.m[2][2] * m.m[3][1]));

	result.m[3][2] = (1 / MatrixFormula) * (
		-(m.m[0][0] * m.m[1][1] * m.m[3][2])
		- (m.m[0][1] * m.m[1][2] * m.m[3][0])
		- (m.m[0][2] * m.m[1][0] * m.m[3][1])
		+ (m.m[0][2] * m.m[1][1] * m.m[3][0])
		+ (m.m[0][1] * m.m[1][0] * m.m[3][2])
		+ (m.m[0][0] * m.m[1][2] * m.m[3][1]));

	result.m[3][3] = (1 / MatrixFormula) * (
		+(m.m[0][0] * m.m[1][1] * m.m[2][2])
		+ (m.m[0][1] * m.m[1][2] * m.m[2][0])
		+ (m.m[0][2] * m.m[1][0] * m.m[2][1])
		- (m.m[0][2] * m.m[1][1] * m.m[2][0])
		- (m.m[0][1] * m.m[1][0] * m.m[2][2])
		- (m.m[0][0] * m.m[1][2] * m.m[2][1]));


	return result;
}

//AffineMatrix
Matrix4x4 MakeAffineMatrix(const Vector3 scale, const Vector3 rotate, const Vector3 translate) {
	Matrix4x4 result;

	//S
	Matrix4x4 scaleMatrix;
	scaleMatrix = MakeScaleMatrix(scale);

	//R
	Matrix4x4 rotateMatrix;
	rotateMatrix = MakeRotateXYZMatrix(rotate.x, rotate.y, rotate.z);

	Matrix4x4 translateMatrix;
	translateMatrix = MakeTranslateMatrix(translate);


	result = Multiply(scaleMatrix, Multiply(rotateMatrix, translateMatrix));

	return result;
}


//RED
Vector3 Cross(const Vector3 v1, const Vector3 v2) {
	Vector3 result = { 0.0f,0.0f,0.0f };
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;
}

float Cot(float theta) {
	return (1.0f / tan(theta));
}

//正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float neaCrlip, float farClip) {
	Matrix4x4 result = {};
	result.m[0][0] = 2.0f / (right - left);
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = (1 / farClip - neaCrlip);
	result.m[2][3] = 0;

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = neaCrlip / (neaCrlip - farClip);
	result.m[3][3] = 1;

	return result;
}
//透視投影行列(正規化する)
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result = {};
	float theta = fovY / 2.0f;

	result.m[0][0] = (1.0f / aspectRatio) * Cot(theta);
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = Cot(theta);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
	result.m[3][3] = 0;

	return result;
}
//スクリーンへ
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result = {};
	result.m[0][0] = width / 2;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = -(height / 2);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = maxDepth - minDepth;
	result.m[2][3] = 0;

	result.m[3][0] = left + (width / 2);
	result.m[3][1] = top + (height / 2);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1;

	return result;
}

//Gridを表示
void DrawGrid(const Matrix4x4& viewMatrix, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	//Gridの半分の幅
	const float GRID_HALF_WIDTH = 1.0f;

	//分割数
	const uint32_t SUB_DEVISION = 10;

	//一つ分の長さ
	const float GRID_EVERY = (GRID_HALF_WIDTH * 2.0f) / float(SUB_DEVISION);



	//縦

	Vector3 LocalVerticesStartColumn[11] = {};
	Vector3 LocalVerticesEndColumn[11] = {};

	Matrix4x4 WorldMatrixStartColumn[11] = {};
	Matrix4x4 WorldMatrixEndColumn[11] = {};


	Vector3 ScreenVerticesColumn = {};

	Vector3 ndcVerticesStartColumn = {};
	Vector3 ndcVerticesEndColumn = {};


	Vector3 screenVerticesStartColumn[11] = {};
	Vector3 screenVerticesEndColumn[11] = {};


	//横
	Vector3 LocalVerticesStartLine[11] = {};
	Vector3 LocalVerticesEndLine[11] = {};

	Matrix4x4 WorldMatrixStartLine[11] = {};
	Matrix4x4 WorldMatrixEndLine[11] = {};


	Vector3 ScreenVerticesLine = {};

	Vector3 ndcVerticesStartLine = {};
	Vector3 ndcVerticesEndLine = {};


	Vector3 screenVerticesStartLine[11] = {};
	Vector3 screenVerticesEndLine[11] = {};




	//奥から手前への線を順々に引いてくる(縦)
	for (int xIndex = 0; xIndex <= SUB_DEVISION; ++xIndex) {
		//上の情報を使ってワールド座標上の始点と終点を求める



		LocalVerticesStartColumn[xIndex].x = xIndex * GRID_EVERY - GRID_HALF_WIDTH;
		LocalVerticesStartColumn[xIndex].y = 0.0f;
		LocalVerticesStartColumn[xIndex].z = -GRID_HALF_WIDTH;

		LocalVerticesEndColumn[xIndex].x = xIndex * GRID_EVERY - GRID_HALF_WIDTH;
		LocalVerticesEndColumn[xIndex].y = 0.0f;
		LocalVerticesEndColumn[xIndex].z = GRID_HALF_WIDTH;








		WorldMatrixStartColumn[xIndex] = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, LocalVerticesStartColumn[xIndex]);
		WorldMatrixEndColumn[xIndex] = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, LocalVerticesEndColumn[xIndex]);


		////ワールドへ
		Matrix4x4 worldViewProjectionMatrixStart = Multiply(WorldMatrixStartColumn[xIndex], Multiply(viewMatrix, viewProjectionMatrix));
		Matrix4x4 worldViewProjectionMatrixEnd = Multiply(WorldMatrixEndColumn[xIndex], Multiply(viewMatrix, viewProjectionMatrix));


		ndcVerticesStartColumn = Transform(LocalVerticesStartColumn[xIndex], worldViewProjectionMatrixStart);
		ndcVerticesEndColumn = Transform(LocalVerticesEndColumn[xIndex], worldViewProjectionMatrixEnd);


		screenVerticesStartColumn[xIndex] = Transform(ndcVerticesStartColumn, viewportMatrix);
		screenVerticesEndColumn[xIndex] = Transform(ndcVerticesEndColumn, viewportMatrix);



		//変換した座標を使って表示

		Novice::DrawLine(
			int(screenVerticesStartColumn[xIndex].x),
			int(screenVerticesStartColumn[xIndex].y),
			int(screenVerticesEndColumn[xIndex].x),
			int(screenVerticesEndColumn[xIndex].y),
			RED);

		Novice::DrawLine(
			int(screenVerticesStartColumn[0].x),
			int(screenVerticesStartColumn[0].y),
			int(screenVerticesEndColumn[0].x),
			int(screenVerticesEndColumn[0].y),
			BLUE);


	}
	//左から右も同じように順々に引いていく(横)
	for (uint32_t zIndex = 0; zIndex <= SUB_DEVISION; ++zIndex) {
		//奥から手前が左右に変わるだけ


		LocalVerticesStartLine[zIndex].x = -GRID_HALF_WIDTH;
		LocalVerticesStartLine[zIndex].y = 0.0f;
		LocalVerticesStartLine[zIndex].z = zIndex * GRID_EVERY - GRID_HALF_WIDTH;

		LocalVerticesEndLine[zIndex].x = GRID_HALF_WIDTH;
		LocalVerticesEndLine[zIndex].y = 0.0f;
		LocalVerticesEndLine[zIndex].z = zIndex * GRID_EVERY - GRID_HALF_WIDTH;






		


		WorldMatrixStartLine[zIndex] = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, LocalVerticesStartLine[zIndex]);
		WorldMatrixEndLine[zIndex] = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, LocalVerticesEndLine[zIndex]);



		////ワールドへ
		Matrix4x4 worldViewProjectionMatrixStartLine = Multiply(WorldMatrixStartLine[zIndex], Multiply(viewMatrix, viewProjectionMatrix));
		Matrix4x4 worldViewProjectionMatrixEndLine = Multiply(WorldMatrixEndLine[zIndex], Multiply(viewMatrix, viewProjectionMatrix));


		ndcVerticesStartLine = Transform(LocalVerticesStartLine[zIndex], worldViewProjectionMatrixStartLine);
		ndcVerticesEndLine = Transform(LocalVerticesEndLine[zIndex], worldViewProjectionMatrixEndLine);


		screenVerticesStartLine[zIndex] = Transform(ndcVerticesStartLine, viewportMatrix);
		screenVerticesEndLine[zIndex] = Transform(ndcVerticesEndLine, viewportMatrix);



		//変換した座標を使って表示


		Novice::DrawLine(
			int(screenVerticesStartLine[zIndex].x),
			int(screenVerticesStartLine[zIndex].y),
			int(screenVerticesEndLine[zIndex].x),
			int(screenVerticesEndLine[zIndex].y),
			RED);

		Novice::DrawLine(
			int(screenVerticesStartLine[0].x),
			int(screenVerticesStartLine[0].y),
			int(screenVerticesEndLine[0].x),
			int(screenVerticesEndLine[0].y), BLUE);




	}



}
//Sphreを表示
void DrawSphere(
	const Sphere& sphere,
	const Matrix4x4& viewMatrix,
	const Matrix4x4& viewProjectionMatrix,
	const Matrix4x4& viewportMatrix,
	unsigned int  colour) {

	//分割数
	const uint32_t SUBDIVISION = 30;
	//lat
	const float LON_EVERY = float(M_PI / 20.0f);
	//lon
	const float LAT_EVERY = float(M_PI / 30.0f);



	float thetaD = float(M_PI / SUBDIVISION);
	float phiD = float(2.0f * M_PI / SUBDIVISION);




	Vector3 ndcVerticesCenter = {};


	Vector3 ndcVerticesStart = {};
	Vector3 ndcVerticesEnd = {};

	Vector3 ndcVerticesXYStart = {};
	Vector3 ndcVerticesXYEnd = {};

	Vector3 screenVerticesA[SUBDIVISION] = {};
	Vector3 screenVerticesB[SUBDIVISION] = {};
	Vector3 screenVerticesC[SUBDIVISION] = {};
	Vector3 screenVerticesCenter = {};


	Vector3 screenVerticesStart[SUBDIVISION] = {};
	Vector3 screenVerticesEnd[SUBDIVISION] = {};

	Vector3 screenVerticesXYStart[SUBDIVISION] = {};
	Vector3 screenVerticesXYEnd[SUBDIVISION] = {};


	for (uint32_t latIndex = 0; latIndex < SUBDIVISION; ++latIndex) {
		//現在の緯度
		//θ
		float lat = float(-M_PI / 2.0f + LAT_EVERY * latIndex);
		for (uint32_t lonIndex = 0; lonIndex < SUBDIVISION; ++lonIndex) {
			//現在の経度
			//ファイ
			float lon = lonIndex * LON_EVERY;

			//world座標でのabcを求める
			//acはxz平面(phi,lon)
			//abがxy平面(theta,lat)
			Vector3 a, b, c;


			//Local
			a = { sphere.radius * (cosf(lat) * cosf(lon)),
				sphere.radius * (sinf(lat)),
				sphere.radius * (cosf(lat) * sinf(lon))
			};

			b = { sphere.radius * (cosf(lat + thetaD) * cosf(lon)),
				sphere.radius * (sinf(lat + thetaD)),
				sphere.radius * (cosf(lat + thetaD) * sinf(lon))
			};

			c = { sphere.radius * (cosf(lat) * cosf(lon + phiD)),
				sphere.radius * (sinf(lat)),
				sphere.radius * (cosf(lat) * sinf(lon + phiD))
			};




			//ab,acに引くよ！
			//SRTだから最後のTは移動ね
			Matrix4x4 WorldMatrixA = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, sphere.center);
			Matrix4x4 WorldMatrixB = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, sphere.center);
			Matrix4x4 WorldMatrixC = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, sphere.center);





			////ワールドへ
			//Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
			Matrix4x4 worldViewProjectionMatrixA = Multiply(WorldMatrixA, Multiply(viewMatrix, viewProjectionMatrix));
			Matrix4x4 worldViewProjectionMatrixB = Multiply(WorldMatrixB, Multiply(viewMatrix, viewProjectionMatrix));
			Matrix4x4 worldViewProjectionMatrixC = Multiply(WorldMatrixC, Multiply(viewMatrix, viewProjectionMatrix));




			Vector3 ndcVerticesA = Transform(a, worldViewProjectionMatrixA);
			Vector3 ndcVerticesB = Transform(b, worldViewProjectionMatrixB);
			Vector3 ndcVerticesC = Transform(c, worldViewProjectionMatrixC);

			Vector3 centerPositionNBC = Transform(sphere.center, worldViewProjectionMatrixA);

			screenVerticesA[latIndex] = Transform(ndcVerticesA, viewportMatrix);
			screenVerticesB[latIndex] = Transform(ndcVerticesB, viewportMatrix);
			screenVerticesC[latIndex] = Transform(ndcVerticesC, viewportMatrix);

			Vector3 screenCenter = Transform(centerPositionNBC, viewportMatrix);

			//Novice::DrawEllipse(int(screenCenter.x), int(screenCenter.y), 30, 30, 0.0f, colour, kFillModeSolid);

			//ab
			Novice::DrawLine(
				int(screenVerticesA[lonIndex].x),
				int(screenVerticesA[lonIndex].y),
				int(screenVerticesB[lonIndex].x),
				int(screenVerticesB[lonIndex].y), colour);

			//ac
			Novice::DrawLine(
				int(screenVerticesA[latIndex].x),
				int(screenVerticesA[latIndex].y),
				int(screenVerticesC[latIndex].x),
				int(screenVerticesC[latIndex].y), colour);





		}



	}



}

float Clamp(float t, float min, float max) {
	if (t < min) {
		return min;
	}
	else if (t > max) {
		return max;
	}

	return t;


}

float DotVector3(Vector3 v1, Vector3 v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float DotVector2(Vector3 v1, Vector3 v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float Length(Vector3 V1) {
	return sqrt(V1.x * V1.x + V1.y * V1.y + V1.z * V1.z);
}

Vector3 Normalize(Vector3 V1) {
	Vector3 result = {};

	float length = sqrt(V1.x * V1.x + V1.y * V1.y + V1.z * V1.z);

	float newX = V1.x;
	float newY = V1.y;
	float newZ = V1.z;


	if (length != 0.0f) {
		newX = V1.x / length;
		newY = V1.y / length;
		newZ = V1.z / length;

	}

	result.x = newX;
	result.y = newY;
	result.z = newZ;


	return result;
}





Vector3 Project(const Vector3 a, const Vector3 b) {

	//Aベクトルを正射影ベクトルにする
	Vector3 Vector3C = {};

	//bの長さを求める
	float lengthB = Length(b);
	float dotAB = DotVector3(a, b);

	//||c||=||a||cosθ
	//     ↓
	// a・b=||a|| ||b||cosθより
	//     ↓
	//||c||=a・b/||b||になる

	//正射影ベクトルの長さ
	float t = dotAB / (lengthB * lengthB);
	float newT = Clamp(t, 0.0f, 1.0f);
	Vector3C.x = newT * b.x;
	Vector3C.y = newT * b.y;
	Vector3C.z = newT * b.z;


	return Vector3C;
}

//最近接点
Vector3 ClosestPoint(const Vector3 point, const Segment segment) {

	//Projectで省略してもよかったけど
	//こっちの方が自分の為になると思った
	//A..PO
	Vector3 Vector3A = Subtract(point, segment.origin);
	Vector3 Vector3B = Subtract(segment.diff, segment.origin);

	float lengthB = Length(Subtract(segment.diff, segment.origin));
	float dotAB = DotVector2(point, Vector3B);

	float t = dotAB / (lengthB * lengthB);
	float newT = Clamp(t, 0.0f, 1.0f);

	Vector3 ProjbA = {};
	ProjbA.x = newT * Vector3B.x;
	ProjbA.y = newT * Vector3B.y;
	ProjbA.z = newT * Vector3B.z;






	Vector3 Vector3CP = Add(segment.origin, ProjbA);
	//float lengthD = Length(Vector3CP);


	return Vector3CP;
}

//Sphereの当たり判定
bool IsCollision(const Sphere s1, Sphere s2) {
	//2つの中心点間の距離を求める
	float distance = Length(Subtract(s2.center, s1.center));

	//いつものの仕組み
	//当たっていたらtrue
	if (distance < s1.radius + s2.radius) {
		return true;
	}
	//当たってない場合はfalse
	else {
		return false;
	}
}




//球と平面の当たり判定
bool IsCollisionSpherePlane(const Sphere s1, Plane plane) {
	//kを求めたいんですよね・・

	//q=c-kn
	////球の中心点
	Vector3 c = s1.center;

	float d = plane.distance;

	//単位ベクトル
	Vector3 n = Normalize(plane.normal);

	float k = abs(DotVector3(n, c) - d);


	if (k < s1.radius) {
		return true;
	}
	else {
		return false;
	}





}

Vector3 Perpendicular(const Vector3 vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y, vector.x, 0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}


void DrawPlane(const Plane plane, const Matrix4x4& viewMatrix, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color) {

	//1.中心点を決める
	Vector3 center = {
		plane.distance * plane.normal.x,
		plane.distance * plane.normal.y,
		plane.distance * plane.normal.z
	};

	Vector3 perpendiculars[4];
	//2.法線と垂直なベクトルを１つを決める
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	//3.2の逆ベクトルを求める
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };
	//4.2と法線のクロス積を求める
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	//5.4の逆ベクトルを求める
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };



	//6.2-5のベクトルを中心点にそれぞれ定数倍して足すと4頂点が出来上がる
	//Vector3 points[4] = {};
	Vector3 extend[4] = {};
	Vector3 point[4] = {};
	//Vector3 points2[4] = {};

	Matrix4x4 worldPoints[4] = {};
	Matrix4x4 worldViewProjectionPoints[4] = {};

	Vector3 ndcPoints[4] = {};
	Vector3 screenPoints[4] = {};

	for (int32_t index = 0; index < 4; ++index) {
		extend[index] = {
			2.0f * perpendiculars[index].x,
			2.0f * perpendiculars[index].y,
			2.0f * perpendiculars[index].z
		};
		point[index] = Add(center, extend[index]);




		//points2[index] = Transform(Transform(point[index], viewProjectionMatrix), viewportMatrix);

		//ab,acに引くよ！
		//SRTだから最後のTは移動ね
		worldPoints[index] = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, point[index]);

		////ワールドへ
		//Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		worldViewProjectionPoints[index] = Multiply(worldPoints[index], Multiply(viewMatrix, viewProjectionMatrix));


		ndcPoints[index] = Transform(point[index], worldViewProjectionPoints[index]);

		screenPoints[index] = Transform(ndcPoints[index], viewportMatrix);




	}




#pragma region 点をつなぎ合わせる

	const float offset = 0.0f;

	//WhiteToBlue
	Novice::DrawLine(
		int(screenPoints[0].x),
		int(screenPoints[0].y + offset),
		int(screenPoints[2].x),
		int(screenPoints[2].y + offset), color);

	//BlueToRed
	Novice::DrawLine(
		int(screenPoints[2].x),
		int(screenPoints[2].y + offset),
		int(screenPoints[1].x),
		int(screenPoints[1].y + offset), color);

	//RedToGreen
	Novice::DrawLine(
		int(screenPoints[1].x),
		int(screenPoints[1].y + offset),
		int(screenPoints[3].x),
		int(screenPoints[3].y + offset), color);

	//GreenWhite
	Novice::DrawLine(
		int(screenPoints[3].x),
		int(screenPoints[3].y + offset),
		int(screenPoints[0].x),
		int(screenPoints[0].y + offset), color);

#pragma endregion




}

void DrawSegment(const Segment& segment, const Matrix4x4& viewMatrix, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color) {

	//引数はローカル
	Vector3 localSegmentOrigin = segment.origin;
	Vector3 localSegmentDiff = segment.diff;


	//ワールド
	Matrix4x4 worldSegmentOrigin = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, localSegmentOrigin);
	Matrix4x4 worldSegmentDiff = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, localSegmentDiff);


	Matrix4x4 worldViewProjectionSegmentOrigin = Multiply(worldSegmentOrigin, Multiply(viewMatrix, viewProjectionMatrix));
	Matrix4x4 worldViewProjectionSegmentDiff = Multiply(worldSegmentDiff, Multiply(viewMatrix, viewProjectionMatrix));


	Vector3 ndcSegmentOrigin = Transform(localSegmentOrigin, worldViewProjectionSegmentOrigin);
	Vector3 ndcSegmentDiff = Transform(localSegmentDiff, worldViewProjectionSegmentDiff);



	Vector3 screenSegmentOrigin = Transform(ndcSegmentOrigin, viewportMatrix);
	Vector3 screenSegmentDiff = Transform(ndcSegmentDiff, viewportMatrix);


	Novice::DrawLine(
		int(screenSegmentOrigin.x),
		int(screenSegmentOrigin.y),
		int(screenSegmentDiff.x),
		int(screenSegmentDiff.y), color);


}



//線と平面の衝突判定
bool IsColliionPlaneSegment(const Segment& segment, const Plane& plane) {
	//tを求めたいんですよね・・

	//t=にしてあげると
	//o・n+tb・n=d
	//tb・n=d-o・n
	//t=d-o・n
	//  b・n




	//資料ではaで衝突している
	//a=o+tb

	Vector3 o = segment.origin;
	Vector3 b = segment.diff;
	float d = plane.distance;
	Vector3 n = Normalize(plane.normal);


	float bn = DotVector3(b, n);

	//平行だったので✕
	if (bn == 0.0f) {
		return false;
	}



	//tを求める
	float t = (d - DotVector3(o, n)) / bn;

	//Segmentなので
	if (t > 0.0f) {
		return true;
	}
	else {
		return false;
	}



}



//ImGUiの方が便利だと思えてきたので消したい・・
#pragma region Printf

void VectorScreenPrintf(int x, int y, const Vector3 vector, const char* string) {
	Novice::ScreenPrintf(x + COLUMN_WIDTH * 0, y, "%6.02f", vector.x);
	Novice::ScreenPrintf(x + COLUMN_WIDTH * 1, y, "%6.02f", vector.y);
	Novice::ScreenPrintf(x + COLUMN_WIDTH * 2, y, "%6.02f", vector.z);

	Novice::ScreenPrintf(x + COLUMN_WIDTH * 4, y, "%s", string);

}


void MatrixScreenPrintf(int x, int y, const Matrix4x4 matrix, const char* string) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x, y, "%s", string);
			Novice::ScreenPrintf(x + column * COLUMN_WIDTH, y + (row + 1) * ROW_HEIGHT, "%6.02f", matrix.m[row][column]);
		}
	}
}

#pragma endregion