#pragma once

#define M_E        2.71828182845904523536
#define M_LOG2E    1.44269504088896340736
#define M_LOG10E   0.434294481903251827651
#define M_LN2      0.693147180559945309417
#define M_LN10     2.30258509299404568402
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616
#define M_1_PI     0.318309886183790671538
#define M_2_PI     0.636619772367581343076
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2    1.41421356237309504880
#define M_SQRT1_2  0.707106781186547524401

//const double PI = 3.141592653589793238463;
//const double E = 2.71828182845904523536;

enum calc_line_type
{
  CALC_LINE_OK,           // это корректное выражение
  CALC_LINE_COMMENT,      // это комментарий
  CALC_LINE_EMPTY,        // это совершенно пустая строка
  CALC_LINE_SPACES,       // это строка без значащих символов
  CALC_LINE_LAST,
  CALC_LINE_ERR_PARSE,    // ошибка - во время разбора выражения
  CALC_LINE_ERR_MEMORY,   // ошибка - выделения памяти
  CALC_LINE_ERR_ZERO_DIV, // ошибка - деление на 0
  CALC_LINE_ERR_BRACKETS, // ошибка - непарность скобок
  CALC_LINE_ERR_SQRT_N,   // ошибка - квадратный корень из отрицательных
  CALC_LINE_ERR_ALGO,     // ошибка - в алгоритме что-то идёт не так
  CALC_LINE_ERR_X,        // ошибка - .... пока не придумано
  CALC_LINE_ERR_OTHER,    // ошибка - прочие
  CALC_LINE_ERR_COUNT,    // ошибка - масимальный номер перечисления
};

// вычисляет строку выражений, возвращает тип строки (ок или ошибка) и результат
int process_line(char* input_line, double* result);


typedef enum NodeType
{                   //OK - реализовано полностью
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
  CALC_FLOUR,       // flour() - округление вниз
  CALC_CEIL,        // ceil()  - округление к ближнему
  CALC_LOG,         // log(a,x)
  CALC_BRACKETS,    //OK выражение в скобках
  CALC_PI,          //OK pi
  CALC_E,           // e(x) e^x
  CALC_VAR,         // переменная              - не используется
  CALC_GLOBAL_VAR,  // глобальная переменная   
  CALC_FUNC,        // функция                 - не используется
} NodeType;

// узел дерева
typedef struct Node 
{
  double value;               // значение
  int ready;                  // 1 если значение готово - не используется
  NodeType type;              // какого типа
  struct Node* left, * right; // поддерево левое и правое
} Node;

typedef struct Node* PNode;   // указатель на узел дерева

