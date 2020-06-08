#include "pch.h"
#include "Close.h"
#include <math.h>


void DoClosingImage(Bitmap^ image)
{
	if (PickImage() == 0)
		image = Binarize(image);


	SE se = SE();
	se.Print();	
	
	Bitmap^ outputimage = AllocateImage(image->Width, image->Height); 


	outputimage = Dilate(image, se); 
	outputimage = Erode(outputimage, se); 

	SaveImage(outputimage); 
}

int PickImage()
{ 
	int p; 
	cout << "Pick Image type:" << endl;
	cout << " 1 - binary " << endl; 
	cout << " 0 - monochromatic, grayscale" << endl; 
	cin >> p; 

	return p; 
}

Bitmap^ Binarize(Bitmap^ image)
{
	int width = image->Width; 
	int height = image->Height; 
	Bitmap^ binary = AllocateImage(width, height);

	Color Px; 

	for(int i = 0; i<width; i++)
		for (int j = 0; j < height; j++)
		{
			Px = image->GetPixel(i, j); 

			if (Px.R > 150)
				binary->SetPixel(i, j, Color::FromArgb(255, 255, 255)); 
			else
				binary->SetPixel(i, j, Color::FromArgb(0, 0, 0));
		}
	
	return binary; 
}

SE::SE()
{	
	int length, angle;

	cout << "Enter size: ";
	cin >> length;
	cout << "Enter angle (0-180) :";
	cin >> angle;

	if (angle == 0 || angle == 180)
	{		
		rows = 1; 
		columns = length;

		Init(); 
		Fill(1); 

		return; 
	}

	if (angle == 90)
	{
		rows = length;
		columns = 1;

		Init(); 
		Fill(1); 

		return; 
	}

	double pi = 3.14159265;
	double rad;

	if(angle<=90)
		rad = pi * angle / 180; 
	else
		rad = pi * (180-angle) / 180;

	
	rows = abs(ceil(sin(rad)* length));
	columns = abs(ceil(cos(rad)* length));

	Init(); 
	Fill(0); 

	// line : y=ax+b 
	// a - wspolczynnik kierunkowy == tg(kata)
	// tez a == (y2-y1)/(x2-x1)
	
	double a = round(tan(rad)*10)/10;
	double b = -(rows - 1); 

	for (double kx= 0; kx < columns; kx += 0.1)
	{ 
		kx = round(kx * 10) / 10;

		if (a * kx + b > 0)
		{
			if(angle<90)
				val[columns-1] = 1; 
			break;
		}

		int x = floor(kx);  
		double y = ceil(abs(a * kx + b)); 

		if(angle<=90)
			val[sub2ind(y,x)] = 1; 
		else
			val[sub2ind(y,rows-x-1)] = 1; 

		//cout << x << " " << y << "  kx: " << a * kx + b << endl;
	}	
	  
}

int SE::sub2ind(int r, int c)
{
	return r * columns + c; 
}

void SE::Print()
{
	cout << rows << "x" << columns << endl; 

	for (int i; i < size; i++)
	{
		cout << val[i] << " ";

		if ((i+1) % columns == 0)
			cout << endl; 
	}
		
}

void SE::Init()
{
	size = rows * columns; 
	val = new int[size];
}

void SE::Fill(int value)
{
	for (int i = 0; i < size; i++)
			val[i] = value;
}


Bitmap^ Erode(Bitmap^ image, SE se)
{
	int width = image->Width;
	int height = image->Height;

	Bitmap^ output_image = AllocateImage(width, height);

	//for every pixel in image
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{

			int minR = 255;
			int minG = 255;
			int minB = 255;
			Color Px;


			for (int n = 0; n < se.columns; n++)
				for (int m = 0; m < se.rows; m++)
				{
					if (se.val[se.sub2ind(n, m)] == 1)
					{
						int posx = i - floor(se.columns/2) + n;
						int posy = j - floor( se.rows / 2) + m;

						if (posx > 0 && posy > 0 && posx < width && posy < height)
						{
							Px = image->GetPixel(posx, posy);

							if (minR > Px.R)
								minR = Px.R;

							if (minG > Px.G)
								minG = Px.G;

							if (minB > Px.B)
								minB = Px.B;
						}
					}

				}


			output_image->SetPixel(i, j, Color::FromArgb(minR, minG, minB));

		}

	return output_image;
}


Bitmap^ Dilate(Bitmap^ image, SE se)
{
	int width = image->Width; 
	int height = image->Height; 

	Bitmap^ output_image = AllocateImage(width, height);

	//for every pixel in image
	for(int i=0; i<width; i++)
		for (int j = 0; j < height; j++)
		{

			int maxR = 0;
			int maxG = 0;
			int maxB = 0;
			Color Px; 


			for(int n=0;n<se.columns; n++)
				for (int m = 0; m < se.rows; m++)
				{
					if (se.val[se.sub2ind(n, m)] == 1)
					{
						int posx = i - floor(se.columns/2) + n;
						int posy = j - floor(se.rows/2) + m;

						if (posx > 0 && posy>0 && posx<width && posy<height)
						{
							Px = image->GetPixel(posx, posy);

							if (maxR < Px.R)
								maxR = Px.R;

							if (maxG < Px.G)
								maxG = Px.G;

							if (maxB < Px.B)
								maxB = Px.B;
						}

						//cout << posx << " " << posy << " " << i << " " << j<< endl; 
					}

				}
				
			//cout << endl; 
			output_image->SetPixel(i,j,Color::FromArgb(maxR, maxG, maxB));

		}

	return output_image; 
}