#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {

	int fd;
	char buffer[100];
	int nbytes;
	int seek;
	struct stat fs; // man stat.3

	// open

	umask(0);
	fd = open("test.txt", O_CREAT | O_RDWR, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fd == -1) {
		fprintf(stderr, "Fail while open file.\n");
		return 1;
	}
	fprintf(stdout, "fd = %d\n", fd);

	// read

	nbytes = read(fd, buffer, sizeof(buffer));
	if (nbytes == -1) {
		fprintf(stderr, "Fail while read file.\n");
		return 2;
	}
	fprintf(stdout, "nbytes read = %d\n", nbytes);
	fprintf(stdout, "buffer read = %s", buffer);

	// fstat

	if (fstat(fd, &fs) == -1) {
		fprintf(stderr, "Fail while fstat file.\n");
		return 3;
	}
	fprintf(stdout, "file fstat size =  %d bytes\n", fs.st_size);

	// lseek

	seek = lseek(fd, 2 * sizeof(char), SEEK_SET);
	if (seek == -1) {
		fprintf(stderr, "Fail while seek file.");
		return 4;
	}
	fprintf(stdout, "seek = %d\n", seek);

	// write

	strcpy((char*)buffer, "xyz");
	nbytes = write(fd, buffer, 3 * sizeof(char));
	if (nbytes == -1) {
		fprintf(stderr, "Fail while write file.");
		return 5;
	}
	fprintf(stdout, "nbytes write = %d\n", nbytes);
	fprintf(stdout, "buffer write = %s\n", buffer);

	// close

	if (close(fd) == -1) {
		fprintf(stderr, "Fail while close file.\n");
		return 6;
	}
	fprintf(stdout, "closed fd = %d\n", fd);

	// stat

	if (stat("test.txt", &fs) == -1) {
		fprintf(stderr, "Fail while stat file.\n");
		return 7;
	};
	fprintf(stdout, "file stat size = %d bytes\n", fs.st_size);

	return 0;
}
