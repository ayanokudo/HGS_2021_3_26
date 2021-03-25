//===============================================
//
// �l�X�ȏ������܂Ƃ߂��t�@�C�� (library.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "library.h"

//===========================================
// ��ʊO���ǂ���(�񎟌�)
//===========================================
bool OutScreen2D(const D3DXVECTOR3 *pPos, const D3DXVECTOR3 *pSize)
{
    // �ϐ��錾
    bool bOutScreen = false;    // ��ʊO���ǂ���

    // ��ʂ̒[����o�Ă��邩�ǂ���
    if (pPos->x < -(pSize->x / 2) ||
        pPos->x > SCREEN_WIDTH + pSize->x / 2 ||
        pPos->y < -(pSize->y / 2) ||
        pPos->y > SCREEN_HEIGHT + pSize->y / 2)
    {
        // ��ʊO�̃t���O��true��
        bOutScreen = true;
    }

    return bOutScreen;
}

//===========================================
// �Q�[���O���ǂ���(�񎟌�)
//===========================================
bool OutGame2D(const D3DXVECTOR3 * pPos, const D3DXVECTOR3 * pSize)
{
    // �ϐ��錾
    bool bOutGame = false;    // �Q�[���O���ǂ���

    // ��ʂ̒[����2�{�̂Ƃ��납��o�Ă��邩�ǂ���
    if (pPos->x < -SCREEN_WIDTH -(pSize->x / 2) ||
        pPos->x > (SCREEN_WIDTH * 2) + pSize->x / 2 ||
        pPos->y < -SCREEN_HEIGHT -(pSize->y / 2) ||
        pPos->y > (SCREEN_HEIGHT * 2) + pSize->y / 2)
    {
        // �Q�[���O�̃t���O��true��
        bOutGame = true;
    }

    return bOutGame;
}

//===========================================
// ��ʓ��ɂƂǂ܂点��(�񎟌�)
//===========================================
bool SteyInScreen2D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pSize)
{
    // �ϐ��錾
    bool bScreenEdge = false;    // ��ʒ[���ǂ���

    // ��ʂ̍�
    if (pPos->x < pSize->x / 2)
    {
        // �Ƃǂ܂点��
        pPos->x = pSize->x / 2;

        // ��ʒ[�̃t���O��true��
        bScreenEdge = true;
    }

    // ��ʂ̉E
    if (pPos->x > SCREEN_WIDTH - pSize->x / 2)
    {
        // �Ƃǂ܂点��
        pPos->x = SCREEN_WIDTH - pSize->x / 2;

        // ��ʒ[�̃t���O��true��
        bScreenEdge = true;
    }

    // ��ʂ̏�
    if (pPos->y < pSize->y / 2)
    {
        // �Ƃǂ܂点��
        pPos->y = pSize->y / 2;

        // ��ʒ[�̃t���O��true��
        bScreenEdge = true;
    }

    // ��ʂ̉�
    if (pPos->y > SCREEN_HEIGHT - pSize->y / 2)
    {
        // �Ƃǂ܂点��
        pPos->y = SCREEN_HEIGHT - pSize->y / 2;

        // ��ʒ[�̃t���O��true��
        bScreenEdge = true;
    }

    return bScreenEdge;
}

//===========================================
// ��`�̓����蔻��2D
//===========================================
bool RectangleCollision2D(const D3DXVECTOR3 *pPos1, const D3DXVECTOR3*pPos2, const D3DXVECTOR3*pSize1, const D3DXVECTOR3*pSize2)
{
    // �ϐ��錾
    bool bHit = false;    // �����������ǂ���

    // ��̂��̂̓����蔻����v�Z
    if (pPos1->x - pSize1->x / 2 <= pPos2->x + pSize2->x / 2 &&
        pPos1->x + pSize1->x / 2 >= pPos2->x - pSize2->x / 2 &&
        pPos1->y - pSize1->y / 2 <= pPos2->y + pSize2->y / 2 &&
        pPos1->y + pSize1->y / 2 >= pPos2->y - pSize2->y / 2)
    {
        // ���������t���O��true��
        bHit = true;
    }

    return bHit;
}

//===========================================
// ��`�̓����蔻��3D
//===========================================
bool RectangleCollision3D(const D3DXVECTOR3 *pPos1, const D3DXVECTOR3*pPos2, const D3DXVECTOR3*pSize1, const D3DXVECTOR3*pSize2)
{
    // �ϐ��錾
    bool bHit = false;    // �����������ǂ���

    // ��̂��̂̓����蔻����v�Z
    if (pPos1->x - pSize1->x / 2 <= pPos2->x + pSize2->x / 2 &&
        pPos1->x + pSize1->x / 2 >= pPos2->x - pSize2->x / 2 &&
        pPos1->y - pSize1->y / 2 >= pPos2->y + pSize2->y / 2 &&
        pPos1->y + pSize1->y / 2 <= pPos2->y - pSize2->y / 2 &&
        pPos1->z - pSize1->z / 2 <= pPos2->z + pSize2->z / 2 &&
        pPos1->z + pSize1->z / 2 >= pPos2->z - pSize2->z / 2)
    {
        // ���������t���O��true��
        bHit = true;
    }

    return bHit;
}

//===========================================
// �͈͓��ŁA�����_���Ȑ����𓾂�
//===========================================
int GetRandNum(int nMax, int nMin)
{
    int nRandNum = rand() % (nMax - nMin + 1) + nMin;

    return nRandNum;
}