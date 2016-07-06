#include "Uitls.h"
#include<opencv2/opencv.hpp>;
#include<math.h>
#include"stdafx.h"

using namespace std;
using namespace cv;
void Uitls::attack() {
	//可选，参数：攻击类型名，攻击类型相关的参数
}
	
void Uitls::calcPBC() {
	//参数：误码率（需要），相关系数（需要），峰值信噪比（可选）
}

Mat Uitls::gauLowPass(Mat cfData,int n,double sigma) {
	//入参：图像数据，入参：窗口大小，标准差；返回值：滤波后的图像，
	Mat glData;
	GaussianBlur(cfData,glData,cv::Size(n,n),sigma);
	return glData;	
}
Mat Uitls::getMatV(Mat cfL, int r1, int r2, int c1, int c2) {
	Mat R = cfL.rowRange(r1,r2).clone();
	Mat C = R.colRange(c1,c2).clone();
	return C;
}
Mat Uitls::Creshape(Mat v,int rows) {
	v = v.t();
	v = v.reshape(0,rows);
	return v;
}
Mat Uitls::getPowMat(Mat c,int i,int p) {
	Mat v1SrcC = c.col(i).clone;
	Mat v1DstC;
	cv::pow(v1SrcC,p,v1DstC);
	return v1DstC;
}
Mat Uitls::getPowMat(Mat c,int p) {
	Mat Dst;
	cv::pow(c, p, Dst);
	return Dst;
}
double Uitls::getLxOrLy(Mat cc,int vlen,double p1) {
	double sum = 0;
	for (int i = 0; i < cc.rows;i++) {
		 sum = sum + cc.at<uchar>(i,0);
	}
	double sum1 = std::abs(sum);
	double sum2 = sum1 / vlen;
	return std::pow(sum2,p1);
}
//产生高斯噪声，即期望为0，方差为Dx服从正太分布就得随机序列
double generateGaussianNoise(double Dx) {
	static double V1, V2, S;
	static int phase = 0;
	double X;
	if (phase == 0) {
		do {
			double U1 = (double)rand() / RAND_MAX;
			double U2 = (double)rand() / RAND_MAX;
			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while (S >= 1 || S == 0);
		X = V1 * sqrt(-2 * log(S) / S);
	}
	else
		X = V2 * sqrt(-2 * log(S) / S);
	phase = 1 - phase;
	return X*(std::sqrt(Dx));
}
//增加高斯噪声
Mat Uitls::cAwgn(Mat v,int i,double db) {
	Mat vv = getPowMat(v,i,2);
	double Ssum = 0;//输入信号能量
	for (int j = 0; j < vv.rows;j++) {
		Ssum = Ssum + vv.at<uchar>(j, 0);
	}
	double Dx = Ssum / (vv.rows*(std::pow(10,db/10)));//计算用于产生高斯噪声的方差
	double gauss = generateGaussianNoise(Dx);//产生高斯白噪声序列
	Mat vi = v.col(i).clone;
	for (int j = 0; j < vi.rows;j++) {
		vi.at<uchar>(j, 0) = vi.at<uchar>(j, 0) + gauss;
	}
	return vi;
}
void Uitls::getBer() {
}
void Uitls::getCorr() {
}
void Uitls::getPsnr() {
}
void Uitls::RGB2GRAY() {
}