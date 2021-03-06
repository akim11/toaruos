/* This file is part of ToaruOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2014 Kevin Lange
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define CHUNK_SIZE 4096

void doit(int fd) {
	lseek(fd, 0, SEEK_SET);
	while (1) {
		char buf[CHUNK_SIZE];
		memset(buf, 0, CHUNK_SIZE);
		ssize_t r = read(fd, buf, CHUNK_SIZE);
		if (!r) return;
		write(STDOUT_FILENO, buf, r);
	}
}


int main(int argc, char * argv[]) {
	int fd = open("/proc/meminfo", O_RDONLY);

	for (int i = 0; i < 500; ++i) {

		if (!fork()) {
			doit(fd);
			return 0;
		}

		waitpid(-1, NULL, 0);
	}

	close(fd);

	return 0;
}
