/*
Make Opcode Common String Library, MakeOpcode Program's Common String Library File
Subhajit Sahu, Copyright(c) 2011
*/



#ifndef _common_string_h_


#include <stdio.h>
#include <string.h>



// Library declaration
#define _common_string_h_	loaded


// Declarations
char* GetLine(char* string);
char* GetWord(char *string);
char* GetWordSym(char *string, char *symbols);
unsigned int CountWords(char* string);
unsigned int CountWordsSym(char* string, char *symbols);
unsigned int PositionOfChar(char *string, char search);
unsigned int PositionOfString(char *string, char *search);
void RemoveSeparators(char *string);
void RemoveSeparatorsSym(char *string, char *symbols);
void RemoveComment(char *string);
void RemoveCommentSym(char *string, char *symbol);







// Get one line and then remove it from the string.
char* GetLine(char* string)
	{
	char *i, *j;
	
	i = string;
	while(*i != '\0')
		{
		if(*i == '\n')
			{
			*i = '\0';
			j  = new char[strlen(string) + 1];
			strcpy(j, string);
			strcpy(string, i + 1);
			return(j);
			}
		if((*i == '\r') && (*i == '\f'))
			{
			*i = '\0';
			j = new char[strlen(string) + 1];
			strcpy(j, string);
			strcpy(string, i + 2);
			return(j);
			}
		}
	j = new char[strlen(string) + 1];
	strcpy(j, string);
	*string = '\0';
	
	return(j);
	}








// Get a word from a string and then remove it from the string.
char* GetWord(char *string)
	{
	char *i, *j, *k;
	char c;

	i = string;
	if(*i == '\0')
		{
		j = new char[1];
		*j = '\0';
		return(j);
		}
	while(*i != '\0')
		{
		if((*i>='0' && *i<='9') || (*i>='A' && *i<='Z') || (*i>='a' && *i<='z')) break;
		i++;
		}
	if(*i == '\0')
		{
		j = new char[1];
		*j = '\0';
		*string = '\0';
		return(j);
		}
	j = i + 1;
	while(*j != '\0')
		{
		if(!((*j>='0' && *j<='9') || (*j>='A' && *j<='Z') || (*j>='a' && *j<='z'))) break;
		j++;
		}
	c = *j;
	*j = '\0';
	k = new char[strlen(i)+1];
	strcpy(k, i);
	*j = c;
	strcpy(string, j);

	return(k);
	}








	
// Get a word from a string(including some symbols)and then remove it from the string.
char* GetWordSym(char *string, char *symbols)
	{
	char *i, *j, *k;
	char c;
	
	i = string;
	if(*i == '\0')
		{
		j = new char[1];
		*j = '\0';
		return(j);
		}
	while(*i != '\0')
		{
		if((*i>='0' && *i<='9') || (*i>='A' && *i<='Z') || (*i>='a' && *i<='z') || PositionOfChar(symbols, *i)) break;
		i++;
		}
	if(*i == '\0')
		{
		j = new char[1];
		*j = '\0';
		*string = '\0';
		return(j);
		}
	j = i + 1;
	while(*j != '\0')
		{
		if(!((*j>='0' && *j<='9') || (*j>='A' && *j<='Z') || (*j>='a' && *j<='z') || PositionOfChar(symbols, *j))) break;
		j++;
		}
	c = *j;
	*j = '\0';
	k = new char[strlen(i)+1];
	strcpy(k, i);
	*j = c;
	strcpy(string, j);

	return(k);
	}





	



// Count the number of words present in a string.
unsigned int CountWords(char* string)
	{
	char *str2, *word;
	unsigned int count;

	count = 0;
	str2 = new char[strlen(string)+1];
	strcpy(str2, string);
	while(strlen(word = GetWord(str2)))
		{
		count++;
		delete word;
		}
	delete word;
	delete str2;

	return(count);
	}


	







// Count the number of words(including given symbols) present in a string.
unsigned int CountWordsSym(char* string, char *symbols)
	{
	char *str2, *word;
	unsigned int count;

	count = 0;
	str2 = new char[strlen(string)+1];
	strcpy(str2, string);
	while(strlen(word = GetWordSym(str2, symbols)))
		{
		count++;
		delete word;
		}
	delete word;
	delete str2;

	return(count);
	}


	




// Gives the position of a character in a string (index + 1)
unsigned int PositionOfChar(char *string, char search)
	{
	char *i;
	unsigned int j;

	j = 1;
	i = string;
	while(*i != '\0')
		{
		if(*i == search)return(j);
		i++;
		j++;
		}
	
	return(0);
	}







// Gives the position of a character in a string (index + 1)
unsigned int PositionOfString(char *string, char *search)
	{
	char c;
	char *i;
	unsigned int len, ends, j;

	j = 1;
	i = string;
	len = strlen(search);
	ends = 1 + strlen(string) - len;
	while(j <= ends)
		{
		c = i[len];
		i[len] = '\0';
		if(strcmp(i, search) == 0)return(j);
		i[len] = c;
		i++;
		j++;
		}
	
	return(0);
	}







// Remove all separators from a string.
void RemoveSeparators(char *string)
	{
	char *i, *j;

	i = string;
	j = string;
	while(*i != '\0')
		{
		if((*i>='0' && *i<='9') || (*i>='A' && *i<='Z') || (*i>='a' && *i<='z'))
			{
			*j = *i;
			j++;
			}
		i++;
		}
	*j = *i;
	}




	
	

// Remove all separators from a string except a given list of symbols.
void RemoveSeparatorsSym(char *string, char *symbols)
	{
	char *i, *j;

	i = string;
	j = string;
	while(*i != '\0')
		{
		if((*i>='0' && *i<='9') || (*i>='A' && *i<='Z') || (*i>='a' && *i<='z') || PositionOfChar(symbols, *i))
			{
			*j = *i;
			j++;
			}
		i++;
		}
	*j = *i;
	}








// Remove comment from a line ( comment starts with - ; ).
void RemoveComment(char *string)
	{
	unsigned int posc;

	if((posc = PositionOfChar(string, ';')) != 0) string[posc - 1] = '\0';
	}



	
	
	
	

// Remove comment from a line ( starting with given symbol ).
void RemoveCommentSym(char *string, char *symbol)
	{
	unsigned int posc;

	if((posc = PositionOfString(string, symbol)) != 0) string[posc - 1] = '\0';
	}



#endif