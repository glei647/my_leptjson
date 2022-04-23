#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leptjson.h"

static int main_ret = 0;
static int test_pass = 0;
static int test_count = 0;

//这个"\"为续行符，采用宏是为了实时的输出所在的行号，因为这里用了续行符，所以下面一段都在一行
#define EXPECT_EQ_BASE(equality, expect, actual)\
    do {\
		test_count++;\
		if (equality) {\
			test_pass++;\
		}\
		else {\
			cout <<"不匹配行号：" <<  __FILE__ << ": " << __LINE__ << ": expect: " << expect << "; actual: " << actual << endl;\
			main_ret++;\
		}\
	} while(0)


#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE(expect == actual, expect, actual) 

static void test_parse_null() {
	lept_value v;
	v.type = LEPT_FALSE;
	EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, "null"));
	EXPECT_EQ_INT(LEPT_NULL, v.type);
}

static void test_parse_empty_value() {
	lept_value v;
	v.type = LEPT_FALSE;
	EXPECT_EQ_INT(LEPT_PARSE_EMPTY_VALUE, lept_parse(&v, " "));
	EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));

	EXPECT_EQ_INT(LEPT_PARSE_EMPTY_VALUE, lept_parse(&v, ""));
	EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

static void test_parse_invalid_value() {
	lept_value v;
	v.type = LEPT_FALSE;
	EXPECT_EQ_INT(LEPT_PARSE_INVALID_VALUE, lept_parse(&v, "nul"));
	EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));

	v.type = LEPT_FALSE;
	EXPECT_EQ_INT(LEPT_PARSE_INVALID_VALUE, lept_parse(&v, "?"));
	EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

static void test_parse_root_not_singular() {
	lept_value v;
	v.type = LEPT_FALSE;
	EXPECT_EQ_INT(LEPT_PARSE_ROOT_NOT_SINGULAR, lept_parse(&v, "null x"));
	EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

static void test_parse() {
	test_parse_null();
	test_parse_empty_value();
	test_parse_invalid_value();
	test_parse_root_not_singular();
}

int main() {
	test_parse();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
	return main_ret;
}
