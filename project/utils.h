#ifndef UTILS_H_
#define UTILS_H_

void show_rules(int);
void tab(int);
void print_header();
void show_shot_res(float*, float*, int, float*);
void print_result(int, float);

long VAL(char *string);
void input_string(char **p_target);
void input_number(int *p_target);

#endif