extern\sint\spthread_cond(\w+?)(\(.+?\));

#define px_cond\1\2 \(\{\\\n	int ret=0;\\\n	ret=pthread_cond\1\2;\\\n	if\(ret\)\{\\\n		show_errno\(ret,"pthread_cond\1"\);\\\n		exit\(-1\);\\\n	\}\\\n\}\)

