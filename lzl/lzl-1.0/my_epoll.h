#ifndef _UN_EPOLL_H
#define _UN_EPOLL_H 1
#include <sys/epoll.h>
#if 0
// size:Since Linux 2.6.8, the size argument is ignored, but must be greater than zero;
int epoll_create(int size);
/* flags: 0：the same of epoll_create
		 EPOLL_CLOEXEC:当进程被替换时关闭 */
int epoll_create1(int flags);
typedef union epoll_data {
    void        *ptr;
    int          fd;
    uint32_t     u32;
    uint64_t     u64;
} epoll_data_t;
//events:EPOLLIN EPOLLOUT 
struct epoll_event {
    uint32_t     events;      /* Epoll events */
    epoll_data_t data;        /* User data variable */
};
/* op :EPOLL_CTL_ADD EPOLL_CTL_MOD EPOLL_CTL_DEL \
		EPOLLRDHUP:对方关闭描述符 \
		EPOLLPRI:有紧急（带外）数据可读 \
		EPOLLHUP:? \
		EPOLLERR:? \
		EPOLLET:空闲到就绪\
		EPOLLONESHOT: 等到一次后就不再轮序\
		EPOLLWAKEUP:? \
		EPOLLEXCLUSIVE：? */
int epoll_ctl( int epfd, int op, int fd, struct epoll_event *event);
/* maxevents：events数组长度 
	timeout: -1:无限等待 \
			0:相当于非阻塞 \
			>0:等待微妙数 */
int epoll_wait( int epfd, struct epoll_event *events,int maxevents, int timeout);
int epoll_pwait(int epfd, struct epoll_event *events,int maxevents, int timeout,const sigset_t *sigmask);
#endif
#define my_epoll_create(flag) ({\
	int epfd=epoll_create1(flag);\
	if(-1==epfd)show_errno(0,"epoll_create1");\
	epfd;\
})
#define my_epoll_ctl(epfd,op,ifd,flags) ({\
    struct epoll_event ev;\
    ev.events = flags;\
    ev.data.fd = ifd;\
	int ret=epoll_ctl(epfd,op,ifd,&ev);\
	if(-1==ret)show_errno(0,"epoll_ctl");\
	ret;\
})
#define add_ep_evt(epfd,fd,flags) my_epoll_ctl(epfd,EPOLL_CTL_ADD,fd,flags)
#define del_ep_evt(epfd,fd,flags) my_epoll_ctl(epfd,EPOLL_CTL_DEL,fd,flags)
#define mod_ep_evt(epfd,fd,flags) my_epoll_ctl(epfd,EPOLL_CTL_MOD,fd,flags)
#define rvt_ep_evt(epfd,fd,flags) my_epoll_ctl(epfd,EPOLL_CTL_MOD,fd,flags==EPOLLIN?EPOLLIN:EPOLLOUT)

#define my_epoll_wait(epfd,event_a,event_n,timeout,p_sigmask) ({\
	int n_ready=0;\
	if(p_sigmask){\
		n_ready=epoll_pwait(epfd,event_a,event_n,timeout,p_sigmask);\
	}else{\
		n_ready=epoll_wait(epfd,event_a,event_n,timeout);\
	}\
	if(-1==n_ready)show_errno(0,"epoll_wait");\
	n_ready;\
})
//________________________________________________________
#define UN_SOCKET_PATH "/tmp/sock_path.unix"
#define EVENTS_SIZE 10
#define BUF_SIZE 1024
#endif