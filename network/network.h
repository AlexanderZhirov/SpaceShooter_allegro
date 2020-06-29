/* 
 * File:   network.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.12
 */

#ifndef client_network
#define client_network

#include <enet/enet.h>
#include <stdbool.h>

typedef enum srv_state
{
    STATE_NONE,
    STATE_LIST,
    STATE_PARTY,
    STATE_GAME,
    STATE_DISCONNECT
} SERVER_STATE;


typedef struct cl_user_command
{
    int dx;
    int dy;
    bool fire;
} SERVER_USER_COMMAND;

typedef struct cl_user
{
    int id;
    char nickname[40];
    bool is_ready;
    SERVER_USER_COMMAND command;
} CLIENT_USER;

typedef struct cl_gamedata
{
    int id;
    char game_name[40];
    int count_connected;
} CLIENT_GAME_DATA;

typedef struct cl_game_command
{
    int dx;
    int dy;
    bool fire;
    bool send;
} CLIENT_GAME_COMMAND;

typedef struct cl_network
{    
    int game_id;
    int user_id;
    char game_name[40];
    CLIENT_USER users[3];
    CLIENT_GAME_DATA games[3];
    int user_size;
    int count_connected;
    int count_game;
    bool game_started;
    bool active;
    bool is_creator;
    bool is_ready;
    CLIENT_GAME_COMMAND command;
} CLIENT_NETWORK;

typedef struct cl_message_none
{
    int display_width;
    int display_height;
    float scale_factor;
    SERVER_STATE state;
    char game_name[40];
    char nickname[40];
    bool is_creator;
    bool is_ready;
} CLIENT_MESSAGE_NONE;

typedef struct cl_message_party
{
    int game_id;
    int user_id;
    CLIENT_USER users[3];
    char game_name[40];
    int count_connected;
    bool game_started;
    bool active;
    bool is_creator;
    bool is_ready;
    SERVER_STATE state;
} CLIENT_MESSAGE_PARTY;

typedef struct cl_message_list
{
    CLIENT_GAME_DATA games[3];
    SERVER_STATE state;
    int count_game;
} CLIENT_MESSAGE_LIST;

typedef struct cl_message_joingame
{
    int id;
    SERVER_STATE state;
} CLIENT_MESSAGE_JOINGAME;

typedef struct cl_message_sendparty
{
    SERVER_STATE state;
    bool is_creator;
    bool is_ready;
    bool kick_user;
    int user_id;
} CLIENT_MESSAGE_SENDPARTY;

typedef struct cl_message_game
{
    int dx;
    int dy;
    bool fire;
    SERVER_STATE state;
} CLIENT_MESSAGE_GAME;

// GAME

typedef struct cl_update_ship
{
    int ID;
    int x;
    int y;
    int dx;
    int dy;
    int lives;
    int score;
    bool active;
} CLIENT_UPDATE_SHIP;

typedef struct cl_update_bullet
{
    int ID;
    int x;
    int y;
    bool live;
    bool active;
} CLIENT_UPDATE_BULLET;

typedef struct cl_update_comet
{
    int x;
    int y;
    bool live;
} CLIENT_UPDATE_COMET;

typedef struct cl_update_explosion
{
    int x;
    int y;
    bool live;
} CLIENT_UPDATE_EXPLOSION;

typedef struct cl_message_update
{
    CLIENT_UPDATE_SHIP ship[3];
    CLIENT_UPDATE_BULLET bullet[15];
    CLIENT_UPDATE_COMET comet[15];
    CLIENT_UPDATE_EXPLOSION explosion[15];
} CLIENT_MESSAGE_UPDATE;

typedef struct cl_enet
{
    ENetHost* client;
    ENetPeer* server;
    ENetEvent event;
    ENetAddress address;
    bool connect;
    int port;
    char host[20];
} CLIENT_ENET;

CLIENT_ENET* cl_create_enet(CLIENT_ENET* enet);
void cl_free_enet(CLIENT_ENET* enet);
void cl_destroy_enet(CLIENT_ENET* enet);
void cl_disconnect_enet(CLIENT_ENET* enet);

#endif

