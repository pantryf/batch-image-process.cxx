/*
 * cpp-batch-image-process, ImageBHASA.cpp
 * Subhajit Sahu, Copyright(c) 2011
 */


// required modules
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "common_string.h"
#include "image_bmp.h"
#include "image_colour.h"
#include "image_edit.h"
#include "image_dos.h"


// function declarations
void Error(char *err);
char* RunScript(char *script, char *logf);


// global data
char *FileExt;
unsigned int FileType;
char *RAWdata;


// main program
main(int argn, char* args[]) {
	char *script, *log;
	script = "Script.txt";
	log = "Script.log";
	if(argn > 1)script = args[1];
	if(argn > 2)log = args[2];
	RunScript(script, log);
	return(0);
}


char* RunScript(char *script, char *logf) {
	FILE *file, *log;
	char *line, *command;
	char *word, *msg;
	int xx, clearmem;
	line = new char[512];
	command = new char[512];
	file = fopen(script, "r");
	if(file == NULL)return("Script file not found");
	log = fopen(logf, "w");
	fprintf(log, "ImageBHASA Script Log\n");
	fprintf(log, "---------------------\n\n\n");
	fprintf(log, "Script File: %s\n\n", script);
	while((xx = fscanf(file, "%[^\n]s", line)) != EOF) {
		if(xx == 0) {
			fscanf(file, "%c", line);
			continue;
		}
		RemoveComment(line);
		strcpy(command, line);
		RemoveSeparators(command);
		if(strlen(command) == 0)continue;
		fprintf(log, "#%s\n", line);
		strcpy(command, line);
		word = GetWordSym(line, "_");
		clearmem = 0;
		// App List
		if(strcmpi(word, "BMP_Info") == 0)msg = BMP_Info(line);
		// Colour based Operations
		else if(strcmpi(word, "Black_And_White") == 0)msg = Black_And_White(line);
		else if(strcmpi(word, "Make_White_Transparent") == 0)msg = Make_White_Transparent(line);
		else if(strcmpi(word, "Make_Black_Transparent") == 0)msg = Make_Black_Transparent(line);
		else if(strcmpi(word, "Brightness") == 0)msg = Brightness(line);
		else if(strcmpi(word, "Contrast") == 0)msg = Contrast(line);
		else if(strcmpi(word, "Sine_Colour") == 0)msg = Sine_Colour(line);
		else if(strcmpi(word, "Negative") == 0)msg = Negative(line);
		else if(strcmpi(word, "Add_Colour") == 0)msg = Add_Colour(line);
		else if(strcmpi(word, "Remove_Transparency") == 0)msg = Remove_Transparency(line);
		else if(strcmpi(word, "Replace_Colour") == 0)msg = Replace_Colour(line);
		else if(strcmpi(word, "Replace_Colours") == 0)msg = Replace_Colours(line);
		else if(strcmpi(word, "Get_Colour") == 0)msg = Get_Colour(line);
		// Edit based Operations
		else if(strcmpi(word, "Copy_To") == 0)msg = Copy_To(line);
		else if(strcmpi(word, "Paste_From") == 0)msg = Paste_From(line);
		else if(strcmpi(word, "Paste_From_Trans") == 0)msg = Paste_From_Trans(line);
		// Dos command
		else {
			msg = Run_Dos(command);
			clearmem = 1;
		}
		if(strlen(word)) {
			if(strlen(msg))fprintf(log, "*Error: %s\n\n", msg);
			else fprintf(log, "*Done.\n\n");
			if(clearmem)delete msg;
		}
		delete word;
		fscanf(file, "%c", line);
	}
	delete command;
	delete line;
	fclose(file);
	fclose(log);
	return("");
}


void Error(char *err) {
	printf("%s\n", err);
	getch();
	exit(0);
}

