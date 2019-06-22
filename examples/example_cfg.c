#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "strchr_adv.h"
#include "config_parser.h"

#include "example_cfg.h"


void config_set_defauls(struct Config * cfg){
  cfg->var_int = 10;
  cfg->var_float = 0.1;
  {
    const char * tmp = "_example.log";
    strncpy(cfg->var_string, tmp,  i_min((int)sizeof(cfg->var_string),(int)strlen(tmp)));  
    cfg->var_string[strlen(tmp)] = 0;
  }
  cfg->update_time_ms = 5;
}

void display_config(const char *name, struct Config * cfg){
  printf("%s->var_int: %d\n",name, cfg->var_int);
  printf("%s->var_float: %g\n",name, cfg->var_float);
  printf("%s->var_string: \"%s\"\n",name, cfg->var_string);
  printf("%s->update_time_ms: %d\n",name, cfg->update_time_ms);
}

void config_read_line(struct Config * cfg,const char * line){
  struct ConfigLine cl;
  int ret = parse_config_line(line, &cl);

  if(ret == CFG_LINE_ERROR){
    printf("line error: \"%s\"\n", line);      
    return;
  }

  if(ret != CFG_LINE_OK) return;
    
  printf("variable: \"%.*s\"\n", (int)cl.var_name_len , cl.var_name);
  printf("value: \"%.*s\"\n", (int)cl.value_len , cl.value);

  if( strncmp("var_int", cl.var_name, (int)cl.var_name_len) == 0){
    cfg->var_int = atoi(cl.value);
    return;
  } 
  if( strncmp("var_float", cl.var_name, (int)cl.var_name_len) == 0){
    cfg->var_float = atof(cl.value);
    return;
  } 

  if( strncmp("var_string", cl.var_name, (int)cl.var_name_len) == 0){
    strncpy(cfg->var_string, cl.value,  i_min((int)sizeof(cfg->var_string),(int)cl.value_len));
    cfg->var_string[i_min((int)sizeof(cfg->var_string),(int)cl.value_len)] = 0;
    return;
  } 
  if( strncmp("update_time_ms", cl.var_name, (int)cl.var_name_len) == 0){
    cfg->update_time_ms = atoi(cl.value);
    return;
  } 

  printf("no match : \"%.*s\"\n", (int)cl.var_name_len , cl.var_name);

  return;
}


void config_read_file(struct Config * cfg,const char * filename ){

  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(filename, "r");
  if (fp == NULL)
      exit(EXIT_FAILURE);

  while ((read = getline(&line, &len, fp)) != -1) {
    printf("%s", line);
    config_read_line(cfg, line);
  }

  fclose(fp);
  if (line)
    free(line);
}


void test_config_read_line(){

  struct Config cfg; 
  config_set_defauls(&cfg);
  display_config("test", &cfg);

  const char * test_01 = "\t config_variable \t = 123";
  config_read_line(&cfg, test_01);

  const char * test_02 = "var_int = 123";
  config_read_line(&cfg, test_02);
  
  {const char * test_03 = "";
  config_read_line(&cfg, test_03);}

  {const char * test_03 = "=";
  config_read_line(&cfg, test_03);}

  const char * test_03 = "var_int = ";
  config_read_line(&cfg, test_03);

  const char * test_04 = "var_string = ";
  config_read_line(&cfg, test_04);

  const char * test_05 = "var_string = ";
  config_read_line(&cfg, test_05);

}

