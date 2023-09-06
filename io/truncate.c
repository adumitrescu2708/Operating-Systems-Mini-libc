/*
	SPDX-License-Identifier: BSD-3-Clause
	@author Dumitrescu Alexandra
	@for SO - mini-libc
*/
#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

/*
	This wrapper calls the syscall corresponding to truncate and sets errno in case of error.
*/
int truncate(const char *path, off_t length)
{
	int res = (int) syscall(__NR_truncate, path, length);
	if (res < 0) {
		errno = -res;
		return -1;
	} else {
		return res;
	}
}
