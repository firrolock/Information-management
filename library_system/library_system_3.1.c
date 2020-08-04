#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
//#include <unistd.h>

typedef struct Book  
{
	int sequence;
	char title[64];
	char author_name[32];
	char publisher[32];
	char location[32];
	char price[16];
	struct Book *next;
} Book;
#if 1
void Read_Data(Book **pp, FILE *fp)
{

	//��ȡ���ݲ���������
	Book *p;
	p = (Book *)malloc(sizeof(Book));
	p->next = NULL;
	/*fseek(fp,0,2);//�ļ�ĩ
	w=ftell(fp);
	rewind(fp);*/
	while(fread(p, sizeof(Book), 1, fp))
	{
		p->next = *pp;
		*pp = p;
		p = (Book *)malloc(sizeof(Book));
		p->next = NULL;
	}
	free(p);
	p = NULL;
	return ;
}
void get_data(char *buf, int num) {
	fgets(buf, num, stdin);
	if (buf[strlen(buf) - 1] != '\n') {
		scanf("%*[^\n]");
		scanf("%*c");
	}
	else {
		buf[strlen(buf) - 1] = 0;
	}
	return;
}
void Add_Data(Book **pp)
{
	//ͼ����Ϣ���
	char c = 0;
	int cnt = 1;
	Book *p = NULL;
	while (1) {
		if (cnt == 1) {
			printf("����ӵ�1��ͼ����Ϣ��\n");
			scanf("%*[^\n]");
			scanf("%*c");
		}
		else {
			printf("����ӵ�%d��ͼ����Ϣ��������������������������'q'�˳���...\n", cnt);
			scanf("%c", &c);
			if (c != '\n') {
				scanf("%*[^\n]");
				scanf("%*c");
			}
		}
		if (c == 'q') {
			return ;
		}
		if (!*pp) {
			p = (Book *)malloc(sizeof(Book));
			p->sequence = 1;
			printf("������������");
			get_data(p->title, 64);
			printf("��������������");
			get_data(p->author_name, 32);
			printf("��������淽���ƣ�");
			get_data(p->publisher, 32);
			printf("������ͼ��۸�");
			get_data(p->price, 16);
			printf("������ͼ�鴢��λ�ã�");
			get_data(p->location, 32);
			p->next = *pp;
			*pp = p;
			cnt++;
		}
		else {
			p = (Book *)malloc(sizeof(Book));
			p->sequence = (*pp)->sequence + 1;
			printf("������������");
			get_data(p->title, 64);
			printf("��������������");
			get_data(p->author_name, 32);
			printf("��������淽���ƣ�");
			get_data(p->publisher, 32);
			printf("������ͼ��۸�");
			get_data(p->price, 16);
			printf("������ͼ�鴢��λ�ã�");
			get_data(p->location, 32);
			p->next = *pp;
			*pp = p;
			cnt++;
		}
	}
}
void Write_Data(const Book *p)
{
	FILE *fp = NULL;
	//ͼ����Ϣ����
	if ((fp = fopen("hc.txt", "w")) == NULL)
	{
		printf("�����ļ�ʧ�ܣ������±���");
		return;
	}
	while(p)
	{
		fwrite(p,sizeof(Book),1,fp);
		p=p->next;
	}
	fclose(fp);
}
void Show_Data(const Book *p)
{
	//ͼ����Ϣ��ʾ
	if (!p) {
		printf("\nû��ͼ����Ϣ��\n");
		return;
	}
	printf("\n��ǰϵͳ��ͼ����Ϣ��\n");
	while(p)
	{
		printf("��ţ�%d�� ͼ������%s�� ���ߣ�%s�� ���淽��%s�� �۸�%s�� ����λ�ã�%s.\n", p->sequence,p->title,p->author_name,p->publisher,p->price,p->location);
		p=p->next;
	}
	return;
}
int Delete_Data(Book **pp, int type, const char *str)
{
	Book *p = *pp;
	Book *p_first = NULL, *p_mid = NULL, *p_last = NULL;
	if (!type) {
		if ((*pp)->sequence == atoi(str)) {
			p_first = *pp;
			*pp = p_first->next;
			free(p_first);
			p_first = NULL;
			return 1;
		}
		while (p->next) {
			p_first = p;
			p_mid = p_first->next;
			p_last = p_mid->next;
			if (p_mid->sequence == atoi(str)) {
				p_first->next = p_last;
				free(p_mid);
				p_mid = NULL;
				return 1;
			}
			p = p->next;
		}
	}
	if (type == 1) {
		if (!strcmp((*pp)->title, str)) {
			p_first = *pp;
			*pp = p_first->next;
			free(p_first);
			p_first = NULL;
			return 1;
		}
		while (p->next) {
			p_first = p;
			p_mid = p_first->next;
			p_last = p_mid->next;
			if (!strcmp(p_mid->title, str))
			{
				p_first->next = p_last;
				free(p_mid);
				p_mid = NULL;
				return 1;
			}
			p = p->next;
		}
	}
	if (type == 2) {
		if (!strcmp((*pp)->author_name, str)) {
			p_first = *pp;
			*pp = p_first->next;
			free(p_first);
			p_first = NULL;
			return 1;
		}
		while (p->next) {
			p_first = p;
			p_mid = p_first->next;
			p_last = p_mid->next;
			if (!strcmp(p_mid->author_name, str))
			{
				p_first->next = p_last;
				free(p_mid);
				p_mid = NULL;
				return 1;
			}
			p = p->next;
		}
	}
	if (type == 3) {
		if (!strcmp((*pp)->publisher, str)) {
			p_first = *pp;
			*pp = p_first->next;
			free(p_first);
			p_first = NULL;
			return 1;
		}
		while (p->next) {
			p_first = p;
			p_mid = p_first->next;
			p_last = p_mid->next;
			if (!strcmp(p_mid->publisher, str))
			{
				p_first->next = p_last;
				free(p_mid);
				p_mid = NULL;
				return 1;
			}
			p = p->next;
		}
	}
	if (type == 4) {
		if (!strcmp((*pp)->price, str)) {
			p_first = *pp;
			*pp = p_first->next;
			free(p_first);
			p_first = NULL;
			return 1;
		}
		while (p->next) {
			p_first = p;
			p_mid = p_first->next;
			p_last = p_mid->next;
			if (!strcmp(p_mid->price, str))
			{
				p_first->next = p_last;
				free(p_mid);
				p_mid = NULL;
				return 1;
			}
			p = p->next;
		}
	}
	return 0;
}
void Modify_Data(Book *p, int num) {
	char type = 0;
	Book *p_tmp = NULL;
	char buf[64] = { 0 };
	for (p_tmp = p; p_tmp; p_tmp = p_tmp->next) {
		if (p_tmp->sequence == num) {
			printf("������Ҫ�޸ĵ���Ϣ�����룺1 ������ 2 �������� 3 ���淽���ƣ� 4 �۸� 5 ����λ�á�\n");
			scanf("%d", &type);
			scanf("%*[^\n]");
			scanf("%*c");
			if (type == 1) {
				printf("�������µ�������");
				get_data(buf, 64);
				strcpy(p_tmp->title, buf);
				break;
			}
			if (type == 2) {
				printf("�������µ���������");
				get_data(buf, 32);
				strcpy(p_tmp->author_name, buf);
				break;
			}
			if (type == 3) {
				printf("�������µĳ��淽���ƣ�");
				get_data(buf, 32);
				strcpy(p_tmp->publisher, buf);
				break;
			}
			if (type == 4) {
				printf("�������µļ۸�");
				get_data(buf, 16);
				strcpy(p_tmp->price, buf);
				break;
			}
			if (type == 5) {
				printf("�������µĴ���λ�ã�");
				get_data(buf, 32);
				strcpy(p_tmp->location, buf);
				break;
			}
		}
	}
	if (!p_tmp) {
		printf("δ�ҵ���Ӧ��ŵ�ͼ����Ϣ�������ԣ�\n");
	}
	return;
}
Book *Find_Data(const Book *p, int type, const char *str)
{
	//ͼ����Ϣ����
	Book *s=NULL;
	if(type==1)//��������
	{
		while(p)
		{
			if(!strcmp(p->title,str))
				break;
			p=p->next;
		}
		s=p;
	}
	if(type==2)//����������
	{
		while(p)
		{
			if(!strcmp(p->author_name,str))
				break;
			p=p->next;
		}
		s=p;
	}
	if (type == 3)//�����淽���Ʋ�
	{
		while (p)
		{
			if (!strcmp(p->publisher, str))
				break;
			p = p->next;
		}
		s = p;
	}
	if (type == 4)//���۸��
	{
		while (p)
		{
			if (!strcmp(p->price, str))
				break;
			p = p->next;
		}
		s = p;
	}
	return s;
}
void swap(Book *p1) {
	int sequence;
	char title[64];
	char author_name[32];
	char publisher[32];
	char location[32];
	char price[16];
	sequence = p1->next->sequence;
	strcpy(title, p1->next->title);
	strcpy(author_name, p1->next->author_name);
	strcpy(publisher, p1->next->publisher);
	strcpy(location, p1->next->location);
	strcpy(price, p1->next->price);  //1
	p1->next->sequence = p1->sequence;
	strcpy(p1->next->title, p1->title);
	strcpy(p1->next->author_name, p1->author_name);
	strcpy(p1->next->publisher, p1->publisher);
	strcpy(p1->next->location, p1->location);
	strcpy(p1->next->price, p1->price);  //2
	p1->sequence = sequence;
	strcpy(p1->title, title);
	strcpy(p1->author_name, author_name);
	strcpy(p1->publisher, publisher);
	strcpy(p1->location, location);
	strcpy(p1->price, price);  //3
	return;
}
void Sort_Data(Book *p, int group) {  //1 title, 2 author_name, 3 publisher, 4 price, 5 location
	Book *p1 = NULL, *p_tmp = NULL;
	int num = 0, cnt = 0;
	//get the number of nodes of the link
	for (p_tmp = p; p_tmp; p_tmp = p_tmp->next) {
		/*if (!p_tmp->next) {
			break;
		}*/
		num++;
	}
	//bubble sort for the link
	while (1) {
		if (num <= 1) {
			break;
		}
		p1 = p;
		cnt = 0;
		p_tmp = p;
		//set destination pointer of the link to sort
		while (1) {
			if (cnt == num - 1) {
				break;
			}
			p_tmp = p_tmp->next;
			cnt++;
		}
		while (1) {
			if (p1 == p_tmp) {
				break;
			}
			if (group == 1) {
				if (strcmp(p1->title, p1->next->title) > 0) {
					swap(p1);
				}
			}
			if (group == 2) {
				if (strcmp(p1->author_name, p1->next->author_name) > 0) {
					swap(p1);
				}
			}
			if (group == 3) {
				if (strcmp(p1->publisher, p1->next->publisher) > 0) {
					swap(p1);
				}
			}
			if (group == 4) {
				if (atoi(p1->price) > atoi(p1->next->price)) {
					swap(p1);
				}
			}
			if (group == 5) {
				if (strcmp(p1->location, p1->next->location) > 0) {
					swap(p1);
				}
			}
			p1=p1->next;
		}
		num--;
	}
	//reset all the sequences of nodes in the link
	cnt = 1;
	for (p_tmp = p; p_tmp; p_tmp = p_tmp->next) {
		p_tmp->sequence = cnt;
		cnt++;
	}
	return ;
}
void menu(void)
	{
		Book *L=NULL,*p=NULL;
		FILE *fp=NULL;
		int choice = 0,flag = 1;
		char type = 0;
		char strtext[64] = { 0 };
		//�ļ�������
		if((fp=fopen("hc.txt","r"))==NULL)
		{
			printf("û��ͼ����Ϣ�����ļ��������ͼ����Ϣ������\n");
		}
		//�ļ�����
		else {
			Read_Data(&L, fp);
			fclose(fp);
			if (!L) {
				printf("\nû��ͼ����Ϣ!\n");
			}
			else {
				Show_Data(L);
			}
		}
		while(flag)
		{
			printf("\n**********************************************\n");
			printf("\n\t���������Խ���ϵͳ��Ӧ����\n\t��ÿ�����������Իس�Ϊȷ�ϣ�\n");
			printf("\t1.���ͼ����Ϣ:\n");
			printf("\t2.��ʾͼ����Ϣ:\n");
			printf("\t3.����ͼ����Ϣ:\n");
			printf("\t4.����ͼ����Ϣ:\n");
			printf("\t5.�޸�ͼ����Ϣ:\n");
			printf("\t6.ɾ��ͼ����Ϣ:\n");
			printf("\t7.����ͼ����Ϣ:\n");
			printf("\t0.�˳�ϵͳ:\n");
			printf("\n**********************************************\n");
			scanf("%d",&choice);
			switch (choice) 
			{
			case 0:
				printf("�������˳�ͼ����Ϣ����ϵͳ.\n���沢�˳������� 1.\n�������˳������� 2.\nȡ���˳������� 3.\n");
				scanf("%d", &choice);
				if (choice == 1) {
					Write_Data(L);
				}
				if (choice == 3) {
					continue;
				}
				flag = 0; break;
			case 1:
				Add_Data(&L);
				Show_Data(L);
				Sleep(700);
				break;
			case 2:
				if (L == NULL) {
					printf("�����������!\n");
					continue;
				}
				Show_Data(L);
				Sleep(700);
				break;
			case 3:
				if (L == NULL)
				{
					printf("�����������!\n");continue;
				}
				Write_Data(L);
				break;
			case 4:
				if (L == NULL) {
					printf("�����������!\n");
					continue;
				}
				printf("�������Ӧ����ѡ��������ͣ�1 ���������ң� 2 ������������, 3 �����淽���Ʋ��ң�4 ���۸���ҡ�\n");
				scanf("%d", &type);
				scanf("%*[^\n]");
				scanf("%*c");
				printf("������Ҫ���ҵ��������ݣ������������������淽�����߼۸񣩣�\n");
				get_data(strtext, 64);
				if (!(p = Find_Data(L, type, strtext))) {
					printf("û���ҵ����:\n");
					continue;
				}
				printf("���ҽ��:\n");
				do {
					printf("��ţ�%d�� ͼ������%s�� ���ߣ�%s�� ���淽��%s�� �۸�%s�� ����λ�ã�%s.\n", \
						p->sequence, p->title, p->author_name, p->publisher, p->price, p->location);
					p = p->next;
				} while (p = Find_Data(p, type, strtext));
				Sleep(700);
				break;
			case 5:
				if (L == NULL) {
					printf("�����������!\n");continue;
				}
				printf("������Ҫ�޸ĵ�ͼ����Ϣ��ţ�\n");
				scanf("%d", &choice);
				Modify_Data(L, choice);
				Show_Data(L);
				Sleep(700);
				break;
			case 6:
				if (L == NULL) {
					printf("�����������!\n");continue;
				}
				printf("�������Ӧ����ѡ��ɾ���������ݣ�\n0 �����ɾ���� 1 ������ɾ���� 2 ��������ɾ���� 3 �����淽����ɾ���� 4 ���۸�ɾ��\n");
				printf("�뾡�������ɾ������������ȷɾ��������ɾ��ǰ��֤����ͼ����Ų��ظ����ɽ��������ܰ�����������\n");
				scanf("%d", &type);
				scanf("%*[^\n]");
				scanf("%*c");
				if (!type) {
					printf("������Ҫɾ��ͼ����Ϣ����ţ�");
					get_data(strtext, 64);
					if (Delete_Data(&L, type, strtext))
						printf("ɾ���ɹ���\n");
					else
						printf("ɾ��ʧ��!\n");
				}
				else {
					printf("������Ҫɾ��ͼ����Ϣ���������ݣ������������������淽���ƻ��߼۸񣩣�\n");
					printf("���ڿ��ܴ��������������������淽�����������߼۸���ͬ�����ڶ�����¼��ֻ��ɾ��������һ������Ϣ�������ɾ��ָ����ĳ����¼����ô�밴���ɾ����\n");
					get_data(strtext, 64);
					if (Delete_Data(&L, type, strtext))
						printf("ɾ���ɹ���\n");
					else
						printf("ɾ��ʧ��!\n");
				}
				Show_Data(L);
				Sleep(700);
				break;
			case 7:
				if (L == NULL) {
					printf("�����������!\n");continue;
				}
				printf("�������Ӧ����ѡ���������\n1 ���������� 2 ������������ 3 �����淽�������� 4 ���۸����� 5 ������λ������\n");
				scanf("%d", &choice);
				Sort_Data(L, choice);
				Show_Data(L);
				Sleep(700);
				break;
			default: break;
			}
		}
	}
#endif
int main(void)
{
	printf("\n***********��ӭ����ͼ����Ϣ����ϵͳ***********\n");
	menu();
	printf("\n*****�˳�ϵͳ*****\n");
	return 0;
}