#pragma once
#include "main.h"

void DoAffineTransformation(Bitmap^ image);
int AskWhichOperation(); 

void Translate(Bitmap^ image, int height, int width, int a, int b);
void Scale(Bitmap^ image, int height, int width, double a, double b);
void Rotate(Bitmap^ image, int height, int width, double angle);
void Shear(Bitmap^ image, int height, int width, double a, double b);

void AffineByMatrix(Bitmap^ image, int height, int width);

