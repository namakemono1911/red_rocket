/////////////////////////////////////////////////////////////////////////////
//	�v���C���[�̓����̏��� (player.h)
//	Author : TAKUMI UENO
////////////////////////////////////////////////////////////////////////////
#ifndef _PLAYER_H
#define _PLAYER_H


//--------------------------------------------------------------------------
//	�}�N����`
//--------------------------------------------------------------------------
#define LENGTH (25)
#define PI (3.141592)

//--------------------------------------------------------------------------
//	�\���̒�`
//--------------------------------------------------------------------------
enum HAND
{
	up,					//��̏��
	down				//��̏��
};

typedef struct
{
	float excit;			//�v���C���[�̋������
	float oldExcit;			//�O��̋����x

	enum HAND hand;			//���݂̎�̈ʒu
	enum HAND oldHand;		//��t���[���O�̎�̈ʒu

	double lastDeg;			//dick�̏I�_�p�x
	double startDeg;		//dick�̎n�_�p�x

	int angle;				//�����̌X��

	double startX[3];		//dick�̎n�_���W
	double startY[3];		//dick�̎n�_���W

	double oldStartX[3];	//�O���dick�̎n�_���W
	double oldStartY[3];	//�O���dick�̎n�_���W

	double lastX[21];		//dick�̏I�_���W
	double lastY[21];		//dick�̏I�_���W

	double oldLastX[21];	//�O���dick�̏I�_���W
	double oldLastY[21];	//�O���dick�̏I�_���W

	bool rightAngle;		//���p���ǂ���
}PLAYER;

//--------------------------------------------------------------------------
//�@�v���g�^�C�v�錾
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