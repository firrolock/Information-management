#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Book  
{
	char title[64];
	char author_name[32];
	char publisher[32];
	char price[16];
	struct Book *next;
}Book;
#if 1
void Read_Data(Book **pp, FILE *fp)
{

	//读取数据并创建链表
	Book *p;
	p = (Book *)malloc(sizeof(Book));
	p->next=NULL;
	/*fseek(fp,0,2);//文件末
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
	//图书信息添加
	char c = 0;
	int cnt = 1;
	Book *p = NULL;
	while (1) {
		printf("请添加第%d本图书信息。按任意键继续（不添加请输入'q'退出）...\n", cnt);
		scanf("%c", &c);
		if (c == 'q') {
			return ;
		}
		p = (Book *)malloc(sizeof(Book));
		printf("请输入书名：");
		get_data(p->title, 64);
		printf("请输入作者名：");
		get_data(p->author_name, 32);
		printf("请输入出版方名称：");
		get_data(p->publisher, 32);
		printf("请输入图书价格：");
		get_data(p->price, 16);
		p->next = *pp;
		*pp = p;
		cnt++;
	}
}
void Write_Data(const Book *p)
{
	FILE *fp = NULL;
	//图书信息保存
	if ((fp = fopen("hc.txt", "w")) == NULL)
	{
		printf("创建文件失败，请重新保存");
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
	//图书信息显示
	while(p)
	{
		printf("图书名：%s， 作者：%s， 出版方：%s， 价格：%s.\n",p->title,p->author_name,p->publisher,p->price);
		p=p->next;
	}
}
int Delete_Data(Book **pp, int type, const char *str)
{
	Book *p = *pp;
	Book *p_first = NULL, *p_mid = NULL, *p_last = NULL;
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
Book *Find_Data(const Book *p, int type, const char *str)
{
	//图书信息查找
	Book *s=NULL;
	if(type==1)//按书名查
	{
		while(p)
		{
			if(!strcmp(p->title,str))
				break;
			p=p->next;
		}
		s=p;
	}
	if(type==2)//按作者名查
	{
		while(p)
		{
			if(!strcmp(p->author_name,str))
				break;
			p=p->next;
		}
		s=p;
	}
	if (type == 3)//按出版方名称查
	{
		while (p)
		{
			if (!strcmp(p->publisher, str))
				break;
			p = p->next;
		}
		s = p;
	}
	if (type == 4)//按价格查
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
	char title[64];
	char author_name[32];
	char publisher[32];
	char price[16];
	strcpy(title, p1->next->title);
	strcpy(author_name, p1->next->author_name);
	strcpy(publisher, p1->next->publisher);
	strcpy(price, p1->next->price);  //1
	strcpy(p1->next->title, p1->title);
	strcpy(p1->next->author_name, p1->author_name);
	strcpy(p1->next->publisher, p1->publisher);
	strcpy(p1->next->price, p1->price);  //2
	strcpy(p1->title, title);
	strcpy(p1->author_name, author_name);
	strcpy(p1->publisher, publisher);
	strcpy(p1->price, price);  //3
	return;
}
void Sort_Data(Book *p, int group) {  //1 title, 2 author_name, 3 publisher, 4 price
	Book *p1, *p_tmp;
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
			p1=p1->next;
		}
		num--;
	}
	return ;
}
void menu()
	{
		Book *L=NULL,*p=NULL;
		FILE *fp=NULL;
		int choice = 0,flag = 1;
		char type,title;
		char strtext[64];
		//文件不存在
		if((fp=fopen("hc.txt","r"))==NULL)
		{
			printf("没有文件，请添加图书信息\n");
		}
		//文件存在
		else {
			Read_Data(&L, fp);
			fclose(fp);
		}
		while(flag)
		{
			printf("\n********欢迎进入图书信息管理系统********\n");
			printf("输入对应数字以进入系统具体功能\n");
			printf("1.添加图书信息:\n");
			printf("2.显示图书信息:\n");
			printf("3.保存图书信息:\n");
			printf("4.查找图书信息:\n");
			printf("5.删除图书信息:\n");
			printf("6.排序图书信息:\n");
			printf("0.退出系统:\n");
			scanf("%d",&choice);
			switch(choice)
			{
			case 0: flag = 0; break;
			case 1: Add_Data(&L); break;
			case 2: if(L==NULL )
				    { printf("请先添加数据!\n");continue;}
				    Show_Data(L); break;
			case 3:
				if(L==NULL )
				{   printf("请先添加数据!\n");continue;}
				Write_Data(L);
				break;
			case 4:
				if (L == NULL) {
					printf("请先添加数据!\n");continue;
				}
				   printf("请输入对应数字选择查找类型：1 按书名查找， 2 按作者名查找, 3 按出版方名称查找，4 按价格查找。\n");
				   scanf("%d", &type);
				   scanf("%*[^\n]");
				   scanf("%*c");
				   printf("请输入要查找的类型内容（书名、作者名、出版方名或者价格）：\n");
				   get_data(strtext, 64);
				   p = Find_Data(L, type, strtext);
				   if (p != NULL)
				   {
					   printf("查找结果:\n");
					   printf("图书名：%s， 作者：%s， 出版方：%s， 价格：%s.\n", p->title, p->author_name, p->publisher, p->price);
				   }
				   else
					   printf("没有找到结果:\n");
				   break;
			case 5: 
				if (L == NULL) {
					printf("请先添加数据!\n");continue;
				}
				   printf("请输入对应数字选择删除类型依据：1 按书名删除， 2 按作者名删除， 3 按出版方名称删除， 4 按价格删除\n");
				   scanf("%d", &type);
				   scanf("%*[^\n]");
				   scanf("%*c");
				   printf("请输入要删除图书信息的类型内容（书名、作者名、出版方名或者价格）：\n");
				   get_data(strtext, 64);
				   if (Delete_Data(&L, type, strtext))
					   printf("删除成功！\n");
				   else
					   printf("删除失败!\n");
				   break;
			case 6: 
				   if(L==NULL )
					   {   printf("请先添加数据!\n");continue;}
				   printf("请输入对应数字选择排序类别：1 按书名排序， 2 按作者排序， 3 按出版方排序， 4 按价格排序\n");
				   scanf("%d", &choice);
				   Sort_Data(L, choice);break;
			default: break;
			}
		}
	}
#endif
int main()
{
	menu();
	printf("退出系统\n");
	return 0;
}