extern\sint\spthread_rwlock(\w+?)(\(.+?\));

#define px_rwlock\1\2 \(\{\\\n	int ret=0;\\\n	ret=pthread_rwlock\1\2;\\\n	if\(ret\)\{\\\n		show_errno\(ret,"pthread_rwlock\1"\);\\\n		exit\(-1\);\\\n	\}\\\n\}\)

