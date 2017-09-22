/////////////////////////////////////////////////////////////////////////////
//	�v���C���[�̓����̏��� (player.cpp)
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
#include <math.h>

//--------------------------------------------------------------------------
//	�\���̒�`
//--------------------------------------------------------------------------
PLAYER player;

//--------------------------------------------------------------------------
//�@�v���g�^�C�v�錾
//--------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
// �֐���	: initShiko
// �Ԃ�l	: 0
// ����		: �֐�������
////////////////////////////////////////////////////////////////////////////
void initSiko ( void )
{
	//�֐��錾
	int loop;		//for���̐���

	//-------------------------------
	// PLAYER�̏�����
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
// �֐���	: sikosiko
// �Ԃ�l	: 0
// ����		: �V�R�葱����̂��E�E�E
////////////////////////////////////////////////////////////////////////////
void sikosiko ( void )
{
	//�֐��錾

	//-------------------------------
	// �V�R�������鏈��
	//-------------------------------
	//��ɋ����̓}�C�i�X
	player.excit += 0.35;
	if ( player.excit >= 0 )
	{
		player.excit = 0;
	}
	
	//��̈ʒu���O��ƈ�����ꍇ
	if( player.hand != player.oldHand )
	{
		stopBGM(5);
		naraseBGM(5, 0);
		player.excit -= 2;
	}

	//��̈ʒu�X�V
	player.oldHand = player.hand;

	//��̕`�ʈʒu
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
// �֐���	: drawSiko
// �Ԃ�l	: 0
// ����		: �V�R�葱����̂��E�E�E
////////////////////////////////////////////////////////////////////////////
void drawSiko ( void )
{
	//�֐��錾
	int x,y;		//AA��X,Y
	char dick[2][18][10] =	//dick
	{
		{
			"������",
			"������",
			"������",
		},
		
		{
			"������",
			"������",
			"������",
			"������",
			"������",
			"������",
			"������",
			"������",
			"������",
			"������",
			"������",
			"������",
			"������",
			"������",
			"������",
			"������",
			"������",
			"������",
		},
	};

	char hand[11][21] =	//hand
	{
		" �@ �@........... ",
		"  �@::::         :",
		"  :::::::........ ",
		"::::::::         :",
		":::::::::........ ",
		"::::::::         :",
		":::::::::........ ",
		":::::::: �@ �@   :",
		":::::::::........ ",
		"::::::::",
		":::::::",
	};

	//LOCATE(1,1);
	//printf("%f",player.excit);

	//�X�y�[�X��������Ă��Ȃ������ꍇ
	if( player.hand == up && player.hand != player.oldHand)
	{
		//��̂�w�i�ŏ㏑��
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

		//dick����
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
		//��̐���
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

	//�X�y�[�X��������Ă����ꍇ
	if( player.hand == down && player.hand != player.oldHand )
	{
		//��̍폜
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

		//dick�C��
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
		//��̐���
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
// �֐���	: angle
// �Ԃ�l	: 0
// ����		: ���ˊp�x�v�Z
////////////////////////////////////////////////////////////////////////////
void angle ( void )
{
	//�֐��錾
	double lastRad;		//�I���̃�
	double startRad;	//�n�܂�̃�
	int loop;
	SPERM *sperm;		//sperm�\���̂̃A�h���X�擾

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

	//�ƌv�Z
	lastRad = ( player.lastDeg * PI ) / 180;
	startRad = ( player.startDeg * PI ) /180;

	//�n�_���W�Z�o
	for( loop = 0; loop < 3; loop++ )
	{
		player.oldStartX[loop] = player.startX[loop];
		player.oldStartY[loop] = player.startY[loop];

		player.startX[loop] = (loop * cos( startRad )) * 2.5;
		player.startY[loop] = loop * sin( startRad ) * 1.5;
	}

	//�I�_���W�Z�o
	for(loop = 0; loop < 21; loop++ )
	{
		player.oldLastX[loop] = player.lastX[loop];
		player.oldLastY[loop] = player.lastY[loop];

		player.lastX[loop] = (loop * cos( lastRad )) * 2;
		player.lastY[loop] = loop * sin( lastRad );
	}

	//X,Y�����ɓ`���͂̊���
	sperm->moveY = -1 * ( sin( lastRad ) );
	sperm->moveX = cos( lastRad );
}

////////////////////////////////////////////////////////////////////////////
// �֐���	: drawAngle
// �Ԃ�l	: 0
// ����		: �p�x�`��
////////////////////////////////////////////////////////////////////////////
void drawAngle ( void )
{
	//�֐��錾
	int loop;
	int width;
	
	int startX[3];
	int startY[3];

	int oldStartX[3];
	int oldStartY[3];

	//�`��
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
	printf("Enter�Ŕ��ˁI");

	//�O��̃i�j�폜
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

	//�i�j�`��
	COLOR(RED, RED);
	for( width = 0; width < 3; width++ )
	{
		for( loop = 0; loop < 21; loop++ )
		{	
			if( (int)player.lastX[loop - 1] + 1 < (int)player.lastX[loop]
				|| player.lastY[loop - 1] != player.lastY[loop])
			{
				LOCATE(startX[width] + (int)player.lastX[loop], startY[width] + (int)player.lastY[loop]);
				printf("��");
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// �ϐ���	: uninitSiko
// �Ԃ�l	: 
// ����		: �I������
////////////////////////////////////////////////////////////////////////////
void uninitSiko ( void )
{

}

/////////////////////////////////////////////////////////////////////////////
// �ϐ���	: getPlayer
// �Ԃ�l	: &player
// ����		: player�\���̂̐擪�A�h���X��������킠�Ȃ���
////////////////////////////////////////////////////////////////////////////
PLAYER *getPlayer ( void )
{
	return &player;
}