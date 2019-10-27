// calc_process.c

#include <stdlib.h>
#include <ctype.h>  // для isspace()
#include <math.h>
#include <stdio.h>


#include "calc_process.h"
#include "str_functions.h"


char* prepare_expression(char const* str)
{
  unsigned int new_len = str_count_non_spaces(str);
  char* new_string = (char*)malloc(new_len + 1 + 4);

  if (NULL == new_string)         // выделение памяти не удалось
    return NULL;

  char* new_str_ptr = new_string; // копирование
  char const* old_str_ptr = str;
  //*(new_str_ptr++) = '0';
  //*(new_str_ptr++) = '+';

  while (*old_str_ptr)            // пока не конец строки
    if (!isspace(*old_str_ptr))   // копируем не пробел
      *(new_str_ptr++) = *(old_str_ptr++);
    else
      old_str_ptr++;              // пробел - пропускаем

  //*(new_str_ptr++) = '+';
  //*(new_str_ptr++) = '0';
  *new_str_ptr = '\0';            //  конец строки
  return new_string;
}


void delete_node(PNode Tree)
{
  if (Tree == NULL) return;
  delete_node(Tree->left);
  // free(Tree->left);
  delete_node(Tree->right);
  // free(Tree->right);
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
      *operand_type = CALC_MOD;
      return 3;
    };
    case '^': {
      *operand_type = CALC_POWER;
      return 4;
    };
  }

  if (*ptr == '(')
  { // выражение в скобках - как единый операнд, приоритет самый высокий
    // выделим кусок до следующей скобки
    char* next_close_bracket = str_find_char(ptr, ')', 1);
    *operand_len = next_close_bracket - ptr + 1;
    *operand_type = CALC_BRACKETS;
/*
    char* i = ptr, * j = next_close_bracket;
    printf("(>");
    while (i <= j)
      printf("%c", *i++);
    printf("<%d)", *operand_len);
*/
    return 10;
  }

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
  

  
  if (str_compare_fix_len(ptr, "sqrt(", 5))
  {
    *operand_len = 4;
    *operand_type = CALC_SQRT;
    return 4;
  }


  // ДОДЕЛАТЬ ПОТОМ ХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХ
  *operand_len = 1;
  return 100;  
}


// первые символы строки - это число или переменная
int calc_evaluate(char* str, int symbols, double * result)
{
  // создаём новую строку
  char* new_str = (char*)malloc(symbols + 1);
  if (NULL == new_str)
    return CALC_LINE_ERR_MEMORY;
  
  str_copy_fix_len(str, new_str, symbols);
  new_str[symbols] = '\0';                    // допишем конец строки

  // делаем пока для числа, пока без проверок ошибок ХХХХХХХХХХХХХХХХХХХХХХХХ
  if (symbols == 0)
  {
    *result = 0;
//    printf("[E0]");
    return 0;
  }
//  printf("[E:%s==", new_str);
  int evaluated = sscanf_s(new_str, "%lf", result);
//  printf("%g{%d}]", *result, evaluated);
  free(new_str);
  return (evaluated == 1);
}

// строит дерево вычислений
PNode MakeTree(char Expr[], int first, int last)
{
  int i, priority, error;
  double result = 0;
  
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
    error = calc_evaluate(Expr + first, 1, &result);
    if (error)
    {
    }  // ОШИБКА ____________________________ переделать с контролем
    
    Tree->value = result;           

    Tree->left = NULL;
    Tree->right = NULL;
    return Tree;
  }

  
  min_priority = 100; //Находим операцию с мин приоритетом
  int operand_len = 1;
  int operand_type = 0;

  for (i = first; i <= last; i+=operand_len) 
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

  if (min_priority == 10 && Expr[first] == '(' && Expr[last] == ')') 
    {
      free(Tree);
      return MakeTree(Expr, first + 1, last - 1);
    }
    
  if (min_priority == 100)
    { // число или переменная
      int num_sym = last - first + 1;
      double result;
      
      error = calc_evaluate(Expr + first, num_sym, &result);
      if(error)
        { }  // ОШИБКА ____________________________ переделать с контролем
      
      Tree->value = result;
      Tree->ready = 1;
      Tree->left = NULL;
      Tree->right = NULL;
      return Tree;
    }

  Tree->type = min_priority_type;
  Tree->left = MakeTree(Expr, first, min_priority_ptr - 1);
  Tree->right = MakeTree(Expr, min_priority_ptr + min_priority_oparand_len, last);
  return Tree;
}


// возвращает код ошибки или 0 если всё ОК
int CalcTree(PNode Tree, double * result)
{
  int error = 0;
  double num_left = 0, num_right = 0;
  if (Tree->left == NULL && Tree->right == NULL)  // если нет потомков,
  { 
    *result = Tree->value;      // вернули число
    return 0;
  }

  // вычисляем поддеревья
  if (NULL != Tree->left)
  {
    error = CalcTree(Tree->left, &num_left);
    //delete_node(Tree->left);
    if (error)
      return error;             // если ошибка - дальше не вычислять
  }
  if (NULL != Tree->right)
  {
    error = CalcTree(Tree->right, &num_right);
    //delete_node(Tree->right);
    if (error)
      return error;             // если ошибка - дальше не вычислять
  }
  switch (Tree->type) 
  { // выполняем операцию
    case CALC_PLUS: 
      {
//        printf("[%g+%g] ", num_left, num_right);
        *result = num_left + num_right;
        return 0;
      }
    case CALC_MINUS: 
      {
//      printf("[%g-%g] ", num_left, num_right);
        *result = num_left - num_right;
        return 0;
      }
    case CALC_MUL:
      {
//        printf("[%g*%g] ", num_left, num_right);
        *result = num_left * num_right;
        return 0;
      }
    case CALC_DIV:      
      { 
        if (num_right == 0)                   // Проверим на деление на 0
          return CALC_LINE_ERR_ZERO_DIV;      // Ошибка
//        printf("[%g/%g] ", num_left, num_right);
        *result = num_left / num_right;       // ОК
        return 0;
      }
    case CALC_MOD:
      {
        if (num_right == 0)                   // Проверим на деление на 0
          return CALC_LINE_ERR_ZERO_DIV;      // Ошибка
//        printf("[%g %% %g] ", num_left, num_right);
        *result = fmod(num_left, num_right);  // ОК
        return 0;
      }
    case CALC_POWER:
      {
 //       printf("[%g^%g] ", num_left, num_right);
        *result = pow(num_left, num_right);
        return 0;
      }
    case CALC_PI:
      {
//        printf("[%g<pi>%g] ", num_left, num_right);
        *result = M_PI;
        return 0;
      }
    case CALC_SQRT:
      {
 //       printf("[%g<sqrt>%g] ", num_left, num_right);
        if (num_right < 0)                  // Проверим на отрицательность
          return CALC_LINE_ERR_SQRT_N;      // Ошибка
        *result = sqrt(num_right);          // ОК
        return 0;
      }
  }
  
  // неизвестная операция,  результат - правое число
  *result = num_right;
  return CALC_LINE_ERR_OTHER;               // пока так
}

// ------------ Главная функция -------------------------------------------
// вычисляет строку выражений, возвращает тип строки (ок или ошибка) и результат
int process_line(char* str, double* result)
{
  int error_code = 0;
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

  char * spaces_removed = prepare_expression(str);
  if (NULL == spaces_removed)
    return CALC_LINE_ERR_MEMORY;

  // LowerCase(spaces_removed);

  PNode Tree = MakeTree(spaces_removed, 0, str_lenght(spaces_removed) - 1);
  
  error_code = CalcTree(Tree, result);
    
  delete_node(Tree);        // удалить дерево 
  free(spaces_removed);     // удалить временную строку
  return error_code;
}