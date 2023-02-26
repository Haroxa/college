#include"menu.h"
#include "tool.h"
#include "billing_service.h"

// 主菜单打印函数
// 功能：打印主菜单
int output_menu() {
	printf("欢迎使用计费管理系统\n\n");
	printf("%s%s%s\n", f, menu[9], f);
	return printf_op(menu, 9);
}

char ask_card_m[30][30] = {
	"返回",
	"查询所有",
	"账号查询",
};
// 查询卡菜单
// 功能：包含  总查询  单个查询  返回
void ask_card_menu() {
	if (is_empty("查询"))return;
	int op = printf_op(ask_card_m, 3);
	if (op <0 || op > 2)printf("注意：输入其它结果均默认为0"), op = 0;
	switch (op) {
	case 1:show_allcard(); break;
	case 2:ask_card(); break;
	default:printf("即将返回\n"); break;
	}
}

char add_card_m[30][30] = {
	"返回",
	"本地加载",
	"创建新卡"
};
// 添加卡菜单
// 功能：包含 文件导入  单个添加  返回
void add_card_menu() {
	int op = printf_op(add_card_m, 3);
	if (op < 0 || op > 2)printf("注意：输入其它结果均默认为0\n"), op = 0;
	switch (op) {
	case 1:upload(); break;
	case 2:add_card(); break;
	default:printf("即将返回\n"); break;
	}
}

// 中间函数
// 功能：循环打印菜单数组 ， 进行 选择
inline int printf_op(char pf[][30], int max) {
	int i = 0, tp;
	for (i = 0; i < max; i++) {
		tp = (i == max-1) ? 0 : i + 1;
		printf("%d.%s\n", tp, pf[tp]);
	}
	printf("%s--------%s\n", f, f);
	printf("请输入你的选择：");
	return get_op();
}


char ak_as_m[30][30] = {
	"返回",
	"所有账单",
	"统计业绩"
};
// 查询添加函数
// 功能：包含  所有账单 统计业绩 返回
void ask_analyse_menu() {
	int op = printf_op(ak_as_m, 3);
	if (op < 0 || op > 2)printf("注意：输入其它结果均默认为0\n"), op = 0;
	switch (op) {
	case 1:show_allbill(); break;
	case 2:analyse_bill(); break;
	default:printf("即将返回\n"); break;
	}
}


char name[100] = "";	// 若为局部变量，则会被清理

// 中间函数
// 功能：读取文件名
void s_name() {
	printf("请输入文件名：");
	scanf("%s", name);
	scanf("%*[^\n]"); scanf("%*c");
}

// 上传函数
// 功能：使 文件 账单 同步上传
void upload() {
	s_name();
	upload_card(name);
	upload_bill(name);
	func(upload);
}
// 保存函数
// 功能：使 文件 账单 同步保存
void save() {
	s_name();
	save_card(name);
	save_bill(name);
}