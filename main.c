#include<stdio.h>
#include<string.h>
#include<stdarg.h>

#define true 1
#define false 0

float train(char *);
void clear();
int findmax(int ,double array[]);
int global_count=0;
char str[200];
FILE *fp;
char *temp_tok;
char *str1;
char *str2;
int word_count[20];
char strings[20][10];
char array1[20][10];
int words_ent=0;
char sentences[100],temp_sen[100];
double p_ls=1;
int ls_length;
int main()
{
    FILE *fp1;
    int check=0;
    char file_name[20];
    int x=0;
    double array_probab[4];
   	printf("please speak\n");
	gets(sentences);
	strcpy(temp_sen,sentences);
	temp_tok=strtok(temp_sen," ");
	strcpy(array1[x],temp_tok);
	while(true)
	{
		if((temp_tok=strtok(NULL," "))!=NULL)
		{
			strcpy(array1[++x],temp_tok);
			continue;
		}
		else
			break;
	}
    words_ent=x+1;
    x=0;
    clear();
    array_probab[0]=train("ls1.txt");
    printf("\n%f:ls\n",array_probab[0]);
    clear();
    array_probab[1]=train("mkdir1.txt");
    printf("\n%f:mkdir\n",array_probab[1]);
    clear();
    array_probab[2]=train("find1.txt");
    printf("\n%f:find1\n",array_probab[2]);
    array_probab[3]=train("grep1.txt");
   printf("\n%f:grep \n",array_probab[3]);
     switch(findmax(4,array_probab))
     {
     	case 0:
     		printf("Output mapped is %lf:ls",array_probab[0]);
     		break;
     	case 1:
     		printf("Output mapped is %lf:mkdir",array_probab[1]);
     		break;
     	case 2:
     		printf("Output mapped is %lf:find",array_probab[2]);
     		break;
     	case 3:
     		printf("Output mapped is %lf:grep",array_probab[3]);
     		break;
     }   
    printf("\n was the output mapped correctly yes=1 no=0\n");
    scanf("%d",&check);
  if(check==0)
    {
        printf("enter the right command for the sentence: ");
        scanf("%s",file_name);
        strcat(file_name,"1.txt");
        fp1=fopen(file_name,"a+");
        fprintf(fp1,"%s",sentences);
        fprintf(fp1," .");
        fprintf(fp1,"\n");

        fclose(fp1);
    }
    return 0;

}

void clear()
{
    for(int m=0; m<20; m++)
    {
        word_count[m]=0;
    }
}
float train(char *fname)
{
    int i=0;
    int num=0;
    int late=0;
    float tmp_p_ls=1;
    fp=fopen(fname,"rw+");
    p_ls=1;
    do
    {
        while(fgets(str,200,fp)!=NULL)
        {
            if(num==0)
            {
                ls_length++;
//printf("\nls_length is %d\n",ls_length);
            }
            str1=(char*)strtok(str," ");
            strcpy(strings[i],str1);

            i++;
            while(str1!=NULL)
            {

                str1=strtok(NULL," ");

                if(str1!=NULL)
                {
                    strcpy(strings[i],str1);
                    i++;
                }

            }


            if(num==0)
            {
                global_count=global_count+i;

            }
            for(int j=0; j<i; j++)
            {
                if(strcmp(array1[num],strings[j])==0)
                {
                    word_count[num]=word_count[num]+1;
                }
            }

//for(int u=0;u<i;u++)
//	{
//	for(int v=0;v<i;v++)
//		{
//			if(strcmp(strings[v],strings[u])==0)
//			{late++;}
//
//		}
//	global_count=global_count-late;
//	late=0;
//	}

            i=0;

        }
        rewind(fp);
        num++;
    }
    while(num<words_ent);
    printf("\n words entered %d",words_ent);
    
    for(int y=0; y<words_ent; y++)
    {
    printf("\nthis word occurs %d times",word_count[y]);

        p_ls=word_count[y];
        p_ls=p_ls+1;
        p_ls=(p_ls)/((10)+30);
        p_ls=p_ls * 10;
        tmp_p_ls=p_ls*tmp_p_ls;

    }

    p_ls=tmp_p_ls*(ls_length-1)/24;
    fclose(fp);
    ls_length=0;
    return p_ls;

}

int findmax(int tot_num,double array[])
{
	double max,num;
	int walker=0,index=0;
	for(walker=0;walker<tot_num;walker++)
	{
		num=array[walker];
		if(num>max)
		{
			max=num;
			index=walker;
		}
	}
	return (index);
}
