#ifndef CALC_VARIABLES_H_INCLUDED__
#define CALC_VARIABLES_H_INCLUDED__
#pragma once
#include "common_defs.h"

// --  Интерфейс работы с переменными  ---------------------------------------

// clear global variables
void VariableClearGlobal(void);

// clear local (for current line) variables
void VariableClearLocal(void);

// create local (for current line) variable
calc_err_t VariableMake(char const* varName, double const value);

// create global variable
calc_err_t VariableMakeGlobal(char const* varName, double const value);

// get value by variable name (if exist), return 0 - variable not exist, 1 - exist
int VariableGet(char const* varName, double* value);

#endif CALC_VARIABLES_H_INCLUDED__
