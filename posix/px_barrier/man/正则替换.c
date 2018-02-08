extern\sint\spthread_(\w+?)(\(.+?\));

#define px_thread_\1\2 \(\{\\\n	int ret=0;\\\n	ret=pthread_\1\2;\\\n	if\(ret\)\{\\\n		show_errno\(ret,"pthread_\1"\);\\\n		exit\(-1\);\\\n	\}\\\n\}\)

