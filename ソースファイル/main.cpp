/////////////////////////////////////////////////////////////////////////////
//	メイン処理 (main.cpp)
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
#include "title.h"
#include "result.h"
#include "aida.h"

//--------------------------------------------------------------------------
//	マクロ定義
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//	構造体定義
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//　プロトタイプ宣言
//--------------------------------------------------------------------------
void init ( void );
void action ( void );
void draw ( void );
void redRocket ( void );
void result ( void );

////////////////////////////////////////////////////////////////////////////
// 関数名	: main
// 返り値	: 0
// 説明		: メインの処理
////////////////////////////////////////////////////////////////////////////
void main ( void )
{
	//関数宣言
	bool check = false;
	bool one = false;

	int CNTFPS = 0;			//FPSカウンター
	DWORD ExecLastTime = 0;
	DWORD FPSLastTime = 0;
	DWORD CurrentTime = 0;
	int CNTFrame = 0;

	DWORD FirestTime;

	//カーソルオフ
	CUROFF();


	//-------------------------------
	// タイトル画面
	//-------------------------------
	do
	{
		CurrentTime = timeGetTime();

		//初期設定
		if( one == false )
		{
			//関数初期化
			init ( );
			//BGM
			naraseBGM(0, 1);
			//現在時刻取得
			FirestTime = timeGetTime();
			one = true;
		}

		//60/1000秒で処理
		if( ( CurrentTime - ExecLastTime ) >= ( 1000 / 60 ) )
		{
			ExecLastTime = CurrentTime;

			if( check != true && (( CurrentTime - FirestTime) / 15000) % 2 == 0 )
			{
				CLS(BLACK, RED);
				drawTitle();
				check = true;
			}
			if( check != false && (( CurrentTime - FirestTime) / 15000) % 2 == 1 )
			{
				CLS(BLACK, RED);
				drawResult(25, 5);
				check = false;
			}

			if( INP(PK_ENTER) != 0 )
			{
				stopBGM(0);
				check = false;
				one = false;

				CLS(WHITE, BLACK);
				redRocket ( );
			}
			CNTFrame++;
		}
	}while( ! INP(KEY_ESC) );

	closeBGM();
}

////////////////////////////////////////////////////////////////////////////
// 関数名	: initData
// 返り値	: 
// 説明		: データの初期化
////////////////////////////////////////////////////////////////////////////
void init ( void )
{
	initSiko ( );
	initSperm ( );
	initBGM();
	initResult();
}

////////////////////////////////////////////////////////////////////////////
// 関数名	: playerAction
// 返り値	: 
// 説明		: プレイヤー
////////////////////////////////////////////////////////////////////////////
void action ( void )
{
	sikosiko ( );
}

////////////////////////////////////////////////////////////////////////////
// 関数名	: draw
// 返り値	: 
// 説明		: プレイヤーの描写
////////////////////////////////////////////////////////////////////////////
void draw ( void )
{
	drawSiko ( );
}

////////////////////////////////////////////////////////////////////////////
// 関数名	: redRocket
// 返り値	: 
// 説明		: 本編開始
////////////////////////////////////////////////////////////////////////////
void redRocket ( void )
{
	//関数宣言
	int CNTFPS = 0;			//FPSカウンター
	DWORD ExecLastTime = 0;
	DWORD FPSLastTime = 0;
	DWORD CurrentTime = 0;
	int CNTFrame = 0;

	DWORD firstSiko;		//制限時間用開始時間
	DWORD lastSiko;			//比較時間

	SPERM *sperm;			//sperm変数取得
	sperm = getSperm();

	bool one;				//1度通ったかどうか

	int len = 0;			//長さ

	//カーソルオフ
	CUROFF();

	//-------------------------------
	// 初期化
	//-------------------------------
	init ( );
	one = false;
	firstSiko = timeGetTime();	//はい、よーい始め
	lastSiko = 0;				//終わり！閉廷！

	//-------------------------------
	// チュートリアル
	//-------------------------------
	naraseBGM(1,0);				//SE
	CLS(WHITE, BLACK);
	INPCLEAR();

	do
	{
		CurrentTime = timeGetTime();

		//60/1000秒で処理
		if( ( CurrentTime - ExecLastTime ) >= ( 1000 / 60 ) )
		{
			ExecLastTime = CurrentTime;

			if( one == false )
			{
				COLOR(WHITE, BLACK);
				LOCATE(20, 11);
				printf("スペースキーを押したり押さなかったりしろ！");
				one = true;
			}

			CNTFrame++;
		}
	}while( INP(PK_SP) == 0 );

	stopBGM(1);

	//背景描写
	CLS();
	COLOR(WHITE, BLACK);
	drawBackground(2, 0, 79, 0, 3, 1, 23);

	//-------------------------------
	// エネルギーチャージ
	//-------------------------------
	firstSiko = timeGetTime();
	lastSiko = 0;
	naraseBGM(7, 1);

	do
	{
		CurrentTime = timeGetTime();
		lastSiko = timeGetTime();

		//60/1000秒で処理
		if( ( CurrentTime - ExecLastTime ) >= ( 1000 / 60 ) )
		{
			ExecLastTime = CurrentTime;

			//LOCATE(60, 1);
			//printf("%d",CNTFPS);

			//エナジーチャージ
			COLOR(WHITE, BLACK);
			draw();
			action();
			LOCATE(40, 10);
			COLOR(BLACK, WHITE);
			printf("残り時間:%2d", 10 - ( (lastSiko - firstSiko) / 1000) );

			CNTFrame++;
		}
	}while( lastSiko - firstSiko < 10000 );
	stopBGM(7);

	//-------------------------------
	// 発射角度
	//-------------------------------
	closeBGM();
	initBGM();
	CLS(WHITE, BLACK);
	INPCLEAR();

	do
	{
		CurrentTime = timeGetTime();

		//60/1000秒で処理
		if( ( CurrentTime - ExecLastTime ) >= ( 1000 / 60 ) )
		{
			ExecLastTime = CurrentTime;

			//発射角度
			angle ( );
			drawAngle ( );

			CNTFrame++;
		}
	}while( INP(PK_ENTER) == 0 );
	
	//-------------------------------
	// 4秒の間
	//-------------------------------
	firstSiko = timeGetTime();
	lastSiko = 0;
	naraseBGM(6, 0);
	WAIT(4000);

	/*
	do
	{
		CurrentTime = timeGetTime();
		lastSiko = timeGetTime();

		//60/1000秒で処理
		if( ( CurrentTime - ExecLastTime ) >= ( 1000 / 60 ) )
		{
			ExecLastTime = CurrentTime;

			updataAida(len);
			drawAida();
			
			CNTFrame++;
			len++;
		}
	}while( lastSiko - firstSiko < 1000 );*/

	stopBGM(6);
	CLS(WHITE, BLACK);
	INPCLEAR();

	//-------------------------------
	// 射精
	//-------------------------------
	lineSperm();
	naraseBGM(2, 0);

	do
	{
		CurrentTime = timeGetTime();

		//60/1000秒で処理
		if( ( CurrentTime - ExecLastTime ) >= ( 1000 / 120 ) )
		{
			ExecLastTime = CurrentTime;
		
			updataSperm();
			drawSperm();

			CNTFrame++;
		}
	}while( ((int)sperm->virtualY * -1) + 20 > 0 );
	stopBGM(2);
	naraseBGM(3, 0);

	//エンター押し街
	INPCLEAR();
	do
	{
		CurrentTime = timeGetTime();

		//60/1000秒で処理
		if( ( CurrentTime - ExecLastTime ) >= ( 1000 / 60 ) )
		{
			ExecLastTime = CurrentTime;

			CNTFrame++;
		}
	}while( INP(PK_ENTER) == 0 );

	stopBGM(3);

	//-------------------------------
	// リザルト
	//-------------------------------
	//一旦BGMを初期化
	closeBGM();
	initBGM();

	result();
	CUROFF();

	//エンター押し町
	INPCLEAR();
	do
	{
		CurrentTime = timeGetTime();

		//60/1000秒で処理
		if( ( CurrentTime - ExecLastTime ) >= ( 1000 / 60 ) )
		{
			ExecLastTime = CurrentTime;

			CNTFrame++;
		}
	}while( INP(PK_ENTER) == 0 );

	closeBGM();
	WAIT(500);
}

///////////////////////////////////////////////////////////////////////////
// 変数名	: result
// 返り値	: 
// 説明		: リザルトの一連の流れ
////////////////////////////////////////////////////////////////////////////
void result ( void )
{
	//変数宣言
	SPERM *sperm;
	sperm = getSperm();

	//giveResult(sperm->virtualX);
	bubbleResult();
	drawResult(25, 5);
}