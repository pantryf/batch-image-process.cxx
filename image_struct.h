/*
ImageBHASA Structures Library, ImageBHASA Program's Structures Library File
Subhajit Sahu, Copyright(c) 2011
*/


#ifndef _image_struct_h_


// Library declaration
#define _image_struct_h_		loaded



// Structures
typedef struct fmtRGBpixel
	{
	char Blue;
	char Green;
	char Red;
	}RGBpixel;


typedef union fmtColour
	{
	char Pixel;
	int Value;
	}Colour;


typedef struct fmtRGBcolour
	{
	Colour Blue;
	Colour Green;
	Colour Red;
	}RGBcolour;








#endif

