
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#define QUEUE_MAX 8

struct NODE
{
	int len;
	char *data;
};

static struct NODE Queue_LIST[QUEUE_MAX];
static int queue_head = 0;
static int queue_font = 0;
static int queue_cout = 0;

void init_queue() 
{
	printf("queue size %lu\n", sizeof(Queue_LIST));
	memset(Queue_LIST,0x0, sizeof(Queue_LIST));
	queue_head = 0;
	queue_font = 0;
	queue_cout = 0;
}

int queue_isEmpty() 
{
	if (queue_font == queue_head) 
	{
		return 1;
	}
	return 0;
}

int queue_push(char *data, int len) 
{
	int font = 0;
	if (queue_cout == QUEUE_MAX-1) 
	{
		printf("%s\n", "队列满了");
		return 0;
	}
	queue_cout ++;
	queue_font ++;
	font = queue_font % QUEUE_MAX;
	printf("=== %d\n", font);
	Queue_LIST[font].len = len;
	Queue_LIST[font].data = data;
	queue_font = font;
	return 1;
}

struct NODE *queue_put() 
{
	int head = 0;
	struct NODE *t;
	if (queue_isEmpty()) 
	{
		printf("%s\n", "队列是空的");
		return NULL;
	}

	printf("%d\n", Queue_LIST[queue_head].len);
	// Queue_LIST[queue_head].len = 0;
	// Queue_LIST[queue_head].data = NULL;
	t = &Queue_LIST[queue_head];
	// printf("%x\n", &t);
	head = queue_head;
	head ++;
	queue_cout --;
	head = head % 8;
	queue_head = head;
	// TODO: 判断满
	return t;
	// queue_head++;
}
#define H_H "hello"
int main(int argc, char const *argv[])
{
	char ge[] = "hello";
	init_queue();
	queue_push(ge, strlen(H_H));
	// queue_put();
	queue_push(ge, strlen(H_H));
	// queue_put();
	queue_push(ge, strlen(H_H));
	queue_push(ge, strlen(H_H));
	queue_push(ge, strlen(H_H));
	queue_push(ge, strlen(H_H));
	queue_push(ge, strlen(H_H));
	queue_put();
	printf("font %d\n", queue_font);
	printf("head %d\n", queue_head);
	printf("count %d\n", queue_cout);
	// queue_push(ge, strlen(H_H));
	// queue_push(ge, strlen(H_H));
	// queue_push(ge, strlen(H_H));
	queue_push(ge, strlen(H_H));
	queue_push(ge, strlen(H_H));
	queue_put();
	printf("font %d\n", queue_font);
	printf("head %d\n", queue_head);
	printf("count %d\n", queue_cout);
	queue_put();
	printf("font %d\n", queue_font);
	printf("head %d\n", queue_head);
	printf("count %d\n", queue_cout);
	queue_put();
	queue_put();
	queue_put();
	printf("font %d\n", queue_font);
	printf("head %d\n", queue_head);
	printf("count %d\n", queue_cout);
	queue_push(ge, strlen(H_H));
		printf("font %d\n", queue_font);
	printf("head %d\n", queue_head);
	printf("count %d\n", queue_cout);
	return 0;
}