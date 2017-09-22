/////////////////////////////////////////////////////////////////////////////
//	�v���C���[�̓����̏��� (player.cpp)
//	Author : TAKUMI UENO
////////////////////////////////////////////////////////////////////////////
#ifndef SPERM_H
#define SPERM_H
#define PI (3.141592)
#define G (0.5)

//--------------------------------------------------------------------------
//	�\���̒�`
//--------------------------------------------------------------------------
typedef struct
{
	float posX;			//X���W
	float posY;			//Y���W

	float moveX;		//X�����̃x�N�g��
	float moveY;		//Y�����̃x�N�g��

	float oldVirtualX;	//�O��̉��zX
	float oldVirtualY;	//�O��̉��zY

	float virtualX;		//���z���WX
	float virtualY;		//���z���WY

	bool sperm;			//���P�b�g��`�ʂ������ǂ���
	bool oldSperm;		//�Â��Ȃ������P�b�g
	bool bgm;			//��x����BGM��炷
}SPERM;

//--------------------------------------------------------------------------
// �v���g�^�C�v�錾
//--------------------------------------------------------------------------
void initSperm ( void );
void lineSperm ( void );
void updataSperm ( void );
void drawSperm ( void );
void uninitSperm ( void );
SPERM *getSperm ( void );

#endif


