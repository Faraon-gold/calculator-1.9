/*
 * Использование очереди для выполнения группы заданий
 * Пример выходных данных:
 * + c 5 6
 * - v 3 9 8 7 1 2 3
 *
 */

#include <stdio.h>
#include <stdlib.h>

// структура для элемента очереди
typedef struct data {
	char *elem;
	struct data *next;
} data;

// структура для очереди
typedef struct queue_t {
	data *head;
	data *tail;
} queue_t;

// инициализация пустой очереди
queue_t init_queue() {
	queue_t queue; // создаём очередь
	queue.head = NULL;
	queue.tail = NULL;
	return queue;
}

void enqueue(queue_t *queue, char *value);
char* dequeue(queue_t *queue);
int is_empty(queue_t queue);
char* read_string(FILE *f1);
int is_digit(float c);
int read_int(char *s, int *i);
double read_double(char *s, int *i);
double factorial(int f);

void numbers(FILE *output, char *s, char sign);
void vectors(FILE *output, char *s, char sign);
void calc(FILE *input, char *s);

int main() {
	char n = 'y';
	char in[20], out[20];
	FILE *input, *output;
	while (n == 'y') {
		printf("Enter name to input file: ");
		scanf("%s", in);
		input = fopen(in, "r");
		queue_t queue = init_queue(); // создаём пустую очередь

		while (!feof(input))
			enqueue(&queue, read_string(input)); // добавляем в очередь строки

		fclose(input);

		printf("Enter name to output file: ");
		scanf("%s", out);

		output = fopen(out, "w");

		while (!is_empty(queue)) { // пока не кончится очередь
			calc(output, dequeue(&queue)); // вычисляем выражение
		}
		fclose(output);
		printf("do you want to continue? (y/n)");
		scanf("%s", &n);
	}
	return 0;
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
	double value = atof(s + start);
	s[*i] = prev;

	return value;
}

double factorial(int f) {
	double fact = 1;

	for (int i = 2; i <= f; i++)
		fact *= i;

	return fact;
}

void numbers(FILE *output, char *s, char sign) {
	int index = 3;

	if (sign == '!') {
		int x = read_int(s, &index);
		fprintf(output, "%.0lf\n", factorial(x));
		return;
	}

	double x = read_double(s, &index);
	double y = read_double(s, &index);

	if (sign == '+') {
		fprintf(output, "%.2lf\n", x + y);
	} else if (sign == '-') {
		fprintf(output, "%.2lf\n", x - y);
	} else if (sign == '*') {
		fprintf(output, "%.2lf\n", x * y);
	} else if (sign == '/') {
		if (y == 0)
			fprintf(output, "division by zero\n");
		else
			fprintf(output, "%.2lf\n", (double) x / y);
	} else if (sign == '^') {

		float S = 1;
		for (int i = 1; i <= y; i++) {
			S *= x;
		}
		fprintf(output, "%.2lf\n", S);
	}

	else {
		fprintf(output, "unknown operation '%c'\n", sign);
	}
}

void vectors(FILE *output, char *s, char sign) {
	int index = 3;
	int n = read_int(s, &index);

	double *v1 = (double*) malloc(n * sizeof(double));
	double *v2 = (double*) malloc(n * sizeof(double));

	// считываем вектора
	for (int i = 0; i < n; i++)
		v1[i] = read_double(s, &index);

	for (int i = 0; i < n; i++)
		v2[i] = read_double(s, &index);

	if (sign == '*') {
		double res = 0;

		for (int i = 0; i < n; i++)
			res += v1[i] * v2[i];

		fprintf(output, "%.2lf\n", res);
	} else if (sign == '+' || sign == '-') {
		if (sign == '+') {
			for (int i = 0; i < n; i++)
				fprintf(output, "%.2lf ", v1[i] + v2[i]);
			fprintf(output, "\n");
		} else {
			for (int i = 0; i < n; i++)
				fprintf(output, "%.2lf ", v1[i] - v2[i]);
			fprintf(output, "\n");
		}

	} else {
		fprintf(output, "unknown operation '%c'\n", sign);
	}

	free(v1);
	free(v2);
}

// вычисление значения выражения
void calc(FILE *input, char *s) {
	char sign = s[0];
	char op = s[2];

	if (op == 'c') {
		numbers(input, s, sign);
	} else if (op == 'v') {
		vectors(input, s, sign);
	}
}
© 2021 GitHub, Inc.
