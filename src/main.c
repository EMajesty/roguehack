#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>

typedef struct Player {
    int xPos, yPos, health;
} Player;

int screenSetup();
int mapSetup();
Player* playerSetup();
int handleInput(int input, Player* player);
int playerMove(int y, int x, Player* player);

int main() {
    Player* player;
    int ch;

    screenSetup();
    mapSetup();
    player = playerSetup();

    /* game loop */
    while ((ch = getch()) != 'q') {
        handleInput(ch, player);
    
    }

    endwin();

    return 0;
}

int screenSetup() {
    initscr();
    printw("Hell world");
    noecho();
    refresh();
    
    return 1;
}

int mapSetup() {
   mvprintw(13, 13, "--------"); 
   mvprintw(14, 13, "|......|"); 
   mvprintw(15, 13, "|......|"); 
   mvprintw(16, 13, "|......|"); 
   mvprintw(17, 13, "|......|"); 
   mvprintw(18, 13, "--------"); 

   mvprintw(2, 40, "--------"); 
   mvprintw(3, 40, "|......|"); 
   mvprintw(4, 40, "|......|"); 
   mvprintw(5, 40, "|......|"); 
   mvprintw(6, 40, "|......|"); 
   mvprintw(7, 40, "--------"); 

   mvprintw(13, 40, "----------"); 
   mvprintw(14, 40, "|........|"); 
   mvprintw(15, 40, "|........|"); 
   mvprintw(16, 40, "|........|"); 
   mvprintw(17, 40, "|........|"); 
   mvprintw(18, 40, "----------"); 
}

Player* playerSetup() {
    Player* player = malloc(sizeof(Player));

    player->xPos = 14;
    player->yPos = 14;
    player->health = 20;

    mvprintw(player->yPos, player->xPos, "@");

    return player;
}

int handleInput(int input, Player* player) {
    switch (input) {
        /* move up, down, left, right */
        case 'w':
            playerMove(player->yPos - 1, player->xPos, player);
            break;
        case 's':
            playerMove(player->yPos + 1, player->xPos, player);
            break;
        case 'a':
            playerMove(player->yPos, player->xPos - 1, player);
            break;
        case 'd':
            playerMove(player->yPos, player->xPos + 1, player);
            break;
        default:
            break;
    }
}

int playerMove(int y, int x, Player* player) {
    mvprintw(player->yPos, player->xPos, ".");

    player->yPos = y;
    player->xPos = x;

    mvprintw(player->yPos, player->xPos, "@");
}
