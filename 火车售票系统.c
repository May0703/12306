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

	printf("***************************��ӭʹ�õ��ӹ�Ʊϵͳ��***************************");
	printf("\n��ϵͳ֧��2020��1��1��00:00:00֮�󱱾����Ϻ��θ����Ĺ�Ʊ����\n");
	printf("\n�����ѡ���Լ����õ�ǰʱ�䣬������1���Զ���ȡϵͳʱ�䣬������2���˳�����������3��������ɺ󣬰��س���������\n");
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
		printf("\n\n�������Ҫ��Ʊ��������1����ǩ��������2����Ʊ��������3���浵��������4���˳�����������5���������󣬰��س���������\n");
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


void buy_tickets(int* nowtime, struct info_train* train, struct list_passenger* users)//��Ʊ
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
		printf("\n�������%dλ�˿͵���������������Ϊ8�����֣�\n", i);
		read_passenger_name(&name[i - 1]);
		printf("\n�������%dλ�˿͵�ID����������Ϊ18�����֣�\n", i);
		read_passenger_ID(&ID[i - 1]);
	}
	printf("\n������������ڣ�ʾ����20200619��\n");
	choose_a_date(date, nowtime);
	printf("\n�����Ǹ��ձ������Ϻ����г�ʱ�̱�\n");
	printf("\n*******************************************�� �� ʱ �� ��*******************************************");
	for (int i = 0; i < 11; i++)
	{
		printf("\n");
		print_train(train + i);
	}
	printf("\n��������Ҫ�������г��ţ�ʾ����G17��\n");
	choose_a_train(nowtime, train, &train_chosen, date,name,ID,users);
	printf("\n�����������վ�ı�ţ�ʾ����1��\n");
	choose_leave_station(nowtime, &leave_station_chosen, train_chosen, date);
	printf("\n�����뵽�ﳵվ�ı�ţ�ʾ����2��\n");
	choose_arrive_station(nowtime, &arrive_station_chosen, leave_station_chosen, train_chosen);

	//��Ʊ����˿���Ϣ
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

	//��Ʊ�����г���Ϣ


	printf("\n********************************* �� Ʊ �� �� *********************************\n");
	printf("�г����Σ�%s", train_chosen->name);
	printf("\t�������ڣ�");
	print_date(new_date(date[0], date[1], date[2]));
	printf("\n����վ��%s ����ʱ�䣺", leave_station_chosen->sta_name);
	print_Time(leave_station_chosen->leave);
	printf("\n����վ��%s ����ʱ�䣺", arrive_station_chosen->sta_name);
	print_Time(arrive_station_chosen->arrive);
	printf("\n��λ��Ϣ��\n");
	for (int i = 0; i < passenger_number; i++)
	{
		printf("������%s  ID��%s\n", name[i], ID[i]);
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
	printf("\n���Ĺ�Ʊ��Ϣ���£�\n");
	print_info_passenger(p);
	printf("\n\n��������Ҫ��ǩ��Ʊ�ı�ţ���ֻ��ѡ��δ�����Ļ����ѷ����ĳ�Ʊ��\n");
	t = choose_a_ticket(nowtime,p,0);
	if (t == NULL) return 0;

	//Ҫ���Ʊ
	printf("\n������������ڣ�ʾ����20200619��\n");
	choose_a_date(date, nowtime);
	printf("\n�����Ǹ��ձ������Ϻ����г�ʱ�̱�\n");
	printf("\n*******************************************�� �� ʱ �� ��*******************************************");
	for (int i = 0; i < 11; i++)
	{
		printf("\n");
		print_train(train + i);
	}
	printf("\n��������Ҫ�������г��ţ�ʾ����G17��\n");
	choose_a_train(nowtime, train, &train_chosen, date,name,ID,users);
	printf("\n�����������վ�ı�ţ�ʾ����1��\n");
	choose_leave_station(nowtime, &leave_station_chosen, train_chosen, date);
	printf("\n�����뵽�ﳵվ�ı�ţ�ʾ����2��\n");
	choose_arrive_station(nowtime, &arrive_station_chosen, leave_station_chosen, train_chosen);

	//��Ʊ
	return_ticket(&(p->tickets), t);
	if (p->tickets.data == NULL)
		init_list_ticket(&(p->tickets), new_ticket(new_date(date[0], date[1], date[2]), train_chosen, leave_station_chosen, arrive_station_chosen,seat));
	else
		add_back_ticket(&(p->tickets), new_ticket(new_date(date[0], date[1], date[2]), train_chosen, leave_station_chosen, arrive_station_chosen,seat));
	
	printf("\n��ǩ�ɹ�������ǩ�ĳ�Ʊ��\n");
	print_ticket2(t);
	printf("\n����ǩ��ĳ�Ʊ��\n");
	printf("��������:%d/%d/%d", date[0],date[1],date[2]);
	printf("\t����:%s", train_chosen->name);
	printf("\t����վ:%s",leave_station_chosen->sta_name);
	printf("\t����ʱ��:");
	print_Time(leave_station_chosen->leave);
	printf("\t����վ:%s", arrive_station_chosen->sta_name);
	printf("\t����ʱ��:");
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
	printf("\n���Ĺ�Ʊ��Ϣ���£�\n");
	print_info_passenger(p);
	printf("\n\n��������Ҫ�˵�Ʊ�ı�ţ���ֻ��ѡ��δ�����ĳ�Ʊ��\n");
	t = choose_a_ticket(nowtime, p, 1);
	if (t == NULL) return;
	return_ticket(&(p->tickets), t);
	printf("\n���ѳɹ��˵����³�Ʊ:\n");
	print_ticket2(t);
	free(t);
}


void save_tickets()
{
}