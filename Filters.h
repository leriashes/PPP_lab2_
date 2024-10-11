#pragma once
using namespace System::Drawing;

int NormalizeColor(int color);
Bitmap^ MakeImgWithBordersCopy(Bitmap^ img, int apert);
void CountKernelGauss(double* kernel, int apert);
void GaussFilter(Bitmap^ img, int startRow, int endRow, Bitmap^ result, double* kernel);
void MedianFilter();
void SobelFilter();
