﻿
#pragma once
#include <Matrix4x4.h>
#include "Vector3.h"
#include "Struct.h"

const int WINDOW_SIZE_WIDTH = 1280;
const int WINDOW_SIZE_HEIGHT = 720;

//四則計算
Vector3 Add(const Vector3 m1, const Vector3 m2);
Vector3 Subtract(const Vector3 m1, const Vector3 m2);

Vector3 Vector3Multiply(const Vector3 v1, const Vector3 v2);


//Scale
Matrix4x4 MakeScaleMatrix(const Vector3 scale);
//Rotate
Matrix4x4 MakeRotateXMatrix(float radian);

Matrix4x4 MakeRotateYMatrix(float radian);

Matrix4x4 MakeRotateZMatrix(float radian);


Matrix4x4 Multiply(const Matrix4x4 m1, const Matrix4x4 m2);

Matrix4x4 Inverse(const Matrix4x4 m);

Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ);

//Translate
Matrix4x4 MakeTranslateMatrix(Vector3 translate);


Vector3 Transform(const Vector3 vector, const Matrix4x4 matrix);


//AffineMatrix
Matrix4x4 MakeAffineMatrix(const Vector3 scale, const Vector3 rotate, const Vector3 translate);


float Cot(float theta);

Vector3 Cross(const Vector3 v1, const Vector3 v2);

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float neaClip, float farClip);

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

#pragma region 文字
void VectorScreenPrintf(int x, int y, const Vector3 vector, const char* string);

const int COLUMN_WIDTH = 60;
const int ROW_HEIGHT = 20;
void MatrixScreenPrintf(int x, int y, const Matrix4x4 matrix, const char* string);
#pragma endregion

void DrawGrid(const Matrix4x4& viewMatrix, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);



void DrawSphere(const Sphere& sphere, const Matrix4x4& viewMatrix, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int colour);



float Clamp(float t, float min, float max);



float DotVector3(const Vector3 v1, const Vector3 v2);
float DotVector2(const Vector3 v1, const Vector3 v2);

float Length(Vector3 V1);
Vector3 Normalize(Vector3 V1);

Vector3 Project(const Vector3 v1, const Vector3 v2);


Vector3 ClosestPoint(const Vector3 point, const Segment segment);

bool IsCollision(const Sphere s1, Sphere s2);

bool IsCollisionSpherePlane(const Sphere s1, Plane plane);

Vector3 Perpendicular(const Vector3 vector);


void DrawPlane(const Plane plane, const Matrix4x4& viewMatrix, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color);


//線と平面の衝突判定
bool IsColliionPlaneSegment(const Segment& segment, const Plane& plane);

//線分の描画
void DrawSegment(const Segment& segment, const Matrix4x4& viewMatrix, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color);