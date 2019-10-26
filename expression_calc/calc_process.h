﻿#pragma once

enum calc_line_type
{
  CALC_LINE_OK,           // это корректное выражение
  CALC_LINE_COMMENT,      // это комментарий
  CALC_LINE_EMPTY,        // это совершенно пустая строка
  CALC_LINE_SPACES,       // это строка без значащих символов
  CALC_LINE_LAST,
  CALC_LINE_ERR_MEMORY,   // ошибка - выделения памяти
  CALC_LINE_ERR_ZERO_DIV, // ошибка - деление на 0
  CALC_LINE_ERR_BRACKETS, // ошибка - непарность скобок
  CALC_LINE_ERR_X,        // ошибка - .... пока не придумано
  CALC_LINE_ERR_OTHER,    // ошибка - прочие
  CALC_LINE_ERR_COUNT,    // ошибка - масимальный номер перечисления
};

// вычисляет строку выражений, возвращает тип строки (ок или ошибка) и результат
int process_line(char* input_line, double* result);


typedef enum NodeType
{
  CALC_MINUS,       // -
  CALC_U_MINUS,     // - унарный  
  CALC_PLUS,        // +
  CALC_U_PLUS,      // + унарный
  CALC_DIV,         // /
  CALC_MUL,         // *
  CALC_REST,        // %
  CALC_POWER,       // ^
  CALC_SIN,         // sin()
  CALC_COS,         // cos()
  CALC_TAN,         // tg()
  CALC_COTAN,       // ctg()
  CALC_ASIN,        // arcsin() 
  CALC_ACOS,        // arccos()
  CALC_ATAN,        // arctg()
  CALC_LN,          // ln()
  CALC_FLOUR,       // flour() - округление вниз
  CALC_CEIL,        // ceil()  - округление
  CALC_LOG,         // log(a,x)
  CALC_BRACKETS,    // выражение в скобках
  CALC_PI,          // pi
  CALC_E,           // e
  CALC_VAR,         // переменная
  CALC_GLOBAL_VAR,  // глобальная переменная
  CALC_FUNC,        // функция 
} NodeType;

// узел дерева
typedef struct Node 
{
  double value;
  char data;
  NodeType type;
  struct Node* left, * right;
} Node;

typedef struct Node* PNode; // указатель на узел дерева

