#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL.h"
#include "define.h"
#include "function.h"
#include "util_snd.h"
#include "extern.h"
#include "option.h" 


// �֐��v���g�^�C�v
void option_main( void );
void option_init( void );
void option_relese( void );
void option_keys( void );
void option_draw( void );


// �ϐ��錾
static int mode;		//���ݑI������Ă��鍀��	�O�F�f�`�l�d�r�s�`�q�s�@�P�F�n�o�s�h�n�m�@�Q�F�d�w�h�s

//----------------------------------------------------------------------
// ���C���֐�
void option_main( void )
{
	option_keys( );
}

void option_init( void )
{
	mode = 0;
}

void option_relese( void )
{
}


void option_keys( void )
{
	if ( IsPushKey( EN_PLAYERNUM_01, EN_INPUT_UP ) )
	{
	}
	else if ( IsPushKey( EN_PLAYERNUM_01, EN_INPUT_DOWN ) )
	{
	}
	if ( IsPushKey( EN_PLAYERNUM_01, EN_INPUT_LEFT ) )
	{
	}
	else if ( IsPushKey( EN_PLAYERNUM_01, EN_INPUT_RIGHT ) )
	{
	}
	
	
	//	���肪�������
	if ( IsPushOKKey( ) )
	{
		soundPlaySe( EN_SE_SELECT );
		mode++;
		if ( mode == 2 )
		{
			SetScene( EN_SN_TITLE );
		}
	}
	
	//	�L�����Z�����������
	if ( IsPushCancelKey(  ) )
	{
		soundPlaySe( EN_SE_SELECT );
		mode--;
		if ( mode == -1 )
		{
			SetScene( EN_SN_TITLE );
		}
	}

}

void option_draw( void )
{
	//-------------------------------------------------------------
	//�ϐ��錾
	INT32 cx = DISPLY_WIDTH / 2;
	INT32 cy = DISPLY_HEIGHT / 2;
	//-------------------------------------------------------------

	//�w�i�N���A
	ClearSecondary();

	ObjSetEx( C_HOWTOPLAY_P000_00_K + mode, 200, cx, cy, 1.0f, 1.0f, 0, 255, 255, 255, 255, 0.0f, 0, 0, -1, -1 );

	DarwFont( "A:NEXT B:BACK", cx, 360 - 16, 1 );


}


