#ifndef _LI_FOP_H
#define _LI_FOP_H 1
#include <stdio.h>
#include <wchar.h>

#if 0
//无锁操作
extern char *fgets_unlocked(char * __s, int __n,FILE * __stream);
extern int feof_unlocked(FILE *__stream);
extern int ferror_unlocked(FILE *__stream);
extern int fflush_unlocked(FILE *__stream);
extern int fgetc_unlocked(FILE *__stream);

extern int fputc_unlocked(int __c, FILE *__stream);
extern int fputs_unlocked(const char * __s,FILE * __stream);
extern int getc_unlocked(FILE *__stream);
extern int getchar_unlocked(void);
extern int putc_unlocked(int __c, FILE *__stream);
extern int putchar_unlocked(int __c);
extern size_t fread_unlocked(void * __ptr, size_t __size,size_t __n, FILE * __stream);
extern size_t fwrite_unlocked(const void * __ptr, size_t __size,size_t __n, FILE * __stream);
extern void clearerr_unlocked(FILE *__stream);
extern int fileno_unlocked(FILE *__stream);
/* typedef struct _IO_FILE {
    int _flags;
    char *_IO_read_ptr;
    char *_IO_read_end;
    char *_IO_read_base;
    char *_IO_write_base;
    char *_IO_write_ptr;
    char *_IO_write_end;
    char *_IO_buf_base;
    char *_IO_buf_end;
    char *_IO_save_base;
    char *_IO_backup_base;
    char *_IO_save_end;
    struct _IO_marker *_markers;
    struct _IO_FILE *_chain;
    int _fileno;
    int _flags2;
    __off_t _old_offset;
    unsigned short _cur_column;
    signed char _vtable_offset;
    char _shortbuf[1];
    _IO_lock_t *_lock;
    __off64_t _offset;
    void *__pad1;
    void *__pad2;
    void *__pad3;
    void *__pad4;
    size_t __pad5;
    int _mode;
    char _unused2[20];
}FILE; */

extern FILE *open_memstream(char **__bufloc, size_t *__sizeloc);
// 可设置分行符的行读取
extern _IO_ssize_t __getdelim(char ** __lineptr,size_t * __n, int __delimiter,FILE * __stream);
extern _IO_ssize_t getdelim(char ** __lineptr,size_t * __n, int __delimiter,FILE * __stream);
// 读取整行文本
extern _IO_ssize_t getline(char ** __lineptr,size_t * __n,FILE * __stream);
// Return the name of the controlling terminal
extern char *ctermid(char *__s);
// 取得用户账户名称
extern char *cuserid(char *__s);
extern char *fgets(char * __s, int __n, FILE * __stream);
extern char *gets(char *__s);
// 设置临时文件目录
extern char *tempnam(const char *__dir, const char *__pfx);
// 是C语言中用于产生一个唯一的文件名。
extern char *tmpnam(char *__s);
extern char *tmpnam_r(char *__s);
// 打开一个特殊的临时文件读/写(w + b)模式，当它关闭或程序终止时 该文件将被自动删除 。
extern FILE *tmpfile(void);
extern FILE *tmpfile64(void);
// 可以说是一个增强版的sprintf(),在不确定字符串的长度时，能够根据格式化的字符串长度，申请足够的内存空间。
extern int asprintf(char ** __ptr,const char * __fmt, ...);
extern int dprintf(int __fd, const char * __fmt, ...);
// 关闭除标准流（stdin、stdout、stderr、stdprn、stdaux）之外的所有打开的流，刷新所有的流缓冲区，并返回关闭的流数。
extern int fcloseall(void);
// 功能是冲洗流中的信息，该函数通常用于处理磁盘文件。fflush()会强迫将缓冲区内的数据写回参数stream 指定的文件中。
extern int fflush(FILE *__stream);
extern int fgetc(FILE *__stream);
extern int fgetpos(FILE * __stream, fpos_t * __pos);
extern int fgetpos64(FILE * __stream, fpos64_t * __pos);

extern int getc(FILE *__stream);
extern int getchar(void);
extern int getw(FILE *__stream);
extern int fscanf(FILE * __stream,const char * __format, ...);
extern int scanf(const char * __format, ...);
extern int sscanf(const char * __s,const char * __format, ...);
extern int fprintf(FILE * __stream,const char * __format, ...);
extern int fputc(int __c, FILE *__stream);
extern int fputs(const char * __s, FILE * __stream);
extern int printf(const char * __format, ...);
extern int putc(int __c, FILE *__stream);
extern int putchar(int __c);
extern int puts(const char *__s);
extern int putw(int __w, FILE *__stream);

extern int remove(const char *__filename);
extern int rename(const char *__old, const char *__new);
extern int renameat(int __oldfd, const char *__old, int __newfd,const char *__new);

// 每写完一行(遇见\n），就会把整行真正的写到磁盘文件上
extern int setvbuf(FILE * __stream, char * __buf,int __modes, size_t __n);
extern int snprintf(char * __s, size_t __maxlen,const char * __format, ...);
extern int sprintf(char * __s,const char * __format, ...);
extern int obstack_printf(struct obstack * __obstack,const char * __format, ...);
extern int obstack_vprintf(struct obstack * __obstack,const char * __format,_G_va_list __args);

// 把一个（或多个）字符退回到steam代表的文件流中，可以理解成一个“计数器”。
extern int ungetc(int __c, FILE *__stream);
/* typedef struct __va_list_tag {
    unsigned int gp_offset;
    unsigned int fp_offset;
    void *overflow_arg_area;
    void *reg_save_area;
}_G_va_list; */
extern int vasprintf(char ** __ptr, const char * __f,_G_va_list __arg);
extern int vdprintf(int __fd, const char * __fmt,_G_va_list __arg);
extern int vfprintf(FILE * __s, const char * __format,_G_va_list __arg);
extern int vfscanf(FILE * __s, const char * __format,_G_va_list __arg);
extern int vprintf(const char * __format, _G_va_list __arg);
extern int vscanf(const char * __format, _G_va_list __arg);
extern int vsnprintf(char * __s, size_t __maxlen,const char * __format, _G_va_list __arg);
extern int vsprintf(char * __s, const char * __format,_G_va_list __arg);
extern int vsscanf(const char * __s,const char * __format, _G_va_list __arg);

extern FILE *popen(const char *__command, const char *__modes);
extern int pclose(FILE *__stream);

extern FILE *fdopen(int __fd, const char *__modes);
extern int fileno(FILE *__stream);

extern FILE *fopen(const char * __filename,const char * __modes);
// 超过2G的文件（fopen）
extern FILE *fopen64(const char * __filename,const char * __modes);
// fmemopen()函数打开一个内存流，使你可以读取或写入由buf指定的缓冲区。其返回FILE*fp就是打开的内存流，\
		虽然仍使用FILE指针进行访问，但其实并没有底层文件（并没有磁盘上的实际文件，因为打开的内存流fp是在内存中的），\
		所有的I/O都是通过在缓冲区与主存（就是内存）之间来回传送字节来完成的。 
extern FILE *fmemopen(void *__s, size_t __len, const char *__modes);
// 该函数用来DIY一个流
extern FILE *fopencookie(void * __magic_cookie,const char * __modes,_IO_cookie_io_functions_t __io_funcs);
// 用于重定向输入输出流
extern FILE *freopen(const char * __filename,const char * __modes,FILE * __stream);
extern FILE *freopen64(const char * __filename,const char * __modes,FILE * __stream);
extern size_t fread(void * __ptr, size_t __size,size_t __n, FILE * __stream);
extern size_t fwrite(const void * __ptr, size_t __size,size_t __n, FILE * __s);
// 获取文件内部指针位置
extern long int ftell(FILE *__stream);	
extern __off64_t ftello64(FILE *__stream);
extern __off_t ftello(FILE *__stream);	
// 来判断文件是否执行结束，若结束，则返回非零值
extern int feof(FILE *__stream);
// stream将指向以fromwhere（偏移起始位置：文件头0(SEEK_SET)，当前位置1(SEEK_CUR)，文件尾2(SEEK_END)）为基准，\
		偏移offset（指针偏移量）个字节的位置。如果执行失败(比如offset超过文件自身大小)，则不改变stream指向的位置。
extern int fseek(FILE *__stream, long int __off, int __whence);
extern int fseeko(FILE *__stream, __off_t __off, int __whence);
extern int fseeko64(FILE *__stream, __off64_t __off, int __whence);
extern int fsetpos(FILE *__stream, const fpos_t *__pos);
extern int fsetpos64(FILE *__stream, const fpos64_t *__pos);
extern int fclose(FILE *__stream);
// clearerr的作用是使文件错误标志和文件结束标志置为0.假设在调用一个输入输出函数时出现了错误，\
		ferror函数值为一个非零值。在调用clearerr（fp）后，ferror（fp）的值变为0。
extern void clearerr(FILE *__stream);
extern int ferror(FILE *__stream);
extern void perror(const char *__s);
// 线程递归文件锁
extern void flockfile(FILE *__stream);
extern void funlockfile(FILE *__stream);
extern int ftrylockfile(FILE *__stream);
// 将文件内部的指针重新指向一个流的开头
extern void rewind(FILE *__stream);
// 把缓冲区与流相联
extern void setbuf(FILE * __stream, char * __buf);
extern void setbuffer(FILE * __stream, char * __buf,size_t __size);
// 是设置文件流为线性缓冲区
extern void setlinebuf(FILE *__stream);
#endif
#define cl_fopen(path,mode) ({\
	FILE* fp=fopen(path,mode);\
	if(!fp)perror("/fopen");\
	fp;\
})
#define cl_fread(buf,usize,nu,fp) ({\
	size_t ret_size=fread(buf,usize,nu,fp);\
	if(!ret_size)perror("/fread");\
	ret_size;\
})
#define cl_fread(buf,usize,nu,fp) ({\
	size_t ret_size=fread(buf,usize,nu,fp);\
	if(!ret_size)perror("/fread");\
	ret_size;\
})
#define cl_fwrite(buf,usize,nu,fp) ({\
	size_t ret_size=fwrite(buf,usize,nu,fp);\
	if(ret_size)perror("/fwrite");\
	ret_size;\
})
#define cl_fclose(fp) ({\
	int ret=fclose(fp);\
	if(ret)perror("/fclose");\
	ret;\
})
#endif