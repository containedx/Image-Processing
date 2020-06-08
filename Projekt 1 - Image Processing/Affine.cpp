#include "pch.h"
#include "Affine.h"

void DoAffineTransformation(Bitmap^ image)
{
	int height = image->Height;
	int width = image->Width;

	switch (AskWhichOperation())
	{
		
	case 1: 
		int a, b;
		cout << "Enter factors  x, y: " << endl; 
		cin >> a; cout << endl; cin >> b; 

		Translate(image, height, width, a,b); 
		break; 
		
	case 2: 
		double q, w; 
		cout << "Enter factors x, y: " << endl;
		cin >> q; cin >> w;

		Scale(image, height, width, q, w);
		break; 

	case 3: 
		double angle;
		cout << "Enter angle: " << endl;
		cin >> angle; 

		Rotate(image, height, width, angle);
		break; 

	case 4:
		double s, d; 
		cout << "Enter factors: " << endl; 
		cin >> s; cin >> d; 
		
		Shear(image, height, width, s, d); 
		break; 

	case 5: 
		AffineByMatrix(image, height, width);
		break;

	default:
		cout << "Something wrong" << endl; 
	}
	
}

int AskWhichOperation()
{
	int operation; 

	cout << endl << "Choose Affine Transformation " << endl; 
	cout << "1 - Translate" << endl; 
	cout << "2 - Scaling" << endl; 
	cout << "3 - Rotation" << endl; 
	cout << "4 - Shear" << endl; 
	cout << "5 - By Matrix " << endl; 
	cin >> operation; 

	return operation; 
}


void AffineByMatrix(Bitmap^ image, int height, int width)
{
	double a, b, c, d, e, f; 
	cout << "Enter Matrix [a b; c d; e f] " << endl; 
	cin >> a;
	cin >> b;
	cin >> c;
	cin >> d;
	cin >> e;
	cin >> f;

	int w = width * a + abs(c)*height + e; 
	int h = height * d + abs(b)*width + f; 


	Bitmap^ outputimage = AllocateImage(w+1, h+1);

	Color Px;


	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			Px = image->GetPixel(i, j);

			int posx = i*a + j*c + e;
			int posy = i*b + j*d + f;
 

			if (posx < w && posy < h && posx > 0 && posy > 0)
			{
				outputimage->SetPixel(posx, posy, Px);

				//Interpolation
				outputimage->SetPixel(posx+1, posy, Px);
				outputimage->SetPixel(posx, posy+1, Px);
				outputimage->SetPixel(posx+1, posy+1, Px);
			}						
		}
	}

	SaveImage(outputimage);
	
}



void Translate(Bitmap^ image, int height, int width, int a, int b)
{
	Bitmap^ outputimage = AllocateImage(width+a, height+b);

	Color Px;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			Px = image->GetPixel(i, j);
			outputimage->SetPixel(i + a, j + b, Px);
		}
	}

	SaveImage(outputimage);
}

void Scale(Bitmap^ image, int height, int width, double a, double b)
{
	int w = width * a; 
	int h = height * b;

	Bitmap^ outputimage = AllocateImage(w, h);

	Color Px;

	for (int i = 0; i < width*a; i++)
	{
		for (int j = 0; j < height*b; j++)
		{
			Px = image->GetPixel(i/a, j/b);

			if (i < w && j < h && i > 0 && j > 0)
				outputimage->SetPixel(i, j, Px);
		}
	}
	
	SaveImage(outputimage);
}

void Rotate(Bitmap^ image, int height, int width, double angle)
{
	double pi = 3.14159265;

	double rad = angle * pi / 180.0;

	double cs = cos(rad);
	double ss = sin(rad);

	double ssx = sin(pi/2 - rad);
	double ss90 = sin(pi / 2);
	
	int w = ss * height/ss90 + ssx * width/ss90;
	int h = ssx * height/ss90 + ss * width/ss90;

	double x0 = (double)width / 2;
	double y0 = (double)height / 2;

	 

	Bitmap^ outputimage = AllocateImage(w+1, h+1);

	Color Px;
	
	for (int i = 0; i < width ; i++)
	{
		for (int j = 0; j < height ; j++)
		{
					
			int posx = (int)round( cs * (i - x0) - ss * (j - y0) + w/2) ;
			int posy = (int)round( ss * (i - x0) + cs * (j - y0) + h/2) ;
		
			if (posx < w && posy < h && posx > 0 && posy > 0)
			{

				Px = image->GetPixel(i, j);

				outputimage->SetPixel( posx,  posy, Px);

				//Interpolation
				outputimage->SetPixel( posx+1,  posy, Px);
				outputimage->SetPixel( posx, posy+1, Px);
				outputimage->SetPixel( posx+1,  posy+1, Px);
			}
			
			
		}
	}

	
	SaveImage(outputimage);
}


void Shear(Bitmap^ image, int height, int width, double a, double b)
{
	int w = width + a*height;
	int h = height + b*width;


	Bitmap^ outputimage = AllocateImage(w, h);

	Color Px;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{

			int posx = i + a*j ;
			int posy = j + b*i ;


			if (posx < w && posy < h && posx > 0 && posy > 0)
			{
				Px = image->GetPixel(i, j);
				outputimage->SetPixel(posx, posy, Px);
			}
		}
	}

	SaveImage(outputimage);
}


