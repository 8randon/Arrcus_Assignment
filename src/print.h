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
	for (int i = 0; i < TABLE_SIZE; i++) {
		if ((*rptr)[i].key != 0) {
			printf("key: %d\n", (*rptr)[i].key);
			printf("value: %s\n", (*rptr)[i].buff);
		}
		printf("%d, %s\n", (*rptr)[10].key, (*rptr)[10].buff);
	}
}