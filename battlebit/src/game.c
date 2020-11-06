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
    unsigned long long int mask = xy_to_bitval(x, y);
    struct player_info *shooter = &game->players[player];
    struct player_info *opponent = &game->players[(player + 1) % 2];
        shooter->shots &= mask;
        if (opponent->ships & mask) {
                shooter->hits &= mask;
                opponent->ships ^= mask;
            return 1;
            }
        else{
            return 0;
        }
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
    // x:0, y:0 == 0b1 (the one is in the first position)
    // x:1, y: 0 == 0b10 (the one is in the second position)
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

    struct player_info * playerInfo = &game ->players[player];
                //checks if the spec is null of is not equal to 15

    int  seen_carrier;
    int seen_battleship;
    int seen_destroyer;
    int seen_submarine;
    int seen_patrol;

    if(NULL == spec|| strlen(spec) !=15){
        return -1;
    }
     for (int i = 0; i <= 15; i = i + 3) {
        char x = spec[i+1];
        int conXtonum = x - '0';
        char y = spec[i + 2];
        int contYtonum = y - '0';
         if (spec[i] == 'C'|| spec[i] =='c') {
            if (seen_carrier == 1) {
                return -1;
            }
            seen_carrier =1;
            if(spec[i] == 'C'){
              //  add_ship_horizontal(playerInfo,conXtonum,contYtonum, 5);
                if(add_ship_horizontal(playerInfo,conXtonum,contYtonum, 5) == -1){
                 return -1;
                }
            }
            else {
              //  add_ship_vertical(playerInfo,conXtonum,contYtonum,5);
                if(add_ship_vertical(playerInfo,conXtonum,contYtonum,5) == -1){
                    return -1;
                }
            }
        }
         else if (spec[i] == 'B'|| spec[i]=='b') {
            if(seen_battleship ==1){
                return -1;
            }
            seen_battleship = 1;
            if(spec[i] =='B'){
               // add_ship_horizontal(playerInfo,conXtonum,contYtonum,4);
                if(add_ship_horizontal(playerInfo,conXtonum,contYtonum,4) == -1){
                    return -1;
                }
            }
            else {
               // add_ship_vertical(playerInfo,conXtonum,contYtonum,4);
                if(add_ship_vertical(playerInfo,conXtonum,contYtonum,4)== -1){
                    return-1;
                }
            }
        }
         else if (spec[i] == 'D'|| spec[i]=='d') {
            if(seen_destroyer == 1){
                return -1;
            }
            seen_destroyer = 1;
            if(spec[i]=='D'){
              //  add_ship_horizontal(playerInfo,conXtonum,contYtonum,3);
                if(add_ship_horizontal(playerInfo,conXtonum,contYtonum,3)==-1){
                    return -1;
                }
            }
            else {
               // add_ship_vertical(playerInfo,conXtonum,contYtonum,3);
                if(add_ship_vertical(playerInfo,conXtonum,contYtonum,3)==-1){
                    return -1;
                }
            }
        }
         else if (spec[i] == 'S' || spec[i] == 's') {
            if(seen_submarine == 1){
                return -1;
            }
            seen_submarine = 1;
            if(spec[i]=='S'){
              //  add_ship_horizontal(playerInfo,conXtonum,contYtonum,3);
                if(add_ship_horizontal(playerInfo,conXtonum,contYtonum,3)==-1){
                    return -1;
                }
            }
            else {
               // add_ship_vertical(playerInfo,conXtonum,contYtonum,3);
                if(add_ship_vertical(playerInfo,conXtonum,contYtonum,3)==-1){
                    return -1;
                }
            }
        }
         else if (spec[i] == 'P'||spec[i] =='p') {
            if(seen_patrol == 1){
                return -1;
            }
            seen_patrol = 1;
            if(spec[i] == 'P'){
                //add_ship_horizontal(playerInfo,conXtonum,contYtonum,2);
                if(add_ship_horizontal(playerInfo,conXtonum,contYtonum,2)==-1){
                    return -1;
                }
            }
            else if (spec[i] == 'P'){
                //add_ship_vertical(playerInfo,conXtonum,contYtonum,2);
                if(add_ship_vertical(playerInfo,conXtonum,contYtonum,2)==-1){
                    return -1;
                }
            }
             return 1;
        }
         else{
             return -1;
        }

    }
    return 1;
}

int add_ship_horizontal(player_info *player, int x, int y, int length) {
    if(length == 0) {
        return 1;
    }
       else{
        unsigned long long int mask = xy_to_bitval(x, y);

           //check if there is a ship on a position where the player is trying to put the ship
           // the player has the information of the ship
           //using the AND operator to check of that position on the board has been used or not.
           // if so then i am returning -1  because it is invalid spec
           if(player->ships & mask){
               return -1;
           }
           else
               {
               player->ships = player->ships | mask;
               return add_ship_horizontal(player, x + 1, y, length - 1);
           }
       }
    // implement this as part of Step 2
    // returns 1 if the ship can be added, -1 if not
    // hint: this can be defined recursively
}
int add_ship_vertical(player_info *player, int x, int y, int length) {
    if(length == 0){
        return 1;
    }

    else {
        unsigned  long long int mask = xy_to_bitval(x,y);
        if(player->ships & mask) {
            return -1;
        } else{

            player->ships = player->ships | mask;
            return add_ship_vertical(player,x,y+1,length-1);
        }

    }


}
    // implement this as part of Step 2
    // returns 1 if the ship can be added, -1 if not
    // hint: this can be defined recursively
