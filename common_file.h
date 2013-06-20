/*
Make Opcode Common String Library, MakeOpcode Program's Common String Library File
Subhajit Sahu, Copyright(c) 2011
*/



#ifndef _common_file_h_


#include <stdio.h>



// Library declaration
#define _common_file_h_		loaded





// Declarations
unsigned int FileSize(FILE *file);





unsigned int FileSize(FILE *file)
	{
	unsigned int currentpos, size;
	
	currentpos = ftell(file);
	fseek(file, 0, SEEK_END);
	size = ftell(file) + 1;
	fseek(file, currentpos, SEEK_SET);
	return(size);
	}













#endif

