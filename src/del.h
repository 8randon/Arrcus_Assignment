// Function Name: del()
// Description: Deletes messages at keys in table as specified by input file.
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

void del(FILE* ptr, region** rptr) 
{
	// Initializing variables
	int key = 0;
	char buf[MAX_LEN];

	// Overwriting messages as specified by keys from file and assign 'empty' message keys to zero
	while (fscanf(ptr, "%d %s", &key, buf) == 2) {
		// Set message array to \0
		memset((*rptr)[key].buff, '\0', sizeof((*rptr)[key].buff));
		(*rptr)[key].key = 0;
	}

	// Prints out remaining table
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (strlen((*rptr)[i].buff) != 0) {
			printf("key: %d\n", (*rptr)[i].key);
			printf("value: %s\n", (*rptr)[i].buff);
		}
	}

}
