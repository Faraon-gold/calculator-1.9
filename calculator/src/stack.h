#ifndef STACK_H_
#define STACK_H_


typedef struct element {
	float data;
	struct element *next;
} stack;


void push_element(stack **head, float data);
float pop_element(stack **head);

#endif /* STACK_H_ */
