#ifndef __charcode_h__
#define __charcode_h__

#include "../include/general.h" 

// �֐��v���g�^�C�v
// �R�[�h
enum {

	C_CC_TOP=0,
	C_CC_DUMMY,
	C_BOOT01_TOP = (C_CC_DUMMY),
		#include"boot/boot01.h"

	C_CHAR_TABLE_END,
};


typedef struct _codedata
{
	INT32		m_ResID;
	UINT32		m_PosX;
	UINT32		m_PosY;
	UINT32		m_SizeX;
	UINT32		m_SizeY;
	UINT32		m_CCode;		// �`�F�b�N�p�L�����R�[�h 
	INT32		m_Bunkatu;		// �`�F�b�N�p�L�����R�[�h 
	INT32		m_OfsX;		// �����p�I�t�Z�b�g
	INT32		m_OfsY;		// �����p�I�t�Z�b�g 
	INT32		m_CutOfsX;		// �J�b�g�p�I�t�Z�b�g
	INT32		m_CutOfsY;		// �J�b�g�p�I�t�Z�b�g 
} CODEDATA,*LPCODEDATA;


extern CODEDATA g_CharCodeData[];


#endif // __charcode_h__

