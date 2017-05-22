#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assign4.h"

FILE *f;
int fat[32];
char dirStr[30][20];
int dirInt[30];

int main()
{
	read_fat();
	read_dir();
	
	char state[80];
	char input[80];
	int index;
	while(true)
	{
		printf(":");
		scanf("%s", state);
		
		if(strcmp(state, "sectors") == 0)
		{
			scanf("%s", input);
			index = does_file_exist_in_dir(input);
			if(index != -1)
			{
				print_sector_chain(dirInt[index]);
			}
			else
			{
				printf("File does not exist\n");
			}
		}
		else if(strcmp(state, "delete") == 0)
		{
			scanf("%s", input);
			index = does_file_exist_in_dir(input);
			if(index != -1)
			{
				deallocate_sectors(dirInt[index]);
				delete_file_from_dir(index);
				save_fat();
				save_dir();
			}
			else
			{
				printf("File does not exist\n");
			}
		}
		else if(strcmp(state, "add") == 0)
		{
			int number;
			scanf("%s %d", input, &number);			
			index = first_free_sectors();
			if(index != -1)
			{				
				if(free_sectors() >= number)
				{					
					if(does_file_exist_in_dir(input) == -1)
					{
						allocate_sectors(index, number);
						add_file_to_dir(input, index);
						save_fat();
						save_dir();
					}
					else
					{
						printf("File already exists\n");
					}
				}
				else
				{
					printf("Not enough free sectors\n");
				}
			}			
			else
			{
				printf("Directory is full\n");
			}
		}
		else if(strcmp(state, "dir") == 0)
		{
			print_dir();
		}
		else if(strcmp(state, "quit") == 0)
		{
			exit(2);
		}		
	}
}