// CS Pacman
//
// This program was written by Shua Yu Xuan, Iryna
// on 5 October 2023
//
// This assignment create, use and manipulate 2D arays and structs to solve problems.  

#include <math.h>
#include <stdio.h>

// Provided constants
#define NUM_ROWS 8
#define NUM_COLS 10
#define NUM_FLOORS 5

#define TRUE 1
#define FALSE 0

// TODO: put your constants here 

// Provided enums
enum entity {
    EMPTY_ENTITY,
    WALL,
    DOT,
    APPLE,
    BANANA,
    POWER_UP,
    STAIRCASE_UP,
    STAIRCASE_DOWN,
};

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// Provided structs
struct enemy {
    enum direction move_direction;
    int is_present;
    // You will need to add more to this struct in stage 3
};

struct tile {
    enum entity entity;
    struct enemy enemy;
};


void initialise_map(struct tile map[NUM_ROWS][NUM_COLS]);
void print_map(
    struct tile map[NUM_ROWS][NUM_COLS],
    int pacman_row,
    int pacman_col
);


int main(void) {
    struct tile map[NUM_ROWS][NUM_COLS];
    initialise_map(map);

    printf("Welcome to cs_pacman!\n");
  
    printf("Enter Pacman's starting coordinates: ");
    int pacman_row = 0, pacman_col = 0;
    scanf(" %d %d", &pacman_row, &pacman_col);

    map[pacman_row][pacman_col].entity = EMPTY_ENTITY;
    print_map(map, pacman_row, pacman_col);

    printf("Create the level: \n");
       
    //checking whether player inserted S to start game or any of the other features
    char letter;
    while (scanf(" %c", &letter) == 1 && letter != 'S') {

        //checking whether player chose the wall feature 
        if (letter == 'W') { 

            //check for coordinates to know where to print feature next
            int start_row, start_col, end_row, end_col;
            scanf(" %d %d %d %d", &start_row, &start_col, &end_row, &end_col);

            //to exclude those that are more than the size, e.g. (W 30 30 30 30)
            if (end_col >= 0 && end_row >= 0 && (start_row < NUM_ROWS || 
            end_row < NUM_ROWS || start_col < NUM_COLS || end_col < NUM_COLS)) {
            
                //if negative values on start, start = 0
                if (start_row > NUM_ROWS) {
                    start_row = 0;
                } else if (start_row < 0) {
                    start_row = 0;
                }
                if (start_col > NUM_COLS) {
                    start_col = 0;
                } else if (start_col < 0) {
                    start_col = 0;  
                } 
                //to loop value such that it stops at the end of table
                if (end_row > NUM_ROWS) {
                    end_row = NUM_ROWS -1;
                } 
                if (end_col > NUM_COLS) {
                    end_col = NUM_COLS -1;
                }
                
                //check whether the player chose a number within the range  
                if (end_row < NUM_ROWS && end_col < NUM_COLS) {
                    //to check whether the wall is either vertical or horizontal
                    if (start_col == end_col || start_row == end_row) {
                        //for horizontal wall
                        while (start_row == end_row) {
                            while (start_col <= end_col) {
                                map[start_row][start_col].entity = WALL;
                                start_col++;
                            }
                            start_row++;
                        }
                        //for vertical wall
                        while (start_col == end_col) {
                            while (start_row <= end_row) {
                                map[start_row][start_col].entity = WALL;
                                start_row++;
                            }  
                            start_col++;
                        } 
                    } else if (start_col != end_col && start_row != end_row) {
                        //if the walls are neither vertical or horizontal
                        printf("Given wall is not horizontal or vertical!\n");
                    }
                } 
            }    
        } else if (letter == 'A') { 
            //if apple function is being used
            int apple_row, apple_col;
            scanf(" %d %d", &apple_row, &apple_col);
            map[apple_row][apple_col].entity = APPLE;
        } else if (letter == 'B') {
            //if banana function is being used
            int banana_row, banana_col;
            scanf(" %d %d", &banana_row, &banana_col);
            map[banana_row][banana_col].entity = BANANA;

        }
    }
    //printing of the dots, ignoring the walls, apple, banana and
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (map[i][j].entity == WALL || map[i][j].entity == APPLE ||
            map[i][j].entity == BANANA) {
            } else {
                map[i][j].entity = DOT;
            }
        }
    }

    //if 'S' is detected then it will print map
    print_map(map, pacman_row, pacman_col);

    printf("Enter command: ");
    char command;
    int origin_pacman_row, origin_pacman_col;
    int points = 0;
    
    
    //checking for the total number of dots in the map
    int check = 0;
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (map[i][j].entity == DOT) {
                check = check + 1;
            }
        }
    }

    while (check != 0) {
        scanf(" %c", &command);
        origin_pacman_col = pacman_col;
        origin_pacman_row = pacman_row;
        //controlling the movement of pacman
        if (command == 'w') {
            pacman_row--;
        } else if (command == 's') {
            pacman_row++;
        } else if (command == 'a') {
            pacman_col--;
        } else if (command == 'd') {
            pacman_col++;
        } else if (command == 'p') {
            printf("You have %d points!\n", points);   
        }
        
        //making the pacman loop if drop off front the right side of the map
        //pacman will reappear on the left, vice versa. Applies to the top and 
        //the bottom of the map as well
        if (pacman_row < 0) {
            pacman_row = NUM_ROWS -1;            
        } else if (pacman_row == NUM_ROWS) {
            pacman_row = 0;
        }
        if (pacman_col < 0) {
            pacman_col = NUM_COLS -1;
        } else if (pacman_col == NUM_COLS) {
            pacman_col = 0;
        }


        //pacman does not move when there is a wall, to check for wall
        if (map[pacman_row][pacman_col].entity == WALL) {
            print_map(map, origin_pacman_row, origin_pacman_col);
            if (command == 'w') {
                pacman_row++;
            } else if (command == 's') {
                pacman_row--;
            } else if (command == 'a') {
                pacman_col++;
            } else if (command == 'd') {
                pacman_col--;
            }
        } else {
            //checking of pacman's position and whether dot is still there, 
            //and making sure if 'p' is keyed first, the pacman did not move
            //hence the point shouldnot be affected and dot should still remain
            if (map[pacman_row][pacman_col].entity != EMPTY_ENTITY &&  
            ((origin_pacman_col != pacman_col) || (origin_pacman_row != pacman_row))) {
                points = points + 10;
                if (map[pacman_row][pacman_col].entity == DOT) {
                    check = check - 1;
                }
            } 
            //when eaten apple "points + 20" along with the dots around it
            if (map[pacman_row][pacman_col].entity == APPLE) {
              
                //checking whether the pacman hits the boarder of NUM_ROWS
                int apple_effect_row = 0, apple_effect_col = 0;
                int apple_effect_row_max = 0, apple_effect_col_max = 0;
                //ensure that when apple bomb, 5x5 is within map on the extreme
                //Setting the apple bomb starting row point
                if (pacman_row > 2 && pacman_row < NUM_ROWS - 2) {
                    apple_effect_row = pacman_row - 2;
                } else if (pacman_row < 2) {
                    apple_effect_row = 0;
                } else if (pacman_row >= NUM_ROWS - 3) {
                    apple_effect_row = NUM_ROWS -3;
                }
                //ensure that when apple bomb, 5x5 is within map on the extreme
                //Setting the apple bomb ending row point
                if (pacman_row + 2 < NUM_ROWS) {
                    apple_effect_row_max = pacman_row + 2;
                } else if (pacman_row + 2 > NUM_ROWS) {
                    apple_effect_row_max = NUM_ROWS - 1;
                }

                while (apple_effect_row <= apple_effect_row_max) {
                    //ensure that when apple bomb, 5x5 is within map on the extreme
                    //Setting the Apple Bomb Starting column point
                    if (pacman_col > 2 && pacman_col < NUM_COLS - 2) {
                        apple_effect_col = pacman_col - 2;
                    } else if (pacman_col <= 2) {
                        apple_effect_col = 0;
                    } else if (pacman_col >= NUM_COLS - 3) {
                        apple_effect_col = NUM_COLS -3;
                    }
                    //ensure that the apple bomb, 5x5 is within map on the extreme
                    //Setting the Apple bomb ending column point
                    if (pacman_col + 2 < NUM_COLS) {
                        apple_effect_col_max = pacman_col + 2;
                    } else if (pacman_col + 2 > NUM_COLS) {
                        apple_effect_col_max = NUM_COLS - 1;
                    }
                    while (apple_effect_col <= apple_effect_col_max) {               
                        //checks whether there is dots in the positions
                        //ensure that the points accumulated are only dots 
                        //and does not include walls
                        if 
                        (map[apple_effect_row][apple_effect_col].entity != EMPTY_ENTITY && 
                        map[apple_effect_row][apple_effect_col].entity != WALL) {
                            points = points + 10;
                            if (map[pacman_row][pacman_col].entity == DOT) {
                                check = check - 1;
                            }
                        } 
                        if ((map[apple_effect_row][apple_effect_col].entity == APPLE || 
                        map[apple_effect_row][apple_effect_col].entity == BANANA ) &&
                        (apple_effect_row != pacman_row || 
                        apple_effect_col != pacman_col)) {
                            points = points + 10;    
                        }
                        //to clear the 5x5 diameter of the pacman,
                        //to add points first before removing the dot/wall
                        map[apple_effect_row][apple_effect_col].entity = EMPTY_ENTITY;
                        apple_effect_col++;
                    }
                    apple_effect_row++;
                }
            } else if (map[pacman_row][pacman_col].entity == BANANA) {
                //if the pacman eats the banana + 20 and clearing of row and col                
                
                int b_effect_top = 0, b_effect_bottom = NUM_COLS - 2;
                int b_effect_left = 0, b_effect_right = NUM_ROWS + 1;
                
                //checking of the wall for the row section,
                //if there is a wall, then clearing of the dot would be stopped
                if (pacman_row == 0) {
                    for (int j = pacman_row; j < b_effect_bottom; j++) {
                        if (map[j][pacman_col].entity == WALL) {
                            break;
                        }
                        if (map[j][pacman_col].entity != EMPTY_ENTITY &&
                            map[j][pacman_col].entity != WALL) {
                            points = points + 10;
                            if (map[pacman_row][pacman_col].entity == DOT) {
                                check = check - 1;
                            }
                        }
                        if (map[j][pacman_col].entity == APPLE || 
                            map[j][pacman_col].entity == BANANA) {
                            if (j != pacman_row) {
                                points = points + 10;
                            }    
                        }
                        map[j][pacman_col].entity = EMPTY_ENTITY;
                    }   
                }
                else if (pacman_row == 9) {
                    for (int i = pacman_row; i >= b_effect_top; i--) {
                        if (map[i][pacman_col].entity == WALL) {
                            break;
                        }
                        else {
                            if (map[i][pacman_col].entity != EMPTY_ENTITY &&
                                map[i][pacman_col].entity != WALL) {
                                points = points + 10;
                                if (map[pacman_row][pacman_col].entity == DOT) {
                                    check = check - 1;
                                }
                            }
                            if ((map[i][pacman_col].entity == APPLE || 
                                map[i][pacman_col].entity == BANANA)  &&
                                (i != pacman_row)) {
                                points = points + 10;   
                            }
                            map[i][pacman_col].entity = EMPTY_ENTITY;
                        }
                    }   
                }
                //When the pacman row is in the middle of the matrix
                else {
                    //Check for wall above of the pacman  
                    for (int i = pacman_row; i >= b_effect_top; i--) {
                        if (map[i][pacman_col].entity == WALL) {
                            break;
                        }
                        else {
                            //Checking if the slot if contains something, but not wall
                            if ((map[i][pacman_col].entity != EMPTY_ENTITY &&
                                map[i][pacman_col].entity != WALL)) {
                                points = points + 10;
                                if (map[pacman_row][pacman_col].entity == DOT) {
                                    check = check - 1;
                                }
                            }
                            //Checking if the slot has apple or banana
                            if (map[i][pacman_col].entity == APPLE || 
                                map[i][pacman_col].entity == BANANA) {
                                if (i != pacman_row) {
                                    points = points + 10;  
                                } 
                            }
                            map[i][pacman_col].entity = EMPTY_ENTITY;
                        }
                    }   

                    //Check for wall below the pacman 
                    for (int j = pacman_row; j < b_effect_bottom; j++) {
                        if (map[j][pacman_col].entity == WALL) {
                            break;
                        }
                        if (map[j][pacman_col].entity != EMPTY_ENTITY &&
                            map[j][pacman_col].entity != WALL) {
                            points = points + 10;
                            if (map[pacman_row][pacman_col].entity == DOT) {
                                check = check - 1;
                            }
                        }
                        if ((map[j][pacman_col].entity == APPLE || 
                            map[j][pacman_col].entity == BANANA) && 
                            (j != pacman_row)) {
                            points = points + 10;    
                        }
                        map[j][pacman_col].entity = EMPTY_ENTITY;
                    }   
                }

                //checking of the wall for the coloum
                //if there is a wall, then clearing of the dot would be stopped
                if (pacman_col == 0) {
                    for (int j = pacman_col; j <= b_effect_right; j++) {
                        if (map[pacman_row][j].entity == WALL) {
                            break;
                        }
                        if (map[pacman_row][j].entity != EMPTY_ENTITY &&
                             map[pacman_row][j].entity != WALL) {
                            points = points + 10;
                            if (map[pacman_row][pacman_col].entity == DOT) {
                                check = check - 1;
                            }
                        }
                        if ((map[pacman_row][j].entity == APPLE || 
                            map[pacman_row][j].entity == BANANA) &&
                            (j != pacman_col)) {
                            points = points + 10;    
                        }
                        map[pacman_row][j].entity = EMPTY_ENTITY;
                    }   
                }
                if (pacman_col == 7) {
                    for (int i = pacman_col; i >= b_effect_left; i--) {
                        if (map[pacman_row][i].entity == WALL) {
                            break;
                        }
                        if (map[pacman_row][i].entity != EMPTY_ENTITY) {
                            points = points + 10;
                            if (map[pacman_row][pacman_col].entity == DOT) {
                                check = check - 1;
                            } 
                        }
                        if (map[pacman_row][i].entity == APPLE || 
                        map[pacman_row][i].entity == BANANA) {
                            if (i != pacman_col) {
                                points = points + 10;  
                            }  
                        }
                        map[pacman_row][i].entity = EMPTY_ENTITY;
                    }   

                }
                
                else {
                    //Check for wall above of the pacman 
                    for (int i = pacman_col; i >= b_effect_left; i--) {
                        if (map[pacman_row][i].entity == WALL) {
                            break;
                        }
                        if (map[pacman_row][i].entity != EMPTY_ENTITY) {                    
                            points = points + 10;   
                            if (map[pacman_row][pacman_col].entity == DOT) {
                                check = check - 1;
                                } 
                        }
                        if  ((map[pacman_row][i].entity == APPLE || 
                            map[pacman_row][i].entity == BANANA) &&
                            (i != pacman_col)) {
                            points = points + 10;    
                        }
                        map[pacman_row][i].entity = EMPTY_ENTITY;
                    }   

                    //Check for wall below of the pacman
                    for (int j = pacman_col; j <= b_effect_right; j++) {
                        if (map[pacman_row][j].entity == WALL) {
                            break;
                        }
                        if (map[pacman_row][j].entity == DOT) {
                            points = points + 10;
                            check = check - 1;
                          
                        }
                        if ((map[pacman_row][j].entity == APPLE || 
                            map[pacman_row][j].entity == BANANA) &&
                            (j != pacman_col)) {
                            points = points + 10;    
                        }
                        map[pacman_row][j].entity = EMPTY_ENTITY;
                    }   
                }
            }
            if (check > 0) {
                print_map(map, pacman_row, pacman_col);
                printf("Enter command: ");
            }
            //to ensure when 'p' function used, no dots then and accumulated to the points
            if (origin_pacman_col != pacman_col || origin_pacman_row != pacman_row ) {            
                map[pacman_row][pacman_col].entity = EMPTY_ENTITY; 
            }
        }         
    } 
           
    printf("Game won! You got %d points.\n", points);
    return 0;
}

void initialise_map(struct tile map[NUM_ROWS][NUM_COLS]) {
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            map[row][col].entity = EMPTY_ENTITY;
            map[row][col].enemy.move_direction = LEFT;
            map[row][col].enemy.is_present = FALSE;
        }
    }
}

void print_map(
    struct tile map[NUM_ROWS][NUM_COLS],
    int pacman_row,
    int pacman_col
) {
    for (int i = 0; i < NUM_COLS; i++) {
        printf("----");
    }
    printf("-\n");
    for (int row = 0; row < NUM_ROWS; row++) {
        printf("|");
        for (int col = 0; col < NUM_COLS; col++) {
            if (map[row][col].entity == WALL) {
                printf("|||");
            } else if (row == pacman_row && col == pacman_col) {
                printf("^_^");
            } else if (map[row][col].enemy.is_present == TRUE) {
                printf("O_O");
            } else if (map[row][col].entity == DOT) {
                printf(" . ");
            } else if (map[row][col].entity == APPLE) {
                printf(" a ");
            } else if (map[row][col].entity == BANANA) {
                printf(" b ");
            } else if (map[row][col].entity == POWER_UP) {
                printf("<o>");
            } else if (map[row][col].entity == STAIRCASE_UP) {
                printf("__/");
            } else if (map[row][col].entity == STAIRCASE_DOWN) {
                printf("\\__");
            } else {
                printf("   ");
            }

            printf("|");
        }
        printf("\n");
        for (int i = 0; i < NUM_COLS; i++) {
            printf("----");
        }
        printf("-\n");
    }
}
