//BALAJI RAJAGURU RAJAKUMAR
//2018503016
// Anna university MIT
//PHARMACY


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 10000

typedef struct node{
    char med[MAX];
    char info[MAX];
    int stock;
    int price;
    struct node* next;
}LIST;
typedef struct Node{char word[40],def[200];
    struct Node *left,*right;}NODE;
typedef NODE *TREE;

typedef LIST *list;
char Left[100],Right[100];
list makenode(char d[],char d1[],int s,int p)
{
    list t=(list)malloc(sizeof(LIST));
    strcpy(t->med,d);
    strcpy(t->info,d1);
    t->stock=s;
    t->price=p;
    t->next=NULL;
    return t;
}
TREE makeNode(char w[],char d[])
{
    TREE t;
    t = (TREE)malloc(sizeof(NODE));
    strcpy(t->word,w);
    strcpy(t->def,d);
    t->left = NULL;
    t->right=NULL;
    return t;
}

list top(list l,char d[],char d1[],int s,int p)
{
    if(!l) return makenode(d,d1,s,p);
    list temp=l;
    list t;
    t=makenode(d,d1,s,p);
    t->next=temp;
    return t;
}
void in(TREE l)
{
    printf("\n*******************************\n");
    while(l)
    {
        puts(l->word);
        l = l->left;
    }
    printf("\n*******************************\n");
}
TREE createtree()
{
    TREE t=(TREE)malloc(sizeof(NODE));
    t->left=NULL;
    t->right=NULL;
    return t;
}
TREE insert(TREE l,char w[],char d[])
{
    if(!l) return makeNode(w,d);

    TREE t,temp;
    t = l;
    while(t->left)
        t = t->left;
    temp = makeNode(w,d);
    t->left = temp;
    return l;
}
int Search(TREE l,char w[])
{
    TREE t;
    t=l;
    int i=0;
    while(t)
    {
        if(strcmp((t->word),w)==0)
        {
            printf("\n*******************************\n");
            printf("Symptom:%s\n",t->word);
            printf("Solution:%s\n",t->def);
            printf("\n*******************************\n");
            i=1;
        }
        t=t->left;
    }
    return i;
}

list back(list l,char d[],char d1[],int s,int p)
{
    list temp=NULL,t=NULL;
    t=makenode(d,d1,s,p);
    if(!l)return t;
    temp=l;
    while(temp->next)
    {
        temp=temp->next;
    }
    temp->next=t;
    return l;
}
list delete(list l,char d[],int s)
{    list t;
    t=l;
    if(!l) return NULL;
    if(strcmp(l->med,d)==0)
    {
        if(((l->stock)-s)<=0)
            return l->next;
        else
            l->stock=(l->stock)-s;
    }
    while(l->next && (strcmp((l->next)->med,d)!=0))
    {
        l=l->next;
    }
    if(l->next)
    {
        if(((l->next)->stock)-s<=0)
            l->next = (l->next)->next;
        else
            ((l->next)->stock)=(((l->next)->stock)-s);
    }
    return t;
}
int count(list l)
{
    list t;
    t=l;
    int c=0;
    while(t)
    {
        c++;
        t=t->next;
    }
    return c;
}
void display(list l)
{
    printf("\n*********************************************************************************************\n");
    while(l)
    {
        printf("Name:%s\n",l->med);
        printf("About:");
        puts(l->info);
        printf("Available Stock : %d\n",l->stock);
        printf("Price: %d\n\n\n",l->price);
        l = l->next;
    }
    printf("\n*********************************************************************************************\n");
}
int search(list l,char d[])
{
    list t;
    t=l;
    int res;
    while(t)
    {
        res=strcmp((t->med),d);
        if(res==0)
            return 1;
        else
            t=t->next;

    }

    return 0;
}
int stp(list l,char d[])
{
    list t;
    t=l;
    int res;
    while(t)
    {
        res=strcmp((t->med),d);
        if(res==0)
            return t->stock;
        else
            t=t->next;
    }
    return 0;
}
int price(list l,char d[])
{
    list t;
    t=l;

    int res;
    while(t)
    {
        res=strcmp((t->med),d);
        if(res==0)
            return t->price;
        else
            t=t->next;
    }
    return 0;
}
list buy(list l)
{

    char name[100];
    int st,i=0,n,m,total=0;
    printf("\nEnter the number of prodcts you want to buy\n");
    beg:
    scanf("%d",&n);
    if(n>count(l))
    {
        printf("\nSorry We dont have that many products, re-enter number\n");
        goto beg;
    }
    while(i<n)
    {
        begin:
        printf("\nEnter the Drug Name:\n");
        scanf("%s",name);
        if(search(l,name)==0)
        {
            printf("\nWrong Input Re-enter name: \n");
            goto begin;
        }
        start:
        printf("\nEnter Nos.:\n");
        scanf("%d",&st);
        m=stp(l,name);
        if(st>m)
        {
            printf("Stock not available, enter a lesser nos.(stock available:%d)",m);
            goto start;
        }
        l=delete(l,name,st);
        total=(price(l,name)*st)+total;
        i++;
    }
    printf("\nTotal Price To be paid:%d\n",total);
    return l;

}
void help(TREE t)
{
    char s[100],ch[100];
    int n;
    printf("\n=============================================\n");

    FILE *fptr;

    static const char filename[] = "C:\\Users\\rrbmd\\CLionProjects\\cproject\\file.txt";
    FILE *file = fopen ( filename, "r" );
    if ( file != NULL )
    {
        char line [ 128 ];
        while ( fgets ( line, sizeof line, file ) != NULL )
        {
            fputs ( line, stdout ); /* write the line */
        }
        fclose ( file );
    }
    else
    {
        perror ( filename );
    }
    printf("\n=============================================\n");
    yes:
    printf("\nEnter the symptom from the above table:\n");
    scanf("%s",s);
    n=Search(t,s);
    if(n==0)
    {
        printf("\nYou have entered the wrong symtom name(please refer to the table for spelling)\n");
        goto yes;
    }
    printf("\n%s\n",ch);
}
void menu(list l,TREE t)
{
    int da;
    START:
    printf("\nMAIN MENU\n");
    printf("\nENTER YOUR OPTION:\n");
    printf("1.Employee\n");
    printf("2.Customer\n");
    scanf("%d",&da);
    if(da==1)
    {
        start:
        printf("\nEMPLOYEE MENU:");
        printf("\n________________________________\n");
        printf("________________________________\n");
        printf("1.Add a new Drug\n");
        printf("2.Remove stock\n");
        printf("3.Total No. of Drugs\n");
        printf("4.Search Drug\n");
        printf("5.Display total Stock\n");
        printf("6.GO TO MAIN MENU\n");
        printf("\n\nTo Exit Press Ctrl+C\n");
        printf("\n________________________________\n");
        printf("________________________________\n");
        int i,d,p,c,stock,price;
        char ch[100],info[100];
        scanf("%d",&i);
        switch(i)
        {

            case 1: printf("Enter MEDICINE Name:");
                scanf("%s",ch);
                printf("\nEnter Medicine Description:\n");
                scanf(" %[^\n]",info);
                printf("\nEnter the available stock:\n");
                scanf("%d",&stock);
                printf("\nEnter the price:\n");
                scanf("%d",&price);
                l = top(l,ch,info,stock,price);
                break;
            case 2: printf("Enter Medicine to be deleted:");
                scanf("%s",ch);
                printf("Enter how much to be removed:");
                scanf("%d",&stock);
                l = delete(l,ch,stock);
                break;
            case 3: c = count(l);printf("\n\nCount=%d\n\n",c);
                break;
            case 4: printf("Enter Data:");
                scanf("%s",ch);
                p = search(l,ch);
                if(p==1)
                    printf("\n\nWe Have The Product\n\n");
                else
                    printf("\n\nProduct Out Of Stock\n\n");

                break;
            case 5: display(l);
                break;
            case 6: goto START;
            default: printf("Wrong Input");
                break;
        }
        goto start;
    }
    else if(da==2)
    {
        start1:
        printf("\nCUSTOMER MENU:");
        printf("\n________________________________");
        printf("\n________________________________\n");
        printf("1.Total Number Of Products\n");
        printf("2.Search For Product\n");
        printf("3.Display All Products\n");
        printf("4.Buy Products\n");
        printf("5.Help Buying\n");
        printf("6.GO TO MAIN MENU\n");
        printf("\n\nTo Exit Press Ctrl+C\n");
        printf("\n________________________________\n");
        printf("________________________________\n");
        int i,d,p,c;
        int m;
        char ch[100];
        scanf("%d",&i);
        switch(i)
        {

            case 1: c = count(l);printf("\n\nCount=%d\n\n",c);
                break;
            case 2: printf("Enter Drug Name:");
                scanf("%s",ch);
                p = search(l,ch);
                if(p==1)
                    printf("\n\nWe Have The Product\n\n");
                else
                    printf("\n\nProduct Out Of Stock\n\n");

                break;
            case 3: display(l);
                break;
            case 4: display(l);
                l=buy(l);

                break;
            case 5: help(t);
                break;
            case 6: goto START;
            default: printf("Wrong Input");
                break;
        }
        goto start1;
    }
    else
    {
        printf("\nWrong Input\n");
        goto START;

    }
}
void main()
{
    list l=NULL;
    int i;
    TREE t;
    t=NULL;
    l=back(l,"Acetaminophen","It is used for mild pain relief",11,135);

    l=top(l,"Amoxicillin","Amoxicillin is used to treat many different types of infection caused by bacteria",12,100);

    l=top(l,"Clindamycin","Clindamycin is an antibiotic that fights bacteria in the body.",100,160);

    l=top(l,"Lisinopril","Lisinopril is an ACE inhibitor. ACE stands for angiotensin converting enzyme.",144,10);

    l=top(l,"Cymbalta","Cymbalta (duloxetine) is a selective serotonin and norepinephrine reuptake inhibitor antidepressant.",5,12);

    l=top(l,"Lyrica","Lyrica (pregabalin) was originally FDA approved as an anti-epileptic drug, also called an anticonvulsant.",90,65);

    l=top(l,"Oxycodone","Oxycodone is an opioid pain medication sometimes called a narcotic.",78,35);
    l=top(l,"Coldact","It is a selective inhibitator, used to treat Common cold",80,10);
    t=insert(t,"Fever","We suggest Acetaminophen");
    t=insert(t,"Bacterial_infection","We suggest Amoxicillin");
    t=insert(t,"Internal_infection","We suggest Clindamycin");
    t=insert(t,"BP","We suggest Lisinopril");
    t=insert(t,"Depression","We suggest Cymbalta");
    t=insert(t,"Nerve_pain","We suggest Lyrica");
    t=insert(t,"Body_Pain","We suggest Oxycodone");
    t=insert(t,"Anxiety","We suggest Ativan");
    t=insert(t,"Cold","We suggest Coldact");
    menu(l,t);

}
