/*
	SPDX-License-Identifier: BSD-3-Clause
	@author Dumitrescu Alexandra
	@for SO - mini-libc
*/
#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

/*
	This wrapper calls the syscall corresponding to close and sets errno in case of error.
*/
int close(int fd)
{
	int res = (int) syscall(__NR_close, fd);

	if (res < 0) {
		errno = -res;
		return -1;
	} else {
		return res;
	}
}
