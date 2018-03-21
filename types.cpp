#ifndef _TYPES_CPP_
#define _TYPES_CPP_

#include <windows.h>

typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned short ushort;

enum GameState
{
   RUNNING,
   GAME_OVER,
   WIN,
   PAUSE,
   EXIT,
};

GameState Game = RUNNING;

enum Direction
{
   LEFT,
   RIGHT,
   UP,
   DOWN,
};

//TODO: SUPER_ENEMY_TANK_BODY is temporary and need to be deleted after testing
enum WorldType
{
   CAPTION,
   EMPTY,
   FIELD,
   WALL,
   HIT_WALL,
   CHEST,
   TANK_LEFT_RIGHT,
   TANK_UP_DOWN,
   ENEMY_TANK_BODY,
   SUPER_ENEMY_TANK_BODY,
   PLAYER_TANK_BODY,
   ENEMY_PROJECTILE,
   PLAYER_PROJECTILE,
};

//TODO: SUPER_ENEMY is temporary and need to be deleted after testing
enum TankType
{
   EMPTY_TANK,
   ENEMY,
   SUPER_ENEMY,
   PLAYER,
};

enum ObjectState
{
   DEAD,
   LIVE,
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
   ObjectState State;
};

struct Wall
{
   COORD Position;
   ObjectState State;
   uint BlocksInWall;
   uint Strength;
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

struct Chest
{
   COORD Position;
   ObjectState State;
};

#endif
