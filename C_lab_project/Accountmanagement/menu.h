#ifndef menu_h
#define menu_h

// 使用 static 来避免重复定义
static char menu[30][30] = {
		"退    出",
		"添 加 卡",
		"查 询 卡",
		"注 销 卡",
		"上    机",
		"下    机",
		"充    值",
		"退    费",
		"查询统计",
		"菜    单"
};

static char f[20] = "------------";
// 主菜单打印函数
int output_menu();
// 查询卡菜单
void add_card_menu();
// 添加卡菜单
void ask_card_menu();
// 查询添加函数
void ask_analyse_menu();
// 中间函数
inline int printf_op(char* pf[], int max);
// 中间函数
void s_name();
// 上传函数
void upload();
// 保存函数
void save();

#endif // !menu_h

