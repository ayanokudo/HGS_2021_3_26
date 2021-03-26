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
    CForeground();
    ~CForeground();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static HRESULT Load(void);
    static void Unload(void);
    static CForeground *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type);

private:
    static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];   // �ǂݍ��񂾃e�N�X�`����ۑ�����
    D3DXCOLOR m_col;    // �F
    TYPE m_type;        // �O�i�̎��
};

#endif