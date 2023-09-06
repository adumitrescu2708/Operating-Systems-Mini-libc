/*
	SPDX-License-Identifier: BSD-3-Clause
	@author Dumitrescu Alexandra
	@for SO - mini-libc
*/
#include <stdio.h>
#include <internal/syscall.h>
#include <internal/io.h>

/*
    This buffer prints to stdout given string. It first counts the number of characters
    and then calls write syscall to fd 1, stdoutb and adds the newline after printing the string.
*/
int puts(const char* str)
{
    int len = 0;
    char *aux = (char *)str;
    while ((*aux) != '\0') {
        len++;
        aux++;
    }
    write(1, str, len);
    write(1, "\n", 1);
    return 1;
}
