//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : �㓡�T�V��
//
//=============================================================================
#include "result.h"
#include "input.h"
#include "manager.h"
#include "sound.h"
#include "ui.h"
#include "fade.h"
#include "ranking.h"
#include "score.h"
#include "logo.h"
#include "afterimage.h"
#include "enemy.h"

//========================================
// �}�N����`
//========================================

// �e���ʂɁA�J�E���^�𗘗p���ēG��z�u���Ă���
#define ENEMY_5 5
#define ENEMY_4 95
#define ENEMY_3 215
#define ENEMY_2 335
#define ENEMY_1 455
#define STOP 1000       // �J�E���^�̃X�g�b�v

#define SET_POS_X 1400  // �z�u��X���W

//=============================================================================
// ���U���g�̃R���X�g���N�^
//=============================================================================
CResult::CResult()
{
    m_nCntTime = 0;
}

//=============================================================================
// ���U���g�̃f�X�g���N�^
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init(void)
{
    // �w�i�𐶐�
    CLogo::Create(LOGO_BG_POS, LOGO_BG_SIZE, DEFAULT_COLOR, CLogo::TYPE_RESULT_BG);

    // �\��/�f���I���擾
    if (CManager::GetUseHelper() == false)
    {
        // �\��
        CUI::Create(RESULT_POS, RESULT_SIZE, DEFAULT_COLOR, CUI::TYPE_RESULT_SOLO);
    }
    else
    {
        // �f���I
        CUI::Create(RESULT_POS, RESULT_SIZE, DEFAULT_COLOR, CUI::TYPE_RESULT_DUO);
    }

    // �����L���O�𐶐�
    CRanking::Create(RANKING_FIRST_POS, SCORE_SIZE);

    // BGM���Đ�
    CSound *pSound = CManager::GetSound();
    pSound->Play(CSound::LABEL_BGM_RESULT);

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
    // BGM���~
    CSound *pSound = CManager::GetSound();
    pSound->Stop(CSound::LABEL_BGM_RESULT);
}

//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update(void)
{
    // �����L���O�̉��o
    //RankingEffect();

    //�L�[�{�[�h�̊m�ۂ������������擾
    CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

    // �R���g���[�����擾
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();
    DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_1);

    // ����L�[�Ń^�C�g����
    if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START))
    {
        // �t�F�[�h���Ă��Ȃ��Ȃ�
        if (CFade::GetFade() == CFade::FADE_NONE)
        {
            // ���艹�Đ�
            CSound *pSound = CManager::GetSound();
            pSound->Play(CSound::LABEL_SE_DECISION);

            // �^�C�g�����[�h�Ɉڍs
            CFade::SetFade(CManager::MODE_TITLE);
        }
    }
}

//=============================================================================
// �����L���O�̕\�����o
//=============================================================================
void CResult::RankingEffect(void)
{
    // �J�E���^���Z
    m_nCntTime++;

    // �J�E���^�𗘗p���āA�G��z�u
    switch (m_nCntTime)
    {
    case ENEMY_5:

        // 5�ʁA�O�\�N���V
        CAfterimage::Create(D3DXVECTOR3(SET_POS_X, 580.0f, 0.0f), ENEMY_GUSOKU_SIZE,
            0.0f, DEFAULT_COLOR, CAfterimage::TYPE_RANK_GUSOKU);

        break;

    case ENEMY_4:

        // 4�ʁA���J���X
        CAfterimage::Create(D3DXVECTOR3(SET_POS_X, 480.0f, 0.0f), ENEMY_CROW_SIZE,
            0.0f, DEFAULT_COLOR, CAfterimage::TYPE_RANK_CROW);

        break;

    case ENEMY_3:

        // 3�ʁA�Β�
        CAfterimage::Create(D3DXVECTOR3(SET_POS_X, 400.0f, 0.0f), ENEMY_GREEN_BIRD_SIZE,
            0.0f, DEFAULT_COLOR, CAfterimage::TYPE_RANK_GREEN);

        break;

    case ENEMY_2:

        // 2�ʁA��
        CAfterimage::Create(D3DXVECTOR3(SET_POS_X, 300.0f, 0.0f), ENEMY_BLUE_BIRD_SIZE,
            0.0f, DEFAULT_COLOR, CAfterimage::TYPE_RANK_BLUE);

        break;

    case ENEMY_1:

        // 1�ʁA�Ԓ�
        CAfterimage::Create(D3DXVECTOR3(SET_POS_X, 200.0f, 0.0f), ENEMY_RED_BIRD_SIZE,
            0.0f, DEFAULT_COLOR, CAfterimage::TYPE_RANK_RED);

        break;
    }

    // �J�E���^�̃X�g�b�v
    if (m_nCntTime > STOP)
    {
        m_nCntTime = STOP;
    }
}
