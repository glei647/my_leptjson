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
	LEPT_PARSE_EMPTY_VALUE,   //=1,一个 JSON 只含有空白
	LEPT_PARSE_INVALID_VALUE,   //=2,不是 null, false, true,这三种字面值
	LEPT_PARSE_ROOT_NOT_SINGULAR   //=3,一个值之后，在空白之后还有其他字符
};

int lept_parse(lept_value* v, const char* json);

lept_type lept_get_type(const lept_value* v);  //定义了一个返回值为lept_type的函数，获取其类型


