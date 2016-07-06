#include "embedWaterMark.h";
#include <vector>;
#include<opencv2/opencv.hpp>;
#include<math.h>
#include"stdafx.h"
using namespace cv;
using namespace std;
void embedWaterMark::initWaterMark(int bitdepth1, int vlen1, float p1, 
	int delta1, int DPI1, float MarginRatio1) {
	bitdepth = bitdepth1;
	vlen = vlen1;
	p = p1;
	delta = delta1;
	DPI = DPI1;
	MarginRatio = MarginRatio1;
	//定义一个储存水印的数组
	vector<int> ones(wfLen,1);
	cfData = imread("图片路径");//读取图像

}
void embedWaterMark::embedWaterMrak() {
	/*
	* 主要分为三步
	* 1.选取嵌入区域
	* 2.低频嵌入处理
	* 3.嵌入调用giQimHide_DCT_block_vertical_Glp
	*/
	//选取嵌入区域
	int m = cfData.cols;//获取图像矩阵的列数
	int n = cfData.rows;//行数
	int t = cfData.depth;//深度
	MarginH = floor(n * MarginRatio); //平方向边距
	MarginV = floor(m * MarginRatio); //垂直方向边距
	RowSt = MarginH + 1;
	RowEd = n - MarginH;
	ColSt = MarginV + 1;
	ColEd = m - MarginV;
	Mat stg = cfData;
	for (int j = 0; j < t;j++) {
		Mat tempCfdata = uitls.getMatV(stg,RowSt,RowEd,ColSt,ColEd);
		Mat dstStg = giQimHide_DCT_block_vertical_Glp(tempCfdata,ones,delta,vlen,p,block);
		for (int row = 0 ; row <= RowEd-RowSt ; row++) {
			for (int col = 0; col <= ColEd-ColSt ; col++) {
				stg.at<Vec3b>(row+RowSt, col+ColSt)[j] = dstStg.at<uchar>(row,col);
			}
		}
	}
	//把stg存储的图像写入文件中

}
Mat embedWaterMark::giQimHide_DCT_block_vertical_Glp(Mat cfData, vector<int> ones,
	int delta,int vlen, double p, int block[2]) {
	//对应giQimHide_DCT_block_vertical_Glp.m的内容
	Mat cfL = uitls.gauLowPass(cfData,3,0.5);//低频部分
	//Mat* cflz = &cfL;
	Mat cfH = cfData - cfL;//高频部分
	int si[2] = {cfL.rows,cfL.cols};//获取矩阵cfL的行数和列数
	int len = wfLen;
	int N1 = floor((floor(si[1] / block[1])*floor(si[0] / block[0])) / (2 * vlen));
	if (len<N1)
	{
		vector<int> zeros((len-N1),0);
		zeros.insert(zeros.begin(), ones.begin(), ones.end());
		wfData = zeros;
	}
	if (len>N1)
	{
		for (int i = N1; i <= len;i++) 
		{
			wfData.erase[i];
		}
	}
	int N = floor(si[0] / block[0]); //there are N blocks in each row
	int M = floor(si[1] / block[1]); // there are M block in each colomn
	if ((M % 2)==1) {
		M -= 1;
	}
	Mat v1 = Mat::zeros(M/2,N, CV_8UC1);
	Mat v2 = Mat::zeros(M / 2, N, CV_8UC1);
	Mat v = Mat::zeros(M , N, CV_8UC1);
	int oddCount = 0;
	int evenCount = 0;
	for (int i = 1; i <= M; i++)
	{
		for (int j = 0; j <= N; j++)
		{
			Mat srcV = uitls.getMatV(cfL, (i - 1)*block[0], i*block[0]-1,
				(j - 1)*block[1], j*block[1]-1);
			Mat V;
			cvDCT(&srcV,&V,CV_DXT_FORWARD);
			v.at<uchar>(i, j) = V.at<uchar>(2,1);
		}
		if ((i%2)==0)
		{
			evenCount = evenCount + 1;
			v2.row(evenCount - 1) = v.row(i);//?matlab是从1开始的，c++是从0开始的，所以要减一
			//v2(evenCount, :) = v(i, :);
		}
		if (true)
		{
			oddCount = oddCount + 1;
			v1.row(oddCount - 1) = v.row(i);//?matlab是从1开始的，c++是从0开始的，所以要减一
			//v1(oddCount,:)=v(i,:);
		}
	}
	v1 = uitls.Creshape(v1,vlen);
	v2 = uitls.Creshape(v2,vlen);
	Mat z1 = Mat::zeros(1, N1, CV_8UC1);
	Mat z = Mat::zeros(1, N1, CV_8UC1);
	for (int i = 0; i < N1;i++) {
		Mat v1Col = uitls.getPowMat(v1,i,p);
		Mat v2Col = uitls.getPowMat(v2,i,p);
		double lx = uitls.getLxOrLy(v1Col,vlen,1/p);
		double ly = uitls.getLxOrLy(v2Col,vlen,1/p);
		if ((std::abs(lx)<=(1e-6))||(std::abs(ly)<=(1e-6)))
		{		
			Mat v1_noise = uitls.cAwgn(v1,i,50);
			Mat v2_noise = uitls.cAwgn(v2,i,50);
			Mat temp_v1_noise = uitls.getPowMat(v1_noise,p);
			Mat temp_v2_noise = uitls.getPowMat(v2_noise,p);
			lx = uitls.getLxOrLy(temp_v1_noise,vlen,1/p);
			ly = uitls.getLxOrLy(temp_v2_noise,vlen,1/p);
		}
		z.at<uchar>(0, i) = lx / ly;
		int d = wfData[i];
		/*if isnan(z(i)) == 1 || isinf(z(i)) == 1 || (abs(lx) <= 1e-6) || (abs(ly) <= 1e-6)
			fprintf(fid, 'HD!i=%d,lx = %f, ly = %f\n', i, lx, ly);
		continue;
		end*/
		z1.at<uchar>(0, i) = waterMarkutils.quantificate(z.at<uchar>(0, i),d,delta);
		if (z1.at<uchar>(0, i)==0)
		{
			z1.at<uchar>(0, i) = delta / 8;
		}
		if (z1.at<uchar>(0, i)<0)
		{
			z1.at<uchar>(0, i) = z1.at<uchar>(0, i) + delta;
		}
		double k = std::sqrt(z1.at<uchar>(0, i)/z.at<uchar>(0, i));
		for (int j = 0; j < v1.rows;j++) {
			v1.at<uchar>(j, i) = k*v1.at<uchar>(j, i);
		} 
		for (int j = 0; j < v2.rows;j++) {
			v2.at<uchar>(j, i) = v2.at<uchar>(j, i) / k;
		}
	}
	int oddP = 0; 
	int evenP = 0;
	Mat v11 = uitls.Creshape(v1, M / 2);
	Mat v22 = uitls.Creshape(v2, M / 2);
	for (int i = 1; i <= M;i++) {
		if (i%2==1) {
			oddP = oddP + 1;
			for (int j = 0; j < v.cols;j++) {
				v.at<uchar>(i , j) = v11.at<uchar>(oddP,j);
			}
		}
		else
		{
			evenP = evenP + 1;
			for (int j = 0; j < v.cols; j++) {
				v.at<uchar>(i , j) = v22.at<uchar>(evenP, j);
			}
		}
		for (int j = 1; j <= N;j++) {
			Mat srcV = uitls.getMatV(cfL, (i - 1)*block[0], i*block[0] - 1,
				(j - 1)*block[1], j*block[1] - 1);
			Mat V;
			cvDCT(&srcV, &V, CV_DXT_FORWARD);
			V.at<uchar>(2, 1) = v.at<uchar>(i, j);
			Mat dct;
			cvDCT(&V,&dct,CV_DXT_INVERSE);
			srcV = dct;
		}
	}
	Mat stg;
	stg = cfL + cfH;
	return stg;

}