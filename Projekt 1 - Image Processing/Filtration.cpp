#include "pch.h"
#include "Filtration.h"

void DoStdFiltration(Bitmap^ image)
{
	int mask_size=3; 
	cout << "Enter Size of a Mask: "; 
	cin >> mask_size;

	DoStd(image, mask_size);

}


void DoStd(Bitmap^ image, int mask_size)
{

	int width = image->Width;
	int height = image->Height;

	Bitmap^ outputimage = AllocateImage(width, height);

	Bitmap^ enlarged = AllocateImage(width + mask_size, height + mask_size);

	Color Px;

	// copy image to enlarged image
	for (int i = mask_size; i < width; i++)
	{
		for (int j = mask_size; j < height; j++)
		{
			Px = image->GetPixel(i, j);
			enlarged->SetPixel(i, j, Px);
		}
	}


	// start at mask size pixel 
	for (int i = mask_size; i < width; i++)
	{
		for (int j = mask_size; j < height; j++)
		{
			Px = enlarged->GetPixel(i, j);

			int StdR;
			int StdG;
			int StdB;

			int s = floor(mask_size / 2); 

			for (int k = -s; k < s; k++)
			{
				for (int z = -s; z < s; z++)
				{
					int R = enlarged->GetPixel(i + k, j + z).R;
					int G = enlarged->GetPixel(i + k, j + z).G;
					int B = enlarged->GetPixel(i + k, j + z).B;

					StdR += (R - Px.R) * (R - Px.R);
					StdG += (G - Px.G) * (G - Px.G);
					StdB += (B - Px.B) * (B - Px.B);
				}
			}

			StdR /= 3 * 3 - 1;
			StdG /= 3 * 3 - 1;
			StdB /= 3 * 3 - 1;

			//cout << StdR << " " << StdG << " " << StdB << endl; 

			StdR = NormalizeValue(StdR); 
			StdG = NormalizeValue(StdG); 
			StdB = NormalizeValue(StdB); 

			outputimage->SetPixel(i, j, Color::FromArgb(StdR, StdG, StdB));
		}
	}

	SaveImage(outputimage);
}

int NormalizeValue(int value)
{
	if (value < 0)
		value = 0; 

	if (value > 255)
		value = 255; 

	return value; 
}