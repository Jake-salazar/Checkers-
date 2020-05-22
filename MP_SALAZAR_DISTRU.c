#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef char Gameboard[8][8]; // SET P
// SET A : {x is an element of  positive integers | x <= 8}
// SET A is the set for rows and columns
// P : A × A forms a a board with A rows X A columns



void display(Gameboard B) // To Display the Current State of the Board
{
	
	int i;
	int j;
	
	for (i=0;i<8;i++)
	{
		for (j=0;j<8;j++)
			printf("%3c |", B[i][j]); 	
		
		printf("  %d", i+1);
		printf("\n");
		printf("========================================= \n");
	}	
	
	printf("\n %2d | %2d | %2d | %2d | %2d | %2d | %2d | %2d", 1, 2, 3, 4, 5, 6, 7, 8);
}




void initialize (Gameboard B) 
// Places all S pieces
// Determine the (x,y) coordinates that are ALPHA, BETA, and FREE
{
	int i;
	int j;
	
	for(i=0; i<8; i++)
	{
		for(j=0; j<8; j++)
		{
			B[i][j] = ' '; // Initialize by turning all (x,y) in the P (board) into FREE
		}
	}
	
	for(i=0; i<8; i++)
	{
		for(j=0; j<8; j++) 
		{
			// ALPHA = {(x, y) is an element of S | x <= 3}
			// ALPHA is symbolised by X
			
			if(i < 3 && i % 2 == 0 && j % 2 == 1) 
				B[i][j] = 'X';
			else if(i < 3 && i % 2 == 1 && j % 2 == 0)
				B[i][j] = 'X';
			
			// BETA = {(x, y) is an element of S | x >= 6}
			// BETA is symbolised by Y
			
			else if(i > 4 && i % 2 == 1 && j % 2 == 0)
				B[i][j] = 'Y';
			else if(i > 4 && i % 2 == 0 && j % 2 == 1)
				B[i][j] = 'Y';
		}
	}
			
}

int Status(Gameboard B)
{
	int i,j;
	int ctrX = 0;
	int ctrY = 0;
	
	for(i=0; i<8; i++)
	{
		for(j=0; j<8; j++)
		{	
			if(B[i][j] == 'X')
				ctrX++;			// counts how many ALPHA (X) is left
		
			if(B[i][j] == 'Y')
				ctrY++;			// counts how many BETA (Y) is left
		}	
	}
	
	// OVER if and only if (|ALPHA| = 0 exclusive-or |BETA| = 0)
	
	if( (ctrX == 0 && ctrY > 0) ) 
		return 1; // OVER is true, Beta won
	else if( (ctrY == 0 && ctrX > 0) )
		return 2; // OVER is true, Alpha won
	else
		return 0; // not OVER
}

int aValid (Gameboard B, int a, int b, int x, int y) // To check if the move is within the allowed moves by the specs
{
	// S : {(x, y) is element of P | (x mod 2 = 1 && y mod 2 = 0) v (x mod 2 = 0 && y mod 2 = 1)}
	
	// S is the Set of all (x,y) coordinates that ALPHA or BETA can move into

	if(y - b != 1 || (x - a != 1 && x - a != -1)) // more than one tile, and not diagonal
		return 1;
	else if (B[y-1][x-1] == 'X') // target coordinate is occupied by ALPHA
		return 2;
	else if(B[y-1][x-1] == 'Y') //  target coordinate is occupied by BETA
		return 3;
	else 
		return 4;  // FREE, valid move 
				
}

int bValid (Gameboard B, int a, int b, int x, int y)
{
	// S : {(x, y) is element of P | (x mod 2 = 1 && y mod 2 = 0) v (x mod 2 = 0 && y mod 2 = 1)}
	
	// S is the Set of all (x,y) coordinates that ALPHA or BETA can move into
	
	if(y - b != -1 || (x - a != 1 && x - a != -1)) // more than one tile, and not diagonal
		return 1;
	else if (B[y-1][x-1] == 'Y') // target coordinate is occupied by BETA
		return 2;
	else if(B[y-1][x-1] == 'X') //  target coordinate is occupied by ALPHA
		return 3;
	else 
		return 4;  // FREE, valid move 				
}


		
void aMove (Gameboard B)
{
	int a,b; // PREV (a,b) is a coordinate pair which contains the current position or the position of ALPHA or BETA BEFORE a move
	
	int x,y; // NEXT (x,y) is a coordinate pair which contains the current position or the position of ALPHA or BETA AFTER a move
	int ok = 0; 
	// OK is an element of  B
	// B : {true, false}
	// In this case, B is represented by Boolean Values 1 (true) and 0 (false)
	// B : {1, 0}
	int i,j;
	
	i = 0;
	while(!i)
	{
		printf("\n\nenter coordinate (x <space> y) of piece to move: ");
		scanf("%d %d", &a, &b); 
		if( (a < 1 || a > 8) || (b < 1 || a > 8) )
			printf("You entered an integer not within 1 to 8 \n");
		
		else
		{
			if(B[b-1][a-1] == 'X')
			{
				if(a > 1 && a < 8)
				{
					if((B[b][a] == ' ' || B[b][a] == 'Y') || ( B[b][a-2] == ' '|| B[b][a-2] == 'Y'))
						i = 1;
					
					else // target coordinate is occupied by own piece
					printf("Invalid move. That piece has no free space to move into! \n");
				}
				
				else if(a == 1)
				{
					if((B[b][a] == ' ' || B[b][a] == 'Y') )
						i = 1;
					
					else // target coordinate is occupied by own piece
					printf("Invalid move. That piece has no free space to move into! \n");
				}
				
				else if(a == 8)
				{
					if(( B[b][a-2] == ' '|| B[b][a-2] == 'Y'))
						i = 1;
					
					else // target coordinate is occupied by own piece
					printf("Invalid move. That piece has no free space to move into! \n");
				}
				
			}
		
			else // target coordinate is occupied by own piece
				printf("Invalid move. Given Coordinate does not contain a piece of yours!!! \n");
		}
	}		

	
	do
	{
		
		printf("enter coordinate (x <space> y), where to put the piece: ");
		scanf("%d %d", &x, &y);
		if( (x < 1 || x > 8) || (y < 1 || y > 8) )
			printf("You entered an integer not within 1 to 8 \n");
			
		else
		{
			j = aValid(B, a, b, x, y);
			
			switch(j)
			{
				case 1: printf("Invalid move. Move only one tile diagonally and forward! \n"); break;
				case 2: printf("Invalid move. Target coordinate is occupied by another piece of yours. \n"); break;
				case 3: ok = 1;
						printf("Enemy piece taken. \n"); break;
				case 4: ok = 1; break;
			}
			
			if(ok)
			{
				B[b-1][a-1] = ' ';
				B[y-1][x-1] = 'X';
			}
		}
		
	} while(!ok);
}
			
void bMove (Gameboard B)
{
	
	int a,b; // PREV (a,b) is a coordinate pair which contains the current position or the position of ALPHA or BETA BEFORE a move
	
	int x,y; // NEXT (x,y) is a coordinate pair which contains the current position or the position of ALPHA or BETA AFTER a move
	int ok = 0;
	// OK is an element of  B
	// B : {true, false}
	// In this case, B is represented by Boolean Values 1 (true) and 0 (false)
	// B : {1, 0}
	int i,j;

	i = 0;
	while(!i)
	{
		printf("\n\nenter coordinate (x <space> y) of piece to move: ");
		scanf("%d %d", &a, &b);
		
		if( (a < 1 || a > 8) || (b < 1 || b > 8) )
			printf("You entered an integer not within 1 to 8 \n");
		
		else
		{
			if(B[b-1][a-1] == 'Y')
			{
				if(a > 1 && a < 8)
				{
					if( (B[b-2][a] == ' ' || B[b-2][a] == 'X' ) || (B[b-2][a-2] == ' ' || B[b-2][a-2] == 'X'))  
						i = 1;
					else // target coordinate is occupied by own piece
					printf("Invalid move. That piece has no free space to move into! \n");
				}
			
				else if(a==1)
				{
					if( (B[b-2][a] == ' ' || B[b-2][a] == 'X' ) )
						i = 1;
					else // target coordinate is occupied by own piece
					printf("Invalid move. That piece has no free space to move into! \n");
				}
				
				else if(a==8)
				{
					if( (B[b-2][a-2] == ' ' || B[b-2][a-2] == 'X' ) )
						i = 1;
					else // target coordinate is occupied by own piece
					printf("Invalid move. That piece has no free space to move into! \n");
				}
			}
		
			else
				printf("Invalid move. Given Coordinate does not contain a piece of yours!!! \n");
		}
	}
		
	do
	{
		printf("enter coordinate (x <space> y), where to put the piece: ");
		scanf("%d %d", &x, &y);
		
		if( (x < 1 || x > 8) || (y < 1 || y > 8) )
			printf("You entered an integer not within 1 to 8 \n");
			
		else
		{
			j = bValid(B, a, b, x, y);
			
			switch(j)
			{
				case 1: printf("Invalid move. Move only one tile diagonally and forward! \n"); break;
				case 2: printf("Invalid move. Target coordinate is occupied by another piece of yours. \n"); break;
				case 3: ok = 1;
						printf("Enemy piece taken. \n"); break;
				case 4: ok = 1; break;
			}
			
			if(ok)
			{
				B[b-1][a-1] = ' ';
				B[y-1][x-1] = 'Y';
			}
		}
		
	} while(!ok);
}


void intro()
{
	system("cls");
	printf("Hello there \nThis is a machine project that is kinda similar to checkers \n");
	system( "pause" );
	printf("\n");
	printf("Lemme tell u how it works before u proceed \n");
	system( "pause" );
	printf("\n");
	printf("Since it is similar to checkers, we need two players. Sorry, no AI yet. \n");
	printf("Player Alpha gets to move first \n");
	printf("First, you need to enter the coordinate of the piece you want to move. \n");
	printf("If u're piece is at (1, 4), input ""1 4"". Then input the destination in the same manner. \n\n\n\n");
	printf("U probably ready now. Let's G!");
	printf("\n");
	system( "pause" );
	system("cls");
	
}

void startgame(Gameboard board)
{
	int i=0;
	int stat;
	
do{
		display(board);
		printf("\n\n");
		
		if(i % 2 == 0) 
		// System Initialization aTurn = true
		// i is initialized to 0, which is an even number
		// 0 % 0 is zero making this statement always true at the beginning
		{
			// aTurn or ALPHA turn
			printf("Alpha Turn");
			aMove(board);
		}
		else
		{
			// bTurn or BETA turn
			printf("Beta Turn");
			bMove(board);
		}
		
		i++; 
		
		system("cls");
		
	}while( !Status(board) );		
	
	stat = Status(board);
	if(stat == 1)
		printf("Lmao, beta won \n");
	else if(stat == 2)
		printf("lmfao, alpha won \n");
	
	system("pause");
}

void Title()
{	
	printf("\n\n");
	printf("   ______    __       __    _________     _______    __     __    _________     ___________        _____________\n");
	printf("  |   ___|  |**|     |**|  |*** _____|   |   ____|  |**|   |**|  |*** _____|   |************|     |******_______|\n");
	printf("  |**|      |**|     |**|  |***|         |**|       |**|  |**|   |***|         |***|      |**|    |*****|      \n");
	printf("  |**|      |**|_____|**|  |***|_____    |**|       |**| |**|    |***|_____    |***|______|**|    |*****|_______  \n");
	printf("  |**|      |** _____ **|  |*** _____|   |**|       |*****|      |*** _____|   |************|     |_______ *****| \n");
	printf("  |**|      |**|     |**|  |***|         |**|       |*****|_     |***|         |*********|                |*****| \n");
	printf("  |**|___   |**|     |**|  |***|         |**|____   |**| |**|    |***|         |***|   |***|       _______|*****| \n");
	printf("  |******|  |**|     |**|  |***|______   |*******|  |**|  |**|   |***|______   |***|    |***|     |*************| \n");
	printf("  |******|  |**|     |**|  |**********|  |*******|  |**|   |**|  |**********|  |***|     |***|    |*************| \n");                        
}



int main()
{
	Gameboard board;
	initialize(board);
	int bExit = 0;
	int nChoice = 0; 
	
	while(!bExit)
	{
		
		do {
		system("cls");
		Title();
		printf("\n");
		printf("************************************************************************************************************************\n");
		printf("************************************************************************************************************************\n");
		printf("                                                    GAME MENU:                                                         \n");
		printf("                                           [1] - HOW THE GAME WORKS                                                     \n");
		printf("                                           [2] - START THE GAME                                                         \n");
		printf("                                           [3] - EXIT THE GAME                                                          \n");
		printf("************************************************************************************************************************\n");
		printf("************************************************************************************************************************\n");
		scanf("%d",&nChoice);
		
	}while(nChoice != 1 && nChoice !=2 && nChoice !=3);
		
	if (nChoice == 1)
		intro();
	else if (nChoice == 2)
		{
			system("cls");
			startgame(board);
		}
	else if (nChoice ==3)
		bExit = 1;	
	}
			
	
	return 0;
}
	

