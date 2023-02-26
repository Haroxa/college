#ifndef service_h

#define service_h

// 消费函数
double charge(double tp);
// 充值函数
void recharge_card();
// 退费函数
void withdrawal_card();
// 中间函数
void rg_wl(int status, char* output, double fh);

#endif