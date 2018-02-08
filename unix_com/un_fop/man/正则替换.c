extern\sint\spthread_mutex(\w+?)(\(.+?\));

#define px_mutex\1\2 \(\{\\\n	int ret=0;\\\n	ret=pthread_mutex\1\2;\\\n	if\(ret\)\{\\\n		show_errno\(ret,"pthread_mutex\1"\);\\\n		exit\(-1\);\\\n	\}\\\n\}\)

