// calc_process.c

#include <stdlib.h>
#include <ctype.h>  // для isspace()
#include <math.h>
#include <stdio.h>


#include "calc_process.h"
#include "str_functions.h"

// Логика приоритетов операций
#define PRIORYTY_BIT_XOR     6      // xor
#define PRIORYTY_BIT_OR      7      // |
#define PRIORYTY_BIT_AND     8      // &
#define PRIORYTY_BIT_NOT    10      // ~

#define PRIORYTY_PLUS       12      // +
#define PRIORYTY_MINUS      12      // -

#define PRIORYTY_MUL_DIV    15      // * / % 
#define PRIORYTY_POWER      18      // ^ 

#define PRIORYTY_FUNCS      20      // функции
#define PRIORYTY_CONST      20      // константы

#define PRIORYTY_BRACKETS   30      // (...)

#define MAX_PRIORITY       100      // фиктивное большое число приоритета

// ТУТ вся предварительная подготовка строки, возвращает новую строку
// - удаление пробелов
// - разборка со сдвоенными -- ++ -+ +-
char* prepare_expression(char const* str)
{
  int made_changes = 1;
  char* spaces_removed = str_remove_spaces(str);      // удалить пробелы
  if (NULL == spaces_removed)
    return NULL;

  while (made_changes)                // заменить множественные --- и +++
  {
    made_changes  = str_replace_all(spaces_removed, "--", "+");
    made_changes += str_replace_all(spaces_removed, "++", "+");
    made_changes += str_replace_all(spaces_removed, "+-", "-");
    made_changes += str_replace_all(spaces_removed, "-+", "-");

    char* new_str = str_remove_spaces(spaces_removed); // удалить пробелы
    if (NULL == new_str)
      return NULL;

    str_copy_str(new_str, spaces_removed);
    free(new_str);
  }

  // LowerCase(spaces_removed);
  return spaces_removed;
}

// проверить на корректность скобок
int is_bracket_err_in_str(const char* str, int start, int end)
{
  int nest = 0;                       // счётчик открытых скобок
  while (start <= end)
  {
    if (*str == '(')        nest++;   // открывающая скобка
    else if (*str == ')')   nest--;   // закрывающая скобка

    if (nest < 0)
      return 1;                       // закрывающая раньше открывающей
    str++;
    start++;
  }
  return nest;            // если >0 - остались незакрытые скобки
}

// удаляет узел дерева и все его дочерние узлы
void delete_node(PNode Tree)
{
  if (Tree == NULL) return;
  delete_node(Tree->left);
  delete_node(Tree->right);
  free(Tree);
}

// определяет приоритет операции для указателя ptr, длину операнда
// и тип операции (многовато)
int get_priority(char* ptr, int *operand_len, int *operand_type)
{
  *operand_len = 1;
  switch (*ptr)
  {
  case '+': {   *operand_type = CALC_PLUS;
                return PRIORYTY_PLUS;             }
  case '-': {   *operand_type = CALC_MINUS;
                return PRIORYTY_MINUS;            }
  case '/': {   *operand_type = CALC_DIV;
                return PRIORYTY_MUL_DIV;          }
  case '*': {   *operand_type = CALC_MUL;
                return PRIORYTY_MUL_DIV;          }
  case '%': {   *operand_type = CALC_MOD;
                return PRIORYTY_MUL_DIV;          }
  case '^': {   *operand_type = CALC_POWER;
                return PRIORYTY_POWER;            }
  case '&': {   *operand_type = CALC_AND_BIT;
                return PRIORYTY_BIT_AND;          }
  case '~': {   *operand_type = CALC_NOT_BIT;
                return PRIORYTY_BIT_NOT;          }
  case '|': {   *operand_type = CALC_OR_BIT;
                return PRIORYTY_BIT_OR;           }
  }

  if (*ptr == '(')
  { // выражение в скобках - как единый операнд, приоритет самый высокий
    // выделим кусок до следующей скобки парной этой
    int nest = 0;                            // счётчик открытых скобок
    char* find_brac = ptr;
    do 
    { if (*find_brac == '(')        nest++;  // открывающая скобка
      else if (*find_brac == ')')   nest--;  // закрывающая скобка
      find_brac++;
    } while (nest != 0);

    *operand_len = find_brac - ptr;
    *operand_type = CALC_BRACKETS;
 /*
    // отладочная печать - удалить
    char* i = ptr, * j = find_brac-1;
    printf("(->");
    while (i <= j) printf("%c", *i++);
    printf("<-)\n");
*/
    return PRIORYTY_BRACKETS;
  }

  *operand_len = 3;
  if (str_compare_fix_len(ptr, "xor", 3))
  { *operand_type = CALC_XOR_BIT;
    return PRIORYTY_BIT_XOR;
  }
  
  if (str_compare_fix_len(ptr, "sin(", 4))
  { *operand_type = CALC_SIN;
    return PRIORYTY_FUNCS;
  }

  if (str_compare_fix_len(ptr, "cos(", 4))
  { *operand_type = CALC_COS;
    return PRIORYTY_FUNCS;
  }
  
  if (str_compare_fix_len(ptr, "ctg(", 3))
  { *operand_type = CALC_COTAN;
    return PRIORYTY_FUNCS;
  }
  
  if (str_compare_fix_len(ptr, "abs(", 3))
  { *operand_type = CALC_ABS;
    return PRIORYTY_FUNCS;
  }


  *operand_len = 2;
  if (str_compare_fix_len(ptr, "tg(", 3))
  { *operand_type = CALC_TAN;
    return PRIORYTY_FUNCS;
  }
  
  if (str_compare_fix_len(ptr, "pi", 2))
  { *operand_type = CALC_PI;
    return PRIORYTY_CONST;
  }
  

  if (str_compare_fix_len(ptr, "sqrt(", 5))
  { *operand_len = 4;
    *operand_type = CALC_SQRT;
    return PRIORYTY_FUNCS;
  }
  if (str_compare_fix_len(ptr, "sign(", 5))
  { *operand_len = 4;
    *operand_type = CALC_SIGN;
    return PRIORYTY_FUNCS;
  }


  // ДОДЕЛАТЬ ПОТОМ все операции ХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХ
  
  
  *operand_len = 1; //операция не найдена
  return MAX_PRIORITY;
}


// первые символы строки - это число или переменная (НЕ РЕАЛИЗОВАНО)
// Шестнадцатеричные переводит, двоичные - ДА, возврат - код ошибки (0 - ОК)
int calc_evaluate(char* str, int symbols, double * result)
{
  // такое бывает на строках (2)(3) обрезанных до 2)(3
  if (symbols < 0) return CALC_LINE_ERR_ALGO; // ASSERT

  if (symbols == 0)
  { // пустое считаем за 0 - прощаем некоторые спорные случаи 3+ или ()
    *result = 0;
    //    printf("[Empty]");
    return 0;
  }

  // создаём новую строку
  char* new_str = (char*)malloc(symbols + 1);
  if (NULL == new_str)
    return CALC_LINE_ERR_MEMORY;
  
  str_copy_fix_len(str, new_str, symbols);
  new_str[symbols] = '\0';                    // допишем конец строки

// делаем пока для числа, пока без проверок ошибок ХХХХХХХХХХХХХХХХХХХХХХХХ

  if (is_binary_digit(new_str, result))  // пробуем на двоичность
  {
    free(new_str);
  }
  else  // ТУТ все остальные варианты, 0x... работает
  { 
    //  printf("[E:%s==", new_str);
    int evaluated = sscanf_s(new_str, "%lf", result);
    //  printf("%g{%d}]", *result, evaluated);
    free(new_str);
    if (evaluated != 1) //должно быть получено ровно 1 число, иначе ошибка
      return CALC_LINE_ERR_EVAL;
  }
  return 0;
}

// строит дерево вычислений, возврат - код ошибки (0 - ОК)
int MakeTree(char Expr[], int first, int last, PNode * result_tree)
{
  int i, priority, error;
  double result = 0;
  
  int min_priority = MAX_PRIORITY;  // минимальный приоритет операции
  int min_priority_ptr;             // указатель на эту операцию
  int min_priority_oparand_len = 1; // длина записи операции символов
  int min_priority_type;            // минимальный приоритет - тип операции

  PNode Tree = (PNode)malloc(sizeof(Node)); // создать в памяти новую вершину
  if (NULL == Tree) 
    return CALC_LINE_ERR_MEMORY;
  
  Tree->left = NULL;
  Tree->right = NULL;
  Tree->value = 0;
  *result_tree = Tree;

  if (first == last) // конечная вершина 1 символ: число или переменная
  {
    error = calc_evaluate(Expr + first, 1, &result);
    if (error)  return error;

    Tree->value = result;           
    return 0;
  }

  
  min_priority = MAX_PRIORITY;  //Находим операцию с мин приоритетом
  int operand_len = 1;
  int operand_type = 0;

  for (i = first; i <= last; i+=operand_len) 
  {
    priority = get_priority(Expr+i, &operand_len, &operand_type);
    // для выполнения операций слева-направо тут должно быть <=
    // тогда операция правее выберется раньше, а выполнится позже (при равных приоритетах)
    // операция правее перебьёт минимум приоритета такой же слева от неё
    if (priority <= min_priority) 
    {
      min_priority = priority;
      min_priority_ptr = i;
      min_priority_oparand_len = operand_len;
      min_priority_type = operand_type;
    }
  }

  if (min_priority == PRIORYTY_BRACKETS && Expr[first] == '(' && Expr[last] == ')')
    { // всё выражение в скобках, избавимся от них в новом вызове
      // в ситуации "(2)(3)(5)" => станет => "2)(3)(5"   непонятно что
      // такое не предусмотрено пока, между скобками должны быть операции 

      free(Tree);
      return MakeTree(Expr, first + 1, last - 1, result_tree);
  }

  if (min_priority == MAX_PRIORITY) // операций в этом куске не найдено, 
    { // считаем это = число или переменная
      int num_sym = last - first + 1;
      // вот тут может быть отлов ситуаций (2)(3)(5) - нет операций тут
      error = calc_evaluate(Expr + first, num_sym, &result);
      if (error) return error;

      Tree->value = result;
      return 0;
    }

  // в ситуаци (2)(-3)(+5) неправильно найдет - и +
  Tree->type = min_priority_type;
  PNode temp;
  error = MakeTree(Expr, first, min_priority_ptr - 1, &temp);
  if (error)  return error;
  Tree->left = temp;

  error = MakeTree(Expr, min_priority_ptr + min_priority_oparand_len, last, &temp);
  if (error)  return error;
  Tree->right = temp;
  
  return 0;
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
    if (error)
      return error;             // если ошибка - дальше не вычислять
  }
  if (NULL != Tree->right)
  {
    error = CalcTree(Tree->right, &num_right);
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
    case CALC_SIGN:
    {
      //       printf("[%g<sign>%g] ", num_left, num_right);
      if (num_right == 0)     *result =  0;
      else if(num_right < 0)  *result = -1;
      else if(num_right > 0)  *result =  1;
      return 0;
    }
    case CALC_ABS:
    {
      //       printf("[%g<abs>%g] ", num_left, num_right);
      if (num_right < 0)  *result = -num_right; 
      else                *result =  num_right;          // ОК
      return 0;
    }

    // ---------- ЛОГИЧЕСКИЕ БИТОВЫЕ ----- отбрасывают дробную часть
    case CALC_AND_BIT:   {
      *result = (double)(((int) num_left) & ((int)num_right));
      return 0;
    }
    case CALC_OR_BIT:    {
      *result = (double)(((int)num_left) | ((int)num_right));
      return 0;
    }
    case CALC_XOR_BIT:   {
      *result = (double)(((int)num_left) ^ ((int)num_right));
      return 0;
    }
    case CALC_NOT_BIT:   {
      //       printf("[%g<not>%g] ", num_left, num_right);
      *result = (double)(~(int)num_right);
      return 0;
    }
  }
  
  // ------------ ДОДЕЛАТЬ ВСЕ ОПЕРАЦИИ =-=-=-==-=-=-=-=-=-=-=-=-=-

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
  
  // явные ошибки и особые случаи
  if (str_len == 0)
    return CALC_LINE_EMPTY;
  if (is_comment(str))
    return CALC_LINE_COMMENT;
  if (is_only_spaces(str))
    return CALC_LINE_SPACES;
  if (is_bracket_error(str))    // пока проверка скобок только на парность
    return CALC_LINE_ERR_BRACKETS;
  
  // тут обработка
  
  char* str_to_process = prepare_expression(str);
  if (NULL == str_to_process)
    return CALC_LINE_ERR_MEMORY;

  PNode Tree;
  // разбор вражения, построение дерева
  error_code = MakeTree(str_to_process, 0, str_lenght(str_to_process) - 1, &Tree);

  if (!error_code)   // вычислять дерево только если не было ошибок в разборе
    error_code = CalcTree(Tree, result);
    
  delete_node(Tree);      // удалить дерево 
  free(str_to_process);   // удалить временную строку
  return error_code;
}