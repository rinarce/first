#include "calc_in_out.h"
#include "calc_process.h"    // for error codes

// ---------------------------------------------------------------------------
// 1 - параметры командной строки ошибочны для данной задачи
// 0 - норм (допустим только 1 доп параметр - имя файла с данными)
int is_command_line_wrong(int arg_count, char* arg_values[])
{ // печать параметров командной строки
  // for (int i = 0; i < arg_count; i++) printf("%d - %s\n", i, arg_values[i]);
  
  // перенаправление не передаётся в параметры, 1й парамерт - имя программы
  return (arg_count > 2);
}

// ---------------------------------------------------------------------------
// return - 0 == OK    1 == ошибка открытия входного файла
// input_file - если указан файл в коммандной строке, то он откроется на ввод
// иначе input_file = stdin  - файл не указан, или ввод перенаправлен (этим займётся windows)
int detect_input_stream(int arg_count, char* arg_values[], FILE** input_file)
{
  if (arg_count == 1) {             // входной файл не задан
    *input_file = stdin;
    return 0;                       // OK
  }
  fopen_s(input_file, arg_values[1], "r");
  return (NULL == *input_file);     // 0 - открыт успешно, 1 - нет (== NULL)
}


// длина строки до '\0'
unsigned int STR_Lenght(char const* str) {  
  int len = 0;
  if (NULL != str)          // проверка, что указатель корректен
    while (*str++) len++;
  return len;
}


// ---------------------------------------------------------------------------
// вводит строку произвольной длины, самостоятельно выделяет память
// в *str возвращает указатель на строку, return = длина строки
// \n в конце обрезается, но считается в длине (длина == 0 - конец потока ввода)
unsigned int read_input_line(FILE* input_stream, char** str)
{
  char* result_str = NULL;  // Это указатель на итоговую строку, тут накапливаем ввод
  unsigned int str_len = 0; // Накапливаем длину строки, в конце - возвращаем
  char buffer[DST_BUFFER_SIZE + 1] = { 0 };     // Для порций ввода

  while (1)  // считываем строку порциями размера DST_BUFFER_SIZE
  {
    // fgets читает на 1 символ меньше, так как в конце всегда добавляет '\0'
    unsigned int input_len = STR_Lenght(fgets(buffer, DST_BUFFER_SIZE + 1, input_stream));

    if (buffer[input_len - 1] == '\n')    // отрезаем '\n'
        buffer[input_len - 1] = '\0';  

    // просим новый кусок памяти
    char* new_str = (char*)realloc(result_str, str_len + input_len + 1);

    if (NULL == new_str)  // выделение памяти не удалось, возвращаем что есть
      break;
    else
    {
      result_str = new_str;                   //  результат возможно уже в другом месте

      // первые ячейки уже заполнены, сместиться на длину имеющейся строки 
      char* res_pointer = result_str + str_len;
      
      char* in_pointer = buffer;                  // добавляем очередную порцию из buffer
      while (*res_pointer++ = *in_pointer++) {};  // копируем пока не '\0' в конце buffer

      str_len += input_len;  // новая длина строки

                             // использован не весь входной буфер => ввод закончен
      if (input_len < DST_BUFFER_SIZE)
        break;
    }
  }

  *str = result_str;
  return str_len;
}

// печатает строку правильное выражение == результат
void print_expression(FILE* output_stream, char* input_line, double result)
{
  fprintf(output_stream, "<OK>%s == %g\n", input_line, result);
}

// печатает строку комментарий 
void print_comment(FILE* output_stream, char* input_line)
{
  fprintf(output_stream, "<comment>%s\n", input_line);
}

// печатает строку без значащих символов 
void print_spaces(FILE* output_stream, char* input_line)
{
  fprintf(output_stream, "<spaces>%s\n", input_line);
}

// печатает строку пустую (в строке только \n)
void print_empty(FILE* output_stream, char* input_line)
{
  fprintf(output_stream, "<empty>\n");
}

// печатает строку с ошибкой
void print_error(FILE* output_stream, char* input_line, int error_code)
{
  fprintf(output_stream, "<error>%s == ERROR: ", input_line);
  switch (error_code)
  {
  case CALC_LINE_ERR_MEMORY:
    fprintf(output_stream, "not enough memory\n");
    break;
  case CALC_LINE_ERR_ZERO_DIV:
    fprintf(output_stream, "divide by 0\n");
    break;
  case CALC_LINE_ERR_BRACKETS:
    fprintf(output_stream, "brackets mismatch\n");
    break;
  case CALC_LINE_ERR_OTHER:
    fprintf(output_stream, "other error\n");
    break;
  case CALC_LINE_ERR_X:
    fprintf(output_stream, "jet not defined error !!!!! \n");
    break;
  default:
    fprintf(output_stream, "not recognized error type\n");
    break;
  }
}