#include "calc_process.h"
#include <stdlib.h>
#include <ctype.h>  // для isspace()


// 1 - если в строке только всевозможные пробелы ( \t\n\v\f\r)
int is_only_spaces(char* str)
{
  while (*str)
    if (!isspace((int)(*str++)))
      return 0;
  return 1;
}

// 1 - если в строке первые значащие символы //
int is_comment(char* str)
{
  while (*str)
    if (!isspace((int)(*str)))   // пропустить все незначащие символы
      break;
    else str++;

  // проверяем что оба символа - это не конец строки и равны '//'
  if (*str && *str == '/' && *(str + 1) && *(str + 1) == '/')
    return 1;
  else return 0;
}

// 1 - если в строке нарушена парность скобок (()
int is_bracket_error(char* str)
{
  int nest = 0;                       // счётчик открытых скобок
  while (*str)
  {
    if (*str == '(')        nest++;   // открывающая скобка
    else if (*str == ')')   nest--;   // закрывающая скобка
    
    if (nest < 0)  return 1;          // закрывающая раньше открывающей
      
    str++;
  }
  return nest;            // если >0 - остались незакрытые скобки
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
  int MinPrt, i, k, prt;
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
  MinPrt = 100;
  for (i = first; i <= last; i++) {
    if (isspace(Expr[i]))
      continue;
    if (Expr[i] == '(') // открывающая скобка
      { nest++; continue; }
    if (Expr[i] == ')') // закрывающая скобка
      { nest--; continue; }
    if (nest > 0) continue; // пропускаем все, что в скобках


    prt = calc_priority(Expr[i]);
    if (prt <= MinPrt) { // ищем последнюю операцию
      MinPrt = prt; // с наименьшим приоритетом
      k = i;
    }
  }

  if (MinPrt == 100 && // все выражение взято в скобки
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


// вычисляет строку выражений, возвращает тип строки (ок или ошибка) и результат
int process_line(char* str, double* result)
{
  *result = 0;
  unsigned str_len = STR_Lenght(str);
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
  PNode Tree = MakeTree(str, 0, str_len - 1);
  *result = CalcTree(Tree);
  // удалить дерево !!!!!!!!!!!!!!!!!!!!!!!!!

  return 0;
}