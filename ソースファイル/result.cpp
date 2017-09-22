/////////////////////////////////////////////////////////////////////////////
//	リザルト(result.h)
//	Author : TAKUMI UENO
////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
//	インクルードファイル
//--------------------------------------------------------------------------
#include "main.h"
#include "result.h"
#include "sperm.h"
#include "BGM.h"

//--------------------------------------------------------------------------
//	構造体定義
//--------------------------------------------------------------------------
RESULT result;
NEWRESULT newResult;
OLDRESULT oldResult;

////////////////////////////////////////////////////////////////////////////
// 関数名	: initResult
// 返り値	: 0
// 説明		: 関数初期化
////////////////////////////////////////////////////////////////////////////
void initResult ( void )
{
	//関数宣言
	int loop;
	int count;
	FILE *fp;

	fp = fopen("result.bin", "rb");
	if( fp == 0 )
	{
		for( loop = 0; loop < 10; loop++ )
		{
			result.result[loop] = 0;
			newResult.newnameResult[loop] = '-';
			for( count = 0; count < 10; count++ )
			{
				result.nameResult[loop][count] = '-';
			}
		}
		newResult.newResult = 0;
	}
	else
	{
		//過去の結果読み込み
		fread(&result, sizeof(RESULT), 1, fp);
		fclose(fp);
	}
}

////////////////////////////////////////////////////////////////////////////
// 関数名	: giveResult
// 返り値	: 0
// 説明		: 結果をresultに格納
////////////////////////////////////////////////////////////////////////////
void giveResult ( float kekka )
{
	newResult.newResult = kekka;
}

////////////////////////////////////////////////////////////////////////////
// 変数名	: nameResult
// 返り値	: 
// 説明		: 新記録者に名前を入力させる
////////////////////////////////////////////////////////////////////////////
void nameResult ( int num, char *nameAd )
{
	//変数宣言
	int check;

	//-------------------------------
	// 名前入力
	//-------------------------------
	while(1)
	{
		CURON();
		CLS(WHITE, BLACK);
		LOCATE(30, 10);
		printf("おめでとう！あなたは%2d位でした！",num + 1);
		LOCATE(30, 11);
		printf("名前を入力してください");
		LOCATE(32, 12);
		scanf("%s",nameAd);
		rewind(stdin);

		check = strlen(nameAd);

		if(check > 10)
		{
			CLS();
			LOCATE(34, 10);
			printf("名前が長すぎます。");
			rewind(stdin);
			getchar();
		}
		else
		{
			for( check; 10 - check > 0; check++ )
			{
				nameAd[check] = ' ';
			}
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////
// 関数名	: bubbleResult
// 返り値	: 0
// 説明		: バブルソート
////////////////////////////////////////////////////////////////////////////
void bubbleResult ( void )
{
	//関数宣言
	int loop;
	int chenge;				//数値入れ替え
	int name;				//名前入れ替え

	float evacuation;		//数値の避難所
	float sort[11];			//ソート用の変数

	char *resultName[11];	//名前も入れ替え
	char escName[10];		//名前の避難所

	bool rankin = false;	//ランクインしたかどうか

	SPERM *sperm;
	sperm = getSperm();
	newResult.newResult = sperm->virtualX;

	FILE *fp;

	fp = fopen("result.bin", "rb");
	if( fp == 0 )
	{
		naraseBGM(4, 0);	//やりますねぇ！
		naraseBGM(9, 1);	//土方BGM

		nameResult(0, &result.nameResult[0][0]);
		result.result[0] = newResult.newResult;

		fp = fopen("result.bin", "wb");
		
		fwrite(&result, sizeof(RESULT), 1, fp);
		fclose(fp);
	}
	else
	{
		//過去の結果読み込み
		fread(&result, sizeof(RESULT), 1, fp);
		fclose(fp);
		for( loop = 0; loop < 10; loop++ )
		{
			oldResult.oldResult[loop] = result.result[loop];
		}

		//最高記録が0だったら
		if( result.result[0] == 0 )
		{
			nameResult(0, &result.nameResult[0][0]);
			result.result[0] = newResult.newResult;

			fp = fopen("result.bin", "wb");
		
			fwrite(&result, sizeof(RESULT), 1, fp);
			fclose(fp);
		}

		//-------------------------------
		// ソート開始
		//-------------------------------
		else
		{
			//比較の為一つの変数に統一
			for( loop = 0; loop < 10; loop++ )
			{
				sort[loop] = result.result[loop];
				resultName[loop] = &result.nameResult[loop][0];
			}
			sort[10] = newResult.newResult;
			resultName[10] = &newResult.newnameResult[0];

			//ソート
			for( loop = 0; loop < 10; loop++ )
			{
				for( chenge = 0; chenge < 10; chenge++ )
				{
					if( sort[chenge] < sort[chenge + 1] )
					{
						evacuation = sort[chenge];
						sort[chenge] = sort[chenge + 1];
						sort[chenge + 1] = evacuation;

						for( name = 0; name < 10; name++ )
						{
							escName[name] = *(resultName[chenge] + name);
							*(resultName[chenge] + name) = *(resultName[chenge + 1] + name);
							*(resultName[chenge + 1] + name) = escName[name];
						}
					}
				
				}
			}

			//再び戻す
			for( loop = 0; loop < 10; loop++ )
			{
				result.result[loop] = sort[loop];
			}

			for( loop = 0; loop < 10; loop++ )
			{
				//ランキング淫したら
				if( result.result[loop] != oldResult.oldResult[loop] )
				{
					rankin = true;
					naraseBGM(4, 0);	//やりますねぇ！
					naraseBGM(9, 1);	//土方BGM

					nameResult(loop, resultName[loop]);

					fp = fopen("result.bin", "wb");
					fwrite(&result, sizeof(RESULT), 1, fp);
					fclose(fp);
					break;
				}
			}

			//ランクインしなかったら
			if( rankin == false )
			{
				naraseBGM(8, 0);	//宝塚淫夢
			}


		}
	}

}

////////////////////////////////////////////////////////////////////////////
// 変数名	: drawResult
// 返り値	: 
// 説明		: リザルト画面表示
////////////////////////////////////////////////////////////////////////////
void drawResult ( int posX, int posY )
{
	//関数宣言
	int loop;
	int name;

	//-------------------------------
	// リザルト画面作成
	//-------------------------------
	CLS(WHITE, RED);
	LOCATE(posX + 13, posY);
	COLOR(BLACK, YELLOW);
	printf("RESULT");
	
	for( loop = 0; loop < 10; loop ++ )
	{
		COLOR(BLACK, WHITE);
		LOCATE(posX, posY + 2 + loop);
		for( name = 0; name < 10; name++ )
		{
			printf("%c",result.nameResult[loop][name]);
		}
		LOCATE(posX + 20, posY + 2 + loop);
		printf(" %15fM ",result.result[loop]);
	}
}