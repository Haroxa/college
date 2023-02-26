#ifndef model_h

#define model_h
#include<time.h>

// 卡 的 结构体
typedef struct CARD {
	long long count,use_c, status ,id_code;	//  使用次数  当前状态  标识码
	//	账号		密码			创建时间	  上次使用时间      余额		
	char account[20], password[30], created_time[30], lastuse_time[30], balance[30];

	double balance_db, balance_used;		// 余额  消费金额
	struct CARD* next, * front;		// 指向 下一张 和 前一张 卡 地址  // 双向链表
} card;

// 账单 的 结构体
typedef struct BILL {
	long long id_code;	// 卡 的 id_code * 100 + count   标识码
	time_t begin_t, end_t; // 开始 和 结束 时间 以秒为单位
	int y, m, d;  // 年月日
	char account[30],begin_time[30],end_time[30]; // 账号 ，开始 结束 时间
	double consume;  // 消费 金额
	struct bill* next, * front;  //  指向 上一个 和 下一个 账单 地址  // 双向 链表
}bill;

// 时间相关整合的结构体
typedef struct TIME_ST {
	time_t t;		//  时间 秒
	struct tm* tm;  //  时间 结构体
}t_st;

#endif
