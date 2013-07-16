#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>

#define LOGPATH "/tmp/myapp.log"

int main(int ac, char **av) {

	FILE *file_log = NULL;
	int fd_stderr;
	int fd_log;

	if(NULL == (file_log = fopen(LOGPATH, "a")))
		return EXIT_FAILURE;

	if(-1 == (fd_log = fileno(file_log))) {
		fprintf(stderr, "error: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	if(-1 == (fd_stderr = fileno(stderr))) {
		fprintf(stderr, "error: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	dup2(fd_log, fd_stderr);

	fprintf(stdout, "info: from stdin\n");
	fprintf(stderr, "error: from stderr\n");

	fclose(file_log);

	return EXIT_SUCCESS;
}
