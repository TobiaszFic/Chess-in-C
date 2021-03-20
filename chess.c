
/*
The challenge for this program is to make it work without the need to call any external libraries, meaning only using stdio.h

The entire program works as advertised and enables two playes to engage in a game of chess in a semi-legal manner

Rules for the movement of pieces, as well as the concept of check and en passant have all been accounted for, with the exception of the concept of stale mate.
*/


#include <stdio.h>

int checkifinarray(char x, char arr[], int size) //this function checks whether or not an item is contained within an array and returns the index of that item if found
{
	for(int i = 0 ; i < size; i++ )
	{
		if (x == arr[i])
		{
			return i;
		}
	}
	return -1;
}
int max(int a, int b) //this function takes an input of two integers and returns the larger one
{
	return a <= b ? b : a; 
}
int min(int a, int b) //this function takes an input of two integers and returns the smaller one
{
	return a <= b ? a : b;
}
int sgn(int a) //this function takes an input of one integer and return its signum (-1 or 1, where 0 is considered a positive integer)
{
	return a >= 0 ? 1 : -1;
}
int abv(int a) //this function takes an input of one integer and returns its absolute value
{
	return a >= 0 ? a : -a;
}
void clrscr(void)
{
	for(int i = 0; i<40; i++)
		printf("\n");	
}



char board[8][8] = { 
	{'r','n','b','q','k','b','n','r'}, //this is the starting board matrix. 
	{'p','p','p','p','p','p','p','p'},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{'P','P','P','P','P','P','P','P'},
	{'R','N','B','Q','K','B','N','R'}};
/*char board[8][8] = { 
	{' ',' ',' ',' ',' ',' ',' ','r'}, //this is the test board matrix. Used only to test the features. All moves will be categorized here
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{'r',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ','K',' ',' ',' ',' '}};*/


void printlogo(void) //this function prints the applet logo
{
	clrscr();
	printf("\n=============================================================================================================\n");
	printf("||        _______   ______   ____     __    __   _   _     _     __     _                                  ||\n");
	printf("||       |__   __| | _____| |  _ \\   |  \\  /  | [_] | \\   | |   /  \\   | |             ___/\\               ||\n");
	printf("||          | |    | |___   | |_/ /  |   \\/   | | | |   \\ | |  / /\\ \\  | |            /   ^/\\              ||\n");
	printf("||          | |    |  ___|  |    /   | |\\  /| | | | | |\\ \\| | | |__| | | |           /     /|\\             ||\n");
	printf("||          | |    | |____  | |\\ \\   | | \\/ | | | | | | \\   | |  __  | | |___       /  o    /|\\            ||\n");
	printf("||          |_|    |______| |_| \\_\\  |_|    |_| |_| |_|   \\_| |_|  |_| |_____|     /         /|\\           ||\n");
	printf("||                                                                                /    __/    /|\\          ||\n");
	printf("||        _________    _____    _____  ____________       _____         _____    |    /\\       /|          ||\n");
	printf("||       /         \\   \\   /    \\   /  \\          /      /     \\       /     \\    \\_//  \\        \\         ||\n");
	printf("||      /   ______  |  |   |    |   |  |  _______/      /   /\\__\\     /   /\\__\\         /        |         ||\n");
	printf("||     /   /      \\_|  |   |    |   |  |  |            /   /         /   /            _/         \\         ||\n");
	printf("||     |   |           |   |____|   |  |  |______      \\   \\____     \\   \\____       /            \\        ||\n");
	printf("||     |   |           |            |  |        /       \\____   \\     \\____   \\     /              \\       ||\n");
	printf("||     |   |           |   ______   |  |  _____/             \\   \\         \\   \\    \\_____    _____/       ||\n");
	printf("||     |   |       _   |   |    |   |  |  |           ____   /   /  ____   /   /         /    \\            ||\n");
	printf("||     \\   \\______/ |  |   |    |   |  |  |_______    |   \\_/   /   |   \\_/   /          \\    /            ||\n");
	printf("||      \\           |  |   |    |   |  |          \\    \\       /     \\       /        __//    \\\\__         ||\n");
	printf("||       \\_________/   /___\\    /___\\  /___________\\    \\____ /       \\____ /        /            \\        ||\n");
	printf("||                                                                                  [==__________==]       ||\n");
	printf("||                                                                                                         ||\n");
	printf("||                                                                                 @ Tobiasz Fic 2021      ||\n");
	printf("=============================================================================================================\n\n");
	for (int i = 1; i<5; i++)
	{
		printf("\n");
	}
}



void printboard(void) //this function prints an updated board (inputs from the board matrix)
{
	clrscr();
	printf("\n\t__________________________________________________________________________________\n");
	printf("\t|   |                                                                        |   |\n");
	printf("\t|   ||   A   ||   B   ||   C   ||   D   ||   E   ||   F   ||   G   ||   H   ||   |\n");
	printf("\t|___|________________________________________________________________________|___|\n");
	printf("\t|   |         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX|   |\n");
	printf("\t|   |         X       X         X       X         X       X         X       X|   |\n");
	printf("\t| 8 |    %c    X   %c   X    %c    X   %c   X    %c    X   %c   X    %c    X   %c   X| 8 |\n", board[0][0], board[0][1], board[0][2], board[0][3], board[0][4], board[0][5], board[0][6], board[0][7] );
	printf("\t|   |         X       X         X       X         X       X         X       X|   |\n");
	printf("\t|___|         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX|___|\n");
	printf("\t|   |XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         |   |\n");
	printf("\t|   |X       X         X       X         X       X         X       X         |   |\n");
	printf("\t| 7 |X   %c   X    %c    X   %c   X    %c    X   %c   X    %c    X   %c   X    %c    | 7 |\n", board[1][0], board[1][1], board[1][2], board[1][3], board[1][4], board[1][5], board[1][6], board[1][7] );
	printf("\t|   |X       X         X       X         X       X         X       X         |   |\n");
	printf("\t|___|XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         |___|\n");
	printf("\t|   |         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX|   |\n");
	printf("\t|   |         X       X         X       X         X       X         X       X|   |\n");
	printf("\t| 6 |    %c    X   %c   X    %c    X   %c   X    %c    X   %c   X    %c    X   %c   X| 6 |\n", board[2][0], board[2][1], board[2][2], board[2][3], board[2][4], board[2][5], board[2][6], board[2][7] );
	printf("\t|   |         X       X         X       X         X       X         X       X|   |\n");
	printf("\t|___|         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX|___|\n");
	printf("\t|   |XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         |   |\n");
	printf("\t|   |X       X         X       X         X       X         X       X         |   |\n");
	printf("\t| 5 |X   %c   X    %c    X   %c   X    %c    X   %c   X    %c    X   %c   X    %c    | 5 |\n", board[3][0], board[3][1], board[3][2], board[3][3], board[3][4], board[3][5], board[3][6], board[3][7] );
	printf("\t|   |X       X         X       X         X       X         X       X         |   |\n");
	printf("\t|___|XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         |___|\n");
	printf("\t|   |         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX|   |\n");
	printf("\t|   |         X       X         X       X         X       X         X       X|   |\n");
	printf("\t| 4 |    %c    X   %c   X    %c    X   %c   X    %c    X   %c   X    %c    X   %c   X| 4 |\n", board[4][0], board[4][1], board[4][2], board[4][3], board[4][4], board[4][5], board[4][6], board[4][7] );
	printf("\t|   |         X       X         X       X         X       X         X       X|   |\n");
	printf("\t|___|         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX|___|\n");
	printf("\t|   |XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         |   |\n");
	printf("\t|   |X       X         X       X         X       X         X       X         |   |\n");
	printf("\t| 3 |X   %c   X    %c    X   %c   X    %c    X   %c   X    %c    X   %c   X    %c    | 3 |\n", board[5][0], board[5][1], board[5][2], board[5][3], board[5][4], board[5][5], board[5][6], board[5][7] );
	printf("\t|   |X       X         X       X         X       X         X       X         |   |\n");
	printf("\t|___|XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         |___|\n");
	printf("\t|   |         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX|   |\n");
	printf("\t|   |         X       X         X       X         X       X         X       X|   |\n");
	printf("\t| 2 |    %c    X   %c   X    %c    X   %c   X    %c    X   %c   X    %c    X   %c   X| 2 |\n", board[6][0], board[6][1], board[6][2], board[6][3], board[6][4], board[6][5], board[6][6], board[6][7] );
	printf("\t|   |         X       X         X       X         X       X         X       X|   |\n");
	printf("\t|___|         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX|___|\n");
	printf("\t|   |XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         XXXXXXXXX         |   |\n");
	printf("\t|   |X       X         X       X         X       X         X       X         |   |\n");
	printf("\t| 1 |X   %c   X    %c    X   %c   X    %c    X   %c   X    %c    X   %c   X    %c    | 1 |\n", board[7][0], board[7][1], board[7][2], board[7][3], board[7][4], board[7][5], board[7][6], board[7][7] );
	printf("\t|   |X       X         X       X         X       X         X       X         |   |\n");
	printf("\t|___|XXXXXXXXX_________XXXXXXXXX_________XXXXXXXXX_________XXXXXXXXX_________|___|\n");
	printf("\t|   |                                                                        |   |\n");
	printf("\t|   ||   A   ||   B   ||   C   ||   D   ||   E   ||   F   ||   G   ||   H   ||   |\n");
	printf("\t|___|________________________________________________________________________|___|\n");
}

void initializeBoard(void)
{
	char stdboard[8][8] = { 
	{'r','n','b','q','k','b','n','r'}, //this is the standard board matrix. 
	{'p','p','p','p','p','p','p','p'},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{'P','P','P','P','P','P','P','P'},
	{'R','N','B','Q','K','B','N','R'}};

	for(int i = 0; i<8; i++)
	{
		for(int j = 0; j<8; j++)
		{
			board[i][j] = stdboard[i][j];
		}
	}
}

char whitepieces[6] = {'P','R','N','B','K','Q'}; //arrays of colored pieces, to check legality
char blackpieces[6] = {'p','r','n','b','k','q'};

int whiteKingLocation[2] = {7,4}; //used to check for checkmate, initialized at standard king location, changed when king moves
int blackKingLocation[2] = {0,4};

int canShortCastleWhite = 1; //used to check if castling is possible 
int canLongCastleWhite = 1;
int canShortCastleBlack = 1;
int canLongCastleBlack = 1;

int attackingPieceWhite[2]; //array used to check for checkmate, stores the location of piece attacking a given coordinate
int attackingPieceBlack[2];

int turn = 0;

int saveGame(void)
{
	char choice;
	printf("\n save current game? \n (Y/N)\n\t>");
	while(1)
	{
		scanf("%c", &choice);
		if(choice == 'Y' || choice == 'N') 
		{
			break;
		}
	}
	if (choice == 'N')
	{
		return 0;
	}

	FILE * fp;

	//buffer to print the lines

	fp = fopen("ChessData.txt", "a"); //analogous to the linux "touch", if a file does not exist, it will create one.
	fclose(fp);

	fp = fopen("ChessData.txt", "r+");

	if ( fp == NULL ) 
    { 
        printf( "Unable to open file." ) ; 
    } 
    else
    { 
        
        printf("Saved games:\n") ;
        int i = 1;
        char buffer[32];

        if( fgets (buffer, 32, fp ) == NULL )
        {
        	printf("\n\tYou have no saved games yet!\n");
        }
        fseek(fp, 0, SEEK_SET);
        while(fgets (buffer, 32, fp ) != NULL)
        {
        	printf("\t%d. ", i);
        	for(int j = 0; j< 32; j++)
        	{
        		char C = buffer[j];
        		if(C == '\n')
        		{
        			break;
        		}
        		printf("%c", C);	
        	}
        	fseek(fp, 84, SEEK_CUR);
        	printf("\n");
          	i++;
        } 
    }

    char saveName[32];//name of save
    printf("\n Pick a name for the current save (less than 32 characters): \n\t>");
    scanf("%s", saveName);

	char data1[32];//board data
	char data2[32];
	for(int i = 0; i<4; i++)//putting board data into the data array
	{
		for(int j = 0; j<8; j++)
		{
			data1[i*8+j] = board[i][j];
		}
	}
	for(int i = 4; i<8; i++)//putting board data into the data array
	{
		for(int j = 0; j<8; j++)
		{
			data2[(i-4)*8+j] = board[i][j];
		}
	}

    if(fp != NULL)
    {
    	fprintf(fp,"%.32s\n",saveName);
    	fprintf(fp,"%.32s\n",data1);
    	fprintf(fp,"%.32s\n",data2);
    	fprintf(fp,"%d %d %d %d %d %d %d %d %d\n", whiteKingLocation[0], whiteKingLocation[1], blackKingLocation[0], blackKingLocation[1], canShortCastleWhite, canLongCastleWhite, canShortCastleBlack, canLongCastleBlack, turn);
    }
	fclose(fp);
	return 1;
}
int loadGame(void)
{
	FILE * fp;
	int i = 1;//number of games available for loading

	//buffer to print the lines

	fp = fopen("ChessData.txt", "a"); //analogous to the linux "touch", if a file does not exist, it will create one.
	fclose(fp);

	fp = fopen("ChessData.txt", "r+");

	if ( fp == NULL ) 
    { 
        printf( "Unable to open file." ) ; 
    } 
    else
    { 
        
        printf("Saved games:\n") ;
        char buffer[32];

        if( fgets (buffer, 32, fp ) == NULL )
        {
        	printf("\n\nYou have no saved games yet! Press Q to quit:\n");
        	char choice = 'B';
        	while(1)
			{
				printf("\n\t>");
				scanf(" %c", &choice);
				if (choice == 'Q')
				{
					return 1;
				}
			}
        }
        fseek(fp, 0, SEEK_SET);
        while(fgets (buffer, 32, fp ) != NULL)
        {
        	printf("\t%d. ", i);
        	for(int j = 0; j< 32; j++)
        	{
        		char C = buffer[j];
        		if(C == '\n')
        		{
        			break;
        		}
        		printf("%c", C);	
        	}
        	fseek(fp, 84, SEEK_CUR); //64 board data + 2\n + 9vars + 8ws +\n
        	printf("\n");
          	i++;
        } 
    }

    int choice = -2;
    while(choice < 0 || choice > i-1)
    {
    	printf("\n Pick a game to load (press 0 to go back to the menu): \n\t>");
    	scanf("%d", &choice);
    	if(choice == 0)
    	{
    		return 1;
    	}
    }

    char buffer[32];
    fseek(fp, 0, SEEK_SET);
    for(int j = 1; j<choice; j++)
    {
    	fgets (buffer, 32, fp );
    	for(int k = 0; k< 32; k++)
    	{
    		char C = buffer[k];
    		if(C == '\n')
    		{
    			break;
    		}	
    	}
    	fseek(fp, 84, SEEK_CUR);
    }
    
    fgets (buffer, 32, fp);
    for(int k = 0; k< 32; k++)
	{
		char C = buffer[k];
		if(C == '\n')
		{
			break;
		}	
	}



	char data1[32];//board data
	if(fgets (data1, 33, fp) != NULL)
	{
		for(int k = 0; k<4; k++)//putting data into the board array
		{
			for(int j = 0; j<8; j++)
			{
				board[k][j] = data1[k*8+j];
			}
		}
	}

	fseek(fp, 1 ,SEEK_CUR);//going over the newline mark

	char data2[32];//board data
	if(fgets (data2, 33, fp) != NULL)
	{
		for(int k = 0; k<4; k++)//putting data into the board array
		{
			for(int j = 0; j<8; j++)
			{
				board[k+4][j] = data2[k*8+j];
			}
		}
	}
	fscanf(fp,"%d %d %d %d %d %d %d %d %d\n", &whiteKingLocation[0], &whiteKingLocation[1], &blackKingLocation[0], &blackKingLocation[1], &canShortCastleWhite, &canLongCastleWhite, &canShortCastleBlack, &canLongCastleBlack, &turn);
	fclose(fp);
	printf("\n\t%d \t%d \n\t%d \t%d \n\t%d \t%d \n\t%d \t%d \n\t%d\n", whiteKingLocation[0], whiteKingLocation[1], blackKingLocation[0], blackKingLocation[1], canShortCastleWhite, canLongCastleWhite, canShortCastleBlack, canLongCastleBlack, turn);
	return 0;
}
int clearMemory(void)
{
    printf("Saved games:\n") ;
    char buffer[32];
    int i = 1;

    FILE * fp;

	fp = fopen("ChessData.txt", "r");

    if( fgets (buffer, 32, fp ) == NULL )
    {
    	printf("\n\tYou have no saved games yet!\nPress Q to quit:\n\n\t>");
    }
    fseek(fp, 0, SEEK_SET);
    while(fgets (buffer, 32, fp ) != NULL)
    {
    	printf("\t%d. ", i);
    	for(int j = 0; j< 32; j++)
    	{
    		char C = buffer[j];
    		if(C == '\n')
    		{
    			break;
    		}
    		printf("%c", C);	
    	}
    	fseek(fp, 84, SEEK_CUR);
    	printf("\n");
      	i++;
    } 
    fclose(fp);

	char choice;
	printf("\n Are you sure you want to delete all saved games?(this cannot be undone) \n (Y/N)\n\t>");
	while(1)
	{
		scanf("%c", &choice);
		if(choice == 'Y' || choice == 'N') 
		{
			break;
		}
	}
	if (choice == 'N')
	{
		return 1;
	}

	fp = fopen("ChessData.txt", "w+"); //opening a file in writing mode should result in clearing it.
	fclose(fp);
	return 0;
}

int openManual(void)
{
	clrscr();
	printf("========================================================================================\n");
	printf("\t\tMANUAL:\n\n");

	printf("\tPIECE SIGNIFICANCE\n");
	printf(" Black pieces are lowercase letters, white pieces are uppercase letters, as follows:\n\n");
	printf("\t p/P - pawn\n");
	printf("\t n/N - knight\n");
	printf("\t b/B - bishop\n");
	printf("\t r/R - rook\n");
	printf("\t q/Q - queen\n");
	printf("\t k/K - king\n");
	printf(" The author makes a supposition that the player knows the rules of chess.\n\n ");

	printf("\t MAKING A MOVE\n");
	printf(" In order to move, the player has to specify the coordinates of the starting point\n");
	printf("and then the coordinates of the ending point. it is worth noting that all coordinates\n");
	printf("must be upper-case letters A through H followed by an integer from 1 to 8. Type in 'QT'\n");
	printf("to pause and exit to min menu (progress will not be lost until the user begins a new \n");
	printf("game or exits the program. Type in 'DR' to offer your opponent a draw.\n\n");

	printf("\tCASTLING\n");
	printf(" In order to castle the player needs to specify the destination of the King as if \n");
	printf("castling were a normal move. Castling, as is in chess, cannot be done if the spaces \n");
	printf("between the king and his destination are occupied or attacked.\n\n");

	printf("\tEN PASSANT\n");
	printf(" En Passant is only enabled when the space between the parn's starting position and \n");
	printf("destination is attacked by the opposite player. An 'x' or 'X' will appear which is to \n");
	printf("be treated like a regular figure. once the X is taken off the board, its corresponding \n");
	printf("pawn will be taken off as well.\n\n");

	printf("\tSAVING A GAME\n");
	printf(" The user can easily save and store the game played through the menu. The user will then \n");
	printf("be asked to give a name to the game in question and can subsequently access it on demand \n");
	printf("even after exiting the game and opening it back up. \n");

	printf("\tLOADING A GAME\n");
	printf(" Loading a game works analogously to saving one, except now the computer will ask for an \n");
	printf("index number of the game in question. There is no upper bound as to how many games can be\n");
	printf("(within reason of course)\n\n");

	printf("\tCLEARING THE MEMORY\n");
	printf(" Game memory can be cleared through the menu, however keep in mind that this action CANNOT \n");
	printf("be undone. \n");

	printf("========================================================================================\n");
	printf("\nPress Q to go back to the Menu\n\t>");
	while(1)
	{
		char choice = 'B';
		scanf("%c", &choice);
		if (choice == 'Q')
		{
			return 0;
		}
	}
}

int isAttackedBlack(int y, int x)//takes in coordinates checks if given place on the board is being attacked by white at the moment
{
	for(int i = 1; i<=4; i++)//checks for rooks and queens across the straight lines (see documentation)
	{
		int dir[4] = {y, 7-x, 7-y, x};
		int cor[5] = {-1, 0, 1, 0, -1};
		for(int j = 1; j <= dir[i-1]; j++)
		{
			if(board[y+cor[i-1]*j][x+cor[i]*j] == 'Q'||board[y+cor[i-1]*j][x+cor[i]*j] == 'R')
			{
				attackingPieceBlack[0] = y+cor[i-1]*j;
				attackingPieceBlack[1] = x+cor[i]*j;
				return 1;
			}
			if(board[y+cor[i-1]*j][x+cor[i]*j] != ' ')
			{
				break;
			}
		}
	}
	for(int i = 1; i<=4; i++)//checks for bishops and queens on the diagonals (see documentation)
	{
		int dir[4] = {min(x,y), min(y,7-x), min(7-x,7-y), min(7-y,x)};
		int cor[8] = {-1, -1, 1, 1, -1, 1, -1, 1};
		for(int j = 1; j <= dir[i-1]; j++)
		{
			if(board[y+cor[i-1]*j][x+cor[i+3]*j] == 'Q' || board[y+cor[i-1]*j][x+cor[i+3]*j] == 'B')
			{
				attackingPieceBlack[0] = y+cor[i-1]*j;
				attackingPieceBlack[1] = x+cor[i+3]*j;
				return 1;
			}
			if(board[y+cor[i-1]*j][x+cor[i+3]*j] != ' ')
			{
				break;
			}
		}
	}
	for(int i = 1; i<=8;i++) //checks for knights
	{
		int cor[14] = {1,2,2,1,-1,-2,-2,-1,1,2,2,1,-1,-2};
		if( (y+cor[i-1] >= 0 && y+cor[i-1] <=7 && x+cor[i+5] >= 0 && x+cor[i+5] <=7 ) && board[y+cor[i-1]][x+cor[i+5]] == 'N')
		{
			attackingPieceBlack[0] = y+cor[i-1];
			attackingPieceBlack[1] = x+cor[i+5];
			return 1;
		}
	}
	for(int i = 1; i<=2; i++) //checks for pawns
	{
		int cor[2] = {-1,1};
		if( (y-1 >= 0 && y-1 <=7 && x+cor[i-1] >= 0 && x+cor[i-1] <=7 ) && board[y+1][x+cor[i-1]] == 'P')
		{
			attackingPieceBlack[0] = y-1;
			attackingPieceBlack[1] = x+cor[i-1];
			return 1;
		}
	}
	for(int i = 1; i<=8;i++) //checks for a lurking king
	{
		int cor[10] = {-1,-1,-1,0,1,1,1,0,-1,-1};
		if( (y+cor[i-1] >= 0 && y+cor[i-1] <=7 && x+cor[i+1] >= 0 && x+cor[i+1] <=7 ) && board[y+cor[i-1]][x+cor[i+1]] == 'K')
		{
			attackingPieceBlack[0] = y+cor[i-1];
			attackingPieceBlack[1] = x+cor[i+1];
			return 2;
		}
	}
	return 0;
}

int isAttackedWhite(int y, int x)//takes in coordinates checks if given place on the board is being attacked by black at the moment
{
	for(int i = 1; i<=4; i++)//checks for rooks and queens across the straight lines (see documentation)
	{
		int dir[4] = {y, 7-x, 7-y, x};
		int cor[5] = {-1, 0, 1, 0, -1};
		for(int j = 1; j <= dir[i-1]; j++)
		{
			if(board[y+cor[i-1]*j][x+cor[i]*j] == 'q'||board[y+cor[i-1]*j][x+cor[i]*j] == 'r')
			{
				attackingPieceWhite[0] = y+cor[i-1]*j;
				attackingPieceWhite[1] = x+cor[i]*j;
				return 1;
			}
			if(board[y+cor[i-1]*j][x+cor[i]*j] != ' ')
			{
				break;
			}
		}
	}

	for(int i = 1; i<=4; i++)//checks for bishops and queens on the diagonals (see documentation)
	{
		int dir[4] = {min(x,y), min(y,7-x), min(7-x,7-y), min(7-y,x)};
		int cor[8] = {-1, -1, 1, 1, -1, 1, -1, 1};
		for(int j = 1; j <= dir[i-1]; j++)
		{
			if(board[y+cor[i-1]*j][x+cor[i+3]*j] == 'q' || board[y+cor[i-1]*j][x+cor[i+3]*j] == 'b')
			{
				attackingPieceWhite[0] = y+cor[i-1]*j;
				attackingPieceWhite[1] = x+cor[i+3]*j;
				return 1;
			}
			if(board[y+cor[i-1]*j][x+cor[i+3]*j] != ' ')
			{
				break;
			}
		}
	}
	for(int i = 1; i<=8;i++) //checks for knights
	{
		int cor[14] = {1,2,2,1,-1,-2,-2,-1,1,2,2,1,-1,-2};
		if( (y+cor[i-1] >= 0 && y+cor[i-1] <=7 && x+cor[i+5] >= 0 && x+cor[i+5] <=7 ) && board[y+cor[i-1]][x+cor[i+5]] == 'n')
		{
			attackingPieceWhite[0] = y+cor[i-1];
			attackingPieceWhite[1] = x+cor[i+5];
			return 1;
		}
	}
	for(int i = 1; i<=2; i++) //checks for pawns
	{
		int cor[2] = {-1,1};
		if( (y-1 >= 0 && y-1 <=7 && x+cor[i-1] >= 0 && x+cor[i-1] <=7 ) && board[y-1][x+cor[i-1]] == 'p')
		{
			attackingPieceWhite[0] = y-1;
			attackingPieceWhite[1] = x+cor[i-1];
			return 1;
		}
	}
	for(int i = 1; i<=8;i++) //checks for a lurking king
	{
		int cor[10] = {-1,-1,-1,0,1,1,1,0,-1,-1};
		if( (y+cor[i-1] >= 0 && y+cor[i-1] <=7 && x+cor[i+1] >= 0 && x+cor[i+1] <=7 ) && board[y+cor[i-1]][x+cor[i+1]] == 'k')
		{
			attackingPieceWhite[0] = y+cor[i-1];
			attackingPieceWhite[1] = x+cor[i+1];
			return 2;
		}
	}
	return 0;
}

int checkIfLegalWhite(int x_1 , int y_1 , int x_2 , int y_2 , char piecemoved)
{
	switch(piecemoved) 
	{
		case 'P' ://pawn legality
			if ((board[y_2][x_2] == ' ')&&(((x_1 == x_2)&&((y_1-y_2 == 1)))||((y_1 == 6)&&(y_1-y_2 == 2))))
			{
				if(((y_1 == 6)&&(y_1-y_2 == 2))&& isAttackedWhite(y_2 + 1, x_1))
				{
					board[y_2 + 1][x_1] = 'X';
				}
				break;
			}
			else
			{
				if ((checkifinarray(board[y_2][x_2], blackpieces, 6) != -1)&&(abv(x_1 - x_2) == 1)&&(y_1-y_2 == 1))
				{
					break;
				}
				return 0;
			}
		case 'N' ://knight legality
			if ((x_1 - x_2)*(x_1-x_2)+(y_1 - y_2)*(y_1 - y_2) == 5 && checkifinarray(board[y_2][x_2], whitepieces, 6) == -1)
			{
				break;
			}
			else
			{
				return 0;
			}
		case 'B' ://bishop legality
			if((checkifinarray(board[y_2][x_2], blackpieces, 6) != -1 || board[y_2][x_2] == ' ') && abv(y_1 - y_2) == abv(x_1 - x_2))//check if x_1,y_1 and x_2,y_2 are on the same diagonal
			{
				for (int i = 1; i < abv(x_1-x_2); i ++) // loop checks for diagonal obstacles, one by one
				{	
					int m = i*sgn(x_1 - x_2);
					int n = i*sgn(y_1 - y_2);
					if (board[y_2 + n][x_2 + m] != ' ')							
					{
						return 0;
					}
				}
				break;
			}
			return 0;
		case 'R' ://rook legality
			if(canLongCastleWhite == 1 && y_1 == 7 && x_1 ==0)
			{
				canLongCastleWhite = 0;
			}
			if(canShortCastleWhite == 1 && y_1 == 7 && x_1 ==7)
			{
				canShortCastleWhite = 0;
			}
			if((checkifinarray(board[y_2][x_2], blackpieces, 6) != -1 || board[y_2][x_2] == ' ')  && (y_1 == y_2 || x_1 == x_2))
			{
				if(y_1 == y_2) //check if row is the same
				{
					for (int i = 1; i < abv(x_1-x_2); i++) // loop checks for horizontal obstacles, one by one
					{	
						int m = (i)*sgn(x_1 - x_2);
						if (board[y_1][x_1 - m] != ' ')
						{
							return 0;
						}		
					}
					break;
				}
				if(x_1 == x_2) //check if file or row is the same
				{	
					for (int i = 1; i < abv(y_1-y_2); i++)// loop checks for vertical obstacles, one by one
					{
						int n = (i)*sgn(y_1 - y_2);	
						if (board[y_1 - n][x_1] != ' ')
						{	
							return 0;
						}
					}
					break;
				}
				
			}
			return 0;
		case 'Q' :
			if((checkifinarray(board[y_2][x_2], blackpieces, 6) != -1 || board[y_2][x_2] == ' ')  && (y_1 == y_2 || x_1 == x_2 || abv(y_1 - y_2) == abv(x_1 - x_2)))
			{
				if(y_1 == y_2) //check if row is the same
				{
					for (int i = 1; i < abv(x_1-x_2); i++) // loop checks for horizontal obstacles, one by one
					{	
						int m = (i)*sgn(x_1 - x_2);
						if (board[y_1][x_1 - m] != ' ')
						{
							return 0;
						}		
					}
					break;
				}
				if(x_1 == x_2) //check if file or row is the same
				{	
					for (int i = 1; i < abv(y_1-y_2); i++)// loop checks for vertical obstacles, one by one
					{
						int n = (i)*sgn(y_1 - y_2);	
						if (board[y_1 - n][x_1] != ' ')
						{	
							return 0;
						}
					}
					break;
				}
				if(abv(y_1 - y_2) == abv(x_1 - x_2))//check if x_1,y_1 and x_2,y_2 are on the same diagonal
				{
					for (int i = 1; i < abv(x_1-x_2); i ++) // loop checks for diagonal obstacles, one by one
					{	
						int m = (i)*sgn(x_1 - x_2);
						int n = (i)*sgn(y_1 - y_2);
						if (board[y_2 + n][x_2 + m] != ' ')							
						{
							return 0;
						}
					}
					break;
				}
				
			}
			return 0;
		case 'K' :
			if(x_2 == 6 && y_2 ==7 && canShortCastleWhite == 1 && board[7][7] == 'R')
			{
				for(int i = 1; i<=2; i++)
				{
					if(board[7][4+i] != ' ' || isAttackedWhite(7, 4+i) == 1)
					{
						printf("\nIn order to castle all spaces between the King and the Rook must be free and must not be attacked!\n %d\t%d\t%d", attackingPieceWhite[0], attackingPieceWhite[1], i);
						return 0;
					}

				}
				canLongCastleWhite = 0;
				canShortCastleWhite = 0;
				board[7][7] = ' ';
				board[7][5] = 'R';
				whiteKingLocation[0] = y_2;
				whiteKingLocation[1] = x_2;
				break;
			}
			if(x_2 == 1 && y_2 ==7 && canLongCastleWhite == 1 && board[7][0] == 'R')
			{
				for(int i = 1; i<=3; i++)
				{
					if(board[7][4-i] != ' ' || isAttackedWhite(7, 4-i) == 1)
					{
						printf("\nIn order to castle all spaces between the King and the Rook must be free and must not be attacked!\n");
						return 0;
					}

				}
				canLongCastleWhite = 0;
				canShortCastleWhite = 0;
				board[7][0] = ' ';
				board[7][2] = 'R';
				whiteKingLocation[0] = y_2;
				whiteKingLocation[1] = x_2;
				break;
			}
			if((checkifinarray(board[y_2][x_2], blackpieces, 6) != -1 || board[y_2][x_2] == ' ') && (x_1 - x_2)*(x_1 - x_2)+(y_1 - y_2)*(y_1 - y_2) <= 2 && isAttackedWhite(y_2, x_2) == 0)
			{
				canLongCastleWhite = 0;
				canShortCastleWhite = 0;
				whiteKingLocation[0] = y_2;
				whiteKingLocation[1] = x_2;
				break;
			}
			return 0;
		case ' ' :
			printf("\nYou cannot move a blank space!\n");
			return 0;
		default :
			return 0;
	}
	return 1;
}

int checkIfLegalBlack(int x_1 , int y_1 , int x_2 , int y_2 , char piecemoved)
{
	switch(piecemoved) 
	{
		case 'p' ://pawn legality
			if ((board[y_2][x_2] == ' ')&&(((x_1 == x_2)&&((y_1-y_2 == -1)))||((y_1 == 1)&&(y_1-y_2 == -2))))
			{
				if(((y_1 == 1)&&(y_1-y_2 == -2))&& isAttackedBlack(y_2 - 1, x_1))
				{
					board[y_2 - 1][x_1] = 'x';
				}
				break;
			}
			else
			{
				if ((checkifinarray(board[y_2][x_2], whitepieces, 6) != -1)&&(abv(x_1 - x_2) == 1)&&(y_1-y_2 == -1))
				{
					break;
				}
				return 0;
			}
		case 'n' ://knight legality
			if ((x_1 - x_2)*(x_1-x_2)+(y_1 - y_2)*(y_1 - y_2) == 5 && checkifinarray(board[y_2][x_2], blackpieces, 6) == -1)
			{
				break;
			}
			else
			{
				return 0;
			}
		case 'b' ://bishop legality
			if((checkifinarray(board[y_2][x_2], whitepieces, 6) != -1 || board[y_2][x_2] == ' ') && abv(y_1 - y_2) == abv(x_1 - x_2))//check if x_1,y_1 and x_2,y_2 are on the same diagonal
			{
				for (int i = 1; i < abv(x_1-x_2); i ++) // loop checks for diagonal obstacles, one by one
				{	
					int m = i*sgn(x_1 - x_2);
					int n = i*sgn(y_1 - y_2);
					if (board[y_2 + n][x_2 + m] != ' ')							
					{
						return 0;
					}
				}
				break;
			}
			return 0;
		case 'r' ://rook legality
			if(canLongCastleBlack == 1 && y_1 == 0 && x_1 ==0)
			{
				canLongCastleBlack = 0;
			}
			if(canShortCastleBlack == 1 && y_1 == 0 && x_1 ==7)
			{
				canShortCastleBlack = 0;
			}
			if((checkifinarray(board[y_2][x_2], whitepieces, 6) != -1 || board[y_2][x_2] == ' ')  && (y_1 == y_2 || x_1 == x_2))
			{
				if(y_1 == y_2) //check if row is the same
				{
					for (int i = 1; i < abv(x_1-x_2); i++) // loop checks for horizontal obstacles, one by one
					{	
						int m = (i)*sgn(x_1 - x_2);
						if (board[y_1][x_1 - m] != ' ')
						{
							return 0;
						}		
					}
					break;
				}
				if(x_1 == x_2) //check if file or row is the same
				{	
					for (int i = 1; i < abv(y_1-y_2); i++)// loop checks for vertical obstacles, one by one
					{
						int n = (i)*sgn(y_1 - y_2);	
						if (board[y_1 - n][x_1] != ' ')
						{	
							return 0;
						}
					}
					break;
				}
				
			}
			return 0;
		case 'q' :
			if((checkifinarray(board[y_2][x_2], whitepieces, 6) != -1 || board[y_2][x_2] == ' ')  && (y_1 == y_2 || x_1 == x_2 || abv(y_1 - y_2) == abv(x_1 - x_2)))
			{
				if(y_1 == y_2) //check if row is the same
				{
					for (int i = 1; i < abv(x_1-x_2); i++) // loop checks for horizontal obstacles, one by one
					{	
						int m = (i)*sgn(x_1 - x_2);
						if (board[y_1][x_1 - m] != ' ')
						{
							return 0;
						}		
					}
					break;
				}
				if(x_1 == x_2) //check if file or row is the same
				{	
					for (int i = 1; i < abv(y_1-y_2); i++)// loop checks for vertical obstacles, one by one
					{
						int n = (i)*sgn(y_1 - y_2);	
						if (board[y_1 - n][x_1] != ' ')
						{	
							return 0;
						}
					}
					break;
				}
				if(abv(y_1 - y_2) == abv(x_1 - x_2))//check if x_1,y_1 and x_2,y_2 are on the same diagonal
				{
					for (int i = 1; i < abv(x_1-x_2); i ++) // loop checks for diagonal obstacles, one by one
					{	
						int m = (i)*sgn(x_1 - x_2);
						int n = (i)*sgn(y_1 - y_2);
						if (board[y_2 + n][x_2 + m] != ' ')							
						{
							return 0;
						}
					}
					break;
				}
				
			}
			return 0;
		case 'k' :
			if(x_2 == 6 && y_2 == 0 && canShortCastleWhite == 1 && board[0][7] == 'r')
			{
				for(int i = 1; i<=2; i++)
				{
					if(board[0][4+i] != ' ' || isAttackedBlack(0, 4+i) != 0)
					{
						printf("\nIn order to castle all spaces between the King and the Rook must be free and must not be attacked!\n");
						return 0;
					}
				}
				canLongCastleBlack = 0;
				canShortCastleBlack = 0;
				board[0][7] = ' ';
				board[0][5] = 'r';
				blackKingLocation[0] = y_2;
				blackKingLocation[1] = x_2;
				break;
			}
			if(x_2 == 1 && y_2 == 0 && canLongCastleBlack == 1 && board[0][0] == 'r')
			{
				for(int i = 1; i<=3; i++)
				{
					if(board[7][4-i] != ' ' || isAttackedBlack(0, 4-i) != 0)
					{
						printf("\nIn order to castle all spaces between the King and the Rook must be free and must not be attacked!\n");
						return 0;
					}

				}
				canLongCastleBlack = 0;
				canShortCastleBlack = 0;
				board[0][0] = ' ';
				board[0][2] = 'r';
				blackKingLocation[0] = y_2;
				blackKingLocation[1] = x_2;
				break;
			}
			if((checkifinarray(board[y_2][x_2], whitepieces, 6) != -1 || board[y_2][x_2] == ' ') && (x_1 - x_2)*(x_1 - x_2)+(y_1 - y_2)*(y_1 - y_2) <= 2 && isAttackedBlack(y_2, x_2) == 0)
			{
				canLongCastleBlack = 0;
				canShortCastleBlack = 0;
				blackKingLocation[0] = y_2;
				blackKingLocation[1] = x_2;
				break;
			}
			return 0;
		case ' ' :
			printf("\nYou cannot move a blank space!\n");
			return 0;
		default :
			return 0;
	}
	return 1;
}

int checkMateWhite (void) //checks if the white king is being mated or checked 0 means no check, 1 means check, 2 means checkmate
{
	int x = whiteKingLocation[1]; //just some helpful variables to make the notation a little shorter
	int y = whiteKingLocation[0];
	if (isAttackedWhite(y, x) == 1) //checks if king is being attacked. if he is, 
	{
		int a_x = attackingPieceWhite[1];//some variables to help see if the attack on the king can be blocked
		int a_y = attackingPieceWhite[0];
		char apiece = board[a_y][a_x];

		board[y][x] = ' '; //the king is momentarily taken off the board for scanning purposes
		for(int i = 1; i<=8;i++) //scanning the surrounding area. if area is not under attack , the function will indicate check. If all possibilities are off the board or attacked, f returns 2 (checkmate)
		{
			board[y][x] = ' '; //the king is momentarily taken off the board for scanning purposes
			int cor[10] = {-1,-1,-1,0,1,1,1,0,-1,-1};
			if(board[y+cor[i-1]][x+cor[i+1]] == ' ' && isAttackedWhite(y+cor[i-1], x+cor[i+1]) == 0 && y+cor[i-1] >= 0 && y+cor[i-1] <= 7 && x+cor[i+1] >= 0 && x+cor[i+1] <= 7)
			{
				board[y][x] = 'K';
				return 1; //check
			}
			board[y][x] = 'K';
			switch (apiece)//checks whether the attack can be blocked
			{
				case 'b':
				{
					for (int i = 1; i < abv(x-a_x); i ++) // loop checks for diagonal obstacles, one by one
					{	
						int m = i*sgn(x - a_x);
						int n = i*sgn(y - a_x);
						if (isAttackedBlack(a_y + n, a_x + m) == 1)							
						{
							return 1;
						}
					}
					break;
				}
				case 'r':
				{
					if(y == a_y) //check if row is the same
					{
						for (int i = 1; i < abv(x - a_x); i++) // loop checks for horizontal obstacles, one by one
						{	
							int m = (i)*sgn(x - a_x);
							if (isAttackedBlack(y , x - m) == 1)
							{
								return 1;
							}		
						}
						break;
					}
					if(x == a_x) //check if file or row is the same
					{	
						for (int i = 1; i < abv(y - a_y); i++)// loop checks for vertical obstacles, one by one
						{
							int n = (i)*sgn(y - a_y);	
							if (isAttackedBlack(y - n, x) == 1)
							{	
								return 1;
							}
						}
						break;
					}

				}
				case 'q':
				{
					if(y == a_y) //check if row is the same
					{
						for (int i = 1; i < abv(x - a_x); i++)
						{	
							int m = (i)*sgn(x - a_x);
							if (isAttackedBlack(y , x - m) == 1)
							{
								return 1;
							}		
						}
						break;
					}
					if(x == a_x) //check if file or row is the same
					{	
						for (int i = 1; i < abv(y - a_y); i++)
						{
							int n = (i)*sgn(y - a_y);	
							if (isAttackedBlack(y - n, x) == 1)
							{	
								return 1;
							}
						}
						break;
					}
					if(abv(x - a_x) == abv(y - a_y))
					{
						for (int i = 1; i < abv(x-a_x); i ++)
						{	
							int m = i*sgn(x - a_x);
							int n = i*sgn(y - a_x);
							if (isAttackedBlack(a_y + n, a_x + m) == 1)							
							{
								return 1;
							}
						}
					break;
					}
				}
			}
		}
		if(isAttackedBlack(a_y, a_x) == 2 && isAttackedWhite(a_y, a_x) == 0 ) //checks if the attacking piece can be taken by the king
			{
				return 1; //check because the attacking piece can be taken by the king
			}
		if(isAttackedBlack(a_y, a_x) == 0 || (isAttackedBlack(a_y, a_x) == 2 && isAttackedWhite(a_y,a_x) != 0) ) //checks if the attacking piece can be taken by white
			{
				return 2; //checkmate
			}
	}
	return 0;//king is safe
}

int checkMateBlack (void) //checks if the black king is being mated or checked 0 means no check, 1 means check, 2 means checkmate
{
	int x = blackKingLocation[1]; //just some helpful variables to make the notation a little shorter
	int y = blackKingLocation[0];
	if (isAttackedBlack(y, x) == 1) //checks if king is being attacked 
	{
		int a_x = attackingPieceBlack[1];//some variables to help see if the attack on the king can be blocked
		int a_y = attackingPieceBlack[0];
		char apiece = board[a_y][a_x];

		
		for(int i = 1; i<=8;i++) //scanning the surrounding area. if area is not under attack , the function will indicate check. If all possibilities are off the board or attacked, f returns 2 (checkmate)
		{
			board[y][x] = ' '; //the king is momentarily taken off the board for scanning purposes
			int cor[10] = {-1,-1,-1,0,1,1,1,0,-1,-1};
			if(board[y+cor[i-1]][x+cor[i+1]] == ' ' &&  isAttackedBlack(y+cor[i-1], x+cor[i+1]) == 0 && y+cor[i-1] >= 0 && y+cor[i-1] <= 7 && x+cor[i+1] >= 0 && x+cor[i+1] <= 7)
			{
				board[y][x] = 'k';
				return 1; //check
			}
			board[y][x] = 'k';
			switch (apiece)//checks whether the attack can be blocked
			{
				case 'B':
				{
					for (int i = 1; i < abv(x-a_x); i ++) // loop checks for diagonal obstacles, one by one
					{	
						int m = i*sgn(x - a_x);
						int n = i*sgn(y - a_x);
						if (isAttackedWhite(a_y + n, a_x + m) == 1)							
						{
							return 1;
							
						}
					}
					break;
				}
				case 'R':
				{
					if(y == a_y) //check if row is the same
					{
						for (int i = 1; i < abv(x - a_x); i++) // loop checks for horizontal obstacles, one by one
						{	
							int m = (i)*sgn(x - a_x);
							if (isAttackedWhite(y , x - m) == 1)
							{
								return 1;
								
							}		
						}
						break;
					}
					if(x == a_x) //check if file or row is the same
					{	
						for (int i = 1; i < abv(y - a_y); i++)// loop checks for vertical obstacles, one by one
						{
							int n = (i)*sgn(y - a_y);	
							if (isAttackedWhite(y - n, x) == 1)
							{	
								return 1;
							}
						}
						break;
					}

				}
				case 'Q':
				{
					if(y == a_y) //check if row is the same
					{
						for (int i = 1; i < abv(x - a_x); i++)
						{	
							int m = (i)*sgn(x - a_x);
							if (isAttackedWhite(y , x - m) == 1)
							{
								return 1;
							}		
						}
						break;
					}
					if(x == a_x) //check if file or row is the same
					{	
						for (int i = 1; i < abv(y - a_y); i++)
						{
							int n = (i)*sgn(y - a_y);	
							if (isAttackedWhite(y - n, x) == 1)
							{	
								return 1;
							}
						}
						break;
					}
					if(abv(x - a_x) == abv(y - a_y))
					{
						for (int i = 1; i < abv(x-a_x); i ++)
						{	
							int m = i*sgn(x - a_x);
							int n = i*sgn(y - a_x);
							if (isAttackedWhite(a_y + n, a_x + m) == 1)							
							{
								return 1;
							}
						}
					break;
					}
				}
			}
		}
		if(isAttackedWhite(a_y, a_x) == 2 && isAttackedBlack(a_y, a_x) == 0 ) //checks if the attacking piece can be taken by the king
		{
			printf("\n4\n");
			return 1; //check because the attacking piece can be taken by the king
		}
		if(isAttackedWhite(a_y, a_x) == 0 || (isAttackedWhite(a_y, a_x) == 2 && isAttackedBlack(a_y, a_x) != 0) ) //checks if the attacking piece can be taken by black
		{
			return 2; //checkmate
		}
	}
	return 0;//king is safe
}

int makemove(int turn) //this function checks validity of user input and then changes the board matrix values
{
	char xcor[8] = {'A','B','C','D','E','F','G','H'}; //these two arrays are used to translate user input into matrix coordinates
	char ycor[8] = {'1','2','3','4','5','6','7','8'};
	int i = 0;
	while(i!= 1)
	{
		char e[4] = {'0','0','0','0'}; //user given coordinates are in the form %c%c. Their validity is verified and they get typed into the e array
		int d[4] = {9,9,9,9}; //they are subsequently translated into matrix coordinates for the computer and typed into the d array

		if (turn == 0)
		{
			printf("\nWHITE to move:\n");
		}
		else
		{
			printf("\nBLACK to move:\n");
		}
		printf("\n Coordinates of piece to be moved: \n \t >");
		scanf(" %c %c", &e[0], &e[1]); //user input for piece-to-be-moved-coordinates
		if (e[0] == 'Q' && e[1] == 'T')//quitting to main menu
		{
			return 3;
		}
		if (e[0] == 'D' && e[1] == 'R')//offering a draw
		{
			char choice1 = 'B';
			printf("Are you sure you want to draw?(Y/N)\n\t>");
			while(1)
			{
				scanf("%c", &choice1);
				if(choice1 == 'Y' || choice1 == 'N') 
				{
					break;
				}
			}
			if (choice1 == 'Y')
			{
				char choice2 = 'B';
				if(turn == 0)
					{
						printf("Does BLACK accept the draw?(Y/N)\n\t>");
					}
				if(turn == 1)
					{
						printf("Does WHITE accept the draw?(Y/N)\n\t>");
					}
				while(1)
				{
					scanf("%c", &choice2);
					if(choice2 == 'Y' || choice2 == 'N') 
					{
						break;
					}
				}
				if(choice2 == 'Y')
				{
					return 5;
				}
			}
		}
		if ((checkifinarray(e[0], xcor, 8) == -1) || (checkifinarray(e[1], ycor, 8) == -1))
		{
			printf("\nPiece cannot be moved here: Invalid coordinates\n");
		}
		else
		{	
			d[0] = 7 - checkifinarray(e[1], ycor, 8);
			d[1] = checkifinarray(e[0], xcor, 8);
			printf("\n Coordinates of destination: \n \t >");
			scanf(" %c %c", &e[2], &e[3]);//user input for destination coordinates

			if ((checkifinarray(e[2], xcor, 8) == -1) || (checkifinarray(e[3], ycor, 8) == -1))
			{
				printf("\nPiece cannot be moved here: Invalid coordinates\n");
			}
			else
			{
				d[2] = 7 - checkifinarray(e[3], ycor, 8);
				d[3] = checkifinarray(e[2], xcor, 8);
				char piecemoved = board[d[0]][d[1]]; //value of places on the matrix pointed out by user
				char destination = board[d[2]][d[3]];
				if (turn == 0)
				{
					for(int j = 0; j<8; j++)//reset en passant
					{
						if(board[5][j] == 'X')
						{
							board[5][j] = ' ';
						}
					}
					if (checkIfLegalWhite(d[1], d[0], d[3], d[2], piecemoved) == 1)
					{
						board[d[0]][d[1]] = ' ';
						board[d[2]][d[3]] = piecemoved;
						if(checkMateWhite() == 0)
						{
							board[d[0]][d[1]] = ' ';
							if (destination == 'x')//en passant
							{
								board[d[2]+1][d[3]] = ' ';
							}
							board[d[2]][d[3]] = piecemoved;
							i = 1;
							return 1;
						}
						else
						{
							board[d[0]][d[1]] = piecemoved;
							board[d[2]][d[3]] = destination;
							
							printf("\nYour king is in check! You can and must move in a way which will change that.\n");
						}
					}
					else
					{
						
						printf("\nPiece cannot be moved here: Illegal move\n");
					}
				}
				else
				{
					if (turn == 1)
					{
						for(int j = 0; j<8; j++)//reset en passant
						{
							if(board[2][j] == 'x')
							{
								board[2][j] = ' ';
							}
						}
						if (checkIfLegalBlack(d[1], d[0], d[3], d[2], piecemoved) == 1 && checkMateBlack() == 0)
						{
							
							board[d[0]][d[1]] = ' ';
							board[d[2]][d[3]] = piecemoved;
							if(checkMateBlack() == 0)
							{
								board[d[0]][d[1]] = ' ';
								if (destination == 'X')//en passant
								{
									board[d[2]-1][d[3]] = ' ';
								}
								board[d[2]][d[3]] = piecemoved;
								i = 1;
								return 0;
							}
							else
							{
								board[d[0]][d[1]] = piecemoved;
								board[d[2]][d[3]] = destination;
								

								printf("\nYour king is in check! You can and must move in a way which will change that.\n");
							}
						}
						else
						{
							printf("\nPiece cannot be moved here: Illegal move\n");
						}
					}
					return 1;
				}
			}
		}
	}
	return 3;
}





int main(void)
{	
	int k = 0, l = 0;//initializing loop variables and turn variable (0 = white, 1 = black)
	while (k != 1)//menu loop
	{
		l = 0;
		char choice = 'A';
		while (choice != 'N' && choice != 'C' && choice != 'S' && choice != 'L' && choice != 'D' && choice != 'M'&& choice != 'Q')
		{
			printlogo();
			printf("\n\n\n Press one of the following:\n\tN - New game\n\tC - Continue\n\tS - Save game\n\tL - Load game\n\tD - Clear Memory\n\tM - Access the Manual\n\tQ - Quit\n\n>");
			scanf("%c", &choice);
		}
		switch (choice)
		{
			case 'N':
			{
				initializeBoard();
				turn = 0;
				break;
			}
			case 'C':
			{
				break;
			}
			case 'S':
			{
				saveGame();
				l = 1;
				break;
			}
			case 'L':
			{
				if (loadGame() == 1)
				{
					l = 1;
				}
				break;
			}
			case 'D':
			{
				clearMemory();
				l = 1;
			}
			case 'M':
			{
				openManual();
				l = 1;
				break;
			}
			case 'Q':
			{
				k = 1;
				l = 1;
				break;
			}
		}
		
		while (l != 1)
		{
			printboard();
			if (checkMateWhite() == 1 || checkMateBlack() == 1)
			{
				printf("\nCHECK!\n");
			}
			int T = makemove(turn);
			if (T == 3)//quit sequence
			{
				l = 1;
				break;
			}
			if (T == 5)//draw sequence
			{
				printboard();
				printf("\n\tIt's a DRAW!\n");
				l = 1;
			}
			turn = T;

			if (checkMateWhite() == 2)//black checkmate
			{
				printboard();
				printf("\n\tCHECKMATE! Black Wins!\n");
				l = 1;
			}
			if (checkMateBlack() == 2)//white checkmate
			{
				printboard();
				printf("\tCHECKMATE! White Wins!");
				l = 1;
			}
			if (l == 1)
			{
				printf("\nPress Q to go back to the Menu!\nThis game will be deleted once you quit and a new game will be started.\n\t>");
				while(1)
				{
					char choice = 'B';
					scanf("%c", &choice);
					if (choice == 'Q')
					{
						initializeBoard();
						break;
					}
				}
			}

		}
	}
	return 0;
}
