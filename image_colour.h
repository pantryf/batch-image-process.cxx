/*
 * cpp-batch-image-process, image_colour.h
 * Subhajit Sahu, Copyright(c) 2011
 */


#ifndef _image_colour_h_
#define _image_colour_h_

// required modules
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common_string.h"
#include "image_struct.h"
#include "image_all.h"


// global data
extern char *RAWdata;


// function declarations
char* Black_And_White(char *params);
char* Make_White_Transparent(char *params);
char* Make_Black_Transparent(char *params);
char* Brightness(char *params);
char* Contrast(char *params);
char* Sine_Colour(char *params);
char* Negative(char *params);
char* Add_Colour(char *params);
char* Remove_Transparency(char *params);
char* Replace_Colour(char *params);
char* Replace_Colours(char *params);
char* Get_Colour(char *params);


char* Black_And_White(char *params) {
	char *word, *msg;
	RGBpixel *Pixels;
	RGBcolour Colours;
	unsigned long *RawData;
	int Monochrome;
	unsigned long Xres, Yres, Size, i;
	// Get source filename
	word = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = LoadImage(word);;
	delete word;
	if(strlen(msg))return(msg);
	Colours.Red.Value = 0;
	Colours.Green.Value = 0;
	Colours.Blue.Value = 0;
	RawData = (unsigned long*)RAWdata;
	Xres = RawData[0];
	Yres = RawData[1];
	Size = Xres * Yres;
	Pixels = (RGBpixel*)(RAWdata + 8);
	for(i=0; i<Size; i++, Pixels++) {
		Colours.Red.Pixel = Pixels->Red;
		Colours.Green.Pixel = Pixels->Green;
		Colours.Blue.Pixel = Pixels->Blue;
		Monochrome = (Colours.Red.Value + Colours.Green.Value + Colours.Blue.Value) / 3;
		Colours.Red.Value = Monochrome;
		Colours.Green.Value = Monochrome;
		Colours.Blue.Value = Monochrome;
		Pixels->Red = Colours.Red.Pixel;
		Pixels->Green = Colours.Green.Pixel;
		Pixels->Blue = Colours.Blue.Pixel;
	}
	// Get dest. filename
	word = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = SaveImage(word);
	delete word;
	return(msg);
}


char* Make_White_Transparent(char *params) {
	double ClrClose, ClrDistance;
	char *word, *msg, *save, *style;
	RGBpixel *Pixels;
	RGBcolour Colours;
	unsigned long *RawData;
	int RgbSum, ClrSum, rdis, gdis, bdis;
	unsigned long Xres, Yres, Size, i;
	// Get filename
	word = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = LoadImage(word);;
	delete word;
	if(strlen(msg))return(msg);
	// Get dest. filename
	save = GetWordSym(params, "`~!@#$%^&-_+=.:");
	// Get Colour Closeness(number)
	word = GetWordSym(params, "-.");
	ClrClose = atof(word);
	delete word;
	// Get Style
	style = GetWordSym(params, "_");
	// Make Ready
	Colours.Red.Value = 0;
	Colours.Green.Value = 0;
	Colours.Blue.Value = 0;
	RawData = (unsigned long*)RAWdata;
	Xres = RawData[0];
	Yres = RawData[1];
	Size = Xres * Yres;
	Pixels = (RGBpixel*)(RAWdata + 8);
	// Select the style
	// RGB_Sum
	if(strcmpi(style, "RGB_Sum") == 0) {
		RgbSum = (int)(ClrClose + 0.5);
		for(i=0; i<Size; i++, Pixels++) {
			Colours.Red.Pixel = Pixels->Red;
			Colours.Green.Pixel = Pixels->Green;
			Colours.Blue.Pixel = Pixels->Blue;
			ClrSum = 765 - (Colours.Red.Value + Colours.Green.Value + Colours.Blue.Value);
			if(ClrSum <= RgbSum) {
				Colours.Red.Value = 255;
				Colours.Green.Value = 255;
				Colours.Blue.Value = 255;
				Pixels->Red = Colours.Red.Pixel;
				Pixels->Green = Colours.Green.Pixel;
				Pixels->Blue = Colours.Blue.Pixel;
			}
		}
	}
	// RGB_Difference
	else if(strcmpi(style, "RGB_Distance") == 0) {
		for(i=0; i<Size; i++, Pixels++) {
			Colours.Red.Pixel = Pixels->Red;
			Colours.Green.Pixel = Pixels->Green;
			Colours.Blue.Pixel = Pixels->Blue;
			rdis = 255 - Colours.Red.Value;
			gdis = 255 - Colours.Green.Value;
			bdis = 255 - Colours.Blue.Value;
			ClrDistance = sqrt((rdis*rdis) + (gdis*gdis) + (bdis*bdis));
			if(ClrDistance <= ClrClose) {
				Colours.Red.Value = 255;
				Colours.Green.Value = 255;
				Colours.Blue.Value = 255;
				Pixels->Red = Colours.Red.Pixel;
				Pixels->Green = Colours.Green.Pixel;
				Pixels->Blue = Colours.Blue.Pixel;
			}
		}
	}
	delete style;
	msg = SaveImage(save);
	delete save;
	return(msg);
}


char* Make_Black_Transparent(char *params) {
	double ClrClose, ClrDistance;
	char *word, *msg, *save, *style;
	RGBpixel *Pixels;
	RGBcolour Colours;
	unsigned long *RawData;
	int RgbSum, ClrSum, rdis, gdis, bdis;
	unsigned long Xres, Yres, Size, i;
	// Get filename
	word = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = LoadImage(word);;
	delete word;
	if(strlen(msg))return(msg);
	// Get dest. filename
	save = GetWordSym(params, "`~!@#$%^&-_+=.:");
	// Get Colour Closeness(number)
	word = GetWordSym(params, "-.");
	ClrClose = atof(word);
	delete word;
	// Get Style
	style = GetWordSym(params, "_");
	// Make Ready
	Colours.Red.Value = 0;
	Colours.Green.Value = 0;
	Colours.Blue.Value = 0;
	RawData = (unsigned long*)RAWdata;
	Xres = RawData[0];
	Yres = RawData[1];
	Size = Xres * Yres;
	Pixels = (RGBpixel*)(RAWdata + 8);
	// Select the style
	// RGB_Sum
	if(strcmpi(style, "RGB_Sum") == 0) {
		RgbSum = (int)(ClrClose + 0.5);
		for(i=0; i<Size; i++, Pixels++) {
			Colours.Red.Pixel = Pixels->Red;
			Colours.Green.Pixel = Pixels->Green;
			Colours.Blue.Pixel = Pixels->Blue;
			ClrSum = Colours.Red.Value + Colours.Green.Value + Colours.Blue.Value;
			if(ClrSum <= RgbSum) {
				Colours.Red.Value = 255;
				Colours.Green.Value = 255;
				Colours.Blue.Value = 255;
				Pixels->Red = Colours.Red.Pixel;
				Pixels->Green = Colours.Green.Pixel;
				Pixels->Blue = Colours.Blue.Pixel;
			}
		}
	}
	// RGB_Difference
	else if(strcmpi(style, "RGB_Distance") == 0) {
		for(i=0; i<Size; i++, Pixels++) {
			Colours.Red.Pixel = Pixels->Red;
			Colours.Green.Pixel = Pixels->Green;
			Colours.Blue.Pixel = Pixels->Blue;
			rdis = Colours.Red.Value;
			gdis = Colours.Green.Value;
			bdis = Colours.Blue.Value;
			ClrDistance = sqrt((rdis*rdis) + (gdis*gdis) + (bdis*bdis));
			if(ClrDistance <= ClrClose) {
				Colours.Red.Value = 255;
				Colours.Green.Value = 255;
				Colours.Blue.Value = 255;
				Pixels->Red = Colours.Red.Pixel;
				Pixels->Green = Colours.Green.Pixel;
				Pixels->Blue = Colours.Blue.Pixel;
			}
		}
	}
	delete style;
	msg = SaveImage(save);
	delete save;
	return(msg);
}


char* Brightness(char *params) {
	char *word, *msg, *save;
	RGBpixel *Pixels;
	RGBcolour Colours;
	unsigned long *RawData;
	int Brightness;
	unsigned long Xres, Yres, Size, i;
	// Get filename
	word = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = LoadImage(word);;
	delete word;
	if(strlen(msg))return(msg);
	// Get dest. filename
	save = GetWordSym(params, "`~!@#$%^&-_+=.:");
	// Get Brightness(number)
	word = GetWordSym(params, "-.");
	Brightness = atoi(word);
	delete word;
	// Make Ready
	Colours.Red.Value = 0;
	Colours.Green.Value = 0;
	Colours.Blue.Value = 0;
	RawData = (unsigned long*)RAWdata;
	Xres = RawData[0];
	Yres = RawData[1];
	Size = Xres * Yres;
	Pixels = (RGBpixel*)(RAWdata + 8);
	for(i=0; i<Size; i++, Pixels++) {
		Colours.Red.Pixel = Pixels->Red;
		Colours.Green.Pixel = Pixels->Green;
		Colours.Blue.Pixel = Pixels->Blue;
		Colours.Red.Value += Brightness;
		Colours.Green.Value += Brightness;
		Colours.Blue.Value += Brightness;
		if(Colours.Red.Value < 0)Colours.Red.Value = 0;
		if(Colours.Green.Value < 0)Colours.Green.Value = 0;
		if(Colours.Blue.Value < 0)Colours.Blue.Value = 0;
		if(Colours.Red.Value > 255)Colours.Red.Value = 255;
		if(Colours.Green.Value > 255)Colours.Green.Value = 255;
		if(Colours.Blue.Value > 255)Colours.Blue.Value = 255;
		Pixels->Red = Colours.Red.Pixel;
		Pixels->Green = Colours.Green.Pixel;
		Pixels->Blue = Colours.Blue.Pixel;
	}
	msg = SaveImage(save);
	delete save;
	return(msg);
}


char* Contrast(char *params) {
	char *word, *msg, *save;
	RGBpixel *Pixels;
	RGBcolour Colours;
	unsigned long *RawData;
	int Contrast;
	unsigned long Xres, Yres, Size, i;
	// Get filename
	word = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = LoadImage(word);
	delete word;
	if(strlen(msg))return(msg);
	// Get dest. filename
	save = GetWordSym(params, "`~!@#$%^&-_+=.:");
	// Get Contrast(number)
	word = GetWordSym(params, "-.");
	Contrast = atoi(word);
	if(Contrast < -256)Contrast = -256;
	Contrast += 256;
	delete word;
	// Make Ready
	Colours.Red.Value = 0;
	Colours.Green.Value = 0;
	Colours.Blue.Value = 0;
	RawData = (unsigned long*)RAWdata;
	Xres = RawData[0];
	Yres = RawData[1];
	Size = Xres * Yres;
	Pixels = (RGBpixel*)(RAWdata + 8);
	for(i=0; i<Size; i++, Pixels++) {
		Colours.Red.Pixel = Pixels->Red;
		Colours.Green.Pixel = Pixels->Green;
		Colours.Blue.Pixel = Pixels->Blue;
		Colours.Red.Value = (Colours.Red.Value * Contrast) >> 8;
		Colours.Green.Value = (Colours.Green.Value * Contrast) >> 8;
		Colours.Blue.Value = (Colours.Blue.Value * Contrast) >> 8;
		if(Colours.Red.Value < 0)Colours.Red.Value = 0;
		if(Colours.Green.Value < 0)Colours.Green.Value = 0;
		if(Colours.Blue.Value < 0)Colours.Blue.Value = 0;
		if(Colours.Red.Value > 255)Colours.Red.Value = 255;
		if(Colours.Green.Value > 255)Colours.Green.Value = 255;
		if(Colours.Blue.Value > 255)Colours.Blue.Value = 255;
		Pixels->Red = Colours.Red.Pixel;
		Pixels->Green = Colours.Green.Pixel;
		Pixels->Blue = Colours.Blue.Pixel;
	}
	msg = SaveImage(save);
	delete save;
	return(msg);
}


char* Sine_Colour(char *params) {
	char *word, *msg, *save;
	RGBpixel *Pixels;
	RGBcolour Colours;
	unsigned long *RawData;
	double SinePer;
	unsigned long Xres, Yres, Size, i;
	// Get filename
	word = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = LoadImage(word);;
	delete word;
	if(strlen(msg))return(msg);
	// Get dest. filename
	save = GetWordSym(params, "`~!@#$%^&-_+=.:");
	// Get Sine Percent(number)
	word = GetWordSym(params, "-.");
	SinePer = atof(word);
	if(SinePer < 0.0)SinePer = 0.0;
	if(SinePer > 100.0) SinePer = 100.0;
	delete word;
	// Make Ready
	Colours.Red.Value = 0;
	Colours.Green.Value = 0;
	Colours.Blue.Value = 0;
	RawData = (unsigned long*)RAWdata;
	Xres = RawData[0];
	Yres = RawData[1];
	Size = Xres * Yres;
	Pixels = (RGBpixel*)(RAWdata + 8);
	for(i=0; i<Size; i++, Pixels++) {
		Colours.Red.Pixel = Pixels->Red;
		Colours.Green.Pixel = Pixels->Green;
		Colours.Blue.Pixel = Pixels->Blue;
		Colours.Red.Value = (int)((((100.0 - SinePer) * Colours.Red.Value)/ 100.0) + 0.5) + (int)(((SinePer * (2 * Colours.Red.Value * sin((2.0 * Colours.Red.Value) / M_PI ))) / 100.0) + 0.5);
		Colours.Green.Value = (int)((((100.0 - SinePer) * Colours.Green.Value)/ 100.0) + 0.5) + (int)(((SinePer * (2* Colours.Green.Value * sin((2.0 * Colours.Green.Value) / M_PI ))) / 100.0) + 0.5);
		Colours.Blue.Value = (int)((((100.0 - SinePer) * Colours.Blue.Value)/ 100.0) + 0.5) + (int)(((SinePer * (2 * Colours.Blue.Value * sin((2.0 * Colours.Blue.Value) / M_PI ))) / 100.0) + 0.5);
		if(Colours.Red.Value < 0)Colours.Red.Value = 0;
		if(Colours.Green.Value < 0)Colours.Green.Value = 0;
		if(Colours.Blue.Value < 0)Colours.Blue.Value = 0;
		if(Colours.Red.Value > 255)Colours.Red.Value = 255;
		if(Colours.Green.Value > 255)Colours.Green.Value = 255;
		if(Colours.Blue.Value > 255)Colours.Blue.Value = 255;
		Pixels->Red = Colours.Red.Pixel;
		Pixels->Green = Colours.Green.Pixel;
		Pixels->Blue = Colours.Blue.Pixel;
	}
	msg = SaveImage(save);
	delete save;
	return(msg);
}


char* Negative(char *params) {
	char *word, *msg;
	RGBpixel *Pixels;
	RGBcolour Colours;
	unsigned long *RawData;
	unsigned long Xres, Yres, Size, i;
	// Get source filename
	word = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = LoadImage(word);;
	delete word;
	if(strlen(msg))return(msg);
	// Start
	Colours.Red.Value = 0;
	Colours.Green.Value = 0;
	Colours.Blue.Value = 0;
	RawData = (unsigned long*)RAWdata;
	Xres = RawData[0];
	Yres = RawData[1];
	Size = Xres * Yres;
	Pixels = (RGBpixel*)(RAWdata + 8);
	for(i=0; i<Size; i++, Pixels++) {
		Colours.Red.Pixel = Pixels->Red;
		Colours.Green.Pixel = Pixels->Green;
		Colours.Blue.Pixel = Pixels->Blue;
		Colours.Red.Value = ~Colours.Red.Value;
		Colours.Green.Value = ~Colours.Green.Value;
		Colours.Blue.Value = ~Colours.Blue.Value;
		Pixels->Red = Colours.Red.Pixel;
		Pixels->Green = Colours.Green.Pixel;
		Pixels->Blue = Colours.Blue.Pixel;
	}
	// Get dest. filename
	word = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = SaveImage(word);
	delete word;
	return(msg);
}


char* Add_Colour(char *params) {
	char *word, *msg, *save;
	RGBpixel *Pixels;
	RGBcolour Colours;
	unsigned long *RawData;
	int AddRed, AddGreen, AddBlue;
	unsigned long Xres, Yres, Size, i;
	// Get source filename
	word = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = LoadImage(word);
	delete word;
	if(strlen(msg))return(msg);
	save = GetWordSym(params, "`~!@#$%^&-_+=.:");
	word = GetWord(params);
	AddRed = atoi(word);
	delete word;
	word = GetWord(params);
	AddGreen = atoi(word);
	delete word;
	word = GetWord(params);
	AddBlue = atoi(word);
	delete word;
	Colours.Red.Value = 0;
	Colours.Green.Value = 0;
	Colours.Blue.Value = 0;
	RawData = (unsigned long*)RAWdata;
	Xres = RawData[0];
	Yres = RawData[1];
	Size = Xres * Yres;
	Pixels = (RGBpixel*)(RAWdata + 8);
	for(i=0; i<Size; i++, Pixels++) {
		Colours.Red.Pixel = Pixels->Red;
		Colours.Green.Pixel = Pixels->Green;
		Colours.Blue.Pixel = Pixels->Blue;
		Colours.Red.Value += AddRed;
		Colours.Green.Value += AddGreen;
		Colours.Blue.Value += AddBlue;
		if(Colours.Red.Value < 0)Colours.Red.Value = 0;
		if(Colours.Green.Value < 0)Colours.Green.Value = 0;
		if(Colours.Blue.Value < 0)Colours.Blue.Value = 0;
		if(Colours.Red.Value > 255)Colours.Red.Value = 255;
		if(Colours.Green.Value > 255)Colours.Green.Value = 255;
		if(Colours.Blue.Value > 255)Colours.Blue.Value = 255;
		Pixels->Red = Colours.Red.Pixel;
		Pixels->Green = Colours.Green.Pixel;
		Pixels->Blue = Colours.Blue.Pixel;
	}
	// Get dest. filename
	msg = SaveImage(save);
	delete save;
	return(msg);
}


char* Remove_Transparency(char *params) {
	char *word, *msg;
	RGBpixel *Pixels;
	RGBcolour Colours;
	unsigned long *RawData;
	unsigned long Xres, Yres, Size, i;
	// Get source filename
	word = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = LoadImage(word);;
	delete word;
	if(strlen(msg))return(msg);
	Colours.Red.Value = 0;
	Colours.Green.Value = 0;
	Colours.Blue.Value = 0;
	RawData = (unsigned long*)RAWdata;
	Xres = RawData[0];
	Yres = RawData[1];
	Size = Xres * Yres;
	Pixels = (RGBpixel*)(RAWdata + 8);
	for(i=0; i<Size; i++, Pixels++) {
		Colours.Red.Pixel = Pixels->Red;
		Colours.Green.Pixel = Pixels->Green;
		Colours.Blue.Pixel = Pixels->Blue;
		if((Colours.Red.Value == 255) && (Colours.Green.Value == 255) && (Colours.Blue.Value == 255)) {
			Colours.Red.Value = 254;
			Colours.Green.Value = 254;
			Colours.Blue.Value = 254;
			Pixels->Red = Colours.Red.Pixel;
			Pixels->Green = Colours.Green.Pixel;
			Pixels->Blue = Colours.Blue.Pixel;
		}
	}
	// Get dest. filename
	word = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = SaveImage(word);
	delete word;
	return(msg);
}


char* Replace_Colour(char *params) {
	char *word, *msg, *save;
	RGBpixel *Pixels;
	RGBcolour Colours;
	unsigned long *RawData;
	unsigned long Xres, Yres, Size, i;
	int OldRed, OldGreen, OldBlue, NewRed, NewGreen, NewBlue;
	// Get source filename
	word = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = LoadImage(word);;
	delete word;
	if(strlen(msg))return(msg);
	save = GetWordSym(params, "`~!@#$%^&-_+=.:");
	word = GetWord(params);
	OldRed = atoi(word);
	delete word;
	word = GetWord(params);
	OldGreen = atoi(word);
	delete word;
	word = GetWord(params);
	OldBlue = atoi(word);
	delete word;
	word = GetWord(params);
	NewRed = atoi(word);
	delete word;
	word = GetWord(params);
	NewGreen = atoi(word);
	delete word;
	word = GetWord(params);
	NewBlue = atoi(word);
	delete word;
	Colours.Red.Value = 0;
	Colours.Green.Value = 0;
	Colours.Blue.Value = 0;
	RawData = (unsigned long*)RAWdata;
	Xres = RawData[0];
	Yres = RawData[1];
	Size = Xres * Yres;
	Pixels = (RGBpixel*)(RAWdata + 8);
	for(i=0; i<Size; i++, Pixels++) {
		Colours.Red.Pixel = Pixels->Red;
		Colours.Green.Pixel = Pixels->Green;
		Colours.Blue.Pixel = Pixels->Blue;
		if((Colours.Red.Value == OldRed) && (Colours.Green.Value == OldGreen) && (Colours.Blue.Value == OldBlue)) {
			Colours.Red.Value = NewRed;
			Colours.Green.Value = NewGreen;
			Colours.Blue.Value = NewBlue;
			Pixels->Red = Colours.Red.Pixel;
			Pixels->Green = Colours.Green.Pixel;
			Pixels->Blue = Colours.Blue.Pixel;
		}
	}
	// Get dest. filename
	msg = SaveImage(save);
	delete save;
	return(msg);
}


char* Replace_Colours(char *params) {
	char *word, *msg, *save;
	RGBpixel *Pixels;
	RGBcolour Colours;
	unsigned long *RawData;
	unsigned long Xres, Yres, Size, i;
	int OldRed, OldGreen, OldBlue, NewRed, NewGreen, NewBlue;
	double OldPerStart, OldPerStop, NewPerStart, NewPerStop, PerRed, PerGreen, PerBlue, PerRatio, OldPer, t;
	// Get source filename
	word = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = LoadImage(word);
	printf("Source File: %s\n", word);
	delete word;
	if(strlen(msg))return(msg);
	save = GetWordSym(params, "`~!@#$%^&-_+=.:");
	printf("Dest File: %s\n", save);
	word = GetWord(params);
	OldRed = atoi(word);
	delete word;
	word = GetWord(params);
	OldGreen = atoi(word);
	delete word;
	word = GetWord(params);
	OldBlue = atoi(word);
	delete word;
	printf("OldColour:   %d:%d:%d\n", OldRed, OldGreen, OldBlue);
	word = GetWordSym(params, ".");
	OldPerStart = atof(word);
	delete word;
	word = GetWordSym(params, ".");
	OldPerStop = atof(word);
	delete word;
	printf("OldRange:   %f%% - %f%%\n", OldPerStart, OldPerStop);
	word = GetWord(params);
	NewRed = atoi(word);
	delete word;
	word = GetWord(params);
	NewGreen = atoi(word);
	delete word;
	word = GetWord(params);
	NewBlue = atoi(word);
	delete word;
	printf("NewColour:   %d:%d:%d\n", NewRed, NewGreen, NewBlue);
	word = GetWordSym(params, ".");
	NewPerStart = atof(word);
	delete word;
	word = GetWordSym(params, ".");
	NewPerStop = atof(word);
	delete word;
	printf("NewRange:   %f%% - %f%%\n", NewPerStart, NewPerStop);
	if(OldPerStop < OldPerStart) {
		t = OldPerStop;
		OldPerStop = OldPerStart;
		OldPerStart = t;
	}
	if(NewPerStop < NewPerStart) {
		t = NewPerStop;
		NewPerStop = NewPerStart;
		NewPerStart = t;
	}
	OldPerStart /= 100.0;
	OldPerStop /= 100.0;
	NewPerStart /= 100.0;
	NewPerStop /= 100.0;
	if(OldPerStart == OldPerStop) PerRatio = 0;
	else PerRatio = (NewPerStop - NewPerStart) / (OldPerStop - OldPerStart);
	printf("OldRange:   %f%% - %f%%\n", OldPerStart, OldPerStop);
	printf("NewRange:   %f%% - %f%%\n", NewPerStart, NewPerStop);
	printf("PerRatio: %f\n", PerRatio);
	Colours.Red.Value = 0;
	Colours.Green.Value = 0;
	Colours.Blue.Value = 0;
	RawData = (unsigned long*)RAWdata;
	Xres = RawData[0];
	Yres = RawData[1];
	Size = Xres * Yres;
	Pixels = (RGBpixel*)(RAWdata + 8);
	for(i=0; i<Size; i++, Pixels++) {
		Colours.Red.Pixel = Pixels->Red;
		Colours.Green.Pixel = Pixels->Green;
		Colours.Blue.Pixel = Pixels->Blue;
		PerRed = (double)Colours.Red.Value / (double)OldRed;
		PerGreen = (double)Colours.Green.Value / (double)OldGreen;
		PerBlue = (double)Colours.Blue.Value / (double)OldBlue;
		OldPer = PerRed;
		if(PerGreen < OldPer)OldPer = PerGreen;
		if(PerBlue < OldPer)OldPer = PerBlue;
		if((OldPer >= OldPerStart) && (OldPer <= OldPerStop)) {
			//printf("OldPer: %f\n", OldPer);
			if(OldPerStop != OldPerStart) {
				PerRed = NewPerStart + (PerRed - OldPerStart) * PerRatio;
				PerGreen = NewPerStart + (PerGreen - OldPerStart) * PerRatio;
				PerBlue = NewPerStart + (PerBlue - OldPerStart) * PerRatio;
				Colours.Red.Value = (int)((double)NewRed * PerRed);
				Colours.Green.Value = (int)((double)NewGreen * PerGreen);
				Colours.Blue.Value = (int)((double)NewBlue * PerBlue);
			}
			else {
				Colours.Red.Value = (int)((double)NewRed * OldPer);
				Colours.Green.Value = (int)((double)NewGreen * OldPer);
				Colours.Blue.Value = (int)((double)NewBlue * OldPer);
			}
			if(Colours.Red.Value < 0)Colours.Red.Value = 0;
			if(Colours.Green.Value < 0)Colours.Green.Value = 0;
			if(Colours.Blue.Value < 0)Colours.Blue.Value = 0;
			if(Colours.Red.Value > 255)Colours.Red.Value = 255;
			if(Colours.Green.Value > 255)Colours.Green.Value = 255;
			if(Colours.Blue.Value > 255)Colours.Blue.Value = 255;
			Pixels->Red = Colours.Red.Pixel;
			Pixels->Green = Colours.Green.Pixel;
			Pixels->Blue = Colours.Blue.Pixel;
		}
	}
	// Get dest. filename
	msg = SaveImage(save);
	delete save;
	//scanf("%c", &c);
	return(msg);
}


char* Get_Colour(char *params) {
	FILE *file;
	char *word, *msg, *save, *src;
	RGBpixel *Pixels;
	RGBcolour Colours;
	unsigned long *RawData;
	unsigned long Xres, Yres, Xpix, Ypix;
	// Get source filename
	src = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = LoadImage(src);
	if(strlen(msg))return(msg);
	save = GetWordSym(params, "`~!@#$%^&-_+=.:");
	word = GetWord(params);
	Xpix = atoi(word);
	delete word;
	word = GetWord(params);
	Ypix = atoi(word);
	delete word;
	Colours.Red.Value = 0;
	Colours.Green.Value = 0;
	Colours.Blue.Value = 0;
	RawData = (unsigned long*)RAWdata;
	Xres = RawData[0];
	Yres = RawData[1];
	Pixels = (RGBpixel*)(RAWdata + 8);
	if((Xpix >= Xres) || (Ypix >= Yres)) {
		delete src;
		delete save;
		return("The Pixel asked for, is not within this image");
	}
	Pixels += (Yres - Ypix - 1) * Xres + Xpix;
	Colours.Red.Pixel = Pixels->Red;
	Colours.Green.Pixel = Pixels->Green;
	Colours.Blue.Pixel = Pixels->Blue;
	file = fopen(save, "w");
	delete save;
	if(file == NULL) {
		delete src;
		return("Cannot open File for saving Colour, probably low disk space");
	}
	fprintf(file, "Get Colour Information\n");
	fprintf(file, "----------------------\n\n\n");
	fprintf(file, "Image File: %s\n", src);
	fprintf(file, "Pixel:      (%u, %u)\n", Xpix, Ypix);
	fprintf(file, "Colour:     %d : %d : %d\n\n\n", Colours.Red.Value, Colours.Green.Value, Colours.Blue.Value);
	// Get dest. filename
	fclose(file);
	msg = SaveImage(src);
	delete src;
	return(msg);
}


// Decrease Colours - reduce to a set of  ? colours and to ? extent
// Increase Colours - increase from a set of ? colours and to ? extent
// Replace Particular Colour - replace ? particular colour with ? colour
// Replace Colour group - replace ? range of colours with ? group of colours
// Make Glow - create a glow effect to ? white range ? extent
// Make Dark - make blacker parts ? range more dark ? extent


#endif

