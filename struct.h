#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct thread_args {
	int mini_batch;
	int k;
    int thread;
	int mini_batch_size;
	int len;
	float** dw;
	float** db;
	char** name;
} thread_args;

#endif
