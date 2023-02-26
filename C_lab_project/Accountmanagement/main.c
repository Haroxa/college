//#define _CRT_SECURE_NO_WARNINGS		//  消除 vs 中 scanf 报错
//要在引入 stdio.h 文件 之前使用
#include<stdio.h>
#include "menu.h"
#include "card_service.h"

int main() {
	// 循环标记   选择
	int flag = 1, op=-1;
	char m[30];
	do { 
		//打印菜单
		op = output_menu();
		if(op<9&&op>=0)printf("%s%s%s\n", f, menu[op], f);
		switch (op) {
			case 1:// 添 加 卡 
				add_card_menu();
				break;
			case 2:// 查 询 卡
				ask_card_menu();
				break;
			case 3:// 注 销 卡
				delete_card();
				break;
			case 4:// 上    机 ---- 使用卡消费
				use_card();
				break;
			case 5:// 下    机 ---- 停止卡消费
				stop_card();
				break;
			case 6:// 充    值
				recharge_card();
				break;
			case 7:// 退    费
				withdrawal_card();
				break;
			case 8:// 查询统计
				ask_analyse_menu();
				break;
			case 0:// 退    出
				flag = 0;
				printf("是否保存当前数据到本地（1-是 0-否）：");
				op = get_op();
				if (op != 0 && op != 1)printf("注意：输入其它结果均默认为1，会保存\n"), op = 1;
				if(op)save();
				printf("\n期待下次使用\n\n");
				break;
			default: 
				printf("\nerror:无此选项\n\n");
				break;
		};
		system("pause");
		system("cls");
	}while(flag);

	return 0;
}
