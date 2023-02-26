#ifndef billing_service_h
#define billing_service_h
#include "card_service.h"

// 上机函数
void use_card();
// 下机函数
void stop_card();
// 查找账单函数
void show_allbill();
// 显示函数
inline bill* is_bill(long long id_code);
// 分析函数
void analyse_bill();

#endif
