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

enum WorldType
{
   CAPTION,
   LIFE_COUNTER_RED,
   LIFE_COUNTER_GREY,
   ENEMIES_COUNTER,
   EMPTY,
   FIELD,
   WALL,
   HIT_WALL,
   CHEST,
   TANK_LEFT_RIGHT,
   TANK_UP_DOWN,
   ENEMY_TANK_BODY,
   PLAYER_TANK_BODY,
   PLAYER_MUZZLE_LEFT_RIGHT,
   PLAYER_MUZZLE_UP_DOWN,
   ENEMY_PROJECTILE,
   PLAYER_PROJECTILE,
};

enum TankType
{
   EMPTY_TANK,
   ENEMY,
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
   uint Life;
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

struct Caption
{
   COORD Position;
   ObjectState State;
   char Character;
};

#endif
