#include "leptjson.h"
#include <assert.h>  //assert()
#include <stdlib.h>  //NULL

#define EXPECT(c, ch) do {	assert(*c->json == (ch)); c->json++; } while(0)   //*c->json表示 取c->json的值


typedef struct {
	const char* json;
}lept_context;

string this_type(int num) {
	switch (num) {
	case 0:	return "LEPT_NULL";
	case 1:	return "LEPT_FALSE";
	case 2: return "LEPT_TURE";
	case 3: return "LEPT_NUMBER";
	case 4: return "LEPT_STRING";
	case 5: return "LEPT_ARRAY";
	default: return "不知道是个啥";
	}
}


//输入文本，去掉文本的空白
void lept_parse_whitespace(lept_context* c) {
	const char* p = c->json;
	while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
		p++;
	c->json = p;
}


//功能函数,服务下面这个函数用的，这是判断是否为"null"的
//还剩判断是否为"false" "true"的函数
//正确就返回OK，错误就返回三种错误中的一个(int)

//1.判断是否为null
int lept_parse_null(lept_context* c, lept_value* v) {
	EXPECT(c, 'n');
	if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
		return LEPT_PARSE_INVALID_VALUE;    //是个无效的值
	c->json += 3;
	v->type = LEPT_NULL;
	return LEPT_PARSE_OK;
}


//声明的节点v，使用上面的功能函数，给v的type添加类型，返回值也是OK或其他三种错误类型的int
int lept_parse_value(lept_context* c, lept_value* v) {
	switch (*c->json) {
	case 'n':	return lept_parse_null(c, v);
	case '\0':	return LEPT_PARSE_EMPTY_VALUE;
	default:	return LEPT_PARSE_INVALID_VALUE;
	}
}


//这是真正主要的 解析函数，结尾直接用return调用上一个函数
int lept_parse(lept_value* v, const char* json) {
	lept_context c;
	assert(v != NULL);   //v不为空
	c.json = json;
	v->type = LEPT_NULL;   //????
	lept_parse_whitespace(&c);
	return lept_parse_value(&c, v);
}


//返回值为lept_type,而不是int
lept_type lept_get_type(const lept_value* v) {       //因为这里少了一个const所以一直提示LNK2019,无法识别的标识符。。。。
	assert(v != NULL);
	return v->type;
}

/*
int main() {
	cout << "我是憨憨" << endl;
	return 0;
} */