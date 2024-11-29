#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct phonenum{
	char name[9];
	char num[14];
	int year;
	struct phonenum* link;
};


void listlook(struct phonenum* link);
void search(struct phonenum* link, struct phonenum** onlink);
void add(struct phonenum* live, struct phonenum** onlive, struct phonenum** onroot);
void update(struct phonenum* link);
void del(struct phonenum* link, struct phonenum** onlink);
void off(struct phonenum* link);


int main() {
	struct phonenum* root;
	struct phonenum* pre=NULL;
	struct phonenum* live;
	struct phonenum** onroot;
	struct phonenum** onlive;
	FILE* fp;
	int select = 0;

	fp = fopen("D:\\c����\\phone\\num.txt","rt");
	
	if (fp == NULL) {
		fp = fopen("D:\\c����\\phone\\num.txt", "w+t");
		live = (struct phonenum*)malloc(sizeof(struct phonenum));
		printf("ó�� ����Ͻô±���!\nó���߰��� �����͸� �Է��ϼ���(�̸� ��ȭ��ȣ(-����) ����⵵) : ");
		scanf("%s %s %d",live->name ,live->num, &live->year);
		fprintf(fp, "%s %s %d", live->name, live->num, live->year);
		free(live);
		fclose(fp);
		fp = fopen("D:\\c����\\phone\\num.txt", "rt");
	}
	root = NULL;
	live = NULL;

	while (!feof(fp)) {
		live = (struct phonenum*)malloc(sizeof(struct phonenum));
		fscanf(fp,"%s %s %d\n",live->name,live->num,&live->year);
		live->link = NULL;
		if (root == NULL){
			root = live;
		}
		else {
			pre->link = live;
		}
		pre = live;
	}
	onroot = &root;
	onlive = &live;
	do{
		printf("�޴�(���ڸ��Է�)\n1.��ü���ǥ��\n2.�˻�\n3.�߰�\n4.����\n5.����\n6.����\n");
		scanf("%d", &select);
		switch (select) {
		case 1:
			listlook(root);
			break;
		case 2:
			search(root,onroot);
			break;
		case 3:
			add(live,onlive,onroot);
			break;
		case 4:
			update(root);
		case 5:
			del(root,onroot);
			break;
		case 6:
			fclose(fp);
			off(root);
			break;
		default:
			break;
		}
	} while (select != 6);

	while (root!=NULL) {
		live = root->link;
		free(root);
		root = live;
	}
	return 0;
}

void listlook(struct phonenum* link) {
	while (link!=NULL) {
		printf("%s %s %d\n", link->name, link->num, link->year);
		link = link->link;
	}
	printf("\n");
}
void search(struct phonenum* link, struct phonenum** onlink) {
	struct phonenum* pre=NULL;
	char search_text[9];
	int flag=0;
	int select=0;
	int con=0;
	int cut = 0;


	while (con!=2){
		flag = 0;
		con = 0;
		cut = 0;

		printf("������ ����ó�� �˻��Ͻðڽ��ϱ�? �̸��� �Է��ϼ��� : ");
		scanf("%s", search_text);
		
		while (link != NULL) {
			cut++;
			if (!strcmp(search_text, link->name)) {
				flag = 1;
				break;
			}
			pre = link;
			link = link->link;
		}
		if (flag) {
			printf("%s %s %d\n", link->name, link->num, link->year);
			printf("�� ����ó�� ������ �۾��� ���ϼ���\n1.����\n2.����\n3.����\n");
			scanf("%d", &select);

			switch (select) {
				case 1:
					printf("������ �����͸� �Է��ϼ���(�̸� ��ȭ��ȣ(-����) ����⵵) : ");
					scanf("%s %s %d", link->name, link->num, &link->year);
					break;
				case 2:
					if (cut == 1) {
						if (link->link == NULL) {
							*onlink = NULL;
							free(link);
							link = NULL;
						}
						else {
							*onlink = link->link;
							free(link);
							link = *onlink;
						}
					}
					else {
						if (link->link == NULL) {
							pre->link = NULL;
							free(link);
						}
						else {
							pre->link = link->link;
							free(link);
						}
					}
					break;
				case 3:
					break;
				default:
					continue;
			}
		}
		else {
			printf("%s�� ����ó�� ���������ʽ��ϴ�\n", search_text);
		}
		while (con != 1 && con != 2) {
			printf("��� �˻��ұ��?\n1.��\n2.�ƴϿ�\n");
			scanf("%d",&con);
		}
	}
}

void add(struct phonenum* live, struct phonenum** onlive, struct phonenum** onroot) {
	struct phonenum* new;
	int con=0;

	do{
		con = 0;
		new = (struct phonenum*)malloc(sizeof(struct phonenum));
		printf("�߰��� �����͸� �Է��ϼ���(�̸� ��ȭ��ȣ(-����) ����⵵) : ");
		scanf("%s %s %d", new->name, new->num, &new->year);
		new->link = NULL;
		if (*onroot == NULL) {
			*onroot = new;
		}
		else {
			live->link = new;
		}
		live = new;

		do {
			printf("��� �߰��ұ��?\n1.��\n2.�ƴϿ�\n");
			scanf("%d", &con);
		} while (con != 1 && con != 2);
	} while (con != 2);
	*onlive = live;
}
void update(struct phonenum* link) {
	char search_text[9];
	struct phonenum* pre;
	int flag=0;
	int con = 0;

	while (con!=2){
		flag = 0;
		con = 0;
		printf("������ ����ó�� �����Ͻðڽ��ϱ�? �̸��� �Է��ϼ��� : ");
		scanf("%s", search_text);
		while (link != NULL) {
			if (!strcmp(search_text, link->name)) {
				flag = 1;
				break;
			}
			pre = link;
			link = link->link;
		}
		if (flag) {
			printf("������ �����͸� �Է��ϼ���(�̸� ��ȭ��ȣ(-����) ����⵵) : ");
			scanf("%s %s %d", link->name, link->num, &link->year);
		}
		else {
			printf("%s�� ����ó�� ���������ʽ��ϴ� ", search_text);
		}
		while (con != 1 && con != 2) {
			printf("��� �����ұ��?\n1.��\n2.�ƴϿ�\n");
			scanf("%d", &con);
		}
	}
}
void del(struct phonenum* link, struct phonenum** onlink) {
	char search_text[9];
	struct phonenum* pre=NULL;
	int flag = 0;
	int con = 0;
	int cut = 0;

	do {
		flag = 0;
		con = 0;
		cut = 0;
		printf("������ ����ó�� �����Ͻðڽ��ϱ�? �̸��� �Է��ϼ��� : ");
		scanf("%s", search_text);
		while (link != NULL) {
			cut++;
			if (!strcmp(search_text, link->name)) {
				flag = 1;
				break;
			}
			pre = link;
			link = link->link;
		}
		if (flag){
			if (cut == 1) {
				if (link->link == NULL) {
					*onlink = NULL;
					free(link);
					link = NULL;
				}
				else {
					*onlink = link->link;
					free(link);
					link = *onlink;
				}
			}
			else {
				if (link->link == NULL) {
					pre->link = NULL;
					free(link);
				}
				else {
					pre->link = link->link;
					free(link);
				}
			}
		}
		else {
			printf("%s�� ����ó�� ���������ʽ��ϴ�", search_text);
		}
		while (con != 1 && con != 2) {
			printf("��� �����ұ��?\n1.��\n2.�ƴϿ�\n");
			scanf("%d", &con);
		}
	} while (con != 2);
}
void off(struct phonenum* link) {
	int select = 0;
	FILE* write;

	do{
		printf("���� �� ���� �Ͻðڽ��ϱ�?\n1.��\n2.�ƴϿ�\n");
		scanf("%d", &select);

		switch (select) {
		case 1:
			write = fopen("D:\\c����\\phone\\num.txt", "wt");
			while (link!=NULL){
				fprintf(write,"%s %s %d\n", link->name, link->num, link->year);
				link = link->link;
			}
			fclose(write);
			break;
		case 2:
			break;
		default:
			continue;
		}
	} while (select != 1 && select != 2);
}