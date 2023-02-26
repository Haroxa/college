#ifndef tool_h

#define tool_h
#include<time.h>
#include "model.h"

// 获取时间函数
t_st* get_nowtime(char* tp);
// 选择函数
int get_op();
// 循环操作函数
void func(void (*f)());


#endif