#ifndef UN_SIGNAL_H_
#define UN_SIGNAL_H_ 1

int un_sigaction(int signum, const struct sigaction *p_act);
int un_sigqueue(char *name, int sig, const union sigval value);
int un_setitimer(int which, const struct itimerval *p_value);

#endif