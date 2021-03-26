//====================================================================
//
// ���S�̏��� (logo.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene2d.h"

//================================================
// �}�N����`
//================================================
#define LOGO_BG_POS (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))   // �w�i���S�̈ʒu
#define LOGO_BG_SIZE (D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f))          // �w�i���S�̑傫��

//================================================
// �N���X�錾
//================================================

// ���S�N���X
class CLogo : public CScene2D
{
public:
    // ���S�̎��
    typedef enum
    {
        TYPE_TITLE_BG,          // �^�C�g���̔w�i
        TYPE_RESULT_BG,         // ���U���g�̔w�i
        TYPE_MAX			    // ��ނ̍ő吔
    }TYPE;
    CLogo();
    ~CLogo();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static HRESULT Load(void);
    static void Unload(void);
    static CLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type);

private:
    static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];   // �ǂݍ��񂾃e�N�X�`����ۑ�����
    D3DXCOLOR m_col;    // �F
    TYPE m_type;        // ���S�̎��
};

#endif