#include "OrientedBoundingBox.h"
#include "GraphicsContext.h"

struct Segment
{
	Vector2 origin;
	Vector2 length;

	Segment() { }

	Segment(const Vector2& origin, const Vector2& endpoint)
	{
		this->origin = origin;
		this->length = endpoint - origin;
	}

	bool intersects(const Segment& other, float &t)
	{
		Vector2 p = origin;
		Vector2 q = other.origin;
		Vector2 r = length;
		Vector2 s = other.length;

		Vector2 p2 = p + r;
		Vector2 q2 = q + s;

		float uNumerator = cross(q - p, r);
		float denominator = cross(r, s);

		float u = uNumerator / denominator;
		t = cross(q - p, s) / denominator;

		if (uNumerator == 0 && denominator == 0) 
		{ // They are collinear, need further check to see if they overlap
			return false;
			return ((q.x - p.x < 0) != (q.x - p2.x < 0) != (q2.x - p.x < 0) != (q2.x - p2.x < 0)) || 
				((q.y - p.y < 0) != (q.y - p2.y < 0) != (q2.y - p.y < 0) != (q2.y - p2.y < 0));
		}

		if (denominator == 0) {
			// lines are parallel
			return false;
		}

		return (t >= 0) && (t <= 1) && (u >= 0) && (u <= 1);
	}
};

bool OrientedBoundingBox::Overlaps1Way(OrientedBoundingBox& other, OverlapResult* result) {
	float amounts[2];

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
			amounts[a] = tMax - tMin;
			/*
			if ( (tMin > 1 + origin[a]) )
			{
				amounts[a] = tMin;
			}
			else
			{
				amounts[a] = tMax;
			}*/
		} else {
			amounts[a] = 0;
			return false;
		}
			
		/*
		// See if [tMin, tMax] intersects [0, 1]
		if ((tMin > 1 + origin[a]) || (tMax < origin[a])) {
			// There was no intersection along this dimension;
			// the boxes cannot possibly overlap.
			return false;
		}/
		*/
	}

	if (result != nullptr)
	{
		result->normal = amounts[0] > amounts[1] ? axis[0] : axis[1];
		result->normal = result->normal.leftNormal();
		result->normal.normalize();
		result->penetration = std::min(amounts[0], amounts[1]);
		result->overlaps = true;
		
		int contactIndex = 0;
		// Calculate contact points.

		Segment edges[4];
		edges[0] = Segment(corner[0], corner[1]);
		edges[1] = Segment(corner[1], corner[2]);
		edges[2] = Segment(corner[2], corner[3]);
		edges[3] = Segment(corner[3], corner[0]);

		Segment otherEdges[4];
		otherEdges[0] = Segment(other.corner[0], other.corner[1]);
		otherEdges[1] = Segment(other.corner[1], other.corner[2]);
		otherEdges[2] = Segment(other.corner[2], other.corner[3]);
		otherEdges[3] = Segment(other.corner[3], other.corner[0]);

		for(int i = 0; i < 4; i++)
		{
			Segment s = edges[i];
			for(int j = 0; j < 4; j++)
			{
				if( contactIndex < 2 )
				{
					float t;
					if(s.intersects(otherEdges[j], t))
					{
						result->contactPoints[contactIndex++] = s.origin + s.length * t;
						context->DrawPoint(s.origin + s.length * t, sf::Color(255, 0, 0));
					}
				}
			}
		}

		result->contactCount = contactIndex;
	}

	return true;
}
