/*
 * cpp-batch-image-process, image_bmp.h
 * Subhajit Sahu, Copyright(c) 2011
 */


#ifndef _image_bmp_h_
#define _image_bmp_h_

// required modules
#include <mem.h>
#include <stdio.h>
#include <string.h>
#include "common_string.h"
#include "common_file.h"


// BMP file format
typedef struct fmtBMPheader {
	char Identifier[2];
	unsigned long FileSize;
	unsigned long Reserved;
	unsigned long PtrToPixelData;
	unsigned long HeaderSize;
	unsigned long Xresolution;
	unsigned long Yresolution;
	unsigned short NumColourPlanes;
	unsigned short BitsPerPixel;
	unsigned long CompressionMode;
	unsigned long PixelDataSize;
	unsigned long XpixelsPerMetre;
	unsigned long YpixelsPerMetre;
	unsigned long NumColoursUsed;
	unsigned long NumImportantColours;
} BMPheader;


// data
extern char *FileExt;
extern unsigned int FileType;
extern char *RAWdata;
BMPheader BMPinfo;


// function declarations
char* LoadBMP(FILE *file);
char* SaveBMP(FILE *file);
char* Raw24BitBMP(FILE *file);
char* BMP24BitRaw(FILE *file);
char* BMP_Info(char *params);


char* BMP_Info(char *params) {
	FILE *file, *log;
	char *word, *word2;
	int seekstatus;
	unsigned int bytesread;
	word = GetWordSym(params, "`~!@#$%^&-_+=.");
	file = fopen(word, "rb");
	if(file == NULL) {
		delete word;
		return("Image file not found");
    }
	word2 = GetWordSym(params, "`~!@#$%^&-_+=.");
	log = fopen(word2, "w");
	seekstatus = fseek(file, 0, SEEK_SET);
	if(seekstatus != 0){delete word; delete word2; return("Cannot Read given file");}
	bytesread = fread(&BMPinfo, 1, sizeof(BMPheader), file);
	if(bytesread < sizeof(BMPheader)){delete word; delete word2; return("The given File is too small");}
	if((BMPinfo.Identifier[0] != 'B') || (BMPinfo.Identifier[1] != 'M')){delete word; delete word2; return("The File is not a valid BMP file");}
	fprintf(log, "\n\nFile Information\n");
	fprintf(log, "----------------\n\n");
	fprintf(log, "Image Filename: %s\n", word);
	delete word;
	delete word2;
	fprintf(log, "Bitmap Identifier: %c%c\n", BMPinfo.Identifier[0], BMPinfo.Identifier[1]);
	fprintf(log, "File Size: %u\n", BMPinfo.FileSize);
	fprintf(log, "Reserved Value: %u\n", BMPinfo.Reserved);
	fprintf(log, "Offset to Pixel data: %u\n", BMPinfo.PtrToPixelData);
	fprintf(log, "BMP Header Size: %u\n", BMPinfo.HeaderSize);
	fprintf(log, "X Resolution of Image: %u\n", BMPinfo.Xresolution);
	fprintf(log, "Y Resolution of Image: %u\n", BMPinfo.Yresolution);
	fprintf(log, "Number of Colour planes: %u\n", BMPinfo.NumColourPlanes);
	fprintf(log, "Bits per pixel: %u\n", BMPinfo.BitsPerPixel);
	fprintf(log, "Compression Mode: %u\n", BMPinfo.CompressionMode);
	fprintf(log, "Size of Pixel data: %u\n", BMPinfo.PixelDataSize);
	fprintf(log, "Pixels per metre horizontally: %u\n", BMPinfo.XpixelsPerMetre);
	fprintf(log, "Pixels per metre vertically: %u\n", BMPinfo.YpixelsPerMetre);
	fprintf(log, "Number of Colours used: %u\n", BMPinfo.NumColoursUsed);
	fprintf(log, "Number of important Colours: %u\n\n", BMPinfo.NumImportantColours);
	fprintf(log, "----------------\n\n\n");
	fclose(log);
	fclose(file);
	return("");
}


// Loads a BMP file into Memory
char* LoadBMP(FILE *file) {
	int seekstatus;
	unsigned int bytesread;
	char *result;
	// Now read the BMP header
	seekstatus = fseek(file, 0, SEEK_SET);
	if(seekstatus != 0)return("Cannot Read given file");
	bytesread = fread(&BMPinfo, 1, sizeof(BMPheader), file);
	if(bytesread < sizeof(BMPheader))return("The given File is too small");
	if((BMPinfo.Identifier[0] != 'B') || (BMPinfo.Identifier[1] != 'M'))return("The File is not a valid BMP file");
	if(BMPinfo.Xresolution == 0)return("Weird, this BMP file has ZERO Width");
	if(BMPinfo.Yresolution == 0)return("Weird, this BMP file has ZERO Height");
	// Try to understand the file, i.e., try to convert to RAW format
	FileExt = "BMP";
	// Try 24-bit BMP
	result = Raw24BitBMP(file);
	if(strlen(result) == 0) return(result);
	
	// Try failed
	FileExt = "";
	return("Cannot understand the given BMP file");
}


// Save the BMP file from RAW format
char* SaveBMP(FILE *file) {
	char *result;
	BMPinfo.Identifier[0] = 'B';
	BMPinfo.Identifier[1] = 'M';
	BMPinfo.Reserved = 0;
	switch(FileType) {
		// 24-bit BMP file
		case 1:
		BMPinfo.PtrToPixelData = 54;
		BMPinfo.HeaderSize = 40;
		BMPinfo.NumColourPlanes = 1;
		BMPinfo.BitsPerPixel = 24;
		BMPinfo.CompressionMode = 0;
		BMPinfo.PixelDataSize = 0;
		BMPinfo.XpixelsPerMetre = 3780;
		BMPinfo.YpixelsPerMetre = 3780;
		BMPinfo.NumColoursUsed = 0;
		BMPinfo.NumImportantColours = 0;
		result = BMP24BitRaw(file);
		BMPinfo.FileSize = FileSize(file);
		fseek(file, 0, SEEK_SET);
		fwrite(&BMPinfo, 1, sizeof(BMPheader), file);
		return(result);
	}
	return("Cannot save the BMP file in the given format");
}


// Create RAW data for 24-bit BMP file
char* Raw24BitBMP(FILE *file) {
	int seekresult;
	unsigned int bytesread;
	char *BMPdata;
	unsigned long *RawData;
	unsigned long SrcRowSize, DestRowSize, DataSize, Padding, y;
	char *SrcRowPtr, *DestRowPtr;
	// Check for validity
	if(BMPinfo.BitsPerPixel != 24)return("This BMP file is not a 24-bit BMP");
	if(BMPinfo.CompressionMode != 0)return("This BMP file is compressed! Cant use that.");
	// Seek to pixel data
	seekresult = fseek(file, BMPinfo.PtrToPixelData, SEEK_SET);
	if(seekresult != 0)return("This BMP file is too small");
	// Load pixel data from file
	DestRowSize = BMPinfo.Xresolution * 3;
	Padding = (4 - (DestRowSize & 3)) & 3;
	SrcRowSize = DestRowSize + Padding;
	DataSize = BMPinfo.Yresolution * SrcRowSize;
	BMPdata = new char[DataSize];
	RAWdata = new char[(DestRowSize * BMPinfo.Yresolution) + 8];
	bytesread = fread(BMPdata, 1, DataSize, file);
	if(bytesread < DataSize) {
		delete BMPdata;
		delete RAWdata;
		return("The BMP file contains insufficient Pixel data");
	}
	// Convert to RAW data
	RawData = (unsigned long*)RAWdata;
	RawData[0] = BMPinfo.Xresolution;
	RawData[1] = BMPinfo.Yresolution;
	SrcRowPtr = BMPdata;
	DestRowPtr = RAWdata + 8 + (BMPinfo.Yresolution - 1) * DestRowSize;
	for(y=0; y<BMPinfo.Yresolution; y++) {
		memcpy(DestRowPtr, SrcRowPtr, DestRowSize);
		SrcRowPtr += SrcRowSize;
		DestRowPtr -= DestRowSize;
	}
	delete BMPdata;
	FileType = 1;
	return("");
}


char* BMP24BitRaw(FILE *file) {
	int seekresult;
	unsigned int byteswrote;
	char *BMPdata;
	unsigned long *RawData;
	unsigned long SrcRowSize, DestRowSize, DataSize, Padding, y, x;
	char *SrcRowPtr, *DestRowPtr;
	
	// Create BMP header and write it to file
	RawData = (unsigned long*)RAWdata;
	BMPinfo.Xresolution = RawData[0];
	BMPinfo.Yresolution = RawData[1];
	SrcRowSize = BMPinfo.Xresolution * 3;
	Padding = (4 - (SrcRowSize & 3)) & 3;
	DestRowSize = SrcRowSize + Padding;
	DataSize = BMPinfo.Yresolution * DestRowSize;

	// Create Pixel data
	BMPdata = new char[DataSize];
	SrcRowPtr = RAWdata + 8 + (BMPinfo.Yresolution - 1) * SrcRowSize;
	DestRowPtr = BMPdata;
	for(y=0; y<BMPinfo.Yresolution; y++) {
		memcpy(DestRowPtr, SrcRowPtr, SrcRowSize);
		for(x=0; x<Padding; x++) {
			DestRowPtr[SrcRowSize + x] = '\0';
		}
		SrcRowPtr -= SrcRowSize;
		DestRowPtr += DestRowSize;
	}

	// Write Pixel Data to file
	seekresult = fseek(file, BMPinfo.PtrToPixelData, SEEK_SET);
	if(seekresult != 0) {
		delete BMPdata;
		delete RAWdata;
		return("You probably have LOW disk space");
	}
	byteswrote = fwrite(BMPdata, 1, DataSize, file);
	if(byteswrote < DataSize) {
		delete BMPdata;
		delete RAWdata;
		return("You probably have LOW disk space");
	}
	delete BMPdata;
	return("");
}


#endif

