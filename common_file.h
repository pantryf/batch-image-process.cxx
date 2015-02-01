/*
 * cpp-batch-image-process, common_file.h
 * Subhajit Sahu, Copyright(c) 2011
 */

#ifndef _common_file_h_
#define _common_file_h_

// required modules
#include <stdio.h>


// function declarations
unsigned int FileSize(FILE *file);


// File Size (file)
unsigned int FileSize(FILE *file) {
	unsigned int currentpos, size;
	currentpos = ftell(file);
	fseek(file, 0, SEEK_END);
	size = ftell(file) + 1;
	fseek(file, currentpos, SEEK_SET);
	return(size);
}













#endif

