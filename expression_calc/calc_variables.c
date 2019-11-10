// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

// calc_variables.c все функции для работы с переменными и структурами данных для их хранения

#include <stdio.h>
#include <stdlib.h> 

#include "calc_variables.h"
#include "common_defs.h"    // общие определения
#include "str_functions.h"  // для строк


// ---------------------------------------------------------------------------
// ВНУТРЕННЯЯ РЕАЛИЗАЦИЯ - 3 связных списка

typedef struct list_node_t {
  double value;             // значение
  char* varName;            // имя переменной
  struct list_node_t* next; // указатель на следующий узел (NULL у последнего)
} list_node_t;

// ---------------------------------------------------------------------------
// Предопределённые глобальные переменные 
list_node_t s_pi = { M_PI, "pi", NULL  };         // будет последней
list_node_t  s_e = { M_E,  "e",  &s_pi };         // будет перед s_pi
// ..... - добавлять сюда, связывая друг с другом
// ---------------------------------------------------------------------------

typedef struct list_node_t* p_list_node_t;        // указатель на узел списка

// Первые узлы для связных списков, эти узлы статические, постоянные
// В них ничего не храню, только сслылка на следующий узел
list_node_t     s_headLocal = { 0, NULL, NULL };  // для локальных переменных
list_node_t    s_headGlobal = { 0, NULL, NULL };  // для глобальных переменных
list_node_t   s_headDefined = { 0, NULL, &s_e };  // для предопределённых

p_list_node_t   s_varsLocal = &s_headLocal;       // работаем через указатели
p_list_node_t  s_varsGlobal = &s_headGlobal;        
p_list_node_t s_varsDefined = &s_headDefined;

// удалить узел списка и все узлы за ним
static void _listDeleteTail (p_list_node_t node) { 
  p_list_node_t next;           // Избавимся от рекурсии
  while (NULL != node) {
    next = node->next;          // запомнить, ведь node удалится
    free(node->varName);        // удалить свою строку
    free(node);                 // удалиться самому
    node = next;                // перейти к следующему
  }
}

// указанный узел связного списка очистить, следующие - удалить
static void _listClear(p_list_node_t list) {
  _listDeleteTail(list->next);  // удалить все после указанного узла
  free(list->varName);          // 
  list->value   = 0;            // себя обнулить, не удалять
  list->next    = NULL;  
  list->varName = NULL;
}

// Добавить переменную к списку, для имени создаётся новая строка в памяти
static calc_err_t _listAdd(p_list_node_t list, char const* varName, double const value) { 
  if (NULL == list) 
    return CALC_ERR_ALGO;   //вызвано для несуществующего списка
  
// для упрощения 
// 1 - не проверять наличие (возможно переопределение переменных), добавлять в начало списка
//     тогда ранние определения будут дальше и при поиске не найдутся
// 2 - имя не проверяется, считаем что ПРАВИЛ ДЛЯ ИМЁН переменных НЕТ
//     тогда возможно переопределение числовых констант, и прочее
//     например 2=3 3=2 [####]=4 pi=3 и т.п.

  int nameLen = StrLenght(varName);        
  if (nameLen == 0) 
    return CALC_ERR_VARZ;    // попытка создать переменную без имени

  char* newStr = (char*)malloc(nameLen + 1); // создать новую строку для имени
  if (NULL == newStr)  
    return CALC_ERR_MEMORY;

  p_list_node_t nextNode = (p_list_node_t)malloc(sizeof(list_node_t));
  if (NULL == nextNode) {
    free(newStr);           // не удалось создать узел => строка уже тоже не нужна
    return CALC_ERR_MEMORY;
  }

  StrCopyFixLen(varName, newStr, nameLen);    // скопировать имя в созданную строку
  newStr[nameLen]   = '\0';                   // конец строки

  nextNode->varName = newStr;      
  nextNode->value   = value;      
  nextNode->next    = list->next;             // присоединить хвост списка 
  list->next        = nextNode;               // новый узел будет за головой
  return CALC_OK;
}


// ищет в списке переменную, если нашло - то изменяет *value
// return 1 - пременная найдена, 0 - нет
static int _listGet(p_list_node_t list, char const* varName, double* value) {
  while (NULL != list) {
    if (StrCompare(list->varName, varName)) {
      *value = list->value;
      return 1;               // нашли
    }
    list = list->next;        // перейти к следующему
  }
  return 0;                   // не нашли
}


// --  ИНТЕРФЕЙС  ------------------------------------------------------------

// создаёт локальную переменную varName
calc_err_t VariableMake(char const* varName, double const value) {  
  return _listAdd(s_varsLocal, varName, value);  
}

// создаёт глобальную переменную varName
calc_err_t VariableMakeGlobal(char const* varName, double const value){
  return _listAdd(s_varsGlobal, varName, value); 
}

// значение переменной varName -> *value, return 0 - не найдено, 1 - есть такая
int VariableGet(char const* varName, double *value) {
  int nameLen = StrLenght(varName);
  if (nameLen == 0) 
    return 0;   //  не передано имя переменной (такой запрос не ошибка)
                
  if (_listGet(s_varsLocal, varName, value))      // сначала ищем в локальных
    return 1;
  if (_listGet(s_varsDefined, varName, value))    // потом в предопределённых
    return 1;
  return _listGet(s_varsGlobal, varName, value);  // а потом в глобальных
}

// очистить локальные (для одной строки) переменные 
void VariableClearLocal(void) {
  _listClear(s_varsLocal);   
}

// очистить глобальные (для следующих строк) переменные
void VariableClearGlobal(void) {
  _listClear(s_varsGlobal);  
}
