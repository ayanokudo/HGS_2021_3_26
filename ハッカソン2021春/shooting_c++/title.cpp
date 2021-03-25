//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : �㓡�T�V��
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "manager.h"
#include "sound.h"
#include "ui.h"
#include "fade.h"
#include "effect.h"
#include "logo.h"

//=============================================================================
// �^�C�g���̃R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
    m_nCntTime = 0;
    m_bNextScene = false;
}

//=============================================================================
// �^�C�g���̃f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(void)
{
    // �w�i�𐶐�
    CLogo::Create(LOGO_BG_POS, LOGO_BG_SIZE, DEFAULT_COLOR, CLogo::TYPE_TITLE_BG);

    // ���S�𐶐�
    CUI::Create(TITLE_LOGO_FIRST_POS, TITLE_LOGO_SIZE, DEFAULT_COLOR, CUI::TYPE_TITLE_LOGO);

    // �v���X�X�^�[�g
    CUI::Create(PRESS_START_POS, PRESS_START_SIZE, DEFAULT_COLOR, CUI::TYPE_PRESS_START);

    // BGM���Đ�
    CSound *pSound = CManager::GetSound();
    pSound->Play(CSound::LABEL_BGM_TITLE);

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
    // �^�C�g���̎��Ԃ��J�E���g
    m_nCntTime++;

    // �^�C�g���̍ő厞��
    if (m_nCntTime > TITLE_MAX_TIME)
    {
        m_nCntTime = TITLE_MAX_TIME;
    }

    //�L�[�{�[�h�̊m�ۂ������������擾
    CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

    // �R���g���[�����擾
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();
    DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_1);

    // �J�ڂ̃t���O��true�Ȃ�
    if (m_bNextScene == true)
    {
        // �G���^�[�A�܂��̓X�^�[�g�{�^������������
        if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START))
        {
            // �t�F�[�h���Ă��Ȃ��Ȃ�
            if (CFade::GetFade() == CFade::FADE_NONE)
            {
                // ���艹�Đ�
                CSound *pSound = CManager::GetSound();
                pSound->Play(CSound::LABEL_SE_DECISION);

                // �V�ѕ����[�h�Ɉڍs
                CFade::SetFade(CManager::MODE_MANUAL);
            }
        }
    }
    // �J�ڂ̃t���O��false�Ȃ�
    else
    {
        // ��莞�Ԍo�߂őJ�ډ\��
        if (m_nCntTime >= TITLE_NEXT_SCENE)
        {
            m_bNextScene = true;
        }
        // ��莞�Ԍo�߂��Ă��Ȃ��Ă�
        else
        {
            // �G���^�[�A�܂��̓X�^�[�g�{�^������������
            if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START))
            {
                // �J�ډ\��
                m_bNextScene = true;
            }
        }
    }

    // ���𐶐�����ʒu
    D3DXVECTOR3 pos = DEFAULT_VECTOR;
    float fAngle = 0.0f;
    float fRadius = 0.0f;
    float fSize = 0.0f;
    D3DXCOLOR color = DEFAULT_COLOR;

    // �Ԃ���
    //==========================================================================================
    // �G�t�F�N�g�p�ɁA�p�x�Ɣ��a�����߂�
    fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
    fRadius = float(rand() % 1000) / 100.0f;
    fSize = float(rand() % 7500 + 2500) / 100.0f;

    // �ʒu�𔽉f
    pos = D3DXVECTOR3(EFFECT_RED_FIRE_POS_X -sinf(fAngle)*fRadius, EFFECT_RED_FIRE_POS_Y - cosf(fAngle)*fRadius, 0.0f);

    if (fSize >= EFFECT_RED_FIRE_OVER_SIZE)
    {
        color = EFFECT_RED_FIRE_RED;
    }
    else
    {
        color = EFFECT_RED_FIRE_FIRST_COLOR;
    }

    // ���𐶐�
    CEffect::Create(pos, D3DXVECTOR3(fSize, fSize, 0.0f), color, CEffect::TYPE_RED_FIRE);
    //===========================================================================================


    // ����
    //==========================================================================================
    // �G�t�F�N�g�p�ɁA�p�x�Ɣ��a�����߂�
    fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
    fRadius = float(rand() % 1000) / 100.0f;
    fSize = float(rand() % 7500 + 2500) / 100.0f;

    // �ʒu�𔽉f
    pos = D3DXVECTOR3(EFFECT_BLUE_FIRE_POS_X - sinf(fAngle)*fRadius, EFFECT_BLUE_FIRE_POS_Y - cosf(fAngle)*fRadius, 0.0f);

    if (fSize >= EFFECT_BLUE_FIRE_OVER_SIZE)
    {
        color = EFFECT_BLUE_FIRE_BLUE;
    }
    else
    {
        color = EFFECT_BLUE_FIRE_FIRST_COLOR;
    }

    // ���𐶐�
    CEffect::Create(pos, D3DXVECTOR3(fSize, fSize, 0.0f), color, CEffect::TYPE_BLUE_FIRE);
    //===========================================================================================


    // ���F����
    //==========================================================================================
    // �G�t�F�N�g�p�ɁA�p�x�Ɣ��a�����߂�
    fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
    fRadius = float(rand() % 1000) / 100.0f;
    fSize = float(rand() % 7500 + 2500) / 100.0f;

    // �ʒu�𔽉f
    pos = D3DXVECTOR3(EFFECT_YELLOW_FIRE_POS_X - sinf(fAngle)*fRadius, EFFECT_YELLOW_FIRE_POS_Y - cosf(fAngle)*fRadius, 0.0f);

    if (fSize >= EFFECT_YELLOW_FIRE_OVER_SIZE)
    {
        color = EFFECT_YELLOW_FIRE_GREEN;
    }
    else
    {
        color = EFFECT_YELLOW_FIRE_FIRST_COLOR;
    }

    // ���𐶐�
    CEffect::Create(pos, D3DXVECTOR3(fSize, fSize, 0.0f), color, CEffect::TYPE_YELLOW_FIRE);
    //===========================================================================================
}
