#include"head.h"

int read_number(int count)//��������Ϊ'1'����count'
{
	char a = getchar();
	char b = getchar();
	if (b != '\n')
	{
		while ((b = getchar()) != '\n') {}
		printf("�������������밴����ʾ����:\n");
		return read_number(count);
	}
	else
	{
		return a - '0';
	}
}

void settime(int* nowtime)//�ֶ�����ʱ��
{
	int i, j, k;
	char temp[15] = { 0 };
	printf("\n�����뵱ǰʱ�䣬�������ں�ʱ���룬��ʽʾ����20200615150545��������ɺ󣬰��س���������\n");
	while (1)
	{
		read_a_string(14, temp);
		if (strlen(temp) != 14) //���ȳ���14����ʾ����
		{
			printf("�������������밴����ʾ������ȷ��ʱ��:\n");
			back_to_zero(temp, nowtime, 6);
			continue;
		}
		for (i = 0; i < 4; i++)//�ֱ����������ʹ���������ʱ����
		{
			nowtime[0] = nowtime[0] * 10 + (temp[i] - '0');
		}
		for (j = 2; j <= 6; j++)
		{
			for (k = 0; k < 2; k++)
			{
				nowtime[j - 1] = nowtime[j - 1] * 10 + (temp[i + 2 * (j - 2) + k] - '0');
			}
		}
		if (nowtime[3] >= 24 && nowtime[4] >= 60 && nowtime[5] >= 60)//�ж�����ʱ�����Ƿ���� 
		{
			printf("�������������밴����ʾ������ȷ��ʱ��:\n");
			back_to_zero(temp, nowtime, 6);
		}
		else
		{
			if (test_a_date1(nowtime))
			{
				break;
			}
			else
			{
				printf("�������������밴����ʾ������ȷ��ʱ��:\n");
				back_to_zero(temp, nowtime, 6);
			}
		}
	}
	printf("��ǰʱ���ǣ�%d/%d/%d %d:%d:%d\n", nowtime[0], nowtime[1], nowtime[2], nowtime[3], nowtime[4], nowtime[5]);
}

void gettime(int* nowtime) //��ȡϵͳʱ��
{
	time_t t;
	struct tm  lt;
	time(&t);
	localtime_s(&lt, &t);
	nowtime[0] = lt.tm_year + 1900;
	nowtime[1] = lt.tm_mon + 1;
	nowtime[2] = lt.tm_mday;
	nowtime[3] = lt.tm_hour;
	nowtime[4] = lt.tm_min;
	nowtime[5] = lt.tm_sec;
	printf("��ǰʱ���ǣ�%d/%d/%d %d:%d:%d\n", lt.tm_year + 1900, lt.tm_mon + 1, lt.tm_mday, lt.tm_hour, lt.tm_min, lt.tm_sec);
}

void back_to_zero(char* temp, int* time, int length_of_time) //�����������
{
	int i;
	temp[0] = 0;
	for (i = 0; i < length_of_time; i++)
	{
		time[i] = 0;
	}
}

void read_a_string(int length, char* string) //��ȡ����Ϊlength���ַ���
{
	int i = 0, j;
	char c;
	while (i < length + 1) //���潫�û�������ַ���������ֹ���
	{
		if ((c = getchar()) != '\n')
		{
			string[i] = c;
			i = i + 1;
		}
		else
		{
			string[i] = c;
			i = length + 1;
		}
	}
	while (c != EOF && c != '\n')
	{
		c = getchar();
	}
	for (j = 0; j < length + 1; j++)
	{
		if (string[j] == '\n')
		{
			string[j] = 0;
			break;
		}
	}
}


int test_a_date1(int* date)//�ж����������Ƿ���ڣ����ڣ�����1�������ڣ�����0
{
	if (date[0] > 2019 && date[1] > 0 && date[1] < 13 && date[2] > 0 && date[2] < 32)
	{
		if (date[1] == 4 || date[1] == 6 || date[1] == 9 || date[1] == 11)
		{
			if (date[2] == 31)
			{
				return 0;
			}
			else return 1;
		}
		else if (date[1] == 2)
		{
			if (date[0] % 4 == 0)
			{
				if (date[0] % 100 == 0 && date[0] % 400 == 0)
				{
					if (date[2] > 29)
					{
						return 0;
					}
					else return 1;
				}
				else if (date[0] % 100 != 0)
				{
					if (date[2] > 29)
					{
						return 0;
					}
					else return 1;
				}
				else
				{
					if (date[2] > 28)
					{
						return 0;
					}
					else return 1;
				}
			}
			else
			{
				if (date[2] > 28)
				{
					return 0;
				}
				else return 1;
			}
		}
		else return 1;
	}
	else
	{
		return 0;
	}
}

void choose_a_date(int* date, int* nowtime)//���ڹ�Ʊ����ǩʱѡ������
{
	int i, j, k;
	char temp[9];
	int choice;
	while (1)
	{
		read_a_string(8, temp);
		if (strlen(temp) != 8) //���ȳ���8����ʾ����
		{
			printf("�������������밴����ʾ������ȷ������:\n");
			back_to_zero(temp, date, 3);
			continue;
		}
		for (i = 0; i < 4; i++)//�ֱ����������ʹ���������
		{
			date[0] = date[0] * 10 + (temp[i] - '0');
		}
		for (j = 0; j < 2; j++)
		{
			date[1] = date[1] * 10 + (temp[4 + j] - '0');
		}
		for (k = 0; k < 2; k++)
		{
			date[2] = date[2] * 10 + (temp[6 + k] - '0');
		}
		if (test_a_date1(date))//���������ڴ��ڣ������Ƿ���30��֮��
		{
			if (test_a_date2(date, nowtime)) break;
			else
			{
				printf("�������������밴����ʾ������ȷ������:\n");
				back_to_zero(temp, date, 3);
			}
		}
		else
		{
			printf("�������������밴����ʾ������ȷ������:\n");
			back_to_zero(temp, date, 3);
		}
	}
	printf("��ѡ��������ǣ�%d/%d/%d\n", date[0], date[1], date[2]);
	if (nowtime[3] >= 23 && nowtime[4] >= 10)
	{
		printf("\n���������г����ѿ���������ѡ�����ڣ�������1���˳�����������2��");
		choice = read_number(2);
		switch (choice)
		{
		case 1:  printf("\n������������ڣ�ʾ����20200619��\n"); choose_a_date(date, nowtime); break;
		case 2:  return 0;
		}
	}
}

int test_a_date2(int* date, int* nowtime)//�ж����������Ƿ��ڵ�ǰʱ��֮������30��֮�ڣ��ǣ�����1���񣬷���0
{
	if (nowtime[1] == 12)
	{
		if (nowtime[2] < 3)
		{
			if (date[0] == nowtime[0] && date[1] == nowtime[1] && date[2] >= nowtime[2] && date[2] <= nowtime[2] + 29) return 1;
			else return 0;
		}
		else
		{
			if (date[0] == nowtime[0] && date[1] == nowtime[1] && date[2] >= nowtime[2]) return 1;
			else if (date[0] == nowtime[0] + 1 && date[1] == 1 && date[2] <= nowtime[2] - 2) return 1;
			else return 0;
		}
	}
	else if (nowtime[1] == 1 || nowtime[1] == 3 || nowtime[1] == 5 || nowtime[1] == 7 || nowtime[1] == 8 || nowtime[1] == 10)
	{
		if (nowtime[2] < 3)
		{
			if (date[0] == nowtime[0] && date[1] == nowtime[1] && date[2] >= nowtime[2] && date[2] <= nowtime[2] + 29) return 1;
			else return 0;
		}
		else
		{
			if (date[0] == nowtime[0] && date[1] == nowtime[1] && date[2] >= nowtime[2]) return 1;
			else if (date[0] == nowtime[0] && date[1] == nowtime[1] + 1 && date[2] <= nowtime[2] - 2) return 1;
			else return 0;
		}
	}
	else if (nowtime[1] == 2)
	{
		if (nowtime[0] % 100 == 0)
		{
			if (nowtime[0] % 400 == 0)
			{
				if (date[0] == nowtime[0] && date[1] == nowtime[1] && date[2] >= nowtime[2]) return 1;
				else if (date[0] == nowtime[0] && date[1] == nowtime[1] + 1 && date[2] <= nowtime[2]) return 1;
				else return 0;
			}
			else
			{
				if (date[0] == nowtime[0] && date[1] == nowtime[1] && date[2] >= nowtime[2]) return 1;
				else if (date[0] == nowtime[0] && date[1] == nowtime[1] + 1 && date[2] <= nowtime[2] + 1) return 1;
				else return 0;
			}
		}
		else if (nowtime[0] % 4 == 0)
		{
			if (date[0] == nowtime[0] && date[1] == nowtime[1] && date[2] >= nowtime[2]) return 1;
			else if (date[0] == nowtime[0] && date[1] == nowtime[1] + 1 && date[2] <= nowtime[2]) return 1;
			else return 0;
		}
		else
		{
			if (date[0] == nowtime[0] && date[1] == nowtime[1] && date[2] >= nowtime[2]) return 1;
			else if (date[0] == nowtime[0] && date[1] == nowtime[1] + 1 && date[2] <= nowtime[2] + 1) return 1;
			else return 0;
		}
	}
	else
	{
		if (nowtime[2] == 1)
		{
			if (date[0] == nowtime[0] && date[1] == nowtime[1]) return 1;
			else return 0;
		}
		else
		{
			if (date[0] == nowtime[0] && date[1] == nowtime[1] && date[2] >= nowtime[2]) return 1;
			else if (date[0] == nowtime[0] && date[1] == nowtime[1] + 1 && date[2] <= nowtime[2] - 1) return 1;
			else return 0;
		}
	}
}

void read_passenger_number(int* passenger_number)
{
	printf("\n����д���ĳ˿�����������ͬʱ����5���˵�Ʊ��\n");
	*passenger_number = read_number(5);
}

void read_passenger_name(char* name)
{
	read_a_string(16, name);
	if (strlen(name) > 16 || strlen(name) <= 2)
	{
		for (int i = 0; i < 18; i++)
			name[i] = 0;
		printf("������������������������룺\n");
		read_passenger_name(name);
	}
}

void read_passenger_ID(char* ID)
{
	read_a_string(18, ID);
	if (strlen(ID) != 18)
	{
		for (int i = 0; i < 19; i++)
			ID[i] = 0;
		printf("�������ID�������������룺\n");
		read_passenger_ID(ID);
	}
	for (int i = 0; i < 17; i++)
	{
		if (ID[i] < '0' || ID[i] > '9')
		{
			for (int j = 0; j < 18; j++)
				ID[j] = 0;
			printf("�������ID�������������룺\n");
			read_passenger_ID(ID);
		}
	}
	if (ID[17] >= '0' && ID[17] <= '9') {}
	else if (ID[17] == 'X') {}
	else
	{
		for (int j = 0; j < 18; j++)
			ID[j] = 0;
		printf("�������ID�������������룺\n");
		read_passenger_ID(ID);
	}
}

void choose_a_train(int* nowtime, struct info_train train[], struct info_train** train_chosen, int* date, char name[][18], char ID[][19], struct list_pssenger* users)
{
	int test = 0, choice = 0;
	char train_name[5] = { 0 };
	read_a_string(4, train_name);
	for (int i = 0; i < 11; i++)
	{
		if (strcmp(train_name, train[i].name) == 0)
		{
			*train_chosen = &train[i];
			test = 1;
			break;
		}
	}
	if (test == 0)
	{
		printf("��������г�����������������:\n");
		choose_a_train(nowtime, train, train_chosen, date, name, ID, users);
		return;
	}
	if (nowtime[2] == date[3] && nowtime[3] >= end_Time(*train_chosen).hour && nowtime[4] >= end_Time(*train_chosen).minute)
	{
		printf("\n���Ѳ����ٹ�����г��ĳ�Ʊ������ѡ���г���������1�����أ�������2��\n");
		choice = read_number(2);
		switch (choice)
		{
		case 1:  printf("\n�������г��ţ�ʾ����G17��\n"); choose_a_train(nowtime, train, train_chosen, date, name, ID, users); return;
		case 2:  return;
		}
	}

	struct date datebuy = new_date(date[0], date[1], date[2]);
	//����ظ�����
	for (int i = 0; i < 5 && name[i][0] != 0 && ID[i][0] != 0; i++)
	{
		struct info_passenger* p = get_passenger(&name[i], &ID[i], users);
		if (p != NULL)
		{
			struct list_ticket* t= &(p->tickets);
			while (t != NULL)
			{
				if (date_cmp( t->data->leave_date,datebuy)&&t->data->train==*train_chosen)
				{
					printf("\n%s�ѹ�������г��ĳ�Ʊ������ѡ���г���������1�����أ�������2��\n", name[i]);
					choice = read_number(2);
					switch (choice)
					{
					case 1:  printf("\n�������г��ţ�ʾ����G17��\n"); choose_a_train(nowtime, train, train_chosen, date, name, ID, users); return;
					case 2:  return;
					}
				}
				t = t->next;
			}
		}
	}
}

void read_station_num(int* station_num_int)
{
	char station_num_char[3] = { 0 };
	read_a_string(2, station_num_char);
	if (strlen(station_num_char) == 1) *station_num_int = station_num_char[0] - '0';
	else if (strlen(station_num_char) == 2)
	{
		*station_num_int = (station_num_char[0] - '0') * 10 + station_num_char[1] - '0';
	}
	else
	{
		printf("������ĳ�վ�����������������:\n");
		read_station_num(station_num_int);
	}
}

void choose_leave_station(int* nowtime, struct info_station** leave_station_chosen, struct info_train* train_chosen, int* date)
{
	int station_num_int = 0, test = 0, choice = 0;
	read_station_num(&station_num_int);

	*leave_station_chosen = search_station(station_num_int, train_chosen);
	if (*leave_station_chosen == NULL)
	{
		printf("������ĳ�վ�����������������:\n");
		choose_leave_station(nowtime, leave_station_chosen, train_chosen, date);
	}
	else
	{
		if (nowtime[2] == date[2] && nowtime[3] > get_leave_Time(train_chosen, (*leave_station_chosen)->sta_name).hour)
		{
			printf("\n���Ѳ����ٹ����վ�ĳ�Ʊ������ѡ��վ��������1�����أ�������2��\n");
			choice = read_number(2);
			switch (choice)
			{
			case 1:  printf("\n�����������վ�ı�ţ�ʾ����1��\n"); choose_leave_station(nowtime, leave_station_chosen, train_chosen, date); break;
			case 2:  return 0;
			}
		}
		else if (nowtime[2] == date[2] && nowtime[3] == get_leave_Time(train_chosen, (*leave_station_chosen)->sta_name).hour && nowtime[4] >= get_leave_Time(train_chosen, (*leave_station_chosen)->sta_name).minute)
		{
			printf("\n���Ѳ����ٹ����վ�ĳ�Ʊ������ѡ��վ��������1�����أ�������2��\n");
			choice = read_number(2);
			switch (choice)
			{
			case 1:  printf("\n�����������վ�ı�ţ�ʾ����1��\n"); choose_leave_station(nowtime, leave_station_chosen, train_chosen, date); break;
			case 2:  return 0;
			}
		}
	}
}

void choose_arrive_station(int* nowtime, struct info_station** arrive_station_chosen, struct info_station* leave_station_chosen, struct info_train* train_chosen)
{
	int station_num_int = 0, test = 0, choice = 0;
	read_station_num(&station_num_int);
	*arrive_station_chosen = search_station(station_num_int, train_chosen);
	if (*arrive_station_chosen == NULL)
	{
		printf("������ĳ�վ�����������������:\n");
		choose_arrive_station(nowtime, arrive_station_chosen, leave_station_chosen, train_chosen);
	}
	else
	{
		if (leave_station_chosen->no >= (*arrive_station_chosen)->no)
		{
			printf("\n�����ܹ��������վ֮ǰ�ĵĳ�Ʊ������ѡ��վ��������1���˳�����������2��\n");
			choice = read_number(2);
			switch (choice)
			{
			case 1:  printf("\n�����뵽�ﳵվ�ı�ţ�ʾ����2��\n"); choose_arrive_station(nowtime, arrive_station_chosen, leave_station_chosen, train_chosen); break;
			case 2:  return 0;
			}
		}
	}
}

struct info_passenger* search_passenger(char* name, char* ID, struct list_passenger* users)
{
	int choice;
	printf("\n������˿͵���������������Ϊ�˸����֣�\n");
	read_passenger_name(name);
	printf("\n������˿͵�ID������Ϊ18�����֣�\n");
	read_passenger_ID(ID);
	struct info_passenger* p = get_passenger(name, ID, users);
	if (p == NULL)
	{
		printf("\n���������ó˿͵Ĺ�Ʊ��Ϣ���������룬������1�����أ�������2��\n");
		choice = read_number(2);
		if (choice == 1) p = search_passenger(name, ID, users);
	}
	return p;
}

struct info_ticket* choose_a_ticket(int* nowtime, struct info_passenger* p, int return_or_change)
{
	struct info_ticket* t = NULL;
	char no_char[3];
	int no, test, choice, date[3];
	read_a_string(2, no_char);
	if (strlen(no_char) == 3)
	{
		printf("\n��������������������ȷ�ı��:\n");
		no_char[0] = 0;
		no_char[1] = 0;
		no_char[2] = 0;
		return choose_a_ticket(nowtime, p, return_or_change);
	}
	else
	{
		if (strlen(no_char) == 1)
		{
			no = (no_char[0] - '0');
			if (no > 9 || no <= 0)
			{
				printf("\n��������������������ȷ�ı��:\n");
				no_char[0] = 0;
				return choose_a_ticket(nowtime, p, return_or_change);
			}
		}
		else
		{
			if (no_char[0] <= '0' || no_char[0] > '9' || no_char[1] < 0 || no_char[1] > 9)
			{
				printf("\n��������������������ȷ�ı��:\n");
				no_char[0] = 0;
				no_char[1] = 0;
				return choose_a_ticket(nowtime, p, return_or_change);
			}
			no = (no_char[0] - '0') * 10 + no_char[1] - '0';
		}
		/*if (no == 1) t = p->tickets.data;
				else
				{
					for (int i = 1; i < no; i++)
					{
						t = p->tickets.next->data;
						if (t == NULL)
						{
							printf("\n��������������������ȷ�ı��:\n");
							return choose_a_ticket(nowtime, p,return_or_change);
						}
					}
				}*/
		struct list_ticket* tp = &(p->tickets);
		for (int i = 1; i < no; i++)
		{
			if (tp->next == NULL)
			{
				printf("\n��������������������ȷ�ı��:\n");
				return choose_a_ticket(nowtime, p, return_or_change);
			}
			else
				tp = tp->next;
		}
		t = tp->data;


		date[0] = t->leave_date.year;
		date[1] = t->leave_date.month;
		date[2] = t->leave_date.day;
		test = test_a_date2(date, nowtime);
		if (test == 1)
		{
			return t;
		}
		else
		{
			if (return_or_change == 0)
			{
				if (date[0] == nowtime[0] && date[1] == nowtime[1] && date[2] == nowtime[2])
				{
					return t;
				}
				else
				{
					printf("\n��ֻ��ѡ��δ�����Ļ����ѷ����ĳ�Ʊ���������룬������1�����أ�������2��:\n");
					choice = read_number(2);
					if (choice == 1) return choose_a_ticket(nowtime, p, return_or_change);
					else return NULL;
				}
			}
			else
			{
				if (date[0] == nowtime[0] && date[1] == nowtime[1] && date[2] == nowtime[2])
				{
					if (nowtime[3] < t->leave_station->leave.hour)
					{
						return t;
					}
					else if (nowtime[3] > t->leave_station->leave.hour)
					{
						printf("\n��ֻ��ѡ��δ�����ĳ�Ʊ���������룬������1�����أ�������2��:\n");
						choice = read_number(2);
						if (choice == 1) return choose_a_ticket(nowtime, p, return_or_change);
						else return NULL;
					}
					else
					{
						if (nowtime[2] < t->leave_station->leave.hour)
						{
							return t;
						}
						else
						{
							printf("\n��ֻ��ѡ��δ�����ĳ�Ʊ���������룬������1���˳�����������2��:\n");
							choice = read_number(2);
							if (choice == 1) return choose_a_ticket(nowtime, p, return_or_change);
							else return NULL;
						}
					}
				}
				else
				{
					printf("\n��ֻ��ѡ��δ�����ĳ�Ʊ���������룬������1���˳�����������2��:\n");
					choice = read_number(2);
					if (choice == 1) return choose_a_ticket(nowtime, p, return_or_change);
					else return NULL;
				}
			}
		}
	}
}

int compare_date(int year1, int month1, int day1, int year2, int month2, int day2)
{
	if (year1 > year2)
	{
		return 1;
	}
	else if (year1 < year2)
	{
		return 2;
	}
	else
	{
		if (month1 > month2)
		{
			return 1;
		}
		else if (month1 < month2)
		{
			return 2;
		}
		else
		{
			if (day1 > day2)
			{
				return 1;
			}
			else if (day1 < day2)
			{
				return 2;
			}
			else
			{
				return 0;
			}
		}
	}
}

int compare_time(int hour1, int minute1, int hour2, int minute2)
{
	if (hour1 > hour2)
	{
		return 1;
	}
	else if (hour1 < hour2)
	{
		return 2;
	}
	else
	{
		if (minute1 > minute2)
		{
			return 1;
		}
		else if (minute1 < minute2)
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}
}