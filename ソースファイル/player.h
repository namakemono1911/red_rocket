/////////////////////////////////////////////////////////////////////////////
//	プレイヤーの動きの処理 (player.h)
//	Author : TAKUMI UENO
////////////////////////////////////////////////////////////////////////////
#ifndef _PLAYER_H
#define _PLAYER_H


//--------------------------------------------------------------------------
//	マクロ定義
//--------------------------------------------------------------------------
#define LENGTH (25)
#define PI (3.141592)

//--------------------------------------------------------------------------
//	構造体定義
//--------------------------------------------------------------------------
enum HAND
{
	up,					//手の状態
	down				//手の状態
};

typedef struct
{
	float excit;			//プレイヤーの興奮状態
	float oldExcit;			//前回の興奮度

	enum HAND hand;			//現在の手の位置
	enum HAND oldHand;		//一フレーム前の手の位置

	double lastDeg;			//dickの終点角度
	double startDeg;		//dickの始点角度

	int angle;				//直線の傾き

	double startX[3];		//dickの始点座標
	double startY[3];		//dickの始点座標

	double oldStartX[3];	//前回のdickの始点座標
	double oldStartY[3];	//前回のdickの始点座標

	double lastX[21];		//dickの終点座標
	double lastY[21];		//dickの終点座標

	double oldLastX[21];	//前回のdickの終点座標
	double oldLastY[21];	//前回のdickの終点座標

	bool rightAngle;		//直角かどうか
}PLAYER;

//--------------------------------------------------------------------------
//　プロトタイプ宣言
//--------------------------------------------------------------------------
void initSiko ( void );
void sikosiko ( void );
void drawSiko ( void );
void angle ( void );
void updataAngle ( void );
void drawAngle ( void );
void uninitSiko ( void );
PLAYER *getPlayer ( void );

#endif