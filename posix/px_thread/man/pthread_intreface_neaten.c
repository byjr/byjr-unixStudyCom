
extern int pthread_attr_init(pthread_attr_t *__attr);
extern int pthread_attr_destroy(pthread_attr_t *__attr);
extern int pthread_attr_getaffinity_np(const pthread_attr_t *__attr,size_t __cpusetsize,cpu_set_t *__cpuset);
extern int pthread_attr_getdetachstate(const pthread_attr_t *__attr,int *__detachstate);
extern int pthread_attr_getguardsize(const pthread_attr_t *__attr,size_t *__guardsize);
extern int pthread_attr_getinheritsched(const pthread_attr_t *__attr,int *__inherit);
extern int pthread_attr_getschedparam(const pthread_attr_t *__attr,struct sched_param *__param);
extern int pthread_attr_getschedpolicy(const pthread_attr_t *__attr,int *__policy);
extern int pthread_attr_getscope(const pthread_attr_t *__attr,int *__scope);
extern int pthread_attr_getstack(const pthread_attr_t *__attr,void **__stackaddr,size_t *__stacksize);
// extern int pthread_attr_getstackaddr(const pthread_attr_t *__attr,void **__stackaddr);
extern int pthread_attr_getstacksize(const pthread_attr_t *__attr,size_t *__stacksize);
extern int pthread_attr_setaffinity_np(pthread_attr_t *__attr,size_t __cpusetsize,const cpu_set_t *__cpuset);
extern int pthread_attr_setdetachstate(pthread_attr_t *__attr,int __detachstate);
extern int pthread_attr_setguardsize(pthread_attr_t *__attr,size_t __guardsize);
extern int pthread_attr_setinheritsched(pthread_attr_t *__attr,int __inherit);
extern int pthread_attr_setschedparam(pthread_attr_t *__attr,const struct sched_param *__param);
extern int pthread_attr_setschedpolicy(pthread_attr_t *__attr,int __policy);
extern int pthread_attr_setscope(pthread_attr_t *__attr,int __scope);
extern int pthread_attr_setstack(pthread_attr_t *__attr,void *__stackaddr,size_t __stacksize);
// extern int pthread_attr_setstackaddr(pthread_attr_t *__attr,void *__stackaddr);
// extern int pthread_attr_setstacksize(pthread_attr_t *__attr,size_t __stacksize);
extern int pthread_setattr_default_np(const pthread_attr_t *__attr);
extern int pthread_getattr_default_np(pthread_attr_t *__attr);
extern int pthread_setschedparam(pthread_t __target_thread,int __policy,const struct sched_param *__param);
extern int pthread_getschedparam(pthread_t __target_thread,int *__policy,struct sched_param *__param);
extern int pthread_getattr_np(pthread_t __th,pthread_attr_t *__attr);
extern int pthread_setaffinity_np(pthread_t __th,size_t __cpusetsize,const cpu_set_t *__cpuset);
extern int pthread_setschedprio(pthread_t __target_thread,int __prio);

extern int pthread_create(pthread_t *__newthread,const pthread_attr_t *__attr,void *(*__start_routine)(void *),void *__arg);
extern pthread_t pthread_self(void);
extern int pthread_detach(pthread_t __th);
extern int pthread_cancel(pthread_t __th);
extern void pthread_testcancel(void);
extern int pthread_setcancelstate(int __state,int *__oldstate);
extern int pthread_setcanceltype(int __type,int *__oldtype);

extern int pthread_yield(void);
extern int pthread_once(pthread_once_t *__once_control,void(*__init_routine)(void));
extern void pthread_exit(void *__retval);
extern int pthread_join(pthread_t __th,void **__thread_return);
extern int pthread_timedjoin_np(pthread_t __th,void **__thread_return,const struct timespec *__abstime);
extern int pthread_tryjoin_np(pthread_t __th,void **__thread_return);
extern int pthread_atfork(void(*__prepare)(void),void(*__parent)(void),void(*__child)(void));
extern int pthread_equal(pthread_t __thread1,pthread_t __thread2);

extern int pthread_key_create(pthread_key_t *__key,void(*__destr_function)(void *));
extern int pthread_key_delete(pthread_key_t __key);
extern void *pthread_getspecific(pthread_key_t __key);
extern int pthread_setspecific(pthread_key_t __key,const void *__pointer);
//并发度控制
extern int pthread_getconcurrency(void);
extern int pthread_setconcurrency(int __level);

extern int pthread_getname_np(pthread_t __target_thread,char *__buf,size_t __buflen);
extern int pthread_setname_np(pthread_t __target_thread,const char *__name);

extern int pthread_getcpuclockid(pthread_t __thread_id,__clockid_t *__clock_id);

//栏杆
extern int pthread_barrier_destroy(pthread_barrier_t *__barrier);
extern int pthread_barrier_init(pthread_barrier_t *__barrier,const pthread_barrierattr_t *__attr,unsigned int __count);
extern int pthread_barrier_wait(pthread_barrier_t *__barrier);
extern int pthread_barrierattr_destroy(pthread_barrierattr_t *__attr);
extern int pthread_barrierattr_getpshared(const pthread_barrierattr_t *__attr,int *__pshared);
extern int pthread_barrierattr_init(pthread_barrierattr_t *__attr);
extern int pthread_barrierattr_setpshared(pthread_barrierattr_t *__attr,int __pshared);

//条件
extern int pthread_cond_broadcast(pthread_cond_t *__cond);
extern int pthread_cond_destroy(pthread_cond_t *__cond);
extern int pthread_cond_init(pthread_cond_t *__cond,const pthread_condattr_t *__cond_attr);
extern int pthread_cond_signal(pthread_cond_t *__cond);
extern int pthread_cond_timedwait(pthread_cond_t *__cond,pthread_mutex_t *__mutex,const struct timespec *__abstime);
extern int pthread_cond_wait(pthread_cond_t *__cond,pthread_mutex_t *__mutex);
extern int pthread_condattr_destroy(pthread_condattr_t *__attr);
extern int pthread_condattr_getclock(const pthread_condattr_t *__attr,__clockid_t *__clock_id);
extern int pthread_condattr_getpshared(const pthread_condattr_t *__attr,int *__pshared);
extern int pthread_condattr_init(pthread_condattr_t *__attr);
extern int pthread_condattr_setclock(pthread_condattr_t *__attr,__clockid_t __clock_id);
extern int pthread_condattr_setpshared(pthread_condattr_t *__attr,int __pshared);

//互斥锁
extern int pthread_mutex_consistent(pthread_mutex_t *__mutex);
extern int pthread_mutex_destroy(pthread_mutex_t *__mutex);
extern int pthread_mutex_getprioceiling(const pthread_mutex_t *__mutex,int *__prioceiling);
extern int pthread_mutex_init(pthread_mutex_t *__mutex,const pthread_mutexattr_t *__mutexattr);
extern int pthread_mutex_lock(pthread_mutex_t *__mutex);
extern int pthread_mutex_setprioceiling(pthread_mutex_t *__mutex,int __prioceiling,int *__old_ceiling);
extern int pthread_mutex_timedlock(pthread_mutex_t *__mutex,const struct timespec *__abstime);
extern int pthread_mutex_trylock(pthread_mutex_t *__mutex);
extern int pthread_mutex_unlock(pthread_mutex_t *__mutex);
extern int pthread_mutexattr_destroy(pthread_mutexattr_t *__attr);
extern int pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *__attr,int *__prioceiling);
extern int pthread_mutexattr_getprotocol(const pthread_mutexattr_t *__attr,int *__protocol);
extern int pthread_mutexattr_getpshared(const pthread_mutexattr_t *__attr,int *__pshared);
extern int pthread_mutexattr_getrobust(const pthread_mutexattr_t *__attr,int *__robustness);
extern int pthread_mutexattr_gettype(const pthread_mutexattr_t *__attr,int *__kind);
extern int pthread_mutexattr_init(pthread_mutexattr_t *__attr);
extern int pthread_mutexattr_setprioceiling(pthread_mutexattr_t *__attr,int __prioceiling);
extern int pthread_mutexattr_setprotocol(pthread_mutexattr_t *__attr,int __protocol);
extern int pthread_mutexattr_setpshared(pthread_mutexattr_t *__attr,int __pshared);
extern int pthread_mutexattr_setrobust(pthread_mutexattr_t *__attr,int __robustness);
extern int pthread_mutexattr_settype(pthread_mutexattr_t *__attr,int __kind);

//读写锁
extern int pthread_rwlock_destroy(pthread_rwlock_t *__rwlock);
extern int pthread_rwlock_init(pthread_rwlock_t *__rwlock,const pthread_rwlockattr_t *__attr);
extern int pthread_rwlock_rdlock(pthread_rwlock_t *__rwlock);
extern int pthread_rwlock_timedrdlock(pthread_rwlock_t *__rwlock,const struct timespec *__abstime);
extern int pthread_rwlock_timedwrlock(pthread_rwlock_t *__rwlock,const struct timespec *__abstime);
extern int pthread_rwlock_tryrdlock(pthread_rwlock_t *__rwlock);
extern int pthread_rwlock_trywrlock(pthread_rwlock_t *__rwlock);
extern int pthread_rwlock_unlock(pthread_rwlock_t *__rwlock);
extern int pthread_rwlock_wrlock(pthread_rwlock_t *__rwlock);
extern int pthread_rwlockattr_destroy(pthread_rwlockattr_t *__attr);
extern int pthread_rwlockattr_getkind_np(const pthread_rwlockattr_t *__attr,int *__pref);
extern int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *__attr,int *__pshared);
extern int pthread_rwlockattr_init(pthread_rwlockattr_t *__attr);
extern int pthread_rwlockattr_setkind_np(pthread_rwlockattr_t *__attr,int __pref);
extern int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *__attr,int __pshared);

//自旋锁
extern int pthread_spin_destroy(pthread_spinlock_t *__lock);
extern int pthread_spin_init(pthread_spinlock_t *__lock,int __pshared);
extern int pthread_spin_lock(pthread_spinlock_t *__lock);
extern int pthread_spin_trylock(pthread_spinlock_t *__lock);
extern int pthread_spin_unlock(pthread_spinlock_t *__lock);

