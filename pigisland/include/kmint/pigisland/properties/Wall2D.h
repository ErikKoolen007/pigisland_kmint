#pragma once
#define WALL_H

#include <fstream>
#include "kmint/math/vector2d.hpp"


class Wall2D
{
protected:

	kmint::math::vector2d    
		m_vA,
		m_vB,
		m_vN;

	void CalculateNormal()
	{
		kmint::math::vector2d  temp = normalize(m_vB - m_vA);

		m_vN.x(-temp.y());
		m_vN.y(temp.x());
	}

public:

	Wall2D() {}

	Wall2D(kmint::math::vector2d  A, kmint::math::vector2d  B) :m_vA(A), m_vB(B)
	{
		CalculateNormal();
	}

	Wall2D(kmint::math::vector2d  A, kmint::math::vector2d  B, kmint::math::vector2d  N) :m_vA(A), m_vB(B), m_vN(N)
	{ }

	Wall2D(std::ifstream& in) { Read(in); }

	virtual void Render(bool RenderNormals = false)const
	{
		//gdi->Line(m_vA, m_vB);

		//render the normals if rqd
		if (RenderNormals)
		{
			int MidX = (int)((m_vA.x() + m_vB.x()) / 2);
			int MidY = (int)((m_vA.y() + m_vB.y()) / 2);

			//gdi->Line(MidX, MidY, (int)(MidX + (m_vN.x * 5)), (int)(MidY + (m_vN.y * 5)));
		}
	}

	kmint::math::vector2d  From()const { return m_vA; }
	void     SetFrom(kmint::math::vector2d  v) { m_vA = v; CalculateNormal(); }

	kmint::math::vector2d  To()const { return m_vB; }
	void     SetTo(kmint::math::vector2d  v) { m_vB = v; CalculateNormal(); }

	kmint::math::vector2d  Normal()const { return m_vN; }
	void     SetNormal(kmint::math::vector2d  n) { m_vN = n; }

	kmint::math::vector2d  Center()const { return (m_vA + m_vB) / 2.0; }

	// std::ostream& Wall2D::Write(std::ostream& os)const
	// {
	// 	os << std::endl;
	// 	os << From() << ",";
	// 	os << To() << ",";
	// 	os << Normal();
	// 	return os;
	// }

	void Read(std::ifstream& in)
	{
		double x, y;

		in >> x >> y;
		SetFrom(kmint::math::vector2d(x, y));

		in >> x >> y;
		SetTo(kmint::math::vector2d(x, y));

		in >> x >> y;
		SetNormal(kmint::math::vector2d(x, y));
	}

};
