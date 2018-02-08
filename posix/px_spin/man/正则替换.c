extern\sint\spthread_spin(\w+?)(\(.+?\));

#define px_spin\1\2 \(\{\\\n	int ret=0;\\\n	ret=pthread_spin\1\2;\\\n	if\(ret\)\{\\\n		show_errno\(ret,"pthread_spin\1"\);\\\n		exit\(-1\);\\\n	\}\\\n\}\)

