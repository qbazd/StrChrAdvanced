
//gcc -g -I../src main.c example_cfg.c ../src/*.c  -o test && ./test
//ddd ./test

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "strchr_adv.h"
#include "config_parser.h"
#include "example_cfg.h"

int main(int argc, char const *argv[])
{

  test_all_strchr_adv();
  test_parse_config_line();

  struct Config cfg; 
  config_set_defauls(&cfg);
  display_config("test", &cfg);

  printf("\n\nRead file:\n\n");
  // readfile
  config_read_file(&cfg, "example.ini");

  display_config("test", &cfg);

  return 0;
}
