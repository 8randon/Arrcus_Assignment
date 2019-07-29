#pragma once

#define MAX_LEN 1000

typedef struct region {
	int len;
	int key;
	char buff[MAX_LEN];
}region;
