#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assign4.h"

//  Read the directory information into memory.
void read_dir(void)
{
	int i = 0;
	char tempStr[13];
	int tempInt;
	
	f = fopen("dir.dat", "r");
	while(fscanf(f, "%s %d", tempStr, &tempInt) != EOF)
	{
		strcpy(dirStr[i], tempStr);
		dirInt[i] = tempInt;
		i++;
	}
	fclose(f);
}

//  Save the current directory information overwriting the previous file.
void save_dir(void)
{
	int i = 0;
	f = fopen("dir.dat", "w");
	while(dirInt[i] != 0)
	{
		fprintf(f, "%s %d\n", dirStr[i], dirInt[i]);
		i++;
	}
	fclose(f);
}

//  Print the current directory, one file per line formate: filename start-sector
void print_dir(void)
{
	int i = 0;
	while(i < 30)
	{
		if (dirInt[i] != 0)
		{
			printf("%s %d\n", dirStr[i], dirInt[i]);
			i++;
		}
		else
		{
			i++;
		}
	}
}

//  Return -1 if the files does not exist, else return its position in the directory
int does_file_exist_in_dir(char *file)
{
	int i = 0;
	while(i < 30)
	{
		if(strstr(dirStr[i], file) != NULL)
		{
			return i;
		}
		else
		{
			i++;
		}
	}
	return -1;
}

//  Add file to memory image of directory.
void add_file_to_dir(char *file, int start_sector)
{
	int i = 0;
	while(i < 30)
	{
		if(dirInt[i] == 0)
		{
			strcpy(dirStr[i], file);
			dirInt[i] = start_sector;
			break;
		}
		else
		{
			i++;
		}
	}	
}

//  Delete file from memory image of directory.
void delete_file_from_dir(int position)
{
	strcpy(dirStr[position], "");
	dirInt[position] = 0;
}