// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

// calc_process.c - обработка строки - построение дерева разбора и вычисление его

#include <stdlib.h>   // memory
#include <ctype.h>    // для isspace()
#include <math.h>
#include <stdio.h>

#include "common_defs.h"
#include "str_functions.h"
#include "calc_variables.h"

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
typedef enum operator_t {      // типы операций, OK - реализовано полностью
  CALC_MINUS,       //OK -
  CALC_PLUS,        //OK +
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
  CALC_RAND,        // rand(x)  - случайное целое число от (0 до Х) 
  CALC_ROUND,       // round()  - округление к ближайшему
  CALC_FLOUR,       // flour()  - округление вниз
  CALC_CEIL,        // ceil()   - округление вверх
  CALC_LOG,         // log(a,x) - не реализовано
  CALC_EXP,         // e(x) e^x

  CALC_BRACKETS,    //OK выражение в скобках
  CALC_SEPARATOR,   //OK ; разделитель подстрок  
  CALC_LET,         //OK переменная =             
  CALC_LETGLOBAL,   //OK глобальная переменная := 

                    //  в битовых отбрасывается дробная часть !!!
  CALC_XOR_BIT,     //OK xor битовое исключающее или (^ занято возведением в степень)
  CALC_AND_BIT,     //OK & битовое 
  CALC_OR_BIT,      //OK | битовое
  CALC_NOT_BIT,     //OK ~ битовое отрицание
} operator_t;

// --  Типы для двоичного дерева   -------------------------------------------

typedef struct tree_node_t {  
  double value;                       // значение
  operator_t type;                    // тип операции
  struct tree_node_t* left, * right;  // поддерево левое и правое
} tree_node_t;

typedef struct tree_node_t* p_tree_t; // указатель на узел дерева


// ---------------------------------------------------------------------------
// Предварительная подготовка строки, возвращает новую строку
// - удаление ВСЕХ пробелов
// - разборка со сдвоенными -- ++ -+ +-
static char* _prepareLine(char const* str) {
  int wasChanges = 1;
  char* newStr = StrRemoveSpaces(str);      // удалить пробелы
  if (NULL == newStr)  
    return NULL;

  while (wasChanges) {                      // заменить множественные --- и +++
    wasChanges  = StrReplaceAll(newStr, "--", "+");
    wasChanges += StrReplaceAll(newStr, "++", "+");
    wasChanges += StrReplaceAll(newStr, "+-", "-");
    wasChanges += StrReplaceAll(newStr, "-+", "-");
  }
  return newStr;
}

// ---------------------------------------------------------------------------
// удаляет узел дерева и все его дочерние узлы
void _deleteTree(p_tree_t tree) {
  if (tree != NULL) {
    _deleteTree(tree->left);
    _deleteTree(tree->right);
    free(tree);                 // удалить себя
  }
}

// ---------------------------------------------------------------------------
// определяет приоритет операции для указателя ptr, длину операнда
// и тип операции (всё сразу за один проход)
static int _getPriority(char const* ptr, int *operLen, operator_t* operType) {
  *operLen = 1;
  switch (*ptr) {
    case '+':   
      *operType = CALC_PLUS;
      return PRIORITY_PLUS; 
    case '-':   
      *operType = CALC_MINUS;
      return PRIORITY_MINUS;
    case '/':   
      *operType = CALC_DIV;
      return PRIORITY_MUL_DIV;    
    case '*':   
      *operType = CALC_MUL;
      return PRIORITY_MUL_DIV;    
    case '%':   
      *operType = CALC_MOD;
      return PRIORITY_MUL_DIV;    
    case '^':   
      *operType = CALC_POWER;
      return PRIORITY_POWER;      
    case '&':   
      *operType = CALC_AND_BIT;
      return PRIORITY_BIT_AND;    
    case '~':   
      *operType = CALC_NOT_BIT;
      return PRIORITY_BIT_NOT;    
    case '|':   
      *operType = CALC_OR_BIT;
      return PRIORITY_BIT_OR;     
    case ';':   
      *operType = CALC_SEPARATOR;
      return PRIORITY_SEPARATOR;  
    case '=':   
      *operType = CALC_LET;
      return PRIORITY_LET;        
  }

  if (StrCompareFixLen(ptr, ":=", 2)) {
    *operLen = 2;
    *operType = CALC_LETGLOBAL;
    return PRIORITY_LETGLOBAL;
  }

  if (*ptr == '(')  { // выражение в скобках - как единый операнд
    // выделим кусок до следующей скобки парной этой
    int nested = 0;                           // счётчик открытых скобок
    char const* findPairBracket = ptr;
    do { 
      if (*findPairBracket == '(')        
        ++nested;                           
      else if (*findPairBracket == ')')   
        --nested;  
      ++findPairBracket;
    } while (nested != 0);                    // ищем только парную скобку

    *operLen  = findPairBracket - ptr;        // длина участка вместе со скобками
    *operType = CALC_BRACKETS;
    return PRIORITY_BRACKETS;
  }

  if (StrCompareFixLen(ptr, "xor", 3)) { 
    *operType = CALC_XOR_BIT; 
    *operLen = 3;    
    return PRIORITY_BIT_XOR;
  }
  if (StrCompareFixLen(ptr, "sin(", 4)) { 
    *operType = CALC_SIN;
    *operLen = 3;
    return PRIORITY_FUNCS;
  }
  if (StrCompareFixLen(ptr, "cos(", 4)) { 
    *operType = CALC_COS;
    *operLen = 3;
    return PRIORITY_FUNCS;
  }
  if (StrCompareFixLen(ptr, "ctg(", 4)) { 
    *operType = CALC_COTAN;
    *operLen = 3;
    return PRIORITY_FUNCS;
  }
  if (StrCompareFixLen(ptr, "abs(", 4)) { 
    *operType = CALC_ABS;
    *operLen = 3;
    return PRIORITY_FUNCS;
  }
  if (StrCompareFixLen(ptr, "tg(", 3)) { 
    *operLen = 2;
    *operType = CALC_TAN;
    return PRIORITY_FUNCS;
  }
  if (StrCompareFixLen(ptr, "sqrt(", 5)) { 
    *operLen = 4;
    *operType = CALC_SQRT;
    return PRIORITY_FUNCS;
  }
  if (StrCompareFixLen(ptr, "sign(", 5)) { 
    *operLen = 4;
    *operType = CALC_SIGN;
    return PRIORITY_FUNCS;
  }

  // ДОДЕЛАТЬ ПОТОМ все операции ХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХ
  
  *operLen = 1;           //операция не найдена, сдвинуться на 1 символ ->
  return PRIORITY_MAX;
}


// ---------------------------------------------------------------------------
// первые символы строки - это число или переменная
// Шестнадцатеричные переводит, двоичные - ДА. Возврат - код ошибки (0 - ОК)
static calc_err_t _calcEvaluate(char const* str, int symbols, double * result) {
  if (symbols < 0) 
    return CALC_ERR_ALGO; // ASSERT - количество символов отрицательно - не порядок

  if (symbols == 0) { // всё пустое считаем за 0 - прощаем некоторые спорные случаи 3+ или ()
    *result = 0;      // так же для унарных операций, вызовов функций - слева ничего нет
    return CALC_OK;
  }

  char* newStr = (char*)malloc(symbols + 1);
  if (NULL == newStr)  
    return CALC_ERR_MEMORY;
  
  StrCopyFixLen(str, newStr, symbols);
  newStr[symbols] = '\0';                    // допишем конец строки
  
  // ТУТ ПРОВЕРКА НА КОНСТАНТЫ И ПЕРЕМЕННЫЕ
  if (VariableGet(newStr, result)) {         // нашлась такая переменная
    free(newStr); 
    return CALC_OK;
  }
  
  // делаем для числа, проверка ошибок - встроенная в Си

  if (IsBinaryDigit(newStr, result)) {       // пробуем на двоичность
    free(newStr); // тогда результат уже передан  наверх в *result
  }
  else {  // ТУТ все остальные варианты, 0x... работает
          // sscanf_s относится к строкам довольно либерально, считаем это фичей
          // берёт из начала строки сколько сможет, в конце может быть 2фигни == 2

    int evaluated = sscanf_s(newStr, "%lf", result);
    free(newStr);
    if (evaluated != 1)     //должно быть получено ровно 1 число, иначе ошибка
      return CALC_ERR_EVAL;
  }
  return CALC_OK;
}


// ---------------------------------------------------------------------------
// вычисляет дерево tree -в-> *result и возвращает код ошибки или 0 если всё ОК
static calc_err_t _calcTree(p_tree_t tree, double* result) {
  int error = 0;
  double valueLeft = 0, valueRight = 0;
  
  // 1. если нет потомков - это число, или была пременная, стало тоже число
  if (tree->left == NULL && tree->right == NULL) {
    *result = tree->value;       // вернуть число
    return CALC_OK;
  }

  // 2. вычисляем поддеревья
  if (NULL != tree->left)  {
    error = _calcTree(tree->left, &valueLeft);
    _deleteTree(tree->left);  // поддерево вычислено, уже не нужно
    if (error)  
      return error;           // если ошибка - дальше не вычислять
  }
  if (NULL != tree->right) {
    error = _calcTree(tree->right, &valueRight);
    _deleteTree(tree->right); // поддерево вычислено, уже не нужно
    if (error)  
      return error;           // если ошибка - дальше не вычислять
  }

  // 3. выполняем операцию
  switch (tree->type) { 
    case CALC_PLUS:     
      *result = valueLeft + valueRight;
      return CALC_OK;
    case CALC_MINUS:    
      *result = valueLeft - valueRight;
      return CALC_OK;
    case CALC_MUL:      
      *result = valueLeft * valueRight;
      return CALC_OK;
    
    case CALC_DIV:                        // Проверим на деление на 0
      if (valueRight == 0)                
        return CALC_ERR_ZERO_DIV;         
      *result = valueLeft / valueRight;   
      return CALC_OK;
    
    case CALC_MOD:                        // Проверим на деление на 0
      if (valueRight == 0)                
        return CALC_ERR_ZERO_DIV;
      *result = fmod(valueLeft, valueRight);
      return CALC_OK;
    
    case CALC_POWER:                      // Проверить на ошибки уже результат
      *result = pow(valueLeft, valueRight);   
      if (isnan(*result))                 // Получено не число NaN (Not a Number)
        return CALC_ERR_NAN;              // скорее всего - чётные корни из отрицательных
      if (isinf(*result))                 // Получена бесконечность Inf
        return CALC_ERR_INF;              // скорее всего - 0 в отрицательной степени
      return CALC_OK;
    
    case CALC_SQRT:                       // Проверим на отрицательность
      if (valueRight < 0)                    
        return CALC_ERR_SQRT_N;           
      *result = sqrt(valueRight);         
      return CALC_OK;
    
    case CALC_SIGN:     
      if (valueRight == 0)     
        *result =  0;
      else if (valueRight < 0) 
        *result = -1;
      else if (valueRight > 0) 
        *result =  1;
      return CALC_OK;

    case CALC_ABS:      
      if (valueRight < 0)      
        *result = -valueRight;
      else                    
        *result =  valueRight;      
      return CALC_OK;
  
    // ---------- ЛОГИЧЕСКИЕ БИТОВЫЕ ----- отбрасывают дробную часть
    case CALC_AND_BIT:  
      *result = (double)(((int)valueLeft) & ((int)valueRight));
      return CALC_OK;
    case CALC_OR_BIT:   
      *result = (double)(((int)valueLeft) | ((int)valueRight));
      return CALC_OK;
    case CALC_XOR_BIT:  
      *result = (double)(((int)valueLeft) ^ ((int)valueRight));
      return CALC_OK;
    case CALC_NOT_BIT:  
      *result = (double)(~(int)valueRight);
      return CALC_OK;

    case CALC_SEPARATOR:      // разделитель формул возвращает правый результат
      *result = valueRight;
      return CALC_OK;
  
  // ------------ ДОДЕЛАТЬ ВСЕ ОПЕРАЦИИ =-=-=-==-=-=-=-=-=-=-=-=-=-

    default:
      return CALC_ERR_ALGO;   // неизвестная операция - таких не должно быть
  }
  
  return CALC_ERR_ALGO;       // Сюда попасть невозможно наверное
}


// ---------------------------------------------------------------------------
// строит дерево вычислений для str[first...last] - // построенное дерево возвращает в *resultTree 
// return - код ошибки (0 - ОК)
static calc_err_t _makeTree(char const str[], int first, int last, p_tree_t * resultTree) {
  calc_err_t error;                 
  int strLen = last - first + 1;   // длина анализируемого куска
  
  p_tree_t tree = (p_tree_t)malloc(sizeof(tree_node_t)); // создать в памяти новую вершину
  if (NULL == tree)  
    return CALC_ERR_MEMORY;

  tree->left = NULL;
  tree->right = NULL;
  tree->value = 0;
  *resultTree = tree; // сразу присоединим к существующему дереву, чтобы тут не освобождать в разных случаях ошибок

  // case 0 - в рассматриваемом куске строки 1 символ: число или переменная
  if (first == last) 
    return _calcEvaluate(str + first, 1, &(tree->value));


  // step 1 - Находим операцию с МИНИМАЛЬНЫМ ПРИОРИТЕТОМ
  // в этих переменных сохранится операция с мин.приоритетом (последняя из таких)
  int minPriority = PRIORITY_MAX;     // минимальный приоритет операции в строке
  int minPriorityPtr = 0;             // указатель на эту операцию
  int minPriorityOparandLen = 1;      // длина записи операции символов
  operator_t minPriorityOperator = 0; // минимальный приоритет - тип операции
  
  // эти переменные определяются для каждой найденой операции
  int priority;                       // найденный приоритет для очередного символа
  int currOperatorLen = 1;            // сколько символов в записи операции - сместиться на столько
  operator_t currOperator = 0;        // тип операции

  for (int position = first; position <= last; position += currOperatorLen) {
    priority = _getPriority(str + position, &currOperatorLen, &currOperator);
    // для выполнения операций слева-направо тут должно быть <=
    // тогда операция правее выберется раньше, а выполнится позже (при равных приоритетах)
    // операция правее перебьёт минимум приоритета такой же слева от неё
    if (priority <= minPriority) {   
      if (PRIORITY_POWER == priority && PRIORITY_POWER == minPriority) { 
        // для возведения в степень выполнять справа - налево, 
        // т.е. следующие встреченные ^ НЕ перезапишут ранние ^ 
        // => левое возведение в степень попадёт в разбор раньше а выполнится позже
        // printf("{skip second ^}");
        // НИЧЕГО НЕ ДЕЛАТЬ, ЭТО возведение в степень, причём не первое в этом куске
      }
      else { // все остальные операции слева-направо => искать последнюю такую в строке
        minPriorityPtr = position;
        minPriority = priority;
        minPriorityOparandLen = currOperatorLen;
        minPriorityOperator = currOperator;
      }
    }
  }
  
  // case 1 - не нашлось операций меньше СКОБОК
  if (minPriority == PRIORITY_BRACKETS) { 
    if (minPriorityPtr == first && minPriorityOparandLen == strLen) {
      // case 1.0. - OK, всё выражение в скобках, избавимся от них в новом вызове
      p_tree_t temp;
      error = _makeTree(str, first + 1, last - 1, &temp);
      if (error == CALC_OK)                       // разбор выражения прошёл успешно
        error = _calcTree(temp, &(tree->value));  // можно сразу вычислить это выражение
      _deleteTree(temp);                          // это поддерево вычислено и уже не нужно
      return error;
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
    tree->type = CALC_MUL;             
    int leftStart = first,             // делим этот кусок строки на 2
        leftEnd,
        rightStart,
        rightEnd = last;

    if (minPriorityPtr == first) { 
      // case 1.1. - первая скобка в начале этого куска строки 
      // от начала куска до закрывающей скобки включая - левый операнд
      leftEnd = first + minPriorityOparandLen - 1;
    }
    else { 
      // case 1.2. - скобка НЕ в начале строки 
      // от начала куска до начала скобок - левый операнд
      leftEnd = minPriorityPtr - 1;
      // в т.ч. случаи когда скобки посередине, это обработается при другом вызове
      // когда они окажутся в начале куска
    }

    rightStart = leftEnd + 1;   // правый начинается сразу за левым
    error = _makeTree(str, leftStart, leftEnd, &(tree->left));
    if (error != CALC_OK)
      return error; 
    return _makeTree(str, rightStart, rightEnd, &(tree->right));
  }
  
  // case 2 - операция в этом куске НЕ НАЙДЕНА, 
  if (minPriority == PRIORITY_MAX) 
    // считаем что это - число или переменная - вычислим операнд прямо в tree->value
    return _calcEvaluate(str + first, strLen, &(tree->value));
    

  // case 3 - операция НАЙДЕНА -  записывается её тип и создаются два поддерева 
  // - то что в этом куске строки слева от операции и то что справа
  
  // case 3.1. - Это присваивание переменной
  // !! Тогда её надо вычислить тут же, возможно она будет использоваться в строке
  if (minPriorityOperator == CALC_LET || minPriorityOperator == CALC_LETGLOBAL) {
    // считаем что всё слева от = имя переменной, справа значение
    int varNameLen = minPriorityPtr - first;
    if (varNameLen == 0)             // переменная без имени (слева от = ничего нет)
      return CALC_ERR_VARZ;

    // создаём строку с сменем переменной
    char* varName = StrMakeSubstr(str, first, minPriorityPtr - 1);
    if (NULL == varName) 
      return  CALC_ERR_MEMORY;

    p_tree_t temp;                       // Во временное дерево - всё что после = или :=
    error = _makeTree(str, minPriorityPtr + minPriorityOparandLen, last, &temp);

    if (error == CALC_OK) {                     // удалось разобрать выражение
      error = _calcTree(temp, &(tree->value));  // вычислим значение для присваивания переменной

      if (error == CALC_OK) {                   // удалось вычислить выражение - в узле дерева будет значение, без потомков
        // создать переменные (будет вызвана только 1 функция - локальные или глобальные переменные)
        if (minPriorityOperator == CALC_LET)
          error = VariableMake(varName, tree->value);
        if (minPriorityOperator == CALC_LETGLOBAL)
          error = VariableMakeGlobal(varName, tree->value);
      }
    }
    free(varName);                     // уже не нужно
    _deleteTree(temp);                 // уже не нужно
    return error;
  }
  
  // case 3.1. - Прочие обычные операции
  tree->type = minPriorityOperator;
  
  // от начала куска до символа операции не включая
  error = _makeTree(str, first, minPriorityPtr - 1, &(tree->left));
  if (error != CALC_OK)
    return error; 
 
  // от конца символа операции (возможно несколько символов) до конца куска строки
  return _makeTree(str, minPriorityPtr + minPriorityOparandLen, last, &(tree->right));
}



// ------------ Главная функция -------------------------------------------

// вычисляет строку выражений, возвращает тип строки (ок или ошибка) и *result
calc_err_t ProcessLine(char const* str, double* result) {
  int error = 0;
  
  // явные ошибки и особые случаи
  if (StrLenght(str) == 0)           
    return CALC_LINE_EMPTY;
  if (IsComment(str))        
    return CALC_LINE_COMMENT;
  if (IsOnlySpaces(str))    
    return CALC_LINE_SPACES;
  if (IsBracketError(str))  
    return CALC_ERR_BRACKETS;
  
  // тут предобработка строки
  char* strForProcess = _prepareLine(str);
  if (NULL == strForProcess)  
    return CALC_ERR_MEMORY;

  p_tree_t tree;
  
  VariableClearLocal();   // очистим локальные переменные
  
  // разбор выражения, построение дерева
  error = _makeTree(strForProcess, 0, StrLenght(strForProcess) - 1, &tree);

  if (error == CALC_OK)   // вычислять дерево только если не было ошибок в разборе
    error = _calcTree(tree, result);
    
  _deleteTree(tree);      // удалить дерево 
  free(strForProcess);    // удалить временную строку
 
  VariableClearLocal();   // очистим локальные переменные
  return error;
}
