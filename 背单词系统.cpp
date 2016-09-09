#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 1000
//����ṹ�����
typedef struct{
		char state;            //����״̬
		int  number;           //�������
		char English[20];
		char Chinese[30];
}Word_type;
typedef struct{
        Word_type word[SIZE];
		int length;
}word_list;
//����ȫ�ֵĽṹ��������Ϊ���Ա�
word_list List;
word_list *L=&List;
//�������� 
void menu(); 
void Switch(int n);
int  Init(word_list *L);
void ShowList(word_list *L);
void recite(word_list *L);
void Insert(word_list *L);
int  Deletee(word_list *L,int nPos,word_list *LElem);
void Delete(word_list *L);
void Conserve(word_list *L);
int  Locate(word_list *L);
void check(word_list *L);
void WordBook(word_list *L);
//������
main(){
	int a;
	a=Init(L);
	if(a==-1){
		printf("��ʼ��ʧ��\n");
		exit(0);
	}
	else
	    menu();
}
//���˵�
void menu(){
	printf("\n\n\t\t*************************************************\n");
	printf("\n\t\t*\t\t��ӭʹ�ñ�����ϵͳ��\t\t*\n");
	printf("\n\t\t*\t1.��ʾ����\t\t2.���е���\t*\n");
	printf("\n\t\t*\t3.��ӵ���\t\t4.ɾ������\t*\n");
	printf("\n\t\t*\t5.��ѯ����\t\t6.���ʿ���\t*\n");
	printf("\n\t\t*\t7.�µ��ʱ�\t\t8.�˳�ϵͳ\t*\n");
	printf("\n\t\t*************************************************\n");
	int n;
    scanf("%d",&n);
    system("CLS");
	Switch(n);
}
//�������
void Switch(int n){ 
	switch(n){
		case 1:
			ShowList(L);   //��ʾ���е���
			break;
		case 2:
			recite(L);     //ÿҳ10�����ʽ��б���
			break;
		case 3:
            Insert(L);     //��ӵ���
			break;
		case 4:
            Delete(L);     //ɾ������
			break;
		case 5:
            Locate(L);     //���ҵ���
			break;
		case 6:
            check(L);      //���ʿ���
			break;
		case 7:
            WordBook(L);   //�����µ��ʱ�
			break;
		case 8:
			exit(0);       //�˳�
			break;
		default:
			printf("\n�����������������룡\n");
			menu();
			
	}
	system("pause");
	system("CLS");
	menu();
}
//��ʼ��˳���
int Init(word_list *L){
	int i=0;
	FILE *fp;
	if((fp=fopen("word.txt","r"))==NULL){
		printf("\t\t�ļ���ʧ�ܣ������ԣ�\n");
		return -1;
	}
	while(!feof(fp)&&i<SIZE){
		fscanf(fp,"%d",&L->word[i].number);
		fscanf(fp,"%s",&L->word[i].English);
		fscanf(fp,"%s",&L->word[i].Chinese);
		i++;
	}
	L->length=i;                      //��¼����
	for(i=0;i<L->length;i++){
		L->word[i].state=0;           //����״̬Ϊ 0 ����ʾû����
	}
 	return 1;
}
//���
void ShowList(word_list *L){
	int i;
	printf("\n\t\t\t     * * * * * * * * \n");
    printf("\t\t\t    *   ��  ��  ��  *\n");
    printf("\t\t\t     * * * * * * * * \n\n\n");
	for(i=0;i<L->length;i++)
		printf("\t   %-5d  %-20s  %s\n",L->word[i].number,L->word[i].English,L->word[i].Chinese);
	printf("\n��������������˵���\n\n");
}
//����(10������Ϊһ��)
void recite(word_list *L){
    int i=0,n=1,k,m;                   //kΪ���ʱ����ҳ��
    if(L->length%10==0)
        k=L->length/10;
	else
	    k=L->length/10+1;
	A:{if(n<k){
    		printf("\n\n\n\t\t\t\t�� %d ҳ\n\n",n);
    		for(i=(n-1)*10;i<10*n;i++){
    			L->word[i].state=1;     //����״̬Ϊ 1 ����ʾ������
				printf("\t   %-5d    %-20s  %s\n",L->word[i].number,L->word[i].English,L->word[i].Chinese);
			}
			n++;
	  	}
	  	else if(n==k){
    		printf("\n\n\n\t\t\t\t�� %d ҳ\n\n",n);
    		for(i=(n-1)*10;i<10*(n-1)+(L->length-10*(n-1))%10;i++){
    			L->word[i].state=1;
				printf("\t   %-5d    %-20s  %s\n",L->word[i].number,L->word[i].English,L->word[i].Chinese);
			}
			n++;
	  	}
		printf("\n   ����456������һҳ,����123������һҳ,����0���������˵�,����1-%d�����ҳ��\n",k);
		B:{scanf("%d",&m);}
	   }
	if(m==123){
		if(n==k+1)
		    n=k;      //��ҳ��Ϊ���һҳʱ��û����һҳ
		system("CLS");
		goto A;
	}
	else if(m==0){
        system("CLS");
		menu();
	}
	else if(m==456){
		if(n==2)
		    n=1;     //��ҳ��Ϊ��һҳʱ��û����һҳ
		else
            n=n-2;
		system("CLS");
		goto A;
	}
	else if(m>=1&&m<=k){
		n=m;         //������1-k����ʱ����ת��ĳһҳ
		system("CLS");
		goto A;
	}
	else
	    printf("���������������������롣\n");
	    goto B;
}
//���
void Insert(word_list *L){
	int i,j=0;
	printf("�����������ʵ�Ӣ��ƴд��\n\n");
	scanf("%s",&L->word[L->length].English);
	for(i=0;i<L->length;i++){
		while(strcmp(L->word[L->length].English,L->word[i].English)==0){    //�Ƚ���������ԭ�е����Ƿ�һ��
			j=1;
			break;
		}
	}
	if(j==1){
        printf("\n���ʱ�������������ʣ��������롣\n");
        printf("\n��������������˵���\n\n");
	}
	else{
        printf("\n����������µ��ʵ��������壺\n");
    	scanf("%s",&L->word[L->length].Chinese);
		L->length=L->length+1;                       //���ȼ�һ
    	L->word[L->length-1].number=L->length;       //�ѵ��ʱ��ȸ�ֵ�������ʵ����
    	Conserve(L);
		ShowList(L);
	}
}
//ɾ��
int Deletee(word_list *L,int nPos){
	int i;
	if(L->length<=0){
		printf("�õ��ʱ�Ϊ�գ��޷�����ɾ��������\n");
		return 0;
    }
	for(i=nPos;i<L->length;i++){
		L->word[i-1]=L->word[i];                      //nPos���ÿ������ǰ��
		L->word[i-1].number=L->word[i].number-1;      //nPos���ÿ��������ż�һ
    }
    L->length--;                                      //���ȼ�һ
    return 1;
}
void Delete(word_list *L){
	int i,nPos;
	for(i=0;i<L->length;i++)
		printf("\t   %-5d  %-20s  %s\n",L->word[i].number,L->word[i].English,L->word[i].Chinese);
    printf("\n��������Ҫɾ�����ʵ����(1-%d):\n",L->length);
    C:{scanf("%d",&nPos);}
    if(nPos>0&&nPos<=L->length){
		Deletee(L,nPos);
        Conserve(L);
        ShowList(L);
    }
    else{
		printf("\n���������������������룡\n");
		goto C;
	}
}
//�������ļ�
void Conserve(word_list *L){
	int i;
    FILE *fp;
    fp=fopen("word.txt","w");
    if(fp==NULL){
		printf("Sorry,cannot open the file!\n");
	    exit (0);
    }
    for(i=0;i<L->length-1;i++){
		fprintf(fp,"%-5d %-20s %s\n",L->word[i].number,L->word[i].English,L->word[i].Chinese);
    }
    fprintf(fp,"%-5d %-20s %s",L->word[L->length-1].number,L->word[L->length-1].English,L->word[L->length-1].Chinese);
    fclose(fp);
    printf("\n���ʱ��޸ĳɹ���\n");
}
//��ѯ
int Locate(word_list *L){
	int i,count;
    char vol[15];
    printf("������õ���\n");
    scanf("%s",&vol);
    printf("\n");
    for(i=0,count=0;i<L->length;i++){
		if(strcmp(L->word[i].English,vol)==0){
			printf("%-5d %-20s %s\n",L->word[i].number,L->word[i].English,L->word[i].Chinese);
			count=1;
		}
    }
    if(count==0)
    	printf("�������󣬵��ʱ���û��������ʣ�\n");
	printf("\n��������������˵���\n\n");
	return 0;
}
//���ʿ���
void check(word_list *L){
	int i,q,p,n=1,s,count1=0,count2=0;    //count1�ǿ��鵥�ʵ�������count2��д�Ե��ʵĸ���
	char answer[20];
	char TF;                              //TFΪ���˺��״̬���Ի��
	char a[20],b[30];
	if(L->word[q].state==0){
		printf("\n����δ���е��ʱ��У����ȱ��е��ʣ�\n");
		printf("\n��������������˵���\n\n");
	}
	for(i=0;i<L->length;i++){
		q=rand()%L->length;              //qΪ�������0��L->length-1֮�����ɵ������
		p=rand()%2;                      //pΪ���ɵ������0��1
		if(L->word[q].state==1){
			if(p==0){                    //p=0ʱ������Ӣ�뺺
		    	strcpy(a,L->word[q].English);
		    	strcpy(b,L->word[q].Chinese);
			}
			else if(p==1){               //p=1ʱ�����˺���Ӣ
				strcpy(a,L->word[q].Chinese);
				strcpy(b,L->word[q].English);
			}
			printf("%s\n\n",a);
			printf("������𰸣�\n\n");
			scanf("%s",&answer);
			printf("\n��ȷ���ǣ�\n\n");
			printf("%s\n\n",b);
			printf("�������ж϶Դ�����T��F����\n\n");
			B:{scanf("%s",&TF);}
			if(TF=='T'||TF=='F'){
				L->word[q].state=TF;
				count1++;
				if(TF=='T')
				    count2++;
			}
			else{
			    printf("�����������������롣\n\n");
			    goto B;
			}
			printf("\n������1������һ�����ʣ�����0�������˲���ʾ�ɼ���\n\n");
			scanf("%d",&s);
			switch(s){
				case 1:
                    printf("\n\n");
                    break;
				case 0:
					system("CLS");
					printf("\n\n\n\t\t���ѿ���%d�����ʣ�����%d��������%d����\n\n",count1,count2,count1-count2);
					printf("\n��������������˵���\n\n");
					system("pause");
					system("CLS");
					menu();
					break;
			}
			
		}
	}
}

//�����ʱ�
void WordBook(word_list *L){
	int i,count;
    FILE *fp;
    fp=fopen("WordBook.txt","w");
    if(fp==NULL){
		printf("Sorry,cannot open the file!\n");
	    exit (0);
    }
    for(i=0,count=1;i<L->length-1;i++){
        if(L->word[i].state=='F'){
			fprintf(fp,"%-5d %-20s %s\n",count,L->word[i].English,L->word[i].Chinese);
			count++;
		}
    }
    fclose(fp);
    printf("\n\t\t\t     * * * * * * * * \n");
    printf("\t\t\t    *   ��  ��  ��  *\n");
    printf("\t\t\t     * * * * * * * * \n\n\n");
    for(i=0,count=1;i<L->length-1;i++){
        if(L->word[i].state=='F'){
			printf("\t   %-5d %-20s %s\n",count,L->word[i].English,L->word[i].Chinese);
			count++;
		}
    }
    printf("\n��������������˵���\n\n");
}
