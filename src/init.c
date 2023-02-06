#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <unistd.h>

#if defined _MSC_VER
#include <direct.h>
#elif defined __GNUC__
#include <sys/types.h>
#include <sys/stat.h>
#endif


#include "define.h"
#include "extern.h"
#include "function.h"
#include "util_snd.h"

#include "scene.h"

#ifdef GP2X
#include <unistd.h>
#endif

//#define MacOS

void main_init( void );
void main_init_config( void );
void ExitProgram(void);
int main(int argc, char *argv[]);

char basicpath[128];
char configPath[128];
char homepath[128];

int main(int argc, char *argv[])
{
	SDL_Rect rect;
	Uint32 flags;
	int color = 16;
	SDL_Surface* tmp;
	char AppPath[1024];
	char AppPathw[1024];
	char *char_work;
	int strlen;

	/* ������ */
	memset( &AppPath[0], '\0', sizeof( AppPath ) );
	memset( &AppPathw[0], '\0', sizeof( AppPath ) );
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;
		
#ifdef GP2X
#else
	#ifdef MacOS
		if ( argc > 0 )	// �N���Ɉ���������ꍇ
		{
			strcpy( &AppPath[0], argv[0] );
	//		strcat( &AppPath[0], "/Contents/Recources/" );
			char_work = strrchr( &AppPath[0], '/' );
//			char_work = strrchr( &AppPath[0], '\\' );
			strlen = char_work - &AppPath[0];
			
			strncpy( &AppPathw[0], &AppPath[0], strlen );
			chdir( &AppPathw[0] );
//			LogFileWrite( "testlog.txt", &AppPathw[0] );
		}
	#else
	#endif
#endif	
	
	main_init_config( );	// ���t�@�C���̓ǂݍ���

	/* ��������ʃT�C�Y */
#ifdef GP2X
	gameflag[61] = 1;	//��ʔ{��
//	color = 8;	//��ʔ{��
	flags = SDL_HWSURFACE | SDL_FULLSCREEN | SDL_DOUBLEBUF | SDL_HWPALETTE;
#else
	gameflag[61] = 1;	//��ʔ{��
	#ifdef GCW0
	flags = SDL_HWSURFACE | SDL_TRIPLEBUF;
	#else
	flags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	#endif
	
	if ( argc > 1 )	// �N���Ɉ���������ꍇ
	{
		while( *++argv != NULL )
		{ 
			if( **argv == '-' )
			{
				switch( *(*argv+1) )
				{
				case 'f':  /* -l �I�v�V�������� */
					flags = SDL_FULLSCREEN  | SDL_SWSURFACE;
					break;
				case 'r':  /* -r �I�v�V�������� */
					gameflag[61] = 2;	//��ʔ{��
					break;
				case 'c':  /* -c �I�v�V�������� */
					color = 8;	//��ʔ{��
					break;
				case 'd':  /* -d �I�v�V�������� */
					color = 16;	//��ʔ{��
					break;
				}
			}
			else
			{
				break;
			}
		}
//		if ( ( char * )argv[1] == "f" )
//		{
//			flags = SDL_FULLSCREEN  | SDL_SWSURFACE;
//		}
//		if ( ( char * )argv[2] == '2' )
//		{
//			gameflag[61] = 2;	//��ʔ{��
//		}
//		LogFileWrite( "testlog.txt", &( char * )argv[1] );
	}
#endif

//	g_screen = SDL_SetVideoMode(DISPLY_WIDTH, DISPLY_HEIGHT, 16, SDL_SWSURFACE);
//	g_screen = SDL_SetVideoMode(DISPLY_WIDTH, DISPLY_HEIGHT, 8, flags);
	g_screen = SDL_SetVideoMode(DISPLY_WIDTH * gameflag[61], DISPLY_HEIGHT * gameflag[61], color, flags);
	rect.x = 0;
	rect.y = 0;
	rect.w = DISPLY_WIDTH * gameflag[61];
	rect.h = DISPLY_HEIGHT * gameflag[61];
	SDL_SetClipRect( g_screen, &rect );

	if ( color == 8 )
	{
		tmp = SDL_LoadBMP("image/color.bmp");		//�v���[���i���o�[�P�Ƀ^�C�g����ʔw�i��ǂݍ���
		SetGscreenPalette( tmp );
		SDL_FreeSurface(tmp);
	}
	SDL_DisplayFormat(g_screen);
	
	if (!g_screen)
	{
		fprintf(stderr, "Couldn't set video mode: %s\n", SDL_GetError());
		return 1;
	}
	//�E�B���h�E�L���v�V����
	SDL_WM_SetCaption( WINDOW_TITLE, "" );
	
	SDL_ShowCursor(SDL_DISABLE);
	FunctionInit( );
//	soundInitBuffer();
	/* �O���[�o���ϐ��̏����� */
	main_init( );


		
	scenemanager( );
	
	ExitProgram( );
	return 0;
}


void main_init( void )
{
	g_scene = EN_SN_EXIT;
	g_scene_req = EN_SN_LOGO;

	LoadBitmap("image/cg/boot01_0.bmp",FID_BOOT01_0,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/cg/boot01_1.bmp",FID_BOOT01_1,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	CreateSurface( FID_WORK01, DISPLY_WIDTH, DISPLY_HEIGHT );
	
	// �Q�[�����̎g�p���鉹�̓ǂݍ���
	soundLoadBuffer(EN_BGM_GAME01, (Uint8 *)"sound/bgm/01.ogg", -1);
	soundLoadBuffer(EN_BGM_GAME02, (Uint8 *)"sound/bgm/02.ogg", -1);
	soundLoadBuffer(EN_BGM_GAME03, (Uint8 *)"sound/bgm/03.ogg", -1);
//	soundLoadBuffer(EN_BGM_GAME04, (Uint8 *)"sound/bgm/04.ogg", -1);
//	soundLoadBuffer(EN_BGM_GAME05, (Uint8 *)"sound/bgm/05.ogg", -1);
//	soundLoadBuffer(EN_BGM_GAME06, (Uint8 *)"sound/bgm/06.ogg", -1);
//	soundLoadBuffer(EN_BGM_GAME07, (Uint8 *)"sound/bgm/07.ogg", 0);
	
	soundLoadBufferSE(EN_SE_ATTACK , (Uint8 *)"sound/se/attack.wav" );
	soundLoadBufferSE(EN_SE_BOM1   , (Uint8 *)"sound/se/bom1.wav" );
	soundLoadBufferSE(EN_SE_BOM2   , (Uint8 *)"sound/se/bom2.wav" );
	soundLoadBufferSE(EN_SE_BOM3   , (Uint8 *)"sound/se/bom3.wav" );
	soundLoadBufferSE(EN_SE_BOSS_DEAD , (Uint8 *)"sound/se/boss_dead.wav" );
	soundLoadBufferSE(EN_SE_DAMEGE , (Uint8 *)"sound/se/damage.wav" );
	soundLoadBufferSE(EN_SE_DEFENCE, (Uint8 *)"sound/se/defence.wav" );
	soundLoadBufferSE(EN_SE_HIT    , (Uint8 *)"sound/se/hit.wav" );
	soundLoadBufferSE(EN_SE_SELECT , (Uint8 *)"sound/se/select.wav" );
//	soundLoadBufferSE(EN_SE_OK     , (Uint8 *)"sound/se/ok.wav" );
//	soundLoadBufferSE(EN_SE_CANSEL , (Uint8 *)"sound/se/cansel.wav" );

	Set_Volume( gameflag[60] );

}

void ExitProgram(void)
{

	soundStopBgm(0);
	soundStopSeAll();
	soundRelease();

	SaveGameFlag("save/config");
	
	closePAD();
//	closeSDL();
	SDL_Quit();

#ifdef GP2X
	chdir("/usr/gp2x");
	execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
#endif
}


void main_init_config( void )
{
	int i;
	i = 0;
	
	// Gameblabla
#ifdef LINUX
	char savepath[128];
	snprintf(basicpath, sizeof(basicpath), "%s", getenv("HOME"));
	snprintf(configPath, sizeof(configPath), "%s/.config", basicpath);
	snprintf(homepath, sizeof(homepath), "%s/.config/wlaol", basicpath);
	snprintf(savepath, sizeof(savepath), "%s/.config/wlaol/save", basicpath);
	
	if(access( configPath, F_OK ) == -1)  mkdir(configPath, 0755);
	if(access( homepath, F_OK ) == -1)  mkdir(homepath, 0755);
	if(access( savepath, F_OK ) == -1)  mkdir(savepath, 0755);
#else
	/* Empty */
	snprintf(basicpath, sizeof(basicpath), "");
	snprintf(configPath, sizeof(configPath), "");
	snprintf(homepath, sizeof(homepath), "");
	snprintf(savepath, sizeof(savepath), "save");
	
	if(access( savepath, , F_OK ) == -1)  mkdir(savepath, 0755);
#endif
	
	if ( ! ( LoadGameFlag("save/config") == 0 ) )
	{
		/* �t�@�C�������݂��Ȃ��ꍇ�̏����l�ݒ� */
		ResetGameFlag();

		gameflag[EN_SAVEDATA_SUM]=0;		//
		gameflag[EN_SAVEDATA_VER]=0;		//

#ifdef GP2X
		gameflag[EN_SAVEDATA_1P_UP]=GP2X_BUTTON_UP;		//��	Up
		gameflag[EN_SAVEDATA_1P_DOWN]=GP2X_BUTTON_DOWN;	//��	Down
		gameflag[EN_SAVEDATA_1P_LEFT]=GP2X_BUTTON_LEFT;	//��	Left
		gameflag[EN_SAVEDATA_1P_RIGHT]=GP2X_BUTTON_RIGHT;	//�E	Right
		gameflag[EN_SAVEDATA_1P_1]=GP2X_BUTTON_X;	//�`	Z
		gameflag[EN_SAVEDATA_1P_2]=GP2X_BUTTON_B;	//�a	X
		gameflag[EN_SAVEDATA_1P_3]=GP2X_BUTTON_Y;	//�b	C
		gameflag[EN_SAVEDATA_1P_4]=GP2X_BUTTON_A;	//�c	S
		gameflag[EN_SAVEDATA_1P_5]=GP2X_BUTTON_L;	//�c	S
		gameflag[EN_SAVEDATA_1P_6]=GP2X_BUTTON_R;	//�c	S
		gameflag[EN_SAVEDATA_1P_START]=GP2X_BUTTON_START;	//�c	S
		gameflag[EN_SAVEDATA_1P_SELECT]=GP2X_BUTTON_SELECT;	//�c	S
#else 
		gameflag[EN_SAVEDATA_1P_UP]=GP2X_BUTTON_UP;		//��	Up
		gameflag[EN_SAVEDATA_1P_DOWN]=GP2X_BUTTON_DOWN;	//��	Down
		gameflag[EN_SAVEDATA_1P_LEFT]=GP2X_BUTTON_LEFT;	//��	Left
		gameflag[EN_SAVEDATA_1P_RIGHT]=GP2X_BUTTON_RIGHT;	//�E	Right
		gameflag[EN_SAVEDATA_1P_1]=GP2X_BUTTON_A;	//�`	Z
		gameflag[EN_SAVEDATA_1P_2]=GP2X_BUTTON_X;	//�a	X
		gameflag[EN_SAVEDATA_1P_3]=GP2X_BUTTON_Y;	//�b	C
		gameflag[EN_SAVEDATA_1P_4]=GP2X_BUTTON_B;	//�c	S
		gameflag[EN_SAVEDATA_1P_5]=GP2X_BUTTON_L;	//�c	S
		gameflag[EN_SAVEDATA_1P_6]=GP2X_BUTTON_R;	//�c	S
		gameflag[EN_SAVEDATA_1P_START]=GP2X_BUTTON_START;	//�c	S
		gameflag[EN_SAVEDATA_1P_SELECT]=GP2X_BUTTON_SELECT;	//�c	S
		gameflag[EN_SAVEDATA_DISPZOOM] = 2;	//��ʔ{��
#endif
		
		gameflag[EN_SAVEDATA_MASTERVOLUME] = 128;	//����
		gameflag[EN_SAVEDATA_BGVOLUME] = 128;	//����
		gameflag[EN_SAVEDATA_SEVOLUME] = 128;	//����
		gameflag[EN_SAVEDATA_VOVOLUME] = 128;	//����

		
		gameflag[EN_SAVEDATA_PLAYTIME_F] = 0;	//play time s
		gameflag[EN_SAVEDATA_PLAYTIME_S] = 0;	//play time s
		gameflag[EN_SAVEDATA_PLAYTIME_M] = 0;	//play time m
		gameflag[EN_SAVEDATA_PLAYTIME_H] = 0;	//play time h
		gameflag[EN_SAVEDATA_CLEARTIME_F] = 59;	//CLEAR time s
		gameflag[EN_SAVEDATA_CLEARTIME_S] = 59;	//CLEAR time s
		gameflag[EN_SAVEDATA_CLEARTIME_M] = 59;	//CLEAR time m
		gameflag[EN_SAVEDATA_CLEARTIME_H] = 99;	//CLEAR time h
		
		//�Q�[���Ǝ��̃f�[�^
		gameflag[EN_SAVEDATA_SELECTLEVEL] = 1;	//

		//�X�R�A�֘A��200�Ԃ���
		gameflag[EN_SAVEDATA_SCORE] = 0;	//
		
	}
// for debug start
/*
		for ( i = 0; i <= 99; i++ )
		{
			gameflag[400 + i] = 1;
		}
*/
// for debug end
	gameflag[121] = 50;	//���B�X�e�[�W
//	gameflag[100] = 1;	//���B�X�e�[�W
	
	g_DebugDisp 				= GetConfig( CONFIGFILE_NAME , "DebugDisp" );
	g_DebugStageProduction 		= GetConfig( CONFIGFILE_NAME , "DebugStageProduction" );
	g_DebugMuteki 				= GetConfig( CONFIGFILE_NAME , "DebugMuteki" );
	g_DebugKey 					= GetConfig( CONFIGFILE_NAME , "DebugKey" );
}




