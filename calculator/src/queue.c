#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

queue_t init_queue() {
	queue_t queue; // создаём очередь
	queue.head = NULL;
	queue.tail = NULL;
	return queue;
}
// добавление элемента в конец очереди
void enqueue(queue_t *queue, char *value) {
	data *node = (data*) malloc(sizeof(data));
	node->elem = value;

	node->next = NULL;
	if (queue->tail == NULL) {
		queue->head = node;
	} else {
		queue->tail->next = node;
	}
	queue->tail = node;
}

// удаление элемента из очереди
char* dequeue(queue_t *queue) {
	char *elem = queue->head->elem;

	data *tmp = queue->head;
	queue->head = queue->head->next;
	free(tmp);
	if (queue->head == NULL) {
		queue->tail = NULL;
	}

	return elem;
}

// проверка очереди на пустоту
int is_empty(queue_t queue) {
	return queue.head == NULL;
}

// считывание строки из файла
char* read_string(FILE *input) {
	int size = 0; // размер строки
	int len = 1; // ёмкость строки
	char *s = (char*) malloc(len * sizeof(char));
	for (char c = fgetc(input); !feof(input) && c != '\n'; c = fgetc(input)) {
		s[size++] = c;
		if (size >= len) { // если ёмкости недостаточно
			len *= 2; // увеличиваем её в 2 раза
			s = (char*) realloc(s, len * sizeof(char)); // и перераспределяем память
		}
	}

	s[size] = '\0';

	return s;
}

// проверка на цифру
int is_digit(float c) {
	return (c >= '0' && c <= '9');
}

// ввод числа из строки
int read_int(char *s, int *i) {
	int value = 0;

	while (s[*i] == ' ')
		(*i)++;

	while (s[*i] && is_digit(s[*i]))
		value = value * 10 + s[(*i)++] - '0';

	return value;
}

double read_double(char *s, int *i) {
	while (s[*i] == ' ')
		(*i)++;

	int start = *i;

	while (s[*i] && (is_digit(s[*i]) || s[*i] == '.'))
		(*i)++;

	char prev = s[*i];
	s[*i] = '\0';
	double value = atof(s + start); // переводим строку в число
	s[*i] = prev;

	return value;
}
