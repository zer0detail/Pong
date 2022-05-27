#include "Ball.h"

// Constructor function
Ball::Ball(float startX, float startY) {
	m_Position.x = startX;
	m_Position.y = startY;
	m_shape.setSize(sf::Vector2f(10, 10));
	m_shape.setPosition(m_Position);
}

FloatRect Ball::getPosition() {
	return m_shape.getGlobalBounds();
}

RectangleShape Ball::getShape() {
	return m_shape;
}

float Ball::getXVelocity() {
	return m_DirectionX;
}

void Ball::reboundSides() {
	m_DirectionX = -m_DirectionX;
}

void Ball::reboundBatOrTop() {
	m_DirectionY = -m_DirectionY;
}

void Ball::reboundBottom() {
	m_Position.y = 0;
	m_Position.x = 500;
}

void Ball::update(Time dt) {
	// Update the balls position
	m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
	m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();
	// Move the ball
	m_shape.setPosition(m_Position);
}