#pragma once

// ---------------------------------------------------------------------------

// создаёт локальную переменную var_name, return - код ошибки
int variable_make(char* var_name, double value);

// создаёт глобальную переменную var_name, return - код ошибки
int variable_make_global(char* var_name, double value);

// значение переменной var_name -> *value, return - код ошибки
int variable_get(char* var_name, double* value);

// очистить локальные (для одной строки) переменные, return - код ошибки
int variable_clear_local(void);

// очистить глобальные (для следующих строк) переменные, return - код ошибки
int variable_clear_global(void);
