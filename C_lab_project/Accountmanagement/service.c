#include"card_service.h"
#include "service.h"
#include<stdlib.h>
#include<string.h>

extern bill* head_b;
extern bill* pre_b;
extern int bill_num;

char my[30] = "";

// 消费函数
// 功能：利用时间长短进行计费
double charge(double tp) {
	double fee = 0;
	if (tp < 100)fee = tp;
	else if (tp < 1000)fee = (tp - 100) * 0.9 + 100;
	else if (tp < 10000)fee = (tp - 1000) * 0.8 + 900 * 0.9 + 100;
	else fee = tp * 0.7;
	return fee;
}

// 充值函数
// 功能：充值
void recharge_card() {
	rg_wl(-2, "充值", 1);
	func(recharge_card);
}

// 退费函数
// 功能：退费
void withdrawal_card() {
	rg_wl(0, "退费", -1);
	func(withdrawal_card);
}

// 中间函数  --  充值和退费的重复部分
// 功能： 输入账号密码以及金额，再进行充值或退费处理
void rg_wl(int status, char* output, double fh) {
	card* temp = is_card_status(status);
	if (temp != NULL) {
		printf("当前账号余额为：%lf\n", temp->balance_db);
		printf("请输入%s金额：",output);
		scanf("%s", my);
		scanf("%*[^\n]"); scanf("%*c");
		double money = change(my);
		if (money <= 0)printf("注意：%s金额格式有误\n",output);
		else {
			bill* card_b = (bill*)calloc(1, sizeof(bill));
			card_b->id_code = temp->id_code*100+temp->count;
			t_st* my_t = get_nowtime(card_b->begin_time);
			card_b->begin_t = my_t->t;
			
			card_b->consume = money * fee_rate;
			strcpy(card_b->account, temp->account);
			
			if (head_b == NULL) {		// 头指针为空，说明 card 链表 为空
				head_b = card_b;
				pre_b = head_b;
			}
			else {
				pre_b->next = card_b;	// 前  ->  后
				card_b->front = pre_b;	// 前  <-  后
				pre_b = card_b;
			}
			bill_num++;

			temp->count++;
			temp->balance_used += card_b->consume;
			//  充值 与 退费 的 先后 顺序 问题
			if (fh == 1)money -= card_b->consume;	//  充 的 少
			temp->balance_db += money*fh;
			if (fh == -1)money -= card_b->consume;  //  得 得 少
			
			my_t= get_nowtime(card_b->end_time);
			card_b->end_t = my_t->t;
			card_b->y = my_t->tm->tm_year + 1900;
			card_b->m = my_t->tm->tm_mon + 1;
			card_b->d = my_t->tm->tm_mday;

			strcpy(temp->lastuse_time, card_b->end_time);


			if (temp->balance_db <= 0)printf("注意：当前余额不足"), temp->status = 2;
			else { printf("%s成功\n",output); if (temp->status == 2)temp->status = 0; }
			printf("实际%s金额为：%lf ，手续费为： %lf ，账号余额为：%lf\n",output,money ,card_b->consume ,temp->balance_db);
		}
	}
}