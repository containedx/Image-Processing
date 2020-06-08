#pragma once

#include "pch.h"
#include "main.h"

#include "Affine.h"
#include "Filtration.h"
#include "Close.h"
#include "Label.h"

int operation_type; 
char* path;

void ReadParameters(); 

int main()
{
    ReadParameters(); 

    Bitmap^ image = LoadImage(path);

   
    switch (operation_type)
    {
    case 1:
        DoAffineTransformation(image); 
        break; 

    case 2:
        DoStdFiltration(image); 
        break; 

    case 3:
        DoClosingImage(image); 
        break; 

    case 4:
        DoLabelingImage(image); 
        break; 

    default:
        cout << "Wrong selection! No such a choice !" << endl; 
    }
    
    
    //delete image; 
    system("pause");
    return 0;
}



void ReadParameters()
{
    path = new char[100];
    cout << "Hello! Please type path to image which you'd like to process" << endl << endl;
    cin >> path;
    cout << endl << "I am going to process this image: " << path << endl;
    cout << "Now, please select operation (by number) : " << endl;
    cout << "1 = Affine Transformation" << endl;
    cout << "2 = Standard Deviation Filtration" << endl;
    cout << "3 = Close Image" << endl;
    cout << "4 = Label Image" << endl;
    cin >> operation_type;
    cout << endl << "You choosed " << operation_type << endl;
}

