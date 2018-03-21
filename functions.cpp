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
MakeField(World *WorldBuffer, uint Width, uint Height)
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
            WorldBuffer[i*Height+j].Type = FIELD;
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
   T->State = LIVE;
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
   else if(Type == SUPER_ENEMY)
   {
      WorldBuffer[T->BodyPosition.X*Height+T->BodyPosition.Y].Type = SUPER_ENEMY_TANK_BODY;
   }
   else if(Type == PLAYER)
   {
      WorldBuffer[T->BodyPosition.X*Height+T->BodyPosition.Y].Type = PLAYER_TANK_BODY;
   }
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
WriteWallStats(World *WorldBuffer, uint Height, Wall *W, COORD Position, ObjectState State, uint Strength)
{
   W->Position = {Position.X, Position.Y};
   W->State = State;
   W->Strength = Strength;
   WorldBuffer[Position.X*Height+Position.Y].Type = WALL;
}

void
MakeWalls(World *WorldBuffer, uint Width, uint Height, Wall *W, uint NumberOfWalls, uint WallStrength)
{
   uint Index = 0;
   for(short i = 2;
       i < (Width - 1);
       i++)
   {
      for(short j = 1;
          j < (Height - 1);
          j++)
      {
         if(WorldBuffer[i*Height+j].Type == WALL)
         {
            if(Index < NumberOfWalls)
            {
               W[Index].Position = {i, j};
               W[Index].State = LIVE;
               W[Index].Strength = WallStrength;
               Index++;
            }

         }
      }
   }
   srand(time(0));
   COORD RandPos = {};

   while(Index < NumberOfWalls)
   {
      RandPos.X = rand() % (Width-1) + 2;
      RandPos.Y = rand() % (Height-1) + 1;
      uint NumberOfBlocks = rand() % 4;
      while(NumberOfBlocks && (Index < NumberOfWalls))
      {
         if(IsEmptyCell(WorldBuffer, Height, RandPos.X, RandPos.Y))
         {
            WriteWallStats(WorldBuffer, Height, &W[Index], RandPos, LIVE, WallStrength);
            --NumberOfBlocks;
            ++RandPos.X;
            ++Index;
         }
         else if(IsEmptyCell(WorldBuffer, Height, ++RandPos.X, RandPos.Y))
         {
            WriteWallStats(WorldBuffer, Height, &W[Index], RandPos, LIVE, WallStrength);
            --NumberOfBlocks;
            ++Index;
         }
         else if(IsEmptyCell(WorldBuffer, Height, RandPos.X, --RandPos.Y))
         {
            WriteWallStats(WorldBuffer, Height, &W[Index], RandPos, LIVE, WallStrength);
            --NumberOfBlocks;
            ++Index;
         }
         else if(IsEmptyCell(WorldBuffer, Height, --RandPos.X, RandPos.Y))
         {
            WriteWallStats(WorldBuffer, Height, &W[Index], RandPos, LIVE, WallStrength);
            --NumberOfBlocks;
            ++Index;
         }
         else if(IsEmptyCell(WorldBuffer, Height, RandPos.X, ++RandPos.Y))
         {
            WriteWallStats(WorldBuffer, Height, &W[Index], RandPos, LIVE, WallStrength);
            --NumberOfBlocks;
            ++Index;
         }
         else
         {
            RandPos.X = rand() % (Width-1) + 2;
            RandPos.Y = rand() % (Height-1) + 1;
         }
      }
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
            WorldBuffer[i*Height+j].Type == SUPER_ENEMY_TANK_BODY ||
            WorldBuffer[i*Height+j].Type == PLAYER_TANK_BODY)
         {
            return false;
         }
      }
   }

   return true;
}

void
MakeTanks(World *WorldBuffer, uint Width, uint Height, Tank *TanksArray, uint TanksNumber)
{
   for(int i = 0;
       i < TanksNumber;
       i++)
   {
      while(TanksArray[i].Type == EMPTY_TANK)
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
                  uint MuzzleDirection = rand() % 4; //NOTE: 0 - Left, 1 - Right, 2 - Top, 3 - Bottom
                  if(i == 0)
                  {
                     InitializeTank(WorldBuffer, Height, &TanksArray[i], RandPos, MuzzleDirection, PLAYER); 
                  }
                  else if(i == 1)
                  {
                     InitializeTank(WorldBuffer, Height, &TanksArray[i], RandPos, MuzzleDirection, SUPER_ENEMY); 
                  }
                  else
                  {
                     InitializeTank(WorldBuffer, Height, &TanksArray[i], RandPos, MuzzleDirection, ENEMY); 
                  }
                  break;
               }
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
MakeChest(World *WorldBuffer, uint Width, uint Height, Chest *GoldChest)
{
   COORD Pos = {};
   Pos.X = Width - 2;
   Pos.Y = Height / 2;

   for(int i = (Pos.X - 1);
       i <= Pos.X;
       i++)
   {
      for(int j = (Pos.Y - 1);
          j <= (Pos.Y + 1);
          j++)
      {
         if(i == Pos.X && j == Pos.Y)
         {
            GoldChest->Position = Pos;
            GoldChest->State = LIVE;
            WorldBuffer[i*Height+j].Type = CHEST;
         }
         else
         {
            WorldBuffer[i*Height+j].Type = WALL;
         }
      }
   }

}

void
InitializeWorld(World *WorldBuffer, uint Width, uint Height,
                Tank *TanksArray, uint TanksNumber,
                Projectile *ProjectilesArray, float ProjectileSpeed,
                Chest *GoldChest,
                Wall *WallsArray, uint NumberOfWalls, uint WallStrength)
{
   MakeField(WorldBuffer, Width, Height);
   MakeChest(WorldBuffer, Width, Height, GoldChest);
   MakeWalls(WorldBuffer, Width, Height, WallsArray, NumberOfWalls, WallStrength);
   MakeTanks(WorldBuffer, Width, Height, TanksArray, TanksNumber);
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
         else if(W.Type == FIELD)
         {
            CharInfo->Char.AsciiChar = ' ';
            CharInfo->Attributes = BACKGROUND_RED;
         }
         else if(W.Type == WALL)
         {
            CharInfo->Char.AsciiChar = ' ';
            CharInfo->Attributes = BACKGROUND_INTENSITY;
         }
         else if(W.Type == HIT_WALL)
         {
            CharInfo->Char.AsciiChar = ' ';
            CharInfo->Attributes = BACKGROUND_RED;
         }
         else if(W.Type == CHEST)
         {
            CharInfo->Char.AsciiChar = ' ';
            CharInfo->Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
         }
         else if(W.Type == PLAYER_TANK_BODY)
         {
            CharInfo->Char.AsciiChar = ' ';
            CharInfo->Attributes = BACKGROUND_RED | BACKGROUND_INTENSITY;
         }
         else if(W.Type == ENEMY_TANK_BODY)
         {
            CharInfo->Char.AsciiChar = ' ';
            CharInfo->Attributes = BACKGROUND_GREEN | BACKGROUND_BLUE;
         }
         else if(W.Type == SUPER_ENEMY_TANK_BODY)
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
         else if(T->Type == SUPER_ENEMY)
         {
            WorldBuffer[T->BodyPosition.X*Height+T->BodyPosition.Y].Type = SUPER_ENEMY_TANK_BODY;
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
   if(T->State == LIVE)
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
ClearProjectile(Projectile *P)
{
   P->Life = 0;
   P->Fire = false;
   P->Position = P->Shooter->MuzzlePosition;
   P->ProjectileDirection = P->Shooter->TankDirection;
}

void CheckProjectileOnTank(World *WorldBuffer, uint Height, Tank *TanksArray, uint NumberOfTanks, Projectile P)
{
   for(int i = 0;
       i < NumberOfTanks;
       i++)
   {
      if((TanksArray[i].MuzzlePosition.X == P.Position.X &&
          TanksArray[i].MuzzlePosition.Y == P.Position.Y) ||
         (TanksArray[i].BodyPosition.X == P.Position.X &&
          TanksArray[i].BodyPosition.Y == P.Position.Y))

      {
         if(P.Shooter->Type != TanksArray[i].Type)
         {
            TanksArray[i].State = DEAD;
            WorldBuffer[TanksArray[i].MuzzlePosition.X*Height+TanksArray[i].MuzzlePosition.Y].Type = EMPTY;
            WorldBuffer[TanksArray[i].BodyPosition.X*Height+TanksArray[i].BodyPosition.Y].Type = EMPTY;
         }
#if 0
         if((P.Shooter->Type == PLAYER) && ((TanksArray[i].Type == ENEMY) || (TanksArray[i].Type == SUPER_ENEMY)))
         {
            TanksArray[i].State = DEAD;
            WorldBuffer[TanksArray[i].MuzzlePosition.X*Height+TanksArray[i].MuzzlePosition.Y].Type = EMPTY;
            WorldBuffer[TanksArray[i].BodyPosition.X*Height+TanksArray[i].BodyPosition.Y].Type = EMPTY;
         }
         else if((P.Shooter->Type == ENEMY) || (P.Shooter->Type == SUPER_ENEMY) && (TanksArray[i].Type == PLAYER))
         {
            TanksArray[i].State = DEAD;
            WorldBuffer[TanksArray[i].MuzzlePosition.X*Height+TanksArray[i].MuzzlePosition.Y].Type = EMPTY;
            WorldBuffer[TanksArray[i].BodyPosition.X*Height+TanksArray[i].BodyPosition.Y].Type = EMPTY;
         }
#endif
      }
   }
}

void
CheckProjectileOnWall(World *WorldBuffer, uint Height,
                      Wall *WallsArray, uint NumberOfWalls, Projectile P)
{
   for(int i = 0;
       i < NumberOfWalls;
       i++)
   {
      if(WallsArray[i].State == LIVE)
      {
         if(WallsArray[i].Position.X == P.Position.X &&
            WallsArray[i].Position.Y == P.Position.Y)
         {
            if(WallsArray[i].Strength != 0)
            {
               --WallsArray[i].Strength;
               WorldBuffer[WallsArray[i].Position.X*Height+WallsArray[i].Position.Y].Type = HIT_WALL;
            }
            else
            {
               WallsArray[i].State = DEAD;
               WorldBuffer[WallsArray[i].Position.X*Height+WallsArray[i].Position.Y].Type = EMPTY;
            }
         }
      }
   }
}

void
MoveProjectile(World *WorldBuffer, uint Height,
               Tank *TanksArray, uint NumberOfTanks,
               Projectile *P, COORD NewProjectilePosition, uint MaxProjectiles,
               Wall *WallsArray, uint NumberOfWalls)
{
   WorldType Object = WorldBuffer[NewProjectilePosition.X*Height+NewProjectilePosition.Y].Type;
   COORD OldProjectilePosition = P->Position;
   P->Position = NewProjectilePosition;
   if(Object == EMPTY)
   {
      P->Fire = true;
      P->Life++;
      if(P->Shooter->Type == ENEMY || P->Shooter->Type == SUPER_ENEMY)
      {
         WorldBuffer[P->Position.X*Height+P->Position.Y].Type = ENEMY_PROJECTILE;
      }
      else if(P->Shooter->Type == PLAYER)
      {
         WorldBuffer[P->Position.X*Height+P->Position.Y].Type = PLAYER_PROJECTILE;
      }
   }
   else if(Object == FIELD)
   {
      ClearProjectile(P);
   }
   else if(Object == WALL)
   {
      CheckProjectileOnWall(WorldBuffer, Height, WallsArray, NumberOfWalls, *P);
      ClearProjectile(P);
   }
   else if(Object == HIT_WALL)
   {
      CheckProjectileOnWall(WorldBuffer, Height, WallsArray, NumberOfWalls, *P);
      ClearProjectile(P);
   }
   else if(Object == CHEST)
   {
      Game = GAME_OVER;
   }
   else if(Object == TANK_LEFT_RIGHT || Object == TANK_UP_DOWN)
   {
      CheckProjectileOnTank(WorldBuffer, Height, TanksArray, NumberOfTanks, *P);
      ClearProjectile(P);
   }
   else if(Object == ENEMY_TANK_BODY)
   {
      CheckProjectileOnTank(WorldBuffer, Height, TanksArray, NumberOfTanks, *P);
      ClearProjectile(P);
   }
   else if(Object == SUPER_ENEMY_TANK_BODY)
   {
      CheckProjectileOnTank(WorldBuffer, Height, TanksArray, NumberOfTanks, *P);
      ClearProjectile(P);
   }
   else if(Object == PLAYER_TANK_BODY)
   {
      CheckProjectileOnTank(WorldBuffer, Height, TanksArray, NumberOfTanks, *P);
      ClearProjectile(P);
   }
}

COORD
CheckNextProjectileMove(Projectile P, COORD NewProjectilePosition)
{
   COORD Result = NewProjectilePosition;
   if(P.ProjectileDirection == LEFT)
   {
      Result.Y--;
   }
   else if(P.ProjectileDirection == RIGHT)
   {
      Result.Y++;
   }
   else if(P.ProjectileDirection == UP)
   {
      Result.X--;
   }
   else if(P.ProjectileDirection == DOWN)
   {
      Result.X++;
   }

   return Result;
}
void
ShootProjectile(World *WorldBuffer, uint Height, Tank *TanksArray, uint NumberOfTanks,
                Projectile *P, uint MaxProjectiles,
                Wall *WallsArray, uint NumberOfWalls)
{
   COORD NewProjectilePosition = P->Position;
   COORD OldProjectilePosition = P->Position;
   if(P->Fire == false && P->Life < MaxProjectiles)
   {
      NewProjectilePosition = CheckNextProjectileMove(*P, NewProjectilePosition);
      MoveProjectile(WorldBuffer, Height, TanksArray, NumberOfTanks,
                     P, NewProjectilePosition, MaxProjectiles,
                     WallsArray, NumberOfWalls);
   }
   else if(P->Life < MaxProjectiles)
   {
      NewProjectilePosition = CheckNextProjectileMove(*P, NewProjectilePosition);
      MoveProjectile(WorldBuffer, Height, TanksArray, NumberOfTanks,
                     P, NewProjectilePosition, MaxProjectiles,
                     WallsArray, NumberOfWalls);
      WorldBuffer[OldProjectilePosition.X*Height+OldProjectilePosition.Y].Type = EMPTY;
      P->Life++;
   }
   else
   {
      ClearProjectile(P);
      WorldBuffer[OldProjectilePosition.X*Height+OldProjectilePosition.Y].Type = EMPTY;
   }
}

void
UpdatePlayerProjectile(World *WorldBuffer, uint Height, Tank *TanksArray, uint NumberOfTanks,
                       Projectile *P, float ProjectileSpeed, uint MaxProjectiles,
                       Wall *WallsArray, uint NumberOfWalls)
{
   static float NewSpeed = 0;
   NewSpeed += P->Speed;
   if(NewSpeed > 1)
   {
      COORD OldProjectilePosition = P->Position;
      COORD NewProjectilePosition = P->Position;
      if(P->Fire == true && P->Life < MaxProjectiles)
      {
         NewProjectilePosition = CheckNextProjectileMove(*P, NewProjectilePosition);
         MoveProjectile(WorldBuffer, Height, TanksArray, NumberOfTanks,
                           P, NewProjectilePosition, MaxProjectiles,
                           WallsArray, NumberOfWalls);
         P->Life++;
         WorldBuffer[OldProjectilePosition.X*Height+OldProjectilePosition.Y].Type = EMPTY;
         if(P->Life >= MaxProjectiles)
         {
            WorldBuffer[NewProjectilePosition.X*Height+NewProjectilePosition.Y].Type = EMPTY;
         }
      }
      else
      {
         ClearProjectile(P);
      }
      NewSpeed = 0;
   }

}

void
UpdateEnemyProjectiles(World *WorldBuffer, uint Height, Tank *TanksArray, uint NumberOfTanks,
                       Projectile *ProjectilesArray, uint MaxProjectiles, float ProjectileSpeed,
                       Wall *WallsArray, uint NumberOfWalls)
{
   static float NewSpeed = 0;
   NewSpeed += ProjectileSpeed;
   if(NewSpeed > 1)
   {
      for(int i = 1;
          i < NumberOfTanks;
          i++)
      {
         if(TanksArray[i].State == LIVE)
         {
            ShootProjectile(WorldBuffer, Height, TanksArray, NumberOfTanks,
                            &ProjectilesArray[i], MaxProjectiles,
                            WallsArray, NumberOfWalls);
         }
         else
         {
            WorldBuffer[ProjectilesArray[i].Position.X*Height+ProjectilesArray[i].Position.Y].Type = EMPTY;
         }
      }
      NewSpeed = 0;
   }
}

ushort
ReadFromConsole(HANDLE ConsoleHandle, INPUT_RECORD *InputBuffer, const int InputBufferSize, ulong *BufferEvents)
{
   ushort Result = 0;
   KEY_EVENT_RECORD KeyEvent = {};
   bool ReadFromConsoleInput = ReadConsoleInput(ConsoleHandle,
                                                InputBuffer,
                                                InputBufferSize,
                                                BufferEvents);

   if(ReadFromConsoleInput)
   {
      if(InputBuffer->EventType == KEY_EVENT)
      {
         KeyEvent = InputBuffer->Event.KeyEvent;
         if(KeyEvent.bKeyDown)
         {
            Result = KeyEvent.wVirtualKeyCode;
         }
      }
   }
   return Result;
}


#endif
