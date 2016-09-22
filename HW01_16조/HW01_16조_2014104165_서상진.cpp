#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
	char *wd;												//����� �ܾ�
	struct Node *next;										//���� ���
}Node;
Node *Head = NULL;											//���� ù ���
int index = 0;												//���° �ε����� �ִ� �ܾ����� �˻��ϱ� ����


void Link(char *S)
{
	Node *temp;												//��� �߰��� ���� �ӽ� ���
	Node *link = Head;										//��尡 ���Ե� ����Ʈ
	link = (Node*)malloc(sizeof(Node));
	link->wd = (char*)malloc((sizeof(S) + 1));
	link->next = NULL;
	strcpy(link->wd, S);

	if (Head == NULL)										//Head�� ����������, �ٷ� ���� ����
	{
		Head = link;
	}

	else
	{
		temp = Head;										//���� ��� ����
		while (temp != NULL)								//next�� NULL�̸� ������ list�� ������, ���� �ű⿡ link �ܾ ����
		{
			if (temp->next == NULL)
			{
				link->next = temp->next;
				temp->next = link;
				return;
			}
			temp = temp->next;
		}
	}
}

Node *Search(char *word)									//���ϴ� �ܾ� �˻� �Լ�
{
	Node *Find = Head;
	while (Find)
	{
		index++;
		if (strcmp(word, Find->wd) == 0)					//strcmp : 2���� ���ڿ��� �������, 0 ��ȯ
		{
			printf("%s\n", Find->wd);
			printf("ã�� �ܾ�� %d��° index�� ����\n", index);	//���° index�� ã�� �ܾ �ִ��� ���
		}
		Find = Find->next;
	}
	return 0;
}

void main()
{
	char Get;												//�޾ƿ� �ܾ�
	char Save[300];											//����� �迭
	char word[100];											//ã����� �ܾ�
	int x = 0;

	FILE *fp;
	fp = fopen("HW01.txt", "r");

	if (fp == NULL)
	{
		printf("txt ���� ����");
	}

	else
	{
		while (1)											//������ ���� �ɶ����� �ݺ�
		{
			Get = fgetc(fp);
			if (isalpha((char)Get))
			{
				Save[x] = Get;								//�迭�� �ܾ� �����, ���� �迭��
				x++;
			}

			else
			{
				if (x)
				{
					Save[x] = '\0';							//Null���� Save�� �־��� ( �ܾ��� ���� )
					Link(Save);								//����Ʈ�� �ֱ� ���� �Լ� ȣ��
					x = 0;									//�ܾ ����Ʈ�� �־�����, �ٽ� �ܾ �޾���
				}
			}
			if (Get == EOF)
				break;
		}
	}
	printf("�˻��� �ܾ� : ");
	scanf("%s", &word);
	printf("\n");
	Search(word);
	printf("\n");
	fclose(fp);
}

