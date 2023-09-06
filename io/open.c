/*
	SPDX-License-Identifier: BSD-3-Clause
	@author Dumitrescu Alexandra
	@for SO - mini-libc
*/
#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

/*
	The open method opens the file given described by filename and it
	can create the file if O_CREAT flag is set. If O_CREAT is set, then a 3rd
	parameter occurs for permissions. In this case, we use va_list to handle
	3rd parameter.
*/
int open(const char *filename, int flags, ...)
{
	mode_t mode = 0;
	int res = 0;
    if ((flags & O_CREAT) >> 2 == 1) {
        va_list arg_list;
        va_start(arg_list, flags);
        mode = (mode_t) va_arg(arg_list, mode_t);
        va_end(arg_list);
		res = (int) syscall(__NR_open, filename, flags, mode);
    } else {
		res = (int) syscall(__NR_open, filename, flags);
	}
	errno = res < 0 ? -res : 0;
	if (res < 0) {
		return -1;
	} else {
		return res;
	}
}
