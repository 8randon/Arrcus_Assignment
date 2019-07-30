//#ifdef _MSC_VER
//#define _CRT_SECURE_NO_WARNINGS


#include <assert.h>
#include "insert.h"
#include "del.h"
#include "print.h"

#define MAX_LEN 1000
#define TABLE_SIZE 1223




int main(int argc, char *argv[])
{
	struct region *rptr;
	int fd;

	//create shm obj and set its size

	fd = shm_open("/myregion", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

	if (fd == -1)
		printf("ERROR\n");

	if (ftruncate(fd, sizeof(struct region)*TABLE_SIZE) == -1)
		printf("ERROR\n");

	rptr = mmap(NULL, sizeof(struct region)*TABLE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (rptr == MAP_FAILED)
		printf("ERROR\n");


	int key = 0;
	FILE* ptr = fopen(argv[1], "r");

	if (ptr == NULL)
	{
		printf("no such file.\n");
		return 0;
	}

	rewind(ptr);

	char buf[MAX_LEN];

	for (int p = 0; p < TABLE_SIZE; p++)
	{
		memset(rptr[p].buff, '\0', sizeof(rptr[p].buff));
		rptr[p].key = 0;
		strcpy(rptr[p].buff, buf);
	}
	
	if (strcmp(argv[2], "1") == 0) {
		insert(ptr, &rptr);
	}
	else if (strcmp(argv[2], "2") == 0) {
		del(ptr, &rptr);
	}
	else if (strcmp(argv[2], "3") == 0) {
		print(ptr, &rptr);
	}
	else {
		printf("Invalid input %s.\n", argv[2]);
		printf("Acceptable commands are\n1: Update/Insert\n2: Delete\n3: Print\n");
	}

	fclose(ptr);
	return 0;
}
