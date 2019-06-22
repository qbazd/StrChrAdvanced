#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "strchr_adv.h"

int isconfig_var_name(int c){
  return (isalnum(c) || (char)c == '_');
}

// advance string but check end
char * str_avd(const char * pch, int n){
  if (n < 0) return (char *)NULL; 
  if (!pch) return (char *)NULL;
  while(*pch){
    if(!n)
      return (char *)pch;
    n --;
    pch ++;
  }
  return NULL;
}

// forward
// get next char of range
char * strchr_range(const char * pch, const char * range){
  if (!pch) return (char *)NULL;
  while(*pch){
    if(strchr(range,*pch)!= NULL)
      return (char *)pch;
    pch ++;
  }
  return NULL;
}

void test_strchr_range(){
  printf("TEST:%s()\n",__FUNCTION__);


  {
    // test empty, empty - error
    const char * test_01 = "";
    char * pch = strchr_range(test_01, "");
    assert (pch == NULL);
    printf("Empty, Empty OK\n");
  }

  {
    // test error
    const char * test_01 = "       ";
    char * pch = strchr_range(test_01, "0123456789.");
    assert (pch == NULL);
    printf("Not found OK\n");
  }

  {
    const char * test_01 = "1   a ";
    char * pch = strchr_range(test_01, "1");
    assert (pch == test_01);
    printf("Found first OK\n");
  }

  {
    const char * test_01 = "a 123   a ";
    char * pch = strchr_range(test_01, "132");
    assert (pch == test_01+2);
    printf("Found middle OK\n");
  }

  {
    const char * test_01 = "abcd5";
    char * pch = strchr_range(test_01, "15");
    assert (pch == (test_01 + strlen(test_01)- 1));
    printf("Found last OK\n");
  }

}


// get next char of not range
char * strchr_not_range(const char * pch, const char * range){
  if (!pch) return (char *)NULL;
  while(*pch){
    if(strchr(range,*pch) == NULL)
      return (char *)pch;
    pch ++;
  }
  return NULL;
}

void test_strchr_not_range(){
  printf("TEST:%s()\n",__FUNCTION__);


  {
    // test empty, empty - error
    const char * test_01 = "";
    char * pch = strchr_not_range(test_01, "");
    assert (pch == NULL);
    printf("Empty, Empty OK\n");
  }

  {
    // test error
    const char * test_01 = "0123456789.";
    char * pch = strchr_not_range(test_01, "0123456789.");
    assert (pch == NULL);
    printf("Not found OK\n");
  }

  {
    const char * test_01 = "1   a ";
    char * pch = strchr_not_range(test_01, " ");
    assert (pch == test_01);
    printf("Found first OK\n");
  }

  {
    const char * test_01 = "a 123   a ";
    char * pch = strchr_not_range(test_01, "a ");
    assert (pch == test_01+2);
    printf("Found middle OK\n");
  }

  {
    const char * test_01 = "abcd5";
    char * pch = strchr_not_range(test_01, "abcd");
    assert (pch == (test_01 + strlen(test_01)- 1));
    printf("Found last OK\n");
  }

}


// get next char of type
char * strchr_type(const char * pch, int (*test_fun_ptr)(int)){
  if (!pch) return (char *)NULL;
  while(*pch){
    if(test_fun_ptr(*pch)){
      return (char *)pch;
    }
    pch ++;
  }
  return NULL;
}

void test_strchr_type(){
  printf("TEST:%s()\n",__FUNCTION__);


  {
    // test empty, empty - error
    const char * test_01 = "";
    char * pch = strchr_type(test_01, isspace);
    assert (pch == NULL);
    printf("Empty, Empty OK\n");
  }

  {
    // test error
    const char * test_01 = "______________";
    char * pch = strchr_type(test_01,  isspace);
    assert (pch == NULL);
    printf("Not found OK\n");
  }

  {
    const char * test_01 = "   a ";
    char * pch = strchr_type(test_01,  isspace);
    assert (pch == test_01);
    printf("Found first OK\n");
  }

  {
    const char * test_01 = "aa 123   a ";
    char * pch = strchr_type(test_01,  isspace);
    assert (pch == test_01+2);
    printf("Found middle OK\n");
  }

  {
    const char * test_01 = "abcd5 ";
    char * pch = strchr_type(test_01,  isspace);
    assert (pch == (test_01 + strlen(test_01)- 1));
    printf("Found last OK\n");
  }
 
}

// get next char of not type
char * strchr_not_type(const char * pch, int (*test_fun_ptr)(int)){
  if (!pch) return (char *)NULL;
  while(*pch){
    if(!test_fun_ptr(*pch)){
      return (char *)pch;
    }
    pch ++;
  }
  return NULL;
}

void test_strchr_not_type(){
  printf("TEST:%s()\n",__FUNCTION__);


  {
    // test empty, empty - error
    const char * test_01 = "";
    char * pch = strchr_not_type(test_01, isspace);
    assert (pch == NULL);
    printf("Empty, Empty OK\n");
  }

  {
    // test error
    const char * test_01 = "   ";
    char * pch = strchr_not_type(test_01,  isspace);
    assert (pch == NULL);
    printf("Not found OK\n");
  }

  {
    const char * test_01 = "a  a ";
    char * pch = strchr_not_type(test_01,  isspace);
    assert (pch == test_01);
    printf("Found first OK\n");
  }

  {
    const char * test_01 = "       aaa 123   a ";
    char * pch = strchr_not_type(test_01,  isspace);
    assert (pch == test_01+7);
    printf("Found middle OK\n");
  }

  {
    const char * test_01 = "               a";
    char * pch = strchr_not_type(test_01,  isspace);
    assert (pch == (test_01 + strlen(test_01)- 1));
    printf("Found last OK\n");
  }

}

// reverse 
// get next char of range
char * strrchr_range(const char * pch_end, const char * pch_limit, const char * range){
  
  if (!pch_end) return (char *)NULL;
  if (!pch_limit) return (char *)NULL;

  while(pch_end >= pch_limit){
    //printf(">%s<\n",pch_end);
    if(strchr(range,*pch_end)!= NULL)
      return (char *)pch_end;
    pch_end --;
  }

  return NULL;
}

void test_strrchr_range(){
  printf("TEST:%s()\n",__FUNCTION__);

  {
    // test pointers reverse
    const char * test_01 = "aaa";
    char * pch = strrchr_range(test_01, test_01 + strlen(test_01)-1, "");
    assert (pch == NULL);
    printf("pointers reverse OK\n");
  }

  {
    // test empty, empty - error
    const char * test_01 = "";
    char * pch = strrchr_range(test_01 + strlen(test_01)-1, test_01, "");
    assert (pch == NULL);
    printf("Empty, Empty OK\n");
  }

  {
    // test error
    const char * test_01 = "       ";
    char * pch = strrchr_range(test_01 + strlen(test_01)-1, test_01, "0123456789.");
    assert (pch == NULL);
    printf("Not found OK\n");
  }

  {
    const char * test_01 = "1   a ";
    char * pch = strrchr_range(test_01 + strlen(test_01)-1, test_01, "1");
    assert (pch == test_01);
    printf("Fount first OK\n");
  }

  {
    const char * test_01 = "123   a ";
    char * pch = strrchr_range(test_01 + strlen(test_01)-1, test_01, "132");
    assert (pch == test_01+2);
    printf("Fount middle OK\n");
  }

  {
    const char * test_01 = "12345";
    char * pch = strrchr_range(test_01 + strlen(test_01)-1, test_01, "15");
    assert (pch == (test_01 + 4));
    printf("Found last OK\n");
  }

}

// get next char of range
char * strrchr_not_range(const char * pch_end, const char * pch_limit, const char * range){
  
  if (!pch_end) return (char *)NULL;
  if (!pch_limit) return (char *)NULL;

  while(pch_end >= pch_limit){
    //printf(">%s<\n",pch_end);
    if(strchr(range,*pch_end) == NULL)
      return (char *)pch_end;
    pch_end --;
  }

  return NULL;
}

void test_strrchr_not_range(){
  printf("TEST:%s()\n",__FUNCTION__);

  {
    // test pointers reverse
    const char * test_01 = "aaaaa";
    char * pch = strrchr_not_range(test_01, test_01 + strlen(test_01)-1, "");
    assert (pch == NULL);
    printf("pointers reverse OK\n");
  }

  {
    // test empty, empty - error
    const char * test_01 = "";
    char * pch = strrchr_not_range(test_01 + strlen(test_01)-1, test_01, "");
    assert (pch == NULL);
    printf("Empty, Empty OK\n");
  }

  {
    // test error
    const char * test_01 = "       0";
    char * pch = strrchr_not_range(test_01 + strlen(test_01)-1, test_01, " 0\t");
    assert (pch == NULL);
    printf("Not found OK\n");
  }

  {
    const char * test_01 = "1   a ";
    char * pch = strrchr_not_range(test_01 + strlen(test_01)-1, test_01, " a\t");
    assert (pch == test_01);
    printf("Fount first OK\n");
  }

  {
    const char * test_01 = "123   a ";
    char * pch = strrchr_not_range(test_01 + strlen(test_01)-1, test_01, " a\t");
    assert (pch == test_01+2);
    printf("Fount middle OK\n");
  }

  {
    const char * test_01 = "123   a ";
    char * pch = strrchr_not_range(test_01 + strlen(test_01)-1, test_01, "123");
    assert (pch == (test_01 + strlen(test_01)-1));
    printf("Found last OK\n");
  }

}

// get rev next char of type
char * strrchr_type(const char * pch_end, const char * pch_limit, int (*test_fun_ptr)(int)){
  if (!pch_end) return (char *)NULL;
  if (!pch_limit) return (char *)NULL;

  while(pch_end >= pch_limit){
    //printf(">%s<\n",pch_end);
    if(test_fun_ptr(*pch_end)){
      return (char *)pch_end;
    }
    pch_end --;
  }

  return NULL;
}

void test_strrchr_type(){
  printf("TEST:%s()\n",__FUNCTION__);

  {
    // test pointers reverse
    const char * test_01 = "aaa";
    char * pch = strrchr_type(test_01, test_01 + strlen(test_01)-1, isalnum);
    assert (pch == NULL);
    printf("pointers reverse OK\n");
  }


  {
    // test empty - error
    const char * test_01 = "";
    char * pch = strrchr_type(test_01 + strlen(test_01)-1, test_01, isalnum);
    assert (pch == NULL);
    printf("Empty OK\n");
  }

  {
    // test error
    const char * test_01 = "       ";
    char * pch = strrchr_type(test_01 + strlen(test_01)-1, test_01, isalnum);
    assert (pch == NULL);
    printf("Not found OK\n");
  }


  {
    const char * test_01 = "1   _ ";
    char * pch = strrchr_type(test_01 + strlen(test_01)-1, test_01, isalnum);
    assert (pch == test_01);
    printf("Fount first OK\n");
  }


  {
    const char * test_01 = "123   _@#$ _";
    char * pch = strrchr_type(test_01 + strlen(test_01)-1, test_01, isalnum);
    assert (pch == test_01+2);
    printf("Fount middle OK\n");
  }

  {
    const char * test_01 = "12345";
    char * pch = strrchr_type(test_01 + strlen(test_01)-1, test_01, isalnum);
    assert (pch == (test_01 + 4));
    printf("Found last OK\n");
  }

}

// get rev next char of type
char * strrchr_not_type(const char * pch_end, const char * pch_limit, int (*test_fun_ptr)(int)){
  if (!pch_end) return (char *)NULL;
  if (!pch_limit) return (char *)NULL;

  while(pch_end >= pch_limit){
    //printf(">%s<\n",pch_end);
    if(!test_fun_ptr(*pch_end)){
      return (char *)pch_end;
    }
    pch_end --;
  }

  return NULL;
}

void test_strrchr_not_type(){
  printf("TEST:%s()\n",__FUNCTION__);

  {
    // test pointers reverse
    const char * test_01 = "aaa";
    char * pch = strrchr_not_type(test_01, test_01 + strlen(test_01)-1, isalnum);
    assert (pch == NULL);
    printf("pointers reverse OK\n");
  }


  {
    // test empty - error
    const char * test_01 = "";
    char * pch = strrchr_not_type(test_01 + strlen(test_01)-1, test_01, isalnum);
    assert (pch == NULL);
    printf("Empty OK\n");
  }

  {
    // test error
    const char * test_01 = "       ";
    char * pch = strrchr_not_type(test_01 + strlen(test_01)-1, test_01, isspace);
    assert (pch == NULL);
    printf("Not found OK\n");
  }


  {
    const char * test_01 = "1    ";
    char * pch = strrchr_not_type(test_01 + strlen(test_01)-1, test_01, isspace);
    assert (pch == test_01);
    printf("Fount first OK\n");
  }


  {
    const char * test_01 = "123     ";
    char * pch = strrchr_not_type(test_01 + strlen(test_01)-1, test_01, isspace);
    assert (pch == test_01+2);
    printf("Fount middle OK\n");
  }

  {
    const char * test_01 = "12345";
    char * pch = strrchr_not_type(test_01 + strlen(test_01)-1, test_01, isspace);
    assert (pch == (test_01 + 4));
    printf("Found last OK\n");
  }

}

void test_all_strchr_adv(){
  test_strchr_range();
  test_strchr_not_range();
  test_strchr_type();
  test_strchr_not_type();

  test_strrchr_range();
  test_strrchr_not_range();
  test_strrchr_type();
  test_strrchr_not_type();
}
