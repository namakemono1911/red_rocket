/////////////////////////////////////////////////////////////////////////////
//	���U���g(result.h)
//	Author : TAKUMI UENO
////////////////////////////////////////////////////////////////////////////
#ifndef RESULT_H
#define RESULT_H

//--------------------------------------------------------------------------
//	�\���̒�`
//--------------------------------------------------------------------------
typedef struct
{
	float result[10];			//���܂ł̖Ҏ҂����̋L�^
	char nameResult[11][10];	//���܂ł̖Ҏ҂����̖��O
}RESULT;

typedef struct
{
	float newResult;			//����҂̋L�^
	char newnameResult[10];		//����҂̖��O
}NEWRESULT;

typedef struct
{
	float oldResult[10];		//�̂̋L�^
}OLDRESULT;
//--------------------------------------------------------------------------
//�@�v���g�^�C�v�錾
//--------------------------------------------------------------------------
void initResult ( void );
void bubbleResult ( void );
void giveResult ( float kekka );
void nameResult ( int num, char *nameAd );
void drawResult ( int posX, int posY );

#endif