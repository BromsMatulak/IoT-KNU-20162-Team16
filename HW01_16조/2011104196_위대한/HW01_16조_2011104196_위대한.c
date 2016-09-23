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
	char buffer[256];//���Ͽ��� ���ڿ��� ������ ������ ����
	char find[50];//�˻��� �ܾ �Է¹��� �迭
	char seps[]="1234567890 `~!@#$%^&*()_+|-=\\[]{};:/?<>,.\"\'\t\n";//�и���
	char *token;//��ū
	int index;//���Ḯ��Ʈ �ε�����
	int index_save[256];//�ε����� ������ �迭
	int i;
	int n;//�ߺ� �ܾ� ���� ����

	fp = fopen("sample.txt","r");//�ؽ�Ʈ������ �б���� ����
	if(fp == NULL)//�ؽ�Ʈ������ ���� ���
	{
		fprintf(stderr,"������ �� �� �����ϴ�.\n");
		exit(1);
	}
	printf("========================================================================\n");
	printf("                          �ؽ�Ʈ ���� ����                              \n");
	printf("========================================================================\n");

	//�ܾ �����Ͽ� ���Ḯ��Ʈ�� �����
	while(fgets(buffer,256,fp))//���Ͽ��� ���ڿ��� �о��
	{
		printf(buffer);//�о�� ���ڿ� ȭ�鿡 ���
		token = strtok(buffer, seps);//ù��° ��ū

		while(token != NULL)
		{
			p=(NODE*)malloc(sizeof(NODE));//���� �޸� �Ҵ�
			strcpy(p->word,token);//����ü�� ��ū�Է�
			
			if(list==NULL)//���Ḯ��Ʈ ù��°
				list=p;
			else//���Ḯ��Ʈ ù��° ����
				prev->link=p;
			p->link=NULL;
			prev = p;

			token = strtok(NULL, seps);//������ū
		}
	}
	fclose(fp);//���� �ݱ�


	printf("\n");
	printf("========================================================================\n");
	printf("                              �ܾ� ����                                 \n");
	printf("========================================================================\n");
	//������ �ܾ� ���
	p=list;
	i=0;//������ �ܾ ������� ��ȣ ���̱�
	while(p != NULL)
	{
		i++;
		printf("%4d  %s\n",i,p->word);
		p=p->link;
	}

	printf("========================================================================\n");
	printf("                              �ܾ� �˻�                                 \n");
	printf("========================================================================\n");
	printf("�˻��� �ܾ� : ");
	scanf("%s",find);//Ű����� ���� �Է��� find �迭�� ���ڿ��� ����


	printf("========================================================================\n");
	printf("                                ���                                    \n");
	printf("========================================================================\n");
	n=0;//�ߺ��� �ܾ� ����
	index=0;//�˻��� �ܾ��� �ε���
	p=list;
	while(p != NULL)
	{
		if(strcmp(p->word,find)==0)//���ڿ� ��
		{ 
			index_save[n]=index;//�ε����� ����
			n++;//�ߺ��ܾ� ī��Ʈ
		}
		p=p->link;
		index++;//�ε��� ī��Ʈ
	}

	if(n==0)//ã�� �ܾ ������
		printf("ã���ô� �ܾ �������� �ʽ��ϴ�.\n");
	else//ã�� �ܾ ������
	{
		printf("�ߺ��Ǵ� �ܾ �����Ͽ� �� %d���� �ܾ �˻��Ǿ����ϴ�.\n",n);//�ߺ��ܾ�� ���
		printf("����Ʈ��");
		for(i=0;i<n-1;i++)//�ε��� �迭�� ������ �ε����� ���
		{
			printf(" %d,",index_save[i]+1);
		}
		printf(" %d ��° index\n",index_save[i]+1);
	}


	//���� �޸� �ݳ�
	p=list;
	while(p != NULL)
	{
		next = p->link;
		free(p);
		p=next;
	}

	return 0;
}