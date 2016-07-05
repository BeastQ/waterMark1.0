#pragma once
#include <vector>;
#include<opencv2/opencv.hpp>
#include "Uitls.h";
using namespace cv;
using namespace std;
/*
嵌入水印类的声明
*/
class embedWaterMark
{
public:
	//初始化水印信息
	void initWaterMark(int bitdepth, int vlen, float p, int delta, int DPI, float MarginRatio);
	//嵌入水印算法
	void embedWaterMrak();
	//giQimHide_DCT_block_vertical_Glp函数的实现,参数待定
	Mat giQimHide_DCT_block_vertical_Glp(Mat cfData, vector<int> ones,int delta,
		int vlen,double p,int block[2]);
private:
	//需要声明一些需要的属性
	//水印长度
	int wfLen = 64;
	int bitdepth;//8
	int vlen;//32
	float p;//2.0
	int delta;//70
	int DPI;//96
	float MarginRatio;//0.059
	int block[2] = {8,8};
	vector<int> ones,wfData;
	double MarginH;//选取水印区域的水平方向边距
	double MarginV;//选取水印区域的垂直方向边距
	double RowSt, RowEd, ColSt, ColEd;
	Mat cfData;
	Uitls uitls;
};


