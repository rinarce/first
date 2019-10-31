// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "common_defs.h"
#include "str_functions.h"

typedef struct result_message_t { 
  calc_err_t type;
  char* textEN;
  char* textRU;
} result_message_t; 

result_message_t  s_resultTypes[] = { 
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

result_message_t s_defaultMessage = 
                 { 0, "Not recognized error type!",   "Таких ошибок не бывает!"     };

int s_resultTypesCount = sizeof(s_resultTypes) / sizeof(result_message_t); // Количество разных сообщений

// ---------------------------------------------------------------------------
// вводит строку произвольной длины, самостоятельно выделяет память
// в *str возвращает указатель на строку, return = код ошибки
// при нехватке памяти - пропуск до конца строки, введённое отбросить
calc_err_t ReadInputLine (FILE* inputStream, char** str)
{
  char* resultStr = NULL;   // Это указатель на итоговую строку, тут накапливаем ввод
  unsigned int strLen = 0;  // Накапливаем длину строки, в конце - возвращаем
  char buffer[DST_BUFFER_SIZE + 1] = { 0 };     // Для порций ввода
  
  while (1) {
    // fgets читает на 1 символ меньше, так как в конце всегда добавляет '\0'
    unsigned int inputLen = StrLenght(fgets(buffer, DST_BUFFER_SIZE + 1, inputStream));
    
    if (0 == inputLen)
      return CALC_LINE_THE_END;           //  закончился поток ввода, 

    if (buffer[inputLen - 1] == '\n')     // отрезаем '\n'
        buffer[inputLen - 1] =  '\0';  

    char* newStr = (char*)realloc(resultStr, strLen + inputLen + 1);

    if (NULL == newStr) {   // выделение памяти не удалось
      // обнуление введёной строки и пропуск данных до конца строки ! п 2.4.7.
      free(resultStr);
      *str = NULL;

      // если использован не весь входной буфер, или обрезан \n => ввод закончен
      while (inputLen == DST_BUFFER_SIZE && buffer[inputLen-1] != '\0') {
        // пропускать всё до конца строки
        inputLen = StrLenght(fgets(buffer, DST_BUFFER_SIZE + 1, inputStream));
        if (buffer[inputLen - 1] == '\n')   // отрезаем '\n'
            buffer[inputLen - 1] =  '\0';
      }
      return CALC_ERR_INPUT;
    }                      
    else {                  // выделение памяти удалось
      resultStr = newStr;                   //  результат возможно уже в другом месте

      // первые ячейки уже заполнены, сместиться на длину имеющейся строки 
      char* resPointer = resultStr + strLen;
      char* inPointer  = buffer;            // добавляем очередную порцию из buffer
      do { *resPointer = *inPointer++;  }   // копируем пока не '\0' в конце buffer
      while (*resPointer++);

      strLen += inputLen;                   // новая длина строки
      // использован не весь входной буфер, или обрезан \n => ввод закончен
      if (inputLen < DST_BUFFER_SIZE || buffer[inputLen-1] == '\0')
        break;
    }
  }
  *str = resultStr;
  return CALC_OK;
}

// ---------------------------------------------------------------------------
// печатает строку с ошибкой
static void _printError(FILE* outputStream, char* line, calc_err_t error) {
  #ifdef MESSAGE_EN    
    char* messageText = s_defaultMessage.textEN;
  #else                
    char* message_text = default_message.text_ru;
  #endif // MESSAGE_EN
  
  for (int typeIndex = 0; typeIndex < s_resultTypesCount; ++typeIndex) { 
    if (error == s_resultTypes[typeIndex].type) {
      #ifdef MESSAGE_EN    
        messageText = s_resultTypes[typeIndex].textEN;
      #else                
        message_text = result_types[typeIndex].text_ru;
      #endif // MESSAGE_EN
      break;
    }
  }
  fprintf(outputStream, "%s == ERROR: %s\n", line, messageText);
}

// ---------------------------------------------------------------------------
// печатает строку по условиям задачи, с учётом кода ошибки
void PrintLine(FILE* outputStream, char* line, calc_err_t error, double result)
{
  switch (error)  {
    case CALC_ERR_ARGS:       // ошибка в параметрах запуска программы
      fprintf(outputStream, "ERROR: bad command line. "
                            " Use: expression_calc.exe inpit_file_name\n");
      break;
    case CALC_ERR_OPEN_FILE:  // ошибка открытия входного файла
      fprintf(outputStream, "ERROR: can't open input file [%s]\n", line);
      break;
    case CALC_OK:             // это корректное выражение
      fprintf(outputStream, "%s == %g\n", line, result);
      break;

    case CALC_LINE_COMMENT:   // это комментарий
    case CALC_LINE_EMPTY:     // это строка пустая (только \n)
    case CALC_LINE_SPACES:    // это строка без значащих символов
      fprintf(outputStream, "%s\n", line);
      break;
    case CALC_ERR_INPUT:      // ошибка, возникшая во время ввода строки 
      #ifdef MESSAGE_EN
        fprintf(outputStream, "ERROR: Input. Not enought memory");
      #else
        fprintf(outputStream, "ERROR: Ввод. Не хватает памяти ввести строку");
      #endif // MESSAGE_EN
    default:                  // всё остальное считаем ошибкой строки
      _printError(outputStream, line, error);
      break;
  }
}
