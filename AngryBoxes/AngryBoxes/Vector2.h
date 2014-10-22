#ifndef Vector2_h__
#define Vector2_h__

#include <cmath>

class Vector2 {
public:
	Vector2() { }
	Vector2(float x, float y) {
		this->x = x;
		this->y = y;
	}

	void normalize() {
		float len = getLength();
		if (len != 0) {
			x /= len;
			y /= len;
		}
	}

	float dot(const Vector2& other) const {
		return x * other.x + y * other.y;
	}

	float getLength() const { return sqrt(x * x + y * y); }

	float LengthSquared() const { return x * x + y * y; }

	bool operator==(const Vector2 &other) const {
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vector2 &other) const {
		return x != other.x || y != other.y;
	}

	Vector2 operator-() const {
		return Vector2(-x, -y);
	}

	Vector2 operator*(float factor) const {
		return Vector2(x * factor, y * factor);
	}

	Vector2 operator+(const Vector2 &other) const {
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator-(const Vector2 &other) const {
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 &operator*=(float factor) {
		x *= factor;
		y *= factor;
		return *this;
	}

	Vector2 &operator+=(float value) {
		x += value;
		y += value;
		return *this;
	}

	Vector2 &operator+=(const Vector2 &other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2 &operator-=(float value) {
		x -= value;
		y -= value;
		return *this;
	}

	Vector2 &operator/=(float value) {
		x /= value;
		y /= value;
		return *this;
	}

	float x, y;
};

#endif // Vector2_h__
