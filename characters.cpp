#include <Windows.h>

const int BufferWidth = 35;
const int BufferHeight = 70;
CHAR_INFO GameOverCharacters[BufferWidth*BufferHeight] = {};

void
InitializeGameOver()
{
//G
   GameOverCharacters[4*BufferHeight+15].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[4*BufferHeight+14].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[4*BufferHeight+13].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[4*BufferHeight+12].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[4*BufferHeight+11].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[5*BufferHeight+11].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+11].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[7*BufferHeight+11].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[8*BufferHeight+11].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+11].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[10*BufferHeight+11].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[11*BufferHeight+11].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+11].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+12].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+13].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+14].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+15].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[11*BufferHeight+15].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[11*BufferHeight+14].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[10*BufferHeight+15].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+15].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+14].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+13].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//a
   GameOverCharacters[12*BufferHeight+17].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[11*BufferHeight+17].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[10*BufferHeight+17].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+17].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[8*BufferHeight+17].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[10*BufferHeight+18].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[7*BufferHeight+18].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[10*BufferHeight+19].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+19].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[10*BufferHeight+20].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[7*BufferHeight+20].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+21].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[11*BufferHeight+21].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[10*BufferHeight+21].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+21].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[8*BufferHeight+21].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//m
   GameOverCharacters[12*BufferHeight+23].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[11*BufferHeight+23].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[10*BufferHeight+23].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+23].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[8*BufferHeight+23].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[7*BufferHeight+23].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+23].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[8*BufferHeight+24].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+25].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[8*BufferHeight+26].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+27].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[11*BufferHeight+27].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[10*BufferHeight+27].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+27].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[8*BufferHeight+27].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[7*BufferHeight+27].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+27].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//e
   GameOverCharacters[12*BufferHeight+33].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+32].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+31].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+30].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+29].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[11*BufferHeight+29].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[10*BufferHeight+29].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+29].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[8*BufferHeight+29].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[7*BufferHeight+29].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+29].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+30].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+31].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+32].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+33].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+30].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+31].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+32].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+33].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//O
   GameOverCharacters[4*BufferHeight+37].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[5*BufferHeight+37].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+37].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[7*BufferHeight+37].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[8*BufferHeight+37].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+37].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[10*BufferHeight+37].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[11*BufferHeight+37].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+37].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[4*BufferHeight+38].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[4*BufferHeight+39].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[4*BufferHeight+40].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[4*BufferHeight+41].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[5*BufferHeight+41].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+41].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[7*BufferHeight+41].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[8*BufferHeight+41].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+41].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[10*BufferHeight+41].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[11*BufferHeight+41].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+41].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+38].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+39].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+40].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

//v   
   GameOverCharacters[6*BufferHeight+43].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[7*BufferHeight+43].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[8*BufferHeight+43].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+43].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[10*BufferHeight+43].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[11*BufferHeight+44].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+45].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[11*BufferHeight+46].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[10*BufferHeight+47].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+47].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[8*BufferHeight+47].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[7*BufferHeight+47].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+47].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//e
   GameOverCharacters[6*BufferHeight+49].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[7*BufferHeight+49].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[8*BufferHeight+49].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+49].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[10*BufferHeight+49].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[11*BufferHeight+49].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+49].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+50].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+51].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+52].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+53].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+50].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+51].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+52].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+53].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+50].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+51].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+52].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+53].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//r
   GameOverCharacters[12*BufferHeight+55].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[11*BufferHeight+55].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[10*BufferHeight+55].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+55].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[8*BufferHeight+55].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[7*BufferHeight+55].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+55].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+56].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+57].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+58].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[6*BufferHeight+59].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[8*BufferHeight+58].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+57].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[9*BufferHeight+56].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[10*BufferHeight+58].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[11*BufferHeight+59].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[12*BufferHeight+59].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[7*BufferHeight+59].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;





//E
   GameOverCharacters[18*BufferHeight+22].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[18*BufferHeight+21].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[18*BufferHeight+20].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[19*BufferHeight+20].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[20*BufferHeight+20].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[21*BufferHeight+20].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[22*BufferHeight+20].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[22*BufferHeight+21].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[22*BufferHeight+22].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[20*BufferHeight+21].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[20*BufferHeight+22].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//s
   GameOverCharacters[18*BufferHeight+26].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[18*BufferHeight+25].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[18*BufferHeight+24].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[19*BufferHeight+24].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[20*BufferHeight+24].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[20*BufferHeight+25].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[20*BufferHeight+26].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[21*BufferHeight+26].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[22*BufferHeight+26].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[22*BufferHeight+25].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[22*BufferHeight+24].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//C
   GameOverCharacters[18*BufferHeight+30].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[18*BufferHeight+29].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[18*BufferHeight+28].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[19*BufferHeight+28].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[20*BufferHeight+28].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[21*BufferHeight+28].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[22*BufferHeight+28].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[22*BufferHeight+29].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[22*BufferHeight+30].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//-
   GameOverCharacters[20*BufferHeight+34].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[20*BufferHeight+35].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[20*BufferHeight+36].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//E
   GameOverCharacters[18*BufferHeight+41].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[18*BufferHeight+40].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[18*BufferHeight+39].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[19*BufferHeight+39].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[20*BufferHeight+39].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[21*BufferHeight+39].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[22*BufferHeight+39].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[22*BufferHeight+40].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[22*BufferHeight+41].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[20*BufferHeight+40].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[20*BufferHeight+41].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//X
   GameOverCharacters[18*BufferHeight+43].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[19*BufferHeight+43].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[20*BufferHeight+44].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[21*BufferHeight+43].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[22*BufferHeight+43].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[18*BufferHeight+45].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[19*BufferHeight+45].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[45*BufferHeight+20].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[45*BufferHeight+22].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[21*BufferHeight+45].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[22*BufferHeight+45].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//I
   GameOverCharacters[18*BufferHeight+47].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[19*BufferHeight+47].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[20*BufferHeight+47].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[21*BufferHeight+47].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[22*BufferHeight+47].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//T
   GameOverCharacters[18*BufferHeight+49].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[18*BufferHeight+50].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[18*BufferHeight+51].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[19*BufferHeight+50].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[20*BufferHeight+50].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[21*BufferHeight+50].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[22*BufferHeight+50].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;


//R
   GameOverCharacters[25*BufferHeight+20].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[26*BufferHeight+20].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+20].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[28*BufferHeight+20].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[29*BufferHeight+20].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[25*BufferHeight+21].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[25*BufferHeight+22].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[26*BufferHeight+22].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+21].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[28*BufferHeight+22].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[29*BufferHeight+22].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//-
   GameOverCharacters[27*BufferHeight+27].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+26].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+25].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//R
   GameOverCharacters[25*BufferHeight+29].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[26*BufferHeight+29].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+29].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[28*BufferHeight+29].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[29*BufferHeight+29].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[25*BufferHeight+30].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[25*BufferHeight+31].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[26*BufferHeight+31].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+30].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[28*BufferHeight+31].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[29*BufferHeight+31].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//E
   GameOverCharacters[25*BufferHeight+33].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[26*BufferHeight+33].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+33].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[28*BufferHeight+33].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[29*BufferHeight+33].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[25*BufferHeight+34].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[25*BufferHeight+35].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+34].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+35].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[29*BufferHeight+34].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[29*BufferHeight+35].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//S
   GameOverCharacters[25*BufferHeight+39].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[25*BufferHeight+38].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[25*BufferHeight+37].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[26*BufferHeight+37].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+37].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+39].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[28*BufferHeight+39].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[29*BufferHeight+39].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[29*BufferHeight+38].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[29*BufferHeight+37].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+38].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//T
   GameOverCharacters[25*BufferHeight+41].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[25*BufferHeight+42].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[25*BufferHeight+43].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[26*BufferHeight+42].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+42].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[28*BufferHeight+42].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[29*BufferHeight+42].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//A
   GameOverCharacters[26*BufferHeight+45].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+45].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[28*BufferHeight+45].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[29*BufferHeight+45].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+46].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[26*BufferHeight+47].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[28*BufferHeight+47].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[29*BufferHeight+47].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[25*BufferHeight+46].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+47].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//R
   GameOverCharacters[25*BufferHeight+49].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[26*BufferHeight+49].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+49].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[28*BufferHeight+49].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[29*BufferHeight+49].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[25*BufferHeight+50].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[25*BufferHeight+51].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[26*BufferHeight+51].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+50].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[28*BufferHeight+51].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[29*BufferHeight+51].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//T
   GameOverCharacters[25*BufferHeight+53].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[25*BufferHeight+54].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[25*BufferHeight+55].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[26*BufferHeight+54].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[27*BufferHeight+54].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[28*BufferHeight+54].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
   GameOverCharacters[29*BufferHeight+54].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
}
