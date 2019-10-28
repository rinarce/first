#pragma once

#include <stdio.h>
#include <stdlib.h>             // для выделения памяти

#define DST_BUFFER_SIZE 100     // порции считывания строки (увеличить в релизе!)
//#define DEBUG_IO              // отладка ввода, закомментировать !


// 1 - параметры командной строки ошибочны для данной задачи
// 0 - норм (допустим только 1 доп параметр - имя файла с данными)
int is_command_line_wrong(int arg_count, char* arg_values[]);


// return - 0 == OK    1 == ошибка открытия входного файла
// input_file - если указан файл в коммандной строке, то он откроется на ввод
// иначе input_file = stdin  - файл не указан, или ввод перенаправлен (этим займётся windows)
int detect_input_stream(int arg_count, char* arg_values[], FILE** input_file);


// вводит строку произвольной длины, самостоятельно выделяет память
// в *str возвращает указатель на строку, return = длина строки
// \n в конце обрезается, но считается в длине (длина == 0 - конец потока ввода)
unsigned int read_input_line(FILE* input_stream, char** str);


// печатает строку правильное выражение == результат
void print_expression(FILE* output_stream, char* input_line, double result);


// печатает строку комментарий 
void print_comment(FILE* output_stream, char* input_line);


// печатает строку без значащих символов 
void print_spaces(FILE* output_stream, char* input_line);


// печатает строку пустую (в строке только \n)
void print_empty(FILE* output_stream);


// печатает строку с ошибкой
void print_error(FILE* output_stream, char* input_line, int error_code);
