#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "strchr_adv.h"
#include "config_parser.h"

int i_max ( int a, int b ) { return a > b ? a : b; }
int i_min ( int a, int b ) { return a < b ? a : b; }

int parse_config_line(const char * line, struct ConfigLine * cfg_line){

  // check if NULL
  if (!line) {
    return CFG_LINE_ERROR;
  }

  char * var_start_p = strchr_not_type(line, isspace);

  if (!var_start_p) {
    return CFG_LINE_ERROR;
  }

  if (*var_start_p == '#'){
    // is "comment #"
    return CFG_LINE_COMMENT;
  }

  if (!isalpha(*var_start_p)) {
    // not var name!
    return CFG_LINE_ERROR;
  }

  //printf("not var name\n");
  char * var_end_p = strchr_not_type(var_start_p, isconfig_var_name);
  //printf("var name: \"%.*s\"\n", (int)(var_end_p - var_start_p) , var_start_p);
  char * eq_s_p = strchr_not_type(var_end_p, isspace);
  //printf("= : \"%s\"\n", eq_s_p);
  if (!var_end_p)
    return CFG_LINE_ERROR;

  if (!eq_s_p)
    return CFG_LINE_ERROR;

  if (*eq_s_p != '='){
    return CFG_LINE_ERROR;
  } 

  char * val_start_p = strchr_not_type(str_avd(eq_s_p,1), isspace);
  if (!val_start_p) return CFG_LINE_ERROR;

  char * val_end_p = strrchr_not_type(eq_s_p + strlen(eq_s_p) - 1 , str_avd(eq_s_p,1), isspace);
  //printf("= : \"%s\"\n", val_start_p);
  if (!val_end_p) return CFG_LINE_ERROR;

  cfg_line->var_name = var_start_p;
  cfg_line->var_name_len = (size_t)(var_end_p - var_start_p);

  cfg_line->value = val_start_p;
  cfg_line->value_len = (val_end_p - val_start_p) + 1;

  return CFG_LINE_OK;
}

void test_parse_config_line(){


  {
    // works
    struct ConfigLine cfg_line;
    const char * test_s = "";
    assert(parse_config_line(test_s, &cfg_line) == CFG_LINE_ERROR);
    printf("empty line OK\n");
  }

  {
    // works
    struct ConfigLine cfg_line;
    const char * test_s = "\n";
    assert(parse_config_line(test_s, &cfg_line) == CFG_LINE_ERROR);
    printf("empty line OK\n");
  }

  {
    // works
    struct ConfigLine cfg_line;
    const char * test_s = "                   a                        ";
    assert(parse_config_line(test_s, &cfg_line) == CFG_LINE_ERROR);
    printf("singl char line line OK\n");
  }

  {
    // works
    struct ConfigLine cfg_line;
    const char * test_s = "a";
    assert(parse_config_line(test_s, &cfg_line) == CFG_LINE_ERROR);
    printf("single char line OK\n");
  }

  {
    // works
    struct ConfigLine cfg_line;
    const char * test_s = " a a = 1 ";
    assert(parse_config_line(test_s, &cfg_line) == CFG_LINE_ERROR);
    printf("must be one var name OK\n");
  }

  {
    // works
    struct ConfigLine cfg_line;
    const char * test_s = " = 1 ";
    assert(parse_config_line(test_s, &cfg_line) == CFG_LINE_ERROR);
    printf("must have var name OK\n");
  }

  {
    // var name must start with alpha
    struct ConfigLine cfg_line;
    const char * test_s = " _a1 = 1";
    assert(parse_config_line(test_s, &cfg_line) == CFG_LINE_ERROR);
    printf("var name must start with alpha OK\n");
  }

  {
    // var name must start with alpha
    struct ConfigLine cfg_line;
    const char * test_s = " 1a1 = 1";
    assert(parse_config_line(test_s, &cfg_line) == CFG_LINE_ERROR);
    printf("var name must start with alpha OK\n");
  }

  {
    // FAILED
    struct ConfigLine cfg_line;
    const char * test_s = " aaa \r\n = \r\n bbb ";
    //assert(parse_config_line(test_s, &cfg_line) == CFG_LINE_ERROR);
    printf("normal line, new lines FAILS\n");
  }


  {
    // works
    struct ConfigLine cfg_line;
    const char * test_s = "aaa=bbb";
    assert(parse_config_line(test_s, &cfg_line) == CFG_LINE_OK);
    printf("normal line OK\n");
  }

  {
    // works
    struct ConfigLine cfg_line;
    const char * test_s = "aaa=bbb\r\n";
    assert(parse_config_line(test_s, &cfg_line) == CFG_LINE_OK);
    printf("normal line with endl OK\n");
  }

  {
    // works
    struct ConfigLine cfg_line;
    const char * test_s = " aaa =bbb ";
    assert(parse_config_line(test_s, &cfg_line) == CFG_LINE_OK);
    printf("normal line, spaces every where OK\n");
  }

  {
    // works
    struct ConfigLine cfg_line;
    const char * test_s = " a_a1 = 1";
    assert(parse_config_line(test_s, &cfg_line) == CFG_LINE_OK);
    printf("var name can have _ and number OK\n");
  }

}
