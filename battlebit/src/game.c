//
// Created by carson on 5/20/20.
//

#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include <string.h>

// STEP 10 - Synchronization: the GAME structure will be accessed by both players interacting
// asynchronously with the server.  Therefore the data must be protected to avoid race conditions.
// Add the appropriate synchronization needed to ensure a clean battle.

static game * GAME = NULL;

void game_init() {
    if (GAME) {
        free(GAME);
    }
    GAME = malloc(sizeof(game));
    GAME->status = CREATED;
    game_init_player_info(&GAME->players[0]);
    game_init_player_info(&GAME->players[1]);
}

void game_init_player_info(player_info *player_info) {
    player_info->ships = 0;
    player_info->hits = 0;
    player_info->shots = 0;
}

int game_fire(game *game, int player, int x, int y) {
    // Step 5 - This is the crux of the game.  You are going to take a shot from the given player and
    // update all the bit values that store our game state.
    //
    //  - You will need up update the players 'shots' value
    //  - you You will need to see if the shot hits a ship in the opponents ships value.  If so, record a hit in the
    //    current players hits field
    //  - If the shot was a hit, you need to flip the ships value to 0 at that position for the opponents ships field
    //
    //  If the opponents ships value is 0, they have no remaining ships, and you should set the game state to
    //  PLAYER_1_WINS or PLAYER_2_WINS depending on who won.
}

unsigned long long int xy_to_bitval(int x, int y) {
    // Step 1 - implement this function.  We are taking an x, y position
    // and using bitwise operators, converting that to an unsigned long long
    // with a 1 in the position corresponding to that x, y
    //
    // x:0, y:0 == 0b00000...0001 (the one is in the first position)
    // x:1, y: 0 == 0b00000...10 (the one is in the second position)
    // ....
    // x:0, y: 1 == 0b100000000 (the one is in the eighth position)
    //
    // you will need to use bitwise operators and some math to produce the right
    // value.
   unsigned long long value = 1ull <<x;
   value = 1ull << (y*8+x);
   return value;
}

struct game * game_get_current() {
    return GAME;
}

int game_load_board(struct game *game, int player, char * spec) {
    // Step 2 - implement this function.  Here you are taking a C
    // string that represents a layout of ships, then testing
    // to see if it is a valid layout (no off-the-board positions
    // and no overlapping ships)
    //

    // if it is valid, you should write the corresponding unsigned
    // long long value into the Game->players[player].ships data
    // slot and return 1
    //
    // if it is invalid, you should return -1


    // strlen to return the length of spec
    //for loop in specs and increment by 3
    // change numbers to chars

    int carrier = 5;
    int battleship = 4;
    int destroyer = 3;
    int submarine = 3;
    int patrolboat = 2;
    bool horizontal;

 struct player_info * playerInfo = &game ->players[player];



    int l = strlen(spec);
    for (int i = 0; i <= 15; i = i + 3) {

       char x = spec[i+1];
       int conXtonum = x - '0';
        char y = spec[i + 2];
         int contYtonum = y - '0';


        if (spec[i] == 'C'|| spec[i] =='c') {

            if(spec[i] == 'C'){
                add_ship_horizontal(playerInfo,conXtonum,contYtonum, carrier);


            }
            else{
                add_ship_vertical(playerInfo,conXtonum,contYtonum,carrier);
            }


        }


        if (spec[i] == 'B'|| spec[i]=='b') {


            if(spec[i] =='B'){
                add_ship_horizontal(playerInfo,conXtonum,contYtonum,battleship);
            }
            else{
                add_ship_vertical(playerInfo,conXtonum,contYtonum,battleship);
            }
        }



            if (spec[i] == 'D'|| spec[i]=='d') {
                if(spec[i]=='D'){
                    add_ship_horizontal(playerInfo,conXtonum,contYtonum,destroyer);
                }
                else{
                    add_ship_vertical(playerInfo,conXtonum,contYtonum,destroyer);
                }
            }



            if (spec[i] == 'S' || spec[i] == 's') {
                if(spec[i]=='S'){
                    add_ship_horizontal(playerInfo,conXtonum,contYtonum,submarine);
                }
                else{
                    add_ship_vertical(playerInfo,conXtonum,contYtonum,submarine);
                }
            }

            if (spec[i] == 'P'||spec =='p') {
                if(spec[i] == 'P'){
                    add_ship_horizontal(playerInfo,conXtonum,contYtonum,patrolboat);
                }
                else{
                    add_ship_vertical(playerInfo,conXtonum,contYtonum,patrolboat);
                }
            }

        }
    }



        int add_ship_horizontal(player_info *player, int x, int y, int length) {

            // make sure x and y in the board
            // check the players ship variable to if there is an existing ship need to use bit mask
            // update tht bit

            // implement this as part of Step 2
            // returns 1 if the ship can be added, -1 if not
            // hint: this can be defined recursively

        }

        int add_ship_vertical(player_info *player, int x, int y, int length) {
            // implement this as part of Step 2
            // returns 1 if the ship can be added, -1 if not
            // hint: this can be defined recursively

        }
