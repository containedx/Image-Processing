#include "pch.h"
#include "ImageOperations.h"

Bitmap^ LoadImage(char* path)
{
    Bitmap^ image;
    String^ path_to_image;
    path_to_image = gcnew String(path);

    try
    {
        image = gcnew Bitmap(path_to_image, true);
    }
    catch (...)
    {
        cout << "Bad Path!!!";  
    }

    return image;
}

Bitmap^ AllocateImage(int x, int y)
{
    Bitmap^ newimage = gcnew Bitmap(x, y); 
    
    Color Px = Color::FromArgb(0, 0, 0);
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            newimage->SetPixel(i, j, Px);

    return newimage; 
}


void SaveImage(Bitmap^ image)
{
    image->Save("C:\\Users\\Kinia\\Desktop\\output.png");
}

void SaveImage(Bitmap^ image, String^ path)
{
    image->Save(path); 
}

                                                                                                                                                                                                                                                                                                                                                                                                                  