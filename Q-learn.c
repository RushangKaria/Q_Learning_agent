#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<float.h>

#define FOR_ALL_ROWS for(i=0;i<world_R;i++)	//for less writing work
#define FOR_ALL_COLUMNS for(j=0;j<world_C;j++)
#define INFINITE for(;;)
#define SIZE 50
#define UNREACHABLE -9999
#define TERMINAL 9999
#define MODEL_TRANSITIONS 3
#define CORRECT 0
#define TOTAL_ANALYSIS 3	//to do 'x' analysis
enum {U,D,L,R};


int world_R,world_C;
int k=1;	//for policy iteration
float BETA;
float ALPHA;
double time_elapsed;
int ACTION;
float R_E=0.5;

int N_E=5;
float fixed_reward;
float transition_function[MODEL_TRANSITIONS];
float reward[SIZE][SIZE];
float utility[SIZE][SIZE];
float old_utility[SIZE][SIZE];
char policy[SIZE][SIZE]={'X'};

float Q[SIZE][SIZE][SIZE];
int FREQUENCY[SIZE][SIZE][SIZE];

int MODEL[4][25];

struct State
{
int row,column,reward;
} *current,*previous;

int main(void)
{
void fastWorld();
void initialize();
void compute_policy();
void display_policy();
void QLEARN();
srand(time(NULL));

	fastWorld();	
	initialize();
	//srand(time(NULL));

	QLEARN();

compute_policy();
display_policy();

return 0;
}

void QLEARN()
{
int exploreit();
void newtrial();
void execute(int);
void LEARN();
void display_Q();
void display_F();
int converge();
int DONE=-1;
int trials=0;

newtrial();

		while(trials<10000)
		{
		ACTION=exploreit();
		
			execute(ACTION);	
			LEARN();

//			printf("Current state [%d,%d]\n",current->row,current->column);

			if(previous->row==-1)
			{
			newtrial();
			trials++;
		//	printf("TRIAL %d\n",trials);
			}

		DONE=converge();

			if(DONE==1)
			{
			printf("DONE in %d trials\n",trials);
			break;
			}	
		}

display_Q();
display_F();

}

int converge()
{
void compute_policy();
int i,j;
char check[3][4]= { 
		{'R','R','R',' '},
		{'U',' ','U',' '},
		{'U','R','U','L'}
	        };
	compute_policy();

		if(policy[2][3]=='L')
if(policy[2][2]=='U' && policy[1][0]=='U' &&  policy[2][0]=='U' && policy[1][2]=='U' || policy[2][2]=='U' && policy[1][0]=='U' &&  policy[2][0]=='R' && policy[1][2]=='U')
		if(policy[0][0]=='R' && policy[0][1]=='R' &&  policy[0][2]=='R' && policy[2][1]=='R')
		return 1;

return -1;
			
}

void LEARN()
{
char get_char(int);
float greedy();
int f;
float r,q;


	r=reward[current->row][current->column];

		if(r>TERMINAL/2)
		r-=TERMINAL;

	FREQUENCY[ACTION][previous->row][previous->column]++;
	f=FREQUENCY[ACTION][previous->row][previous->column];
	q=Q[ACTION][previous->row][previous->column];
	
	Q[ACTION][previous->row][previous->column]+=ALPHA*(r-q+(BETA*greedy()));


//	if(previous->row==0 && previous->column==2 && ACTION==R)
//	{
//	printf("Q[%c][%d][%d]=%f\n",get_char(ACTION),previous->row,previous->column,Q[ACTION][previous->row][previous->column]);
//	getchar();
//	}

		if(reward[current->row][current->column]>TERMINAL/2)
		{
		previous->row=-1;
		previous->column=-1;
		}
		else
		{
		previous->row=current->row;
		previous->column=current->column;
		}
}

float greedy()
{
char get_char(int);
int action;
int best;

	float max=UNREACHABLE;

		for(action=U;action<=R;action++)
		{
			if(Q[action][current->row][current->column]>max)
			{
			max=Q[action][current->row][current->column];
			}
		}
//	if(previous->row==2 && previous->column==3 && ACTION==L)
//	printf("MAX Q[%c][%d][%d]=%f\n",get_char(best),current->row,current->column,max);

return max;
}

void execute(int INTENDED_ACTION)
{
void do_action(int,int,int);
char get_char(int);
int row,column;
int SIMULATED,INCORRECT;

	row=rand()%4;
	column=rand()%25;

		SIMULATED=MODEL[row][column];

//if(previous->row==2 && previous->column==3)
//{
//printf("EXPECTED ACTION WAS %c\n",get_char(INTENDED_ACTION));
//printf("SIMULATED ACTION %d\n",SIMULATED);
//}
	switch(SIMULATED)
	{
	case 0: ACTION=INTENDED_ACTION; 
		do_action(previous->row,previous->column,ACTION);
	break;

	case 1: INCORRECT=SIMULATED%2==0?SIMULATED+2:SIMULATED-2;
			if(INCORRECT>3)
			INCORRECT=U;
			if(INCORRECT<0)
			INCORRECT=R;

		ACTION=INCORRECT;
		do_action(previous->row,previous->column,ACTION);
	break;

	case 2: INCORRECT=SIMULATED%2==0?SIMULATED+3:SIMULATED-3;
			if(INCORRECT>3)
			INCORRECT=D;
			if(INCORRECT<0)
			INCORRECT=L;

		ACTION=INCORRECT;
		do_action(previous->row,previous->column,ACTION);	
	break;
	}	

}

int exploreit()
{
int best;
float max=UNREACHABLE;
int action;
int ALL_ZERO=1;
float values[4]={UNREACHABLE};

		for(action=U;action<=R;action++)
		{
			if(Q[action][previous->row][previous->column]==0)
			continue;
			else
			{
			ALL_ZERO=0;
			break;
			}
		}

		if(ALL_ZERO)
		{
			return rand()%4;
		}


		for(action=U;action<=R;action++)
		{
			if(FREQUENCY[action][previous->row][previous->column]<N_E && ALL_ZERO==0)
			{
			values[action]=1.5;			
			ALL_ZERO=1;
			}
			else	
			values[action]=Q[action][previous->row][previous->column];
			
		}

	for(action=U;action<=R;action++)
	{
		if(values[action]>max)
		{
		max=values[action];
		best=action;
		}
	}	

return best;
}

void newtrial()
{
	int x,y;
		
		do
		{
		x=rand()%world_R;
		y=rand()%world_C;
		}
		while(reward[x][y]==UNREACHABLE || reward[x][y] > TERMINAL/2);

		previous->row=x;
		previous->column=y;

		current->row=x;
		current->column=y;
}


void initialize()
{
int i,j,action;

	for(action=U;action<=R;action++)
	{
		FOR_ALL_ROWS
		FOR_ALL_COLUMNS
		{
		Q[action][i][j]=0.0;
		FREQUENCY[action][i][j]=0;
		}	
//	Q[action][0][3]=1;
//	Q[action][1][3]=-1;
	}


	current=malloc(sizeof(struct State));
	previous=malloc(sizeof(struct State));

	current->row=-1;
	current->column=-1;
	current->reward=-1;

	previous->row=-1;
	previous->column=-1;
	previous->reward=-1;

	
	for(i=0;i<4;i++)
	for(j=0;j<25;j++)
	MODEL[i][j]=UNREACHABLE;

		
	i=0;
	int frequency,row,column;

		while(i<3)
		{
			frequency=transition_function[i]*100;

				while(frequency-->0)
				{
					do
					{
					row=rand()%4;
					column=rand()%25;
					}
					while(MODEL[row][column]!=UNREACHABLE);

				MODEL[row][column]=i;
				}		

		i++;
		}

//		for(i=0;i<4;i++)
//		{
//			for(j=0;j<25;j++)
//			printf("%d ",MODEL[i][j]);
//
//		printf("\n");
//		}

//free(current);
//free(previous);
}



char get_char(int x)
{
	switch(x)
	{
	case U: return 'U';
	case D: return 'D';
	case L:	return 'L';
	case R:	return 'R';
	}
}



void do_action(int i,int j,int action)
{
int a=i,b=j;

//if(previous->row==2 && previous->column==3)
//{
//printf("DID ACTION %c\n",get_char(action));
//getchar();
//}
	switch(action)
	{
		case U: a--;
			if(a<0 || reward[a][b]==UNREACHABLE)	//hit wall or pit
			{					//return same state
			current->row=i;
			current->column=j;
			}
			else
			{
			current->row=a;
			current->column=b;
			}
		break;

		case D: a++;
			if(a>world_R-1 || reward[a][b]==UNREACHABLE)
			{
			current->row=i;
			current->column=j;
			}
			else
			{
			current->row=a;
			current->column=b;
			}
		break;

		case L: b--;
			if(b<0 || reward[a][b]==UNREACHABLE)
			{
			current->row=i;
			current->column=j;
			}
			else
			{
			current->row=a;
			current->column=b;
			}
		break;

		case R: b++;
			if(b>world_C-1 || reward[a][b]==UNREACHABLE)
			{
			current->row=i;
			current->column=j;
			}
			else
			{
			current->row=a;
			current->column=b;
			}
		break;
	}

//if(previous->row==2 && previous->column==3 && ACTION==L)
//{
//printf("PREVIOUS STATE [%d,%d]\n",previous->row,previous->column);
//printf("DID ACTION %c\n",get_char(action));
//printf("CURRENT STATE [%d,%d]\n",current->row,current->column);
//getchar();
//}
}

inline void fastWorld()
{	
void display_world();

int i,j;

	world_R=3;
	world_C=4;

	BETA=0.9;
	ALPHA=1;
	transition_function[0]=0.8;
	transition_function[1]=0.1;
	transition_function[2]=0.1;


				FOR_ALL_ROWS
				FOR_ALL_COLUMNS
				reward[i][j]=-0.04;

			reward[1][1]=UNREACHABLE;
			utility[1][1]=UNREACHABLE;
			
			reward[0][3]=1+TERMINAL;
			utility[0][3]=1;	

			reward[1][3]=-1+TERMINAL;
			utility[1][3]=-1;
		

display_world();
}


inline void inputWorld()
{	
void display_world();

int i=-1,j=-1;
int temp,temp2;
float reward_of;

	printf("Please enter the characteristics of the world\nROWS=");
	scanf("%d",&world_R);

	printf("COLUMNS=");
	scanf("%d",&world_C);

	printf("BETA=");
	scanf("%f",&BETA);

	printf("Please enter the transition function probabilities in descending order...since correct action is at index 0\n");

		for(i=0;i<MODEL_TRANSITIONS;i++)
		{
		printf("Enter value:");
		scanf("%f",&transition_function[i]);
		}

	printf("WHICH TYPE OF REWARD DO YOU WANT TO CHOOSE\n1.FIXED FOR ALL STATES\n2.DIFFERENT FOR ALL THE STATES\nENTER YOUR OPTION: ");
	scanf("%d",&temp);

		switch(temp)
		{
		case 1: printf("Enter the reward:");
			scanf("%f",&fixed_reward);

				FOR_ALL_ROWS
				FOR_ALL_COLUMNS
				reward[i][j]=fixed_reward;
		break;

		case 2: FOR_ALL_ROWS
			{
				FOR_ALL_COLUMNS
				{
				printf("Enter the reward for state [%d,%d]:",i,j);
				scanf("%f",&reward[i][j]);
				}
			}
		break;
		}

	printf("Enter the pits of the world....Press -1 to stop ");	

		INFINITE
		{
			printf("\nPIT_ROW #=");
			scanf("%d",&temp);
			
				if(temp<0)
				break;
			
			printf("PIT_COLUMN #=");
			scanf("%d",&temp2);

			reward[temp][temp2]=UNREACHABLE;
			utility[temp][temp2]=UNREACHABLE;
		}


	printf("Enter the terminal states and their rewards....Press -1 to stop");

		INFINITE
		{
			printf("\nTERMINAL_ROW #=");
			scanf("%d",&temp);
				
				if(temp<0)
				break;
			
			printf("TERMINAL_COLUMN #=");
			scanf("%d",&temp2);

			printf("TERMINAL_REWARD=");
			scanf("%f",&reward_of);	
			
			reward[temp][temp2]=reward_of+TERMINAL;
			utility[temp][temp2]=reward_of;	
		}

display_world();
}

void display_world()
{
int i,j;

printf("###################### WORLD #####################\n");

	FOR_ALL_ROWS
	{
		FOR_ALL_COLUMNS
			if(reward[i][j] > TERMINAL/2)	
			printf("%.2f\t",reward[i][j]-TERMINAL);
			else
			printf("%.2f\t",reward[i][j]);
			

	printf("\n");
	}

printf("####################################################\n");
}

void display_utility()
{
int i,j;

printf("###################### UTILITY #####################\n");

	FOR_ALL_ROWS
	{
		FOR_ALL_COLUMNS
			if(utility[i][j]==UNREACHABLE)
			printf("NULL\t");
			else
			printf("%.2f\t",utility[i][j]);
			

			

	printf("\n");
	}

printf("####################################################\n");
}

void display_policy()
{
int i,j;

printf("###################### OPTIMUM POLICY #####################\n");

	FOR_ALL_ROWS
	{
		FOR_ALL_COLUMNS
			printf("%c\t",policy[i][j]);

	printf("\n");
	}

printf("############################################################\n");
}

void display_Q()
{
int i,j,action;

	for(action=U;action<=R;action++)
	{
	printf("%c\n",get_char(action));
		
		FOR_ALL_ROWS
		{
		FOR_ALL_COLUMNS
		printf("%f\t",Q[action][i][j]);

		printf("\n");
		}
	}
}

void display_F()
{
int i,j,action;

	for(action=U;action<=R;action++)
	{
	printf("%c\n",get_char(action));
		
		FOR_ALL_ROWS
		{
		FOR_ALL_COLUMNS
		printf("%d\t",FREQUENCY[action][i][j]);

		printf("\n");
		}
	}
}

void compute_policy()
{
char get_char(int);
int i,j,action;
float max=UNREACHABLE;
int best;

	FOR_ALL_ROWS
	FOR_ALL_COLUMNS
	{
		if(reward[i][j] > TERMINAL/2 || reward[i][j]==UNREACHABLE)
		continue;

		for(action=U;action<=R;action++)
		{
		//printf("Q[%d][%d][%d]=%f\n",action,i,j,Q[action][i][j]);
			if(Q[action][i][j]>max)
			{
			max=Q[action][i][j];
			best=action;
			}
		//getchar();

		}

		//printf("Best action was %c\n",get_char(best));			
		policy[i][j]=get_char(best);
		max=UNREACHABLE;
	}
}


int get_policy_action(int i,int j)
{
//printf("Policy is %c",policy[i][j]);

	switch(policy[i][j])
	{
	case 'U': return 0;
	case 'D': return 1;
	case 'L': return 2;
	case 'R': return 3;
	}
}

void random_policy()
{
char get_char(int);
int i,j;

srand(time(NULL)); //set seed

	FOR_ALL_ROWS
	{
		FOR_ALL_COLUMNS
		{
			if(reward[i][j]>TERMINAL/2 || reward[i][j]==UNREACHABLE)
			continue;

		policy[i][j]=get_char(rand()%4);
		}
	}
}
