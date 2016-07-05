#pragma once
/*
提取水印类的声明
*/
class extractWaterMark
{
public:
	//初始化提取水印需要的信息，返回类型和参数待定
	void initExtractWaterMark();
	//提取水印算法实现
	void ExtractWaterMark();
	//返回类型和参数待定,对应giQimDehide_DCT_block_vertical_Glp.m的内容
	void giQimDehide_DCT_block_vertical_Glp();
private:
	//需要声明一些需要的属性
};