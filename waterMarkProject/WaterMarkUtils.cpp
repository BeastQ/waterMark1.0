#include "WaterMarkUtils.h"
#include"stdafx.h"
void WaterMarkUtils::addBorder() {
	//入参：图像数据，入参：边框厚度，返回值：加边框后的图像，
}


void WaterMarkUtils::genData() {
}

void WaterMarkUtils::getDiag() {
}

void WaterMarkUtils::igetDiag() {
}

/*void WaterMarkUtils::initDIR(string *dirs) {
	for (int i = 1; i <= 8;i++) {
		if () {
		}
	}
}*/

void WaterMarkUtils::izigzagOrder() {
}

void WaterMarkUtils::minEucDistance() {
}

double WaterMarkUtils::quantificate(double z,int d,int delta) {
	double dither = d*delta / 2;
	double z1 = delta * round((z + dither) / delta) - dither;
	return z1;
}

void WaterMarkUtils::zigzagOrder() {
}