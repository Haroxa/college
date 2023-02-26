#include "tool.h"
#include<stdio.h>
#include<windows.h>

t_st my_t;


// 获取时间函数
// 功能：获取当前的系统时间，格式如：2023/02/23_19:21:40
t_st* get_nowtime(char * tp) {
	Sleep(1000);	// 停顿1000毫秒
	time(&my_t.t);		//  返回 1970年1月1日至今所经历的时间（以秒为单位）
	//printf("now:  %lld  m: %lld\n", now , m);
	my_t.tm = localtime(&my_t.t);	// 匹配 本地 时间格式
	//printf("%d %d %d %d\n", time_now->tm_year, time_now->tm_mon, time_now->tm_hour, time_now->tm_min);
	//m = mktime(time_now);		
	//printf("mktime:  %lld\n", m);
	//printf("asctime:  %s\n", asctime(time_now));  // 按 asc 形式 输出
	strftime(tp, 30, "%Y/%m/%d_%X", my_t.tm);//按自定义形式输出
	//printf("strftime: %s\n", tp);	
	return &my_t;
}

// 选择函数
// 功能：输入选择，清空缓冲区，防止误操作
int get_op() {
	int op=-1;
	scanf("%d",&op);
	scanf("%*[^\n]"); scanf("%*c");
	printf("你的实际选择为：%d\n", op);
	return op;
}

// 循环操作函数
// 功能：当操作结束后，利用此函数来决定是否再次进行
void func(void (*f)()) {
	int op = 0;
	printf("是否继续此操作（1-是 0-否）：");
	op = get_op();
	if (op != 0 && op != 1)printf("注意：输入其它结果均默认为0"), op = 0;
	if (op)f();
}