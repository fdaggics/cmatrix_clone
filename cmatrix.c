#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define DELAY 50000

void initMatrix(int* positions, int width) {
    for(int i = 0; i < width; ++i) {
        positions[i] = -1;
    }
}

void updateMatrix(int* positions, int width, int height) {
    for(int i = 0; i < width; ++i) {
        if(positions[i] >= 0) {
            mvaddch(positions[i], i, ' ');
        }
        // Randomly decide whether to start a new "drop"
        if(positions[i] == -1 && (rand() % 15) < 2) {
            positions[i] = 0;
        }
        if(positions[i] >= 0) {
            mvaddch(positions[i], i, rand() % 256);
        }
        positions[i]++;
        if(positions[i] > height) {
            positions[i] = -1;
        }
    }
}

int main() {
    int width, height;
    int* positions;

    srand(time(NULL));
    initscr();              // Start ncurses mode
    getmaxyx(stdscr, height, width); // Get the size of the terminal
    curs_set(0);            // Hide cursor
    start_color();          // Start color functionality
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    nodelay(stdscr, TRUE);  // Non-blocking getch
    noecho();               // Don't echo input characters
    positions = (int*)malloc(width * sizeof(int));
    initMatrix(positions, width);

    while(getch() == ERR) { // Run until user presses a key
        updateMatrix(positions, width, height);
        refresh();
        usleep(DELAY);
    }

    free(positions);
    endwin();               // End ncurses mode

    return 0;
}

