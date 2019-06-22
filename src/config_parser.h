#pragma once

#include "strchr_adv.h"

struct ConfigLine{
  char * var_name;
  size_t var_name_len;
  char * value;
  size_t value_len;
};

int parse_config_line(const char * line, struct ConfigLine * cfg_line);

int i_max ( int a, int b );
int i_min ( int a, int b );

enum {CFG_LINE_ERROR, CFG_LINE_COMMENT, CFG_LINE_OK};

void test_parse_config_line();
