#pragma once

#include<stdio.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <assert.h>
#include "region.h"
#include <stdbool.h> 

#define TABLE_SIZE 1223

void insert(FILE* ptr, region** rptr)
{
	int itemcount = 0;
	int key = 0;
	char buf[MAX_LEN];
	bool overwriteAll = false;
	bool choice = false;

	while (choice == false) {
		printf("Would you like to run in Update or Insert Mode?(u/i) ");
		char c[2];
		fgets(c, 2, stdin);
		if (c[0] == 'u' || c[0] == 'U') { overwriteAll = true; choice = true; }
		else if (c[0] == 'i' || c[0] == 'I') { choice = true; }
		else { printf("Invalid input\n"); }
	}

	while (fscanf(ptr, "%d %s", &key, buf) == 2) {
		choice = false;
		itemcount++;
		if (itemcount < TABLE_SIZE)
		{
			if (key < TABLE_SIZE && key != 0)
			{
				bool overwrite = false;

				if (overwriteAll == false) {
					if ((*rptr)[key].key != 0) {
						while (choice == false) {
							printf("Item %s exists at %d, would you like to overwrite?(y/n) ", (*rptr)[key].buff, key);
							char c[2];
							scanf("%*[^\n]"); scanf("%*c");
							fgets(c, 2, stdin);
							if (c[0] == 'y' || c[0] == 'Y') { overwrite = true;  choice = true; }
							else if (c[0] == 'n' || c[0] == 'N') { choice = true; }
							else { printf("Invalid input %s %ld\n", c, sizeof(c)); }
						}
					}
					else { overwrite = true; }
				}
				
				if (overwriteAll == true || overwrite ==true) {
					memset((*rptr)[key].buff, '\0', sizeof((*rptr)[key].buff));
					(*rptr)[key].key = key;
					strcpy((*rptr)[key].buff, buf);
				}
				
			}
			else { printf("Invalid key. Keys must be between 0 and %d\n", TABLE_SIZE); }
		}
		else { printf("Table has reached max capacity\n"); }
	}

	return;
}
