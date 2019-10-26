#include "calc_in_out.h"
#include "calc_process.h"    // for error codes

// ---------------------------------------------------------------------------
// 1 - ��������� ��������� ������ �������� ��� ������ ������
// 0 - ���� (�������� ������ 1 ��� �������� - ��� ����� � �������)
int is_command_line_wrong(int arg_count, char* arg_values[])
{ // ������ ���������� ��������� ������
  // for (int i = 0; i < arg_count; i++) printf("%d - %s\n", i, arg_values[i]);
  
  // ��������������� �� ��������� � ���������, 1� �������� - ��� ���������
  return (arg_count > 2);
}

// ---------------------------------------------------------------------------
// return - 0 == OK    1 == ������ �������� �������� �����
// input_file - ���� ������ ���� � ���������� ������, �� �� ��������� �� ����
// ����� input_file = stdin  - ���� �� ������, ��� ���� ������������� (���� ������� windows)
int detect_input_stream(int arg_count, char* arg_values[], FILE** input_file)
{
  if (arg_count == 1) {             // ������� ���� �� �����
    *input_file = stdin;
    return 0;                       // OK
  }
  fopen_s(input_file, arg_values[1], "r");
  return (NULL == *input_file);     // 0 - ������ �������, 1 - ��� (== NULL)
}


// ����� ������ �� '\0'
unsigned int STR_Lenght(char const* str) {  
  int len = 0;
  if (NULL != str)          // ��������, ��� ��������� ���������
    while (*str++) len++;
  return len;
}


// ---------------------------------------------------------------------------
// ������ ������ ������������ �����, �������������� �������� ������
// � *str ���������� ��������� �� ������, return = ����� ������
// \n � ����� ����������, �� ��������� � ����� (����� == 0 - ����� ������ �����)
unsigned int read_input_line(FILE* input_stream, char** str)
{

  char* result_str = NULL;  // ��� ��������� �� �������� ������, ��� ����������� ����
  unsigned int str_len = 0; // ����������� ����� ������, � ����� - ����������
  char buffer[DST_BUFFER_SIZE + 1] = { 0 };     // ��� ������ �����

  while (1)  // ��������� ������ �������� ������� DST_BUFFER_SIZE
  {
    // fgets ������ �� 1 ������ ������, ��� ��� � ����� ������ ��������� '\0'
    unsigned int input_len = STR_Lenght(fgets(buffer, DST_BUFFER_SIZE + 1, input_stream));

#ifdef DEBUG_IO    
    printf("\n��������� %u �������� ", input_len);
#endif

    if (buffer[input_len - 1] == '\n')
    {
      buffer[input_len - 1] = '\0';  // �������� '\n'
#ifdef DEBUG_IO
      printf(" {CR ������ [%u], �����} ", input_len);
#endif
    }

#ifdef DEBUG_IO
    printf("\"%s\"\n", buffer);
#endif
    // ������ ����� ����� ������
    char* new_str = (char*)realloc(result_str, str_len + input_len + 1);

    if (NULL == new_str)  // ��������� ������ �� �������, ���������� ��� ����
    {
#ifdef DEBUG_IO
      printf("No more memory\n");
#endif
      break;
    }
    else
    {
      result_str = new_str;                   //  ��������� �������� ��� � ������ �����
      // ������ ������ ��� ���������, ���������� �� ����� ��������� ������ 
      char* res_pointer = result_str + str_len;
      char* in_pointer = buffer;                  // ��������� ��������� ������ �� buffer
      while (*res_pointer++ = *in_pointer++) {};  // �������� ���� �� '\0' � ����� buffer

      str_len += input_len;  // ����� ����� ������
#ifdef DEBUG_IO
      printf("���� ������� %u ��������, \"%s\"\n", str_len, result_str);
#endif
      // ����������� �� ���� ������� ����� => ���� ��������
      if (input_len < DST_BUFFER_SIZE)
        break;
    }
  }
  *str = result_str;
  return str_len;
}

// �������� ������ ���������� ��������� == ���������
void print_expression(FILE* output_stream, char* input_line, double result)
{
  fprintf(output_stream, "<OK>%s == %g\n", input_line, result);
}

// �������� ������ ����������� 
void print_comment(FILE* output_stream, char* input_line)
{
  fprintf(output_stream, "<comment>%s\n", input_line);
}

// �������� ������ ��� �������� �������� 
void print_spaces(FILE* output_stream, char* input_line)
{
  fprintf(output_stream, "<spaces>%s\n", input_line);
}

// �������� ������ ������ (� ������ ������ \n)
void print_empty(FILE* output_stream, char* input_line)
{
  fprintf(output_stream, "<empty>\n");
}

// �������� ������ � �������
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