#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<unistd.h>

//ch is the new input
//cch is the old input
//a is the array where empty spaces and snake will be stored
char ch,cch,a[15][50];
int points=0,top_score,speed;
FILE *scores;


//this structure is used to create nodes which are blocks of snake from head to tail
typedef struct block
{
	int *p;//p pointer is an integer array which stores the snake co-ordinates of individual block these co-ordinates will used to store snake in array "a"
	struct block * next;
}block;

block *head,*tail=NULL;//tail represents tail of snake and head represents head of snake

//used to increase size of snake
//tail represents tail of snake
void newblock()
{
	block * nb;
	nb=(block *)malloc(sizeof(block));
	nb->next=tail;    //the linked list representation tail->node->node....node->x->head->null
	tail=nb;
	nb->p=(int *)malloc(2*sizeof(int));
}


int is_equal(int x1,int y1,int x2,int y2)
{
	return (x1==x2 && y1==y2);
}

//creates delay 
void delay(int d)
{
	int t1=clock();
	while(clock()-t1<d*CLOCKS_PER_SEC/7);
}



void stop()
{
	printf("\t\t\tGAME OVER");
}



void line_printer(int x,char c)
{
	int i,j;
	for(i=0;i<x;i++)
	{
		printf("%c",c);
	}
}


//this function used to print the game in console
void print()
{
	int i,j;
	printf("ENTER 0 TO QUIT\n");
	printf("\t\t\tSCORE : %d\n",points);
	for(i=0;i<2;i++)
	{
		line_printer(60,' ');
	}
	printf("\n");
	line_printer(15,' ');
	line_printer(30,'|');
	printf("\n");
	for(i=0;i<15;i++)
	{
		line_printer(14,' ');
		printf("|");
		for(j=0;j<30;j++)
		{
			printf("%c",a[i][j]);
		}
		printf("|");
		printf("\n");
	}
	line_printer(15,' ');
	line_printer(30,'|');
	printf("\n");
	
}


//"pcl" represents point collected
//"tail" represents tail of snake
//"head" represents head of snake
//"ch" is the new input
//"cch" is the old input
//this function is used to move the snake
void move(int pcl){
	int c=0,i;
	if(pcl)
	{

		newblock();
	}
	else
	{
		a[tail->p[0]][tail->p[1]]=' ';
	}
	if(points>0)
	{
		a[head->p[0]][head->p[1]]='O';
	}
	tail->p[0]=head->p[0];
	tail->p[1]=head->p[1];
	head->next=tail;   
	head=tail;
	tail=head->next;
	head->next=NULL;
	if(ch=='6' && cch=='4')
	{
		ch='4';
	}
	else if(ch=='4' && cch=='6')
	{
		ch='6';
	}
	else if(ch=='2' && cch=='8')
	{
		ch='8';
	}
	else if(ch=='8' && cch=='2')
	{
		ch='2';
	}
	else if(ch!='2' && ch!='8' && ch!='6' && ch!='4')
	{
		ch=cch;
	}
	if(ch=='6')
	{
		(head->p[1])+=1;
	}
	else if(ch=='8')
	{
		(head->p[0])+=1;
	}
	else if(ch=='4')
	{
		(head->p[1])-=1;
	}
	else if(ch=='2')
	{
		(head->p[0])-=1;
	}
	cch=ch;
	a[head->p[0]][head->p[1]]='X';
}

//"tail" represents tail of snake
//"head" represents head of snake
//this function is used to check weather snake hit walls or itself
int crash_check() 
{
	block *i;
	
	
		if(head->p[0]<0 || head->p[1]<0 || head->p[0]>14 || head->p[1]>29)
		{
			stop();
			return 1;
		}



	for(i=tail;i!=head;i=i->next)
	{
			if(is_equal(i->p[0],i->p[1],head->p[0],head->p[1]))
			{
				stop();
				return 1;
			}
	}
	return 0;
}


//this function is used to take input 
//clock returns real time while running
void input()
{
	int t1=clock();
	while(clock()-t1<CLOCKS_PER_SEC/(speed*8));//used to provide delay for input
	//delay(2);
	if(kbhit())//check weather there is an input
	{
		ch=getch();//return input enteres
		if(ch=='0')
		{
			exit(0);
		}
	}
	if(ch=='w' || ch=='W')
	{
		ch='2';
	}
	else if(ch=='s' ||ch=='S')
	{
		ch='8';
	}
	else if(ch=='a' ||ch =='A')
	{
		ch='4';
	}
	else if(ch=='d' || ch=='D')
	{
		ch='6';
	}
}



//this function is used to crete random value to place food at random locations
int rando()
{
	int x,c;
	block *i;
	while(1)
	{
		srand(time(0));
		x=rand()%450;//"rand" function creates random value
		if(a[x/30][x%30]==' ')//this condition make sure the food falls on the empty space not on snake
		{
			a[x/30][x%30]='0';
			break;
		}
	}
	return x;
}



//starting for the game
void start()
{
	int strt=1;
	system("cls");
	printf("2 or w-> up\n8 or s-> down\n4 or a-> LEFT\n6 or d-> RIGHT\n");
	printf("\t\t\tEnter 0 to start : ");
	while(strt)
	{

		scanf("%d",&strt);
	}
}

//this function is used to reset the snake while playing more than once
void nullify()
{
	if(tail!=NULL)
	{
		block *i=tail;
		while(i!=NULL)
		{
			tail=i->next;
			free(i);
			i=tail;
		}
	}
}


void set_speed()
{
	system("cls");
	printf("Select Speed\n\"1\" for low\n\"2\" for medium\n\"3\" for high\n");
	printf("Enter here : ");
	scanf("%d",&speed);
	system("cls");
}
//this function is used to initalize different variables while starting of every game
void initialize()
{
	set_speed();
	ch='6';//it is set to "6" so that the snake moves in x-axis at starting
	cch='6';
	points=0;
	top_score=0;
	int i,j,rch=1,x=0,y=0;
	for(i=0;i<15;i++)
	{
		for(j=0;j<50;j++)
		{
			a[i][j]=' ';
		}
	}
	nullify();
	newblock();
	head=tail;
	tail->p[0]=7;//row value at starting of snake
	tail->p[1]=0;//coloumn value at starting of snake
	a[head->p[0]][head->p[1]]='X';

}


//main process of snake
void process()
{
	int x=0,y=0,pcl=1,i;
	while(1)
	{
		if(pcl)//"pcl" poinr collected weather snake collects point(food)
		{
			x=rando();
			pcl=0;
		};
		print();
		if(crash_check())
		{
			break;
		}
		input();
		move(y);
		pcl=is_equal(x/30,x%30,head->p[0],head->p[1]);
		if(pcl)
		{
			points++;
		}
		y=pcl;
		system("cls");
	}
}



//this function is used to store points using "FILES" in c
void save()
{
	FILE *sc;
	char mode[2]="w";
	int s;
	long l;
	if(!access("scores.txt",F_OK))
	{
		mode[0]='a';
	}
	scores=fopen("scores.txt",mode);
	fprintf(scores,"%d\n",points);
	fclose(scores);
	scores=fopen("scores.txt","r");
	fseek(scores,0,SEEK_END);
	l=ftell(scores);

	fseek(scores,0,SEEK_SET);
	while(l!=ftell(scores))
	{
		fscanf(scores,"%d",&s);
		if(s>top_score)
		{
			top_score=s;
		}
	}
	fclose(scores);
}


// this function is used to print score board
void score_board()
{
	int s;
	long l;
	printf("\n\n\nYour score - %d\n",points);
	printf("\n\n\n\n\t\t\tTOP SCORE\n\t\t\t   %d\n",top_score);
	line_printer(60,'-');
	printf("\n\t\t\tSCORES\n");
	scores=fopen(".\\scores.txt","r");
	fseek(scores,0,SEEK_END);
	l=ftell(scores)-2;
	fseek(scores,0,SEEK_SET);
	while(l!=ftell(scores))
	{
		fscanf(scores,"%d",&s);
		printf("\t\t\t   %d\n",s);
	}
	fclose(scores);
}


//this function is used to play again
int again()
{
	int c;
	printf("\n\nENTER \"1\" TO CONTINUE OR\"0\" TO QUIT > ");
	scanf("%d",&c);
	if(c==0)
	{
		return 1;
	}
	return 0;
}



void delete_save()
{
	int c;
	printf("ENTER \"0\" TO RESET SCORES OR ENTER \"1\" TO CONTINUE>");
	scanf("%d",&c);
	if(c==0)
	{
		scores=fopen("scores.txt","w");
	    fclose(scores);
	}
}

//mian operation of game will happen in this
void game()
{
	int i;
	while(1)
	{
		initialize();
		process();
		delay(10);
		system("cls");
		save();
		score_board();
		delete_save();
		if(again())

		{
			exit(0);
		}
	}
}


int main()
{
	start();
	game();
}
//this is a comment by parthava
