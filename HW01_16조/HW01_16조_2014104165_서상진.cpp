#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
	char *wd;												//저장될 단어
	struct Node *next;										//다음 노드
}Node;
Node *Head = NULL;											//가장 첫 노드
int index = 0;												//몇번째 인덱스에 있는 단어인지 검색하기 위함


void Link(char *S)
{
	Node *temp;												//노드 추가를 위한 임시 노드
	Node *link = Head;										//노드가 삽입될 리스트
	link = (Node*)malloc(sizeof(Node));
	link->wd = (char*)malloc((sizeof(S) + 1));
	link->next = NULL;
	strcpy(link->wd, S);

	if (Head == NULL)										//Head가 비어있을경우, 바로 값을 삽입
	{
		Head = link;
	}

	else
	{
		temp = Head;										//더미 노드 생성
		while (temp != NULL)								//next가 NULL이면 무조건 list의 마지막, 따라서 거기에 link 단어를 연결
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

Node *Search(char *word)									//원하는 단어 검색 함수
{
	Node *Find = Head;
	while (Find)
	{
		index++;
		if (strcmp(word, Find->wd) == 0)					//strcmp : 2개의 문자열이 같을경우, 0 반환
		{
			printf("%s\n", Find->wd);
			printf("찾는 단어는 %d번째 index에 존재\n", index);	//몇번째 index에 찾는 단어가 있는지 출력
		}
		Find = Find->next;
	}
	return 0;
}

void main()
{
	char Get;												//받아올 단어
	char Save[300];											//저장될 배열
	char word[100];											//찾고싶은 단어
	int x = 0;

	FILE *fp;
	fp = fopen("HW01.txt", "r");

	if (fp == NULL)
	{
		printf("txt 파일 없음");
	}

	else
	{
		while (1)											//파일의 끝이 될때까지 반복
		{
			Get = fgetc(fp);
			if (isalpha((char)Get))
			{
				Save[x] = Get;								//배열에 단어 저장뒤, 다음 배열로
				x++;
			}

			else
			{
				if (x)
				{
					Save[x] = '\0';							//Null값을 Save에 넣어줌 ( 단어의 구분 )
					Link(Save);								//리스트에 넣기 위한 함수 호출
					x = 0;									//단어를 리스트에 넣었으니, 다시 단어를 받아줌
				}
			}
			if (Get == EOF)
				break;
		}
	}
	printf("검색할 단어 : ");
	scanf("%s", &word);
	printf("\n");
	Search(word);
	printf("\n");
	fclose(fp);
}

