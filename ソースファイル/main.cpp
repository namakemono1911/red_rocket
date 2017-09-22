/////////////////////////////////////////////////////////////////////////////
//	���C������ (main.cpp)
//	Author : TAKUMI UENO
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
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
//	�}�N����`
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//	�\���̒�`
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//�@�v���g�^�C�v�錾
//--------------------------------------------------------------------------
void init ( void );
void action ( void );
void draw ( void );
void redRocket ( void );
void result ( void );

////////////////////////////////////////////////////////////////////////////
// �֐���	: main
// �Ԃ�l	: 0
// ����		: ���C���̏���
////////////////////////////////////////////////////////////////////////////
void main ( void )
{
	//�֐��錾
	bool check = false;
	bool one = false;

	int CNTFPS = 0;			//FPS�J�E���^�[
	DWORD ExecLastTime = 0;
	DWORD FPSLastTime = 0;
	DWORD CurrentTime = 0;
	int CNTFrame = 0;

	DWORD FirestTime;

	//�J�[�\���I�t
	CUROFF();


	//-------------------------------
	// �^�C�g�����
	//-------------------------------
	do
	{
		CurrentTime = timeGetTime();

		//�����ݒ�
		if( one == false )
		{
			//�֐�������
			init ( );
			//BGM
			naraseBGM(0, 1);
			//���ݎ����擾
			FirestTime = timeGetTime();
			one = true;
		}

		//60/1000�b�ŏ���
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
// �֐���	: initData
// �Ԃ�l	: 
// ����		: �f�[�^�̏�����
////////////////////////////////////////////////////////////////////////////
void init ( void )
{
	initSiko ( );
	initSperm ( );
	initBGM();
	initResult();
}

////////////////////////////////////////////////////////////////////////////
// �֐���	: playerAction
// �Ԃ�l	: 
// ����		: �v���C���[
////////////////////////////////////////////////////////////////////////////
void action ( void )
{
	sikosiko ( );
}

////////////////////////////////////////////////////////////////////////////
// �֐���	: draw
// �Ԃ�l	: 
// ����		: �v���C���[�̕`��
////////////////////////////////////////////////////////////////////////////
void draw ( void )
{
	drawSiko ( );
}

////////////////////////////////////////////////////////////////////////////
// �֐���	: redRocket
// �Ԃ�l	: 
// ����		: �{�ҊJ�n
////////////////////////////////////////////////////////////////////////////
void redRocket ( void )
{
	//�֐��錾
	int CNTFPS = 0;			//FPS�J�E���^�[
	DWORD ExecLastTime = 0;
	DWORD FPSLastTime = 0;
	DWORD CurrentTime = 0;
	int CNTFrame = 0;

	DWORD firstSiko;		//�������ԗp�J�n����
	DWORD lastSiko;			//��r����

	SPERM *sperm;			//sperm�ϐ��擾
	sperm = getSperm();

	bool one;				//1�x�ʂ������ǂ���

	int len = 0;			//����

	//�J�[�\���I�t
	CUROFF();

	//-------------------------------
	// ������
	//-------------------------------
	init ( );
	one = false;
	firstSiko = timeGetTime();	//�͂��A��[���n��
	lastSiko = 0;				//�I���I��I

	//-------------------------------
	// �`���[�g���A��
	//-------------------------------
	naraseBGM(1,0);				//SE
	CLS(WHITE, BLACK);
	INPCLEAR();

	do
	{
		CurrentTime = timeGetTime();

		//60/1000�b�ŏ���
		if( ( CurrentTime - ExecLastTime ) >= ( 1000 / 60 ) )
		{
			ExecLastTime = CurrentTime;

			if( one == false )
			{
				COLOR(WHITE, BLACK);
				LOCATE(20, 11);
				printf("�X�y�[�X�L�[���������艟���Ȃ������肵��I");
				one = true;
			}

			CNTFrame++;
		}
	}while( INP(PK_SP) == 0 );

	stopBGM(1);

	//�w�i�`��
	CLS();
	COLOR(WHITE, BLACK);
	drawBackground(2, 0, 79, 0, 3, 1, 23);

	//-------------------------------
	// �G�l���M�[�`���[�W
	//-------------------------------
	firstSiko = timeGetTime();
	lastSiko = 0;
	naraseBGM(7, 1);

	do
	{
		CurrentTime = timeGetTime();
		lastSiko = timeGetTime();

		//60/1000�b�ŏ���
		if( ( CurrentTime - ExecLastTime ) >= ( 1000 / 60 ) )
		{
			ExecLastTime = CurrentTime;

			//LOCATE(60, 1);
			//printf("%d",CNTFPS);

			//�G�i�W�[�`���[�W
			COLOR(WHITE, BLACK);
			draw();
			action();
			LOCATE(40, 10);
			COLOR(BLACK, WHITE);
			printf("�c�莞��:%2d", 10 - ( (lastSiko - firstSiko) / 1000) );

			CNTFrame++;
		}
	}while( lastSiko - firstSiko < 10000 );
	stopBGM(7);

	//-------------------------------
	// ���ˊp�x
	//-------------------------------
	closeBGM();
	initBGM();
	CLS(WHITE, BLACK);
	INPCLEAR();

	do
	{
		CurrentTime = timeGetTime();

		//60/1000�b�ŏ���
		if( ( CurrentTime - ExecLastTime ) >= ( 1000 / 60 ) )
		{
			ExecLastTime = CurrentTime;

			//���ˊp�x
			angle ( );
			drawAngle ( );

			CNTFrame++;
		}
	}while( INP(PK_ENTER) == 0 );
	
	//-------------------------------
	// 4�b�̊�
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

		//60/1000�b�ŏ���
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
	// �ː�
	//-------------------------------
	lineSperm();
	naraseBGM(2, 0);

	do
	{
		CurrentTime = timeGetTime();

		//60/1000�b�ŏ���
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

	//�G���^�[�����X
	INPCLEAR();
	do
	{
		CurrentTime = timeGetTime();

		//60/1000�b�ŏ���
		if( ( CurrentTime - ExecLastTime ) >= ( 1000 / 60 ) )
		{
			ExecLastTime = CurrentTime;

			CNTFrame++;
		}
	}while( INP(PK_ENTER) == 0 );

	stopBGM(3);

	//-------------------------------
	// ���U���g
	//-------------------------------
	//��UBGM��������
	closeBGM();
	initBGM();

	result();
	CUROFF();

	//�G���^�[������
	INPCLEAR();
	do
	{
		CurrentTime = timeGetTime();

		//60/1000�b�ŏ���
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
// �ϐ���	: result
// �Ԃ�l	: 
// ����		: ���U���g�̈�A�̗���
////////////////////////////////////////////////////////////////////////////
void result ( void )
{
	//�ϐ��錾
	SPERM *sperm;
	sperm = getSperm();

	//giveResult(sperm->virtualX);
	bubbleResult();
	drawResult(25, 5);
}