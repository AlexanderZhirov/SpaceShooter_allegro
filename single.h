/* 
 * File:   single.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.08
 */

#ifndef client_single
#define client_single

void single_handling(CLIENT_DATA* data);
void single_draw(CLIENT_DATA* data);

void cl_init_objects(CLIENT_DATA* data);

/************************************************************
 * SHIP
 ***********************************************************/
static void cl_draw_ship(CLIENT_DATA* data);
static void cl_move_ship_up(CLIENT_DATA* data);
static void cl_move_ship_down(CLIENT_DATA* data);
static void cl_move_ship_left(CLIENT_DATA* data);
static void cl_move_ship_right(CLIENT_DATA* data);
static void cl_reset_ship_animation(CLIENT_DATA* data, int position);
static bool cl_dead_ship(CLIENT_DATA* data);
/************************************************************
 * BULLET
 ***********************************************************/
static void cl_draw_bullet(CLIENT_DATA* data);
static void cl_fire_bullet(CLIENT_DATA* data);
static void cl_update_bullet(CLIENT_DATA* data);
static void cl_collide_bullet(CLIENT_DATA* data);
/************************************************************
 * COMET
 ***********************************************************/
static void cl_draw_comet(CLIENT_DATA* data);
static void cl_start_comet(CLIENT_DATA* data);
static void cl_update_comet(CLIENT_DATA* data);
static void cl_collide_comet(CLIENT_DATA* data);
/************************************************************
 * EXPLOSIONS
 ***********************************************************/
static void cl_draw_explosions(CLIENT_DATA* data);
static void cl_start_explosions(CLIENT_DATA* data, int x, int y);
static void cl_update_explosions(CLIENT_DATA* data);
/************************************************************
 * STATISTIC
 ***********************************************************/
static void cl_draw_statistic(CLIENT_DATA* data);

#endif



