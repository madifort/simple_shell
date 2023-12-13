#include "madifort.h"

/**
 * set_memory - Fills memory with a constant byte.
 * @n: The number of bytes to be filled.
 * @s: Pointer to the memory area.
 * @b: The byte to fill *s with.
 * Return: A pointer to the memory area s.
 */
char *set_memory(char *s, char b, unsigned int n)
{
    unsigned int m = 0;
    while (m < n)
    {
        s[m] = b;
        m++;
    }
    return (s);
}

/**
 * free_memory - Frees a string of strings.
 * @zz: String of strings.
 */
void free_memory(char **zz)
{
    char **a = zz;

    if (!zz)
        return;
    while (*zz)
    {
        free(*zz);
        zz++;
    }
    free(a);
}

/**
 * resize_memory - Reallocates a block of memory.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 * @ptr: Pointer to the previous malloc'ated block.
 * Return: Pointer to the old block if new_size is zero,
 *         a pointer to the new block otherwise.
 */
void *resize_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
    unsigned int m = 0;
    char *z;

    if (!ptr)
        return malloc(new_size);
    if (!new_size)
    {
        free(ptr);
        return NULL;
    }
    if (new_size == old_size)
        return ptr;

    z = malloc(new_size);
    if (!z)
        return NULL;

    while (m < old_size && m < new_size)
    {
        z[m] = ((char *)ptr)[m];
        m++;
    }

    free(ptr);
    return z;
}


