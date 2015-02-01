/*
 * cpp-batch-image-process, image_struct.h
 * Subhajit Sahu, Copyright(c) 2011
 */


#ifndef _image_struct_h_
#define _image_struct_h_


// Structures
typedef struct fmtRGBpixel {
	char Blue;
	char Green;
	char Red;
} RGBpixel;


typedef union fmtColour {
	char Pixel;
	int Value;
} Colour;


typedef struct fmtRGBcolour {
	Colour Blue;
	Colour Green;
	Colour Red;
} RGBcolour;


#endif

