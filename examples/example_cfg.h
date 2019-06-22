#pragma once

struct Config{
  int var_int;
  float var_float;
  char var_string [32+1];
  int update_time_ms;
};

void config_set_defauls(struct Config * cfg);
void display_config(const char *name, struct Config * cfg);
void config_read_line(struct Config * cfg,const char * line);
void config_read_file(struct Config * cfg,const char * filename );

void test_config_read_line();
