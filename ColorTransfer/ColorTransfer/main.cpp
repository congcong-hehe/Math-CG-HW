#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

using namespace cv;

int main()
{
	Mat src_img = imread("image/source.jpg");
	Mat target_img = imread("image/target.jpg");

	//ת��Դ�ļ���Ŀ���ļ�����Ϊ32λfloat
	Mat src_32f_img, target_32f_img;
	src_img.convertTo(src_32f_img, CV_32FC3, 1.0f/255.0f);
	target_img.convertTo(target_32f_img, CV_32FC3, 1.0f/255.0f);
	
	//��ɫ�ռ䣺RGB -> lab
	Mat src_lab_img, target_lab_img;
	cvtColor(src_32f_img, src_lab_img, COLOR_BGR2Lab);
	cvtColor(target_32f_img, target_lab_img, COLOR_BGR2Lab);

	//�����ֵ�ͱ�׼��
	Scalar mean_src, mean_target, std_src, std_target;
	meanStdDev(src_lab_img, mean_src, std_src);
	meanStdDev(target_lab_img, mean_target, std_target);

	//�ָ�ͼ�������ͨ��
	std::vector<Mat> channel_src, channel_target;
	split(src_lab_img, channel_src);
	split(target_lab_img, channel_target);

	//��ȥԴ�ļ����ؾ�ֵ
	channel_src[0] -= mean_src[0];
	channel_src[1] -= mean_src[1];
	channel_src[2] -= mean_src[2];

	//���ͬ�����Ŵ󣬼���Ŀ���ļ���ֵ
	channel_src[0] = channel_src[0] * std_target[0] / std_src[0] + mean_target[0];
	channel_src[1] = channel_src[1] * std_target[1] / std_src[1] + mean_target[1];
	channel_src[2] = channel_src[2] * std_target[2] / std_src[2] + mean_target[2];

	//���ͼ����ɫ�ռ䣺lab -> RGB
	Mat result_img;
	merge(channel_src, result_img);
	cvtColor(result_img, result_img, COLOR_Lab2BGR);
	result_img.convertTo(result_img, CV_8UC3, 255.0f);

	imwrite("image/result.jpg", result_img);
	imshow("src", src_img);
	imshow("target", target_img);
	imshow("result", result_img);

	waitKey(0);

	return 0;
}