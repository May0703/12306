#include"head.h"

//date

struct date new_date(int year, int month, int day)
{
	struct date t;
	t.year = year;
	t.month = month;
	t.day = day;
	return t;
}
void print_date(struct date t)
{
	printf("%d/%d/%d", t.year, t.month, t.day);
}

int date_cmp(struct date d1, struct date d2)		//一样返回1，不一样返回0
{
	if (d1.day == d2.day && d1.month == d2.month && d1.year == d2.year)
		return 1;
	else
		return 0;
}

//ticket

void map_seat(char* seat_name, int seat)
{
	if (seat <= 45)
	{
		for (int i = 1; i < 10; i++)
		{
			if ((seat + 4) / 5 == i)
			{
				seat_name[0] = '0';
				seat_name[1] = '0' + i;
				break;
			}
		}
	}
	else if (seat > 45 && seat <= 95)
	{
		for (int i = 10; i < 20; i++)
		{
			if ((seat + 4) / 5 == i)
			{
				seat_name[0] = '1';
				seat_name[1] = '0' + (i-10);
				break;
			}
		}
	}
	else
	{
		seat_name[0] = '2';
		seat_name[1] = '0';
	}
	if (seat / 5 == 0)
	{
		seat_name[3] = 'E';
	}
	else
	{
		for (int i = 1; i < 5; i++)
		{
			if (seat % 5 == i)
			{
				seat_name[3] = 'A' + i;
				break;
			}
		}
	}
}

struct info_ticket new_ticket(struct date leave_date, struct info_train* train, struct info_station* leave_station, struct info_station* arrive_station,int seat)
{
	struct info_ticket t;
	t.leave_date = leave_date;
	t.train = train;
	t.leave_station = leave_station;
	t.arrive_station = arrive_station;
	t.seat = seat;
	return t;
}
void init_ticket(struct info_ticket* t, struct date leave_date, struct info_train* train, struct info_station* leave_station, struct info_station* arrive_station,int seat)
{
	t->leave_date = leave_date;
	t->train = train;
	t->leave_station = leave_station;
	t->arrive_station = arrive_station;
	t->seat = seat;
}

void print_ticket(struct info_ticket* a, int no)
{
	char* seat_name[3];
	map_seat(seat_name, a->seat);
	printf("\n编号:%d", no);
	printf("\t出发日期:%d/%d/%d", a->leave_date.year, a->leave_date.month, a->leave_date.day);
	printf("\t车次:%s", a->train->name);
	printf("\t出发站:%s", a->leave_station->sta_name);
	printf("\t出发时间:");
	print_Time(a->leave_station->leave);
	printf("\t到达站:%s", a->arrive_station->sta_name);
	printf("\t到达时间:");
	print_Time(a->arrive_station->arrive);
	printf("\t座位：%s", seat_name);
}

void print_ticket2(struct info_ticket* a)
{
	char* seat_name[3];
	map_seat(seat_name, a->seat);
	printf("出发日期:%d/%d/%d", a->leave_date.year, a->leave_date.month, a->leave_date.day);
	printf("\t车次:%s", a->train->name);
	printf("\t出发站:%s", a->leave_station->sta_name);
	printf("\t出发时间:");
	print_Time(a->leave_station->leave);
	printf("\t到达站:%s", a->arrive_station->sta_name);
	printf("\t到达时间:");
	print_Time(a->arrive_station->arrive);
	printf("\t座位：%s", seat_name);
}

void init_list_ticket(struct list_ticket* a, struct info_ticket data)
{
	a->data = (struct info_ticket*)malloc(sizeof(struct info_ticket));
	*(a->data) = data;
	a->next = NULL;
}

void delete_list_ticket(struct list_ticket* a)
{
	free(a->data);
	a = a->next;
	if (a == NULL)
		return;
	struct list_ticket* p = a->next;
	while (p != NULL)
	{
		free(a->data);
		free(a);
		a = p;
		p = a->next;
	}
	free(a->data);
	free(a);
}
void add_back_ticket(struct list_ticket* a, struct info_ticket data)
{
	while (a->next != NULL)
		a = a->next;
	struct list_ticket* p;
	p = (struct list_ticket*)malloc(sizeof(struct list_ticket));
	a->next = p;
	p->data = (struct info_ticket*)malloc(sizeof(struct info_ticket));
	*(p->data) = data;
	p->next = NULL;
}

void return_ticket(struct list_ticket* l, struct info_ticket* t)		//退票
{
	if (l->data == t)
	{
		if (l->next != NULL)
		{
			l->data = l->next->data;
			l->next = l->next->next;
		}
		else
		{
			l->data = NULL;
			l->next = NULL;
		}
		return;
	}
	while (l->next->data != t)
		l = l->next;				//might be a bug here,if t not in l
	struct list_ticket* p = l->next;
	l->next = l->next->next;
	free(p);
}

void print_list_ticket(struct list_ticket* a ,int no)
{
	print_ticket(a->data, no);
	no = no + 1;
	if (a->next != NULL)
		print_list_ticket(a->next, no);
}

//passenger

struct info_passenger new_passenger(char* name, char* ID, struct info_ticket first_ticket)
{
	struct info_passenger s;
	strcpy_s(s.name, 18, name);
	strcpy_s(s.ID, 19, ID);
	init_list_ticket(&s.tickets, first_ticket);
	return s;
}
void print_info_passenger(struct info_passenger* s)
{
	printf("\n姓名:%s", s->name);
	printf("\nID:%s", s->ID);
	print_list_ticket(&(s->tickets), 1);
}

struct list_passenger new_list_passenger(struct info_passenger data)
{
	struct list_passenger l;
	l.data = (struct info_passenger*)malloc(sizeof(struct info_passenger));
	*(l.data) = data;
	l.next = NULL;
	return l;
}
void init_list_passenger(struct list_passenger* a, struct info_passenger data)
{
	a->data = (struct info_passenger*)malloc(sizeof(struct info_passenger));
	*(a->data) = data;
	a->next = NULL;
}
void delete_list_passenger(struct list_passenger* a)
{
	free(a->data);
	a = a->next;
	if (a == NULL)
		return;
	struct list_passenger* p = a->next;
	while (p != NULL)
	{
		delete_list_ticket(&(a->data->tickets));
		free(a->data);
		free(a);
		a = p;
		p = a->next;
	}
	free(a->data);
	free(a);
}


void add_front_passenger(struct list_passenger* a, struct info_passenger data)
{
	struct list_passenger* p;
	p = (struct list_passenger*)malloc(sizeof(struct list_passenger));
	p->next = a->next;
	a->next = p;
	p->data = a->data;
	a->data = (struct info_passenger*)malloc(sizeof(struct info_passenger));
	*(a->data) = data;
}
void add_back_passenger(struct list_passenger* a, struct info_passenger data)
{
	while (a->next != NULL)
		a = a->next;
	struct list_passenger* p;
	p = (struct list_passenger*)malloc(sizeof(struct list_passenger));
	a->next = p;
	p->data = (struct info_passenger*)malloc(sizeof(struct info_passenger));
	*(p->data) = data;
	p->next = NULL;
}


struct info_passenger* get_passenger(char* name, char* ID, struct list_passenger* l)
{
	if (l->data == NULL)
		return NULL;
	while (strcmp(name, l->data->name) || strcmp(ID, l->data->ID))
	{
		l = l->next;
		if (l == NULL)
			return NULL;
	}
	return l->data;
}
