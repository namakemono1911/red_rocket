/////////////////////////////////////////////////////////////////////////////
//	プレイヤーの動きの処理 (player.cpp)
//	Author : TAKUMI UENO
////////////////////////////////////////////////////////////////////////////
#ifndef SPERM_H
#define SPERM_H
#define PI (3.141592)
#define G (0.5)

//--------------------------------------------------------------------------
//	構造体定義
//--------------------------------------------------------------------------
typedef struct
{
	float posX;			//X座標
	float posY;			//Y座標

	float moveX;		//X方向のベクトル
	float moveY;		//Y方向のベクトル

	float oldVirtualX;	//前回の仮想X
	float oldVirtualY;	//前回の仮想Y

	float virtualX;		//仮想座標X
	float virtualY;		//仮想座標Y

	bool sperm;			//ロケットを描写したかどうか
	bool oldSperm;		//古くなったロケット
	bool bgm;			//一度だけBGMを鳴らす
}SPERM;

//--------------------------------------------------------------------------
// プロトタイプ宣言
//--------------------------------------------------------------------------
void initSperm ( void );
void lineSperm ( void );
void updataSperm ( void );
void drawSperm ( void );
void uninitSperm ( void );
SPERM *getSperm ( void );

#endif


