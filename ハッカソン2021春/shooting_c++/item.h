//====================================================================
//
// �A�C�e���̏��� (item.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene2d.h"

//================================================
// �}�N����`
//================================================
#define ITEM_SIZE D3DXVECTOR3(55.0f, 55.0f, 0.0f)	 // �A�C�e���̃T�C�Y
#define ITEM_SPEED 5.0f                              // �A�C�e���̑���
#define ITEM_FLOWING_SPEED 2.5f                      // �A�C�e���̗���鑬��
#define ITEM_ROT_ANGLE 0.05f                         // �A�C�e���������p�x

#define ITEM_EFFECT_ADD_SIZE D3DXVECTOR3(50.0f, 50.0f, 0.0f)// �A�C�e���̃G�t�F�N�g�̒ǉ��T�C�Y
#define BARRIER_COLOR D3DXCOLOR(0.2f, 0.858f, 0.98f, 1.0f)  // �o���A�̐F
#define STOCK_COLOR D3DXCOLOR(1.0f, 0.262f, 0.447f, 1.0f)   // �X�g�b�N�̐F

//================================================
// �N���X�錾
//================================================

// �A�C�e���N���X
class CItem : public CScene2D
{
public:
    // �A�C�e���̎��
    typedef enum
    {
        TYPE_BARRIER,   // �o���A
        TYPE_STOCK,     // �n�[�g
        TYPE_MAX        // ��ނ̍ő吔
    }TYPE;
    CItem();
    ~CItem();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static HRESULT Load(void);
    static void Unload(void);
    static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);
    TYPE GetType(void) { return m_type; }   // �^�C�v���擾

private:
    static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];   // �ǂݍ��񂾃e�N�X�`����ۑ�����
    TYPE m_type;        // �A�C�e���̎��
    float m_fAngle;     // �p�x
    D3DXVECTOR3 m_move; // �ړ���
};

#endif