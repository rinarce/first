// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

// calc_process.c
// обработка строки - построение дерева разбора и вычисление его

// ---------------------------------------------------------------------------
#include <stdlib.h>   // memory
#include <ctype.h>    // для isspace()
#include <math.h>
#include <stdio.h>

#include "calc_process.h"
#include "str_functions.h"
#include "calc_variables.h"        // модуль для переменных и пр.

// --  Неявное умножение скобок ? использовать ? -----------------------------
#define CALC_USE_BRACKET_MULTIPLY  // считать ли 2(3) (4)5(6) умножением - ДА

// -- Логика приоритетов операций --------------------------------------------

#define PRIORITY_SEPARATOR   3   // ; разделитель выражений результат - правое выражение

#define PRIORITY_LETGLOBAL   4   // := глобальное присваивание
#define PRIORITY_LET         5   //  = присваивание

#define PRIORITY_BIT_XOR     8   // xor
#define PRIORITY_BIT_OR      9   // |
#define PRIORITY_BIT_AND    10   // &
#define PRIORITY_BIT_NOT    11   // ~

#define PRIORITY_PLUS       13   // +
#define PRIORITY_MINUS      13   // -

#define PRIORITY_MUL_DIV    15   // * / % 
#define PRIORITY_POWER      18   // ^ 

#define PRIORITY_FUNCS      20   // функции
#define PRIORITY_CONST      20   // константы

#define PRIORITY_BRACKETS   30   // (...)

#define PRIORITY_MAX       100   // фиктивное большое число приоритета


// --  Типы операций  --------------------------------------------------------
typedef enum        // типы операций, OK - реализовано полностью
{
  CALC_MINUS,       //OK -
  CALC_U_MINUS,     //OK - унарный - не используется, работает и так 
  CALC_PLUS,        //OK +
  CALC_U_PLUS,      //OK + унарный - не используется, работает и так 
  CALC_DIV,         //OK /
  CALC_MUL,         //OK *
  CALC_MOD,         //OK % - остаток от деления
  CALC_POWER,       //OK ^ - возведение в степень
  CALC_SQRT,        //OK sqrt()
  CALC_ABS,         //OK abs() - модуль
  CALC_SIGN,        //OK sign - знак числа == {-1, 0, 1}
  CALC_SIN,         // sin()
  CALC_COS,         // cos()
  CALC_TAN,         // tg()
  CALC_COTAN,       // ctg()
  CALC_ASIN,        // arcsin() 
  CALC_ACOS,        // arccos()
  CALC_ATAN,        // arctg()
  CALC_LN,          // ln()
  CALC_ROUND,       // round()  - округление к ближайшему
  CALC_FLOUR,       // flour()  - округление вниз
  CALC_CEIL,        // ceil()   - округление вверх
  CALC_LOG,         // log(a,x) - не реализовано

  CALC_BRACKETS,    //OK выражение в скобках
  CALC_PI,          //OK pi == M_PI ==  3.14159265358979323846
  CALC_E,           //OK e  == M_E  ==  2.71828182845904523536
  CALC_EXP,         // e(x) e^x

                    //  в битовых отбрасывается дробная часть !!!
  CALC_XOR_BIT,     //OK xor битовое исключающее или (^ занято возведением в степень)
  CALC_AND_BIT,     //OK & битовое 
  CALC_OR_BIT,      //OK | битовое
  CALC_NOT_BIT,     //OK ~ битовое отрицание

  
  CALC_SEPARATOR,   //OK ; разделитель подстрок 
  CALC_LET,         //OK переменная =             
  CALC_LETGLOBAL,   //OK глобальная переменная := 
  CALC_USER_FUNC,   // определение функции        - не реализовано
} OperatorType;

// --  Типы для двоичного дерева   -------------------------------------------

typedef struct Node           // узел дерева
{
  double value;               // значение
  OperatorType type;          // тип операции
  struct Node* left, * right; // поддерево левое и правое
} Node;

typedef struct Node* PNode;   // указатель на узел дерева


// ---------------------------------------------------------------------------
// Предварительная подготовка строки, возвращает новую строку
// - удаление ВСЕХ пробелов
// - разборка со сдвоенными -- ++ -+ +-
char* prepare_expression(char const* str)
{
  int made_changes = 1;
  char* new_str = str_remove_spaces(str);      // удалить пробелы
  if (NULL == new_str)  return NULL;

  while (made_changes)        // заменить множественные --- и +++
  {
    made_changes  = str_replace_all(new_str, "--", "+");
    made_changes += str_replace_all(new_str, "++", "+");
    made_changes += str_replace_all(new_str, "+-", "-");
    made_changes += str_replace_all(new_str, "-+", "-");
  }
  return new_str;
}

// ---------------------------------------------------------------------------
// удаляет узел дерева и все его дочерние узлы
void delete_node(PNode Tree)
{
  if (Tree == NULL) return;
  delete_node(Tree->left);
  delete_node(Tree->right);
  free(Tree);                 // удалить себя
}

// ---------------------------------------------------------------------------
// определяет приоритет операции для указателя ptr, длину операнда
// и тип операции (многовато)
int get_priority(char const* ptr, int *oper_len, OperatorType* oper_type)
{
  *oper_len = 1;
  switch (*ptr)
  {
  case '+':   *oper_type = CALC_PLUS;
              return PRIORITY_PLUS; 
  case '-':   *oper_type = CALC_MINUS;
              return PRIORITY_MINUS;
  case '/':   *oper_type = CALC_DIV;
              return PRIORITY_MUL_DIV;    
  case '*':   *oper_type = CALC_MUL;
              return PRIORITY_MUL_DIV;    
  case '%':   *oper_type = CALC_MOD;
              return PRIORITY_MUL_DIV;    
  case '^':   *oper_type = CALC_POWER;
              return PRIORITY_POWER;      
  case '&':   *oper_type = CALC_AND_BIT;
              return PRIORITY_BIT_AND;    
  case '~':   *oper_type = CALC_NOT_BIT;
              return PRIORITY_BIT_NOT;    
  case '|':   *oper_type = CALC_OR_BIT;
              return PRIORITY_BIT_OR;     
  case ';':   *oper_type = CALC_SEPARATOR;
              return PRIORITY_SEPARATOR;  
  case '=':   *oper_type = CALC_LET;
              return PRIORITY_LET;        
  }

  if (str_compare_fix_len(ptr, ":=", 2)) {
    *oper_len = 2;
    *oper_type = CALC_LETGLOBAL;
    return PRIORITY_LETGLOBAL;
  }

  if (*ptr == '(')
  { // выражение в скобках - как единый операнд, приоритет самый высокий
    // выделим кусок до следующей скобки парной этой
    int nested = 0;                            // счётчик открытых скобок
    char const* find_brac = ptr;
    do 
    { if (*find_brac == '(')        ++nested;  // открывающая скобка
      else if (*find_brac == ')')   --nested;  // закрывающая скобка
      ++find_brac;
    } while (nested != 0);

    *oper_len = find_brac - ptr;
    *oper_type = CALC_BRACKETS;
 
/* // отладочная печать - удалить
    char* i = ptr, * j = find_brac-1;
    printf("(->");  while (i <= j) printf("%c", *i++); printf("<-)\n");
*/
    return PRIORITY_BRACKETS;
  }

  
  if (str_compare_fix_len(ptr, "xor", 3)) { 
    *oper_type = CALC_XOR_BIT; 
    *oper_len = 3;    
    return PRIORITY_BIT_XOR;
  }
  
  if (str_compare_fix_len(ptr, "sin(", 4)) { 
    *oper_type = CALC_SIN;
    *oper_len = 3;
    return PRIORITY_FUNCS;
  }

  if (str_compare_fix_len(ptr, "cos(", 4)) { 
    *oper_type = CALC_COS;
    *oper_len = 3;
    return PRIORITY_FUNCS;
  }
  
  if (str_compare_fix_len(ptr, "ctg(", 4)) { 
    *oper_type = CALC_COTAN;
    *oper_len = 3;
    return PRIORITY_FUNCS;
  }
  
  if (str_compare_fix_len(ptr, "abs(", 4)) { 
    *oper_type = CALC_ABS;
    *oper_len = 3;
    return PRIORITY_FUNCS;
  }
   
  if (str_compare_fix_len(ptr, "tg(", 3)) { 
    *oper_len = 2;
    *oper_type = CALC_TAN;
    return PRIORITY_FUNCS;
  }
  if (str_compare_fix_len(ptr, "sqrt(", 5)) { 
    *oper_len = 4;
    *oper_type = CALC_SQRT;
    return PRIORITY_FUNCS;
  }
  if (str_compare_fix_len(ptr, "sign(", 5)) { 
    *oper_len = 4;
    *oper_type = CALC_SIGN;
    return PRIORITY_FUNCS;
  }


  // ДОДЕЛАТЬ ПОТОМ все операции ХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХ
  
  
  *oper_len = 1; //операция не найдена, сдвинуться на 1 символ ->
  return PRIORITY_MAX;
}


// ---------------------------------------------------------------------------
// первые символы строки - это число или переменная
// Шестнадцатеричные переводит, двоичные - ДА. Возврат - код ошибки (0 - ОК)
int calc_evaluate(char const* str, int symbols, double * result)
{
  // такое бывало на строках (2)(3) обрезанных до 2)(3
  if (symbols < 0) return CALC_ERR_ALGO; // ASSERT

  if (symbols == 0)
  { // всё пустое считаем за 0 - прощаем некоторые спорные случаи 3+ или ()
    *result = 0;
    //    printf("[Empty]");
    return 0;
  }

  // создаём новую строку
  char* new_str = (char*)malloc(symbols + 1);
  if (NULL == new_str)  return CALC_ERR_MEMORY;
  
  str_copy_fix_len(str, new_str, symbols);
  new_str[symbols] = '\0';                    // допишем конец строки


// ---------------------------------------------------------------------------
// ТУТ НУЖНО ПРОВЕРИТЬ НА ВСЕ КОНСТАНТЫ И ПЕРЕМЕННЫЕ, убрать их из операций
// ---------------------------------------------------------------------------
  if (variable_get(new_str, result))          // нашлась такая переменная
  {
    free(new_str); 
    return 0;
  }
  
  if (symbols == 2 && str_compare_fix_len(str, "pi", 2)) {
    *result = M_PI;     
    free(new_str);    
    return 0;
  }
  if (symbols == 1 && str_compare_fix_len(str, "e", 1))  {
    *result = M_E;      
    free(new_str);    
    return 0;
  }


// делаем для числа, проверка ошибок - встроенная в Си

  if (is_binary_digit(new_str, result))  // пробуем на двоичность
  {
    free(new_str); // тогда результат уже передан  наверх в *result
  }
  else  // ТУТ все остальные варианты, 0x... работает
  { 
    // sscanf_s относится к строкам довольно либерально, считаем это фичей
    // берёт из начала строки сколько сможет, в конце может быть 2фигни == 2

    int evaluated = sscanf_s(new_str, "%lf", result);
//    printf("[<%s>=%g{%d}]", new_str, *result, evaluated);
    free(new_str);
    if (evaluated != 1) //должно быть получено ровно 1 число, иначе ошибка
      return CALC_ERR_EVAL;
  }
  return 0;
}


// ---------------------------------------------------------------------------
// вычисляет дерево Tree -в-> *result и возвращает код ошибки или 0 если всё ОК
int CalcTree(PNode Tree, double* result)
{
  int error = 0;
  double num_left = 0, num_right = 0;
  
  // 1. если нет потомков - это число, или была пременная, стало тоже число
  if (Tree->left == NULL && Tree->right == NULL) {
    *result = Tree->value;      // вернули число
    return 0;
  }

  // 2. вычисляем поддеревья
  if (NULL != Tree->left)  {
    error = CalcTree(Tree->left, &num_left);
    if (error)  return error;    // если ошибка - дальше не вычислять
  }
  if (NULL != Tree->right) {
    error = CalcTree(Tree->right, &num_right);
    if (error)  return error;    // если ошибка - дальше не вычислять
  }

  // 3. выполняем операцию
  switch (Tree->type)
  { 
  case CALC_PLUS:     *result = num_left + num_right;
                      return 0;
  
  case CALC_MINUS:    *result = num_left - num_right;
                      return 0;
    
  case CALC_MUL:      *result = num_left * num_right;
                      return 0;
  
  case CALC_DIV:      // Проверим на деление на 0
                      if (num_right == 0)                   
                          return CALC_ERR_ZERO_DIV;         // Ошибка
                      *result = num_left / num_right;       // ОК
                      return 0;
  
  case CALC_MOD:      // Проверим на деление на 0
                      if (num_right == 0)                   
                          return CALC_ERR_ZERO_DIV;         // Ошибка
                      *result = fmod(num_left, num_right);  // ОК
                      return 0;
  
  case CALC_POWER:    // ПРОВЕРИТЬ НА ОШИБКИ АРГУМЕТОВ ?
                      *result = pow(num_left, num_right);
                      if (isnan(*result))     // Получено не число NaN (Not a Number)
                        return CALC_ERR_NAN;  // скорее всего - чётные корни из отрицательных
                      if (isinf(*result))     // Получена бесконечность Inf
                        return CALC_ERR_INF;  // скорее всего - 0 в отрицательной степени
                      return 0;
  
  case CALC_SQRT:     // Проверим на отрицательность
                      if (num_right < 0)                    
                          return CALC_ERR_SQRT_N;           // Ошибка
                      *result = sqrt(num_right);            // ОК
                      return 0;
  
  case CALC_SIGN:     if (num_right == 0)       *result = 0;
                      else if (num_right < 0)   *result = -1;
                      else if (num_right > 0)   *result = 1;
                      return 0;
  
  case CALC_ABS:      if (num_right < 0)  *result = -num_right;
                      else                *result =  num_right;      
                      return 0;
  

  // ---------- ЛОГИЧЕСКИЕ БИТОВЫЕ ----- отбрасывают дробную часть
  case CALC_AND_BIT:  *result = (double)(((int)num_left) & ((int)num_right));
                      return 0;
  case CALC_OR_BIT:   *result = (double)(((int)num_left) | ((int)num_right));
                      return 0;
  case CALC_XOR_BIT:  *result = (double)(((int)num_left) ^ ((int)num_right));
                      return 0;
  case CALC_NOT_BIT:  //       printf("[%g<not>%g] ", num_left, num_right);
                      *result = (double)(~(int)num_right);
                      return 0;

  case CALC_SEPARATOR:  // разделитель формул возвращает правый результат
                        //      printf("[%g<;>%g] ", num_left, num_right);
                      *result = num_right;
                      return 0;
  
  // ------------ ДОДЕЛАТЬ ВСЕ ОПЕРАЦИИ =-=-=-==-=-=-=-=-=-=-=-=-=-
  }

  // неизвестная операция - таких не должно быть
  return CALC_ERR_ALGO;
}


// ---------------------------------------------------------------------------
// строит дерево вычислений для str[first...last] 
// построенное дерево возвращает в *result_tree 
// return - код ошибки (0 - ОК)
int MakeTree(char const str[], int first, int last, PNode * result_tree)
{
  int error;                        // код ошибки
  double result = 0;                // результат
  int str_len = last - first + 1;   // длина анализируемого куска
  
  PNode Tree = (PNode)malloc(sizeof(Node)); // создать в памяти новую вершину
  if (NULL == Tree)  return CALC_ERR_MEMORY;
  
  Tree->left = NULL;
  Tree->right = NULL;
  Tree->value = 0;
  *result_tree = Tree;

  // case 0 - в рассматриваемом куске строки 1 символ: число или переменная
  if (first == last) 
  {
    error = calc_evaluate(str + first, 1, &result);
    if (error) { free(Tree);  return error; }

    Tree->value = result;           
    return 0;
  }
  
  
  // step 1 - Находим операцию с МИНИМАЛЬНЫМ ПРИОРИТЕТОМ
  // в этих переменных сохранится операция с мин.приоритетом (последняя из таких)
  int min_priority = PRIORITY_MAX;    // минимальный приоритет операции в строке
  int min_priority_ptr = 0;           // указатель на эту операцию
  int min_priority_oparand_len = 1;   // длина записи операции символов
  OperatorType min_priority_type = 0; // минимальный приоритет - тип операции
  
  // эти переменные определяются для каждой найденой операции
  int priority;                       // найденный приоритет для очередного символа
  int oper_len = 1;                   // сколько символов в записи операции - сместиться на столько
  OperatorType oper_type = 0;         // тип операции

  for (int i = first; i <= last; i+=oper_len) 
  {
    priority = get_priority(str+i, &oper_len, &oper_type);
    // для выполнения операций слева-направо тут должно быть <=
    // тогда операция правее выберется раньше, а выполнится позже (при равных приоритетах)
    // операция правее перебьёт минимум приоритета такой же слева от неё
    if (priority <= min_priority) 
    {   
      if (PRIORITY_POWER == priority && PRIORITY_POWER == min_priority)
      { // для возведения в степень выполнять справа - налево, 
        // т.е. следующие встреченные ^ НЕ перезапишут ранние ^ 
        // => левое возведение в степень попадёт в разбор раньше а выполнится позже
        // printf("{skip second ^}");
        // НИЧЕГО НЕ ДЕЛАТЬ, ЭТО возведение в степень, причём не первое в этом куске
      }
      else
      { // все остальные операции слева-направо => искать последнюю такую в строке
        min_priority_ptr = i;
        min_priority = priority;
        min_priority_oparand_len = oper_len;
        min_priority_type = oper_type;
      }
    }
  }
  
  // case 1 - не нашлось операций меньше СКОБОК
  if (min_priority == PRIORITY_BRACKETS) 
  { 
    if (min_priority_ptr == first && min_priority_oparand_len == str_len)
    { 
      // case 1.0. - OK, всё выражение в скобках, избавимся от них в новом вызове
      free(Tree);
      return MakeTree(str, first + 1, last - 1, result_tree);
    }

    // тут ситуация, когда найденные скобки не занимают всю длину обрабатываемого куска  
    // это значит, что и операций меньшего приоритета тоже не найдено
    // варианты 1(2) или (3)(4) или (2)3 или 2(3)4(5)6 и т.п.
    
    // решение 1 - считать это ошибкой, алгоритм дальше не пойдёт
    // тогда закоментировать #define CALC_USE_BRACKET_MULTIPLY в начале файла

#ifndef CALC_USE_BRACKET_MULTIPLY      // считать ли 2(3) (4)5(6) умножением - ДА
    return CALC_ERR_BRACKETS;
#endif // !CALC_USE_BRACKET_MULTIPLY   // считать ли 2(3) (4)5(6) умножением - ДА
    
    // решение 2 - считать что в таких случаях используется неявное умножение
    Tree->type = CALC_MUL;             // умножение
    int left_start = first,            // делим этот кусок строки на 2
        left_end,
        right_start,
        right_end = last;

    if (min_priority_ptr == first)    
    { // case 1.1. - первая скобка в начале этого куска строки 
          // от начала куска до закрывающей скобки включая - левый операнд
          left_end = first + min_priority_oparand_len - 1;
    }
    else      
    { // case 1.2. - скобка НЕ в начале строки 
          // от начала куска до начала скобок - левый операнд
          left_end = min_priority_ptr - 1;
          // в т.ч. случаи когда скобки посередине, это обработается при другом вызове
          // когда они окажутся в начале куска
    }

    right_start = left_end + 1;   // правый начинается сразу за левым
    PNode temp;            
    error = MakeTree(str, left_start, left_end, &temp);
    if (error) { free(Tree);  return error; }

    Tree->left = temp;     // записываем поддерево если не было ошибок

    error = MakeTree(str, right_start, right_end, &temp);
    if (error) { free(Tree);  return error; }

    Tree->right = temp;     // записываем поддерево если не было ошибок

    return 0;               // ОК. ошибок нет
  }
  
  // case 2 - операция в этом куске НЕ НАЙДЕНА, 
  if (min_priority == PRIORITY_MAX) 
    { 
      // считаем что это - число или переменная - вычислим операнд
      error = calc_evaluate(str + first, str_len, &result);
      if (error) { free(Tree);  return error; }

      Tree->value = result; // поддеревьев не будет, сохранить результат
      return 0;
    }

  // case 3 - операция НАЙДЕНА -  записывается её тип и создаются два поддерева 
  // - то что в этом куске строки слева от операции и то что справа
  
  // case 3.1. - Это присваивание переменной
  // !! Тогда её надо вычислить тут же, возможно она будет использоваться в строке
  if  (min_priority_type == CALC_LET
    || min_priority_type == CALC_LETGLOBAL)
  { 
    // считаем что всё слева = имя переменной, справа значение
    int name_len = min_priority_ptr - first;
    if (name_len == 0)            // переменная без имени (слева от = ничего нет)
      { free(Tree);  return CALC_ERR_VARZ; }

    // создаём строку с сменем переменной
    char* var_name = str_make_substr(str, first, min_priority_ptr - 1);
    if (NULL == var_name)  
      { free(Tree);  return  CALC_ERR_MEMORY; }

  
    PNode temp;            
    // Во временное дерево - всё что после = или :=
    // от конца символа операции (возможно несколько символов) до конца куска строки
    error = MakeTree(str, min_priority_ptr + min_priority_oparand_len, last, &temp);
    if (error) {  free(Tree);  return error;   }
    
    double var_value;
    error = CalcTree (temp, &var_value);
    if (error) { free(Tree);  return error; }

    Tree->value = var_value;            // в узле дерева будет значение, без потомков
    Tree->type = min_priority_type;     // тип не используется, запомним на всякий случай
   
    // создать переменные
    if (min_priority_type == CALC_LET)  
      error = variable_make(var_name, var_value);
    if (min_priority_type == CALC_LETGLOBAL) 
      error = variable_make_global(var_name, var_value);
    if (error) free(Tree);
    
    free(var_name);                     // уже не нужно
    delete_node(temp);                  // уже не нужно
    return error;
  }
  
  // case 3.1. - Прочие обычные операции
  Tree->type = min_priority_type;
  
  PNode temp;            // от начала куска до символа операции не включая
  error = MakeTree(str, first, min_priority_ptr - 1, &temp);
  if (error) { free(Tree);  return error; }
  Tree->left = temp;     // записываем поддерево если не было ошибок
  
  // от конца символа операции (возможно несколько символов) до конца куска строки
  error = MakeTree(str, min_priority_ptr + min_priority_oparand_len, last, &temp);
  if (error) { free(Tree);  return error; }
  Tree->right = temp;
  
  return 0;  // если добрались сюда => все этапы пройдены без ошибок
}



// ------------ Главная функция -------------------------------------------

// вычисляет строку выражений, возвращает тип строки (ок или ошибка) и *result
int process_line(char const* str, double* result)
{
  int error_code = 0;
  *result = 0;
  unsigned str_len = str_lenght(str);
  
  // явные ошибки и особые случаи
  if (str_len == 0)           return CALC_LINE_EMPTY;
  if (is_comment(str))        return CALC_LINE_COMMENT;
  if (is_only_spaces(str))    return CALC_LINE_SPACES;
  if (is_bracket_error(str))  return CALC_ERR_BRACKETS;
  
  // тут обработка
  
  char* str_to_process = prepare_expression(str);
  if (NULL == str_to_process)  return CALC_ERR_MEMORY;

  PNode Tree;
  
  variable_clear_local();  // очистим локальные переменные
  
  // разбор вражения, построение дерева
   
  error_code = MakeTree(str_to_process, 0, str_lenght(str_to_process) - 1, &Tree);

  if (!error_code)        // вычислять дерево только если не было ошибок в разборе
    error_code = CalcTree(Tree, result);
    
  delete_node(Tree);      // удалить дерево 
  free(str_to_process);   // удалить временную строку
 
  variable_clear_local(); // очистим локальные переменные

  return error_code;
}