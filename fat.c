#include <stdio.h>
#include <stdlib.h>
#include "assign4.h"


//  Read the file into memory 32 numbers, one per line. First two numbers are 0.
void read_fat(void)
{	
	int i = 0;
	int tempInt;
	f = fopen("fat.dat", "r");
	while(fscanf(f, "%d", &tempInt) != EOF)
	{
		fat[i] = tempInt;
		i++;
	}
   fclose(f);
}

//  Write the current memory contents back to disk, overwriting the previous file.
void save_fat(void)
{
	int i = 0;
	f = fopen("fat.dat", "w");
	for (i = 0; i < 32; i++)
	{		
		fprintf(f, "%d\n", fat[i]);	
	}
	fclose(f);
}

//  Return the total number of sectors that are currently free.
int free_sectors(void)
{
	int i;
	int count;
	count = 0;
	for(i = 2; i < 32; i++)
	{
		if (fat[i] == 1)
		{
			count++;
		}
	}
	return count;
}

//  Return the lowest numbered sector that is currently free.
//	If no sectors are free a -1 is returned.
int first_free_sectors(void)
{	
	int i;
	int count = -1;
	for(i = 2; i < 32; i++)
	{
		if (fat[i] == 1)
		{
			return i;
		}
	}
	return count;
}

//  Form a chain n sectors long beginning at start_sector.
void allocate_sectors(int start_sector, int n)
{
	int i;
	int count = 0;
	
	if(fat[start_sector] == 1)
	{
		if(n != 1)
		{
			while(count < n - 1)
			{
				i = start_sector;
				while(true)
				{
					start_sector++;
					if(fat[start_sector] == 1)
					{
						break;
					}
				}
				fat[i] = start_sector;
				count++;
			}
			fat[start_sector] = 0;
		}
		else
		{
			fat[start_sector] = 0;
		}
	}
}

//  Make free the chain starting at start_sector.
void deallocate_sectors(int start_sector)
{
	int i;
	int j = fat[start_sector];
	fat[start_sector] = 1;
	while(true)
	{		
		i = fat[j];
		if (fat[j] != 0)
		{
			fat[j] = 1;
		}
		else
		{
			fat[j] = 1;
			break;
		}
		j = i;
	}
}

//  Print the chain of sectors starting at start_sector.
void print_sector_chain(int start_sector)
{
	int i = start_sector;
	printf("%d\n", i);
	while(true)
	{			
		if(fat[i] == 1 || fat[i] == 0)
		{
			break;
		}
		else
		{
			printf("%d\n", fat[i]);	
			i = fat[i];
		}
	}	
}