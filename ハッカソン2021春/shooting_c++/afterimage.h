//====================================================================
//
// �c���̏��� (afterimage.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _AFTERIMAGE_H_
#define _AFTERIMAGE_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene2d.h"
#include "player.h"

//================================================
// �}�N����`
//================================================
#define AFTERIMAGE_PLAYER_FADE_RATE (0.07f)                              // �v���C���[�̎c���̃t�F�[�h�A�E�g����
#define AFTERIMAGE_PLAYER_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f))      // �v���C���[�̎c���̐F

#define AFTERIMAGE_PLAYER_DISP_POS (D3DXVECTOR3(-100.0f, PLAYER_START_POS_Y, 0.0f))     // �v���C���[�̔z�u�ʒu

#define AFTERIMAGE_BOSS_FADE_RATE (0.002f)                                       // �{�X�̎c���̃t�F�[�h�A�E�g����
#define AFTERIMAGE_BOSS_RADIUS (25000)                                           // �{�X�̔��a
#define AFTERIMAGE_BOSS_SET_EFFECT (15)                                          // �{�X�̃G�t�F�N�g���Z�b�g����J�E���^
#define AFTERIMAGE_BOSS_EXPLOSION_SIZE (D3DXVECTOR3(250.0f, 250.0f, 0.0f))       // �{�X�̔����G�t�F�N�g�T�C�Y

#define MAGIC_EXTEND_RATE 20.0f                                          // �_�ʗ͂̊g�劄��
#define MAGIC_FADE_OUT_RATE 0.05f                                        // �_�ʗ͂̃t�F�[�h�A�E�g����

#define AFTERIMAGE_RANKING_FADE_OUT_POS_X -250.0f                        // �����L���O��ʂŁA�c����������X���W

//================================================
// �N���X�錾
//================================================

// �c���N���X
class CAfterimage : public CScene2D
{
public:
    // �c���̎��
    typedef enum
    {
        TYPE_PLAYER = 0,        // �v���C���[
        TYPE_PLAYER_DISP,       // �v���C���[�z�u
        TYPE_BOSS_FOREST,	    // �{�X�X
        TYPE_BOSS_DRAGON,	    // �{�X�h���S��
        TYPE_BOSS_BLAZE,        // �{�X�u���C�Y
        TYPE_GOD_BIRD,          // �S�b�h�o�[�h
        TYPE_MAGIC,             // �_�ʗ�
        TYPE_RANK_GUSOKU,       // �����L���O�̃O�\�N���V
        TYPE_RANK_CROW,         // �����L���O�̔��J���X
        TYPE_RANK_GREEN,        // �����L���O�̗Β�
        TYPE_RANK_BLUE,         // �����L���O�̐�
        TYPE_RANK_RED,          // �����L���O�̐Ԓ�
        TYPE_MAX			    // ��ނ̍ő吔
    }TYPE;
    CAfterimage();
    ~CAfterimage();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static HRESULT Load(void);
    static void Unload(void);
    static CAfterimage *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fAngle, D3DXCOLOR col, TYPE type);

    void RankingFadeOut(D3DXVECTOR3 pos);   // �����L���O��ʂŁA�����鉉�o

private:
    static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];   // �ǂݍ��񂾃e�N�X�`����ۑ�����
    int m_nCntTime;     // �J�E���^
    float m_fAngle;     // �p�x
    D3DXVECTOR3 m_move; // �ړ���
    D3DXCOLOR m_col;    // �F
    TYPE m_type;        // �c���̎��
};

#endif