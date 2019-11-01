// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

// calc_variables.c ��� ������� ��� ������ � ����������� � ����������� ������ ��� �� ��������

#include <stdio.h>
#include <stdlib.h> 

#include "calc_variables.h"
#include "common_defs.h"    // ����� �����������
#include "str_functions.h"  // ��� �����


// ---------------------------------------------------------------------------
// ���������� ���������� - 3 ������� ������

typedef struct list_node_t  
{
  double value;             // ��������
  char* varName;            // ��� ����������
  struct list_node_t* next; // ��������� �� ��������� ���� (NULL � ����������)
} list_node_t;

// ---------------------------------------------------------------------------
// ��������������� ���������� ���������� 
list_node_t s_pi = { M_PI, "pi", NULL  };         // ����� ���������
list_node_t  s_e = { M_E,  "e",  &s_pi };         // ����� ����� s_pi
// ..... - ��������� ����, �������� ���� � ������
// ---------------------------------------------------------------------------

typedef struct list_node_t* p_list_node_t;        // ��������� �� ���� ������

// ������ ���� ��� ������� �������, ��� ���� �����������, ����������
// � ��� ������ �� �����, ������ ������� �� ��������� ����
list_node_t     s_headLocal = { 0, NULL, NULL };  // ��� ��������� ����������
list_node_t    s_headGlobal = { 0, NULL, NULL };  // ��� ���������� ����������
list_node_t   s_headDefined = { 0, NULL, &s_e };  // ��� ���������������

p_list_node_t   s_varsLocal = &s_headLocal;       // �������� ����� ���������
p_list_node_t  s_varsGlobal = &s_headGlobal;        
p_list_node_t s_varsDefined = &s_headDefined;

// ������� ���� ������ � ��� ���� �� ���
static void _listDeleteTail (p_list_node_t node)
{ 
  p_list_node_t next;           // ��������� �� ��������
  while (NULL != node) {
    next = node->next;          // ���������, ���� node ��������
    free(node->varName);        // ������� ���� ������
    free(node);                 // ��������� ������
    node = next;                // ������� � ����������
  }
}

// ��������� ���� �������� ������ ��������, ��������� - �������
static void _listClear(p_list_node_t list) {
  _listDeleteTail(list->next);  // ������� ��� ����� ���������� ����
  free(list->varName);          // �������� ����� �� �� ������ ������
  list->value   = 0;            // ���� ��������, �� �������
  list->next    = NULL;  
  list->varName = NULL;
}

// �������� ���������� � ������, ��� ����� �������� ����� ������ � ������
static calc_err_t _listAdd(p_list_node_t list, char const* varName, double const value) { 
  if (NULL == list) 
    return CALC_ERR_ALGO;   //������� ��� ��������������� ������
  
// ��� ��������� 
// 1 - �� ��������� ������� (�������� ���������������), ��������� � ������ ������
//     ����� ������ ����������� ����� ������ � ��� ������ �� ��������
// 2 - ��� �� �����������, ������� ��� ������ ��� �̨� ���������� ���
//     ����� �������� ��������������� �������� ��������, � ������
//     �������� 2=3 3=2 [####]=4 pi=3 � �.�.

  int nameLen = StrLenght(varName);        
  if (nameLen == 0) 
    return CALC_ERR_VARZ;    // ������� ������� ���������� ��� �����

  char* newStr = (char*)malloc(nameLen + 1); // ������� ����� ������ ��� �����
  if (NULL == newStr)  
    return CALC_ERR_MEMORY;

  p_list_node_t nextNode = (p_list_node_t)malloc(sizeof(list_node_t));
  if (NULL == nextNode) {
    free(newStr);           // �� ������� ������� ���� => ������ ��� ���� �� �����
    return CALC_ERR_MEMORY;
  }

  StrCopyFixLen(varName, newStr, nameLen);    // ����������� ��� � ��������� ������
  newStr[nameLen]   = '\0';                   // ����� ������

  nextNode->varName = newStr;      
  nextNode->value   = value;      
  nextNode->next    = list->next;             // ������������ ����� ������ 
  list->next        = nextNode;               // ����� ���� ����� �� �������
  return CALC_OK;
}


// ���� � ������ ����������, ���� ����� - �� �������� *value
// return 1 - ��������� �������, 0 - ���
static int _listGet(p_list_node_t list, char const* varName, double* value) {
  while (NULL != list) {
    if (StrCompare(list->varName, varName)) {
      *value = list->value;
      return 1;               // �����
    }
    list = list->next;        // ������� � ����������
  }
  return 0;                   // �� �����
}


// --  ���������  ------------------------------------------------------------

// ������ ��������� ���������� varName
calc_err_t VariableMake(char const* varName, double const value) {  
  return _listAdd(s_varsLocal, varName, value);  
}

// ������ ���������� ���������� varName
calc_err_t VariableMakeGlobal(char const* varName, double const value){
  return _listAdd(s_varsGlobal, varName, value); 
}

// �������� ���������� varName -> *value, return 0 - �� �������, 1 - ���� �����
int VariableGet(char const* varName, double *value) {
  int nameLen = StrLenght(varName);
  if (nameLen == 0) 
    return 0;   //  �� �������� ��� ���������� (����� ������ �� ������)
                
  if (_listGet(s_varsLocal, varName, value))      // ������� ���� � ���������
    return 1;
  if (_listGet(s_varsDefined, varName, value))    // ����� � ���������������
    return 1;
  return _listGet(s_varsGlobal, varName, value);  // � ����� � ����������
}

// �������� ��������� (��� ����� ������) ���������� 
void VariableClearLocal(void) {
  _listClear(s_varsLocal);   
}

// �������� ���������� (��� ��������� �����) ����������
void VariableClearGlobal(void) {
  _listClear(s_varsGlobal);  
}