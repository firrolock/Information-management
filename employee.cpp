#include <iostream>
#include <cstring>
using namespace std;

void get_data(char *buf, int size) {
	fgets(buf, size, stdin);
	if (buf[strlen(buf) - 1] != '\n') {
		scanf("%*[^\n]");
		scanf("%*c");
	}
	else {
		buf[strlen(buf) - 1] = 0;
	}
	return ;
}
void get_data(string &buf) {
	getline(cin, buf);
	return ;
}
class member {
public:
	member(void) {
		sequence = 0;
		number = 0;
		name = "\0";
		wage = 0;
	}
	void salary(double wage1, float days) {
		double primary_wage = wage1 * days / 23.0;
		wage = primary_wage + primary_wage / 2;
		return ;
	}
	void set_member(int num1, int num2, const string &name1) {
		sequence = num1;
		number = num2;
		name = name1;
		return ;
	}
	void set_info(int num, string str, double wage0) {
		number = num;
		name = str;
		wage = wage0;
		return ;
	}
	int get_sequence(void) {
		return sequence;
	}
	int &get_number(void) {
		return number;
	}
	string &get_name(void) {
		return name;
	}
	double &get_wage(void) {
		return wage;
	}
	void print(void) {
		cout << "sequence: " << sequence << "\twork_number: " << number\
			<< "\tname: " << name << "\twage: " << wage << endl;
		return ;
	}
private:	
	int sequence;
	int number;
	string name;
	double wage;
};
//callback function cannot be used in class
	void swap_member_cb(member *p1, member *p2) {
		swap(p1->get_number(), p2->get_number());
		swap(p1->get_name(), p2->get_name());
		swap(p1->get_wage(), p2->get_wage());
		return ;
	}
class Employee {
public:
	void add_member(int number, const string &name0,\
		   	double wage, float days) {
		int i = 0;
		for (i = 0; i <= 99; i++) {
			if (!employee[i].get_sequence()) {
				employee[i].salary(wage, days);
				employee[i].set_member(i + 1, number, name0);
				break;
			}
		}
		if (i >= 100) {
			printf("employees in this company are full...\n");
		}
		return ;
	}
	void add_member(void) {
		char choice = 0;
		int number = 0;
		float days = 0;
		double wage = 0;
		char buf[20] = {0};
		string name = "\0";
		do {
				printf("enter the imformation about the employee. \n");
				printf("work number(beyond 10000): ");
				scanf("%d", &number);
				printf("name: ");
				scanf("%*[^\n]");
				scanf("%*c");
				//get_data(const_cast<char *>(name.c_str()), 20);
				get_data(name);
				/*fgets(buf, 20, stdin);
				if (buf[strlen(buf) - 1] != '\n') {
					scanf("%*[^\n]");
					scanf("%*c");
				}
				else {
					buf[strlen(buf) - 1] = 0;
				}
				strcpy(const_cast<char *>(name.c_str()), buf);*/  //\
				strcpy fails
				printf("given salary: ");
				scanf("%lf", &wage);
				printf("attend days(0.0~23.0): ");
				scanf("%f", &days);
				add_member(number, name, wage, days);
				printf("continue to enter the imformation of another employee press any key, or 'q' to quit.\n");
				cin >> choice;
		} while (choice != 'q');
		return ;
	}
	void sort_member(int num, void (*func)(member *, member *)) {
		int i = 0;
		int size = 0;
		for (i = 0; i <= 99; i++) {
			if (!employee[i].get_sequence()) {
				break;
			}
		}
		for (size = i; size >= 2; size--) {
			for (i = 0; i <= size - 2; i++) {
				switch (num) {
					case 1:
						if (employee[i].get_number() > \
								employee[i + 1].get_number()) {
							func(employee + i, employee + i + 1);
						}
						break;
					case 2:
						if (employee[i].get_name() > \
								employee[i + 1].get_name()) {
							func(employee + i, employee + i + 1);
						}
						break;
					case 3:
						if (employee[i].get_wage() > \
								employee[i + 1].get_wage()) {
							func(employee + i, employee + i + 1);
						}
						break;
				}
			}
		}
		return ;
	}
	void sort_member(void) {
		int choice = 0;
		printf("Enter the type which you want to sort on: \n");
		cout << "1. work_number\t" << "2. name\t" << "3. wage\n";
		cin >> choice;
		switch (choice) {
			case 1:
				sort_member(1, swap_member_cb);
				break;
			case 2:
				sort_member(2, swap_member_cb);
				break;
			case 3:
				sort_member(3, swap_member_cb);
				break;
		}
		return ;
	}
	void print(void) {
		cout << "All company employees listed here: " << endl;
		for (int i = 0; i <= 99; i++) {
			if (!employee[i].get_sequence()) {
				break;
			}
			(employee + i)->print();
		}
		return ;
	}
private:
	member employee[100];
};
int main(void) {
	short choice = 0;
	Employee emp;
	while (1) {
	printf("\nPlease enter the number to select the function: \n to add members press '1', to print members press '2', to sort members press '3', or '0' to quit the program.\n");
		scanf("%hd", &choice);
		if (!choice) {
			break;
		}
		if (choice == 1) {
			emp.add_member();
		}
		if (choice == 2) {
			emp.print();
		}
		if (choice == 3) {
			emp.sort_member();
		}
	}
	return 0;
}
