#pragma once
#ifndef HEAD_H
#define HEAD_H

#include<stdio.h>
#include<time.h>
#include<string.h>
#include"train.h"
#include"passenger.h"

int read_number(int count);
int test_a_date1(int* date);
int test_a_date2(int* date, int* nowtime);
void gettime(int* nowtime);
void settime(int* nowtime);
void back_to_zero(char* temp, int* time, int length_of_time);
void read_a_string(int length, char* string);
void choose_a_date(int* date, int* nowtime);
void read_passenger_number(int* passenger_number);
void read_passenger_name(char* name);
void read_passenger_ID(char* ID);
void choose_a_train(int* nowtime, struct info_train* train, struct info_train** train_chosen, int* date,char name[][18],char ID[][19],struct list_pssenger * users);
void read_station_num(int* station_num_int);
void choose_leave_station(int* nowtime, struct info_station** leave_station_chosen, struct info_train* train_chosen, int* date);
void choose_arrive_station(int* nowtime, struct info_station** arrive_station_chosen, struct info_station* leave_station_chosen, struct info_train* train_chosen);
struct info_passenger* search_passenger(char* name, char* ID, struct list_passenger* users);
struct info_ticket* choose_a_ticket(int* nowtime, struct info_passenger* p, int return_or_change);
int compare_date(int year1, int month1, int day1, int year2, int month2, int day2);
int compare_time(int hour1, int minute1,int hour2, int minute2);

#endif