// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <stdio.h>

// calc_variables.c
// все функции для работы с переменными 
// и структурами данных для их хранения

// СОЗДАТЬ 2 СТРУКТУРЫ ДЛЯ ХРАНЕНИЯ ПЕРЕМЕННЫХ И ВСЕ ФУНКЦИИ

// ---------------------------------------------------------------------------
// создаёт локальную переменную var_name, return - код ошибки
// ПОКА НЕ СОЗДАЁТСЯ РЕАЛЬНО
int variable_make(char* var_name, double value)
{
  printf("[VAR <%s>==%g]\n", var_name, value);
  return 0;
}

// ---------------------------------------------------------------------------
// создаёт глобальную переменную var_name, return - код ошибки
// ПОКА НЕ СОЗДАЁТСЯ РЕАЛЬНО
int variable_make_global(char* var_name, double value)
{
  printf("[GL_VAR <%s>==%g]\n", var_name, value);
  return 0;
}

// ---------------------------------------------------------------------------
// значение переменной var_name -> *value,  - код ошибки
// ПОКА НЕ РЕАЛЬНО    return 0 - не найдено, 1 - есть такая
int variable_get(char* var_name, double *value)
{
  *value = 0;
  return 0;
}

// ---------------------------------------------------------------------------
// очистить локальные (для одной строки) переменные, return - код ошибки
// ПОКА НЕ РЕАЛЬНО
int variable_clear_local(void)
{

  return 0;
}

// ---------------------------------------------------------------------------
// очистить глобальные (для следующих строк) переменные, return - код ошибки
// ПОКА НЕ РЕАЛЬНО
int variable_clear_global(void)
{

  return 0;
}