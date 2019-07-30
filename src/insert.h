// Function Name: insert()
// Description: Inserts messages at keys in table as specified by input file.
//              Update Mode overwrites all collisions, while Insert Mode asks before overwriting.
// Inputs: Pointer to input file object and pointer to pointer to mapped memory
// Author: Brandon Townsend

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
	// Variable initiation
	int itemcount = 0;
	int key = 0;
	char buf[MAX_LEN];
	bool overwriteAll = false;
	bool choice = false;

	// Asking user which mode they wish to run in
	while (choice == false) {
		printf("Would you like to run in Update or Insert Mode?(u/i) ");
		char c[2];
		fgets(c, 2, stdin);
		if (c[0] == 'u' || c[0] == 'U') { overwriteAll = true; choice = true; }
		else if (c[0] == 'i' || c[0] == 'I') { choice = true; }
		else { printf("Invalid input\n"); }
	}

	// Reading file
	while (fscanf(ptr, "%d %s", &key, buf) == 2) {
		choice = false;
		itemcount++;

		// User shouldn't be inserting more items than the table can hold, as they would be
		// making redundant updates/insertions.
		if (itemcount < TABLE_SIZE)
		{
			// If the key is valid...
			if (key < TABLE_SIZE && key != 0)
			{
				bool overwrite = false;

				// If the user chose insert mode...
				if (overwriteAll == false) {
					// And if the current key is populated..
					if ((*rptr)[key].key != 0) {
						while (choice == false) {
							// Ask the user if they want to overwrite the message at the current key
							printf("Item %s exists at %d, would you like to overwrite?(y/n) ", (*rptr)[key].buff, key);
							// Make buffer and clear stream
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
				
				//If the user chose Update Mode or to overwrite the message at the current key...
				if (overwriteAll == true || overwrite ==true) {
					// Set message array to \0
					memset((*rptr)[key].buff, '\0', sizeof((*rptr)[key].buff));
					// Set values
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
