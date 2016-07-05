#include "extractWaterMark.h"
#include"stdafx.h"
void extractWaterMark::initExtractWaterMark() {
	//对应以下这些内容具体实现
	/*load exMsg_512.mat;
	wfLen = 64;
	block = [8,8];
	%---进行水印提取----
	psnrSum1 = 0.0;berSum1 = 0.0;corrSum1 =0.0;countSum1 = 0.0;
	psnrSum2 = 0.0;berSum2 = 0.0;corrSum2 =0.0;countSum2 = 0.0;
	psnrSum3 = 0.0;berSum3 = 0.0;corrSum3 =0.0;countSum3 = 0.0;
	bitdepth = 8;vlen = 32;p = 2.0;delta = 0.70;
	%cfNum = 1;
	fid = fopen('Outcome\fuyin512_96.txt','w');
	%fid = 1;
	%for cfName = 1:cfNum
	% cfData=imread(strcat('Output\Glp\wm_image\',num2str(cfName),'_watermarked.jpg'));
	%  cfData0 = imread('Output\Glp\wm_image\tiqu.jpg');
	MarginRatio = 0.059;*/
}
void extractWaterMark::ExtractWaterMark() {
	/**
	* 1.嵌入水印
	* 2.提取具体实现，里边会调用giQimDehide_DCT_block_vertical_Glp方法
	*/
}
void extractWaterMark::giQimDehide_DCT_block_vertical_Glp() {
	//对应giQimDehide_DCT_block_vertical_Glp.m的内容
}