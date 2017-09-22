/////////////////////////////////////////////////////////////////////////////
//	発射された弾頭の処理 (sperm.h)
//	Author : TAKUMI UENO
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
//	インクルードファイル
//--------------------------------------------------------------------------
#include "player.h"
#include "main.h"
#include "sperm.h"
#include "redrocketField.h"
#include "BGM.h"
#include <math.h>

//--------------------------------------------------------------------------
//	構造体定義
//--------------------------------------------------------------------------
SPERM sperm;

////////////////////////////////////////////////////////////////////////////
// 変数名	: initSperm
// 返り値	: 
// 説明		: 変数の初期化
////////////////////////////////////////////////////////////////////////////
void initSperm ( void )
{
	sperm.moveX = 0;
	sperm.moveY = 0;
	sperm.posX = 0;
	sperm.posY = 0;
	sperm.oldVirtualX = 0;
	sperm.oldVirtualY = 0;
	sperm.virtualX = 0;
	sperm.virtualY = 0;
	sperm.sperm = false;
	sperm.oldSperm = false;
	sperm.bgm = false;
}

////////////////////////////////////////////////////////////////////////////
// 変数名	: lineSperm
// 返り値	: 
// 説明		: 直線の方程式算出
////////////////////////////////////////////////////////////////////////////
void lineSperm ( void )
{
	//変数宣言
	float startX;
	float startY;
	
	float lastX;
	float lastY;
	
	float katamuki;

	PLAYER *player;

	player = getPlayer();
	
	//-------------------------------
	// X,Y方向のベクトル計算
	//-------------------------------
	sperm.moveX *= ( player->excit * -1 );
	player->excit *= sperm.moveY;
}

////////////////////////////////////////////////////////////////////////////
// 変数名	: updataSperm
// 返り値	: 
// 説明		: Spermの更新処理
////////////////////////////////////////////////////////////////////////////
void updataSperm ( void )
{
	//変数宣言
	PLAYER *player;

	player = getPlayer();

	//-------------------------------
	//重力処理
	//-------------------------------
	player->oldExcit = player->excit;
	player->excit += G;

	//-------------------------------
	//仮想座標更新
	//-------------------------------
	sperm.oldVirtualX = sperm.virtualX;
	sperm.oldVirtualY = sperm.virtualY;

	sperm.virtualY += player->lastY[21] + player->startY[1] + player->excit;
	sperm.virtualX += sperm.moveX;

	//-------------------------------
	//地面に着地したら
	//-------------------------------
	if( sperm.virtualY >= 19 )
	{
		sperm.moveX = 0;
		sperm.moveY = 0;
		sperm.virtualY = 20;
	}

	//-------------------------------
	// 前回描写したかを更新
	//-------------------------------
	sperm.oldSperm = sperm.sperm;
}

////////////////////////////////////////////////////////////////////////////
// 変数名	: drawSperm
// 返り値	: 
// 説明		: Spermの描写処理
////////////////////////////////////////////////////////////////////////////
void drawSperm ( void )
{
	//関数宣言
	int type = 1;		//背景の種類
	int startX;			//背景描写開始の位置X
	int startY;			//背景描写開始の位置Y
	int loop;			//いつもの
	PLAYER *player;

	player = getPlayer();

	//-------------------------------
	// 描写する背景ループの計算
	//-------------------------------
	//X方向
	startX = ( (int)sperm.virtualX / 2 ) % 80;

	//Y方向
	if( player->excit > 100 )
	{
		startY = ( (int)sperm.virtualY / 50 ) % 25;
	}
	else
	{
		startY = ( (int)sperm.virtualY / 10 ) % 25;
	}
	if( startY < 0 )
	{
		startY *= -1;
	}

	//-------------------------------
	//背景描写
	//-------------------------------
	for( loop = 1; loop <= 25; loop++ )
	{
		if( sperm.oldVirtualX != startX && sperm.oldVirtualY != startY )
		{
			//--------------------------------
			// 高度によって背景変更
			//--------------------------------
			//地面
			if( sperm.virtualY + loop - 11 > 20 )
			{
				type = 2;
				COLOR(WHITE, BLACK);
			}

			//空
			if( sperm.virtualY + loop - 11 > -20000 && sperm.virtualY + loop - 11 < 20 )
			{
				type = 1;
				COLOR(WHITE, BLUE);
				sperm.sperm = true;
			}

			//宇宙
			if( sperm.virtualY + loop - 11 <= -20000 )
			{
				type = 0;
				COLOR(WHITE, BLACK);
				sperm.sperm = false;
			}

			//-------------------------------
			// ロケットの部分を避けて描写
			//-------------------------------
			if( loop == 11 )
			{
				drawBackground( type, startX, 39, ( 25 - startY ) % 25 + loop, 1, 1, loop );
				drawBackground( type, startX + 41, 79 - 41, ( 25 - startY ) % 25 + loop, 1, 42, loop );

				//-------------------------------
				// ロケット描写
				//-------------------------------
				if( (int)sperm.virtualY * -1 + 20 > 0 )
				{
					//ロケットの落下速度によって変色
					if( player->excit > 100 )
					{
						if( sperm.bgm == false )
						{
							naraseBGM(10, 0);
							sperm.bgm = true;
						}

						sperm.sperm = false;
						COLOR(RED);
					}
					LOCATE( 40, 11 );
					printf("●");
				}
				//着地時
				else
				{
					LOCATE(40, 11);
					printf("..");
				}
			}
			//-------------------------------
			// 記録と高度の部分を避けて描写
			//-------------------------------
			if( loop == 20 || loop == 21 )
			{
				drawBackground( type, startX, 29, ( 25 - startY ) % 25 + loop, 1, 1, loop );
				drawBackground( type, startX + 50, 79 - 50, ( 25 - startY ) % 25 + loop, 1, 51, loop );
			}
			//それ以外は通常
			if( loop != 11 && loop != 20 && loop != 21 )
			{
				drawBackground( type, startX, 79, ( 25 - startY ) % 25 + loop, 1, 1, loop );
			}
		}
	}

	/*
	//-------------------------------
	// ロケット描写
	//-------------------------------
	//ロケットの落下速度によって変色
	if( player->excit > 100 )
	{
		sperm.sperm = false;
		COLOR(RED);
	}
	//ロケットを1度だけ描写
	if( sperm.sperm == false )
	{
		sperm.sperm = true;
		LOCATE( 40, 11 );
		printf("●");
	}
	*/
	//-------------------------------
	// 記録と高度描写
	//-------------------------------
	COLOR(WHITE, BLACK);
	LOCATE(30, 20);
	printf("高度:%14dM",( (int)sperm.virtualY) * -1 + 20 );
	LOCATE(30, 21);
	printf("記録:%14fM",sperm.virtualX);
}


////////////////////////////////////////////////////////////////////////////
// 変数名	: uninitSperm
// 返り値	: 
// 説明		: Spermの終了処理
////////////////////////////////////////////////////////////////////////////
void uninitSperm ( void )
{

}

////////////////////////////////////////////////////////////////////////////
// 変数名	: getSperm
// 返り値	: 
// 説明		: Spermの先頭アドレス
////////////////////////////////////////////////////////////////////////////
SPERM *getSperm ( void )
{
	return &sperm;
}