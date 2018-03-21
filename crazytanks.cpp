#include <stdio.h>
#include "characters.cpp"
#include "Functions.cpp"

int main()
{
   HANDLE ConsoleInHandle = 0;
   HANDLE ConsoleOutHandle = 0;

   if(!InitializeConsole(&ConsoleInHandle, &ConsoleOutHandle))
   {
      return 1;
   }

   const char* ConsoleTitle = "Crazy Tanks";
   SetConsoleTitle(ConsoleTitle);

   if(!ConsoleInHandle || !ConsoleOutHandle)
   {
      return(1);
   }

   SMALL_RECT WriteRegion = {};
   COORD BufferOfCharacterSize = {}; 
   COORD BufferOfCharacterCoord = {};

   WriteRegion.Left = 0;
   WriteRegion.Top = 0;
   WriteRegion.Right = BufferHeight - 1;
   WriteRegion.Bottom = BufferWidth - 1;

   SetConsoleWindowInfo(ConsoleOutHandle, TRUE, &WriteRegion);
   SetConsoleScreenBufferSize(ConsoleOutHandle, BufferOfCharacterSize);
   
   BufferOfCharacterSize.X = BufferHeight;
   BufferOfCharacterSize.Y = BufferWidth;

   BufferOfCharacterCoord.X = 0;
   BufferOfCharacterCoord.Y = 0;

   CHAR_INFO BufferOfCharacters[BufferWidth*BufferHeight] = {};

   ConsoleOutHandle = CreateConsoleScreenBuffer(GENERIC_READ|GENERIC_WRITE,
                                                FILE_SHARE_READ | FILE_SHARE_WRITE,
                                                0,
                                                CONSOLE_TEXTMODE_BUFFER,
                                                0);
   
   if(ConsoleOutHandle == INVALID_HANDLE_VALUE)
   {
      printf("CreateConsoleScreenBuffer failed. Error: %d\n", GetLastError());
      return(1);
   }

   if(!SetConsoleActiveScreenBuffer(ConsoleOutHandle))
   {
      printf("SetConsoleActiveScreenBuffer failed. Error: %d\n", GetLastError());
      return(1);
   }

   CONSOLE_CURSOR_INFO CursorInfo = {};
   CursorInfo.dwSize = 1;
   CursorInfo.bVisible = false;

   SetConsoleCursorInfo(ConsoleOutHandle, &CursorInfo);

      
   INPUT_RECORD InputBuffer = {};
   const int InputBufferSize = 200;
   ulong InputBufferEvents = 0;

   const uint NumberOfWalls = 50;
   const uint WallStrength = 2;
   Wall WallsArray[NumberOfWalls] = {};

   const uint NumberOfTanks = 15; //NOTE: This number includes player tank and GoldTank
   Tank TanksArray[NumberOfTanks] = {};
   Tank *PlayerTank = &TanksArray[0];
   Tank *GoldTank = &TanksArray[1];
   
   Projectile ProjectilesArray[NumberOfTanks] = {};
   Projectile *PlayerProjectile = &ProjectilesArray[0];
   float ProjectileSpeed = 0.008f;
   uint MaxProjectiles = 15;

   World WorldBuffer[BufferWidth*BufferHeight] = {};
   Chest GoldChest = {};

   InitializeWorld(WorldBuffer, BufferWidth, BufferHeight,
                   TanksArray, NumberOfTanks,
                   ProjectilesArray, ProjectileSpeed,
                   &GoldChest,
                   WallsArray, NumberOfWalls, WallStrength);

   bool Out = false;
   float TankSpeed = 0.003f;


   while(Game != EXIT)
   {
      OutputDebugStringA("Running game");

      if(Game == RUNNING)
      {
         ushort Key = ReadFromConsole(ConsoleInHandle,
                                      &InputBuffer,
                                      InputBufferSize,
                                      &InputBufferEvents);

         switch(Key)
         {
            case VK_ESCAPE:
               {
                  Game = EXIT;
               }break;
            case VK_LEFT:
               {
                  UpdateTankPosition(WorldBuffer, BufferHeight, PlayerTank, LEFT);
               }break;

            case VK_RIGHT:
               {
                  UpdateTankPosition(WorldBuffer, BufferHeight, PlayerTank, RIGHT);
               }break;

            case VK_UP:
               {
                  UpdateTankPosition(WorldBuffer, BufferHeight, PlayerTank, UP);
               }break;

            case VK_DOWN:
               {
                  UpdateTankPosition(WorldBuffer, BufferHeight, PlayerTank, DOWN);
               }break;

            case VK_SPACE:
               {
                  if(PlayerProjectile->Shooter->State == LIVE)
                  {
                     ShootProjectile(WorldBuffer, BufferHeight, TanksArray, NumberOfTanks,
                                     PlayerProjectile, MaxProjectiles,
                                     WallsArray, NumberOfWalls);
                  }
               }break;

            default:
               {
               }break;

         }

         MoveEnemieTanks(WorldBuffer, BufferHeight, TanksArray, NumberOfTanks, TankSpeed);
         UpdateEnemyProjectiles(WorldBuffer, BufferHeight, TanksArray, NumberOfTanks,
                                ProjectilesArray, MaxProjectiles, ProjectileSpeed,
                                WallsArray, NumberOfWalls);

         UpdatePlayerProjectile(WorldBuffer, BufferHeight, TanksArray, NumberOfTanks,
                                PlayerProjectile, ProjectileSpeed, MaxProjectiles,
                                WallsArray, NumberOfWalls);
         DrawCharactersToBuffer(WorldBuffer, BufferWidth, BufferHeight, BufferOfCharacters);


      }
      else if(Game == GAME_OVER)
      {
         InitializeGameOver();
         for(int i = 0;
             i < BufferWidth;
             i++)
         {
            for(int j = 0;
                j < BufferHeight;
                j++)
            {
               BufferOfCharacters[i*BufferHeight+j].Char.AsciiChar = GameOverCharacters[i*BufferHeight+j].Char.AsciiChar;
               BufferOfCharacters[i*BufferHeight+j].Attributes = GameOverCharacters[i*BufferHeight+j].Attributes;
            }
         }
         ushort Key = ReadFromConsole(ConsoleInHandle,
                                      &InputBuffer,
                                      InputBufferSize,
                                      &InputBufferEvents);

         switch(Key)
         {
            case VK_ESCAPE:
               {
                  Game = EXIT;
               }break;
            case 0x52:
               {
                  TanksArray[NumberOfTanks] = {};
                  InitializeWorld(WorldBuffer, BufferWidth, BufferHeight,
                                  TanksArray, NumberOfTanks,
                                  ProjectilesArray, ProjectileSpeed,
                                  &GoldChest,
                                  WallsArray, NumberOfWalls, WallStrength);
                  UpdateTankPosition(WorldBuffer, BufferHeight, PlayerTank, UP);
                  Game = RUNNING;
               }break;
            default:
               {
               }break;
         }
      }

      bool WriteToConsoleResult = WriteConsoleOutput(ConsoleOutHandle,
                                                     BufferOfCharacters,
                                                     BufferOfCharacterSize,
                                                     BufferOfCharacterCoord,
                                                     &WriteRegion);
      if(!WriteToConsoleResult)
      {
         printf("WriteConsoleOutput failed. Error: %d\n", GetLastError());
         return(1);
      }

      SetConsoleActiveScreenBuffer(ConsoleOutHandle);
   }

   return(0);
}
