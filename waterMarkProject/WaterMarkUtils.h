#pragma once
#include<string>;
#include<opencv2/opencv.hpp>;
using namespace cv;
using namespace std;
/*
算法相关方法类声明
*/
class WaterMarkUtils
{
public:
	//以下方法的实现,返回类型和参数待定
	//void initDIR(string *dirs);	//初始化目录具体实现，对应prepare.m									
	void addBorder();//入参：图像数据，入参：边框厚度，返回值：加边框后的图像，						 
	void genData();
	//getDiag
	void getDiag();
	//igetDiag
	void igetDiag();
	//zigzagOrder
	void zigzagOrder();
	void izigzagOrder();
	//minEucDistance
	void minEucDistance();
	//quantificate
	void quantificate();
	void getWaterMarkRect(Mat img);
private:
	//声明一些需要的属性
	string INPUT_DIR = ".\\Input\\";
	string OUTPUT_DIR = ".\\Output\\";
	string COVER_CMYK_DIR = INPUT_DIR + "orgImage\\CMYK\\";
	string COVER_RGB_DIR = INPUT_DIR + "orgImage\\RGB\\";
	string WATERMARK_DIR = INPUT_DIR + "Watermark\\";
	string LOG_DIR = OUTPUT_DIR + "Log\\";
	string STEGO_CMYK_DIR = OUTPUT_DIR + "Glp\\CMYK\\";
	string STEGO_RGB_DIR = OUTPUT_DIR + "Glp\\RGB\\";
	string dirs[8] = {INPUT_DIR,OUTPUT_DIR,COVER_CMYK_DIR,COVER_RGB_DIR,
		WATERMARK_DIR,LOG_DIR,STEGO_CMYK_DIR,STEGO_RGB_DIR};

};