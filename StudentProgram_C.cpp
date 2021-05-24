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
		printf("*   학생 관리 시스템   *\n");
		printf("*----------------------*\n");
		printf("*1. 학생 등록           \n");
		printf("*2. 학생 삭제           \n");
		printf("*3. 학생 출력           \n");
		printf("*4. 저장                \n");
		printf("*5. 불러오기            \n");
		printf("                 종료:6 \n");
		printf("*----------------------*\n");

		printf("원하시는 작업을 입력하시오>");

		scanf_s("%d", &select);

		fflush(stdin);

		switch (select) {
		case 1:
			printf("\n학생 등록을 선택하셨습니다.");
			printf("\n학생 정보를 예시와 같이 입력하시오.");
			printf("\n예시)홍길동 092827 전자공학과\n");
			insert(ptr);
			break;
		case 2:
			printf("\n학생 삭제를 선택하셨습니다.");
			printf("\n삭제할 학번을 입력해주십시오.\n");
			del(ptr);
			break;
		case 3:
			printf("\n학생 출력을 선택하셨습니다.");
			printf("\n현재 등록된 주소록은 아래와 같습니다.\n");
			display(ptr->link);
			break;
		case 4:
			printf("\n저장을 선택하셨습니다.");
			printf("\n지금까지의 주소록을 아래의 경로에 저장합니다 . . . \n");
			save(ptr->link);
			break;
		case 5:
			printf("\n불러오기를 선택하셨습니다.");
			printf("\n저장한 주소록을 불러옵니다 . . . \n");
			load(ptr);
			break;
		case 6:
			printf("\n종료합니다.\n");
			break;
		default:
			printf("\n\n잘못된 키 입력입니다.\n\n");
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

		printf("이름: ");
		scanf_s("%s", ptr->name, sizeof(ptr->name));
		fflush(stdin);
		printf("학번: ");
		scanf_s("%s", ptr->SN, sizeof(ptr->SN));
		fflush(stdin);
		printf("과: ");
		scanf_s("%s", ptr->SD, sizeof(ptr->SD));
		fflush(stdin);
		printf("\n*등록 완료되었습니다.*");
		for (;;) {
			printf("\n계속 등록하시겠습니까?(Y or N):");
			scanf_s(" %c", &re);

			fflush(stdin);
			if (re != 'Y' && re != 'y' && re != 'N' && re != 'n') {
				printf("\n다른 값을 입력하셨습니다. Y 혹은 N을 선택해주십시오.\n");
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
	printf("삭제할 사람의 이름 :");
	scanf_s(" %s", name1, 20);
	fflush(stdin);

	while (ptr->link != NULL) {
		temp = ptr;
		ptr = ptr->link;
		if (strcmp(name1, ptr->name) == 0) {
			temp->link = ptr->link;
			free(ptr);
			printf("\n삭제 되었습니다.\n");
			break;
		}
		else {
			printf("\n등록되지 않은 이름입니다.\n");
		}
	}
	return;
}


void display(student* ptr) {
	student* left;
	student* right;


	system("cls");
	printf("정렬 순서를 선택해주세요. (1:오름차순, 2:내림차순)>>");
	scanf_s("%d", &p);
	printf("정렬 방법을 선택해주세요. (1:이름, 2:학번, 3:학과)>>");
	scanf_s("%d", &q);

	if (p == 1) {
		sort1(ptr);
	}
	else if (p == 2) {
		sort2(ptr);
	}
	else printf("\n잘못된 키를 입력하셨습니다. 오름차순, 내림차순을 1,2를 눌러 선택해주세요.\n");


	printf("\n<<<<학생 명단>>>>\n");
	printf("%-15s", "이름");
	printf("%-20s", "학번");
	printf("%-25s", "학과");
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
		printf("파일이 성공적으로 열림\n");
	}
	else {
		printf("파일이 제대로 열리지 않음\n");
	}
	while (ptr != NULL) {
		fprintf_s(sa, "%s %s %s", ptr->name, ptr->SN, ptr->SD);
		fprintf_s(sa, "\n");
		ptr = ptr->link;
	}
	filecon = fclose(sa);
	if (filecon != EOF) {
		printf("파일이 성공적으로 저장됨\n");
	}
	else {
		printf("파일이 제대로 저장되지 않음\n");
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
	printf("정렬을 진행중입니다.\n");
	if (q == 1) {
		while (temp1->link != NULL)//버블 소트
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
	printf("정렬을 진행중입니다.\n");
	if (q == 1) {
		while (temp1->link != NULL)//버블 소트
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

