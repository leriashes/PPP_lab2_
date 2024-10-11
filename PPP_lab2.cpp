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

    string path = "1.jpg";

    //cin >> path;

    String^ filePath = gcnew String(path.c_str());

    try {
        Bitmap^ img = gcnew Bitmap(filePath);
        cout << "Изображение загружено успешно!";
    }
    catch (Exception^ ex) {
        cout << "Ошибка: " << context.marshal_as<string>(ex->Message);
    }

    return 0;
}
