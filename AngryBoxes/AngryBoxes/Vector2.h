#ifndef Vector2_h__
#define Vector2_h__

#include <cmath>

const float PI = 3.141592741f;
const float EPSILON = 0.0001f;

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

	Vector2 leftNormal() 
	{
		return Vector2(-y , x);
	}

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

	Vector2 &operator-=(const Vector2 &other) {
		x -= other.x;
		y -= other.y;
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

inline bool fequals(float a, float b)
{
	return std::abs(a - b) <= EPSILON;
}

inline Vector2 cross( const Vector2& v, float a )
{
	return Vector2( a * v.y, -a * v.x );
}

inline Vector2 cross( float a, const Vector2& v )
{
	return Vector2( -a * v.y, a * v.x );
}

inline float cross( const Vector2& a, const Vector2& b )
{
	return a.x * b.y - a.y * b.x;
}

#endif // Vector2_h__
