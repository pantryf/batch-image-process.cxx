/*
 * cpp-batch-image-process, image_dos.h
 * Subhajit Sahu, Copyright(c) 2011
 */


#ifndef _image_dos_h_
#define _image_dos_h_

// required modules
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_string.h"


// function declarations
char* Run_Dos(char *params);


// Run_Dos{just a Dos command will do};
char* Run_Dos(char *params) {
	FILE *file;
	char *word;
	char *DosStr = new char[10000];
	char DosLn[256];
	int xx, len;
	// Get Dos parameters
	DosStr[0] = '\0';
	while(strlen(word = GetWordSym(params, "`~!@#$%^&-_+=.:"))) {
		strcat(DosStr, word);
		strcat(DosStr, " ");
		delete word;
	}
	delete word;
	strcat(DosStr, ">Script.tmp");
	system(DosStr);
	file = fopen("Script.tmp", "r");
	if(file == NULL) {
		strcpy(DosStr, "Can\'t execute DOS command");
		return(DosStr);
	}
	DosStr[0] = '\0';
	while((xx = fscanf(file, "%[^\n]s", DosLn)) != EOF) {
		if(xx == 0) {
			fscanf(file, "%c", DosLn);
			continue;
		}
		strcat(DosStr, DosLn);
		strcat(DosStr, "\n");
	}
	fclose(file);
	system("del Script.tmp");
	len = strlen(DosStr);
	if(len)DosStr[len-1]='\0';
	return(DosStr);
}


#endif

