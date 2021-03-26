//====================================================================
//
// �A�̏��� (bubble.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _BUBBLE_H_
#define _BUBBLE_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene2d.h"

//================================================
// �}�N����`
//================================================

#define BUBBLE_MINIMUM_SIZE D3DXVECTOR3(10.0f, 10.0f, 0.0f)        // �ɏ��̑傫��
#define BUBBLE_SMALL_SIZE D3DXVECTOR3(15.0f, 15.0f, 0.0f)          // ���̑傫��
#define BUBBLE_NORMAL_SIZE D3DXVECTOR3(20.0f, 20.0f, 0.0f)         // �ʏ�̑傫��
#define BUBBLE_NORMAL2_SIZE D3DXVECTOR3(25.0f, 25.0f, 0.0f)        // �ʏ�̑傫��2
#define BUBBLE_BIG_SIZE D3DXVECTOR3(30.0f, 30.0f, 0.0f)            // ��̑傫��
#define BUBBLE_MAXIMUM_SIZE D3DXVECTOR3(35.0f, 35.0f, 0.0f)        // �ɑ�̑傫��

#define BUBBLE_MINIMUM_MOVE D3DXVECTOR3(7.5f, -7.5f, 0.0f)        // �ɏ��̓���
#define BUBBLE_SMALL_MOVE D3DXVECTOR3(-8.0f, -8.0f, 0.0f)         // ���̓���
#define BUBBLE_NORMAL_MOVE D3DXVECTOR3(8.5f, -8.5f, 0.0f)         // �ʏ�̓���
#define BUBBLE_NORMAL2_MOVE D3DXVECTOR3(-9.0f, -9.0f, 0.0f)       // �ʏ�̓���2
#define BUBBLE_BIG_MOVE D3DXVECTOR3(9.5f, -9.5f, 0.0f)            // ��̓���
#define BUBBLE_MAXIMUM_MOVE D3DXVECTOR3(-10.0f, -10.0f, 0.0f)     // �ɑ�̓���

#define BUBBLE_COLOR D3DXCOLOR(1.0f,1.0f,1.0f,0.55f)            // �A�̃J���[
#define BUBBLE_FADE_OUT_RATE 0.01f                              // �A�̃t�F�[�h�A�E�g����
#define BUBBLE_RETURN_POS (13.0f)                               // �A�̒��˕Ԃ�ʒu

//================================================
// �N���X�錾
//================================================

// �A�N���X
class CBubble : public CScene2D
{
public:
    // �A�̎��
    typedef enum
    {
        TYPE_MINIMUM = 0,	// �ɏ�
        TYPE_SMALL,         // ��
        TYPE_NORMAL,        // �ʏ�
        TYPE_NORMAL2,       // �ʏ�2
        TYPE_BIG,           // ��
        TYPE_MAXIMUM,       // �ɑ�
        TYPE_MAX			// ��ނ̍ő吔
    }TYPE;
    CBubble();
    ~CBubble();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static HRESULT Load(void);
    static void Unload(void);
    static CBubble *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;   // �ǂݍ��񂾃e�N�X�`����ۑ�����
    D3DXVECTOR3 m_move;     // �ړ���
    D3DXVECTOR3 m_posSet;   // �Z�b�g�ʒu���L��
    D3DXCOLOR m_col;        // �F
    TYPE m_type;            // �A�̎��
};

#endif