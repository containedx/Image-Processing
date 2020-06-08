#pragma once
#include "main.h"

public class SE {

public: 

    int* val; 

    int rows; 
    int columns; 

    int size; 
    
    SE();
    void Print();
    void Fill(int value);
    void Init();
    int sub2ind(int r, int c); 

};

void DoClosingImage(Bitmap^ image);
int PickImage(); 
Bitmap^ Binarize(Bitmap^ image); 

Bitmap^ Erode(Bitmap^ image, SE se); 
Bitmap^ Dilate(Bitmap^ image, SE se); 
 