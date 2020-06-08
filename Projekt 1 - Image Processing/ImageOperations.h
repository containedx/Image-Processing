#pragma once
#include "main.h"

void SaveImage(Bitmap^ image);
void SaveImage(Bitmap^ image, String^ path);

Bitmap^ AllocateImage(int x,int y);

Bitmap^ LoadImage(char* path);

