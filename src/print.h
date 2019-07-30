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
	int key = 0;
	char buf[MAX_LEN];
	while (fscanf(ptr, "%d %s", &key, buf) == 2) {
		//for (int i = 0; i < TABLE_SIZE; i++) {
			if (key < TABLE_SIZE && (*rptr)[key].key != 0) {
				printf("--------\n");
				printf("key: %d | value: %s\n", (*rptr)[key].key, (*rptr)[key].buff);
			}
			else if(key < TABLE_SIZE) { printf("--------\nInvalid key. Keys must be between 0 and %d\n--------\n", TABLE_SIZE); }
			else if((*rptr)[key].key != 0)(printf("--------\nNo value exitst at key %d\n--------\n", key)
		//}
		printf("--------\n");
	}
}