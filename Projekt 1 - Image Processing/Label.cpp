#include "pch.h"
#include "Label.h"

void DoLabelingImage(Bitmap^ image)
{
	int width = image->Width; 
	int height = image->Height; 

	Bitmap^ output_image = AllocateImage(width, height); 
	
	Label label(width, height);
	
	label.Init(image); 


	label.LabelAreas(); 

	label.SaveSeparatedAreas(); 
}

void Label::LabelAreas()
{
	label_count = 1;  // bo 0 == background, a 1 == foreground

	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			if (image_map[i][j] != 1 || image_map[i][j] == 0) //=> pixel labeled
				continue; 

			label_count++; // 2 - first label   
			LabelPixel(i, j, label_count);
		}
}

void Label::LabelPixel(int i, int j, int label_no)
{
	if (image_map[i][j] != 1 || image_map[i][j] == 0) //=> pixel labeled
		return;

	image_map[i][j] = label_no; 

	if (i > 0)
		LabelPixel(i - 1, j, label_no);
	if (i < width - 1)
		LabelPixel(i + 1, j, label_no); 
	if (j > 0)
		LabelPixel(i, j - 1, label_no);
	if (j < height - 1)
		LabelPixel(i, j + 1, label_no); 
}


void Label::Init(Bitmap^ image)
{
	Color Px;

	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			Px = image->GetPixel(i, j);

			if (Px.R == 255 && image_map[i][j] == 0)
			{
				image_map[i][j] = 1;
			}
		}
}

Label::Label(int width, int height)
{
	this->width = width; 
	this->height = height; 

	image_map = new int* [width]; 
	for (int i = 0; i < width; i++)
		image_map[i] = new int[height];

	// init with 0 
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			image_map[i][j] = 0;

	label_count = 1; 
}

void Label::PrintLabel()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
			cout << image_map[i][j];
		
		cout << endl; 
	}
}

void Label::SaveSeparatedAreas()
{
	for (int k = 2; k <= label_count; k++) //for every label 
	{
		Bitmap^ piece = AllocateImage(width, height); 

		Color Px; 

		for(int i=0; i<width; i++)
			for (int j = 0; j < height; j++)
			{
				if (image_map[i][j] == k)
				{
					piece->SetPixel(i, j, Color::FromArgb(255,255,255)); 
				}
			}

		char* p = new char[100];
		sprintf(p, "C:\\Users\\Kinia\\Desktop\\outputs\\label%d.png", k-1); //k-1 bo zaczynalismy od 2
		String^ path = gcnew String(p); 
		SaveImage(piece, path); 
	}

}
