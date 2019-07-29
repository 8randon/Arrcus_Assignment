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
	int key = 0;
	char buf[MAX_LEN];

	while (fscanf(ptr, "%d %s", &key, buf) == 2) {
		memset((*rptr)[key].buff, '\0', sizeof((*rptr)[key].buff));
		(*rptr)[key].key = 0;
	}

	for (int i = 0; i < TABLE_SIZE; i++) {

		if (strlen((*rptr)[i].buff) != 0) {
			printf("key: %d\n", (*rptr)[i].key);
			printf("value: %s\n", (*rptr)[i].buff);
		}
	}

}
