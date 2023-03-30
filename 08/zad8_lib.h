#ifndef _ZAD6_LIB_
#define _ZAD6_LIB_

#define SERVER_NAME "/server"
#include <mqueue.h>

extern mqd_t qd;
mqd_t mqcreate(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
mqd_t mqopen(const char *name, int oflag);
int mqsend(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);
int mqreceive(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);
int mqclose(mqd_t mqdes);
int mqdelete(const char *name);

#endif
