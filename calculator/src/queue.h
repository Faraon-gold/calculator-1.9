#ifndef QUEUE_H_
#define QUEUE_H_
#include <stdio.h>

typedef struct data {
	char *elem;
	struct data *next;
} data;

// структура для очереди
typedef struct queue_t {
	data *head;
	data *tail;
} queue_t;

queue_t init_queue();
void enqueue(queue_t *queue, char *value);
char* dequeue(queue_t *queue);
int is_empty(queue_t queue);
char* read_string(FILE *input);
int is_digit(float c);
int read_int(char *s, int *i);
double read_double(char *s, int *i);

#endif /* QUEUE_H_ */
