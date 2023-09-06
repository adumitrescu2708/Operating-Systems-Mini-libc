
/*
	SPDX-License-Identifier: BSD-3-Clause
	@author Dumitrescu Alexandra
	@for SO - mini-libc
*/
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <internal/syscall.h>

/*
	After  - Directly used syscall __NR_fstat
	Before - Used fstatat and statx, fstatat(AT_FDCWD, path, buf, 0); 
*/
int stat(const char *restrict path, struct stat *restrict buf)
{
	int res = syscall(__NR_stat, path, buf);
	if (res < 0) {
		errno = -res;
		return -1;
	}
	return 0;
}
