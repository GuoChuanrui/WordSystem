#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 1000
//定义结构体变量
typedef struct{
		char state;            //单词状态
		int  number;           //单词序号
		char English[20];
		char Chinese[30];
}Word_type;
typedef struct{
        Word_type word[SIZE];
		int length;
}word_list;
//定义全局的结构体数组作为线性表
word_list List;
word_list *L=&List;
//函数声明 
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
//主函数
main(){
	int a;
	a=Init(L);
	if(a==-1){
		printf("初始化失败\n");
		exit(0);
	}
	else
	    menu();
}
//主菜单
void menu(){
	printf("\n\n\t\t*************************************************\n");
	printf("\n\t\t*\t\t欢迎使用背单词系统！\t\t*\n");
	printf("\n\t\t*\t1.显示单词\t\t2.背诵单词\t*\n");
	printf("\n\t\t*\t3.添加单词\t\t4.删除单词\t*\n");
	printf("\n\t\t*\t5.查询单词\t\t6.单词考核\t*\n");
	printf("\n\t\t*\t7.新单词本\t\t8.退出系统\t*\n");
	printf("\n\t\t*************************************************\n");
	int n;
    scanf("%d",&n);
    system("CLS");
	Switch(n);
}
//输入序号
void Switch(int n){ 
	switch(n){
		case 1:
			ShowList(L);   //显示所有单词
			break;
		case 2:
			recite(L);     //每页10个单词进行背诵
			break;
		case 3:
            Insert(L);     //添加单词
			break;
		case 4:
            Delete(L);     //删除单词
			break;
		case 5:
            Locate(L);     //查找单词
			break;
		case 6:
            check(L);      //单词考核
			break;
		case 7:
            WordBook(L);   //生成新单词本
			break;
		case 8:
			exit(0);       //退出
			break;
		default:
			printf("\n输入有误，请重新输入！\n");
			menu();
			
	}
	system("pause");
	system("CLS");
	menu();
}
//初始化顺序表
int Init(word_list *L){
	int i=0;
	FILE *fp;
	if((fp=fopen("word.txt","r"))==NULL){
		printf("\t\t文件打开失败，请重试！\n");
		return -1;
	}
	while(!feof(fp)&&i<SIZE){
		fscanf(fp,"%d",&L->word[i].number);
		fscanf(fp,"%s",&L->word[i].English);
		fscanf(fp,"%s",&L->word[i].Chinese);
		i++;
	}
	L->length=i;                      //记录长度
	for(i=0;i<L->length;i++){
		L->word[i].state=0;           //单词状态为 0 ，表示没看过
	}
 	return 1;
}
//输出
void ShowList(word_list *L){
	int i;
	printf("\n\t\t\t     * * * * * * * * \n");
    printf("\t\t\t    *   单  词  本  *\n");
    printf("\t\t\t     * * * * * * * * \n\n\n");
	for(i=0;i<L->length;i++)
		printf("\t   %-5d  %-20s  %s\n",L->word[i].number,L->word[i].English,L->word[i].Chinese);
	printf("\n按任意键返回主菜单。\n\n");
}
//背诵(10个单词为一组)
void recite(word_list *L){
    int i=0,n=1,k,m;                   //k为单词表的总页数
    if(L->length%10==0)
        k=L->length/10;
	else
	    k=L->length/10+1;
	A:{if(n<k){
    		printf("\n\n\n\t\t\t\t第 %d 页\n\n",n);
    		for(i=(n-1)*10;i<10*n;i++){
    			L->word[i].state=1;     //单词状态为 1 ，表示看过了
				printf("\t   %-5d    %-20s  %s\n",L->word[i].number,L->word[i].English,L->word[i].Chinese);
			}
			n++;
	  	}
	  	else if(n==k){
    		printf("\n\n\n\t\t\t\t第 %d 页\n\n",n);
    		for(i=(n-1)*10;i<10*(n-1)+(L->length-10*(n-1))%10;i++){
    			L->word[i].state=1;
				printf("\t   %-5d    %-20s  %s\n",L->word[i].number,L->word[i].English,L->word[i].Chinese);
			}
			n++;
	  	}
		printf("\n   输入456进入上一页,输入123进入下一页,输入0键返回主菜单,输入1-%d进入该页。\n",k);
		B:{scanf("%d",&m);}
	   }
	if(m==123){
		if(n==k+1)
		    n=k;      //当页数为最后一页时，没有下一页
		system("CLS");
		goto A;
	}
	else if(m==0){
        system("CLS");
		menu();
	}
	else if(m==456){
		if(n==2)
		    n=1;     //当页数为第一页时，没有上一页
		else
            n=n-2;
		system("CLS");
		goto A;
	}
	else if(m>=1&&m<=k){
		n=m;         //当输入1-k数字时，跳转至某一页
		system("CLS");
		goto A;
	}
	else
	    printf("您的输入有误，请重新输入。\n");
	    goto B;
}
//添加
void Insert(word_list *L){
	int i,j=0;
	printf("请输入新添单词的英文拼写：\n\n");
	scanf("%s",&L->word[L->length].English);
	for(i=0;i<L->length;i++){
		while(strcmp(L->word[L->length].English,L->word[i].English)==0){    //比较新添单词与原有单词是否一致
			j=1;
			break;
		}
	}
	if(j==1){
        printf("\n单词表中已有这个单词，无须输入。\n");
        printf("\n按任意键返回主菜单。\n\n");
	}
	else{
        printf("\n请输入添加新单词的中文释义：\n");
    	scanf("%s",&L->word[L->length].Chinese);
		L->length=L->length+1;                       //长度加一
    	L->word[L->length-1].number=L->length;       //把单词表长度赋值给新添单词的序号
    	Conserve(L);
		ShowList(L);
	}
}
//删除
int Deletee(word_list *L,int nPos){
	int i;
	if(L->length<=0){
		printf("该单词表为空，无法进行删除操作！\n");
		return 0;
    }
	for(i=nPos;i<L->length;i++){
		L->word[i-1]=L->word[i];                      //nPos后的每个单词前移
		L->word[i-1].number=L->word[i].number-1;      //nPos后的每个单词序号减一
    }
    L->length--;                                      //长度减一
    return 1;
}
void Delete(word_list *L){
	int i,nPos;
	for(i=0;i<L->length;i++)
		printf("\t   %-5d  %-20s  %s\n",L->word[i].number,L->word[i].English,L->word[i].Chinese);
    printf("\n请输入想要删除单词的序号(1-%d):\n",L->length);
    C:{scanf("%d",&nPos);}
    if(nPos>0&&nPos<=L->length){
		Deletee(L,nPos);
        Conserve(L);
        ShowList(L);
    }
    else{
		printf("\n您的输入有误，请重新输入！\n");
		goto C;
	}
}
//保存至文件
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
    printf("\n单词表修改成功！\n");
}
//查询
int Locate(word_list *L){
	int i,count;
    char vol[15];
    printf("请输入该单词\n");
    scanf("%s",&vol);
    printf("\n");
    for(i=0,count=0;i<L->length;i++){
		if(strcmp(L->word[i].English,vol)==0){
			printf("%-5d %-20s %s\n",L->word[i].number,L->word[i].English,L->word[i].Chinese);
			count=1;
		}
    }
    if(count==0)
    	printf("输入有误，单词表中没有这个单词！\n");
	printf("\n按任意键返回主菜单。\n\n");
	return 0;
}
//单词考核
void check(word_list *L){
	int i,q,p,n=1,s,count1=0,count2=0;    //count1是考查单词的总数，count2是写对单词的个数
	char answer[20];
	char TF;                              //TF为考核后的状态（对或错）
	char a[20],b[30];
	if(L->word[q].state==0){
		printf("\n您还未进行单词背诵，请先背诵单词！\n");
		printf("\n按任意键返回主菜单。\n\n");
	}
	for(i=0;i<L->length;i++){
		q=rand()%L->length;              //q为单词序号0到L->length-1之内生成的随机数
		p=rand()%2;                      //p为生成的随机数0或1
		if(L->word[q].state==1){
			if(p==0){                    //p=0时，考核英译汉
		    	strcpy(a,L->word[q].English);
		    	strcpy(b,L->word[q].Chinese);
			}
			else if(p==1){               //p=1时，考核汉译英
				strcpy(a,L->word[q].Chinese);
				strcpy(b,L->word[q].English);
			}
			printf("%s\n\n",a);
			printf("请输入答案：\n\n");
			scanf("%s",&answer);
			printf("\n正确答案是：\n\n");
			printf("%s\n\n",b);
			printf("请自行判断对错（输入T或F）：\n\n");
			B:{scanf("%s",&TF);}
			if(TF=='T'||TF=='F'){
				L->word[q].state=TF;
				count1++;
				if(TF=='T')
				    count2++;
			}
			else{
			    printf("输入有误！请重新输入。\n\n");
			    goto B;
			}
			printf("\n请输入1进入下一个单词，输入0结束考核并显示成绩。\n\n");
			scanf("%d",&s);
			switch(s){
				case 1:
                    printf("\n\n");
                    break;
				case 0:
					system("CLS");
					printf("\n\n\n\t\t您已考查%d个单词，对了%d个，错了%d个。\n\n",count1,count2,count1-count2);
					printf("\n按任意键返回主菜单。\n\n");
					system("pause");
					system("CLS");
					menu();
					break;
			}
			
		}
	}
}

//新生词本
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
    printf("\t\t\t    *   生  词  本  *\n");
    printf("\t\t\t     * * * * * * * * \n\n\n");
    for(i=0,count=1;i<L->length-1;i++){
        if(L->word[i].state=='F'){
			printf("\t   %-5d %-20s %s\n",count,L->word[i].English,L->word[i].Chinese);
			count++;
		}
    }
    printf("\n按任意键返回主菜单。\n\n");
}
