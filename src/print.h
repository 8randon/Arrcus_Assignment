// Function Name: print()
// Description: Prints out messages at keys in table as specified by input file.
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

void print(FILE* ptr, region**rptr)
{
	// Variable initialization
	int key = 0;
	char buf[MAX_LEN];

	//Read through file line-by-line
	while (fscanf(ptr, "%d %s", &key, buf) == 2) {

		//Checking to see if keys are valid and printing results
		if (key < TABLE_SIZE && (*rptr)[key].key != 0) {
			printf("--------\n");
			printf("key: %d | value: %s\n", (*rptr)[key].key, (*rptr)[key].buff);
		}
		else if(key > TABLE_SIZE) { printf("--------\nInvalid key. Keys must be between 0 and %d\n--------\n", TABLE_SIZE); }
		else if ((*rptr)[key].key == 0) { (printf("--------\nNo value exists at key %d\n--------\n", key)); }

		printf("--------\n");
	}
}