#include "zad8_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <mqueue.h>


mqd_t qd;
// TWORZENIE
mqd_t mqcreate(const char *name, int oflag, mode_t mode, struct mq_attr *attr)
{
	qd = mq_open(name, oflag, mode, attr);
	if(qd == -1)
	{
		perror("mqcreate error");
		return qd;
	}
	else return qd;
}
// OTWIERANIE
mqd_t mqopen(const char *name, int oflag)
{
	qd = mq_open(name, oflag);
	if(qd == -1)
	{
		perror("mqopen error");
		return qd;
	}
	else return qd;
}
// WYSYLANIE
int mqsend(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio)
{
	if(mq_send(mqdes, msg_ptr, msg_len, msg_prio) == -1)
	{
		perror("mqsend error");
		return -1;
	}
	else return 0;
}
// ODBIERANIE
int mqreceive(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio)
{
	if(mq_receive(mqdes, msg_ptr, msg_len, msg_prio) == -1)
	{
		perror("mqreceive error");
		return -1;
	}
	else return 0;
}

// ZAMYKANIE
int mqclose(mqd_t mqdes)
{
	if(mq_close(mqdes) == -1)
	{
		perror("mqclose error");
		return -1;
	}
	else return 0;
}
// USUWANIE
int mqdelete(const char *name)
{
	if(mq_unlink(name) == -1)
	{
		perror("mqdelete error");
		return -1;
	}
	else return 0;
}
