#pragma once

#include <stdio.h>
#include <stdlib.h>             // для выделения памяти

#define DST_BUFFER_SIZE 10     // порции считывания строки (увеличить в релизе!)


// 1 - параметры командной строки ошибочны для данной задачи
// 0 - норм (допустим только 1 доп параметр - имя файла с данными)
int is_command_line_wrong(int arg_count, char* arg_values[]);


// return - 0 == OK    1 == ошибка открытия входного файла
// input_file - если указан файл в коммандной строке, то он откроется на ввод
// иначе input_file = stdin  - файл не указан, или ввод перенаправлен (этим займётся windows)
int detect_input_stream(int arg_count, char* arg_values[], FILE** input_file);


// вводит строку произвольной длины, самостоятельно выделяет память
// в *str возвращает указатель на строку, return = код ошибки
// \n в конце обрезается, но считается в длине (длина == 0 - конец потока ввода)
// при нехватке памяти - пропуск до конца строки, введённое отбросить
int read_input_line(FILE* input_stream, char** str, unsigned int* readed_len);


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

// печатает строку с ошибкой, 2я редакция
void print_error_v2(FILE* output_stream, char* input_line, int error_code);

// печатает строку с ошибкой, возникшей во время ввода строки
void print_input_error(FILE* output_stream);
