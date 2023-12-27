#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>

typedef struct Position {
    int y, x;
} Position;

typedef struct Room {
    Position position;
    int width, height;
} Room;

typedef struct Entity {
    Position position;
    int health;
} Entity;

void screenSetup();
Room** mapSetup();
Entity* playerSetup();
void handleInput(int input, Entity* player);
void playerMove(int y, int x, Entity* player);
void checkPosition(int targetY, int targetX, Entity* player);

Room* createRoom(int y, int x, int height, int width);
void drawRoom(Room* room);

int main() {
    Entity* player;
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

void screenSetup() {
    initscr();
    printw("Hell world");
    noecho();
    refresh();
}

Room** mapSetup() {
    Room** rooms;

    rooms[0] = createRoom(13, 13, 6, 8);
    drawRoom(rooms[0]);

    rooms[1] = createRoom(2, 40, 6, 8);
    drawRoom(rooms[1]);

    rooms[2] = createRoom(10, 40, 6, 12);
    drawRoom(rooms[2]);

    return rooms;
}

Room* createRoom(int y, int x, int height, int width) {
    Room* room;
    room = malloc(sizeof(Room));

    room->yPos = y;
    room->xPos = x;
    room->height = height;
    room->width = width;

    return room;
}

void drawRoom(Room* room) {
    int y, x;

    /* draw top and bottom */
    for (x = room->xPos; x < room->xPos + room->width; x++) {
        mvprintw(room->yPos, x, "-");
        mvprintw(room->yPos + room->height - 1, x, "-");
    }

    /* draw floors and side walls */
    for (y = room->yPos + 1; y < room->yPos + room->height - 1; y++) {
        mvprintw(y, room->xPos, "|");
        mvprintw(y, room->xPos + room->width -1, "|");
        for (x = room->xPos +1; x < room->xPos + room->width - 1; x++) {
            mvprintw(y, x, ".");
        }
    }
}

Entity* playerSetup() {
    Entity* player = malloc(sizeof(Entity));

    player->yPos = 14;
    player->xPos = 14;
    player->health = 20;

    playerMove(14, 14, player);

    return player;
}

void handleInput(int input, Entity* player) {
    int targetY, targetX;

    switch (input) {
        /* move up, down, left, right */
        case 'w':
            targetY = player->yPos - 1;
            targetX = player->xPos;
            break;

        case 's':
            targetY = player->yPos + 1;
            targetX = player->xPos;
            break;

        case 'a':
            targetY = player->yPos;
            targetX = player->xPos - 1;
            break;

        case 'd':
            targetY = player->yPos;
            targetX = player->xPos + 1;
            break;

        default:
            break;
    }

    checkPosition(targetY, targetX, player);
}

void playerMove(int y, int x, Entity* player) {
    mvprintw(player->yPos, player->xPos, ".");

    player->yPos = y;
    player->xPos = x;

    mvprintw(player->yPos, player->xPos, "@");
    move(player->yPos, player->xPos);
}

void checkPosition(int targetY, int targetX, Entity* entity) {
    int tile;
    switch (mvinch(targetY, targetX)) {
        case '.':
            playerMove(targetY, targetX, entity);
            break;

        default:
            move(entity->yPos, entity->xPos);
            break;
    
    }
}

