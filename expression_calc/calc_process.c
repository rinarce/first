// calc_process.c

#include <stdlib.h>
#include <ctype.h>  // для isspace()
#include <math.h>

#include "calc_process.h"
#include "str_functions.h"

void delete_node(PNode Tree)
{
  if (Tree == NULL) return;
  delete_node(Tree->left);
  delete_node(Tree->right);
  free(Tree);
}

// определяет приоритет операции для указателя, длину операнда
// и тип операции (многовато)
int get_priority(char* ptr, int *operand_len, int *operand_type)
{
  *operand_len = 1;
  switch (*ptr)
  {
    case '+': { 
      *operand_type = CALC_PLUS; 
      return 1; 
    }
    case '-': {
      *operand_type = CALC_MINUS;
      return 2;
    };
    case '/': {
      *operand_type = CALC_DIV;
      return 3;
    };
    case '*': {
      *operand_type = CALC_MUL;
      return 3;
    };
    case '%': {
      *operand_type = CALC_REST;
      return 3;
    };
    case '^': {
      *operand_type = CALC_POWER;
      return 4;
    };
  }
  //* Что-то не работает как надо
  *operand_len = 3;
  if (str_compare_fix_len(ptr, "sin(", 4))
  {
    *operand_type = CALC_SIN;
    return 4;
  }

  if (str_compare_fix_len(ptr, "cos(", 4))
  {
    *operand_type = CALC_COS;
    return 4;
  }
  if (str_compare_fix_len(ptr, "ctg(", 3))
  {
    *operand_type = CALC_COTAN;
    return 4;
  }
  
  *operand_len = 2;
  if (str_compare_fix_len(ptr, "tg(", 3))
  {
    *operand_type = CALC_TAN;
    return 4;
  };
  if (str_compare_fix_len(ptr, "pi", 2))
  {
    *operand_type = CALC_PI;
    return 4;
  };
  

  // ДОДЕЛАТЬ ПОТОМ ХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХ
  *operand_len = 1;
  return 100;  
}


// строит дерево вычислений
PNode MakeTree(char Expr[], int first, int last)
{
  int i, priority;
  
  int min_priority = 100;            // минимальный приоритет операции
  int min_priority_ptr;             // указатель на эту операцию
  int min_priority_oparand_len = 1; // длина записи операции символов
  int min_priority_type;            // минимальный приоритет - тип операции

  PNode Tree = (PNode)malloc(sizeof(Node)); // создать в памяти новую вершину
  if (NULL == Tree)
  { // передача ошибки нехватка памяти
    // реализовать потом ХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХ
    return 0;
  }

  if (first == last) // конечная вершина: число или
  {
    Tree->data[0] = Expr[first];           // переменная
    Tree->data[1] = '\0';
    Tree->left = NULL;
    Tree->right = NULL;
    return Tree;
  }


  min_priority = 100; //Находим операцию с мин приоритетом
  int operand_len = 1;
  int operand_type = 0;
  for (i = first; i <= last; i++) 
  {
    priority = get_priority(Expr+i, &operand_len, &operand_type);
    if (priority <= min_priority)
    {
      min_priority = priority;
      min_priority_ptr = i;
      min_priority_oparand_len = operand_len;
      min_priority_type = operand_type;
    }
  }

  if (min_priority == 100)
    if (Expr[first] == '(' && Expr[last] == ')') 
    {
      delete_node(Tree);
      return MakeTree(Expr, first + 1, last - 1);
    }
    
    else 
    { // число или переменная
      int num_sym = last - first + 1;

      str_copy_fix_len(Expr + first, Tree->data, num_sym);
      Tree->data[num_sym] = '\0';

      Tree->left = NULL;
      Tree->right = NULL;
      return Tree;
    }

  Tree->type = min_priority_type;
  Tree->left = MakeTree(Expr, first, min_priority_ptr - 1);
  Tree->right = MakeTree(Expr, min_priority_ptr + min_priority_oparand_len, last);
  return Tree;
}


double CalcTree(PNode Tree)
{
  double num1, num2;
  if (!Tree->left)                    // если нет потомков,
    return (double)atof(Tree->data);  // вернули число

  num1 = CalcTree(Tree->left);        // вычисляем поддеревья
  num2 = CalcTree(Tree->right);
  switch (Tree->type) 
  { // выполняем операцию
    case CALC_PLUS:     return num1 + num2;
    case CALC_MINUS:    return num1 - num2;
    case CALC_MUL:      return num1 * num2;
    case CALC_DIV:      return num1 / num2;
    case CALC_POWER:    return pow(num1, num2);
    case CALC_PI:       return M_PI;
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
  LowerCase(spaces_removed);

  PNode Tree = MakeTree(spaces_removed, 0, str_lenght(spaces_removed) - 1);
  *result = CalcTree(Tree);

  // удалить дерево !!!!!!!!!!!!!!!!!!!!!!!!! !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  free(spaces_removed);
  return 0;
}