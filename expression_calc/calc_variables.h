#pragma once

// ---------------------------------------------------------------------------
// ИНТЕРФЕЙС ДЛЯ ПЕРЕМЕННЫХ
// ---------------------------------------------------------------------------

// создаёт локальную переменную var_name, return - код ошибки
int variable_make(char* var_name, double value);

// создаёт глобальную переменную var_name, return - код ошибки
int variable_make_global(char* var_name, double value);

// получить значение переменной var_name -> *value, 
// return 0 - не найдено, 1 - есть такая
int variable_get(char* var_name, double* value);

// очистить локальные (для одной строки) переменные 
void variable_clear_local(void);

// очистить глобальные (для следующих строк) переменные
void variable_clear_global(void);
