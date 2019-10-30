#pragma once

// ---------------------------------------------------------------------------
// ИНТЕРФЕЙС ДЛЯ ПЕРЕМЕННЫХ
// ---------------------------------------------------------------------------

// создаёт локальную переменную var_name, return - код ошибки
int variable_make(char const* var_name, double const value);

// создаёт глобальную переменную var_name, return - код ошибки
int variable_make_global(char const* var_name, double const value);

// получить значение переменной var_name -> *value, 
// return 0 - не найдено, 1 - есть такая
int variable_get(char const* var_name, double* value);

// очистить локальные (для одной строки) переменные 
void variable_clear_local(void);

// очистить глобальные (для следующих строк) переменные
void variable_clear_global(void);
