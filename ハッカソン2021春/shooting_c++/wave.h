//====================================================================
//
// �g�̏��� (wave.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _WAVE_H_
#define _WAVE_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene2d.h"

//================================================
// �}�N����`
//================================================
#define WAVE_FADE_RATE (0.025f)                                             // �g�̃t�F�[�h�A�E�g����
#define WAVE_EXTEND_RATE 0.5f                                               // �g�̊g��k��
#define WAVE_FADE_RATE2 (0.02f)                                             // �g�̃t�F�[�h�A�E�g����
#define WAVE_EXTEND_RATE2 1.0f                                              // �g�̊g��k��
#define WAVE_MIN_COLOR 0.3f                                                 // �g�̍ŏ��̐F
#define WAVE_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.375f))                    // �g�̐F
#define WAVE_COLOR2 (D3DXCOLOR(WAVE_MIN_COLOR, WAVE_MIN_COLOR, 1.0f, 0.35f))// �g�̐F2
#define WAVE_POS (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))   // �g�̈ʒu
#define WAVE_MIN_SIZE 1000.0f                                               // �g�̍ŏ��̑傫��
#define WAVE_SIZE (D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f))          // �g�̑傫��
#define WAVE_SIZE2 (D3DXVECTOR3(SCREEN_WIDTH, WAVE_MIN_SIZE, 0.0f))         // �g�̑傫��2

//================================================
// �N���X�錾
//================================================

// �g�N���X
class CWave : public CScene2D
{
public:
    // �g�̎��
    typedef enum
    {
        TYPE_BIG_WAVE,          // �傫���g
        TYPE_BIG_WAVE2,         // �傫���g2
        TYPE_MAX			    // ��ނ̍ő吔
    }TYPE;
    CWave();
    ~CWave();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static HRESULT Load(void);
    static void Unload(void);
    static CWave *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type);

private:
    static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];   // �ǂݍ��񂾃e�N�X�`����ۑ�����
    bool m_bExtend;     // �g��k���̃t���O
    bool m_bToBlue;     // �ɋ߂Â���t���O
    D3DXVECTOR3 m_move; // �ړ���
    D3DXCOLOR m_col;    // �F
    TYPE m_type;        // �g�̎��
};

#endif