/*
 * cpp-batch-image-process, image_edit.h
 * Subhajit Sahu, Copyright(c) 2011
 */


#ifndef _image_edit_h_
#define _image_edit_h_

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
char* Copy_To(char *params);
char* Paste_From(char *params);
char* Paste_From_Trans(char *params);


// Copy_To(srcfile,destfile,xs,ys,xr,yr);
char* Copy_To(char *params) {
	char *word, *msg, *save;
	RGBpixel *Pixels, *Pixels2;
	// RGBcolour Colours;
	unsigned long *RawData;
	unsigned long Xres, Yres, i, j, PixSkip;
	unsigned long xstart, ystart, xsize, ysize;
	// Get source filename
	word = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = LoadImage(word);
	delete word;
	if(strlen(msg)){return(msg);}
	// Get destination filename
	save = GetWordSym(params, "`~!@#$%^&-_+=.:");
	word = GetWord(params);
	xstart = atoi(word);
	delete word;
	word = GetWord(params);
	ystart = atoi(word);
	delete word;
	word = GetWord(params);
	xsize = atoi(word);
	delete word;
	word = GetWord(params);
	ysize = atoi(word);
	delete word;
	// Checkups
	if(xstart < 0)xstart = 0;
	if(ystart < 0)ystart = 0;
	if(xsize < 1)xsize = 1;
	if(ysize < 1)ysize = 1;
	// Initialize Colours
	// Colours.Red.Value = 0;
	// Colours.Green.Value = 0;
	// Colours.Blue.Value = 0;
	RawData = (unsigned long*)RAWdata;
	Xres = RawData[0];
	Yres = RawData[1];
	// Size = Xres * Yres;
	Pixels = (RGBpixel*)(RAWdata + 8);
	if((xstart >= Xres) || (ystart >= Yres)) {
		delete save;
		delete RAWdata;
		return("Nothing to Capture! Beyond image limit.");
	}
	if(xstart + xsize > Xres)xsize = Xres - xstart;
	if(ystart + ysize > Yres)ysize = Yres - ystart;
	PixSkip = Xres - xsize;
	Pixels2 = Pixels + (ystart * Xres + xstart);
	for(i=0; i<ysize; i++, Pixels2+=PixSkip) {
		for(j=0; j<xsize; j++, Pixels2++, Pixels++) {
			*Pixels = *Pixels2;
		}
	}
	RawData[0] = xsize;
	RawData[1] = ysize;
	// Save dest. file
	msg = SaveImage(save);
	delete save;
	return(msg);
}


// Paste_From(srcfile,destfile,xs,ys);
char* Paste_From(char *params) {
	char *word, *msg, *save;
	RGBpixel *Pixels1, *Pixels2;
	unsigned long *RawData1, *RawData2;
	unsigned long Xres, Yres, i, j, PixSkip;
	unsigned long xstart, ystart, xsize, ysize;
	// Get source filename
	word = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = LoadImage(word);
	delete word;
	if(strlen(msg))return(msg);
	RawData1 = (unsigned long*)RAWdata;
	// Get destination filename
	save = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = LoadImage(save);
	if(strlen(msg)){delete save;return(msg);}
	RawData2 = (unsigned long*)RAWdata;
	// Ger parameters
	word = GetWord(params);
	xstart = atoi(word);
	delete word;
	word = GetWord(params);
	ystart = atoi(word);
	delete word;
	// General Checkups
	if(xstart < 0)xstart = 0;
	if(ystart < 0)ystart = 0;
	// Getting Info
	xsize = RawData1[0];
	ysize = RawData1[1];
	Xres = RawData2[0];
	Yres = RawData2[1];
	Pixels1 = (RGBpixel*)(RawData1 + 2);
	Pixels2 = (RGBpixel*)(RawData2 + 2);
	if((xstart >= Xres) || (ystart >= Yres)) {
		delete save;
		delete RawData1;
		delete RawData2;
		return("Nowhere to Paste! Beyond image limit.");
	}
	if(xstart + xsize > Xres)xsize = Xres - xstart;
	if(ystart + ysize > Yres)ysize = Yres - ystart;
	PixSkip = Xres - xsize;
	Pixels2 = Pixels2 + (ystart * Xres + xstart);
	for(i=0; i<ysize; i++, Pixels2+=PixSkip) {
		for(j=0; j<xsize; j++, Pixels2++, Pixels1++) {
			*Pixels2 = *Pixels1;
		}
	}
	delete RawData1;
	// Save dest. file
	msg = SaveImage(save);
	delete save;
	return(msg);
}


// Paste_From_Trans(srcfile,destfile,xs,ys,transclr);
char* Paste_From_Trans(char *params) {
	char *word, *msg, *save;
	RGBcolour Colours;
	RGBpixel *Pixels1, *Pixels2;
	unsigned long *RawData1, *RawData2;
	unsigned long Xres, Yres, i, j, PixSkip;
	unsigned long xstart, ystart, xsize, ysize;
	int TransRed, TransGreen ,TransBlue;
	// Get source filename
	word = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = LoadImage(word);
	delete word;
	if(strlen(msg))return(msg);
	RawData1 = (unsigned long*)RAWdata;
	// Get destination filename
	save = GetWordSym(params, "`~!@#$%^&-_+=.:");
	msg = LoadImage(save);
	if(strlen(msg)){delete save;return(msg);}
	RawData2 = (unsigned long*)RAWdata;
	// Ger parameters
	word = GetWord(params);
	xstart = atoi(word);
	delete word;
	word = GetWord(params);
	ystart = atoi(word);
	delete word;
	word = GetWord(params);
	TransRed = atoi(word);
	delete word;
	word = GetWord(params);
	TransGreen = atoi(word);
	delete word;
	word = GetWord(params);
	TransBlue = atoi(word);
	delete word;
	// General Checkups
	if(xstart < 0)xstart = 0;
	if(ystart < 0)ystart = 0;
	// Getting Info
	xsize = RawData1[0];
	ysize = RawData1[1];
	Xres = RawData2[0];
	Yres = RawData2[1];
	Pixels1 = (RGBpixel*)(RawData1 + 2);
	Pixels2 = (RGBpixel*)(RawData2 + 2);
	if((xstart >= Xres) || (ystart >= Yres)) {
		delete save;
		delete RawData1;
		delete RawData2;
		return("Nowhere to Paste! Beyond image limit.");
	}
	if(xstart + xsize > Xres)xsize = Xres - xstart;
	if(ystart + ysize > Yres)ysize = Yres - ystart;
	PixSkip = Xres - xsize;
	Pixels2 = Pixels2 + (ystart * Xres + xstart);
	// Initialize Colours
	Colours.Red.Value = 0;
	Colours.Green.Value = 0;
	Colours.Blue.Value = 0;
	for(i=0; i<ysize; i++, Pixels2+=PixSkip) {
		for(j=0; j<xsize; j++, Pixels2++, Pixels1++) {
			Colours.Red.Pixel	= Pixels1->Red;
			Colours.Green.Pixel	= Pixels1->Green;
			Colours.Blue.Pixel	= Pixels1->Blue;
			if((Colours.Red.Value != TransRed) || (Colours.Green.Value != TransGreen) || (Colours.Blue.Value != TransBlue))
				*Pixels2 = *Pixels1;
		}
	}
	delete RawData1;
	// Save dest. file
	msg = SaveImage(save);
	delete save;
	return(msg);
}


#endif

