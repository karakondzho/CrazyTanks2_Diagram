#ifndef _FUNCTION_CPP_
#define _FUNCTION_CPP_

#include <stdlib.h>
#include <time.h>
#include "Types.cpp"

bool
InitializeConsole(HANDLE *InputHandle, HANDLE *OutputHandle)
{
   bool Result = true;
   
   *InputHandle = GetStdHandle(STD_INPUT_HANDLE);
   *OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   if((*InputHandle) == INVALID_HANDLE_VALUE ||
      (*OutputHandle) == INVALID_HANDLE_VALUE)
   {
      Result = false;
      return Result;
   }
   
   return Result;
}

void
MakeOutWalls(World *WorldBuffer, uint Width, uint Height)
{
   for(int i = 0;
       i < Width;
       i++)
   {
      for(int j = 0;
          j < Height;
          j++)
      {
         if(i == 0)
         {
            WorldBuffer[i*Height+j].Type = CAPTION;
         }
         else if((i == 1) || (i == (Width-1)) ||
                 (j == 0) || (j == (Height-1)))
         {
            WorldBuffer[i*Height+j].Type = WALL;
         }
         else
         {
            WorldBuffer[i*Height+j].Type = EMPTY;
         }
      }
   }
}

void
InitializeTank(World *WorldBuffer, uint Height, Tank *T,
               COORD TankPosition, uint TankDirection, TankType Type)
{
   T->MuzzlePosition = TankPosition;
   T->Type = Type;
   T->State = ACTIVE;
   if(TankDirection == 0)
   {
      T->BodyPosition = {TankPosition.X, TankPosition.Y + 1};
      T->TankDirection = LEFT;
      WorldBuffer[T->MuzzlePosition.X*Height+T->MuzzlePosition.Y].Type = TANK_LEFT_RIGHT;
   }
   else if(TankDirection == 1)
   {
      T->BodyPosition = {TankPosition.X, TankPosition.Y - 1};
      T->TankDirection = RIGHT;
      WorldBuffer[T->MuzzlePosition.X*Height+T->MuzzlePosition.Y].Type = TANK_LEFT_RIGHT;
   }
   else if(TankDirection == 2)
   {
      T->BodyPosition = {TankPosition.X + 1, TankPosition.Y};
      T->TankDirection = UP;
      WorldBuffer[T->MuzzlePosition.X*Height+T->MuzzlePosition.Y].Type = TANK_UP_DOWN;
   }
   else if(TankDirection == 3) 
   {
      T->BodyPosition = {TankPosition.X - 1, TankPosition.Y};
      T->TankDirection = DOWN;
      WorldBuffer[T->MuzzlePosition.X*Height+T->MuzzlePosition.Y].Type = TANK_UP_DOWN;
   }
   if(Type == ENEMY)
   {
      WorldBuffer[T->BodyPosition.X*Height+T->BodyPosition.Y].Type = ENEMY_TANK_BODY;
   }
   else if(Type == PLAYER)
   {
      WorldBuffer[T->BodyPosition.X*Height+T->BodyPosition.Y].Type = PLAYER_TANK_BODY;
   }
}

void
MakeMainPlayer(World *WorldBuffer, uint Width, uint Height, Tank *TanksArray)
{
   COORD Pos = {};
   Pos.X = Width - 3;
   Pos.Y = Height / 2;

   uint TankDirection = 2; //NOTE: 0 - Left, 1 - Right, 2 - Up , 3 - Down
   TankType Type = PLAYER;
   InitializeTank(WorldBuffer, Height, &TanksArray[0], Pos, TankDirection, Type);
}

bool
IsEmptyCell(World *WorldBuffer, uint Height, uint i, uint j)
{
   if(WorldBuffer[i*Height+j].Type == EMPTY)
   {
      return true;
   }

   return false;
}

void
PutWall(World *WorldBuffer, uint Width, uint Height, Wall W)
{
   while(W.BlocksInWall)
   {
      COORD RandPos = {};

      RandPos.X = rand() % (Width-1) + 2;
      RandPos.Y = rand() % (Height-1) + 1;

      if(IsEmptyCell(WorldBuffer, Height, RandPos.X, RandPos.Y))
      {
         WorldBuffer[RandPos.X*Height+RandPos.Y].Type = WALL;
         W.BlocksInWall--;
         while(W.BlocksInWall)
         {
            int i = RandPos.X;
            int j = RandPos.Y;

            if(IsEmptyCell(WorldBuffer, Height, --i, j))
            {
               WorldBuffer[i*Height+j].Type = WALL;
               RandPos.X = i;
               W.BlocksInWall--;
            }
            else if(IsEmptyCell(WorldBuffer, Height, ++i, j))
            {
               WorldBuffer[i*Height+j].Type = WALL;
               RandPos.X = i;
               W.BlocksInWall--;
            }
            else if(IsEmptyCell(WorldBuffer, Height, i, --j))
            {
               WorldBuffer[i*Height+j].Type = WALL;
               RandPos.Y = j;
               W.BlocksInWall--;
            }
            else if(IsEmptyCell(WorldBuffer, Height, i, ++j))
            {
               WorldBuffer[i*Height+j].Type = WALL;
               RandPos.Y = j;
               W.BlocksInWall--;
            }
         }
      }
   }
}

void
MakeInnerWalls(World *WorldBuffer, uint Width, uint Height)
{
   Wall BigWalls = {};
   Wall MiddleWalls = {};
   Wall SmallWalls = {};

   //NOTE: Yeah, magic numbers :)
   uint NumberOfBigWalls = 10;
   uint NumberOfMiddleWalls = 15;
   uint NumberOfSmallWalls = 20;

   srand(time(0));
   BigWalls.NumberOfWalls = rand() % NumberOfBigWalls + 1;
   BigWalls.BlocksInWall = 4;

   MiddleWalls.NumberOfWalls = rand() % NumberOfMiddleWalls + 1;
   MiddleWalls.BlocksInWall = 2;

   SmallWalls.NumberOfWalls = rand() % NumberOfSmallWalls + 1;
   SmallWalls.BlocksInWall = 1;

   while(BigWalls.NumberOfWalls)
   {
      PutWall(WorldBuffer, Width, Height, BigWalls);
      BigWalls.NumberOfWalls--;
   }
   
   while(MiddleWalls.NumberOfWalls)
   {
      PutWall(WorldBuffer, Width, Height, MiddleWalls);
      MiddleWalls.NumberOfWalls--;
   }

   while(SmallWalls.NumberOfWalls)
   {
      PutWall(WorldBuffer, Width, Height, SmallWalls);
      SmallWalls.NumberOfWalls--;
   }
}

bool
CheckNearbyTanks(World *WorldBuffer, uint Width, uint Height, int PosX, int PosY)
{
   int MinI = 1;
   int MinJ = 0;
   int MaxI = Width;
   int MaxJ = Height;

   int StartI = PosX;
   int StartJ = PosY;
   int FinishI = PosX;
   int FinishJ = PosY;

   if((StartI - 4) < MinI)
   {
      StartI = 2;
   }
   else
   {
      StartI -= 2;
   }
   
   if((StartJ - 4) < MinJ)
   {
      StartJ = 1;
   }
   else
   {
      StartJ -= 2;
   }

   if((FinishI + 4) > MaxI)
   {
      FinishI = MaxI - 1;
   }
   else
   {
      FinishI += 2;
   }

   if((FinishJ + 4) > MaxJ)
   {
      FinishJ = MaxJ - 1;
   }
   else
   {
      FinishJ += 2;
   }

   for(int i = StartI;
       i <= FinishI;
       i++)
   {
      for(int j = StartJ;
          j <= FinishJ;
          j++)
      {
         if(WorldBuffer[i*Height+j].Type == TANK_LEFT_RIGHT ||
            WorldBuffer[i*Height+j].Type == TANK_UP_DOWN ||
            WorldBuffer[i*Height+j].Type == ENEMY_TANK_BODY ||
            WorldBuffer[i*Height+j].Type == PLAYER_TANK_BODY)
         {
            return false;
         }
      }
   }

   return true;
}

void
MakeEnemyTanks(World *WorldBuffer, uint Width, uint Height, Tank *TanksArray, uint TanksNumber)
{
   uint Count = TanksNumber-1;
   while(Count)
   {
      COORD RandPos;
      RandPos.X = rand() % (Width - 1) + 2;
      RandPos.Y = rand() % (Height - 1) + 1;

      if(IsEmptyCell(WorldBuffer, Height, RandPos.X, RandPos.Y))
      {
         if(IsEmptyCell(WorldBuffer, Height, RandPos.X+1, RandPos.Y+1) &&
            IsEmptyCell(WorldBuffer, Height, RandPos.X-1, RandPos.Y+1) &&
            IsEmptyCell(WorldBuffer, Height, RandPos.X+1, RandPos.Y-1) &&
            IsEmptyCell(WorldBuffer, Height, RandPos.X-1, RandPos.Y-1))

         {
            if(CheckNearbyTanks(WorldBuffer, Width, Height, RandPos.X, RandPos.Y))
            {
               for(int i = 1;
                   i < TanksNumber;
                   i++)
               {
                  if(TanksArray[i].Type == EMPTY_TANK)
                  {
                     uint MuzzleDirection = rand() % 4; //NOTE: 0 - Left, 1 - Right, 2 - Top, 3 - Bottom
                     InitializeTank(WorldBuffer, Height, &TanksArray[i], RandPos, MuzzleDirection, ENEMY); 
                     break;
                  }
               }
               Count--;
            }
         }
      }
   }
}

void
MakeProjectileArray(Projectile *ProjectilesArray, Tank *TanksArray, uint TanksNumber, float ProjectileSpeed)
{
   for(int i = 0;
       i < TanksNumber;
       i++)
   {
      ProjectilesArray[i].Fire = false;
      ProjectilesArray[i].Shooter = &TanksArray[i];
      ProjectilesArray[i].Position = TanksArray[i].MuzzlePosition;
      ProjectilesArray[i].Life = 0;
      ProjectilesArray[i].Speed = ProjectileSpeed;
      ProjectilesArray[i].ProjectileDirection = TanksArray[i].TankDirection;
   }
}

void
InitializeWorld(World *WorldBuffer, uint Width, uint Height, Tank *TanksArray,
                Projectile *ProjectilesArray, uint TanksNumber, float ProjectileSpeed)
{
   MakeOutWalls(WorldBuffer, Width, Height);
   MakeMainPlayer(WorldBuffer, Width, Height, TanksArray);
   MakeInnerWalls(WorldBuffer, Width, Height);
   MakeEnemyTanks(WorldBuffer, Width, Height, TanksArray, TanksNumber);
   MakeProjectileArray(ProjectilesArray, TanksArray, TanksNumber, ProjectileSpeed);
}

void
DrawCharactersToBuffer(World *WorldBuffer, uint Width, uint Height, CHAR_INFO *BufferOfCharacters)
{
   for(int i = 0;
       i < Width;
       i++)
   {
      for(int j = 0;
          j < Height;
          j++)
      {
         World W = WorldBuffer[i*Height+j];
         CHAR_INFO *CharInfo = &BufferOfCharacters[i*Height+j];

         if(W.Type == EMPTY)
         {
            CharInfo->Char.AsciiChar = ' ';
            CharInfo->Attributes = BACKGROUND_RED | BACKGROUND_GREEN |
               BACKGROUND_BLUE| BACKGROUND_INTENSITY;
         }
         else if(W.Type == CAPTION)
         {
            CharInfo->Char.AsciiChar = ' ';
            CharInfo->Attributes = 0;
         }
         else if(W.Type == WALL)
         {
            CharInfo->Char.AsciiChar = ' ';
            CharInfo->Attributes = BACKGROUND_RED;
         }
         else if(W.Type == PLAYER_TANK_BODY)
         {
            CharInfo->Char.AsciiChar = ' ';
            CharInfo->Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
         }
         else if(W.Type == ENEMY_TANK_BODY)
         {
            CharInfo->Char.AsciiChar = ' ';
            CharInfo->Attributes = BACKGROUND_GREEN | BACKGROUND_BLUE;
         }
         else if(W.Type == TANK_LEFT_RIGHT)
         {
            CharInfo->Char.AsciiChar = (char)205;
            CharInfo->Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY | 
               BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
         }
         else if(W.Type == TANK_UP_DOWN)
         {
            CharInfo->Char.AsciiChar = (char)186;
            CharInfo->Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY | 
               BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
         }
         else if(W.Type == ENEMY_PROJECTILE)
         {
            CharInfo->Char.AsciiChar = (char)248;
            CharInfo->Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE | 
               BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
         }
         else if(W.Type == PLAYER_PROJECTILE)
         {
            CharInfo->Char.AsciiChar = (char)248;
            CharInfo->Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY | 
               BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
         }
      }
   }
}

void
MakeMove(World *WorldBuffer, uint Height, Tank *T, COORD OldBodyPosition,
         COORD OldMuzzlePosition, COORD NewMuzzlePosition, Direction NewTankDirection) 
{
      if(IsEmptyCell(WorldBuffer, Height, NewMuzzlePosition.X, NewMuzzlePosition.Y))
      {
         T->MuzzlePosition = NewMuzzlePosition;
         T->TankDirection = NewTankDirection;

         WorldBuffer[OldMuzzlePosition.X*Height+OldMuzzlePosition.Y].Type = EMPTY;
         WorldBuffer[OldBodyPosition.X*Height+OldBodyPosition.Y].Type = EMPTY;

         if(NewTankDirection == LEFT)
         {
            T->BodyPosition = {NewMuzzlePosition.X, NewMuzzlePosition.Y + 1};
            WorldBuffer[T->MuzzlePosition.X*Height+T->MuzzlePosition.Y].Type = TANK_LEFT_RIGHT;
         }
         else if(NewTankDirection == RIGHT)
         {
            T->BodyPosition = {NewMuzzlePosition.X, NewMuzzlePosition.Y - 1};
            WorldBuffer[T->MuzzlePosition.X*Height+T->MuzzlePosition.Y].Type = TANK_LEFT_RIGHT;
         }
         else if(NewTankDirection == UP)
         {
            T->BodyPosition = {NewMuzzlePosition.X + 1, NewMuzzlePosition.Y};
            WorldBuffer[T->MuzzlePosition.X*Height+T->MuzzlePosition.Y].Type = TANK_UP_DOWN;
         }
         else if(NewTankDirection == DOWN)
         {
            T->BodyPosition = {NewMuzzlePosition.X - 1, NewMuzzlePosition.Y};
            WorldBuffer[T->MuzzlePosition.X*Height+T->MuzzlePosition.Y].Type = TANK_UP_DOWN;
         }
         if(T->Type == ENEMY)
         {
            WorldBuffer[T->BodyPosition.X*Height+T->BodyPosition.Y].Type = ENEMY_TANK_BODY;
         }
         else if(T->Type == PLAYER)
         {
            WorldBuffer[T->BodyPosition.X*Height+T->BodyPosition.Y].Type = PLAYER_TANK_BODY;
         }

      }
}

void
UpdateTankPosition(World *WorldBuffer, uint Height, Tank *T, Direction NewTankDirection)
{
   if(T->State == ACTIVE)
   {
      Direction OldTankDirection = T->TankDirection;
      COORD NewMuzzlePosition = T->MuzzlePosition;
      COORD OldMuzzlePosition = T->MuzzlePosition;
      COORD OldBodyPosition = T->BodyPosition;

      if(NewTankDirection == LEFT)
      {
         if(OldTankDirection == NewTankDirection)
         {
            --NewMuzzlePosition.Y;
         }
         else
         {
            if(OldTankDirection == UP)
            {
               NewMuzzlePosition.X++;
               NewMuzzlePosition.Y--;
            }
            else if(OldTankDirection == DOWN)
            {
               NewMuzzlePosition.X--;
               NewMuzzlePosition.Y--;
            }
            else if(OldTankDirection == RIGHT)
            {
               NewMuzzlePosition.Y -= 2;
            }
         }
         MakeMove(WorldBuffer, Height, T, OldBodyPosition, OldMuzzlePosition, NewMuzzlePosition, NewTankDirection);
      }
      else if(NewTankDirection == RIGHT)
      {
         if(OldTankDirection == NewTankDirection)
         {
            ++NewMuzzlePosition.Y;
         }
         else
         {
            if(OldTankDirection == UP)
            {
               NewMuzzlePosition.X++;
               NewMuzzlePosition.Y++;
            }
            else if(OldTankDirection == DOWN)
            {
               NewMuzzlePosition.X--;
               NewMuzzlePosition.Y++;
            }
            else if(OldTankDirection == LEFT)
            {
               NewMuzzlePosition.Y += 2;
            }
         }
         MakeMove(WorldBuffer, Height, T, OldBodyPosition, OldMuzzlePosition, NewMuzzlePosition, NewTankDirection);
      }
      else if(NewTankDirection == UP)
      {
         if(OldTankDirection == NewTankDirection)
         {
            --NewMuzzlePosition.X;
         }
         else
         {
            if(OldTankDirection == LEFT)
            {
               NewMuzzlePosition.X--;
               NewMuzzlePosition.Y++;
            }
            else if(OldTankDirection == DOWN)
            {
               NewMuzzlePosition.X -= 2;
            }
            else if(OldTankDirection == RIGHT)
            {
               NewMuzzlePosition.X--;
               NewMuzzlePosition.Y--;
            }
         }
         MakeMove(WorldBuffer, Height, T, OldBodyPosition, OldMuzzlePosition, NewMuzzlePosition, NewTankDirection);
      }
      else if(NewTankDirection == DOWN)
      {
         if(OldTankDirection == NewTankDirection)
         {
            ++NewMuzzlePosition.X;
         }
         else
         {
            if(OldTankDirection == UP)
            {
               NewMuzzlePosition.X += 2;
            }
            else if(OldTankDirection == LEFT)
            {
               NewMuzzlePosition.X++;
               NewMuzzlePosition.Y++;
            }
            else if(OldTankDirection == RIGHT)
            {
               NewMuzzlePosition.Y--;
               NewMuzzlePosition.X++;
            }
         }
         MakeMove(WorldBuffer, Height, T, OldBodyPosition, OldMuzzlePosition, NewMuzzlePosition, NewTankDirection);
      }
   }
}

void
MoveEnemieTanks(World *WorldBuffer, uint Height, Tank *TanksArray, uint NumberOfTanks, float Speed)
{
   static float NewSpeed = 0;
   NewSpeed += Speed;
   if(NewSpeed > 1)
   {
      for(int i = 1;
          i < NumberOfTanks;
          i++)
      {
         uint Direction = rand() % 4;
         if(Direction == 0)
         {
            UpdateTankPosition(WorldBuffer, Height, &TanksArray[i], LEFT);
         }
         else if(Direction == 1)
         {
            UpdateTankPosition(WorldBuffer, Height, &TanksArray[i], RIGHT);
         }
         else if(Direction == 2)
         {
            UpdateTankPosition(WorldBuffer, Height, &TanksArray[i], UP);
         }
         else if(Direction == 3)
         {
            UpdateTankPosition(WorldBuffer, Height, &TanksArray[i], DOWN);
         }
      }
      NewSpeed = 0;
   }
}

void
MoveProjectile(World *WorldBuffer, uint Height, Tank *TanksArray, uint NumberOfTanks,
               Projectile *P, COORD NewProjectilePosition,
               uint MaxProjectiles)
{
   WorldType Object = WorldBuffer[NewProjectilePosition.X*Height+NewProjectilePosition.Y].Type;
   COORD OldProjectilePosition = P->Position;
   if(Object == EMPTY)
   {
      P->Position = NewProjectilePosition;
      P->Fire = true;
      P->Life++;
      if(P->Shooter->Type == ENEMY)
      {
         WorldBuffer[P->Position.X*Height+P->Position.Y].Type = ENEMY_PROJECTILE;
      }
      else if(P->Shooter->Type == PLAYER)
      {
         WorldBuffer[P->Position.X*Height+P->Position.Y].Type = PLAYER_PROJECTILE;
      }
   }
   else if(Object == WALL)
   {
      P->Life = 0;
      P->Fire = false;
      P->Position = P->Shooter->MuzzlePosition;
      P->ProjectileDirection = P->Shooter->TankDirection;
   }
   else if(Object == TANK_LEFT_RIGHT || Object == TANK_UP_DOWN)
   {
      P->Life = 0;
      P->Fire = false;
      P->Position = P->Shooter->MuzzlePosition;
      P->ProjectileDirection = P->Shooter->TankDirection;
      for(int i = 0;
          i < NumberOfTanks;
          i++)
      {
         if((TanksArray[i].MuzzlePosition.X == NewProjectilePosition.X &&
            TanksArray[i].MuzzlePosition.Y == NewProjectilePosition.Y) ||
            (TanksArray[i].BodyPosition.X == NewProjectilePosition.X &&
             TanksArray[i].BodyPosition.Y == NewProjectilePosition.Y))

         {
            if(P->Shooter->Type != TanksArray[i].Type)
            {
               TanksArray[i].State = DEAD;
               WorldBuffer[TanksArray[i].MuzzlePosition.X*Height+TanksArray[i].MuzzlePosition.Y].Type = EMPTY;
               WorldBuffer[TanksArray[i].BodyPosition.X*Height+TanksArray[i].BodyPosition.Y].Type = EMPTY;
            }
         }
      }
   }
   else if(Object == ENEMY_TANK_BODY)
   {
      P->Life = 0;
      P->Fire = false;
      P->Position = P->Shooter->MuzzlePosition;
      P->ProjectileDirection = P->Shooter->TankDirection;
      for(int i = 0;
          i < NumberOfTanks;
          i++)
      {
         if((TanksArray[i].MuzzlePosition.X == NewProjectilePosition.X &&
            TanksArray[i].MuzzlePosition.Y == NewProjectilePosition.Y) ||
            (TanksArray[i].BodyPosition.X == NewProjectilePosition.X &&
             TanksArray[i].BodyPosition.Y == NewProjectilePosition.Y))

         {
            if(P->Shooter->Type != TanksArray[i].Type)
            {
               TanksArray[i].State = DEAD;
               WorldBuffer[TanksArray[i].MuzzlePosition.X*Height+TanksArray[i].MuzzlePosition.Y].Type = EMPTY;
               WorldBuffer[TanksArray[i].BodyPosition.X*Height+TanksArray[i].BodyPosition.Y].Type = EMPTY;
            }
         }
      }
   }
   else if(Object == PLAYER_TANK_BODY)
   {
      P->Life = 0;
      P->Fire = false;
      P->Position = P->Shooter->MuzzlePosition;
      P->ProjectileDirection = P->Shooter->TankDirection;
      for(int i = 0;
          i < NumberOfTanks;
          i++)
      {
         if((TanksArray[i].MuzzlePosition.X == NewProjectilePosition.X &&
            TanksArray[i].MuzzlePosition.Y == NewProjectilePosition.Y) ||
            (TanksArray[i].BodyPosition.X == NewProjectilePosition.X &&
             TanksArray[i].BodyPosition.Y == NewProjectilePosition.Y))

         {
            if(P->Shooter->Type != TanksArray[i].Type)
            {
               TanksArray[i].State = DEAD;
               WorldBuffer[TanksArray[i].MuzzlePosition.X*Height+TanksArray[i].MuzzlePosition.Y].Type = EMPTY;
               WorldBuffer[TanksArray[i].BodyPosition.X*Height+TanksArray[i].BodyPosition.Y].Type = EMPTY;
            }
         }
      }
   }
}

void
ShootProjectile(World *WorldBuffer, uint Height, Tank *TanksArray, uint NumberOfTanks,
                Projectile *P, uint MaxProjectiles)
{
   COORD NewProjectilePosition = P->Position;
   COORD OldProjectilePosition = P->Position;
   if(P->Fire == false && P->Life < MaxProjectiles)
   {
      if(P->ProjectileDirection == LEFT)
      {
         NewProjectilePosition.Y--;
         MoveProjectile(WorldBuffer, Height, TanksArray, NumberOfTanks,
                        P, NewProjectilePosition, MaxProjectiles);
      }
      else if(P->ProjectileDirection == RIGHT)
      {
         NewProjectilePosition.Y++;
         MoveProjectile(WorldBuffer, Height, TanksArray, NumberOfTanks,
                        P, NewProjectilePosition, MaxProjectiles);
      }
      else if(P->ProjectileDirection == UP)
      {
         NewProjectilePosition.X--;
         MoveProjectile(WorldBuffer, Height, TanksArray, NumberOfTanks,
                        P, NewProjectilePosition, MaxProjectiles);
      }
      else if(P->ProjectileDirection == DOWN)
      {
         NewProjectilePosition.X++;
         MoveProjectile(WorldBuffer, Height, TanksArray, NumberOfTanks,
                        P, NewProjectilePosition, MaxProjectiles);
      }
   }
   else if(P->Life < MaxProjectiles)
   {
         if(P->ProjectileDirection == LEFT)
         {
            NewProjectilePosition.Y--;
            MoveProjectile(WorldBuffer, Height, TanksArray, NumberOfTanks,
                           P, NewProjectilePosition, MaxProjectiles);
         }
         else if(P->ProjectileDirection == RIGHT)
         {
            NewProjectilePosition.Y++;
            MoveProjectile(WorldBuffer, Height, TanksArray, NumberOfTanks,
                           P, NewProjectilePosition, MaxProjectiles);
         }
         else if(P->ProjectileDirection == UP)
         {
            NewProjectilePosition.X--;
            MoveProjectile(WorldBuffer, Height, TanksArray, NumberOfTanks,
                           P, NewProjectilePosition, MaxProjectiles);
         }
         else if(P->ProjectileDirection == DOWN)
         {
            NewProjectilePosition.X++;
            MoveProjectile(WorldBuffer, Height, TanksArray, NumberOfTanks,
                           P, NewProjectilePosition, MaxProjectiles);
         }
         WorldBuffer[OldProjectilePosition.X*Height+OldProjectilePosition.Y].Type = EMPTY;
         P->Life++;
   }
   else
   {
      P->Life = 0;
      P->Fire = false;
      P->Position = P->Shooter->MuzzlePosition;
      P->ProjectileDirection = P->Shooter->TankDirection;
      WorldBuffer[OldProjectilePosition.X*Height+OldProjectilePosition.Y].Type = EMPTY;
   }
}

void
UpdatePlayerProjectile(World *WorldBuffer, uint Height, Tank *TanksArray, uint NumberOfTanks,
                       Projectile *P, float ProjectileSpeed, uint MaxProjectiles)
{
   static float NewSpeed = 0;
   NewSpeed += P->Speed;
   if(NewSpeed > 1)
   {
      COORD OldProjectilePosition = P->Position;
      COORD NewProjectilePosition = P->Position;
      if(P->Fire == true && P->Life < MaxProjectiles)
      {
         if(P->ProjectileDirection == LEFT)
         {
            NewProjectilePosition.Y--;
            MoveProjectile(WorldBuffer, Height, TanksArray, NumberOfTanks,
                           P, NewProjectilePosition, MaxProjectiles);
         }
         else if(P->ProjectileDirection == RIGHT)
         {
            NewProjectilePosition.Y++;
            MoveProjectile(WorldBuffer, Height, TanksArray, NumberOfTanks,
                           P, NewProjectilePosition, MaxProjectiles);
         }
         else if(P->ProjectileDirection == UP)
         {
            NewProjectilePosition.X--;
            MoveProjectile(WorldBuffer, Height, TanksArray, NumberOfTanks,
                           P, NewProjectilePosition, MaxProjectiles);
         }
         else if(P->ProjectileDirection == DOWN)
         {
            NewProjectilePosition.X++;
            MoveProjectile(WorldBuffer, Height, TanksArray, NumberOfTanks,
                           P, NewProjectilePosition, MaxProjectiles);
         }
         P->Life++;
         WorldBuffer[OldProjectilePosition.X*Height+OldProjectilePosition.Y].Type = EMPTY;
         if(P->Life >= MaxProjectiles)
         {
            WorldBuffer[NewProjectilePosition.X*Height+NewProjectilePosition.Y].Type = EMPTY;
         }
      }
      else
      {
         P->Life = 0;
         P->Fire = false;
         P->Position = P->Shooter->MuzzlePosition;
         P->ProjectileDirection = P->Shooter->TankDirection;
      }
      NewSpeed = 0;
   }

}

void
UpdateEnemyProjectiles(World *WorldBuffer, uint Height, Tank *TanksArray, uint NumberOfTanks,
                       Projectile *ProjectilesArray, uint MaxProjectiles, float ProjectileSpeed)
{
   static float NewSpeed = 0;
   NewSpeed += ProjectileSpeed;
   if(NewSpeed > 1)
   {
      for(int i = 1;
          i < NumberOfTanks;
          i++)
      {
         if(TanksArray[i].State == ACTIVE)
         {
            ShootProjectile(WorldBuffer, Height, TanksArray, NumberOfTanks, &ProjectilesArray[i], MaxProjectiles);
         }
         else
         {
            WorldBuffer[ProjectilesArray[i].Position.X*Height+ProjectilesArray[i].Position.Y].Type = EMPTY;
         }
      }
      NewSpeed = 0;
   }
}

#endif
