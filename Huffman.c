#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>

#define N 27
#define M 52

typedef struct {
	float weight;
	int parent,lchild,rchild;
}HuffmanTree;

void GetWeight(float weight[]);
void CreatHuffmanTree(HuffmanTree HT[],float weight[]);
void GetCode(HuffmanTree *HT,char Code[][N]);
void Select(HuffmanTree *HT,int n,int *min1,int *min2);
void HuffmanEncode(char Code[][N]);
void HuffmanDecode(HuffmanTree *HT);
void Menu(HuffmanTree *HT,float weight[],char Code[][N]);
void PrintTree(HuffmanTree *HT);
void PrintCode(float weight[],char Code[][N]);

int main()
{
	float weight[N];
	HuffmanTree HT[M];
	char Code[N][N];

	GetWeight(weight);
	CreatHuffmanTree(HT,weight);
	GetCode(HT,Code);

	Menu(HT,weight,Code);
	return 0;
}

void GetWeight(float weight[])
{
	FILE *fp;
	char ch;
	int i;
	int count[N]={0};

    printf("正在读取文件，获得权重，请稍后。。。\n\n");
    Sleep(2000);
	fp=fopen("speech.txt","rt");
	if(fp==NULL||fgetc(fp)==EOF)
	{
		printf("文件不存在或为空，请确认后重新运行程序！\n");
		exit(0);
	}
	rewind(fp);
	while((ch=fgetc(fp))!=EOF)
	{
		if(ch>='a'&&ch<='z')
		{
			count[0]++;
			count[ch-'a'+1]++;
		}
		else if(ch<='A'&&ch>='B')
		{
			count[0]++;
			count[ch-'A'+1]++;
		}
	}
	for(i=1;i<N;i++)
	{
		weight[i]=(float)count[i]/count[0]*100;
	}
	fclose(fp);
	printf("\n\n获取权重成功！\n\n");
}


void CreatHuffmanTree(HuffmanTree *HT,float weight[])
{
	int i;
	int min1,min2;

    printf("正在创建Huffman树，请稍后。。。\n\n");
    Sleep(2000);
	for(i=1;i<N;i++)
	{
		HT[i].weight=weight[i];
		HT[i].parent=0;
		HT[i].lchild=HT[i].rchild=0;
	}

	for(i=N;i<M;i++)
	{
		HT[i].weight=0;
		HT[i].parent=0;
		HT[i].lchild=HT[i].rchild=0;
	}

	for(i=N;i<M;i++)
	{
		Select(HT,i-1,&min1,&min2);
		HT[min1].parent=HT[min2].parent=i;
		HT[i].lchild=min1;		HT[i].rchild=min2;
		HT[i].weight=HT[min1].weight+HT[min2].weight;
	}
	printf("\n\n成功创建Huffman树！\n\n");
}

void Select(HuffmanTree *HT,int n,int *min1,int *min2)
{
	int i,j=1;
	int mark[M+1];
	for(i=1;i<=n;i++)
		if(HT[i].parent==0)mark[j++]=i;
	*min1=HT[mark[1]].weight<HT[mark[2]].weight?mark[1]:mark[2];
	*min2=HT[mark[1]].weight>=HT[mark[2]].weight?mark[1]:mark[2];
	for(i=3;i<j;i++)
	{
		if(HT[mark[i]].weight<HT[*min2].weight)
		{
			if(HT[mark[i]].weight<=HT[*min1].weight)
			{
				*min2=*min1;
				*min1=mark[i];
			}
			else
			{
				*min2=mark[i];
			}
		}
	}
}


void GetCode(HuffmanTree *HT,char Code[][N])
{
	int i,child,parent,start;
	char code[N]={"\0"};

    printf("正在计算字符编码，请稍后。。。\n\n");
    Sleep(2000);
	for(i=1;i<N;i++)
	{
		child=i;
		start=N-1;
		while(HT[child].parent!=0)
		{
			parent=HT[child].parent;
			if(HT[parent].lchild==child)
				code[--start]='0';
			else
				code[--start]='1';
			child=parent;
		}
		strcpy(Code[i],&code[start]);
	}
	printf("\n\n成功获取编码！\n\n");
}


void HuffmanEncode(char Code[][N])
{
	char ch;

	fflush(stdin);
	printf("请输入需要编码的字符串:\n");
	while((ch=getchar())!='\n')
	{
		if(ch>='a'&&ch<='z')
			printf("%s",Code[ch-'a'+1]);
		else if(ch>='A'&&ch<='Z')
			printf("%s",Code[ch-'A'+1]);
	}
	putchar('\n');
	system("pause");
}


void HuffmanDecode(HuffmanTree *HT)
{
	char ch;
	int temp=M-1;

	fflush(stdin);
	printf("请输入需要解码的二进制代码:\n");
	while((ch=getchar())!='\n')
	{
		if(ch=='0')temp=HT[temp].lchild;
		else if (ch=='1')temp=HT[temp].rchild;
		if(HT[temp].lchild==0)
		{
			printf("%c",temp+'a'-1);
			temp=M-1;
		}
	}
	putchar('\n');
	system("pause");
}

void Menu(HuffmanTree *HT,float weight[],char Code[][N])
{
	char choose;


	while(1)
	{
	    printf("\n\n\n");
	    printf("*******************************\n");
	    printf("*   1：输入字符进行编码       *\n");
        printf("*   2：输入编码进行解码       *\n");
        printf("*   3：打印Huffman树          *\n");
        printf("*   4：打印所有字符编码       *\n");
        printf("*   5：退出                   *\n");
        printf("*******************************\n");
        printf("请选择：  ");
		scanf("%c",&choose);
		fflush(stdin);
		switch(choose)
		{
		case '1':
			HuffmanEncode(Code);
			break;
		case '2':
			HuffmanDecode(HT);
			break;
		case '3':
			PrintTree(HT);
			break;
        case '4':
            PrintCode(weight,Code);
            break;
        case '5':
            exit(0);
		default:
			printf("输入有误，请重新输入\n");
			continue;
		}
	}
}

void PrintTree(HuffmanTree *HT)
{
    int i;

	printf("节点   权重  双亲  左孩子  右孩子\n");
	for(i=1;i<M;i++)
	{
		printf("%2d： %6.2f   %02d    %02d      %02d\n",i,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
	}
	printf("\n\n");
}
void PrintCode(float weight[],char Code[][N])
{
    int i;

    printf("字符    权重    编码\n");
	for(i=1;i<N;i++)
	{
		printf("%c:     %5.2f    %s\n",i+64,weight[i],Code[i]);
	}
	printf("\n\n");
}
