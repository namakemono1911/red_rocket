/////////////////////////////////////////////////////////////////////////////
//	���˂��ꂽ�e���̏��� (sperm.h)
//	Author : TAKUMI UENO
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//--------------------------------------------------------------------------
#include "player.h"
#include "main.h"
#include "sperm.h"
#include "redrocketField.h"
#include "BGM.h"
#include <math.h>

//--------------------------------------------------------------------------
//	�\���̒�`
//--------------------------------------------------------------------------
SPERM sperm;

////////////////////////////////////////////////////////////////////////////
// �ϐ���	: initSperm
// �Ԃ�l	: 
// ����		: �ϐ��̏�����
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
// �ϐ���	: lineSperm
// �Ԃ�l	: 
// ����		: �����̕������Z�o
////////////////////////////////////////////////////////////////////////////
void lineSperm ( void )
{
	//�ϐ��錾
	float startX;
	float startY;
	
	float lastX;
	float lastY;
	
	float katamuki;

	PLAYER *player;

	player = getPlayer();
	
	//-------------------------------
	// X,Y�����̃x�N�g���v�Z
	//-------------------------------
	sperm.moveX *= ( player->excit * -1 );
	player->excit *= sperm.moveY;
}

////////////////////////////////////////////////////////////////////////////
// �ϐ���	: updataSperm
// �Ԃ�l	: 
// ����		: Sperm�̍X�V����
////////////////////////////////////////////////////////////////////////////
void updataSperm ( void )
{
	//�ϐ��錾
	PLAYER *player;

	player = getPlayer();

	//-------------------------------
	//�d�͏���
	//-------------------------------
	player->oldExcit = player->excit;
	player->excit += G;

	//-------------------------------
	//���z���W�X�V
	//-------------------------------
	sperm.oldVirtualX = sperm.virtualX;
	sperm.oldVirtualY = sperm.virtualY;

	sperm.virtualY += player->lastY[21] + player->startY[1] + player->excit;
	sperm.virtualX += sperm.moveX;

	//-------------------------------
	//�n�ʂɒ��n������
	//-------------------------------
	if( sperm.virtualY >= 19 )
	{
		sperm.moveX = 0;
		sperm.moveY = 0;
		sperm.virtualY = 20;
	}

	//-------------------------------
	// �O��`�ʂ��������X�V
	//-------------------------------
	sperm.oldSperm = sperm.sperm;
}

////////////////////////////////////////////////////////////////////////////
// �ϐ���	: drawSperm
// �Ԃ�l	: 
// ����		: Sperm�̕`�ʏ���
////////////////////////////////////////////////////////////////////////////
void drawSperm ( void )
{
	//�֐��錾
	int type = 1;		//�w�i�̎��
	int startX;			//�w�i�`�ʊJ�n�̈ʒuX
	int startY;			//�w�i�`�ʊJ�n�̈ʒuY
	int loop;			//������
	PLAYER *player;

	player = getPlayer();

	//-------------------------------
	// �`�ʂ���w�i���[�v�̌v�Z
	//-------------------------------
	//X����
	startX = ( (int)sperm.virtualX / 2 ) % 80;

	//Y����
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
	//�w�i�`��
	//-------------------------------
	for( loop = 1; loop <= 25; loop++ )
	{
		if( sperm.oldVirtualX != startX && sperm.oldVirtualY != startY )
		{
			//--------------------------------
			// ���x�ɂ���Ĕw�i�ύX
			//--------------------------------
			//�n��
			if( sperm.virtualY + loop - 11 > 20 )
			{
				type = 2;
				COLOR(WHITE, BLACK);
			}

			//��
			if( sperm.virtualY + loop - 11 > -20000 && sperm.virtualY + loop - 11 < 20 )
			{
				type = 1;
				COLOR(WHITE, BLUE);
				sperm.sperm = true;
			}

			//�F��
			if( sperm.virtualY + loop - 11 <= -20000 )
			{
				type = 0;
				COLOR(WHITE, BLACK);
				sperm.sperm = false;
			}

			//-------------------------------
			// ���P�b�g�̕���������ĕ`��
			//-------------------------------
			if( loop == 11 )
			{
				drawBackground( type, startX, 39, ( 25 - startY ) % 25 + loop, 1, 1, loop );
				drawBackground( type, startX + 41, 79 - 41, ( 25 - startY ) % 25 + loop, 1, 42, loop );

				//-------------------------------
				// ���P�b�g�`��
				//-------------------------------
				if( (int)sperm.virtualY * -1 + 20 > 0 )
				{
					//���P�b�g�̗������x�ɂ���ĕϐF
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
					printf("��");
				}
				//���n��
				else
				{
					LOCATE(40, 11);
					printf("..");
				}
			}
			//-------------------------------
			// �L�^�ƍ��x�̕���������ĕ`��
			//-------------------------------
			if( loop == 20 || loop == 21 )
			{
				drawBackground( type, startX, 29, ( 25 - startY ) % 25 + loop, 1, 1, loop );
				drawBackground( type, startX + 50, 79 - 50, ( 25 - startY ) % 25 + loop, 1, 51, loop );
			}
			//����ȊO�͒ʏ�
			if( loop != 11 && loop != 20 && loop != 21 )
			{
				drawBackground( type, startX, 79, ( 25 - startY ) % 25 + loop, 1, 1, loop );
			}
		}
	}

	/*
	//-------------------------------
	// ���P�b�g�`��
	//-------------------------------
	//���P�b�g�̗������x�ɂ���ĕϐF
	if( player->excit > 100 )
	{
		sperm.sperm = false;
		COLOR(RED);
	}
	//���P�b�g��1�x�����`��
	if( sperm.sperm == false )
	{
		sperm.sperm = true;
		LOCATE( 40, 11 );
		printf("��");
	}
	*/
	//-------------------------------
	// �L�^�ƍ��x�`��
	//-------------------------------
	COLOR(WHITE, BLACK);
	LOCATE(30, 20);
	printf("���x:%14dM",( (int)sperm.virtualY) * -1 + 20 );
	LOCATE(30, 21);
	printf("�L�^:%14fM",sperm.virtualX);
}


////////////////////////////////////////////////////////////////////////////
// �ϐ���	: uninitSperm
// �Ԃ�l	: 
// ����		: Sperm�̏I������
////////////////////////////////////////////////////////////////////////////
void uninitSperm ( void )
{

}

////////////////////////////////////////////////////////////////////////////
// �ϐ���	: getSperm
// �Ԃ�l	: 
// ����		: Sperm�̐擪�A�h���X
////////////////////////////////////////////////////////////////////////////
SPERM *getSperm ( void )
{
	return &sperm;
}