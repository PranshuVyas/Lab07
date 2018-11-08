#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "doOperator.h"
#include "tokenStack.h"
#include "lexical.h"
#include <stdint.h>

static int op_quit(struct tokenStack *stack);
static int op_print(struct tokenStack *stack);
static int op_dump(struct tokenStack *stack);
static int op_add(struct tokenStack *stack);

static int op_diff(struct tokenStack *stack);
static int op_prod(struct tokenStack *stack);
static int op_div(struct tokenStack *stack);
static int op_great(struct tokenStack *stack);
static int op_less(struct tokenStack *stack);
static int op_geq(struct tokenStack *stack);
static int op_leq(struct tokenStack *stack);
static int op_eq(struct tokenStack *stack);
static int op_mod(struct tokenStack *stack);
static int op_drop(struct tokenStack *stack);

static struct operator_struct {
  char *name;
  int (*fn_ptr)(struct tokenStack *);
} ops[] = {
  {"quit", op_quit},
  {"print", op_print},
  {"dump", op_dump},
  {"+", op_add},
  {"-", op_diff},
  {"*", op_prod},
  {"/", op_div},
  {"gt", op_great},
  {"lt", op_less},
  {"ge", op_geq},
  {"le", op_leq},
  {"eq", op_eq},
  {"mod", op_mod},
  {"drop", op_drop},
  {(char *)NULL, (int(*)(struct tokenStack *)) NULL}
};


/* YOU WRITE THIS */
static int popInt(struct tokenStack *s)
{
 struct lexToken *t = popTokenStack(s);
 int x;
 x = atoi(t->symbol);
 freeToken(t); 
 return (x); 

}

/* YOU WRITE THIS */
static void pushInt(struct tokenStack *s, int v)
{
 struct lexToken *t;
 char ph[200]; 
 int i;
 i = 0;
t = allocToken();
 t->kind = 4;
 sprintf(ph,"%d",v);
 while(ph[i] < sizeof(ph)){ 
 t->symbol[i] = ph[i];
 i++;
 }
 pushTokenStack(s, t);
 
}

int doOperator(struct tokenStack *stack, char *o) 
{
  struct operator_struct *op = ops;
  for(op=ops;op->name != (char *)NULL; op++) {
    if(!strcmp(op->name, o))
      return op->fn_ptr(stack);
  }
  return(-1);
}

/*ARGSUSED*/
static int op_quit(struct tokenStack *stack)
{
  printf("[quit]\n");
  exit(0);
  /*NOTREACHED*/
}

static int op_print(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  printToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_dump(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  dumpToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_add(struct tokenStack *stack)
{
   int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1+v2);
  return(0);
}

static int op_diff(struct tokenStack *stack)
{
   int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1-v2);
  return(0);
}
static int op_prod(struct tokenStack *stack)
{
    int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1*v2);
  return(0); 
}
static int op_div(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1/v2);
  return(0); 
}
static int op_great(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  if(v1>v2) {
  pushInt(stack, 1);
  }
  else {
    pushInt(stack, 0);
  }
  return(0); 
  }
static int op_less(struct tokenStack *stack)
      {
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  if(v1<v2) {
  pushInt(stack, 1);
  }
  else {
    pushInt(stack, 0);
  }
  return(0); 
  }
static int op_geq(struct tokenStack *stack)
  {
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  if(v1>=v2) {
  pushInt(stack, 1);
  }
  else {
    pushInt(stack, 0);
  }
  return(0); 
  }
static int op_leq(struct tokenStack *stack)
  {
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  if(v1<=v2) {
  pushInt(stack, 1);
  }
  else {
    pushInt(stack, 0);
  }
  return(0); 
  }
static int op_eq(struct tokenStack *stack)
  {
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  if(v1==v2) {
  pushInt(stack, 1);
  }
  else {
    pushInt(stack, 0);
  }
  return(0); 
  }
static int op_mod(struct tokenStack *stack)
{
  int v1;
  v1 = popInt(stack);
  pushInt(stack, v1);
  pushInt(stack, v1);
  return(0);
}
static int op_drop(struct tokenStack *stack)
{
 popInt(stack); 
  return(0);
}
