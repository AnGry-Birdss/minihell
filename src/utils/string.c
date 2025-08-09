/*
** minishell: src/utils/string.c
** User-implemented string/memory functions (42 Norm, no forbidden stdlib)
*/

#include <stdlib.h>
#include "minishell.h"


size_t  ft_strlen(const char *s)
{
    size_t  i;
    i = 0;
    while (s && s[i])
        i++;
    return (i);
}


char    *ft_strdup(const char *s)
{
    size_t  len;
    char    *dup;
    size_t  i;

    len = ft_strlen(s);
    dup = (char *)malloc(len + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (i < len)
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}


char    *ft_strcpy(char *dst, const char *src)
{
    size_t  i;

    i = 0;
    while (src && src[i])
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}


int ft_strcmp(const char *s1, const char *s2)
{
    size_t  i;

    i = 0;
    while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    if (!s1 || !s2)
        return (0);
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}


int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t  i;

    if (!n)
        return (0);
    i = 0;
    while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
        i++;
    if (!s1 || !s2)
        return (0);
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}


char    *ft_strchr(const char *s, int c)
{
    size_t  i;

    if (!s)
        return (NULL);
    i = 0;
    while (s[i])
    {
        if (s[i] == (char)c)
            return ((char *)&s[i]);
        i++;
    }
    if (c == 0)
        return ((char *)&s[i]);
    return (NULL);
}


char    *ft_strjoin(char const *s1, char const *s2)
{
    size_t  len1;
    size_t  len2;
    char    *res;
    size_t  i;
    size_t  j;

    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    res = (char *)malloc(len1 + len2 + 1);
    if (!res)
        return (NULL);
    i = 0;
    while (i < len1)
    {
        res[i] = s1[i];
        i++;
    }
    j = 0;
    while (j < len2)
    {
        res[i + j] = s2[j];
        j++;
    }
    res[i + j] = '\0';
    return (res);
}


char    *ft_substr(char const *s, unsigned int start, size_t len)
{
    size_t  slen;
    char    *sub;
    size_t  i;

    slen = ft_strlen(s);
    if (!s || start >= slen)
        return (ft_strdup(""));
    if (len > slen - start)
        len = slen - start;
    sub = (char *)malloc(len + 1);
    if (!sub)
        return (NULL);
    i = 0;
    while (i < len)
    {
        sub[i] = s[start + i];
        i++;
    }
    sub[i] = '\0';
    return (sub);
}


size_t  ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t  i;

    if (!dstsize)
        return (ft_strlen(src));
    i = 0;
    while (src && src[i] && i < dstsize - 1)
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (ft_strlen(src));
}


size_t  ft_strlcat(char *dst, const char *src, size_t dstsize)
{
    size_t  dlen;
    size_t  slen;
    size_t  i;

    dlen = ft_strlen(dst);
    slen = ft_strlen(src);
    if (dstsize <= dlen)
        return (dstsize + slen);
    i = 0;
    while (src && src[i] && dlen + i < dstsize - 1)
    {
        dst[dlen + i] = src[i];
        i++;
    }
    dst[dlen + i] = '\0';
    return (dlen + slen);
}


char    *ft_strcat(char *dst, const char *src)
{
    size_t  dlen;
    size_t  i;

    dlen = ft_strlen(dst);
    i = 0;
    while (src && src[i])
    {
        dst[dlen + i] = src[i];
        i++;
    }
    dst[dlen + i] = '\0';
    return (dst);
}


char    *ft_strncat(char *dst, const char *src, size_t n)
{
    size_t  dlen;
    size_t  i;

    dlen = ft_strlen(dst);
    i = 0;
    while (src && src[i] && i < n)
    {
        dst[dlen + i] = src[i];
        i++;
    }
    dst[dlen + i] = '\0';
    return (dst);
}


void    *ft_memset(void *b, int c, size_t len)
{
    size_t  i;
    unsigned char   *p;

    p = (unsigned char *)b;
    i = 0;
    while (i < len)
    {
        p[i] = (unsigned char)c;
        i++;
    }
    return (b);
}


void    *ft_memcpy(void *dst, const void *src, size_t n)
{
    size_t  i;
    unsigned char   *d;
    const unsigned char *s;

    if (!dst && !src)
        return (NULL);
    d = (unsigned char *)dst;
    s = (const unsigned char *)src;
    i = 0;
    while (i < n)
    {
        d[i] = s[i];
        i++;
    }
    return (dst);
}


void    *ft_memmove(void *dst, const void *src, size_t len)
{
    size_t  i;
    unsigned char   *d;
    const unsigned char *s;

    if (!dst && !src)
        return (NULL);
    d = (unsigned char *)dst;
    s = (const unsigned char *)src;
    if (d < s)
    {
        i = 0;
        while (i < len)
        {
            d[i] = s[i];
            i++;
        }
    }
    else
    {
        i = len;
        while (i-- > 0)
            d[i] = s[i];
    }
    return (dst);
}


int ft_memcmp(const void *s1, const void *s2, size_t n)
{
    size_t  i;
    const unsigned char *a;
    const unsigned char *b;

    a = (const unsigned char *)s1;
    b = (const unsigned char *)s2;
    i = 0;
    while (i < n)
    {
        if (a[i] != b[i])
            return (a[i] - b[i]);
        i++;
    }
    return (0);
}


void    *ft_memchr(const void *s, int c, size_t n)
{
    size_t  i;
    const unsigned char *p;

    p = (const unsigned char *)s;
    i = 0;
    while (i < n)
    {
        if (p[i] == (unsigned char)c)
            return ((void *)&p[i]);
        i++;
    }
    return (NULL);
}


void    ft_bzero(void *s, size_t n)
{
    size_t  i;
    unsigned char   *p;

    p = (unsigned char *)s;
    i = 0;
    while (i < n)
    {
        p[i] = 0;
        i++;
    }
}


void    *ft_calloc(size_t count, size_t size)
{
    void    *ptr;
    size_t  total;

    total = count * size;
    ptr = malloc(total);
    if (!ptr)
        return (NULL);
    ft_bzero(ptr, total);
    return (ptr);
}
