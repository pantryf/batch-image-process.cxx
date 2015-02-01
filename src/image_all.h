/*
 * cpp-batch-image-process, image_all.h
 * Subhajit Sahu, Copyright(c) 2011
 */


#ifndef _image_all_h_
#define _image_all_h_

// required modules
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common_file.h"
#include "image_bmp.h"


// data
extern char *FileExt;


// function declarations
char* LoadImage(char *imgfile);
char* SaveImage(char *imgfile);


// Load the BMP file as RAW format
char* LoadImage(char *imgfile) {
	char *msg;
	char Ext[32];
	FILE *file;
	unsigned int ExtIndex;
	file = fopen(imgfile, "rb");
	if(file == NULL)return("The Filename you gave does not exist");
	ExtIndex = PositionOfChar(imgfile, '.');
	strcpy(Ext, imgfile + ExtIndex);
	//Choose from Extension name
	if(strcmpi(Ext, "BMP") == 0)msg = LoadBMP(file);
	else {
		fclose(file);
		return("Failed to load image of given format");
	}
	fclose(file);
	return(msg);
}


// Load the BMP file as RAW format
char* SaveImage(char *imgfile) {
	char *msg;
	char Ext[32];
	FILE *file;
	unsigned int ExtIndex;
	file = fopen(imgfile, "wb");
	if(file == NULL)return("There is probably insufficient disk space");
	ExtIndex = PositionOfChar(imgfile, '.');
	strcpy(Ext, imgfile + ExtIndex);
	// Choose from Extension name
	if(strcmpi(Ext, "BMP") == 0)msg = SaveBMP(file);
	else {
		fclose(file);
		if(strlen(FileExt))delete RAWdata;
		return("Failed to Save image in given format");
	}
	fclose(file);
	if(strlen(FileExt))delete RAWdata;
	return(msg);
}


#endif

