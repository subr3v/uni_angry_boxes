#ifndef OrientedBoundingBox_h__
#define OrientedBoundingBox_h__

#include "Vector2.h"
#include <cmath>

class OrientedBoundingBox {
private:
	float width;
	float height;

	//The corners of the box, starting where 0 = lower left and working clockwise.
	Vector2 corner[4];

	//The two axes moving away from corner O, where 0 represents the first clockwise.
	Vector2 axis[2];

	//The origin where origin[a] = corner[0].dot(axis[a]);
	float origin[2];

	//Calculates the length of the axes based on the current corner positions
	void GetAxes(){
		axis[0] = corner[1] - corner[0];
		axis[0] = corner[3] - corner[0];

		// Make the length of each axis 1/edge length so we know any
		// dot product must be less than 1 to fall within the edge.

		for (int a = 0; a < 2; ++a) {
			axis[a] /= axis[a].LengthSquared();
			origin[a] = corner[0].dot(axis[a]);
		}
	}

	//Will return true if 'other' overlaps one dimension of 'this'
	bool Overlaps(const OrientedBoundingBox& other) const{
		for (int a = 0; a < 2; a++){

			float t = other.corner[0].dot(axis[a]);

			// Find the extent of box 2 on axis a
			float tMin = t;
			float tMax = t;

			for (int c = 1; c < 4; ++c) {
				t = other.corner[c].dot(axis[a]);

				if (t < tMin) {
					tMin = t;
				} else if (t > tMax) {
					tMax = t;
				}

				// We have to subtract off the origin

				// See if [tMin, tMax] intersects [0, 1]
				if ((tMin > 1 + origin[a]) || (tMax < origin[a])) {
					// There was no intersection along this dimension;
					// the boxes cannot possibly overlap.
					return false;
				}
			}
		}
	}

public:
	OrientedBoundingBox() { }

	OrientedBoundingBox(const Vector2 center, const float w, const float h, float angle)
	{
		Vector2 X( cos(angle), sin(angle));
		Vector2 Y(-sin(angle), cos(angle));

		width = w;
		height = h;

		X *= width / 2;
		Y *= height / 2;

		corner[0] = center - X - Y;
		corner[1] = center + X - Y;
		corner[2] = center + X + Y;
		corner[3] = center - X + Y;

		GetAxes();
	}

	void UpdateOBB2D(Vector2 center, float angle)
	{
		Vector2 X( cos(angle), sin(angle));
		Vector2 Y(-sin(angle), cos(angle));

		X *= width / 2;
		Y *= height / 2;

		corner[0] = center - X - Y;
		corner[1] = center + X - Y;
		corner[2] = center + X + Y;
		corner[3] = center - X + Y;

		GetAxes();
	}
};

#endif // OrientedBoundingBox_h__
