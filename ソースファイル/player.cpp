/////////////////////////////////////////////////////////////////////////////
//	プレイヤーの動きの処理 (player.cpp)
//	Author : TAKUMI UENO
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
//	インクルードファイル
//--------------------------------------------------------------------------
#include "main.h"
#include "player.h"
#include "sperm.h"
#include "redrocketField.h"
#include "BGM.h"
#include <math.h>

//--------------------------------------------------------------------------
//	構造体定義
//--------------------------------------------------------------------------
PLAYER player;

//--------------------------------------------------------------------------
//　プロトタイプ宣言
//--------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
// 関数名	: initShiko
// 返り値	: 0
// 説明		: 関数初期化
////////////////////////////////////////////////////////////////////////////
void initSiko ( void )
{
	//関数宣言
	int loop;		//for文の制御

	//-------------------------------
	// PLAYERの初期化
	//-------------------------------
	player.excit = 0;
	player.hand = up;
	player.oldHand = down;
	player.lastDeg = 275;
	player.startDeg = 185;
	player.angle = 0;

	for( loop = 0; loop < 21; loop++ )
	{
		player.lastX[loop] = 0;
		player.lastY[loop] = 0;
		player.oldLastX[loop] = 0;
		player.oldLastY[loop] = 0;
	}
	player.rightAngle = true;
}

////////////////////////////////////////////////////////////////////////////
// 関数名	: sikosiko
// 返り値	: 0
// 説明		: シコり続けるのだ・・・
////////////////////////////////////////////////////////////////////////////
void sikosiko ( void )
{
	//関数宣言

	//-------------------------------
	// シコリ続ける処理
	//-------------------------------
	//常に興奮はマイナス
	player.excit += 0.35;
	if ( player.excit >= 0 )
	{
		player.excit = 0;
	}
	
	//手の位置が前回と違った場合
	if( player.hand != player.oldHand )
	{
		stopBGM(5);
		naraseBGM(5, 0);
		player.excit -= 2;
	}

	//手の位置更新
	player.oldHand = player.hand;

	//手の描写位置
	if( INP(PK_SP) != 0 )
	{
		player.hand = down;
	}
	else
	{
		player.hand = up;
	}

}

////////////////////////////////////////////////////////////////////////////
// 関数名	: drawSiko
// 返り値	: 0
// 説明		: シコり続けるのだ・・・
////////////////////////////////////////////////////////////////////////////
void drawSiko ( void )
{
	//関数宣言
	int x,y;		//AAのX,Y
	char dick[2][18][10] =	//dick
	{
		{
			"■■■",
			"■■■",
			"■■■",
		},
		
		{
			"■■■",
			"■■■",
			"■■■",
			"■■■",
			"■■■",
			"■■■",
			"■■■",
			"■■■",
			"■■■",
			"■■■",
			"■■■",
			"■■■",
			"■■■",
			"■■■",
			"■■■",
			"■■■",
			"■■■",
			"■■■",
		},
	};

	char hand[11][21] =	//hand
	{
		" 　 　........... ",
		"  　::::         :",
		"  :::::::........ ",
		"::::::::         :",
		":::::::::........ ",
		"::::::::         :",
		":::::::::........ ",
		":::::::: 　 　   :",
		":::::::::........ ",
		"::::::::",
		":::::::",
	};

	//LOCATE(1,1);
	//printf("%f",player.excit);

	//スペースが押されていなかった場合
	if( player.hand == up && player.hand != player.oldHand)
	{
		//手のを背景で上書き
		/*
		COLOR(WHITE, BLACK);
		drawBackground(1, 0, 21, 11, 11, 1, 12);
		*/
		for( y = 0; y < 11; y++ )
		{
			LOCATE(1, 12 + y);
			for( x = 0; x < 21; x++ )
			{
				printf(" ");
			}
		}

		//dick生成
		COLOR(RED, BLACK);
		for( y = 0; y < 3; y++ )
		{
			LOCATE(10, 2 + y);
			for( x = 0; x < 6; x++);
			{
				printf("%c",dick[0][y][x]);
			}
		}
		for( y = 0; y < 18; y++ )
		{
			LOCATE(10, 5 + y);
			for( x = 0; x < 6; x++)
			{
				printf("%c",dick[1][y][x]);
			}
		}

		COLOR(WHITE, BLACK);
		//手の生成
		for( y = 0; y < 11; y++ )
		{
			LOCATE(1, 1 + y);
			for( x = 0; x < 18; x++ )
			{
				printf("%c",hand[y][x]);

				if( y == 9 && x == 8 )
				{
					x = 22;
				}

				if( y == 10 && x == 7 )
				{
					x = 22;
				}
			}
		}
	}

	//スペースが押されていた場合
	if( player.hand == down && player.hand != player.oldHand )
	{
		//手の削除
		/*
		COLOR(WHITE, BLACK);
		drawBackground(1, 0, 21, 0, 11, 1, 1);for( y = 0; y < 11; y++ )
		*/
		for( y = 0; y < 11; y++ )
		{
			LOCATE(1, 1 + y);
			for( x = 0; x < 21; x++ )
			{
				printf(" ");
			}
		}

		//dick修正
		if( player.excit > -45 )
		{
			COLOR(RED, BLACK);
		}

		if( player.excit < -45 )
		{
			COLOR(H_MAGENTA, BLACK);
		}

		if( player.excit < -100 )
		{
			COLOR(L_MAGENTA, BLACK);
		}

		for( y = 0; y < 3; y++ )
		{
			LOCATE(10, 2 + y);
			for( x = 0; x < 6; x++ )
			{
				printf("%c",dick[0][y][x]);
			}
		}

		COLOR(RED, BLACK);
		for( y = 0; y < 8; y++ )
		{
			LOCATE(10, 5 + y);
			for( x = 0; x < 6; x++)
			{
				printf("%c",dick[1][y][x]);
			}
		}
		
		COLOR(WHITE, BLACK);
		//手の生成
		for( y = 0; y < 11; y++ )
		{
			LOCATE(1, 12 + y);
			for( x = 0; x < 18; x++ )
			{
				printf("%c",hand[y][x]);

				if( y == 9 && x == 8 )
				{
					x = 22;
				}

				if( y == 10 && x == 7 )
				{
					x = 22;
				}
			}
		}
	}

}

////////////////////////////////////////////////////////////////////////////
// 関数名	: angle
// 返り値	: 0
// 説明		: 発射角度計算
////////////////////////////////////////////////////////////////////////////
void angle ( void )
{
	//関数宣言
	double lastRad;		//終わりのθ
	double startRad;	//始まりのθ
	int loop;
	SPERM *sperm;		//sperm構造体のアドレス取得

	sperm = getSperm();

	if(player.rightAngle == false)
	{
		player.lastDeg += 4;
		player.startDeg += 4;

		if( player.lastDeg > 355 )
		{
			player.rightAngle = true;
		}
	}
	else
	{
		player.lastDeg -= 4;
		player.startDeg -= 4;

		if( player.lastDeg < 275 )
		{
			player.rightAngle = false;
		}
	}

	//θ計算
	lastRad = ( player.lastDeg * PI ) / 180;
	startRad = ( player.startDeg * PI ) /180;

	//始点座標算出
	for( loop = 0; loop < 3; loop++ )
	{
		player.oldStartX[loop] = player.startX[loop];
		player.oldStartY[loop] = player.startY[loop];

		player.startX[loop] = (loop * cos( startRad )) * 2.5;
		player.startY[loop] = loop * sin( startRad ) * 1.5;
	}

	//終点座標算出
	for(loop = 0; loop < 21; loop++ )
	{
		player.oldLastX[loop] = player.lastX[loop];
		player.oldLastY[loop] = player.lastY[loop];

		player.lastX[loop] = (loop * cos( lastRad )) * 2;
		player.lastY[loop] = loop * sin( lastRad );
	}

	//X,Y方向に伝わる力の割合
	sperm->moveY = -1 * ( sin( lastRad ) );
	sperm->moveX = cos( lastRad );
}

////////////////////////////////////////////////////////////////////////////
// 関数名	: drawAngle
// 返り値	: 0
// 説明		: 角度描写
////////////////////////////////////////////////////////////////////////////
void drawAngle ( void )
{
	//関数宣言
	int loop;
	int width;
	
	int startX[3];
	int startY[3];

	int oldStartX[3];
	int oldStartY[3];

	//描写
	COLOR(YELLOW);
	for( loop = 0; loop < 3; loop++ )
	{
		startX[loop] = 10 + (int)player.startX[loop];
		startY[loop] = 22 + (int)player.startY[loop];

		oldStartX[loop] = 10 + (int)player.oldStartX[loop];
		oldStartY[loop] = 22 + (int)player.oldStartY[loop];
	}

	COLOR(RED, YELLOW);
	LOCATE(50, 3);
	printf("Enterで発射！");

	//前回のナニ削除
	COLOR(BLACK, BLACK);
	for( width = 0; width < 3; width++ )
	{
		for( loop = 0; loop < 21; loop++ )
		{
			LOCATE(oldStartX[width] + (int)player.oldLastX[loop], oldStartY[width] + (int)player.oldLastY[loop]);
			if( player.oldLastX != player.lastX && player.oldLastY != player.lastY )
			{
				printf("  ");
			}
		}
	}

	//ナニ描画
	COLOR(RED, RED);
	for( width = 0; width < 3; width++ )
	{
		for( loop = 0; loop < 21; loop++ )
		{	
			if( (int)player.lastX[loop - 1] + 1 < (int)player.lastX[loop]
				|| player.lastY[loop - 1] != player.lastY[loop])
			{
				LOCATE(startX[width] + (int)player.lastX[loop], startY[width] + (int)player.lastY[loop]);
				printf("■");
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// 変数名	: uninitSiko
// 返り値	: 
// 説明		: 終了処理
////////////////////////////////////////////////////////////////////////////
void uninitSiko ( void )
{

}

/////////////////////////////////////////////////////////////////////////////
// 変数名	: getPlayer
// 返り値	: &player
// 説明		: player構造体の先頭アドレスをあげるわあなたに
////////////////////////////////////////////////////////////////////////////
PLAYER *getPlayer ( void )
{
	return &player;
}