/*
	SPDX-License-Identifier: BSD-3-Clause
	@author Dumitrescu Alexandra
	@for SO - mini-libc
*/
#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
	void *res = (void *) mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	mem_list_add(res, size);
	return res;
}

void *calloc(size_t nmemb, size_t size)
{
	size_t len_elements = (size_t) nmemb * size;
	void *res = (void *) mmap(0, len_elements, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	memset(res, 0, len_elements);
	mem_list_add(res, len_elements);
	return res;
}

void free(void *ptr)
{
	if(ptr != NULL) {
		struct mem_list *item = mem_list_find(ptr);
		void *cp = ptr;
		munmap(ptr, item->len);
		mem_list_del(cp);
	}
}

void *realloc(void *ptr, size_t size)
{
	if(ptr != NULL) {
		struct mem_list *item = mem_list_find(ptr);
		int len_before = item->len;
		int len_after = size;
		void *res = mremap(ptr, len_before, len_after, 1);
		item->len = size;
		item->start = res;
		return res;
	} else {
		return NULL;
	}
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	if(ptr != NULL) {
		struct mem_list *item = mem_list_find(ptr);
		int len_before = item->len;
		int len_after = nmemb * size;
		void *res = mremap(ptr, len_before, len_after, 1);
		item->len = len_after;
		item->start = res;
		return res;
	} else {
		return NULL;
	}
}
