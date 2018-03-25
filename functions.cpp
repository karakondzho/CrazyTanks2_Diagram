#ifndef _FUNCTION_CPP_
#define _FUNCTION_CPP_

#include <stdlib.h>
#include <time.h>
#include "Types.cpp"

static float GameSpeed = 0;

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
MakeField(World *WorldBuffer, uint BufferWidth, uint BufferHeight)
{
   for(int i = 0;
       i < BufferWidth;
       i++)
   {
      for(int j = 0;
          j < BufferHeight;
          j++)
      {
         if(i == 0)
         {
            WorldBuffer[i*BufferHeight+j].Type = CAPTION;
         }
         else if((i == 1) || (i == (BufferWidth-1)) ||
                 (j == 0) || (j == (BufferHeight-1)))
         {
            WorldBuffer[i*BufferHeight+j].Type = FIELD;
         }
         else
         {
            WorldBuffer[i*BufferHeight+j].Type = EMPTY;
         }
      }
   }
}

void
InitializeTank(World *WorldBuffer, uint BufferHeight, Tank *T,
               COORD TankPosition, uint TankDirection, uint TankLife, TankType Type)
{
   T->MuzzlePosition = TankPosition;
   T->Type = Type;
   T->State = LIVE;
   T->Life = TankLife;
   if(TankDirection == 0)
   {
      T->BodyPosition = {T->MuzzlePosition.X, T->MuzzlePosition.Y + 1};
      T->TankDirection = LEFT;
      if(T->Type == PLAYER)
      {
         WorldBuffer[T->MuzzlePosition.X*BufferHeight+T->MuzzlePosition.Y].Type = PLAYER_MUZZLE_LEFT_RIGHT;
         WorldBuffer[T->BodyPosition.X*BufferHeight+T->BodyPosition.Y].Type = PLAYER_TANK_BODY;
      }
      else
      {
         WorldBuffer[T->MuzzlePosition.X*BufferHeight+T->MuzzlePosition.Y].Type = TANK_LEFT_RIGHT;
         WorldBuffer[T->BodyPosition.X*BufferHeight+T->BodyPosition.Y].Type = ENEMY_TANK_BODY;
      }
   }
   else if(TankDirection == 1)
   {
      T->BodyPosition = {T->MuzzlePosition.X, T->MuzzlePosition.Y - 1};
      T->TankDirection = RIGHT;
      if(T->Type == PLAYER)
      {
         WorldBuffer[T->MuzzlePosition.X*BufferHeight+T->MuzzlePosition.Y].Type = PLAYER_MUZZLE_LEFT_RIGHT;
         WorldBuffer[T->BodyPosition.X*BufferHeight+T->BodyPosition.Y].Type = PLAYER_TANK_BODY;
      }
      else
      {
         WorldBuffer[T->MuzzlePosition.X*BufferHeight+T->MuzzlePosition.Y].Type = TANK_LEFT_RIGHT;
         WorldBuffer[T->BodyPosition.X*BufferHeight+T->BodyPosition.Y].Type = ENEMY_TANK_BODY;
      }
   }
   else if(TankDirection == 2)
   {
      T->BodyPosition = {T->MuzzlePosition.X + 1, T->MuzzlePosition.Y};
      T->TankDirection = UP;
      if(T->Type == PLAYER)
      {
         WorldBuffer[T->MuzzlePosition.X*BufferHeight+T->MuzzlePosition.Y].Type = PLAYER_MUZZLE_UP_DOWN;
         WorldBuffer[T->BodyPosition.X*BufferHeight+T->BodyPosition.Y].Type = PLAYER_TANK_BODY;
      }
      else
      {
         WorldBuffer[T->MuzzlePosition.X*BufferHeight+T->MuzzlePosition.Y].Type = TANK_UP_DOWN;
         WorldBuffer[T->BodyPosition.X*BufferHeight+T->BodyPosition.Y].Type = ENEMY_TANK_BODY;
      }
   }
   else if(TankDirection == 3) 
   {
      T->BodyPosition = {T->MuzzlePosition.X - 1, T->MuzzlePosition.Y};
      T->TankDirection = DOWN;
      if(T->Type == PLAYER)
      {
         WorldBuffer[T->MuzzlePosition.X*BufferHeight+T->MuzzlePosition.Y].Type = PLAYER_MUZZLE_UP_DOWN;
      WorldBuffer[T->BodyPosition.X*BufferHeight+T->BodyPosition.Y].Type = PLAYER_TANK_BODY;
      }
      else
      {
         WorldBuffer[T->MuzzlePosition.X*BufferHeight+T->MuzzlePosition.Y].Type = TANK_UP_DOWN;
      WorldBuffer[T->BodyPosition.X*BufferHeight+T->BodyPosition.Y].Type = ENEMY_TANK_BODY;
      }
   }
}

bool
IsEmptyCell(World *WorldBuffer, uint BufferHeight, uint i, uint j)
{
   if(WorldBuffer[i*BufferHeight+j].Type == EMPTY)
   {
      return true;
   }

   return false;
}

void
WriteWallStats(World *WorldBuffer, uint BufferHeight, Wall *W, COORD Position, ObjectState State, uint Strength)
{
   W->Position = {Position.X, Position.Y};
   W->State = State;
   W->Strength = Strength;
   WorldBuffer[Position.X*BufferHeight+Position.Y].Type = WALL;
}

void
MakeWalls(World *WorldBuffer, uint BufferWidth, uint BufferHeight, Wall *W, uint NumberOfWalls, uint WallStrength)
{
   uint Index = 0;
   for(short i = 2;
       i < (BufferWidth - 1);
       i++)
   {
      for(short j = 1;
          j < (BufferHeight - 1);
          j++)
      {
         if(WorldBuffer[i*BufferHeight+j].Type == WALL)
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
      RandPos.X = rand() % (BufferWidth-1) + 2;
      RandPos.Y = rand() % (BufferHeight-1) + 1;
      uint NumberOfBlocks = rand() % 4;
      while(NumberOfBlocks && (Index < NumberOfWalls))
      {
         if(IsEmptyCell(WorldBuffer, BufferHeight, RandPos.X, RandPos.Y))
         {
            WriteWallStats(WorldBuffer, BufferHeight, &W[Index], RandPos, LIVE, WallStrength);
            --NumberOfBlocks;
            ++RandPos.X;
            ++Index;
         }
         else if(IsEmptyCell(WorldBuffer, BufferHeight, ++RandPos.X, RandPos.Y))
         {
            WriteWallStats(WorldBuffer, BufferHeight, &W[Index], RandPos, LIVE, WallStrength);
            --NumberOfBlocks;
            ++Index;
         }
         else if(IsEmptyCell(WorldBuffer, BufferHeight, RandPos.X, --RandPos.Y))
         {
            WriteWallStats(WorldBuffer, BufferHeight, &W[Index], RandPos, LIVE, WallStrength);
            --NumberOfBlocks;
            ++Index;
         }
         else if(IsEmptyCell(WorldBuffer, BufferHeight, --RandPos.X, RandPos.Y))
         {
            WriteWallStats(WorldBuffer, BufferHeight, &W[Index], RandPos, LIVE, WallStrength);
            --NumberOfBlocks;
            ++Index;
         }
         else if(IsEmptyCell(WorldBuffer, BufferHeight, RandPos.X, ++RandPos.Y))
         {
            WriteWallStats(WorldBuffer, BufferHeight, &W[Index], RandPos, LIVE, WallStrength);
            --NumberOfBlocks;
            ++Index;
         }
         else
         {
            RandPos.X = rand() % (BufferWidth-1) + 2;
            RandPos.Y = rand() % (BufferHeight-1) + 1;
         }
      }
   }
}

bool
CheckNearbyTanks(World *WorldBuffer, uint BufferWidth, uint BufferHeight, int PosX, int PosY)
{
   int MinI = 1;
   int MinJ = 0;
   int MaxI = BufferWidth;
   int MaxJ = BufferHeight;

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
         if(WorldBuffer[i*BufferHeight+j].Type == TANK_LEFT_RIGHT ||
            WorldBuffer[i*BufferHeight+j].Type == TANK_UP_DOWN ||
            WorldBuffer[i*BufferHeight+j].Type == ENEMY_TANK_BODY ||
            WorldBuffer[i*BufferHeight+j].Type == PLAYER_TANK_BODY ||
            WorldBuffer[i*BufferHeight+j].Type == PLAYER_MUZZLE_LEFT_RIGHT ||
            WorldBuffer[i*BufferHeight+j].Type == PLAYER_MUZZLE_UP_DOWN)
         {
            return false;
         }
      }
   }

   return true;
}

void
MakeTanks(World *WorldBuffer, uint BufferWidth, uint BufferHeight, Tank *TanksArray, uint TanksNumber, uint TankLife)
{
   for(int i = 0;
       i < TanksNumber;
       i++)
   {
      while(TanksArray[i].Type == EMPTY_TANK)
      {
         COORD RandPos;
         RandPos.X = rand() % (BufferWidth - 1) + 2;
         RandPos.Y = rand() % (BufferHeight - 1) + 1;
         if(IsEmptyCell(WorldBuffer, BufferHeight, RandPos.X, RandPos.Y))
         {
            if(IsEmptyCell(WorldBuffer, BufferHeight, RandPos.X, RandPos.Y+1) &&
               IsEmptyCell(WorldBuffer, BufferHeight, RandPos.X, RandPos.Y-1) &&
               IsEmptyCell(WorldBuffer, BufferHeight, RandPos.X+1, RandPos.Y) &&
               IsEmptyCell(WorldBuffer, BufferHeight, RandPos.X-1, RandPos.Y))

            {
               if(CheckNearbyTanks(WorldBuffer, BufferWidth, BufferHeight, RandPos.X, RandPos.Y))
               {
                  uint MuzzleDirection = rand() % 4; //NOTE: 0 - Left, 1 - Right, 2 - Top, 3 - Bottom
                  uint EnemyLife = 1;
                  if(i == 0)
                  {
                     InitializeTank(WorldBuffer, BufferHeight, &TanksArray[i], RandPos, MuzzleDirection, TankLife, PLAYER); 
                  }
                  else
                  {
                     InitializeTank(WorldBuffer, BufferHeight, &TanksArray[i], RandPos, MuzzleDirection, EnemyLife, ENEMY); 
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
MakeChest(World *WorldBuffer, uint BufferWidth, uint BufferHeight, Chest *GoldChest)
{
   COORD Pos = {};
   Pos.X = BufferWidth - 2;
   Pos.Y = BufferHeight / 2;

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
            WorldBuffer[i*BufferHeight+j].Type = CHEST;
         }
         else
         {
            WorldBuffer[i*BufferHeight+j].Type = WALL;
         }
      }
   }

}

void
ClearTanksArray(Tank *TanksArray, uint NumberOfTanks)
{
   for(int i = 0;
       i < NumberOfTanks;
       i++)
   {
      TanksArray[i].MuzzlePosition = {};
      TanksArray[i].BodyPosition = {};
      TanksArray[i].TankDirection = LEFT;
      TanksArray[i].Type = EMPTY_TANK;
      TanksArray[i].State = DEAD;
   }
}

void
ClearWallsArray(Wall *WallsArray, uint NumberOfWalls)
{
   for(int i = 0;
       i < NumberOfWalls;
       i++)
   {
      WallsArray[i].Position = {};
      WallsArray[i].State = DEAD;
      WallsArray[i].BlocksInWall = 0;
      WallsArray[i].Strength = 0;
   }
}

void
ClearProjectileArray(Projectile *ProjectilesArray, uint NumberOfProjectiles)
{
   for(int i = 0;
       i < NumberOfProjectiles;
       i++)
   {
      ProjectilesArray[i].Fire = false;
      ProjectilesArray[i].Shooter = 0;
      ProjectilesArray[i].Position = {};
      ProjectilesArray[i].Life = 0;
      ProjectilesArray[i].Speed = 0;
      ProjectilesArray[i].ProjectileDirection = LEFT;
   }
}

void
ClearWorld(World *WorldBuffer, uint BufferWidth, uint BufferHeight)
{
   for(int i = 0;
       i < BufferWidth;
       i++)
   {
      for(int j = 0;
          j < BufferHeight;
          j++)
      {
         WorldBuffer[i*BufferHeight+j].Type = EMPTY;
      }
   }
}

void
ClearCaption(Caption *CaptionArray, uint BufferHeight)
{
   for(int i = 0;
       i < BufferHeight;
       i++)
   {
      CaptionArray[i].Position = {};
      CaptionArray[i].State = DEAD;
   }
}

void
MakeLifeCaption(World *WorldBuffer, Caption *LifeCaption, uint LifeCaptionLength)
{
   for(uint i = 0;
       i < LifeCaptionLength;
       i++)
   {
      LifeCaption[i].Position.Y = i;
      LifeCaption[i].State = LIVE;
      LifeCaption[i].Character = 3;
      WorldBuffer[i].Type = LIFE_COUNTER_RED;
   }

}

void
MakeEnemyCaption(World *WorldBuffer, Caption *EnemyCaption, uint BufferHeight, uint EnemyCaptionCounter)
{
   for(uint i = 0;
       i < EnemyCaptionCounter;
       i++)
   {
      EnemyCaption[i].Position.Y = i + (BufferHeight - EnemyCaptionCounter-1);
      EnemyCaption[i].State = LIVE;
      WorldBuffer[EnemyCaption[i].Position.Y].Type = ENEMIES_COUNTER;
   }
   EnemyCaption[0].Character = 'E';
   EnemyCaption[1].Character = 'n';
   EnemyCaption[2].Character = 'e';
   EnemyCaption[3].Character = 'm';
   EnemyCaption[4].Character = 'i';
   EnemyCaption[5].Character = 'e';
   EnemyCaption[6].Character = 's';
   EnemyCaption[7].Character = ' ';
   EnemyCaption[8].Character = 'k';
   EnemyCaption[9].Character = 'i';
   EnemyCaption[10].Character = 'l';
   EnemyCaption[11].Character = 'l';
   EnemyCaption[12].Character = 'e';
   EnemyCaption[13].Character = 'd';
   EnemyCaption[14].Character = ':';
}

void
InitializeWorld(World *WorldBuffer, uint BufferWidth, uint BufferHeight,
                Tank *TanksArray, uint NumberOfTanks, uint TanksLife,
                Projectile *ProjectilesArray, float ProjectileSpeed,
                Chest *GoldChest,
                Wall *WallsArray, uint NumberOfWalls, uint WallStrength,
                Caption *LifeCaption, uint LifeCaptionLength,
                Caption *EnemyCaption, uint EnemyCaptionCounter)
{
   ClearWorld(WorldBuffer, BufferWidth, BufferHeight);
   ClearCaption(LifeCaption, LifeCaptionLength);
   ClearCaption(EnemyCaption, EnemyCaptionCounter);
   ClearTanksArray(TanksArray, NumberOfTanks);
   ClearWallsArray(WallsArray, NumberOfWalls);
   ClearProjectileArray(ProjectilesArray, NumberOfTanks);

   MakeField(WorldBuffer, BufferWidth, BufferHeight);
   MakeLifeCaption(WorldBuffer, LifeCaption, LifeCaptionLength);
   MakeEnemyCaption(WorldBuffer, EnemyCaption, BufferHeight, EnemyCaptionCounter);
   MakeChest(WorldBuffer, BufferWidth, BufferHeight, GoldChest);
   MakeWalls(WorldBuffer, BufferWidth, BufferHeight, WallsArray, NumberOfWalls, WallStrength);
   MakeTanks(WorldBuffer, BufferWidth, BufferHeight, TanksArray, NumberOfTanks, TanksLife);
   MakeProjectileArray(ProjectilesArray, TanksArray, NumberOfTanks, ProjectileSpeed);
}

void
DrawCharactersToBuffer(World *WorldBuffer, uint BufferWidth, uint BufferHeight, CHAR_INFO *BufferOfCharacters,
                       Caption *LifeCaption, Caption *EnemyCaption, uint EnemyCaptionCounter)
{
   for(int i = 0;
       i < BufferWidth;
       i++)
   {
      for(int j = 0;
          j < BufferHeight;
          j++)
      {
         World W = WorldBuffer[i*BufferHeight+j];
         CHAR_INFO *CharInfo = &BufferOfCharacters[i*BufferHeight+j];

         if(W.Type == EMPTY)
         {
            CharInfo->Char.AsciiChar = ' ';
            CharInfo->Attributes = BACKGROUND_RED | BACKGROUND_GREEN |
               BACKGROUND_BLUE| BACKGROUND_INTENSITY;
         }
         else if(W.Type == CAPTION)
         {
            CharInfo->Char.AsciiChar = 0;
            CharInfo->Attributes = FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN |
               BACKGROUND_INTENSITY;
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
         else if(W.Type == PLAYER_MUZZLE_LEFT_RIGHT)
         {
            CharInfo->Char.AsciiChar = (char)205;
            CharInfo->Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY | 
               BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
         }
         else if(W.Type == PLAYER_MUZZLE_UP_DOWN)
         {
            CharInfo->Char.AsciiChar = (char)186;
            CharInfo->Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY | 
               BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
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
         else if(W.Type == LIFE_COUNTER_RED)
         {
            CharInfo->Char.AsciiChar = LifeCaption[0].Character;
            CharInfo->Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
               BACKGROUND_INTENSITY;
         }
         else if(W.Type == LIFE_COUNTER_GREY)
         {
            CharInfo->Char.AsciiChar = LifeCaption[0].Character;
            CharInfo->Attributes = FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
               BACKGROUND_INTENSITY;
         }
         else if(W.Type == ENEMIES_COUNTER)
         {
            //TODO: This needs to be implemented
            int CaptionEdge = BufferHeight - EnemyCaptionCounter - 1;
            CharInfo->Char.AsciiChar = EnemyCaption[j-CaptionEdge].Character;
            CharInfo->Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
               BACKGROUND_INTENSITY;
         }
      }
   }
}

void
MakeMove(World *WorldBuffer, uint BufferHeight, Tank *T, COORD OldBodyPosition,
         COORD OldMuzzlePosition, COORD NewMuzzlePosition, Direction NewTankDirection) 
{
      if(IsEmptyCell(WorldBuffer, BufferHeight, NewMuzzlePosition.X, NewMuzzlePosition.Y))
      {
         T->MuzzlePosition = NewMuzzlePosition;
         T->TankDirection = NewTankDirection;

         WorldBuffer[OldMuzzlePosition.X*BufferHeight+OldMuzzlePosition.Y].Type = EMPTY;
         WorldBuffer[OldBodyPosition.X*BufferHeight+OldBodyPosition.Y].Type = EMPTY;

         if(NewTankDirection == LEFT)
         {
            T->BodyPosition = {NewMuzzlePosition.X, NewMuzzlePosition.Y + 1};
            WorldBuffer[T->MuzzlePosition.X*BufferHeight+T->MuzzlePosition.Y].Type = TANK_LEFT_RIGHT;
         }
         else if(NewTankDirection == RIGHT)
         {
            T->BodyPosition = {NewMuzzlePosition.X, NewMuzzlePosition.Y - 1};
            WorldBuffer[T->MuzzlePosition.X*BufferHeight+T->MuzzlePosition.Y].Type = TANK_LEFT_RIGHT;
         }
         else if(NewTankDirection == UP)
         {
            T->BodyPosition = {NewMuzzlePosition.X + 1, NewMuzzlePosition.Y};
            WorldBuffer[T->MuzzlePosition.X*BufferHeight+T->MuzzlePosition.Y].Type = TANK_UP_DOWN;
         }
         else if(NewTankDirection == DOWN)
         {
            T->BodyPosition = {NewMuzzlePosition.X - 1, NewMuzzlePosition.Y};
            WorldBuffer[T->MuzzlePosition.X*BufferHeight+T->MuzzlePosition.Y].Type = TANK_UP_DOWN;
         }

         if(T->Type == ENEMY)
         {
            WorldBuffer[T->BodyPosition.X*BufferHeight+T->BodyPosition.Y].Type = ENEMY_TANK_BODY;
         }
         else if(T->Type == PLAYER)
         {
            WorldBuffer[T->BodyPosition.X*BufferHeight+T->BodyPosition.Y].Type = PLAYER_TANK_BODY;
         }
      }
}

void
UpdateTankPosition(World *WorldBuffer, uint BufferHeight, Tank *T, Direction NewTankDirection)
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
         MakeMove(WorldBuffer, BufferHeight, T, OldBodyPosition, OldMuzzlePosition, NewMuzzlePosition, NewTankDirection);
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
         MakeMove(WorldBuffer, BufferHeight, T, OldBodyPosition, OldMuzzlePosition, NewMuzzlePosition, NewTankDirection);
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
         MakeMove(WorldBuffer, BufferHeight, T, OldBodyPosition, OldMuzzlePosition, NewMuzzlePosition, NewTankDirection);
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
         MakeMove(WorldBuffer, BufferHeight, T, OldBodyPosition, OldMuzzlePosition, NewMuzzlePosition, NewTankDirection);
      }
   }
}

void
MoveEnemieTanks(World *WorldBuffer, uint BufferHeight, Tank *TanksArray, uint NumberOfTanks, float Speed)
{
   static float TankSpeed = 0;
   TankSpeed += Speed;
   if(TankSpeed >= 1)
   {
      for(int i = 1;
          i < NumberOfTanks;
          i++)
      {
         uint Direction = rand() % 4;
         if(Direction == 0)
         {
            UpdateTankPosition(WorldBuffer, BufferHeight, &TanksArray[i], LEFT);
         }
         else if(Direction == 1)
         {
            UpdateTankPosition(WorldBuffer, BufferHeight, &TanksArray[i], RIGHT);
         }
         else if(Direction == 2)
         {
            UpdateTankPosition(WorldBuffer, BufferHeight, &TanksArray[i], UP);
         }
         else if(Direction == 3)
         {
            UpdateTankPosition(WorldBuffer, BufferHeight, &TanksArray[i], DOWN);
         }
      }
      TankSpeed = 0;
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

void CheckProjectileOnTank(World *WorldBuffer, uint BufferHeight, Tank *TanksArray, uint NumberOfTanks, Projectile P,
                           Caption *LifeCaption)
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
            if(TanksArray[i].Life > 1)
            {
               if(TanksArray[i].Type == PLAYER)
               {
                  short Index = TanksArray[i].Life-1;
                  LifeCaption[Index].Position = {0, Index};
                  LifeCaption[Index].State = DEAD;
                  WorldBuffer[LifeCaption[Index].Position.X*BufferHeight+LifeCaption[Index].Position.Y].Type = LIFE_COUNTER_GREY;
               }
               --TanksArray[i].Life;
            }
            else
            {
               if(TanksArray[i].Type == PLAYER)
               {
                  short Index = TanksArray[i].Life;
                  LifeCaption[Index].Position = {0, Index};
                  LifeCaption[Index].State = DEAD;
                  WorldBuffer[LifeCaption[Index].Position.X*BufferHeight+LifeCaption[Index].Position.Y].Type = LIFE_COUNTER_GREY;
                  TanksArray[i].State = DEAD;
                  Game = GAME_OVER; 
               }
               TanksArray[i].State = DEAD;
               WorldBuffer[TanksArray[i].MuzzlePosition.X*BufferHeight+TanksArray[i].MuzzlePosition.Y].Type = EMPTY;
               WorldBuffer[TanksArray[i].BodyPosition.X*BufferHeight+TanksArray[i].BodyPosition.Y].Type = EMPTY;
            }
         }
      }
   }
}

void
CheckProjectileOnWall(World *WorldBuffer, uint BufferHeight,
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
               WorldBuffer[WallsArray[i].Position.X*BufferHeight+WallsArray[i].Position.Y].Type = HIT_WALL;
            }
            else
            {
               WallsArray[i].State = DEAD;
               WorldBuffer[WallsArray[i].Position.X*BufferHeight+WallsArray[i].Position.Y].Type = EMPTY;
            }
         }
      }
   }
}

void
MoveProjectile(World *WorldBuffer, uint BufferHeight,
               Tank *TanksArray, uint NumberOfTanks,
               Projectile *P, COORD NewProjectilePosition, uint MaxProjectiles,
               Wall *WallsArray, uint NumberOfWalls,
               Caption *LifeCaption)
{
   WorldType Object = WorldBuffer[NewProjectilePosition.X*BufferHeight+NewProjectilePosition.Y].Type;
   COORD OldProjectilePosition = P->Position;
   P->Position = NewProjectilePosition;
   if(Object == EMPTY)
   {
      P->Fire = true;
      P->Life++;
      if(P->Shooter->Type == ENEMY)
      {
         WorldBuffer[P->Position.X*BufferHeight+P->Position.Y].Type = ENEMY_PROJECTILE;
      }
      else if(P->Shooter->Type == PLAYER)
      {
         WorldBuffer[P->Position.X*BufferHeight+P->Position.Y].Type = PLAYER_PROJECTILE;
      }
   }
   else if(Object == FIELD)
   {
      ClearProjectile(P);
   }
   else if(Object == WALL)
   {
      CheckProjectileOnWall(WorldBuffer, BufferHeight, WallsArray, NumberOfWalls, *P);
      ClearProjectile(P);
   }
   else if(Object == HIT_WALL)
   {
      CheckProjectileOnWall(WorldBuffer, BufferHeight, WallsArray, NumberOfWalls, *P);
      ClearProjectile(P);
   }
   else if(Object == CHEST)
   {
      Game = GAME_OVER;
   }
   else if(Object == TANK_LEFT_RIGHT || Object == TANK_UP_DOWN)
   {
      CheckProjectileOnTank(WorldBuffer, BufferHeight, TanksArray, NumberOfTanks, *P, LifeCaption);
      ClearProjectile(P);
   }
   else if(Object == ENEMY_TANK_BODY)
   {
      CheckProjectileOnTank(WorldBuffer, BufferHeight, TanksArray, NumberOfTanks, *P, LifeCaption);
      ClearProjectile(P);
   }
   else if(Object == PLAYER_TANK_BODY)
   {
      CheckProjectileOnTank(WorldBuffer, BufferHeight, TanksArray, NumberOfTanks, *P, LifeCaption);
      ClearProjectile(P);
   }
   else if(Object == PLAYER_MUZZLE_LEFT_RIGHT || Object == PLAYER_MUZZLE_UP_DOWN)
   {
      CheckProjectileOnTank(WorldBuffer, BufferHeight, TanksArray, NumberOfTanks, *P, LifeCaption);
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
ShootProjectile(World *WorldBuffer, uint BufferHeight, Tank *TanksArray, uint NumberOfTanks,
                Projectile *P, uint MaxProjectiles,
                Wall *WallsArray, uint NumberOfWalls,
                Caption *LifeCaption)
{
   COORD NewProjectilePosition = P->Position;
   COORD OldProjectilePosition = P->Position;
   if(P->Fire == false && P->Life < MaxProjectiles)
   {
      NewProjectilePosition = CheckNextProjectileMove(*P, NewProjectilePosition);
      MoveProjectile(WorldBuffer, BufferHeight, TanksArray, NumberOfTanks,
                     P, NewProjectilePosition, MaxProjectiles,
                     WallsArray, NumberOfWalls,
                     LifeCaption);
   }
   else if(P->Life < MaxProjectiles)
   {
      NewProjectilePosition = CheckNextProjectileMove(*P, NewProjectilePosition);
      MoveProjectile(WorldBuffer, BufferHeight, TanksArray, NumberOfTanks,
                     P, NewProjectilePosition, MaxProjectiles,
                     WallsArray, NumberOfWalls,
                     LifeCaption);
      WorldBuffer[OldProjectilePosition.X*BufferHeight+OldProjectilePosition.Y].Type = EMPTY;
      P->Life++;
   }
   else
   {
      ClearProjectile(P);
      WorldBuffer[OldProjectilePosition.X*BufferHeight+OldProjectilePosition.Y].Type = EMPTY;
   }
}

void
UpdatePlayerProjectile(World *WorldBuffer, uint BufferHeight, Tank *TanksArray, uint NumberOfTanks,
                       Projectile *P, float ProjectileSpeed, uint MaxProjectiles,
                       Wall *WallsArray, uint NumberOfWalls,
                       Caption *LifeCaption)
{
   static float PlayerProjectileSpeed = 0;
   PlayerProjectileSpeed += P->Speed;
   if(PlayerProjectileSpeed >= 1)
   {
      COORD OldProjectilePosition = P->Position;
      COORD NewProjectilePosition = P->Position;
      if(P->Fire == true && P->Life < MaxProjectiles)
      {
         NewProjectilePosition = CheckNextProjectileMove(*P, NewProjectilePosition);
         MoveProjectile(WorldBuffer, BufferHeight, TanksArray, NumberOfTanks,
                           P, NewProjectilePosition, MaxProjectiles,
                           WallsArray, NumberOfWalls,
                           LifeCaption);
         P->Life++;
         WorldBuffer[OldProjectilePosition.X*BufferHeight+OldProjectilePosition.Y].Type = EMPTY;
         if(P->Life >= MaxProjectiles)
         {
            WorldBuffer[NewProjectilePosition.X*BufferHeight+NewProjectilePosition.Y].Type = EMPTY;
         }
      }
      else
      {
         ClearProjectile(P);
      }
      PlayerProjectileSpeed = 0;
   }

}

void
UpdateEnemyProjectiles(World *WorldBuffer, uint BufferHeight, Tank *TanksArray, uint NumberOfTanks,
                       Projectile *ProjectilesArray, uint MaxProjectiles, float ProjectileSpeed,
                       Wall *WallsArray, uint NumberOfWalls,
                       Caption *LifeCaption)
{
   static float EnemyProjectileSpeed = 0;
   EnemyProjectileSpeed += ProjectileSpeed;
   if(EnemyProjectileSpeed >= 1)
   {
      for(int i = 1;
          i < NumberOfTanks;
          i++)
      {
         if(TanksArray[i].State == LIVE)
         {
            srand(time(0));
            ShootProjectile(WorldBuffer, BufferHeight, TanksArray, NumberOfTanks,
                            &ProjectilesArray[i], MaxProjectiles,
                            WallsArray, NumberOfWalls,
                            LifeCaption);
         }
         else
         {
            WorldBuffer[ProjectilesArray[i].Position.X*BufferHeight+ProjectilesArray[i].Position.Y].Type = EMPTY;
         }
      }
      EnemyProjectileSpeed = 0;
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

void
CheckOnWin(Tank *TanksArray, uint NumberOfTanks)
{
   for(int i = 1;
       i < NumberOfTanks;
       i++)
   {
      if(TanksArray[i].State == LIVE)
      {
         return;
      }
   }
   Game = WIN;
}

void
CountDeadTanks(Tank *TanksArray, uint NumberOfTanks, uint BufferHeight, Caption *EnemyCaption)
{
   int Counter = 0;
   for(int i = 1;
       i < NumberOfTanks;
       i++)
   {
      if(TanksArray[i].State == DEAD)
      {
         Counter++;
      }
   }
   EnemyCaption[15].Character = 48+(Counter/10);//NOTE: 48 is 0 in ASCII table
   EnemyCaption[16].Character = 48+(Counter%10);
}

#endif
