/* 
 * File:   network_game.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.12
 */

#ifndef client_network_game
#define client_network_game

void networkgame_handling(CLIENT_DATA* data);
void networkgame_draw(CLIENT_DATA* data);

void networkgame_create_objects(CLIENT_DATA* data);
void networkgame_enet_receive(CLIENT_DATA* data);

static void networkgame_send_move_ship(CLIENT_DATA* data);

/************************************************************
 * SHIP
 ***********************************************************/
static void networkgame_draw_ship(CLIENT_DATA* data);
static void networkgame_move_ship_up(CLIENT_DATA* data);
static void networkgame_move_ship_down(CLIENT_DATA* data);
static void networkgame_move_ship_left(CLIENT_DATA* data);
static void networkgame_move_ship_right(CLIENT_DATA* data);
static void networkgame_reset_ship_animation(CLIENT_DATA* data, int position);
static bool networkgame_dead_ship(CLIENT_DATA* data);
/************************************************************
 * BULLET
 ***********************************************************/
static void networkgame_fire_bullet(CLIENT_DATA* data);
static void networkgame_draw_bullet(CLIENT_DATA* data);
/************************************************************
 * COMET
 ***********************************************************/
static void networkgame_draw_comet(CLIENT_DATA* data);
void networkgame_update_comet(CLIENT_DATA* data);
/************************************************************
 * EXPLOSION
 ***********************************************************/
static void networkgame_draw_explosions(CLIENT_DATA* data);
void networkgame_update_explosions(CLIENT_DATA* data);
/************************************************************
 * STATISTIC
 ***********************************************************/
static void networkgame_draw_statistic(CLIENT_DATA* data);

#endif



