/////////////////////////////////////////////////////////////////////////////
//	���U���g(result.h)
//	Author : TAKUMI UENO
////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//--------------------------------------------------------------------------
#include "main.h"
#include "result.h"
#include "sperm.h"
#include "BGM.h"

//--------------------------------------------------------------------------
//	�\���̒�`
//--------------------------------------------------------------------------
RESULT result;
NEWRESULT newResult;
OLDRESULT oldResult;

////////////////////////////////////////////////////////////////////////////
// �֐���	: initResult
// �Ԃ�l	: 0
// ����		: �֐�������
////////////////////////////////////////////////////////////////////////////
void initResult ( void )
{
	//�֐��錾
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
		//�ߋ��̌��ʓǂݍ���
		fread(&result, sizeof(RESULT), 1, fp);
		fclose(fp);
	}
}

////////////////////////////////////////////////////////////////////////////
// �֐���	: giveResult
// �Ԃ�l	: 0
// ����		: ���ʂ�result�Ɋi�[
////////////////////////////////////////////////////////////////////////////
void giveResult ( float kekka )
{
	newResult.newResult = kekka;
}

////////////////////////////////////////////////////////////////////////////
// �ϐ���	: nameResult
// �Ԃ�l	: 
// ����		: �V�L�^�҂ɖ��O����͂�����
////////////////////////////////////////////////////////////////////////////
void nameResult ( int num, char *nameAd )
{
	//�ϐ��錾
	int check;

	//-------------------------------
	// ���O����
	//-------------------------------
	while(1)
	{
		CURON();
		CLS(WHITE, BLACK);
		LOCATE(30, 10);
		printf("���߂łƂ��I���Ȃ���%2d�ʂł����I",num + 1);
		LOCATE(30, 11);
		printf("���O����͂��Ă�������");
		LOCATE(32, 12);
		scanf("%s",nameAd);
		rewind(stdin);

		check = strlen(nameAd);

		if(check > 10)
		{
			CLS();
			LOCATE(34, 10);
			printf("���O���������܂��B");
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
// �֐���	: bubbleResult
// �Ԃ�l	: 0
// ����		: �o�u���\�[�g
////////////////////////////////////////////////////////////////////////////
void bubbleResult ( void )
{
	//�֐��錾
	int loop;
	int chenge;				//���l����ւ�
	int name;				//���O����ւ�

	float evacuation;		//���l�̔�
	float sort[11];			//�\�[�g�p�̕ϐ�

	char *resultName[11];	//���O������ւ�
	char escName[10];		//���O�̔�

	bool rankin = false;	//�����N�C���������ǂ���

	SPERM *sperm;
	sperm = getSperm();
	newResult.newResult = sperm->virtualX;

	FILE *fp;

	fp = fopen("result.bin", "rb");
	if( fp == 0 )
	{
		naraseBGM(4, 0);	//���܂��˂��I
		naraseBGM(9, 1);	//�y��BGM

		nameResult(0, &result.nameResult[0][0]);
		result.result[0] = newResult.newResult;

		fp = fopen("result.bin", "wb");
		
		fwrite(&result, sizeof(RESULT), 1, fp);
		fclose(fp);
	}
	else
	{
		//�ߋ��̌��ʓǂݍ���
		fread(&result, sizeof(RESULT), 1, fp);
		fclose(fp);
		for( loop = 0; loop < 10; loop++ )
		{
			oldResult.oldResult[loop] = result.result[loop];
		}

		//�ō��L�^��0��������
		if( result.result[0] == 0 )
		{
			nameResult(0, &result.nameResult[0][0]);
			result.result[0] = newResult.newResult;

			fp = fopen("result.bin", "wb");
		
			fwrite(&result, sizeof(RESULT), 1, fp);
			fclose(fp);
		}

		//-------------------------------
		// �\�[�g�J�n
		//-------------------------------
		else
		{
			//��r�̈׈�̕ϐ��ɓ���
			for( loop = 0; loop < 10; loop++ )
			{
				sort[loop] = result.result[loop];
				resultName[loop] = &result.nameResult[loop][0];
			}
			sort[10] = newResult.newResult;
			resultName[10] = &newResult.newnameResult[0];

			//�\�[�g
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

			//�Ăі߂�
			for( loop = 0; loop < 10; loop++ )
			{
				result.result[loop] = sort[loop];
			}

			for( loop = 0; loop < 10; loop++ )
			{
				//�����L���O��������
				if( result.result[loop] != oldResult.oldResult[loop] )
				{
					rankin = true;
					naraseBGM(4, 0);	//���܂��˂��I
					naraseBGM(9, 1);	//�y��BGM

					nameResult(loop, resultName[loop]);

					fp = fopen("result.bin", "wb");
					fwrite(&result, sizeof(RESULT), 1, fp);
					fclose(fp);
					break;
				}
			}

			//�����N�C�����Ȃ�������
			if( rankin == false )
			{
				naraseBGM(8, 0);	//��ˈ���
			}


		}
	}

}

////////////////////////////////////////////////////////////////////////////
// �ϐ���	: drawResult
// �Ԃ�l	: 
// ����		: ���U���g��ʕ\��
////////////////////////////////////////////////////////////////////////////
void drawResult ( int posX, int posY )
{
	//�֐��錾
	int loop;
	int name;

	//-------------------------------
	// ���U���g��ʍ쐬
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