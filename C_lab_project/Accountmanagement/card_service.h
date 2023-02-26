#ifndef card_service_h
#define card_service_h

#include<stdbool.h>
#include "tool.h"
#include "global.h"


// 添加卡
void add_card();

// 检查函数
inline bool is_correct(char* tp, int min, int max);

// 转换函数
inline double change(char* tp);

// 判断 账号是否存在
inline card* is_account(char* account);

// 查询卡
void ask_card();
// 显示函数
void show_allcard();

// 注销卡
void delete_card();
// 中间函数
inline card* is_card_status(int status);
// 验空函数
inline bool is_empty(char * output);

#endif