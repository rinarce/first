// calc_process.c

#include <stdlib.h>
#include <ctype.h>  // для isspace()

#include "calc_process.h"
#include "str_functions.h"

// определяет приоритет операции для указателя, и длину операнда
int get_priority(char* ptr, int *operand_len)
{
  *operand_len = 1;
  switch (*ptr)
  {
    case '+': return 0;
    case '-': return 1;
    case '/': return 2;
    case '*': return 2;
    case '%': return 2;
    case '^': return 3;
  }

  *operand_len = 3;
  if (str_compare_fix_len(ptr, "sin(", 4))    return 4;
  if (str_compare_fix_len(ptr, "cos(", 4))    return 4;
  if (str_compare_fix_len(ptr, "ctg(", 3))    return 4;

  *operand_len = 2;
  if (str_compare_fix_len(ptr, "tg(", 3))     return 4;
  if (str_compare_fix_len(ptr, "pi", 2))      return 4;
  
  // ДОДЕЛАТЬ ПОТОМ ХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХ
  *operand_len = 1;
  return 10;  
}

// приоритет операций
int calc_priority(char c)
{
  switch (c) {
  case '+': 
  case '-': return 1;
  case '*': 
  case '/': return 2;
  case '^': return 3;
  default:              // это не арифметическая операция
  return 100; 
  }
}

// строит дерево вычислений
PNode MakeTree(char Expr[], int first, int last)
{
  int min_priority, i, k, prt;
  int nest = 0; // счетчик открытых скобок
  PNode Tree = (PNode)malloc(sizeof(Node)); // создать в памяти новую вершину
  if (NULL == Tree)
  { // передача ошибки нехватка памяти
    // реализовать потом ХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХ

  }

  if (first == last) { // конечная вершина: число или
    Tree->data = Expr[first]; // переменная
    Tree->left = NULL;
    Tree->right = NULL;
    return Tree;
  }

  min_priority = 100;
  for (i = first; i <= last; i++) {
    if (isspace(Expr[i]))
      continue;

    if (Expr[i] == '(') // открывающая скобка
      { nest++; continue; }
    if (Expr[i] == ')') // закрывающая скобка
      { nest--; continue; }
    if (nest > 0) continue; // пропускаем все, что в скобках


    prt = calc_priority(Expr[i]);
    if (prt <= min_priority) { // ищем последнюю операцию
      min_priority = prt;      // с наименьшим приоритетом
      k = i;
    }
  }

  if (min_priority == 100 && // все выражение взято в скобки
    Expr[first] == '(' && Expr[last] == ')') {
    free(Tree);
    return MakeTree(Expr, first + 1, last - 1);
  }


  Tree->data = Expr[k]; // внутренняя вершина (операция)
  Tree->left = MakeTree(Expr, first, k - 1); // рекурсивно строим
  Tree->right = MakeTree(Expr, k + 1, last); // поддеревья
  return Tree;
}


int CalcTree(PNode Tree)
{
  int num1, num2;
  if (!Tree->left) // если нет потомков,
    return Tree->data - '0'; // вернули число
  num1 = CalcTree(Tree->left); // вычисляем поддеревья
  num2 = CalcTree(Tree->right);
  switch (Tree->data) { // выполняем операцию
  case '+': return num1 + num2;
  case '-': return num1 - num2;
  case '*': return num1 * num2;
  case '/': return num1 / num2;
  }
  return 32767; // неизвестная операция, ошибка!
}

// ------------ Главная функция -------------------------------------------
// вычисляет строку выражений, возвращает тип строки (ок или ошибка) и результат
int process_line(char* str, double* result)
{
  *result = 0;
  unsigned str_len = str_lenght(str);
  if (str_len == 0)
    return CALC_LINE_EMPTY;
  if (is_comment(str))
    return CALC_LINE_COMMENT;
  if (is_only_spaces(str))
    return CALC_LINE_SPACES;
  if (is_bracket_error(str))   // пока проверка скобок только на парность
    return CALC_LINE_ERR_BRACKETS;
  
  // тут обработка
  // return 0;
  char * spaces_removed = str_remove_spaces(str);

  PNode Tree = MakeTree(spaces_removed, 0, str_lenght(spaces_removed) - 1);
  *result = CalcTree(Tree);

  // удалить дерево !!!!!!!!!!!!!!!!!!!!!!!!! !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  free(spaces_removed);
  return 0;
}