#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct
{
	int weight;
	int parent,lchild,rchild;
}HFNode,*HFTree; 
typedef char *HFCode;//�洢���������� 
void select(HFTree *ht,int n,int *s1,int *s2)//ѡ������parentΪ0����weight��С�Ľ��s1,s2 
{
	int i,min;
	for(i=1;i<=n;i++)
	{
		if((*ht)[i].parent==0)
		{
			min=i;
			break;
		} 
	}
	for(i=1;i<=n;i++)
	{
		if((*ht)[i].parent==0)
		{
			if((*ht)[i].weight<(*ht)[min].weight)
			{
				min=i;
			}
		}
	}
	*s1=min;
	for(i=1;i<=n;i++)
	{
		if((*ht)[i].parent==0 && i!=*s1)
		{
			min=i;
			break; 
		}
	}
	for(i=1;i<=n;i++)
	{
		if((*ht)[i].parent==0 && i!=*s1)
		{
			if((*ht)[i].weight<(*ht)[min].weight)
			{
				min=i;
			}
		}
	}
	*s2=min;
}
void CreatHFTree(HFTree *ht,int *w,int n)//w���n��Ȩֵ 
{
	int m,i,s1,s2;
	m=2*n-1;//�ܹ��Ľ���� 
	*ht=(HFTree)malloc ((m+1)*sizeof(HFNode)) ;
	for(i=1;i<=n;i++)   //��Ҷ�ӽ���ʼ�� 
	{
		(*ht)[i].weight=w[i];
		(*ht)[i].lchild=0;
		(*ht)[i].rchild=0;
		(*ht)[i].parent=0;
	}
	for(i=n+1;i<=m;i++)//��Ҷ�ӽ��ĳ�ʼ�� 
	{
		(*ht)[i].weight=0;
		(*ht)[i].lchild=0;
		(*ht)[i].rchild=0;
		(*ht)[i].parent=0;
	} 
	for(i=n+1;i<=m;i++)
	{
		select(ht,i-1,&s1,&s2);
		(*ht)[s1].parent=i;
		(*ht)[s2].parent=i;
		(*ht)[i].lchild=s1;
		(*ht)[i].rchild=s2;
		(*ht)[i].weight=(*ht)[s1].weight+(*ht)[s2].weight;
	}
}
void Code(HFTree *ht,HFCode *hc,int n)
{
	char *cd;
	int a[100];
	int i,start,j,p;
	float w;
	hc=(HFCode *)malloc ((n+1)*sizeof(char *));
	cd=(char *)malloc (n*sizeof(char));
	cd[n-1]='\0';
	for(i=1;i<=n;i++)
	{
		a[i]=0;
		start=n-1;//��ʼָ��λ�������ұ�
		for(j=i,p=(*ht)[i].parent;p!=0;j=p,p=(*ht)[p].parent)//�ж�����p!=0 
		{
			if((*ht)[p].lchild==j)
			{
				cd[--start]='0';
				a[i]++;
			}
			else
			{
				cd[--start]='1';
				a[i]++;
			}
		}
		hc[i]=(char *)malloc((n-start)*sizeof(char));
		strcpy(hc[i],&cd[start]);//��cd���Ʊ��뵽hc 
	}
	free(cd);
	for(i=1;i<=n;i++) 
		printf("ȨֵΪ%d������ǰ׺����Ϊ��%s\n",(*ht)[i].weight,hc[i]);
	for(i=1; i<=n; i++)
		w+=(*ht)[i].weight*a[i];
	w=w/100;
	printf("ƽ���볤Ϊ: %.2f\n", w);
}
int main()
{
	HFTree ht;
	HFCode hc;
	int *w,i,n,q;
	printf("����������ַ�����:\n");
	scanf("%d",&n);
	w=(int *)malloc((n+1)*sizeof(int));
	printf("\n����%d��Ԫ�ص�Ȩֵ��\n",n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&q);
		w[i]=q;
	}
	CreatHFTree(&ht,w,n);
	Code(&ht,&hc,n);
}

