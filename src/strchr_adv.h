#pragma once

#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int isconfig_var_name(int c);

// advance string but check end
char * str_avd(const char * pch, int n);

// FORWARD
// get next char of range
char * strchr_range(const char * pch, const char * range);

void test_strchr_range();

// get next char of not range
char * strchr_not_range(const char * pch, const char * range);

void test_strchr_not_range();
// get next char of type
char * strchr_type(const char * pch, int (*test_fun_ptr)(int));

void test_strchr_type();

// get next char of not type
char * strchr_not_type(const char * pch, int (*test_fun_ptr)(int));

void test_strchr_not_type();

// REVERSE 
// get next char of range
char * strrchr_range(const char * pch_end, const char * pch_limit, const char * range);

void test_strrchr_range();

// get next char of range
char * strrchr_not_range(const char * pch_end, const char * pch_limit, const char * range);

void test_strrchr_not_range();

// get rev next char of type
char * strrchr_type(const char * pch_end, const char * pch_limit, int (*test_fun_ptr)(int));

void test_strrchr_type();

// get rev next char of type
char * strrchr_not_type(const char * pch_end, const char * pch_limit, int (*test_fun_ptr)(int));

void test_strrchr_not_type();

void test_all_strchr_adv();