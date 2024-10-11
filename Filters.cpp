#include "Filters.h"
#include "pch.h"
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
using namespace System::Drawing;

int NormalizeColor(int color)
{
    if (color < 0)
    {
        color = 0;
    }
    else if (color > 255)
    {
        color = 255;
    }

    return color;
}

Bitmap^ MakeImgWithBordersCopy(Bitmap^ img, int apert)
{
    Bitmap^ res = gcnew Bitmap(img->Width + apert * 2, img->Height + apert * 2);

    for (int i = 0; i < res->Width; i++)
    {
        for (int j = 0; j < res->Height; j++)
        {
            int x, y;

            if (i < apert)
            {
                x = 0;
            }
            else if (i >= apert + img->Width)
            {
                x = img->Width - 1;
            }
            else
            {
                x = i - apert;
            }

            if (j < apert)
            {
                y = 0;
            }
            else if (j >= apert + img->Height)
            {
                y = img->Height - 1;
            }
            else
            {
                y = j - apert;
            }

            res->SetPixel(i, j, img->GetPixel(x, y));
        }
    }

    return res;
}

void CountKernelGauss(double* kernel, int apert)
{
    double sigma = round((double)apert * 10.0 / 3) / 10;

    int n = 2 * apert + 1;
    int len = int(pow(n, 2));

    for (int i = -apert; i < apert + 1; i++)
    {
        for (int j = -apert; j < apert + 1; j++)
        {
            kernel[(i + apert) * n + j + apert] = exp(-(i * i + j * j) / (2 * sigma * sigma));
        }
    }

    double A = 0;

    for (int i = 0; i < len; i++)
    {
        A += kernel[i];
    }

    for (int i = -apert; i < apert + 1; i++)
    {
        for (int j = -apert; j < apert + 1; j++)
        {

            kernel[(i + apert) * n + j + apert] /= A;
        }
    }
}


void GaussFilter(Bitmap^ img, int startRow, int endRow, Bitmap^ result, double* kernel, int apert)
{
    int n = apert * 2 + 1;

    for (int i = 0; i < result->Width; i++)
    {
        for (int j = startRow; j <= endRow; j++)
        {
            double R = 0;
            double G = 0;
            double B = 0;

            for (int k = 0; k < n; k++)
            {
                for (int l = 0; l < n; l++)
                {
                    Color pixel = img->GetPixel(i + l, j + k);

                    R += pixel.R * kernel[k * n + l];
                    G += pixel.G * kernel[k * n + l];
                    B += pixel.B * kernel[k * n + l];
                }
            }

            result->SetPixel(i, j, Color::FromArgb(result->GetPixel(i, j).A, NormalizeColor(int(round(R))), NormalizeColor(int(round(G))), NormalizeColor(int(round(B)))));
        }
    }
}


void MedianFilter(Bitmap^ img, int startRow, int endRow, Bitmap^ result, int apert)
{
    int n = apert * 2 + 1;
    int size = n * n;

    for (int i = 0; i < result->Width; i++)
    {
        for (int j = 0; j < result->Height; j++)
        {
            vector<int> rmas(size, 0);
            vector<int> gmas(size, 0);
            vector<int> bmas(size, 0);

            for (int k = 0; k < n; k++)
            {
                for (int l = 0; l < n; l++)
                {
                    Color pixel = img->GetPixel(i + l, j + k);

                    rmas[k * n + l] = pixel.R;
                    gmas[k * n + l] = pixel.G;
                    bmas[k * n + l] = pixel.B;
                }
            }

            sort(rmas.begin(), rmas.end());
            sort(gmas.begin(), gmas.end());
            sort(bmas.begin(), bmas.end());

            result->SetPixel(i, j, Color::FromArgb(result->GetPixel(i, j).A, rmas[apert], gmas[apert], bmas[apert]));
        }
    }
}


void SobelFilter()
{
	;
}
