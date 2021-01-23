#include "IDW.h"
#include <stdio.h>

IDW::IDW(const std::vector<QPoint> &p_points,const std::vector<QPoint> &q_points, int u) 
	: p_points_(p_points), q_points_(q_points), u_(u)
{
	points_size_ = p_points_.size();
}

IDW::~IDW()
{

}

REAL IDW::getDistanceOfPoints(const QPoint& p, const QPoint& q)
{
	return sqrt(pow(p.x() - q.x(), 2) + pow(p.y() - q.y(), 2));
}

REAL IDW::getWiSum(const QPoint& p, int i)
{
	//如果点是控制点
	if (p == p_points_[i])
	{
		return 1;
	}
	
	REAL sum_wi = 0;

	for (int i = 0; i < p_points_.size(); ++i)
	{
		sum_wi += 1 / pow(getDistanceOfPoints(p, p_points_[i]), u_);
	}

	return sum_wi;
}

REAL IDW::getWi(const QPoint &p ,int i, REAL sum_wi)
{
	//如果点是控制点
	if (p == p_points_[i])
	{
		return 1;
	}
	
	return 1 / pow(getDistanceOfPoints(p, p_points_[i]), u_) / sum_wi;
}

QPoint IDW::transfer(const QPoint &p)
{
	REAL fp_x = 0, fp_y = 0;
	for (int i = 0; i < points_size_; ++i)
	{
		REAL sum_wi = getWiSum(p, i);
		REAL wi = getWi(p, i, sum_wi);
		REAL fpi_x = q_points_[i].x() + ((REAL)p.x() - p_points_[i].x());
		REAL fpi_y = q_points_[i].y() + ((REAL)p.y() - p_points_[i].y());
		fp_x += wi * fpi_x;
		fp_y += wi * fpi_y;
	}
	return QPoint(fp_x, fp_y);
}









