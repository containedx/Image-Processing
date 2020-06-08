#pragma once
#include "main.h"

public class Label {

public: 

	int** image_map;  // 0 == unmarked 1== marked
	int width; 
	int height; 

	int label_count; 

	Label(int width, int height); 

	void Init(Bitmap^ image); 
	void PrintLabel(); 

	void LabelAreas();
	void LabelPixel(int i, int j, int label_no); 

	void SaveSeparatedAreas();

};


void DoLabelingImage(Bitmap^ image);


