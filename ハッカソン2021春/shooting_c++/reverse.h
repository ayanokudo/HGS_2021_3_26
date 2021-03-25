//====================================================================
//
// ���]�����̏��� (reverse.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _REVERSE_H_
#define _REVERSE_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene2d.h"

//================================================
// �}�N����`
//================================================

#define REVERSE_MAX_SIZE 7000.0f            // �ő�T�C�Y
#define REVERSE_EXTEND_RATE 10.0f            // �g�劄��
#define REVERSE_FADE_OUT_RATE 0.01f         // ���]�����̃t�F�[�h�A�E�g����

//================================================
// �N���X�錾
//================================================

// ���]�����N���X
class CReverse : public CScene2D
{
public:
    CReverse();
    ~CReverse();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static HRESULT Load(void);
    static void Unload(void);
    static CReverse *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;   // �ǂݍ��񂾃e�N�X�`����ۑ�����
    D3DXVECTOR3 m_move;     // �ړ���
    D3DXCOLOR m_col;        // �F
};

#endif