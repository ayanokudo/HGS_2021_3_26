//====================================================================
//
// �O�i�̏��� (foreground.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _FOREGROUND_H_
#define _FOREGROUND_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene2d.h"

//================================================
// �}�N����`
//================================================
#define FOREGROUND_FOREST_FADE_RATE (0.1f)                                                // �X�̑O�i�̃t�F�[�h�A�E�g����
#define FOREGROUND_FOREST_POS (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT,0.0f))         // �X�̑O�i�̈ʒu
#define FOREGROUND_FOREST_SIZE (D3DXVECTOR3(SCREEN_WIDTH, 350.0f,0.0f))                   // �X�̑O�i�̑傫��
#define FOREGROUND_FOREST_FLOWING_SPEED 175                                               // �X�̑O�i�̗���鑬�x

#define FOREGROUND_CORAL_POS  (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 120.0f,0.0f))// �T���S�̑O�i�̈ʒu
#define FOREGROUND_CORAL_SIZE (D3DXVECTOR3(SCREEN_WIDTH + 250.0f, 250.0f,0.0f))           // �T���S�̑O�i�̑傫��
#define FOREGROUND_CORAL_FLOWING_SPEED 400                                                // �T���S�̑O�i�̗���鑬�x

//================================================
// �N���X�錾
//================================================

// �O�i�N���X
class CForeground : public CScene2D
{
public:
    // �O�i�̎��
    typedef enum
    {
        TYPE_FOREST,          // �X
        TYPE_CORAL,           // �T���S
        TYPE_MAX			  // ��ނ̍ő吔
    }TYPE;

    // �O�i�̎��
    typedef enum
    {
        SCROLL_1,          // �X
        SCROLL_2,           // �T���S
        SCROLL_3			  // ��ނ̍ő吔
    }SCROLL;

    // �O�i�̎��
    typedef enum
    {
        DIRECT_RIGHT,          // �E
        DIRECT_LEFT,           // ��
    }DIRECT;

    CForeground();
    ~CForeground();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static HRESULT Load(void);
    static void Unload(void);
    static CForeground *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type);

    void Forest(void);

    static DIRECT GetDirect1(void) { return direct1; }
    static DIRECT GetDirect2(void) { return direct2; }
    static DIRECT GetDirect3(void) { return direct3; }

private:
    static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];   // �ǂݍ��񂾃e�N�X�`����ۑ�����
    D3DXCOLOR m_col;    // �F
    TYPE m_type;        // �O�i�̎��

    SCROLL m_scroll;
    int m_nSelectCoolTime;

    static DIRECT direct1;
    static DIRECT direct2;
    static DIRECT direct3;
};

#endif