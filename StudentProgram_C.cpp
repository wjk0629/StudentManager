#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
	char name[20];
	char SN[10];
	char SD[25];
	struct student* link;
};
typedef struct student student;

void insert(student*);
void del(student*);
void display(student*);
void save(student*);
void load(student*);
void sort1(student*);
void sort2(student*);
int p, q;



int main(void) {
	student* ptr;
	int select;
	ptr = (student*)malloc(sizeof(student));
	ptr->link = NULL;
	do {
		printf("*----------------------*\n");
		printf("*   �л� ���� �ý���   *\n");
		printf("*----------------------*\n");
		printf("*1. �л� ���           \n");
		printf("*2. �л� ����           \n");
		printf("*3. �л� ���           \n");
		printf("*4. ����                \n");
		printf("*5. �ҷ�����            \n");
		printf("                 ����:6 \n");
		printf("*----------------------*\n");

		printf("���Ͻô� �۾��� �Է��Ͻÿ�>");

		scanf_s("%d", &select);

		fflush(stdin);

		switch (select) {
		case 1:
			printf("\n�л� ����� �����ϼ̽��ϴ�.");
			printf("\n�л� ������ ���ÿ� ���� �Է��Ͻÿ�.");
			printf("\n����)ȫ�浿 092827 ���ڰ��а�\n");
			insert(ptr);
			break;
		case 2:
			printf("\n�л� ������ �����ϼ̽��ϴ�.");
			printf("\n������ �й��� �Է����ֽʽÿ�.\n");
			del(ptr);
			break;
		case 3:
			printf("\n�л� ����� �����ϼ̽��ϴ�.");
			printf("\n���� ��ϵ� �ּҷ��� �Ʒ��� �����ϴ�.\n");
			display(ptr->link);
			break;
		case 4:
			printf("\n������ �����ϼ̽��ϴ�.");
			printf("\n���ݱ����� �ּҷ��� �Ʒ��� ��ο� �����մϴ� . . . \n");
			save(ptr->link);
			break;
		case 5:
			printf("\n�ҷ����⸦ �����ϼ̽��ϴ�.");
			printf("\n������ �ּҷ��� �ҷ��ɴϴ� . . . \n");
			load(ptr);
			break;
		case 6:
			printf("\n�����մϴ�.\n");
			break;
		default:
			printf("\n\n�߸��� Ű �Է��Դϴ�.\n\n");
		}
	} while (select != 6);
}



void insert(student* ptr) {
	char re;
	student* temp;
	fflush(stdin);
	temp = ptr->link;
	do {
		ptr->link = (student*)malloc(sizeof(student));
		ptr = ptr->link;

		printf("�̸�: ");
		scanf_s("%s", ptr->name, sizeof(ptr->name));
		fflush(stdin);
		printf("�й�: ");
		scanf_s("%s", ptr->SN, sizeof(ptr->SN));
		fflush(stdin);
		printf("��: ");
		scanf_s("%s", ptr->SD, sizeof(ptr->SD));
		fflush(stdin);
		printf("\n*��� �Ϸ�Ǿ����ϴ�.*");
		for (;;) {
			printf("\n��� ����Ͻðڽ��ϱ�?(Y or N):");
			scanf_s(" %c", &re);

			fflush(stdin);
			if (re != 'Y' && re != 'y' && re != 'N' && re != 'n') {
				printf("\n�ٸ� ���� �Է��ϼ̽��ϴ�. Y Ȥ�� N�� �������ֽʽÿ�.\n");
				continue;
			}
			else
				break;
		}
	} while (re != 'n' && re != 'N');
	ptr->link = NULL;
	if (temp != NULL) {
		ptr->link = temp;

	}
	printf("\n");
}



void del(student* ptr) {
	student* temp;
	char name1[20];
	printf("������ ����� �̸� :");
	scanf_s(" %s", name1, 20);
	fflush(stdin);

	while (ptr->link != NULL) {
		temp = ptr;
		ptr = ptr->link;
		if (strcmp(name1, ptr->name) == 0) {
			temp->link = ptr->link;
			free(ptr);
			printf("\n���� �Ǿ����ϴ�.\n");
			break;
		}
		else {
			printf("\n��ϵ��� ���� �̸��Դϴ�.\n");
		}
	}
	return;
}


void display(student* ptr) {
	student* left;
	student* right;


	system("cls");
	printf("���� ������ �������ּ���. (1:��������, 2:��������)>>");
	scanf_s("%d", &p);
	printf("���� ����� �������ּ���. (1:�̸�, 2:�й�, 3:�а�)>>");
	scanf_s("%d", &q);

	if (p == 1) {
		sort1(ptr);
	}
	else if (p == 2) {
		sort2(ptr);
	}
	else printf("\n�߸��� Ű�� �Է��ϼ̽��ϴ�. ��������, ���������� 1,2�� ���� �������ּ���.\n");


	printf("\n<<<<�л� ���>>>>\n");
	printf("%-15s", "�̸�");
	printf("%-20s", "�й�");
	printf("%-25s", "�а�");
	printf("\n\n");
	while (ptr != NULL) {

		printf("%-15s", ptr->name);
		printf("%-20s", ptr->SN);
		printf("%-25s", ptr->SD);
		ptr = ptr->link;
		printf("\n");
	}
	printf("\n");
	return;
}



void save(student* ptr) {
	FILE* sa;
	int filecon;
	fopen_s(&sa, "C:\\Users\\PC\\source\\repos\\Project1\\test.txt", "w");
	if (sa != NULL) {
		printf("������ ���������� ����\n");
	}
	else {
		printf("������ ����� ������ ����\n");
	}
	while (ptr != NULL) {
		fprintf_s(sa, "%s %s %s", ptr->name, ptr->SN, ptr->SD);
		fprintf_s(sa, "\n");
		ptr = ptr->link;
	}
	filecon = fclose(sa);
	if (filecon != EOF) {
		printf("������ ���������� �����\n");
	}
	else {
		printf("������ ����� ������� ����\n");
	}
	return;
}


void load(student* ptr) {
	FILE* fp;
	int filecon2;
	fopen_s(&fp, "C:\\Users\\PC\\source\\repos\\Project1\\test.txt", "r");
	do {
		ptr->link = (student*)malloc(sizeof(student));
		ptr = ptr->link;

		fscanf_s(fp, "%s %s %s\n", ptr->name, sizeof(ptr->name), ptr->SN, sizeof(ptr->SN), ptr->SD, sizeof(ptr->SD));
		printf("%s %s %s\n", ptr->name, ptr->SN, ptr->SD);
		fflush(stdin);
		ptr->link = NULL;
	} while (feof(fp) == 0);
	filecon2 = fclose(fp);

	printf("\n");
}


void sort1(student* ptr)
{
	student* temp1;
	student* temp2;
	char str[20];
	char tmp[10];
	char tmp2[25];

	temp1 = ptr;
	printf("������ �������Դϴ�.\n");
	if (q == 1) {
		while (temp1->link != NULL)//���� ��Ʈ
		{
			temp2 = temp1->link;
			while (temp2 != NULL)
			{
				if (strcmp(temp1->name, temp2->name) > 0)
				{
					strcpy_s(str, sizeof(temp1->name), temp1->name);
					strcpy_s(temp1->name, sizeof(temp2->name), temp2->name);
					strcpy_s(temp2->name, sizeof(str), str);

					strcpy_s(tmp, sizeof(temp1->SN), temp1->SN);
					strcpy_s(temp1->SN, sizeof(temp2->SN), temp2->SN);
					strcpy_s(temp2->SN, sizeof(tmp), tmp);

					strcpy_s(tmp2, sizeof(temp1->SD), temp1->SD);
					strcpy_s(temp1->SD, sizeof(temp2->SD), temp2->SD);
					strcpy_s(temp2->SD, sizeof(tmp2), tmp2);

				}
				temp2 = temp2->link;
			}

			temp1 = temp1->link;
		}

	}
	else if (q == 2) {
		while (temp1->link != NULL)
		{
			temp2 = temp1->link;
			while (temp2 != NULL)
			{
				if (strcmp(temp1->SN, temp2->SN) > 0)
				{
					strcpy_s(str, sizeof(temp1->name), temp1->name);
					strcpy_s(temp1->name, sizeof(temp2->name), temp2->name);
					strcpy_s(temp2->name, sizeof(str), str);

					strcpy_s(tmp, sizeof(temp1->SN), temp1->SN);
					strcpy_s(temp1->SN, sizeof(temp2->SN), temp2->SN);
					strcpy_s(temp2->SN, sizeof(tmp), tmp);

					strcpy_s(tmp2, sizeof(temp1->SD), temp1->SD);
					strcpy_s(temp1->SD, sizeof(temp2->SD), temp2->SD);
					strcpy_s(temp2->SD, sizeof(tmp2), tmp2);

				}
				temp2 = temp2->link;
			}

			temp1 = temp1->link;
		}
	}
	else {
		while (temp1->link != NULL)
		{
			temp2 = temp1->link;
			while (temp2 != NULL)
			{
				if (strcmp(temp1->SD, temp2->SD) > 0)
				{
					strcpy_s(str, sizeof(temp1->name), temp1->name);
					strcpy_s(temp1->name, sizeof(temp2->name), temp2->name);
					strcpy_s(temp2->name, sizeof(str), str);

					strcpy_s(tmp, sizeof(temp1->SN), temp1->SN);
					strcpy_s(temp1->SN, sizeof(temp2->SN), temp2->SN);
					strcpy_s(temp2->SN, sizeof(tmp), tmp);

					strcpy_s(tmp2, sizeof(temp1->SD), temp1->SD);
					strcpy_s(temp1->SD, sizeof(temp2->SD), temp2->SD);
					strcpy_s(temp2->SD, sizeof(tmp2), tmp2);

				}
				temp2 = temp2->link;
			}

			temp1 = temp1->link;
		}
	}
}

void sort2(student* ptr)
{
	student* temp1;
	student* temp2;
	char str[20];
	char tmp[10];
	char tmp2[25];

	temp1 = ptr;
	printf("������ �������Դϴ�.\n");
	if (q == 1) {
		while (temp1->link != NULL)//���� ��Ʈ
		{
			temp2 = temp1->link;
			while (temp2 != NULL)
			{
				if (strcmp(temp1->name, temp2->name) < 0)
				{
					strcpy_s(str, sizeof(temp1->name), temp1->name);
					strcpy_s(temp1->name, sizeof(temp2->name), temp2->name);
					strcpy_s(temp2->name, sizeof(str), str);

					strcpy_s(tmp, sizeof(temp1->SN), temp1->SN);
					strcpy_s(temp1->SN, sizeof(temp2->SN), temp2->SN);
					strcpy_s(temp2->SN, sizeof(tmp), tmp);

					strcpy_s(tmp2, sizeof(temp1->SD), temp1->SD);
					strcpy_s(temp1->SD, sizeof(temp2->SD), temp2->SD);
					strcpy_s(temp2->SD, sizeof(tmp2), tmp2);

				}
				temp2 = temp2->link;
			}

			temp1 = temp1->link;
		}

	}
	else if (q == 2) {
		while (temp1->link != NULL)
		{
			temp2 = temp1->link;
			while (temp2 != NULL)
			{
				if (strcmp(temp1->SN, temp2->SN) < 0)
				{
					strcpy_s(str, sizeof(temp1->name), temp1->name);
					strcpy_s(temp1->name, sizeof(temp2->name), temp2->name);
					strcpy_s(temp2->name, sizeof(str), str);

					strcpy_s(tmp, sizeof(temp1->SN), temp1->SN);
					strcpy_s(temp1->SN, sizeof(temp2->SN), temp2->SN);
					strcpy_s(temp2->SN, sizeof(tmp), tmp);

					strcpy_s(tmp2, sizeof(temp1->SD), temp1->SD);
					strcpy_s(temp1->SD, sizeof(temp2->SD), temp2->SD);
					strcpy_s(temp2->SD, sizeof(tmp2), tmp2);

				}
				temp2 = temp2->link;
			}

			temp1 = temp1->link;
		}
	}
	else {
		while (temp1->link != NULL)
		{
			temp2 = temp1->link;
			while (temp2 != NULL)
			{
				if (strcmp(temp1->SD, temp2->SD) < 0)
				{
					strcpy_s(str, sizeof(temp1->name), temp1->name);
					strcpy_s(temp1->name, sizeof(temp2->name), temp2->name);
					strcpy_s(temp2->name, sizeof(str), str);

					strcpy_s(tmp, sizeof(temp1->SN), temp1->SN);
					strcpy_s(temp1->SN, sizeof(temp2->SN), temp2->SN);
					strcpy_s(temp2->SN, sizeof(tmp), tmp);

					strcpy_s(tmp2, sizeof(temp1->SD), temp1->SD);
					strcpy_s(temp1->SD, sizeof(temp2->SD), temp2->SD);
					strcpy_s(temp2->SD, sizeof(tmp2), tmp2);

				}
				temp2 = temp2->link;
			}

			temp1 = temp1->link;
		}
	}
}

