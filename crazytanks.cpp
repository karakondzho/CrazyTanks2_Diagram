#include <stdio.h>
#include "Functions.cpp"


int main()
{
   HANDLE ConsoleInHandle = 0;
   HANDLE ConsoleOutHandle = 0;

   if(!InitializeConsole(&ConsoleInHandle, &ConsoleOutHandle))
   {
      printf("Console initialization error. Error code: %d\n", GetLastError());
      getchar();
      return 1;
   }

   const char* ConsoleTitle = "Crazy Tanks";
   SetConsoleTitle(ConsoleTitle);

   if(!ConsoleInHandle || !ConsoleOutHandle)
   {
      printf("Handles are not created. Error: %d\n", GetLastError());
      return(1);
   }

   //Buffer size
   const ushort BufferWidth = 35;
   const ushort BufferHeight = 70;

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
                                             0,
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
   uint InputBufferSize = 128;
   ulong InputBufferEvents;

   const uint NumberOfTanks = 15; //NOTE: This number includes player tank
   Tank TanksArray[NumberOfTanks] = {};
   Tank *PlayerTank = &TanksArray[0];
   
   Projectile ProjectilesArray[NumberOfTanks] = {};
   Projectile *PlayerProjectile = &ProjectilesArray[0];
   float ProjectileSpeed = 0.008f;
   uint MaxProjectiles = 15;

   World WorldBuffer[BufferWidth*BufferHeight] = {};

   InitializeWorld(WorldBuffer, BufferWidth, BufferHeight, TanksArray, ProjectilesArray,
                   NumberOfTanks, ProjectileSpeed);

   KEY_EVENT_RECORD KeyEvent = {};

   bool Out = false;
   float TankSpeed = 0.0008f;

   while(!Out)
   {
      bool ReadFromConsoleInput = ReadConsoleInput(ConsoleInHandle,
                                                   &InputBuffer,
                                                   InputBufferSize,
                                                   &InputBufferEvents);

      for(ulong i = 0;
          i < InputBufferEvents;
          i++)
      {
         if(InputBuffer.EventType == KEY_EVENT)
         {
            KeyEvent = InputBuffer.Event.KeyEvent;
            if(KeyEvent.bKeyDown)
            {
               switch(KeyEvent.wVirtualKeyCode)
               {
                  case VK_ESCAPE:
                     {
                        Out = true;
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
                        ShootProjectile(WorldBuffer, BufferHeight, TanksArray, NumberOfTanks,
                                        PlayerProjectile, MaxProjectiles);
                     }break;

                  default:
                     {
                     }break;

               }
            }
         }
      }

      MoveEnemieTanks(WorldBuffer, BufferHeight, TanksArray, NumberOfTanks, TankSpeed);
      UpdateEnemyProjectiles(WorldBuffer, BufferHeight, TanksArray, NumberOfTanks,
                             ProjectilesArray, MaxProjectiles, ProjectileSpeed);

      UpdatePlayerProjectile(WorldBuffer, BufferHeight, TanksArray, NumberOfTanks,
                             PlayerProjectile, ProjectileSpeed, MaxProjectiles);
      DrawCharactersToBuffer(WorldBuffer, BufferWidth, BufferHeight, BufferOfCharacters);


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

