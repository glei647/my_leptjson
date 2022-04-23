#include "leptjson.h"
#include <assert.h>  //assert()
#include <stdlib.h>  //NULL

#define EXPECT(c, ch) do {	assert(*c->json == (ch)); c->json++; } while(0)   //*c->json��ʾ ȡc->json��ֵ


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
	default: return "��֪���Ǹ�ɶ";
	}
}


//�����ı���ȥ���ı��Ŀհ�
void lept_parse_whitespace(lept_context* c) {
	const char* p = c->json;
	while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
		p++;
	c->json = p;
}


//���ܺ���,����������������õģ������ж��Ƿ�Ϊ"null"��
//��ʣ�ж��Ƿ�Ϊ"false" "true"�ĺ���
//��ȷ�ͷ���OK������ͷ������ִ����е�һ��(int)

//1.�ж��Ƿ�Ϊnull
int lept_parse_null(lept_context* c, lept_value* v) {
	EXPECT(c, 'n');
	if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
		return LEPT_PARSE_INVALID_VALUE;    //�Ǹ���Ч��ֵ
	c->json += 3;
	v->type = LEPT_NULL;
	return LEPT_PARSE_OK;
}


//�����Ľڵ�v��ʹ������Ĺ��ܺ�������v��type������ͣ�����ֵҲ��OK���������ִ������͵�int
int lept_parse_value(lept_context* c, lept_value* v) {
	switch (*c->json) {
	case 'n':	return lept_parse_null(c, v);
	case '\0':	return LEPT_PARSE_EMPTY_VALUE;
	default:	return LEPT_PARSE_INVALID_VALUE;
	}
}


//����������Ҫ�� ������������βֱ����return������һ������
int lept_parse(lept_value* v, const char* json) {
	lept_context c;
	assert(v != NULL);   //v��Ϊ��
	c.json = json;
	v->type = LEPT_NULL;   //????
	lept_parse_whitespace(&c);
	return lept_parse_value(&c, v);
}


//����ֵΪlept_type,������int
lept_type lept_get_type(const lept_value* v) {       //��Ϊ��������һ��const����һֱ��ʾLNK2019,�޷�ʶ��ı�ʶ����������
	assert(v != NULL);
	return v->type;
}

/*
int main() {
	cout << "���Ǻ���" << endl;
	return 0;
} */