#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
static int xwins=0;
static int total=0;
static int win1=0;
static int win2=0;
static int total1=0;
	void updateStats(int total, int xWins) 
		{
    		FILE *file;
			file = fopen("match_history", "w");
    		if (file == NULL) 
			{
        		printf("Error opening file.\n");
    			exit (0);
    		}
    		fprintf(file, "Single player: \n");
    		fprintf(file, "\t Total Matches: %d\n", total);
    		fprintf(file, "\t Matches Won: %d\n", xWins);
    		fprintf(file, "Multiple player: \n");
    		fprintf(file, "\t Total Matches: %d\n", total1);
    		fprintf(file, "\t Matches Won by player 1: %d\n", win1);
    		fprintf(file, "\t Matches Won by player 2: %d\n", win2);
    		fclose(file);
		}

		void displayStats() {
    FILE *file;
    char line[256];
    int y = 50; 

    cleardevice();
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(50, y, "Match History:");
    y += 40; 

    file = fopen("match_history", "r");
    if (file == NULL) {
        outtextxy(50, y, "Error opening file.");
        delay(2000);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        outtextxy(50, y, line);
        y += 30; 
    }
    fclose(file);

    outtextxy(50, y + 40, "Press any key to return to the menu.");
    getch(); 
}

void draw_board() {
    int i;
    int x1 = 50, y1 = 50;
    int x2 = 500, y2 = 500;
    int line_thickness = 4;
    
    setcolor(WHITE);
    
    setfillstyle(SOLID_FILL, BLACK);
    rectangle(x1, y1, x2, y2);
    floodfill((x1 + x2) / 2, y1 + 20, WHITE);

    for (i = 1; i < 3; i++) {
        setlinestyle(SOLID_LINE, 0, line_thickness);
        line(x1, y1 + i * (y2 - y1) / 3, x2, y1 + i * (y2 - y1) / 3);
    }
    for (i = 1; i < 3; i++) {
        setlinestyle(SOLID_LINE, 0, line_thickness);
        line(x1 + i * (x2 - x1) / 3, y1, x1 + i * (x2 - x1) / 3, y2);
    }

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
    setcolor(WHITE);
    outtextxy(200, 10, "Tic-Tac-Toe");
}

draw_circle(int a , int b){
	circle(a,b,20);
	circle(a,b,30);
	setfillstyle(SOLID_FILL,WHITE );
	floodfill(a+25,b,WHITE);
}

draw_cross(int a, int b){
	line(a-20,b-20,a+20,b+20);
	line(a+20,b-20,a-20,b+20);
}
int check_win(char board[9]) {
    if ((board[0] == board[1] && board[1] == board[2] && board[0] != ' ') ||
        (board[3] == board[4] && board[4] == board[5] && board[3] != ' ') ||
        (board[6] == board[7] && board[7] == board[8] && board[6] != ' ') ||
        (board[0] == board[3] && board[3] == board[6] && board[0] != ' ') ||
        (board[1] == board[4] && board[4] == board[7] && board[1] != ' ') ||
        (board[2] == board[5] && board[5] == board[8] && board[2] != ' ') ||
        (board[0] == board[4] && board[4] == board[8] && board[0] != ' ') ||
        (board[2] == board[4] && board[4] == board[6] && board[2] != ' ')) {
        return 1;
    }
    return 0;
}

int minimax(char board[9], int depth, int isMaximizing) {
    if (check_win(board)) {
        return isMaximizing ? -1 : 1;
    }
    int movesLeft = 0;
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') movesLeft++;
    }
    if (movesLeft == 0) return 0;

    int bestScore = isMaximizing ? -1000 : 1000;
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = isMaximizing ? 'O' : 'X';
            int score = minimax(board, depth + 1, !isMaximizing);
            board[i] = ' ';
            if (isMaximizing) {
                bestScore = (score > bestScore) ? score : bestScore;
            } else {
                bestScore = (score < bestScore) ? score : bestScore;
            }
        }
    }
    return bestScore;
}

int find_best_move(char board[9]) {
    int bestMove = -1;
    int bestScore = -1000;
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = 'O';
            int score = minimax(board, 0, 0);
            board[i] = ' ';
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    return bestMove;
}

void draw_mark(int pos, char mark) {
    int x1 = 120, x2 = 270, x3 = 420;
    int y1 = 120, y2 = 270, y3 = 420;
    int coords[9][2] = {{x1, y1}, {x2, y1}, {x3, y1},
                        {x1, y2}, {x2, y2}, {x3, y2},
                        {x1, y3}, {x2, y3}, {x3, y3}};
    int x = coords[pos][0];
    int y = coords[pos][1];
    if (mark == 'X') {
        draw_cross(x, y);
    } else {
        draw_circle(x, y);
    }
}

void play_game(int mode) {
    cleardevice();
    draw_board();
    int x1 = 75, x2 = 300, x3 = 500;
    int y1 = 75, y2 = 220, y3 = 400;
    setcolor(WHITE);

    char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    int moves = 0;
    char player = 'X';

    while (moves < 9) {
        if (player == 'X' || mode == 1) {
            if (kbhit()) {
                char ch = getch();
                if (ch >= 'a' && ch <= 'i') {
                    int pos = ch - 'a';
                    if (board[pos] == ' ') {
                        board[pos] = player;
                        draw_mark(pos, player);
                        moves++;
                        if (check_win(board)) {
                            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
                            outtextxy(200, 20, "Player 1 wins");
                            xwins++;
                            if (mode == 0)
                            {
                            	win1++;
							}
                            delay(2000);
                            break;
                        }
                        total++;
        				updateStats(total, xwins);
                        player = (player == 'X') ? 'O' : 'X';
                        
                    }
                }
                else if (ch == 'q' || ch == 'Q') {
                    break;
                }
            }
        }
        else {
            delay(500);
            int pos = find_best_move(board);
            board[pos] = player;
            draw_mark(pos, player);
            moves++;
            if (check_win(board)) {
                settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
                outtextxy(200, 20, "Player 2 wins");
                win2++;
                delay(2000);
                break;
            }
            total1++;
            player = 'X';
        }
        if (moves == 9) {
            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
            outtextxy(200, 20, "DRAW");
            delay(2000);
        }
    }
}

void display_menu(int option) {
    cleardevice();
    setcolor(LIGHTMAGENTA);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
    outtextxy(250, 50, "Game Menu");
    line(260, 110, 350, 110);
    rectangle(40, 40, 590, 440);
    if (option == 0) {
        setcolor(LIGHTMAGENTA);
        rectangle(220, 90, 375, 130);
        circle(235, 110, 10);
        setfillstyle(SOLID_FILL, LIGHTMAGENTA);
        floodfill(235, 110, LIGHTMAGENTA);
        setcolor(WHITE);
        outtextxy(250, 100, "Single Player");
        setcolor(LIGHTGREEN);
        outtextxy(250, 200, "Multiplayer");
        outtextxy(250, 300, "History");
        outtextxy(250, 400, "Exit");
    }
    else if (option == 1) {
        setcolor(LIGHTGREEN);
        outtextxy(250, 100, "Single Player");
        setcolor(LIGHTMAGENTA);
        rectangle(220, 190, 375, 230);
        circle(235, 210, 10);
        setfillstyle(SOLID_FILL, LIGHTMAGENTA);
        floodfill(235, 210, LIGHTMAGENTA);
        setcolor(WHITE);
        outtextxy(250, 200, "Multiplayer");
        setcolor(LIGHTGREEN);
        outtextxy(250, 300, "History");
        outtextxy(250, 400, "Exit");
    }
    else if (option == 2) {
        setcolor(LIGHTGREEN);
        outtextxy(250, 100, "Single Player");
        outtextxy(250, 200, "Multiplayer");
        setcolor(LIGHTMAGENTA);
        rectangle(220, 290, 375, 330);
        circle(235, 310, 10);
        setfillstyle(SOLID_FILL, LIGHTMAGENTA);
        floodfill(235, 310, LIGHTMAGENTA);
        setcolor(WHITE);
        outtextxy(250, 300, "History");
        setcolor(LIGHTGREEN);
        outtextxy(250, 400, "Exit");
    }
    else if (option == 3) {
        setcolor(LIGHTGREEN);
        outtextxy(250, 100, "Single Player");
        outtextxy(250, 200, "Multiplayer");
        outtextxy(250, 300, "History");
        setcolor(LIGHTMAGENTA);
        rectangle(220, 390, 375, 430);
        circle(235, 410, 10);
        setfillstyle(SOLID_FILL, LIGHTMAGENTA);
        floodfill(235, 410, LIGHTMAGENTA);
        setcolor(WHITE);
        outtextxy(250, 400, "Exit");
    }
    setcolor(RED);
}

int main() {
    srand(time(NULL));
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    int option = 0;
    int key;

    display_menu(option);

    while (1) {
        if (kbhit()) {
            key = getch();
            if (key == 72) { 
                option = (option - 1 + 4) % 4;
                display_menu(option);
            }
            else if (key == 80) { 
                option = (option + 1) % 4;
                display_menu(option);
            }
            else if (key == 13) { 
                if (option == 0) {
                    play_game(0);
                }
                else if (option == 1) {
                    play_game(1);
                }
                else if (option == 2) {
                    displayStats();
                }
                else if (option == 3) {
                    closegraph();
                    getch();
                }
                
                cleardevice();
                display_menu(option);
            }
        }
        delay(100);
    }
    closegraph();
    getch();
    return 0;
}

