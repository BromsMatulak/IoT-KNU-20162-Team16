#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct NODE{
	char word[50];
	struct NODE *link;
}NODE;

int main()
{
	FILE *fp = NULL;
	NODE *list=NULL;
	NODE *prev,*p,*next;
	char buffer[256];//파일에서 문자열을 가져와 저장할 버퍼
	char find[50];//검색할 단어를 입력받을 배열
	char seps[]="1234567890 `~!@#$%^&*()_+|-=\\[]{};:/?<>,.\"\'\t\n";//분리자
	char *token;//토큰
	int index;//연결리스트 인덱스값
	int index_save[256];//인덱스값 저장할 배열
	int i;
	int n;//중복 단어 개수 저장

	fp = fopen("sample.txt","r");//텍스트파일을 읽기모드로 열기
	if(fp == NULL)//텍스트파일이 없을 경우
	{
		fprintf(stderr,"파일을 열 수 없습니다.\n");
		exit(1);
	}
	printf("========================================================================\n");
	printf("                          텍스트 파일 내용                              \n");
	printf("========================================================================\n");

	//단어를 추출하여 연결리스트로 만들기
	while(fgets(buffer,256,fp))//파일에서 문자열을 읽어옴
	{
		printf(buffer);//읽어온 문자열 화면에 출력
		token = strtok(buffer, seps);//첫번째 토큰

		while(token != NULL)
		{
			p=(NODE*)malloc(sizeof(NODE));//동적 메모리 할당
			strcpy(p->word,token);//구조체에 토큰입력
			
			if(list==NULL)//연결리스트 첫번째
				list=p;
			else//연결리스트 첫번째 이후
				prev->link=p;
			p->link=NULL;
			prev = p;

			token = strtok(NULL, seps);//다음토큰
		}
	}
	fclose(fp);//파일 닫기


	printf("\n");
	printf("========================================================================\n");
	printf("                              단어 추출                                 \n");
	printf("========================================================================\n");
	//추출한 단어 출력
	p=list;
	i=0;//추출한 단어에 순서대로 번호 붙이기
	while(p != NULL)
	{
		i++;
		printf("%4d  %s\n",i,p->word);
		p=p->link;
	}

	printf("========================================================================\n");
	printf("                              단어 검색                                 \n");
	printf("========================================================================\n");
	printf("검색할 단어 : ");
	scanf("%s",find);//키보드로 받은 입력을 find 배열에 문자열로 저장


	printf("========================================================================\n");
	printf("                                결과                                    \n");
	printf("========================================================================\n");
	n=0;//중복된 단어 개수
	index=0;//검색한 단어의 인덱스
	p=list;
	while(p != NULL)
	{
		if(strcmp(p->word,find)==0)//문자열 비교
		{ 
			index_save[n]=index;//인덱스값 저장
			n++;//중복단어 카운트
		}
		p=p->link;
		index++;//인덱스 카운트
	}

	if(n==0)//찾는 단어가 없을때
		printf("찾으시는 단어가 존재하지 않습니다.\n");
	else//찾는 단어가 있을때
	{
		printf("중복되는 단어를 포함하여 총 %d개의 단어가 검색되었습니다.\n",n);//중복단어수 출력
		printf("리스트의");
		for(i=0;i<n-1;i++)//인덱스 배열에 저장한 인덱스값 출력
		{
			printf(" %d,",index_save[i]+1);
		}
		printf(" %d 번째 index\n",index_save[i]+1);
	}


	//동적 메모리 반납
	p=list;
	while(p != NULL)
	{
		next = p->link;
		free(p);
		p=next;
	}

	return 0;
}