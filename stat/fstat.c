
/*
	SPDX-License-Identifier: BSD-3-Clause
	@author Dumitrescu Alexandra
	@for SO - mini-libc
*/
#include <sys/stat.h>
#include <errno.h>
#include <internal/syscall.h>
/*
	After  - Directly used syscall __NR_fstat
	Before - Used fstatat and statx, fstatat(fd, "", st, AT_EMPTY_PATH); 
*/
int fstat(int fd, struct stat *st)
{
	int res = syscall(__NR_fstat, fd, st);
	if (res < 0) {
		errno = -res;
		return -1;
	}
	return 0;
}
