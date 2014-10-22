#ifndef OrientedBoundingBox_h__
#define OrientedBoundingBox_h__

#include "Vector2.h"
#include <cmath>
#include <cfloat>

struct OverlapResult
{
	bool overlaps;
	float amount[2];

	OverlapResult()
	{
		amount[0] = amount[1] = 0;
		overlaps = false;
	}
};

class OrientedBoundingBox {
public:
	float width;
	float height;

	Vector2 center;

	//The corners of the box, starting where 0 = lower left and working clockwise.
	Vector2 corner[4];

	//The two axes moving away from corner O, where 0 represents the first clockwise.
	Vector2 axis[2];

	//The origin where origin[a] = corner[0].dot(axis[a]);
	float origin[2];

	//Calculates the length of the axes based on the current corner positions
	void GetAxes(){
		axis[0] = corner[1] - corner[0];
		axis[1] = corner[3] - corner[0];

		// Make the length of each axis 1/edge length so we know any
		// dot product must be less than 1 to fall within the edge.

		for (int a = 0; a < 2; ++a) {
			axis[a] /= axis[a].LengthSquared();
			origin[a] = corner[0].dot(axis[a]);
		}
	}

	bool Overlaps(OrientedBoundingBox& other, OverlapResult& result) {
		bool collides = Overlaps1Way(other, &result) && other.Overlaps1Way(*this, nullptr);
        return collides;
    }

	//Will return true if 'other' overlaps one dimension of 'this'
	bool Overlaps1Way(OrientedBoundingBox& other, OverlapResult* result) {

		for (int a = 0; a < 2; a++) {

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
            }

			// We have to subtract off the origin
			bool overlaps = ((tMin > 1 + origin[a]) || (tMax < origin[a])) == false;
			
			if (overlaps)
			{
				if (result != nullptr)
				{
					if ( (tMin > 1 + origin[a]) )
					{
						result->amount[a] = tMin;
					}
					else
					{
						result->amount[a] = tMax;
					}
				}
			} else {
				if (result != nullptr)
					result->amount[a] = 0;
				return false;
			}
			
			/*
			// See if [tMin, tMax] intersects [0, 1]
			if ((tMin > 1 + origin[a]) || (tMax < origin[a])) {
				// There was no intersection along this dimension;
				// the boxes cannot possibly overlap.
				return false;
			}
			*/
		}

		return true;
	}

public:
	OrientedBoundingBox() { }

	OrientedBoundingBox(const Vector2 center, const float w, const float h, float angle)
	{
		width = w;
		height = h;
		UpdateOBB2D(center, angle);
	}

	void UpdateOBB2D(Vector2 center, float angle)
	{
		this->center = center;
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
