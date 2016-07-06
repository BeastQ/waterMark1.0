#pragma once
#include<opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <iostream> 
using namespace cv;
/*
通用方法类的声明
*/
class Uitls
{
public:
	//attack实现，返回类型和参数待定
	void attack();//可选，参数：攻击类型名，攻击类型相关的参数
				  //calcPBC实现，返回类型和参数待定
	void calcPBC();//误码率（需要），相关系数（需要），峰值信噪比（可选）	
				   //gauLowPass实现，返回类型和参数待定
	Mat gauLowPass(Mat cfData,int n,double sigma); //入参：图像数据，入参：窗口大小，标准差；返回值：滤波后的图像，
					   //getBer
	void getBer();
	//getCorr
	void getCorr();
	//getPsnr
	void getPsnr();
	//RGB2GRAY
	void RGB2GRAY();
	Mat getMatV(Mat cfL,int r1,int r2,int c1,int c2);
	Mat Creshape(Mat v,int rows);
	Mat getPowMat(Mat v,int i,int p);
	Mat getPowMat(Mat v,int p);
	double getLxOrLy(Mat cc,int vlen,double p1);
	//产生高斯噪声
	double generateGaussianNoise(double Dx);
	//加入高斯白噪声
	Mat cAwgn(Mat v, int i, double db);
private:
	//声明一些相关属性
};