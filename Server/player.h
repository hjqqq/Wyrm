#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <list>
#include <set>
#include <SFML/Network.hpp>
#include "inventory.h"
#include "objects/object.h"

class Player {
  public:
    Player(Object* o);
    ~Player();

    // Network Handlers
    void Update();
    void SendPacket(sf::Packet& p, bool prio = false );
    void ReceivePacket(sf::Packet*);
    void HandlePacket(sf::Packet& p);
    void Auth(sf::Packet p);
    inline void Delete() { delete_me = true; }
    inline bool IsDeleted() { return delete_me; }

    // ID Handlers
    inline sf::Uint16 GetId() { return id; }
    inline Object* GetAgent() { return agent; }
    void SetAgent(Object* o);

    inline std::string GetName() { return name; }
    inline Inventory* GetInventory() { return inventory; }
  private:
    void Send(sf::Packet& p);
    void HandleSocketData();
    void FlushBuffer();

    // ID vars
    sf::Uint16 id;
    sf::String name;

    // Network vars
    sf::TcpSocket* connection;
    bool delete_me;
    bool half_open;
    std::list<sf::Packet*> send_buffer;
    std::list<sf::Packet*> recv_buffer;

    // Character vars
    Object* agent;
    Inventory* inventory;
};

#endif // PLAYER_H_INCLUDED
