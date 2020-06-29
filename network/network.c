#include <stdio.h>

#include "../common.h"
#include "network.h"
#include "../lib/message.h"

CLIENT_ENET* cl_create_enet(CLIENT_ENET* enet)
{
    if(!enet)
    {
        enet = (CLIENT_ENET*)malloc(sizeof(CLIENT_ENET));
        show_message_error(enet, "Failed to allocate space for CLIENT_ENET");
    }
    
    show_message_error(enet_initialize() == 0, "Failed to allocate space for CLIENT_ENET");
    
    int port = enet->port;
    char host[20];
    strncpy(host, enet->host, 20);
    
    enet->client = enet_host_create(NULL, 1, 2, 0, 0);
    show_message_error(enet->client, "Failed to client host create");
    
    enet_address_set_host(&enet->address, host);
    enet->address.port = port;
    
    enet->server = enet_host_connect(enet->client, &enet->address, 2, 0);
    show_message_error(enet->server, "Failed to server connect");
    
    if (enet_host_service(enet->client, &enet->event, 5000) > 0 && enet->event.type == ENET_EVENT_TYPE_CONNECT)
    {
        enet->connect = true;
        printf("Клиент: присоединён к серверу %x:%hu\n", enet->event.peer->address.host, enet->event.peer->address.port);
    }
    else
    {
        enet->connect = false;
        puts("Клиент: не удалось присоединиться к серверу");
        enet_peer_reset(enet->server);
        cl_destroy_enet(enet);
    }
    
    return enet;
}

void cl_free_enet(CLIENT_ENET* enet)
{
    cl_destroy_enet(enet);
    free(enet);
}

void cl_destroy_enet(CLIENT_ENET* enet)
{
    enet_host_destroy(enet->client);
    enet_deinitialize();
}

void cl_disconnect_enet(CLIENT_ENET* enet)
{
    enet_peer_disconnect(enet->server, 0);
    
    ENetEvent event;
    
    while (enet_host_service (enet->client, &event, 3000) > 0)
        switch (event.type)
        {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                puts("Клиент: успешное отсоединение");
                return;
            case ENET_EVENT_TYPE_NONE:
            case ENET_EVENT_TYPE_CONNECT:
                break;
        }
      
    enet_peer_reset(enet->server);

    enet->connect = false;
    cl_destroy_enet(enet);
}
