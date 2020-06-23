#pragma once
#ifndef PASSENGER_H
#define PASSENGER_H

#include"head.h"

struct date
{
	int year, month, day;
};
struct date new_date(int year, int month, int day);
int date_cmp(struct date d1, struct date d2);			//一样返回1，不一样返回0
void print_date(struct date t);


struct info_ticket
{
	struct date leave_date;
	struct info_train* train;
	struct info_station* leave_station;
	struct info_station* arrive_station;
	int seat;
};
struct info_ticket new_ticket(struct date leave_date, struct info_train* train, struct info_station* leave_station, struct info_station* arrive_station,int seat);
void init_ticket(struct info_ticket* ticket, struct date leave_date, struct info_train* train, struct info_station* leave_station, struct info_station* arrive_station,int seat);
void print_ticket(struct info_ticket* a, int no);
void print_ticket2(struct info_ticket* a);
void map_seat(char* seat_name, int seat);


struct list_ticket
{
	struct info_ticket* data;
	struct list_ticket* next;
};
void init_list_ticket(struct list_ticket* a, struct info_ticket data);
void delete_list_ticket(struct list_ticket* a);
void add_back_ticket(struct list_ticket* a, struct info_ticket data);
void return_ticket(struct list_ticket* l, struct info_ticket* t);
void print_list_ticket(struct list_ticket* a, int no);

struct info_passenger
{
	char name[18];
	char ID[19];
	struct list_ticket tickets;
};
struct info_passenger new_passenger(char* name, char* ID, struct info_ticket first_ticket);
void print_info_passenger(struct info_passenger* s);


struct list_passenger
{
	struct info_passenger* data;
	struct  list_passenger* next;
};
struct list_passenger new_list_passenger(struct info_passenger data);
void init_list_passenger(struct list_passenger* a, struct info_passenger data);
void delete_list_passenger(struct list_passenger* a);
void add_front_passenger(struct list_passenger* a, struct info_passenger data);
void add_back_passenger(struct list_passenger* a, struct info_passenger data);

struct info_passenger* get_passenger(char* name, char* ID, struct list_passenger* l);


#endif
