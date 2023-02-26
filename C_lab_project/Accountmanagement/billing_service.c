#include "billing_service.h"
#include "service.h"
#include<stdio.h>
#include "time.h"
#include<stdlib.h>

extern card* head;
extern char f_space[20];

bill* head_b=NULL, * pre_b=NULL;
int bill_num = 0 ;
time_t b_t, e_t;

// 上机函数
// 功能：改变卡状态，新建 半个账单
void use_card() {

	if (is_empty("上机"))return;
	card* temp = is_card_status(0);
	if (temp == NULL)printf("上机失败\n");
	else {
		temp->status = 1;

		bill* pnow = (bill*)calloc(1, sizeof(bill));
		t_st * my_t = get_nowtime(pnow->begin_time);
		pnow->begin_t = my_t->t;
		strcpy(pnow->end_time, "上机中");

		pnow->id_code = temp->id_code*100+temp->count;
		temp->use_c = temp->count;
		temp->count++;

		strcpy(pnow->account, temp->account);
		
		if (head_b == NULL) {		// 头指针为空，说明 card 链表 为空
			head_b = pnow;
			pre_b = head_b;
		}
		else {
			pre_b->next = pnow;	// 前  ->  后
			pnow->front = pre_b;	// 前  <-  后
			pre_b = pnow;
		}
		bill_num++;
		//printf("%d   %s   %s  %d\n", head_b->id_code, head_b->account, head_b->begin_time, head_b->next);
		//printf("%d   %s   %s  %d\n", pre_b->id_code, pre_b->account, pre_b->begin_time , pre_b->next);
		printf("上机中，可以进行其它操作\n");
	}
	func( use_card );
}


// 下机函数
// 功能：改变卡状态，查找到 对应 半个账单 ，通过 时间长短 来消费
void stop_card() {
	
	if (is_empty("下机"))return;
	card* temp = is_card_status(1);
	if (temp != NULL) {
		bill* temp_b = is_bill(temp->id_code*100+temp->use_c);
		if (temp_b!= NULL) {
			t_st * my_t = get_nowtime(temp_b->end_time);
			temp_b->end_t = my_t->t;
			
			temp_b->y = my_t->tm->tm_year + 1900;
			temp_b->m = my_t->tm->tm_mon + 1;
			temp_b->d = my_t->tm->tm_mday;

			temp_b->consume = charge(difftime(temp_b->end_t, temp_b->begin_t));
			
			strcpy(temp->lastuse_time, temp_b->end_time);
			temp->balance_used += temp_b->consume;
			temp->balance_db -= temp->balance_used;
			
			temp->status = 0;


			if (temp->balance_db < 0)temp->status = 2,printf("账号已欠费，请及时缴费\n");
			printf("下机成功,本次上机共消费 %lf (RMB)\n",temp_b->consume);
		}
		else {
			printf("下机失败，无对应账单记录\n");
		}
	}
	func(stop_card);
}


// 查找账单函数
// 功能：遍历链表，利用 id 查找账单
inline bill* is_bill(long long id_code) {
	bill* temp = head_b;
	while (temp != NULL) {
		if (temp->id_code == id_code)break;
		temp = temp->next;
	}
	return temp;
}

// 显示函数
// 功能：显示所有账单
void show_allbill() {
	if (head_b == NULL){printf("当前账单为空，无法打印\n\n"); return;}
	printf("id         卡   号%s本次消费   %s 开始时间  %s  结束时间\n", f_space, f_space, f_space);
	bill* temp = head_b;
	while (temp != NULL) {
		printf("%-9lld  %-17s %-22lf %-20s   %-20s \n"  /*  %d-%d-%d*/
			, temp->id_code, temp->account, temp->consume, temp->begin_time, temp->end_time
			/*, temp->y, temp->m, temp->d*/); // 前 后 要 对 应
		temp = temp->next;
	}
	printf("操作成功,查找账单数为：%d\n", bill_num);
}

// 分析函数
// 功能：对各个时间段营业额 汇总 输出
void analyse_bill() {
	double bill_m_d[16][32] = { 0 };
	double bill_sum[16] = { 0 };

	bill* temp = head_b;
	while (temp != NULL) {
		bill_m_d[temp->m][temp->d] += temp->consume;
		temp = temp->next;
	}

	int i, j , fg =0;
	printf("2023 年 营业额 如下 ：\n");
	for (i = 1; i <= 12; i++) {
		fg = 0;
		for (j = 1; j <= 31; j++) {
			if (bill_m_d[i][j] != 0) {
				fg = 1;
				printf("%02d 月 %02d 日  营业额  为： %-20lf\n", i, j, bill_m_d[i][j]);
				bill_sum[i] += bill_m_d[i][j];
			}
		}
		if (fg) {
			printf("在 %02d 月 中 总营业额 为：%-20lf\n\n", i, bill_sum[i]);
			bill_sum[13] += bill_sum[i];
		}
	}
	printf("截止至今日 总营业额 为：%-20lf\n", bill_sum[13]);

}