#ifndef _STR_OP_H
#define _STR_OP_H 1
#if 0
extern void *memcpy(void *__dest, const void *__src,size_t __n);
// 如果目标区域和源区域有重叠的话，memmove能够保证源串在被覆盖之前将重叠区域的字节拷贝到目标区域中。\
	但复制后src内容会被更改。但是当目标区域与源区域没有重叠则和memcpy函数功能相同。
extern void *memmove(void *__dest, const void *__src, size_t __n);
// 由src所指内存区域复制不多于count个字节到dest所指内存区域，如果遇到字符c则停止复制。\
	返回值：如果c没有被复制，则返回NULL，否则，返回字符c 后面紧挨一个字符位置的指针。
extern void *memccpy(void *__dest, const void *__src,int __c, size_t __n);
extern void *memset(void *__s, int __c, size_t __n);
extern int memcmp(const void *__s1, const void *__s2, size_t __n);
// 从s所指内存区域的[0,n)字节查找字符c。
extern void *memchr(const void *__s, int __c, size_t __n);

extern void *rawmemchr(const void *__s, int __c);
// 从s所指内存区域的[n,len)字节查找字符ch。
extern void *memrchr(const void *__s, int __c, size_t __n);
extern char *strcpy(char *__dest, const char *__src);
extern char *strncpy(char *__dest,const char *__src, size_t __n);
extern int strcoll_l(const char *__s1, const char *__s2, __locale_t __l);
extern size_t strxfrm_l(char *__dest, const char *__src, size_t __n, __locale_t __l);
extern char *strdup(const char *__s);
extern char *strndup(const char *__string, size_t __n);
// 可以查找字符串s中首次出现字符c的位置
extern char *strchr(const char *__s, int __c);
// 可以查找字符串s中末次出现字符c的位置
extern char *strrchr(const char *__s, int __c);
// c 在 s中返回首次出现位置，否则返回'\0' ???
extern char *strchrnul(const char *__s, int __c);
//无 __reject 中字符的连续字符串数
extern size_t strcspn(const char *__s, const char *__reject);
//含于 __reject 中字符的连续字符串数
extern size_t strspn(const char *__s, const char *__accept);
// 在源字符串（s1）中找出最先含有搜索字符串（s2）中任一字符的位置并返回，若找不到则返回空指针。
extern char *strpbrk(const char *__s, const char *__accept);
// strstr() 函数搜索一个字符串在另一个字符串中的第一次出现。
extern char *strstr(const char *__haystack, const char *__needle);
// 分解字符串为一组字符串。s为要分解的字符串，delim为分隔符字符串。
extern char *strtok(char *__s, const char *__delim);
// strtok_r函数是strtok函数的可重入版本。
extern char *__strtok_r(char *__s, const char *__delim, char **__save_ptr);
extern char *strtok_r(char *__s, const char *__delim,char **__save_ptr);
// 用于在c串haystack中查找c串needle，忽略大小写。如果找到则返回needle串在haystack串中第一次出现的位置的char指针
extern char *strcasestr(const char *__haystack, const char *__needle);
// memmem函数与strstr类似，不同之处是字符串needle和haystack都是字符数组，而不是以空字符结束的字符串。
extern void *memmem(const void *__haystack, size_t __haystacklen,const void *__needle, size_t __needlelen);
extern void *__mempcpy(void *__dest,const void *__src, size_t __n);
extern size_t strnlen(const char *__string, size_t __maxlen);
extern char *strerror(int __errnum) ;
extern int __xpg_strerror_r(int __errnum, char *__buf, size_t __buflen);
extern char *strerror_r(int __errnum, char *__buf, size_t __buflen);
extern char *strerror_l(int __errnum, __locale_t __l) ;
extern void __bzero(void *__s, size_t __n);
extern void bcopy(const void *__src, void *__dest, size_t __n);
extern void bzero(void *__s, size_t __n)
extern char *index(const char *__s, int __c);
extern char *rindex(const char *__s, int __c);
extern int ffs(int __i);
extern int ffsl(long int __l);
extern int ffsll(long long int __ll);
extern int strcasecmp(const char *__s1, const char *__s2);
extern int strncasecmp(const char *__s1, const char *__s2, size_t __n);
extern int strcasecmp_l(const char *__s1, const char *__s2, __locale_t __loc);
extern int strncasecmp_l(const char *__s1, const char *__s2,size_t __n, __locale_t __loc);
extern char *strsep(char **__stringp,const char *__delim);
extern char *strsignal(int __sig) ;
extern char *__stpcpy(char *__dest, const char *__src);
extern char *strfry(char *__string);
extern char *basename(const char *__filename);
extern char *strcat(char *__dest, const char *__src);
extern int strcmp(const char *__s1, const char *__s2);
extern int strcoll(const char *__s1, const char *__s2);
extern void *mempcpy(void *__dest,const void *__src, size_t __n);
extern int bcmp(const void *__s1, const void *__s2, size_t __n);
extern char *stpcpy(char *__dest, const char *__src);
extern char *stpncpy(char *__dest,const char *__src, size_t __n);
extern void *memfrob(void *__s, size_t __n);
#endif
#endif