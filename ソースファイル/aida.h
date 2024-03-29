/////////////////////////////////////////////////////////////////////////////
//	幕間 (aida.h)
//	Author : TAKUMI UENO
////////////////////////////////////////////////////////////////////////////
#ifndef AIDA_H
#define AIDA_H

//--------------------------------------------------------------------------
// 構造体定義
//--------------------------------------------------------------------------
typedef struct
{
	float posX;
	float posY;
}AIDA;

//--------------------------------------------------------------------------
// プロトタイプ宣言
//--------------------------------------------------------------------------
void initAida ( void );
void updataAida ( int len );
void drawAida ( void );

#endif