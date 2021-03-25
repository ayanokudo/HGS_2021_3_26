//===============================================
//
// �l�X�ȏ������܂Ƃ߂��t�@�C�� [library.h]
// Author : �㓡�T�V��
//
//===============================================
#ifndef _LIBRARY_H_
#define _LIBRARY_H_

//========================
// �C���N���[�h�t�@�C��
//========================
#include "main.h"

//========================
// �}�N����`
//========================

//===========================================
// �v���g�^�C�v�錾
//===========================================
bool OutScreen2D(const D3DXVECTOR3 *pPos, const D3DXVECTOR3 *pSize);
bool OutGame2D(const D3DXVECTOR3 *pPos, const D3DXVECTOR3 *pSize);
bool SteyInScreen2D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pSize);
bool RectangleCollision2D(const D3DXVECTOR3 *pPos1, const D3DXVECTOR3*pPos2, const D3DXVECTOR3*pSize1, const D3DXVECTOR3*pSize2);
bool RectangleCollision3D(const D3DXVECTOR3 *pPos1, const D3DXVECTOR3*pPos2, const D3DXVECTOR3*pSize1, const D3DXVECTOR3*pSize2);
int GetRandNum(int nMax, int nMin);

#endif