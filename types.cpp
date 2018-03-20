#ifndef _TYPES_CPP_
#define _TYPES_CPP_

#include <windows.h>

typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned short ushort;

enum Direction
{
   LEFT,
   RIGHT,
   UP,
   DOWN,
};

enum WorldType
{
   EMPTY,
   WALL,
   CAPTION,
   TANK_LEFT_RIGHT,
   TANK_UP_DOWN,
   ENEMY_TANK_BODY,
   PLAYER_TANK_BODY,
   ENEMY_PROJECTILE,
   PLAYER_PROJECTILE,
};

enum TankType
{
   EMPTY_TANK,
   GOLD,
   ENEMY,
   PLAYER,
};

enum TankState
{
   ACTIVE,
   DEAD,
};

struct World
{
   WorldType Type;
};

struct Tank
{
   COORD MuzzlePosition;
   COORD BodyPosition;
   Direction TankDirection;
   TankType Type;
   TankState State;
};

struct Wall
{
   uint BlocksInWall;
   uint NumberOfWalls;
};

struct Projectile
{
   bool Fire;
   Tank *Shooter;
   COORD Position;
   uint Life;
   float Speed;
   Direction ProjectileDirection;
};

#endif
