#pragma once
#include "stdafx.h"

#define _USE_MATH_DEFINES

#include "../Utilities/utilities.h"

class Camera
{
public:
	static const int Camera::MOVE_NONE = -1;
	static const int Camera::MOVE_LEFT = 0x1;
	static const int Camera::MOVE_RIGHT = 0x1 << 1;
	static const int Camera::MOVE_FORWARD = 0x1 << 2;
	static const int Camera::MOVE_BACKWARD = 0x1 << 3;
	static const int Camera::LOOK_UP = 0x1 << 4;
	static const int Camera::LOOK_DOWN = 0x1 << 5;
	static const int Camera::LOOK_LEFT = 0x1 << 6;
	static const int Camera::LOOK_RIGHT = 0x1 << 7;

	Matrix m_ViewMatrix;
	Vector3 m_position;
	float m_speed;
	float m_angle_X;
	float m_angle_Y;

public:
	int m_direction;
	float m_Speed;
	Matrix projectionMatrix;

	Camera();
	~Camera();

	Matrix GetMatrixView();
	void SetDirection(int dir);
	void Update(float deltaTime);
};