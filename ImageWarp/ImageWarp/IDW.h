#pragma once
#include "REAL.h"
#include <vector>
#include <QPoint>
#include <cmath>

class IDW
{
public:
	IDW(const std::vector<QPoint> &p_points,const std::vector<QPoint> &q_points, int u = 2);
	~IDW();

	QPoint transfer(const QPoint &p);

private:
	REAL getDistanceOfPoints(const QPoint &p, const QPoint &q);
	REAL getWiSum(const QPoint& pi, int i);
	REAL getWi(const QPoint &pi, int i,REAL sum_wi);

private:
	int u_;
	
	std::vector<QPoint> p_points_;
	std::vector<QPoint> q_points_;

	int points_size_;
};

