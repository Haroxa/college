#include"billing_service.h"
#include<stdio.h>
#include "menu.h"
#include<stdlib.h>

extern bill* head_b;
extern bill* pre_b;
extern int bill_num;

// 保存账单函数
// 功能：保存账单的数据到 需求文件 中
void save_bill(char name[]) {
	if (head_b == NULL) { printf("\n当前 账单 链表为空，无法保存\n"); return; }

	char path[100] = "bill//";
	int i = 0;
	while (name[i] != '\0')path[6 + i] = name[i], i++;
	//printf("%s\n\n", path);

	FILE* fp = fopen(path, "w");
	if (fp == NULL) { printf("error：账单文件打开出错\n"); return; }

	bill* temp = head_b;
	while (temp != NULL) {
		fprintf(fp, "#%lld %-9lld %-9lld %-20s  %-20s %-20s %-20lf %d-%d-%d\n"
			, temp->id_code, temp->begin_t, temp->end_t
			, temp->account, temp->begin_time, temp->end_time
			, temp->consume, temp->y, temp->m, temp->d
		); // 前 后 要 对 应
		temp = temp->next;
	}
	fclose(fp);
	printf("操作成功,保存账单数为：%d\n", bill_num);
}

// 加载账单函数
// 功能：从指定文件中加载 合适 非重复 账单
void upload_bill(char name[]) {

	bill* temp;
	char path[100] = "bill//", clear[5000] , ch;
	int i = 0;
	while (name[i] != '\0')path[6+i] = name[i],i++;

	FILE* fp = fopen(path, "r");
	if (fp == NULL) { printf("error：账单文件打开出错\n"); return; }
	int tmp, file_num = 0, added_num = 0;
	while (1) {
		temp = (bill*)calloc(1, sizeof(bill));
		tmp = 0;
		ch = fgetc(fp);
		//  以 # 开头的才为正确格式
		if(ch=='#') {
			tmp = fscanf(fp, "%lld %lld %lld %s  %s %s %lf %d-%d-%d"
				, &temp->id_code, &temp->begin_t, &temp->end_t
				, temp->account, temp->begin_time, temp->end_time
				, &temp->consume, &temp->y, &temp->m, &temp->d
			); // 前 后 要 对 应
		}
		fgets(clear, 5000, fp);		//  清空 该行 数据，使得文件指针 往后 移动
		if (feof(fp))break;		//  到达 文件尾 ，则 跳出 循环
		else if (tmp != 10)continue;		//  若 读入正确数 不为 9 ，则 数据 无效
		file_num++;
		bill* m = is_bill(temp->id_code);
		if (m != NULL)continue;	// 存在，不添加
		bill_num++;

		added_num++;
		if (head_b == NULL) {		// 头指针为空，说明 bill 链表 为空
			head_b = temp;
			pre_b = head_b;
		}
		else {
			pre_b->next = temp;	// 前  ->  后
			temp->front = pre_b;	// 前  <-  后
			pre_b = temp;
		}

	}
	printf("此文件中存在有效账单 %d 个，实际增加数为 %d 个\n", file_num, added_num);
	printf("操作成功,现有账单数为：%d \n", bill_num);
}