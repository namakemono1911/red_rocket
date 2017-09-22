/////////////////////////////////////////////////////////////////////////////
//	リザルト(result.h)
//	Author : TAKUMI UENO
////////////////////////////////////////////////////////////////////////////
#ifndef RESULT_H
#define RESULT_H

//--------------------------------------------------------------------------
//	構造体定義
//--------------------------------------------------------------------------
typedef struct
{
	float result[10];			//今までの猛者たちの記録
	char nameResult[11][10];	//今までの猛者たちの名前
}RESULT;

typedef struct
{
	float newResult;			//挑戦者の記録
	char newnameResult[10];		//挑戦者の名前
}NEWRESULT;

typedef struct
{
	float oldResult[10];		//昔の記録
}OLDRESULT;
//--------------------------------------------------------------------------
//　プロトタイプ宣言
//--------------------------------------------------------------------------
void initResult ( void );
void bubbleResult ( void );
void giveResult ( float kekka );
void nameResult ( int num, char *nameAd );
void drawResult ( int posX, int posY );

#endif