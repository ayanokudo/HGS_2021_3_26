//====================================================================
//
// �w�i���� (bg.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _BG_H_
#define _BG_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene.h"

//================================================
// �O���錾(�s���S�ȃN���X�́Acpp�̕��Ńw�b�_���Ăяo��)
//================================================
class CScene2D;

//================================================
// �}�N����`
//================================================

#define SCROLL_FIRST_SPEED 500
#define SCROLL_VALUE 200.0f

//================================================
// �N���X�錾
//================================================

// �w�i�N���X
class CBg : public CScene
{
public:

    // �w�i�̃Z�b�g
    typedef enum
    {
        SET_NONE = 0,   // �Ȃ�
        SET_A,          // ��
        SET_B,          // ��
        SET_C ,         // ��
        SET_MAX         // �Z�b�g�̍ő吔
    }SET;

    // �w�i�̎��
    typedef enum
    {
        TYPE_SKY = 0,   // ��
        TYPE_MOUNTAIN,  // �R
        TYPE_WOODS,     // ��
        TYPE_FOREST,    // �X�i�{�X�̂���j
        TYPE_SAND,      // ��
        TYPE_OCEAN,     // �C
        TYPE_ROCKS,     // ��
        TYPE_FISHES,    // ���Q
        TYPE_DEAD_END,  // �s���~�܂�
        TYPE_RED_SKY,   // �Ԃ���
        TYPE_RED_GROUND,// �Ԃ��n��
        TYPE_VOLCANO,   // �ΎR
        TYPE_THE_TOP,   // ����
        TYPE_MAX        // �w�i�̍ő吔
    }TYPE;

    CBg();
    ~CBg();
    static HRESULT Load(void);
    static void Unload(void);
    static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, SET set);
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static void Shake(int nCntState) { m_bShake = true; m_nCntState = nCntState; }  // �󂯎�������h�炷
    static void EraseForest(void) { m_bEraseForest = true; }                        // �{�X�X������

    static bool GetInTheSky(void) { return m_bInTheSky; }                           // ��̒��ɂ��邩�ǂ�����Ԃ�

    static float GetScrollSpeed(void) { return (float)m_nScrollSpeed / SCROLL_VALUE; }

    void direct(void);

private:
    static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];   // �e�N�X�`���ւ̃|�C���^
    CScene2D *m_apScene2D[MAX_POLYGON];                // 2D�|���S���ւ̃|�C���^
    D3DXCOLOR m_col;                                   // �F
    SET m_set;                                         // �`�悷����̂̃Z�b�g
    int m_nCntTime;                                    // ���Ԃ��J�E���g

    static bool m_bShake;                              // �h�炷���ǂ���
    static int m_nCntState;                            // ��ԃJ�E���^
    static bool m_bEraseForest;                        // �X���������ǂ���

    static bool m_bInTheSky;                           // ��̒����ǂ���

    static int m_nScrollSpeed;                        // �X�N���[������
};

#endif