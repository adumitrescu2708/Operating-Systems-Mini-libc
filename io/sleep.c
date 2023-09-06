/*
	SPDX-License-Identifier: BSD-3-Clause
	@author Dumitrescu Alexandra
	@for SO - mini-libc
*/
#include <unistd.h>
#include <time.h>
#include <internal/syscall.h>
#include <internal/arch/x86_64/syscall_list.h>
#include <string.h>

/*
    This wrapper uses nanosleep method.
*/
unsigned sleep(unsigned int seconds)
{
    struct timespec time, rem;
    memset(&time, 0, sizeof(struct timespec));
    time.tv_sec = seconds;
    unsigned res = (unsigned) nanosleep(&time, &rem);
    return res;
}
