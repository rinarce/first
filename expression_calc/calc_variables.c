// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

// calc_variables.c
// все функции для работы с переменными 
// и структурами данных для их хранения

#include <stdio.h>
#include <stdlib.h>         // memory

#include "calc_process.h"   // код ошибки
#include "str_functions.h"  // для строк


// ---------------------------------------------------------------------------
// ВНУТРЕННЯЯ РЕАЛИЗАЦИЯ - 2 связных списка для локальных и глобальных переменных
// ---------------------------------------------------------------------------

// Связный список
typedef struct List_Node  // узел списка
{
  double value;           // значение
  char* var_name;         // имя переменной
  struct List_Node* next; // указатель на следующий узел (NULL у последнего)
} List_Node;

typedef struct List_Node* P_List_Node;    // указатель на узел списка

// Первые узлы для связных списков, эти узлы статические, постоянные
// В них ничего не храню
List_Node   head_local  = { 0, NULL, NULL };  // для локальных переменных
List_Node   head_global = { 0, NULL, NULL };  // для глобальных переменных
P_List_Node vars_local  = &head_local;        // работаем через указатели
P_List_Node vars_global = &head_global;       // работаем через указатели


// удалить узел списка и все узлы за ним
void list_delete_tail(P_List_Node node)
{ 
  P_List_Node next;
  while (NULL != node)          // Избавимся от рекурсии
  {
    next = node->next;          // запомнить, ведь node удалится
    free(node->var_name);       // удалить свою строку
    free(node);                 // удалиться самому
    node = next;                // перейти к следующему
  }
}

// очистить связный список - указанный узел очистить, следующие - удалить
void list_clear(P_List_Node list)
{
  list_delete_tail(list->next);  // удалить все после указанного узла
  free(list->var_name);          // возможно вызов не из головы списка
  list->value = 0;               // себя обнулить, не удалять
  list->next = NULL;  
  list->var_name = NULL;
}

// Добавить переменную к списку, для имени создаётся новая строка в памяти
// return - код ошибки 
int list_add(P_List_Node list, char* var_name, double value)
{ 
  if (NULL == list) return CALC_ERR_ALGO;  //вызвано для несуществующего списка
  
// для упрощения 
// 1 - не проверять наличие (переопределение), добавлять в начало списка
//     тогда ранние определения будут дальше и при поиске не найдутся
// 2 - имя не проверяется, считаем что ПРАВИЛ ДЛЯ ИМЁН переменных НЕТ
//     тогда возможно переопределение числовых констант, и прочее
//     например 2=3 [###]=8 pi=3 

  int name_len = str_lenght(var_name);        
  if (name_len == 0) return CALC_ERR_VARZ;    // попытка создать переменную без имени

  char* new_str = (char*)malloc(name_len + 1);// создать новую строку для имени
  if (NULL == new_str)  return CALC_ERR_MEMORY;

  P_List_Node next_node = (P_List_Node)malloc(sizeof(List_Node));
  if (NULL == next_node)
  {
    free(new_str);  // не удалось создать узел => строка уже тоже не нужна
    return CALC_ERR_MEMORY;
  }

  str_copy_fix_len(var_name, new_str, name_len);    // скопировать имя в созданную строку
  new_str[name_len] = '\0';                         // конец строки

  next_node->var_name = new_str;      // имя переменной 
  next_node->value    = value;        // значение
  next_node->next     = list->next;   // присоединить хвост списка 

  list->next = next_node;             // новый узел будет за головой
  return 0;                           // дошли до сюда - ошибок нет
}


// ищет в списке переменную, если нашло - то изменяет *value
// return 1 - пременная найдена, 0 - нет
int list_get(P_List_Node list, char* var_name, double* value)
{
  while (NULL != list) 
  {
    if (str_compare(list->var_name, var_name)) {
      *value = list->value;
      return 1;               // нашли
    }
    list = list->next;        // перейти к следующему
  }
  return 0;                   // не нашли
}


// ---------------------------------------------------------------------------
// ИНТЕРФЕЙС 
// ---------------------------------------------------------------------------
// создаёт локальную переменную var_name, return - код ошибки
int variable_make(char* var_name, double value) {
  return list_add(vars_local, var_name, value);
}

// создаёт глобальную переменную var_name, return - код ошибки
int variable_make_global(char* var_name, double value) {
  return list_add(vars_global, var_name, value);
}

// значение переменной var_name -> *value,
// return 0 - не найдено, 1 - есть такая
int variable_get(char* var_name, double *value)
{
  int name_len = str_lenght(var_name);
  if (name_len == 0) return 0;    //  не передано имя переменной
  
                // сначала ищем в локальных
  if(list_get(vars_local, var_name, value)) return 1;
                // потом в глобальных
  return list_get(vars_global, var_name, value);
}

// очистить локальные (для одной строки) переменные 
void variable_clear_local(void) {
  list_clear(vars_local);    // удалить все после первого узла
}

// очистить глобальные (для следующих строк) переменные
void variable_clear_global(void) {
   list_clear(vars_global);  // удалить все после первого узла
}