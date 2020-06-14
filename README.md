# Image-Processing-
University Project - implementation of several Image Transformations.
CLR application in .NET framework. Using System::Drawing namespace. 

### Standard Deviation Filtration
new value of every pixel is standard deviation of its neibourhood (size of mask)

result with mask of size 3: 

![](outputs/coke.jpg)                        ![](outputs/other/coke&#32;stdfilt.png)


### Labeling Image
dividing objects on image by labelling connected pixels using recursion

![](outputs/dots.png)

![](outputs/sprawozdanie/labels.png)

### Closing Image 
use of erosion and dilation, creating structural element

![](outputs/i.png)                       ![](outputs/other/close10_45.png)

### Affine Transformations

implementation of scaling, rotation, shear,translate and affine by transformation matrix

![](outputs/other/38st.png)

![](outputs/other/matrix2.png)

![](outputs/other/shear0.5.png)

![](outputs/other/072.png)


