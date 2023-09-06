/*
	SPDX-License-Identifier: BSD-3-Clause
	@author Dumitrescu Alexandra
	@for SO - mini-libc
*/
#include <time.h>
#include <errno.h>
#include <internal/syscall.h>
#include <internal/arch/x86_64/syscall_list.h>

/*
	This wrapper calls the syscall corresponding to ftrunchate and sets errno in case of error.
*/
int nanosleep(const struct timespec *req, struct timespec *rem)
{
    int res = (int) syscall(__NR_nanosleep, req, rem);
    if (res < 0) {
        errno = -res;
        return -1;
    } else {
        return res;
    }
}
