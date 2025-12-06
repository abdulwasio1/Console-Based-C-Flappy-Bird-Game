#include<iostream>
#include<windows.h> //for Accessing Windows OS functions
#include<stdlib.h> //for exit(), rand() and srand() functions to generate random numbers(Gap Pos)
#include<time.h>  //for time function
#include<conio.h> //for getch() like functions

#define SCREEN_WIDTH 90 //Constant Paramenter | can be writen as | const int SCREEN_WIDTH = 90;
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define GAP_SIZE 6

int score =0;
int pipe_flag[2];
int pipe_pos[2];
int gap_pos[2];
int bird_pos = 6;
char bird[2][6] = {'/','-','-','o','\\',' ','|','_','_','_',' ','>'};

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); //to handle Console Screen
COORD cursor_points; //to get coordinate points of console

void gotoxy(int a , int b){
	cursor_points.X = a;
	cursor_points.Y =b;
	SetConsoleCursorPosition(console , cursor_points); //SetConsoleCursorPosition | Build in Function which set position of cusror
}

void set_cursor(bool visible , DWORD size){ //pass 0,0 parameters | Work : It will hide blinking text cursor which looks anoying like _
	if(size==0)
	size =20; //pending
	CONSOLE_CURSOR_INFO cursor_info;
	cursor_info.bVisible = visible; //false NOTE: yaha par agar visible ase use kro to error aye ga so use this Visible "V" bari
	cursor_info.dwSize = size;
	SetConsoleCursorInfo(console ,&cursor_info); //SetConsoleCursorInfo | Build In Function Which hold information of Cursor
	
}

//ALL FUNCTIONS PROTOTYPES

void play();
void draw_border();
void gen_pos(int ind);
void draw_bird();
void draw_pipe(int ind);
int collision();
void erase_bird();
void erase_pipe(int ind);
void update_score();
void game_over();
void instruction();

using namespace std;
int main(){
	set_cursor(0,0); 
	srand(time(NULL)); //for random values after each game
	gotoxy(10,5);cout<<"-----------------";
	gotoxy(10,6);cout<<"FLAPPY BIRD GAME";
	gotoxy(10,7);cout<<"-----------------";
do{
	system("cls");
	for(int a=0 ; a<20 ; a++){
		gotoxy(7+a ,7);cout<<"*";
		gotoxy(7+a , 15);cout<<"*";
	}
	for(int a=0 ; a<7; a++){
		gotoxy(7 , 8+a);cout<<"|";
		gotoxy(26 , 8+a);cout<<"|";
	}
	gotoxy(10,9);cout<<"1. Start Game";
	gotoxy(10,10);cout<<"2. Instructions";
	gotoxy(10,11);cout<<"0. Exit Game";
	gotoxy(10,13);cout<<"Enter Choice : ";
	char ch = getch();
	if(ch=='1'){
		play();
	}else if(ch=='2'){
		instruction();
	}else if(ch=='0'){
		cout<<"\n\n";
		exit(0);
		
	/*
		exit() is bulid in function comes from stdlib library which IMMEDIATELY  exit the program
		Exit Code	Meaning
		exit(0)	Normal termination (Success)
		exit(1)	Abnormal termination (Error)
		exit(2)	Another error code
		exit(-1)	Failure
	*/
	
	}
	
}while(true);	

return 0;

}

void play(){
	//Reset all parameters first such that for every new game we get values from zero again
	score = 0;
	pipe_flag[0] =1; //activate 1st flag/pipe
	pipe_flag[1] =0; //unactivated
	pipe_pos[0] = pipe_pos[1] = 4; //set postion for every new pipe
	bird_pos = 6;
	
	system("cls"); //for Clear Screen after every try
	draw_border();
	gen_pos(0); //generate random values for 1st pipe
	update_score(); 
	
	
	gotoxy(WIN_WIDTH+3 , 4);cout<<"----------------";
	gotoxy(WIN_WIDTH+6 , 5);cout<<"FLAPPY BIRD";
	gotoxy(WIN_WIDTH+3 , 6);cout<<"----------------";
	gotoxy(WIN_WIDTH+7 , 14);cout<<"Control";
	gotoxy(WIN_WIDTH+3 , 15);cout<<"---------------";
	gotoxy(WIN_WIDTH+3 , 16);cout<<"SPACE BAR = JUMP";
	gotoxy(10,5);cout<<"Press any Key to Continue";
	getch();
	gotoxy(10,5);cout<<"                           ";
	
	
	while(true){
		if(kbhit()){
			char ch	= getch();
			if(ch==32){ //space to Jump , ASC Code of SPace = 32
				if(bird_pos>3){
					bird_pos-=3; //Jumping Effect
				}
			}
			if(ch==27){ //Esc to go back to home, ASC Code of Esc = 27
				break;
			}
		}
			
		
		draw_bird();
		draw_pipe(0);
		draw_pipe(1);
		
		if(collision() == 1){ //check pipe collsion
			return; 
		}
		
//		GAME LOOP = RESET --> DRAW --> ERASE --> CHECK/UPDATE CONDITIONS --> DRAW WITH UPDATED VALUES, IF GAME OVER
//		            ^          |                                                 |                             |        
//		            |          ----------------------------------------------<---                              |
//		            ---------------------------------------------------------------------------------<----------
//	
		
		Sleep(100); //make 100 millisec delay after each frame(loop ilteration)
		erase_bird();
		erase_pipe(0);
		erase_pipe(1);
		
		if(bird_pos>SCREEN_HEIGHT-3){ //check floor collisoion
			game_over();
			return;
		}
		
		if(pipe_flag[0] ==1){
			pipe_pos[0]+=2;
		}
		
		if(pipe_flag[1] ==1){
			pipe_pos[1]+=2;
		}
		bird_pos+=1;
		
		if(pipe_pos[0]>=40 && pipe_pos[0]<42){
			pipe_flag[1] = 1; //activate 2nd Pipe
			pipe_pos[1] = 4; //set postion for 2nd
			gen_pos(1);     //generate random values for 2nd pipe
		}
		if(pipe_pos[0]>68){
			score++;
			update_score();
			pipe_flag[1] =0; //jab kio b pipe 68th position pa aye to wo deactivate ho jaye ga or 1st pipe ban jaye ga 
			//In short: Pipe 1 become Pipe 0, Reason: To create Infinte Pipes Effect using only 2 Pipes
			pipe_pos[0] =pipe_pos[1]; //copy all properties
			gap_pos[0] = gap_pos[1]; //copy all properties
			
		}
	}
	
	
}

void draw_border(){
	for(int a=0 ; a<=SCREEN_WIDTH ; a++){
		gotoxy(a , 0);cout<<"||";
		gotoxy(a , SCREEN_HEIGHT);cout<<"||"; 
	}
	for(int a=0 ; a<SCREEN_HEIGHT ; a++){
		gotoxy(0 , a);cout<<"||";
		gotoxy(SCREEN_WIDTH , a);cout<<"||";
	}
	for(int a= 0 ; a<SCREEN_HEIGHT ; a++){
		gotoxy(WIN_WIDTH , a);cout<<"||";
	}
	cout<<endl;
}

void gen_pos(int ind){
	gap_pos[ind] = (rand()% 14) + 3;
}

void draw_bird(){
	for(int a=0 ; a<2; a++){
		for(int b=0 ; b<6 ; b++){
			gotoxy(b+2 , bird_pos+a);cout<<bird[a][b];
		}
	}
}

void draw_pipe(int ind){
	if(pipe_flag[ind] == 1){
		for(int a=0 ; a<gap_pos[ind] ; a++){
			gotoxy(WIN_WIDTH - pipe_pos[ind] , a+1);cout<<"****";
		}
		for(int a=GAP_SIZE+gap_pos[ind] ; a<SCREEN_HEIGHT-1 ; a++){
			gotoxy(WIN_WIDTH - pipe_pos[ind] , a+1);cout<<"****";
		} 
	}
}

int collision(){
	if(pipe_pos[0]>61){
		if(bird_pos<gap_pos[0] || bird_pos>GAP_SIZE+gap_pos[0]){
			game_over();
			return 1;
		}
	}
	return 0;
}

void erase_bird(){
	for(int a=0 ; a<2; a++){
		for(int b=0 ; b<6 ; b++){
			gotoxy(b+2 , bird_pos+a);cout<<" ";
		}
	}
}

void erase_pipe(int ind){
	if(pipe_flag[ind] == 1){
		for(int a=0 ; a<gap_pos[ind] ; a++){
			gotoxy(WIN_WIDTH - pipe_pos[ind] , a+1);cout<<"    ";
		}
		for(int a=GAP_SIZE+gap_pos[ind] ; a<SCREEN_HEIGHT-1 ; a++){
			gotoxy(WIN_WIDTH - pipe_pos[ind] , a+1);cout<<"    ";
		} 
	}
}

void update_score(){
	gotoxy(WIN_WIDTH+6 , 10);cout<<"Score : "<<score;
}

void game_over(){
	system("cls");
	cout<<endl;
	cout<<"\t\t---------------------------"<<endl;
	cout<<"\t\t-------- Game Over --------"<<endl;
	cout<<"\t\t----- Your Score : "<<score<<" -----"<<endl;
	cout<<"\t\t---------------------------"<<endl<<endl;
	cout<<"\t\tPress any key to go back to menu.";
	getch();
}

void instruction(){
	system("cls");
	gotoxy(10,9);cout<<"-----------INSTRUCTIONS-----------";
	gotoxy(10,10);cout<<"----------------------------------";
	gotoxy(10,12);cout<<"o Press spacebar to make bird fly";
	gotoxy(10,13);cout<<"o Press Esc to Over Game";
	gotoxy(10,14);cout<<"o Press any key to go back to menu";
	getch();
}







