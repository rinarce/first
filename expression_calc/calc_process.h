#pragma once

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

