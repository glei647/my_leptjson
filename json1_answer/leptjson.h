#pragma once
#include <iostream>
#include <string>
using namespace std;

//typedef enum { LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY } lept_type;

enum lept_type { LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY };

string this_type(int num);

typedef struct {
	lept_type type;
} lept_value;

enum {
	LEPT_PARSE_OK = 0,
	LEPT_PARSE_EMPTY_VALUE,   //=1,һ�� JSON ֻ���пհ�
	LEPT_PARSE_INVALID_VALUE,   //=2,���� null, false, true,����������ֵ
	LEPT_PARSE_ROOT_NOT_SINGULAR   //=3,һ��ֵ֮���ڿհ�֮���������ַ�
};

int lept_parse(lept_value* v, const char* json);

lept_type lept_get_type(const lept_value* v);  //������һ������ֵΪlept_type�ĺ�������ȡ������


