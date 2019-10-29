// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

// calc_variables.c
// ��� ������� ��� ������ � ����������� 
// � ����������� ������ ��� �� ��������

#include <stdio.h>
#include <stdlib.h>         // memory

#include "calc_process.h"   // ��� ������
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

typedef struct List_Node* P_List_Node;    // ��������� �� ���� ������

// ������ ���� ��� ������� �������, ��� ���� �����������, ����������
// � ��� ������ �� �����
List_Node   head_local  = { 0, NULL, NULL };  // ��� ��������� ����������
List_Node   head_global = { 0, NULL, NULL };  // ��� ���������� ����������
P_List_Node vars_local  = &head_local;        // �������� ����� ���������
P_List_Node vars_global = &head_global;       // �������� ����� ���������


// ������� ���� ������ � ��� ���� �� ���
void list_delete_tail(P_List_Node node)
{
  if (NULL == node) return;     // ������� ��� ��������������� ����
  if (NULL != node->next)       // ���������� ���������� � ���������� ����
    list_delete_tail(node->next);
//  printf("{delete <%s>=%g}", node->var_name, node->value);
  free(node->var_name);         // ������� ���� ������
  free(node);                   // ��������� ������
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
// return - ��� ������ 
int list_add(P_List_Node list, char* var_name, double value)
{ 
  if (NULL == list) return CALC_ERR_ALGO;  //������� ��� �������������� ������
  
// ��� ��������� 
// 1 - �� ��������� ������� (���������������), ��������� � ������ ������
//     ����� ������ ����������� ����� ������ � ��� ������ �� ��������
// 2 - ��� �� �����������, ������� ��� ������ ��� ��� ���������� ���
//     ����� �������� ��������������� �������� ��������, � ������
//     �������� 2=3 [###]=8 pi=3 

  int name_len = str_lenght(var_name);       // ������� ����� ������ ��� �����
  char* new_str = (char*)malloc(name_len + 1);
  if (NULL == new_str)  return CALC_ERR_MEMORY;

  P_List_Node next_node = (P_List_Node)malloc(sizeof(List_Node));
  if (NULL == next_node)
  {
    free(new_str);  // �� ������� ������� ���� => ������ ��� ���� �� �����
    return CALC_ERR_MEMORY;
  }

  str_copy_fix_len(var_name, new_str, name_len);    // ����������� ��� � ��������� ������
  new_str[name_len] = '\0';                         // ����� ������

  next_node->var_name = new_str;      // ��� ���������� 
  next_node->value    = value;        // ��������
  next_node->next     = list->next;   // ������������ ����� ������ 

  list->next = next_node;             // ����� ���� ����� �� �������
  return 0;                           // ����� �� ���� - ������ ���
}


// ���� � ������ ����������, ���� ����� - �� �������� *value
// return 1 - ��������� �������, 0 - ���
int list_get(P_List_Node list, char* var_name, double* value)
{
  if (NULL == list) return 0; // ������� ��� ��������������� ���� 

  if (str_compare(list->var_name, var_name)) 
    {                         
      *value = list->value;
      return 1;               // �����
    }
  return list_get(list->next, var_name, value);  // �������� ������ �� ������
}


// ---------------------------------------------------------------------------
// ��������� 
// ---------------------------------------------------------------------------
// ������ ��������� ���������� var_name, return - ��� ������
int variable_make(char* var_name, double value) {
  return list_add(vars_local, var_name, value);
}

// ������ ���������� ���������� var_name, return - ��� ������
int variable_make_global(char* var_name, double value) {
  return list_add(vars_global, var_name, value);
}

// �������� ���������� var_name -> *value,
// return 0 - �� �������, 1 - ���� �����
int variable_get(char* var_name, double *value)
{
  int name_len = str_lenght(var_name);
  if (name_len == 0) return 0;    //  �� �������� ��� ����������
  
  // ������� ���� � ���������
  if(list_get(vars_local, var_name, value)) return 1;
  
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