// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "common_defs.h"
#include "str_functions.h"

typedef struct                // тип структуры для одного собщения
{
  calc_err type;
  char* text_en;
  char* text_ru;
} result_message; 

result_message  result_types[] = { 
// все типы результата и соответствующие им сообщения EN, RU
{ CALC_OK,            "OK",                           "OK - корректное выражение"   },
{ CALC_LINE_COMMENT,  "Comment",                      "Комментарий"                 },
{ CALC_LINE_EMPTY,    "Empty",                        "Пустая строка"               },
{ CALC_LINE_SPACES,   "Only spaces",                  "Строка без значащих символов"},

{ CALC_ERR_INPUT,     "Input. Not enought memory",    "Ввод. Не хватает памяти"     },
{ CALC_ERR_PARSE,     "Can' parse expression.",       "Во время разбора выражения"  },
{ CALC_ERR_EVAL,      "Can't evaluate number.",       "Преобразования в число"      },
{ CALC_ERR_MEMORY,    "Not enough memory.",           "Выделения памяти"            },
{ CALC_ERR_ZERO_DIV,  "Divide by 0.",                 "Деление на 0"                },
{ CALC_ERR_BRACKETS,  "Brackets mismatch.",           "Непарность скобок"           },
{ CALC_ERR_SQRT_N,    "Square root from negative.",   "Квадратный корень из отрицательного"},
{ CALC_ERR_NAN,       "NaN - result = Not a Number.", "Получено NaN - не число"     },
{ CALC_ERR_INF,       "Inf - result = Infinity.",     "Получено Inf - бесконечность"},
{ CALC_ERR_ALGO,      "ASSERT. Something wrong.",     "В алгоритме что-то не так"   },
{ CALC_ERR_X,         "Jet not defined error !",      ".... пока не придумано"      },
{ CALC_ERR_VARS,      "Variables.",                   "С переменными"               },
{ CALC_ERR_VARZ,      "Variable - without name.",     "Переменная без имени"        },
{ CALC_ERR_VAR_BADNAME,"Variable - bad name.",        "Переменная - плохое имя"     },
{ CALC_ERR_OTHER,     "Other error.",                 "Труднообъяснимые ошибки"     },
{ CALC_ERR_COUNT,     "Not recognized error type.",   "Таких ошибок не бывает"      },
};

result_message default_message = 
                 { 0, "Not recognized error type!",   "Таких ошибок не бывает!"     };

int result_message_count = sizeof(result_types) / sizeof(result_message); // Количество разных сообщений

// ---------------------------------------------------------------------------
// вводит строку произвольной длины, самостоятельно выделяет память
// в *str возвращает указатель на строку, return = код ошибки
// \n в конце обрезается, но считается в длине (длина == 0 - конец потока ввода)
// при нехватке памяти - пропуск до конца строки, введённое отбросить
calc_err read_input_line(FILE* input_stream, char** str)
{
  char* result_str = NULL;  // Это указатель на итоговую строку, тут накапливаем ввод
  unsigned int str_len = 0; // Накапливаем длину строки, в конце - возвращаем
  char buffer[DST_BUFFER_SIZE + 1] = { 0 };     // Для порций ввода
  
  while (1)  // считываем строку порциями размера DST_BUFFER_SIZE
  {
    // fgets читает на 1 символ меньше, так как в конце всегда добавляет '\0'
    unsigned int input_len = str_lenght(fgets(buffer, DST_BUFFER_SIZE + 1, input_stream));
    
    if (0 == input_len)
      return CALC_LINE_THE_END; //  закончился поток ввода, 

    if (buffer[input_len - 1] == '\n')    // отрезаем '\n'
        buffer[input_len - 1] =  '\0';  

    // просим новый кусок памяти
    char* new_str = (char*)realloc(result_str, str_len + input_len + 1);

    if (NULL == new_str)  // выделение памяти не удалось, 
    { // обнуление введёной строки и пропуск данных до конца строки ! п 2.4.7.
      free(result_str);
      *str = NULL;

      // если использован не весь входной буфер, или обрезан \n => ввод закончен
      while (input_len == DST_BUFFER_SIZE && buffer[input_len-1] != '\0')
      { // пропускать всё до конца строки
        input_len = str_lenght(fgets(buffer, DST_BUFFER_SIZE + 1, input_stream));
        if (buffer[input_len - 1] == '\n')    // отрезаем '\n'
            buffer[input_len - 1] =  '\0';
      }
      return CALC_ERR_INPUT;
    }                      
    else
    {
      result_str = new_str;                  //  результат возможно уже в другом месте

      // первые ячейки уже заполнены, сместиться на длину имеющейся строки 
      char* res_pointer = result_str + str_len;
      
      char* in_pointer = buffer;             // добавляем очередную порцию из buffer
      do { *res_pointer = *in_pointer++;  }  // копируем пока не '\0' в конце buffer
      while (*res_pointer++);

      str_len += input_len;  // новая длина строки
      // использован не весь входной буфер, или обрезан \n => ввод закончен
      if (input_len < DST_BUFFER_SIZE || buffer[input_len-1] == '\0')
        break;
    }
  }
  *str = result_str;
  return CALC_OK;
}


// ---------------------------------------------------------------------------
// печатает строку с ошибкой, 2я редакция - через массив 
void print_error(FILE* output_stream, char* input_line, int error_code)
{
#ifdef MESSAGE_EN    
    char* message_text = default_message.text_en;
#else                
    char* message_text = default_message.text_ru;
#endif // MESSAGE_EN
  
  // найдём текст сообщения
  for (int i = 0; i < result_message_count; ++i)
  {
    if (error_code == result_types[i].type)
    {
#ifdef MESSAGE_EN    
      message_text = result_types[i].text_en;
#else                
      message_text = result_types[i].text_ru;
#endif // MESSAGE_EN
      break;
    }
  }
  fprintf(output_stream, "%s == ERROR: %s\n", input_line, message_text);
}

// ---------------------------------------------------------------------------
// печатает строку по условиям задачи, с учётом кода ошибки
void print_line(FILE* output_stream, char* line, int error, double result)
{
  switch (error)
  {
  case CALC_ERR_ARGS:         // ошибка в параметрах запуска программы
        fprintf(output_stream, "ERROR: bad command line. "
                               " Use: expression_calc.exe inpit_file_name\n");
        break;

  case CALC_ERR_OPEN_FILE:    // ошибка открытия входного файла
        fprintf(output_stream, "ERROR: can't open input file [%s]\n", line);
        break;

  case CALC_OK:          // это корректное выражение
        fprintf(output_stream, "%s == %g\n", line, result);
        break;

  case CALC_LINE_COMMENT:     // это комментарий
  case CALC_LINE_EMPTY:       // это строка пустая (только \n)
  case CALC_LINE_SPACES:      // это строка без значащих символов
        fprintf(output_stream, "%s\n", line);
        break;

  case CALC_ERR_INPUT:        // ошибка, возникшая во время ввода строки 
#ifdef MESSAGE_EN
        fprintf(output_stream, "ERROR: Input. Not enought memory");
#else
        fprintf(output_stream, "ERROR: Ввод. Не хватает памяти ввести строку");
#endif // MESSAGE_EN

  default:                    // всё остальное считаем ошибкой строки
        print_error(output_stream, line, error);
        break;
  }
}
