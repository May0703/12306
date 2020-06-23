#include "head.h"

struct Time new_Time(int hour, int minute)
{
	struct Time t;
	t.hour = hour;
	t.minute = minute;
	if (hour >= 24 || hour < 0 || minute >= 60 || minute < 0)		//判断合法
	{
		hour = -1;
		minute = -1;
	}
	return t;
}

void print_Time(struct Time t)
{
	if (t.hour <= 0)
		printf("——");
	else
		printf("%02d:%02d", t.hour, t.minute);
}

int Time_minus(struct Time t1, struct  Time t2)
{
	int t;
	if (t1.hour < 0 || t2.hour < 0)
	{
		return -1;
	}
	t = (t1.hour - t2.hour) * 60 + t1.minute - t2.minute;
	if (t < 0)
		t = -1;
	return t;
}

struct info_station new_station(int no, char* sta_name, struct Time arrive, struct Time leave)
{
	struct info_station s;
	strcpy_s(s.sta_name, 10, sta_name);
	s.no = no;
	s.arrive = arrive;
	s.leave = leave;
	return s;
}

void print_info_station(struct info_station* s)
{
	int stop;
	printf("no: %d\t站名: %s\t到达: ", s->no, s->sta_name);
	print_Time(s->arrive);
	printf("\t出发: ");
	print_Time(s->leave);
	stop = Time_minus(s->leave, s->arrive);
	if (stop == -1)
		printf("\t停靠时间: ——\n");
	else
		printf("\t停靠时间: %d分钟\n", stop);
}


//struct info_station
struct list_station new_list_station(struct info_station data)
{
	struct list_station l;
	l.data = (struct info_station*)malloc(sizeof(struct info_station));
	*(l.data) = data;
	l.next = NULL;
	return l;
}

void init_list_station(struct list_station* a, struct info_station data)
{
	a->data = (struct info_station*)malloc(sizeof(struct info_station));
	*(a->data) = data;
	a->next = NULL;
}

void delete_list_station(struct list_station* a)
{
	free(a->data);
	a = a->next;
	if (a == NULL)
		return;
	struct list_station* p = a->next;
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
/*
void add_front_station(struct list_station* a, struct info_station* data)
{
	struct list_station* p;
	p = (struct list_station*)malloc(sizeof(struct list_station));
	p->next = a->next;
	a->next = p;
	p->data = a->data;
	a->data = data;
}*/
/*
void add_back_station(struct list_station* a, struct info_station* data)
{
	while (a->next != NULL)
		a = a->next;
	struct list_station* p;
	p = (struct list_station*)malloc(sizeof(struct list_station));
	a->next = p;
	p->data = data;
	p->next = NULL;
}*/
void add_front_station(struct list_station* a, struct info_station data)
{
	struct list_station* p;
	p = (struct list_station*)malloc(sizeof(struct list_station));
	p->next = a->next;
	a->next = p;
	p->data = a->data;
	a->data = (struct info_station*)malloc(sizeof(struct info_station));
	*(a->data) = data;
}

void add_back_station(struct list_station* a, struct info_station data)
{
	while (a->next != NULL)
		a = a->next;
	struct list_station* p;
	p = (struct list_station*)malloc(sizeof(struct list_station));
	a->next = p;
	p->data = (struct info_station*)malloc(sizeof(struct info_station));
	*(p->data) = data;
	p->next = NULL;

}

void print_list_station(struct list_station* a)
{
	print_info_station(a->data);
	if (a->next != NULL)
		print_list_station(a->next);
}


void delete_train(struct info_train* t)
{
	delete_list_station(&(t->stations));
}

struct info_train new_train(char* train_name, struct info_station first_station)
{
	struct info_train t;
	strcpy_s(t.name, 10, train_name);
	init_list_station(&(t.stations), first_station);
	return t;
}

void init_train(struct info_train* train, char* train_name, struct info_station first_station)
{
	strcpy_s(train->name, 10, train_name);
	init_list_station(&(train->stations), first_station);
}

void add_station(struct info_train* train, struct info_station data)
{
	add_back_station(&(train->stations), data);
}

void print_train(struct info_train* a)
{
	printf("车次: %s\n", a->name);
	printf("出发: %s\t", start_station(a));
	print_Time(start_Time(a));
	printf("\t到达: %s\t", end_station(a));
	print_Time(end_Time(a));
	printf("\n");
	print_list_station(&(a->stations));
}

char* start_station(struct info_train* a)
{
	return (a->stations).data->sta_name;
}

char* end_station(struct info_train* a)
{
	struct list_station* p = &(a->stations);
	while (p->next != NULL)
		p = p->next;
	return p->data->sta_name;
}

struct Time start_Time(struct info_train* a)
{
	return (a->stations).data->leave;
}

struct Time end_Time(struct info_train* a)
{
	struct list_station* p = &(a->stations);
	while (p->next != NULL)
		p = p->next;
	return p->data->arrive;
}

struct Time get_leave_Time(struct info_train* a, char* sta_name)
{
	struct list_station* p = &(a->stations);
	while (p != NULL)
	{
		if (!strcmp(sta_name, p->data->sta_name))
			return p->data->leave;
		p = p->next;
	}
	return new_Time(-1, -1);
}

struct Time get_arrive_Time(struct info_train* a, char* sta_name)
{
	struct list_station* p = &(a->stations);
	while (p != NULL)
	{
		if (!strcmp(sta_name, p->data->sta_name))
			return p->data->arrive;
		p = p->next;
	}
	return new_Time(-1, -1);

}

void read_info_train(struct info_train* train)
{
	char trainnum[11][5] = { "G143","G1","G141","G7","G9","G3","G11","G13","G15","G17","G21" };
	char station[14][10] = { "北京南" ,"天津南" ,"济南西" ,"南京南" ,"常州北" ,"上海虹桥","蚌埠南","沧州西","上海","无锡东","嘉兴南","泰安","丹阳北","苏州北" };

	init_train(train, trainnum[0], new_station(1, station[0], new_Time(-1, -1), new_Time(7, 50)));
	add_station(train, new_station(2, station[1], new_Time(8, 24), new_Time(8, 31)));
	add_station(train, new_station(3, station[2], new_Time(9, 37), new_Time(9, 39)));
	add_station(train, new_station(4, station[3], new_Time(11, 55), new_Time(11, 57)));
	add_station(train, new_station(5, station[4], new_Time(12, 29), new_Time(12, 31)));
	add_station(train, new_station(6, station[5], new_Time(13, 12), new_Time(-1, -1)));


	init_train(train + 1, trainnum[1], new_station(1, station[0], new_Time(-1, -1), new_Time(9, 00)));
	add_station(train + 1, new_station(2, station[2], new_Time(10, 22), new_Time(10, 24)));
	add_station(train + 1, new_station(3, station[3], new_Time(12, 24), new_Time(12, 26)));
	add_station(train + 1, new_station(4, station[4], new_Time(13, 28), new_Time(-1, -1)));


	init_train(train + 2, trainnum[2], new_station(1, station[0], new_Time(-1, -1), new_Time(9, 12)));
	add_station(train + 2, new_station(2, station[7], new_Time(10, 03), new_Time(10, 05)));
	add_station(train + 2, new_station(3, station[2], new_Time(10, 51), new_Time(10, 58)));
	add_station(train + 2, new_station(4, station[11], new_Time(11, 15), new_Time(11, 17)));
	add_station(train + 2, new_station(5, station[6], new_Time(12, 42), new_Time(12, 47)));
	add_station(train + 2, new_station(6, station[3], new_Time(13, 29), new_Time(13, 31)));
	add_station(train + 2, new_station(7, station[12], new_Time(13, 57), new_Time(14, 02)));
	add_station(train + 2, new_station(8, station[4], new_Time(14, 49), new_Time(14, 51)));
	add_station(train + 2, new_station(9, station[10], new_Time(15, 18), new_Time(15, 24)));
	add_station(train + 2, new_station(10, station[4], new_Time(13, 12), new_Time(-1, -1)));


	init_train(train + 3, trainnum[3], new_station(1, station[0], new_Time(-1, -1), new_Time(10, 00)));
	add_station(train + 3, new_station(2, station[2], new_Time(11, 22), new_Time(11, 24)));
	add_station(train + 3, new_station(3, station[3], new_Time(13, 23), new_Time(13, 25)));
	add_station(train + 3, new_station(4, station[4], new_Time(14, 28), new_Time(-1, -1)));


	init_train(train + 4, trainnum[4], new_station(1, station[0], new_Time(-1, -1), new_Time(12, 00)));
	add_station(train + 4, new_station(2, station[1], new_Time(12, 31), new_Time(12, 33)));
	add_station(train + 4, new_station(3, station[2], new_Time(13, 30), new_Time(13, 32)));
	add_station(train + 4, new_station(4, station[3], new_Time(15, 30), new_Time(15, 32)));
	add_station(train + 4, new_station(5, station[4], new_Time(16, 36), new_Time(-1, -1)));


	init_train(train + 5, trainnum[5], new_station(1, station[0], new_Time(-1, -1), new_Time(14, 00)));
	add_station(train + 5, new_station(2, station[2], new_Time(15, 22), new_Time(15, 24)));
	add_station(train + 5, new_station(3, station[3], new_Time(17, 23), new_Time(17, 25)));
	add_station(train + 5, new_station(4, station[4], new_Time(18, 28), new_Time(-1, -1)));


	init_train(train + 6, trainnum[6], new_station(1, station[0], new_Time(-1, -1), new_Time(15, 00)));
	add_station(train + 6, new_station(2, station[2], new_Time(16, 22), new_Time(16, 24)));
	add_station(train + 6, new_station(3, station[3], new_Time(18, 21), new_Time(18, 23)));
	add_station(train + 6, new_station(4, station[4], new_Time(19, 28), new_Time(-1, -1)));


	init_train(train + 7, trainnum[7], new_station(1, station[0], new_Time(-1, -1), new_Time(17, 00)));
	add_station(train + 7, new_station(2, station[2], new_Time(18, 22), new_Time(18, 24)));
	add_station(train + 7, new_station(3, station[3], new_Time(20, 22), new_Time(20, 24)));
	add_station(train + 7, new_station(4, station[13], new_Time(21, 9), new_Time(21, 11)));
	add_station(train + 7, new_station(5, station[4], new_Time(21, 36), new_Time(-1, -1)));


	init_train(train + 8, trainnum[8], new_station(1, station[0], new_Time(-1, -1), new_Time(18, 00)));
	add_station(train + 8, new_station(2, station[1], new_Time(18, 31), new_Time(18, 33)));
	add_station(train + 8, new_station(3, station[2], new_Time(19, 30), new_Time(19, 32)));
	add_station(train + 8, new_station(4, station[3], new_Time(21, 32), new_Time(21, 34)));
	add_station(train + 8, new_station(5, station[4], new_Time(22, 43), new_Time(-1, -1)));


	init_train(train + 9, trainnum[9], new_station(1, station[0], new_Time(-1, -1), new_Time(19, 00)));
	add_station(train + 9, new_station(2, station[3], new_Time(22, 13), new_Time(22, 15)));
	add_station(train + 9, new_station(3, station[4], new_Time(23, 18), new_Time(-1, -1)));


	init_train(train + 10, trainnum[10], new_station(1, station[0], new_Time(-1, -1), new_Time(19, 8)));
	add_station(train + 10, new_station(2, station[2], new_Time(20, 30), new_Time(20, 32)));
	add_station(train + 10, new_station(3, station[9], new_Time(23, 8), new_Time(23, 10)));
	add_station(train + 10, new_station(4, station[8], new_Time(23, 40), new_Time(-1, -1)));
}

struct info_station* search_station(int station_num, struct info_train* a)
{
	struct list_station* p = &(a->stations);
	while (p != NULL)
	{
		if (station_num == p->data->no)
			return p->data;
		p = p->next;
	}
	return NULL;
}

struct ticket_chosen new_ticket_chosen(struct info_passenger* passenger, struct ticket_chosen* ticket)
{
	struct ticket_chosen t;
	t.passenger = passenger;
	t.ticket = ticket;
	return t;
}

void init_ticket_chosen(struct ticket_chosen* t, struct info_passenger* passenger, struct info_ticket* ticket)
{
	t->passenger = passenger;
	t->ticket = ticket;
}

void init_list_ticket_chosen(struct list_ticket_chosen* a, struct ticket_chosen data)
{
	a->data = (struct ticket_chosen*)malloc(sizeof(struct ticket_chosen));
	*(a->data) = data;
	a->next = NULL;
}

void delete_list_ticket_chosen(struct list_ticket_chosen* a)
{
	free(a->data);
	a = a->next;
	if (a == NULL)
		return;
	struct list_ticket_chosen* p = a->next;
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

void add_back_ticket_chosen(struct list_ticket_chosen* a, struct ticket_chosen data)
{
	while (a->next != NULL)
		a = a->next;
	struct list_ticket_chosen* p;
	p = (struct list_ticket_chosen*)malloc(sizeof(struct list_ticket_chosen));
	a->next = p;
	p->data = (struct ticket_chosen*)malloc(sizeof(struct ticket_chosen));
	*(p->data) = data;
	p->next = NULL;
}

struct start_date new_start_date(struct date start_date, struct list_ticket_chosen tickets_chosen)
{
	struct start_date t;
	t.start_date = start_date;
	t.tickets_chosen = tickets_chosen;
	return t;
}

void init_list_start_date(struct list_start_date* a, struct start_date data)
{
	a->data = (struct start_date*)malloc(sizeof(struct start_date));
	*(a->data) = data;
	a->next = NULL;
}

void add_start_date(struct list_start_date* a, struct start_date data)		//data只有一节
{
	if (a->data == NULL)
	{
		a->data = (struct start_date*)malloc(sizeof(struct start_date));
		a->data = &data;
	}
	int test;
	while ((test = compare_date(a->data->start_date.year, a->data->start_date.month, a->data->start_date.day, data.start_date.year, data.start_date.month, data.start_date.day)) == 2)
	{
		if (a->next == NULL)
		{
			a->next = (struct list_start_date*)malloc(sizeof(struct list_start_date));
			a = a->next;
			a->data = (struct start_date*)malloc(sizeof(struct start_date));
			*(a->data) = data;
			a->next = NULL;
			return;
		}
		a = a->next;
	}
	if (test == 1)
	{
		struct list_start_date* p;
		p = (struct list_start_date*)malloc(sizeof(struct list_start_date));
		p->next = a->next;
		a->next = p;
		p->data = a->data;
		a->data = (struct start_date*)malloc(sizeof(struct start_date));
		*(a->data) = data;
	}
	else if (test == 0)
	{
		a->data->start_date = data.start_date;
		add_back_ticket_chosen(&(a->data->tickets_chosen), *(data.tickets_chosen.data));
	}


}


void delete_list_start_date(struct list_start_date* a)
{
	free(a->data);
	a = a->next;
	if (a == NULL)
		return;
	struct list_start_date* p = a->next;
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
