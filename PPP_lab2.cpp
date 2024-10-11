#include "pch.h"
#include "Filters.h"
#include <iostream>
#include <windows.h>
#include <msclr/marshal_cppstd.h>
#include <string>

using namespace std;
using namespace System;
using namespace System::Drawing;

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    msclr::interop::marshal_context context;

    string path = "bad.jpg";

    //cin >> path;

    String^ filePath = gcnew String(path.c_str());
    Bitmap^ img, ^bordered, ^result;

    try {
        img = gcnew Bitmap(filePath);
        cout << "Изображение загружено успешно!";
    }
    catch (Exception^ ex) {
        cout << "Ошибка: " << context.marshal_as<string>(ex->Message);
    }

    result = gcnew Bitmap(img);

    int apert = 2;
    
    int n = 2 * apert + 1;
    int len = n * n;

    double* kernel = new double[len];

    bordered = MakeImgWithBordersCopy(img, apert);

    CountKernelGauss(kernel, apert);
    GaussFilter(bordered, 0, img->Height - 1, result, kernel);

    result->Save("result.jpg");

    return 0;
}
