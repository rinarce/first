// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

// calc_variables.c
// ��� ������� ��� ������ � ����������� 
// � ����������� ������ ��� �� ��������

#include <stdio.h>
#include <stdlib.h>         // memory

#include "common_defs.h"    // ����� �����������
#include "str_functions.h"  // ��� �����


// ---------------------------------------------------------------------------
// ���������� ���������� - 2 ������� ������ ��� ��������� � ���������� ����������
// ---------------------------------------------------------------------------

// ������� ������
typedef struct List_Node  // ���� ������
{
  double value;           // ��������
  char* var_name;         // ��� ����������
  struct List_Node* next; // ��������� �� ��������� ���� (NULL � ����������)
} List_Node;

// ---------------------------------------------------------------------------
// ��������������� ���������� ���������� 
List_Node pi = { M_PI, "pi", NULL };           // ����� ���������
List_Node  e = { M_E,  "e",  &pi };            // ����� ����� pi
// ..... - ��������� ����, �������� ���� � ������
// ---------------------------------------------------------------------------

typedef struct List_Node* P_List_Node;         // ��������� �� ���� ������

// ������ ���� ��� ������� �������, ��� ���� �����������, ����������
// � ��� ������ �� �����, ������ ������� �� ��������� ����
List_Node     head_local = { 0, NULL, NULL };  // ��� ��������� ����������
List_Node    head_global = { 0, NULL, NULL };  // ��� ���������� ����������
List_Node   head_defined = { 0, NULL, &e   };  // ��� ���������������

P_List_Node   vars_local = &head_local;        // �������� ����� ���������
P_List_Node  vars_global = &head_global;        
P_List_Node vars_defined = &head_defined;


// ������� ���� ������ � ��� ���� �� ���
void list_delete_tail(P_List_Node node)
{ 
  P_List_Node next;
  while (NULL != node)          // ��������� �� ��������
  {
    next = node->next;          // ���������, ���� node ��������
    free(node->var_name);       // ������� ���� ������
    free(node);                 // ��������� ������
    node = next;                // ������� � ����������
  }
}

// �������� ������� ������ - ��������� ���� ��������, ��������� - �������
void list_clear(P_List_Node list)
{
  list_delete_tail(list->next);  // ������� ��� ����� ���������� ����
  free(list->var_name);          // �������� ����� �� �� ������ ������
  list->value = 0;               // ���� ��������, �� �������
  list->next = NULL;  
  list->var_name = NULL;
}

// �������� ���������� � ������, ��� ����� �������� ����� ������ � ������
calc_err list_add(P_List_Node list, char const* var_name, double const value)
{ 
  if (NULL == list) return CALC_ERR_ALGO;  //������� ��� ��������������� ������
  
// ��� ��������� 
// 1 - �� ��������� ������� (�������� ���������������), ��������� � ������ ������
//     ����� ������ ����������� ����� ������ � ��� ������ �� ��������
// 2 - ��� �� �����������, ������� ��� ������ ��� �̨� ���������� ���
//     ����� �������� ��������������� �������� ��������, � ������
//     �������� 2=3 3=2 [####]=4 pi=3 � �.�.

  int name_len = str_lenght(var_name);        
  if (name_len == 0) return CALC_ERR_VARZ;    // ������� ������� ���������� ��� �����

  char* new_str = (char*)malloc(name_len + 1);// ������� ����� ������ ��� �����
  if (NULL == new_str)  return CALC_ERR_MEMORY;

  P_List_Node next_node = (P_List_Node)malloc(sizeof(List_Node));
  if (NULL == next_node)
  {
    free(new_str);  // �� ������� ������� ���� => ������ ��� ���� �� �����
    return CALC_ERR_MEMORY;
  }

  str_copy_fix_len(var_name, new_str, name_len);    // ����������� ��� � ��������� ������
  new_str[name_len]   = '\0';                       // ����� ������

  next_node->var_name = new_str;      // ��� ���������� 
  next_node->value    = value;        // ��������
  next_node->next     = list->next;   // ������������ ����� ������ 
  list->next          = next_node;    // ����� ���� ����� �� �������
  return CALC_OK;                     // ����� �� ���� - ������ ���
}


// ���� � ������ ����������, ���� ����� - �� �������� *value
// return 1 - ��������� �������, 0 - ���
int list_get(P_List_Node list, char const* var_name, double* value)
{
  while (NULL != list) 
  {
    if (str_compare(list->var_name, var_name)) {
      *value = list->value;
      return 1;               // �����
    }
    list = list->next;        // ������� � ����������
  }
  return 0;                   // �� �����
}


// ---------------------------------------------------------------------------
// ��������� 
// ---------------------------------------------------------------------------
// ������ ��������� ���������� var_name
calc_err variable_make(char const* var_name, double const value) {
  return list_add(vars_local, var_name, value);
}

// ������ ���������� ���������� var_name
calc_err variable_make_global(char const* var_name, double const value) {
  return list_add(vars_global, var_name, value);
}

// �������� ���������� var_name -> *value,
// return 0 - �� �������, 1 - ���� �����
int variable_get(char const* var_name, double *value)
{
  int name_len = str_lenght(var_name);
  if (name_len == 0) return 0;    //  �� �������� ��� ���������� (����� ������ �� ������)
  
                // ������� ���� � ���������
  if (list_get(vars_local, var_name, value)) return 1;
                // ��������������� � ���������
  if (list_get(vars_defined, var_name, value)) return 1;
                // ����� � ����������
  return list_get(vars_global, var_name, value);
}

// �������� ��������� (��� ����� ������) ���������� 
void variable_clear_local(void) {
  list_clear(vars_local);    // ������� ��� ����� ������� ����
}

// �������� ���������� (��� ��������� �����) ����������
void variable_clear_global(void) {
   list_clear(vars_global);  // ������� ��� ����� ������� ����
}