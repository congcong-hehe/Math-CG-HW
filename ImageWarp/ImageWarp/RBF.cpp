#include "RBF.h"
#include <limits.h>

RBF::RBF(const std::vector<QPoint>& p_points, const std::vector<QPoint>& q_points)
	: p_points_(p_points), q_points_(q_points)
{
	u_ = -1;
	points_size_ = p_points_.size();
	ris_.resize(points_size_);
	d_.resize((long long)points_size_ * points_size_);

	getDMatrix();
	getRis();
	getAis();
}

RBF::~RBF()
{

}

REAL RBF::getDistance2OfPoints(const QPoint& p, const QPoint& q)
{
	return ((REAL)p.x() - q.x()) * (p.x() - q.x()) + (p.y() - q.y()) * (p.y() - q.y());
}

void RBF::getDMatrix()
{
	for (int i = 0; i < points_size_; ++i)
	{
		for (int j = 0; j < points_size_; ++j)
		{
			d_[i * points_size_ + j] = getDistance2OfPoints(p_points_[i], p_points_[j]);
		}
	}
}

void RBF::getRis()
{
	REAL dis_min = 0;

	for (int i = 0; i < points_size_; ++i)
	{
		dis_min = DBL_MAX;
		for (int j = 0; j < points_size_; ++j)
		{
			if (dis_min > d_[i * points_size_ + j] && i != j)
			{
				dis_min = d_[i * points_size_ + j];
			}
		}
		ris_[i] = dis_min;
	}
}

void RBF::getAis()
{
	Eigen::MatrixXd K(points_size_, points_size_);
	Eigen::VectorXd bx(points_size_);
	Eigen::VectorXd by(points_size_);

	for (int i = 0; i < points_size_; ++i)
	{
		bx(i) = q_points_[i].x() - p_points_[i].x();
		by(i) = q_points_[i].y() - p_points_[i].y();

		for (int j = 0; j < points_size_; ++j)
		{
			K(i, j) = pow(d_[i * points_size_ + j] + ris_[j], u_);
		}
	}

	Ais_x_ = K.colPivHouseholderQr().solve(bx);
	Ais_y_ = K.colPivHouseholderQr().solve(by);
}

QPoint RBF::transfer(const QPoint& p)
{
	QPoint new_p(p);

	for (int i = 0; i < points_size_; ++i)
	{
		REAL temp = pow(getDistance2OfPoints(p, p_points_[i]) + ris_[i], u_);
		new_p.rx() += Ais_x_[i] * temp;
		new_p.ry() += Ais_y_[i] * temp;
	}

	return new_p;
}