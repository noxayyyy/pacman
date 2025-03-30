#pragma once

#include <iostream>

struct Vector2D {
public:
	float x, y;

	Vector2D() {
		x = y = 0.0f;
	}

	Vector2D(float x, float y) {
		this->x = x;
		this->y = y;
	}

	Vector2D& add(const Vector2D vec) {
		x += vec.x;
		y += vec.y;

		return *this;
	}

	Vector2D& subtract(const Vector2D vec) {
		x -= vec.x;
		y -= vec.y;

		return *this;
	}

	Vector2D& multiply(const Vector2D vec) {
		x *= vec.x;
		y *= vec.y;

		return *this;
	}

	Vector2D& divide(const Vector2D vec) {
		x /= vec.x;
		y /= vec.y;

		return *this;
	}

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2) {
		return v1.add(v2);
	}

	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2) {
		return v1.subtract(v2);
	}

	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2) {
		return v1.multiply(v2);
	}

	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2) {
		return v1.divide(v2);
	}

	Vector2D& operator+=(const Vector2D& vec) {
		return this->add(vec);
	}

	Vector2D& operator-=(const Vector2D& vec) {
		return this->subtract(vec);
	}

	Vector2D& operator*=(const Vector2D& vec) {
		return this->multiply(vec);
	}

	Vector2D& operator/=(const Vector2D& vec) {
		return this->divide(vec);
	}

	Vector2D& operator*(const int& i) {
		x *= i;
		y *= i;

		return *this;
	}

	bool operator==(const Vector2D& vec) {
		return x == vec.x && y == vec.y;
	}

	bool operator!() {
		return x == y == 0;
	}

	Vector2D& zero() {
		x = y = 0;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec) {
		return stream << "(" << vec.x << ", " << vec.y << ")";
	}
};
