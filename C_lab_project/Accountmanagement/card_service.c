#include "card_service.h"

#include<string.h>
#include<stdio.h>
#include<stdlib.h>

extern bill* head_b;
extern bill* pre_b;
extern int bill_num;


card * head = NULL ,* pre = NULL;
int card_num = 0;


// 添加卡
// 功能：创建双向卡链表 ，对信息进行检查，对账号查重，字符金额转换成数字,获取当前系统时间 根据创建时间得到标识码
void add_card() {
	int op=0;
	card* pnow = (card*)calloc(1,sizeof(card));

	// 创建时的格式判断
	do {
		printf("请创建账号名（5~15位长度，仅包含数字字母）：");
		scanf("%s", pnow->account);
		scanf("%*[^\n]"); scanf("%*c");
		if (!is_correct(pnow->account,5,15))printf("账号格式不对\n");
		else {
			if (is_account(pnow->account) != NULL) {
				printf("账号已存在\n");
				printf("是否返回菜单（1-是 0-否）：");
				op = get_op();
				if (op != 0 && op != 1)printf("注意：输入其它结果均默认为0，不退出"),op=0;
				if (op)return;
			}
			else break;
		}
	} while (1);
	do {
		printf("请创建密码（8~18位长度，仅包含数字字母）：");
		scanf("%s", pnow->password);
		scanf("%*[^\n]"); scanf("%*c");
		if (!is_correct(pnow->password,8,18))printf("密码格式不对\n");
		else break;
	} while (1);
	do {
		printf("请输入开卡金额<RMB>（12位数以内，仅包含数字小数点）：");
		scanf("%s", pnow->balance);
		scanf("%*[^\n]"); scanf("%*c");
		pnow->balance_db = change(pnow->balance);
		if (pnow->balance_db==-1e11)printf("金额格式不对\n");
		else break;
	} while (1);
	if (pnow->balance_db < 0)printf("注意：此卡已欠费\n"),pnow->status = 2;

	printf("是否确认创建（1-是 0-否）：");
	op = get_op();
	if (op != 0 && op != 1)printf("注意：输入其它结果均默认为0,不会创建\n"), op = 0;
	if (!op)return;

	t_st* my_t = get_nowtime(pnow->created_time);
	pnow->id_code=my_t->t - 1677317531;
	strcpy(pnow->lastuse_time,pnow->created_time);
	card_num++;


	if (head == NULL) {		// 头指针为空，说明 card 链表 为空
		head = pnow;
		pre = head; 
	}
	else {		
		pre->next = pnow;	// 前  ->  后
		pnow->front = pre;	// 前  <-  后
		pre = pnow;
	}
	
	//printf("%d %d\n\n", head->account, head);

	printf("操作成功,现有卡数为：%d\n", card_num);
	func(add_card);
}

// 检查函数
// 功能：检查 卡信息 格式 是否正确
inline bool is_correct(char * tp , int min ,int max) {
	bool status = true;
	int i = 0;
	while (tp[i] != '\0') {	 //  字 符 判 断
		if (check(tp[i], '0', '9') || check(tp[i], 'a', 'z') || check(tp[i], 'A', 'Z')) {
			i++;
		}
		else {
			status = false;
			break;
		}
	}
	if (i<min || i>max)status = false;	// 长 度 判 断
	return status;
}

// 转换函数
// 功能：将字符数组转换为数字
inline double change(char* tp) {
	int i = 0 ;
	char bi;
	double t = 0.0 , zs=10.0 , xs=1.0 , flag = 1.0 ;
	while (1) {
		bi = tp[i];
		if (bi == 0)break; // 正常退出
		else if (bi == '-')flag = -1.0;		// 符号
		else if (bi == '.')zs = 1.0, xs = 0.1;	// 小数
		else if (check(bi, '0', '9')) {
			t = t * zs + (bi - 48) * xs;	// 累计转换
			if (xs < 1)xs *= 0.1;		// 小数位后移
		}
		else {		// 异 常 终 止
			flag = 0; break;
		}
		i++;
	}
	if (i > 12)flag = 0;
	if (flag) return t*flag;	// 存储
	return -1e11;
}

char f_space[20] = "           ";

// 显示函数
// 功能：显示所有卡信息
void show_allcard() {
	
	//printf("%s %d\n\n", head->account, head->id_code);
	printf("id         卡   号%s状态      余   额    %s 累计消费   %s 使用次数  上次使用时间%s创建时间\n", f_space, f_space, f_space, f_space);
	card* temp = head;
	while (temp != NULL) {
		
		printf("%-9lld  %-17s %-9lld %-22lf %-22lf %-9lld %-20s   %-20s\n"
		,temp->id_code,temp->account, temp->status, temp->balance_db, temp->balance_used, temp->count, temp->lastuse_time, temp->created_time); // 前 后 要 对 应
		temp = temp->next;
	}
	printf("操作成功,查找卡数为：%d\n", card_num );
}
// 单个查询
// 功能：利用卡号查询相关信息
void ask_card() {
	char account[30];
	int flag = 1;
	printf("请输入要查询卡号（5~15位长度，仅包含数字字母）：");
	scanf("%s", account);
	scanf("%*[^\n]"); scanf("%*c");
	printf("id        卡   号%s状态      余   额    %s 累计消费   %s 使用次数  上次使用时间%s创建时间\n", f_space, f_space, f_space,f_space);
	card * temp = is_account(account);
	if (temp == NULL)printf("\n查无此卡，请正确输入卡号或前往添加\n\n");
	else printf("%-9lld %-17s %-9lld %-22lf %-22lf %-9lld %-20s   %-20s\n"
		,temp->id_code, temp->account,temp->status
		, temp->balance_db,temp->balance_used
		,temp->count, temp->lastuse_time, temp->created_time); // 前 后 要 对 应
	func(ask_card);
}

// 判断 账号是否存在
// 原理：对链表进行遍历，判断是否相等
inline card* is_account(char* account) {
	card * temp = head;
	while (temp != NULL) {
		if (strcmp(account, temp->account) == 0) {
			break;
		}
		temp = temp->next;
	}
	return temp;
}

		
// 注销卡
// 功能：根据卡号删除
void delete_card() {
	if (is_empty("注销"))return;
	int op = 1;
	card* temp = is_card_status(0);
	if(temp!=NULL) {
		printf("查找成功\n");
		printf("当前账号余额为：%lf\n", temp->balance_db);
		printf("是否确认删除（1-是 0-否）：");
		op = get_op();
		if (op != 0 && op != 1)printf("注意：输入其它结果均默认为0,不会删除"), op = 0;
		if (op) {
			double money = temp->balance_db ,fh = -1;
			char output[30] = "退费";

			bill* card_b = (bill*)calloc(1, sizeof(bill));
			card_b->id_code = temp->id_code*100+temp->count;
			card_b->begin_t = get_nowtime(card_b->begin_time);

			card_b->consume = money * 0.034;
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

			temp->balance_db -= money;
			money -= card_b->consume;  //  得 的 少

			card_b->end_t = get_nowtime(card_b->end_time);
			printf("删除成功\n实际%s金额为：%lf ，手续费为： %lf ，账号余额为：%lf\n", output, money, card_b->consume, temp->balance_db);

			card* front = temp->front, * next = temp->next;
			if (front != NULL)front->next = next;
			else head = next;
			if(next  != NULL)next->front = front;
			free(temp);
			temp = NULL;
			card_num--;
			printf("现有卡数为：%d\n", card_num);
		}
	}
	func(delete_card);
}

// 中间函数
// 功能：卡号密码输入查找判断状态，用于 删除 充值 退费
inline card* is_card_status(int status) {
	char account[30], password[30];
	printf("请输入卡号（5~15位长度，仅包含数字字母）：");scanf("%s", account); scanf("%*[^\n]"); scanf("%*c");
	printf("请输入密码核验身份（8~18位长度，仅包含数字字母）：");scanf("%s", password); scanf("%*[^\n]"); scanf("%*c");
	card* temp = is_account(account);
	if (temp == NULL)printf("\n查无此卡，请正确输入卡号或前往添加\n\n");
	else if (strcmp(temp->password, password) != 0)printf("\n密码错误，请正确输入密码\n\n");
	else if (status>-1&&temp->status != status)printf("\n当前卡状态异常，请正确操作：status = %lld\n\n", temp->status);
	else return temp;
	return NULL;
}


// inline 内联函数，调用时会被编译替换，以空间换时间，常用于代码量少，但又会被频繁调用的函数

// 验空函数
// 功能：检验链表是否为空
inline bool is_empty(char * output) {
	bool ans = false;
	if (head == NULL) { printf("\n当前 卡 链表为空，无法%s\n",output); ans=true; }
	return ans;
}

