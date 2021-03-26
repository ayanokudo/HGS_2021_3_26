//====================================================================
//
// ���C�g2D�̏��� (light2d.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _LIGHT2D_H_
#define _LIGHT2D_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene2d.h"

//================================================
// �}�N����`
//================================================

#define LIGHT_FIRST_POS D3DXVECTOR3(-400.0f, -400.0f, 0.0f)                 // ���C�g2D�̏����ʒu
#define LIGHT_SIZE D3DXVECTOR3(SCREEN_WIDTH * 4, SCREEN_HEIGHT * 4, 0.0f)   // ���C�g2D�̑傫��
#define LIGHT_SET_COLOR D3DXCOLOR(1.0f,1.0f,1.0f,0.001f)                    // ���C�g2D�̃J���[
#define LIGHT_FADE_OUT_RATE 0.01f                                           // ���C�g2D�ɂ��A�t�F�[�h�A�E�g����
#define LIGHT_CONSIDER_CLOSE_DEST 20.0f                                     // �ړI�̈ʒu�ɋ߂��Ƃ݂Ȃ��l

// �Ƃ炷�ꏊ�Ƃ����ɓ��B���邽�߂̃X�s�[�h
#define LIGHT_SPOT_POS_X_1 300.0f
#define LIGHT_SPOT_POS_Y_1 580.0f
#define LIGHT_SPOT_SPEED_1 10.0f

#define LIGHT_SPOT_POS_X_2 680.0f
#define LIGHT_SPOT_POS_Y_2 180.0f
#define LIGHT_SPOT_SPEED_2 7.5f

#define LIGHT_SPOT_POS_X_3 980.0f
#define LIGHT_SPOT_POS_Y_3 380.0f
#define LIGHT_SPOT_SPEED_3 5.0f

// �{�X�̈ʒu�܂ł̓��B
#define LIGHT_SPOT_SPEED_4 2.5f
#define LIGHT_EXTEND_RATE_X 180.0f  // ���B��̊g��X�i��ʔ� �c:�� = 2:3�j
#define LIGHT_EXTEND_RATE_Y 120.0f  // ���B��̊g��Y�i��ʔ� �c:�� = 2:3�j
#define LIGHT_MAX_SIZE_X 54000.0f   // �������̉摜�́A���ł���������ʂ����邭������Ƃ��̑傫��

//================================================
// �N���X�錾
//================================================

// ���C�g2D�N���X
class CLight2D : public CScene2D
{
public:

    CLight2D();
    ~CLight2D();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static HRESULT Load(void);
    static void Unload(void);
    static CLight2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;   // �ǂݍ��񂾃e�N�X�`����ۑ�����
    D3DXCOLOR m_col;        // �F
    int m_nStage;           // ���C�g���Ƃ炷�i�K
};

#endif