#include"head.h"

void buy_tickets(int* nowtime, struct info_train* train, struct list_passenger* users);
void change_tickets(int* nowtime, struct info_train* train, struct list_passenger* users);
void return_tickets(int* nowtime, struct info_train* train, struct list_passenger* users);
void save_tickets();


int main()
{
	int nowtime[6] = { 0,0,0,0,0,0 };
	int  how_to_get_time, which_service;
	struct info_train train[11];
	struct list_passenger users;

	users.data = NULL;
	users.next = NULL;

	printf("***************************欢迎使用电子购票系统！***************************");
	printf("\n本系统支持2020年1月1日00:00:00之后北京到上海段高铁的购票服务。\n");
	printf("\n如果您选择自己设置当前时间，请输入1，自动获取系统时间，请输入2，退出程序，请输入3，输入完成后，按回车键继续：\n");
	how_to_get_time = read_number(3);
	switch (how_to_get_time)
	{
	case 1:  settime(nowtime); break;
	case 2:  gettime(nowtime); break;
	default: return 0;
	}

	read_info_train(train);

	while (1)
	{
		printf("\n\n如果您想要购票，请输入1，改签，请输入2，退票，请输入3，存档，请输入4，退出程序，请输入5，完成输入后，按回车键继续：\n");
		which_service = read_number(5);
		switch (which_service)
		{
		case 1: buy_tickets(nowtime, train, &users); break;
		case 2: change_tickets(nowtime,train,&users); break;
		case 3: return_tickets(nowtime,train,&users); break;
		case 4: save_tickets(); break;
		default: return 0;
		}
	}

	for (int j = 0; j < 11; j++)
	{
		delete_train(train + j);
	}
	delete_list_passenger(&users);

	return 0;
}


void buy_tickets(int* nowtime, struct info_train* train, struct list_passenger* users)//买票
{
	int passenger_number = 0;
	int date[3] = { 0 };
	int seat = 0;
	char name[5][18] = { 0 };
	char ID[5][19] = { 0 };
	struct info_train* train_chosen = NULL;
	struct info_station* leave_station_chosen = NULL, * arrive_station_chosen = NULL;
	int choice;
	read_passenger_number(&passenger_number);
	for (int i = 1; i <= passenger_number; i++)
	{
		printf("\n请输入第%d位乘客的姓名，长度限制为8个汉字：\n", i);
		read_passenger_name(&name[i - 1]);
		printf("\n请输入第%d位乘客的ID，长度限制为18个数字：\n", i);
		read_passenger_ID(&ID[i - 1]);
	}
	printf("\n请输入出发日期，示例：20200619：\n");
	choose_a_date(date, nowtime);
	printf("\n下面是该日北京到上海的列车时刻表：\n");
	printf("\n*******************************************列 车 时 刻 表*******************************************");
	for (int i = 0; i < 11; i++)
	{
		printf("\n");
		print_train(train + i);
	}
	printf("\n请输入您要乘坐的列车号，示例：G17：\n");
	choose_a_train(nowtime, train, &train_chosen, date,name,ID,users);
	printf("\n请输入出发车站的编号，示例：1：\n");
	choose_leave_station(nowtime, &leave_station_chosen, train_chosen, date);
	printf("\n请输入到达车站的编号，示例：2：\n");
	choose_arrive_station(nowtime, &arrive_station_chosen, leave_station_chosen, train_chosen);

	//将票加入乘客信息
	for (int i = 0; i < passenger_number; i++)
	{
		struct info_passenger* p = get_passenger(&name[i], &ID[i], users);
		if (p != NULL)
			if (p->tickets.data == NULL)
				init_list_ticket(&(p->tickets), new_ticket(new_date(date[0], date[1], date[2]), train_chosen, leave_station_chosen, arrive_station_chosen,seat));
			else
				add_back_ticket(&(p->tickets), new_ticket(new_date(date[0], date[1], date[2]), train_chosen, leave_station_chosen, arrive_station_chosen,seat));
		else
			if (users->data == NULL)
				init_list_passenger(users, new_passenger(&name[i], &ID[i], new_ticket(new_date(date[0], date[1], date[2]), train_chosen, leave_station_chosen, arrive_station_chosen,seat)));
			else
				add_back_passenger(users, new_passenger(&name[i], &ID[i], new_ticket(new_date(date[0], date[1], date[2]), train_chosen, leave_station_chosen, arrive_station_chosen,seat)));
	}

	//将票加入列车信息


	printf("\n********************************* 购 票 结 果 *********************************\n");
	printf("列车车次：%s", train_chosen->name);
	printf("\t出发日期：");
	print_date(new_date(date[0], date[1], date[2]));
	printf("\n出发站：%s 出发时间：", leave_station_chosen->sta_name);
	print_Time(leave_station_chosen->leave);
	printf("\n到达站：%s 到达时间：", arrive_station_chosen->sta_name);
	print_Time(arrive_station_chosen->arrive);
	printf("\n座位信息：\n");
	for (int i = 0; i < passenger_number; i++)
	{
		printf("姓名：%s  ID：%s\n", name[i], ID[i]);
	}
}

void change_tickets(int* nowtime, struct info_train* train, struct list_passenger* users)
{
	char name[18] = { 0 };
	char ID[19] = { 0 };
	struct info_passenger* p;
	p = search_passenger(name, ID, users);
	if (p == NULL) return;

	struct info_ticket* t;
	int date[3] = { 0 };
	int seat = 0;
	struct info_train* train_chosen = NULL;
	struct info_station* leave_station_chosen = NULL, * arrive_station_chosen = NULL;
	printf("\n您的购票信息如下：\n");
	print_info_passenger(p);
	printf("\n\n请输入您要改签的票的编号，您只能选择未发车的或当日已发车的车票：\n");
	t = choose_a_ticket(nowtime,p,0);
	if (t == NULL) return 0;

	//要买的票
	printf("\n请输入出发日期，示例：20200619：\n");
	choose_a_date(date, nowtime);
	printf("\n下面是该日北京到上海的列车时刻表：\n");
	printf("\n*******************************************列 车 时 刻 表*******************************************");
	for (int i = 0; i < 11; i++)
	{
		printf("\n");
		print_train(train + i);
	}
	printf("\n请输入您要乘坐的列车号，示例：G17：\n");
	choose_a_train(nowtime, train, &train_chosen, date,name,ID,users);
	printf("\n请输入出发车站的编号，示例：1：\n");
	choose_leave_station(nowtime, &leave_station_chosen, train_chosen, date);
	printf("\n请输入到达车站的编号，示例：2：\n");
	choose_arrive_station(nowtime, &arrive_station_chosen, leave_station_chosen, train_chosen);

	//换票
	return_ticket(&(p->tickets), t);
	if (p->tickets.data == NULL)
		init_list_ticket(&(p->tickets), new_ticket(new_date(date[0], date[1], date[2]), train_chosen, leave_station_chosen, arrive_station_chosen,seat));
	else
		add_back_ticket(&(p->tickets), new_ticket(new_date(date[0], date[1], date[2]), train_chosen, leave_station_chosen, arrive_station_chosen,seat));
	
	printf("\n改签成功！您改签的车票：\n");
	print_ticket2(t);
	printf("\n您改签后的车票：\n");
	printf("出发日期:%d/%d/%d", date[0],date[1],date[2]);
	printf("\t车次:%s", train_chosen->name);
	printf("\t出发站:%s",leave_station_chosen->sta_name);
	printf("\t出发时间:");
	print_Time(leave_station_chosen->leave);
	printf("\t到达站:%s", arrive_station_chosen->sta_name);
	printf("\t到达时间:");
	print_Time(arrive_station_chosen->arrive);
	free(t);
}

void return_tickets(int* nowtime, struct info_train* train, struct list_passenger* users)
{
	char name[18] = { 0 };
	char ID[19] = { 0 };
	struct info_passenger* p;
	p = search_passenger(name, ID, users);
	if (p == NULL) return;

	struct info_ticket* t;
	printf("\n您的购票信息如下：\n");
	print_info_passenger(p);
	printf("\n\n请输入您要退的票的编号，您只能选择未发车的车票：\n");
	t = choose_a_ticket(nowtime, p, 1);
	if (t == NULL) return;
	return_ticket(&(p->tickets), t);
	printf("\n您已成功退掉以下车票:\n");
	print_ticket2(t);
	free(t);
}


void save_tickets()
{
}