#pragma once
#ifndef TRAIN_H
#define TRAIN_H

#include"head.h"
#include"passenger.h"


struct ticket_chosen
{
	struct info_passenger* passenger;
	struct info_ticket* ticket;
};
struct ticket_chosen new_ticket_chosen(struct info_passenger* passenger, struct ticket_chosen* ticket);
void init_ticket_chosen(struct ticket_chosen* t, struct info_passenger* passenger, struct info_ticket* ticket);

struct list_ticket_chosen
{
	struct ticket_chosen* data;
	struct list_ticket_chosen* next;
};
void init_list_ticket_chosen(struct list_ticket_chosen* a, struct ticket_chosen data);
void delete_list_ticket_chosen(struct list_ticket_chosen* a);
void add_back_ticket_chosen(struct list_ticket_chosen* a, struct ticket_chosen data);

struct start_date
{
	struct date start_date;
	struct list_ticket_chosen tickets_chosen;
};
struct start_date new_start_date(struct date start_date, struct list_ticket_chosen tickets_chosen);

struct list_start_date
{
	struct start_date* data;
	struct list_start_date* next;
};
void init_list_start_date(struct list_start_date* a, struct start_date data);
void add_start_date(struct list_start_date* a, struct start_date data);
void delete_list_start_date(struct list_start_date* a);

//时间类
struct Time
{
	int hour, minute;
};
struct Time new_Time(int hour, int minute); //新建一个时间
void print_Time(struct Time t); //打印时间
int  Time_minus(struct Time t1, struct Time t2); //算间隔时长

//站信息
struct info_station
{
	int no;
	char sta_name[10];
	struct Time arrive;
	struct Time leave;
};
struct info_station new_station(int no, char* sta_name, struct Time arrive, struct Time leave);			//编号，站名，到达时间，出发时间
//struct info_station new_station(int no, std::string sta_name, struct Time arrive, struct Time leave);
void print_info_station(struct info_station* s);

//站列表，存在列车信息中
struct list_station
{
	struct info_station* data;
	struct  list_station* next;
};
struct list_station new_list_station(struct info_station data);
void init_list_station(struct list_station* a, struct info_station data);
void delete_list_station(struct list_station* a);
//void add_front_station(struct list_station* a, struct info_station* data);
//void add_back_station(struct list_station* a, struct info_station* data);
void add_front_station(struct list_station* a, struct info_station data);
void add_back_station(struct list_station* a, struct info_station data);
void print_list_station(struct list_station* a);


//列车信息，存为常量
struct info_train
{
	char name[10];
	struct list_station stations;
	struct list_start_date start_dates;
	//~struct info_train();
};
struct info_train new_train(char* train_name, struct info_station first_station);						//车次，第一站信息
void init_train(struct info_train* train, char* train_name, struct info_station first_station);
//void init_train(struct info_train* train, std::string train_name, struct info_station first_station);
void delete_train(struct info_train* t);
void add_station(struct info_train* train, struct info_station data);
void print_train(struct info_train* a);
char* start_station(struct info_train* a);
char* end_station(struct info_train* a);
void read_info_train(struct info_train* train);
struct Time start_Time(struct info_train* a);
struct Time end_Time(struct info_train* a);
struct Time get_leave_Time(struct info_train* a, char* sta_name);
struct Time get_arrive_Time(struct info_train* a, char* sta_name);
struct info_station* search_station(int no, struct info_train*);

#endif