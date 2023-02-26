#include"card_service.h"
#include<stdio.h>
#include<stdlib.h>
#include "menu.h"

extern card* head;
extern card* pre;
extern int card_num;

// 保存账单
// 功能：将账单保存到 指定文件中
void save_card(char name[]) {
	if (head == NULL) { printf("\n当前 卡 链表为空，无法保存\n"); return; }

	char path[100] = "card//";
	int i = 0;
	while (name[i] != '\0')path[6 + i] = name[i], i++;
	//printf("%s\n\n", path);

	FILE* fp = fopen(path, "w");
	if (fp == NULL) {printf("error：文件打开出错\n"); return;}

	card* temp = head;
	while ( temp != NULL) {
		fprintf(fp, "#%lld %-9lld %-9lld %-20s  %-20s %-20s %-20s %-20lf %-20lf %lld\n"
			, temp->id_code, temp->status, temp->count 
			, temp->account, temp->password, temp->created_time, temp->lastuse_time
			, temp->balance_db, temp->balance_used,temp->use_c
			); // 前 后 要 对 应
		temp = temp->next;
	}
	fclose(fp);
	printf("操作成功,保存卡数为：%d\n", card_num);
}

// 加载账单
// 功能：从 指定文件中加载账单
void upload_card(char name[]) {
	
	card* temp;
	
	char path[100] = "card//", clear[1000], ch;
	int i = 0;
	while (name[i] != '\0')path[6 + i] = name[i], i++;
	
	FILE* fp = fopen(path, "r");
	if (fp == NULL) {printf("error：卡文件打开出错\n"); return;}
	int tmp ,file_num=0,added_num=0;
	while (1) {
		temp = (card*)calloc(1, sizeof(card));
		tmp = 0;
		ch = fgetc(fp);
		//  以 # 开头的才为正确格式
		if(ch=='#') {
			tmp = fscanf(fp, "%lld %lld %lld %s %s %s %s %lf %lf %lld"
				, &temp->id_code ,&temp->status ,&temp->count
				, temp->account, temp->password, temp->created_time,temp->lastuse_time
				, &temp->balance_db, &temp->balance_used , &temp->use_c);
		}
		fgets(clear, 1000, fp);		//  清空 该行 数据，使得文件指针 往后 移动
		if (feof(fp))break;		//  到达 文件尾 ，则 跳出 循环
		else if (tmp!=10)continue;		//  若 读入正确数 不为 9 ，则 数据 无效
		file_num++;
		card* m = is_account(temp->account);
		if (m != NULL)continue;		// 已存在，不添加
		card_num++;
		added_num++;
		if (head == NULL) {		// 头指针为空，说明 card 链表 为空
			head = temp;
			pre = head;
		}
		else {
			pre->next = temp;	// 前  ->  后
			temp->front = pre;	// 前  <-  后
			pre = temp;
		}
	}
	printf("此文件中存在有效账号 %d 个，实际增加数为 %d 个\n", file_num, added_num);
	printf("操作成功,现有卡数为：%d \n", card_num);
}