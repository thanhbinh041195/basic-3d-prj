#include <stdafx.h>
#include "Camera.h"

Camera::Camera()
{
	m_speed = 3.0f;
	m_ViewMatrix.SetIdentity();
	m_position = Vector3(0.0f, 1.0f, 5.0f);
	m_ViewMatrix = m_ViewMatrix.SetTranslation(-m_position.x, -m_position.y, -m_position.z);
	m_direction = 0;
	m_angle_X = 0;
	m_angle_Y = 0;
}

Camera::~Camera()
{

}

void Camera::Update(float deltaTime)
{
	if (m_direction != 0)
	{
		Matrix m_rotateX;
		Matrix m_rotateY;

		Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
		Vector3 right = Vector3(1.0f, 0.0f, 0.0f);
		Vector3 forward = Vector3(0.0f, 0.0f, 1.0f);
		float speed = m_speed * deltaTime;

		if (m_direction & MOVE_LEFT)
		{
			m_position -= right*speed;
		}

		if (m_direction & MOVE_RIGHT)
		{
			m_position += right*speed;
		}

		if (m_direction & MOVE_FORWARD)
		{
			m_position -= forward*speed;
		}

		if (m_direction & MOVE_BACKWARD)
		{
			m_position += forward*speed;
		}

		if (m_direction &  LOOK_UP)
		{
			m_angle_X -= speed;
		}

		if (m_direction &  LOOK_DOWN)
		{
			m_angle_X += speed;
		}

		if (m_direction &  LOOK_LEFT)
		{
			m_angle_Y -= speed;
		}

		if (m_direction &  LOOK_RIGHT)
		{
			m_angle_Y += speed;
		}

		m_rotateX = m_ViewMatrix.SetRotationX(-m_angle_X);
		m_rotateY = m_ViewMatrix.SetRotationY(-m_angle_Y);
		m_ViewMatrix = m_rotateX * m_rotateY * m_ViewMatrix.SetTranslation(-m_position.x, -m_position.y, -m_position.z);
	}
}

Matrix Camera::GetMatrixView()
{
	return m_ViewMatrix;
}

void Camera::SetDirection(int dir)
{
	m_direction = dir;
}

