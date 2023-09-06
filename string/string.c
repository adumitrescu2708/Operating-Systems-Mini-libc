
/*
	SPDX-License-Identifier: BSD-3-Clause
	@author Dumitrescu Alexandra
	@for SO - mini-libc
*/
#include <string.h>
#include <stdlib.h>


/*
	Copies the string stored in source in destionation, null-terminated.
	Used an auxiliar buffer to store the beginning address of the string.
*/
char *strcpy(char *destination, const char *source)
{
	char *destination_aux = destination;
	while((*source) != '\0') {
		(*destination_aux) = (*source);
		destination_aux++;
		source++;
	}

	(*destination_aux) = '\0';
	return destination;
}

/*
	Copies first len bytes from source to destination, not null-terminated.
	If the source has less than len bytes, then the destination is padded with null bytes.
	Used an auxiliar buffer to store the beginning address of the string.
*/
char *strncpy(char *destination, const char *source, size_t len)
{
	char *destination_aux = destination;
	size_t i = 0;

	for(i = 0; i < len && (*source) != '\0'; i++, source++, destination_aux++) {
		(*destination_aux) = (*source);
	}

	if(i != len) {
		for(size_t j = i; j < len; j++) {
			(*destination_aux) = '\0';
		}
	}

	return destination;
}

/*
	Appends all bytes from source starting from the null character in destination.
	The result is null-terminated. Used an auxiliar buffer to store the beginning address of the string.
*/
char *strcat(char *destination, const char *source)
{
	char *destination_aux = destination;
	while((*destination_aux) != '\0') {
		destination_aux++;
	}

	while((*source) != '\0') {
		(*destination_aux) = (*source);
		destination_aux++;
		source++;
	}

	(*destination_aux) = '\0';
	return destination_aux;
}


/*
	Appends len bytes from source to destination starting from null character in destination.
	If the source has less than len bytes then only the content before null is appended.
	The result is null-terminated. Used an auxiliar buffer to store the beginning address of the string.
*/
char *strncat(char *destination, const char *source, size_t len)
{
	if(source == NULL) {
		return destination;
	}

	char *destination_aux = destination;

	while(((*destination_aux) != '\0')) {
		destination_aux++;
	}

	for(size_t i = 0; i < len && (*source) != '\0'; i++, destination_aux++, source++) {
		(*destination_aux) = (*source);
	}

	(*destination_aux) = '\0';

	return destination;
}

/*
	Compares strings and returns 0 if strings are equal. 
	Keeps comparing each character in both strings until a difference is found.
	Returns a negative value if s2nd string has higher int-value for different character
	and positive value otherwise.
*/
int strcmp(const char *str1, const char *str2)
{
	unsigned int ascii_str1 = 0, ascii_str2 = 0;

	for(; (*str1) != '\0' && (*str2) != '\0'; str1++, str2++) {
		ascii_str1 = (unsigned int) (*str1);
		ascii_str2 = (unsigned int) (*str2);
		if(ascii_str1 != ascii_str2) {
			return (ascii_str1 > ascii_str2) ? 1 : -1;
		}
	}

	if((*str1) != '\0') {
		return 1;
	}

	if((*str2) != '\0') {
		return -1;
	}

	if((*str1) == '\0' && (*str2) == '\0') {
		return 0;
	}

	return 0;
}

/*
	Compares first len bytes in the strings, acts similar to strcmp() method.
*/
int strncmp(const char *str1, const char *str2, size_t len)
{
	unsigned int ascii_1 = 0, ascii_2 = 0;
	size_t i;
	for(i = 0; i != len && ((*str1) != '\0' && (*str2) != '\0'); i++, str1++, str2++) {
		ascii_1 = (unsigned int) (*str1);
		ascii_2 = (unsigned int) (*str2);
		if(ascii_1 != ascii_2) {
			return (ascii_1 > ascii_2) ? 1 : -1;
		}
	}

	if(i == len) {
		return 0;
	}

	if((*str1) != '\0') {
		return 1;
	}

	if((*str2) != '\0') {
		return -1;
	}

	return 0;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

/*
	Returns the address of first occurance of given character in str, or NULL if not found.
*/
char *strchr(const char *str, int c)
{
	if(str == NULL) {
		return NULL;
	}
	for(char *ptr = (char *)str; (*ptr) != '\0'; ptr ++) {
		if((*ptr) == (char) c) {
			return ptr;
		}
	}

	return NULL;
}

/*
	Returns the address of last occurance of given character in str, or NULL if not found.
*/
char *strrchr(const char *str, int c)
{
	if(str == NULL) {
		return NULL;
	}

	char *last_occurance = NULL;

	for(char *ptr = (char *)str; (*ptr) != '\0'; ptr++) {
		if((*ptr) == (char) c) {
			last_occurance = ptr;
		}
	}

	return last_occurance;
}

/*
	Returns the address of first occurance of given string in source, or NULL if not found.
	Checks if the needle can be found starting from each position in haystack.
*/
char *strstr(const char *haystack, const char *needle)
{
	if(haystack == NULL || needle == NULL) {
		return NULL;
	}

	for(char *p = (char *)haystack; (*p) != '\0'; p++) {
		short int is_needle_found = 1;
		char *ptr1 = p;
		for(char *ptr2 = (char *)needle; (*ptr2) != '\0' && is_needle_found == 1; ptr2++, ptr1++) {
			if((*ptr1) != (*ptr2)) {
				is_needle_found = -1;
			}
		}
		if(is_needle_found == 1) {
			return p;
		}
	}
	return NULL;
}

/*
	Returns the address of last occurance of given string in source, or NULL if not found.
	Checks if the needle can be found starting from each position in haystack.
	Stores the last successful search in haystack.
*/
char *strrstr(const char *haystack, const char *needle)
{
	if(haystack == NULL || needle == NULL) {
		return NULL;
	}

	char *last_occurance = NULL;

	for(char *p = (char *)haystack; (*p) != '\0'; p++) {
		short int is_needle_found = 1;
		char *ptr1 = p;
		for(char *ptr2 = (char *)needle; (*ptr2) != '\0' && is_needle_found == 1; ptr2++, ptr1++) {
			if((*ptr1) != (*ptr2)) {
				is_needle_found = -1;
			}
		}
		if(is_needle_found == 1) {
			last_occurance = p;
		}
	}
	return last_occurance;
}

/*
	Copies num bytes from source to destination. Used an auxiliar buffer to store the
	beginning address of the string.
*/
void *memcpy(void *destination, const void *source, size_t num)
{
	char *ptr1 = (char *)destination;
	char *ptr2 = (char *)source;

	for(size_t i = 0; i < num; i++) {
		(*ptr1) = (*ptr2);
		ptr1++;
		ptr2++;
	}
	return destination;
}

/*
	Copies num bytes from source to destination, allowing overlap between source and destination.
	Used an auxiliar buffer to store saved string in source and then copy to destination.
*/
void *memmove(void *destination, const void *source, size_t num)
{
	char *ptr1 = (char *)destination;
	char *ptr2 = (char *)source;
	const int kLen = num;
	char aux[kLen + 1];
	char *aux_cp = aux;
	for(size_t i = 0; i < num; i++) {
		(*aux_cp) = (*ptr2);
		ptr2++;
		aux_cp++;
	}

	for(size_t i = 0; i < num; i++) {
		(*ptr1) = aux[i];
		ptr1++;
	}

	return destination;
}

/*
	Compares ptr1 and ptr2. Method similar to strcmp.
*/
int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	char *p1 = (char *)ptr1;
	char *p2 = (char *)ptr2;
	unsigned int ascii_1 = 0, ascii_2 = 0;
	size_t i;
	for(i = 0; i < num && (*p1) != '\0' && (*p2) != '\0'; p1++, p2++, i++) {
		ascii_1 = (unsigned int) (*p1);
		ascii_2 = (unsigned int) (*p2);
		if(ascii_1 != ascii_2) {
			return (ascii_1 > ascii_2) ? 1 : -1;
		}
	}
	if(i == num) {
		return 0;
	}

	if((*p1) == '\0') {
		return -1;
	}

	if((*p2) == '\0') {
		return 1;
	}

	return 0;
}

/*
	Sets num bytes in source with given token.
*/
void *memset(void *source, int value, size_t num)
{
	if(source == NULL) {
		return NULL;
	}

	char *ptr = (char *)source;
	unsigned char token = (unsigned char) value;
	for(size_t i = 0; i < num; i++, ptr++) {
		(*ptr) = token;
	}

	return source;
}
