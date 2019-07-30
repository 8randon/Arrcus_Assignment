// Arrcus assignment
// Author: Brandon Townsend

#include <assert.h>
#include "insert.h"
#include "del.h"
#include "print.h"

#define MAX_LEN 1000
#define TABLE_SIZE 1223

int main(int argc, char *argv[])
{
	// Making sure there are the correct number of args
	if (argc != 3) {
		printf("USAGE: Arrcus_Assignment input_file mode\n");
		exit(1);
	}

	struct region *rptr;
	int fd;

	//create shared memory object
	fd = shm_open("/myregion", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

	// Error handling
	if (fd == -1) {
		printf("ERROR Shared memory not created\n");
		exit(1);
	}

	if (ftruncate(fd, sizeof(struct region)*TABLE_SIZE) == -1){
		printf("ERROR Memory not truncated\n");
		exit(1);
	}

	// Set size and permissions of shared memory
	rptr = mmap(NULL, sizeof(struct region)*TABLE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (rptr == MAP_FAILED) {
		printf("ERROR Memory not mapped\n");
		exit(1);
	}
	
	int key = 0;

	//Opening file
	FILE* ptr = fopen(argv[1], "r");

	if (ptr == NULL)
	{
		printf("no such file.\n");
		return 0;
	}

	// Reset file
	rewind(ptr);

	char buf[MAX_LEN];
	
	// Runs functions based on user input
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

	// Closing file
	fclose(ptr);
	return 0;
}
