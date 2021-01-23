#pragma once

#include "REAL.h"
#include <vector>
#include <QPoint>
#include <Eigen/Dense>
#include <math.h>

class RBF
{
public:
	RBF(const std::vector<QPoint>& p_points, const std::vector<QPoint>& q_points);
	~RBF();

	QPoint transfer(const QPoint& p);

private:
	REAL getDistance2OfPoints(const QPoint& p, const QPoint& q);
	void getRis();
	void getDMatrix();
	void getAis();

private:
	std::vector<QPoint> p_points_;
	std::vector<QPoint> q_points_;

	int points_size_;
	REAL u_;

	std::vector<REAL> ris_;
	std::vector<REAL> d_;

	Eigen::VectorXd Ais_x_;
	Eigen::VectorXd Ais_y_;
};

