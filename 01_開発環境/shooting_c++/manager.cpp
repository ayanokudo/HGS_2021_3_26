//===============================================
//
// �����̊Ǘ����� (manager.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "manager.h"
#include "scene2d.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "player.h"
#include "bullet.h"
#include "effect.h"
#include "enemy.h"
#include "bg.h"
#include "number.h"
#include "score.h"
#include "ui.h"
#include "item.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "manual.h"
#include <typeinfo.h>
#include "block.h"
#include "afterimage.h"
#include "whiteFade.h"
#include "bubble.h"
#include "reverse.h"
#include "fade.h"
#include "light2d.h"
#include "pause.h"
#include "wave.h"
#include "helper.h"
#include "foreground.h"
#include "logo.h"

//========================================
// �ÓI�����o�ϐ��錾
//========================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputJoypad *CManager::m_pInputJoypad = NULL;
CSound *CManager::m_pSound = NULL;
CMode *CManager::m_pMode = NULL;
CFade *CManager::m_pFade = NULL;

int CManager::m_nScore = 0;
bool CManager::m_bUseHelper = false;
CManager::STAGE CManager::m_stage = STAGE_��;

//========================================
// �����̊Ǘ��̃f�t�H���g�R���X�g���N�^
//========================================
CManager::CManager()
{

}

//========================================
// �����̊Ǘ��̃f�X�g���N�^
//========================================
CManager::~CManager()
{

}

//========================================
// �����̊Ǘ��̏���������
//========================================
HRESULT CManager::Init(HINSTANCE hInstance , HWND hWnd, BOOL bWindow)
{
    // �����_���[�̐���(��񂵂��������Ȃ����̂́ACreate��p�ӂ��Ă��Ȃ�)
    m_pRenderer = new CRenderer;

    // �����_���[����������
    if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
    {
        return E_FAIL;
    }

    // �L�[�{�[�h�̐���(new��Init�͘A�������ď���)
    m_pInputKeyboard = new CInputKeyboard;

    // �L�[�{�[�h�̏���������
    if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
    {
        return E_FAIL;
    }

    // �R���g���[���̐���
    m_pInputJoypad = new CInputJoypad;

    // �R���g���[���̏���������
    if (FAILED(m_pInputJoypad->Init(hInstance, hWnd)))
    {
        return E_FAIL;
    }

    // �T�E���h�̐���
    m_pSound = new CSound;
    if (FAILED(m_pSound->Init(hWnd)))
    {
        return E_FAIL;
    }

    // �t�F�[�h�̐���
    m_pFade = CFade::Create(MODE_TITLE);    // �ŏ��̓^�C�g��

    // �e�N�X�`���̃��[�h
    CPlayer::Load();
    CBullet::Load();
    CEffect::Load();
    CEnemy::Load();
    CBg::Load();
    CNumber::Load();
    CUI::Load();
    CItem::Load();
    CBlock::Load();
    CAfterimage::Load();
    CWhiteFade::Load();
    CBubble::Load();
    CReverse::Load();
    CLight2D::Load();
    CPause::Load();
    CWave::Load();
    CHelper::Load();
    CForeground::Load();
    CLogo::Load();

    return S_OK;
}

//========================================
// �����̊Ǘ��̏I������
//========================================
void CManager::Uninit(void)
{
    // �S�ẴI�u�W�F�N�g��j��
    CScene::ReleaseAll();

    // �e�N�X�`���̃A�����[�h
    CPlayer::Unload();
    CBullet::Unload();
    CEffect::Unload();
    CEnemy::Unload();
    CBg::Unload();
    CNumber::Unload();
    CUI::Unload();
    CItem::Unload();
    CBlock::Unload();
    CAfterimage::Unload();
    CWhiteFade::Unload();
    CBubble::Unload();
    CReverse::Unload();
    CLight2D::Unload();
    CPause::Unload();
    CWave::Unload();
    CHelper::Unload();
    CForeground::Unload();
    CLogo::Unload();

    // ���[�h�j��
    if (m_pMode != NULL)
    {
        // ���[�h�̏I������
        m_pMode->Uninit();

        // ���[�h�̃������̊J��
        delete m_pMode;
        m_pMode = NULL;
    }

    // �t�F�[�h�j��
    if (m_pFade != NULL)
    {
        // �t�F�[�h�̏I������
        m_pFade->Uninit();

        // �t�F�[�h�̃������̊J��
        delete m_pFade;
        m_pFade = NULL;
    }

    // �T�E���h�j��
    if (m_pSound != NULL)
    {
        // �T�E���h�I������
        m_pSound->Uninit();

        // �T�E���h�̃������̊J��
        delete m_pSound;
        m_pSound = NULL;
    }

    // �R���g���[���j��
    if (m_pInputJoypad != NULL)
    {
        // �R���g���[���I������
        m_pInputJoypad->Uninit();

        // �R���g���[���̃������̊J��
        delete m_pInputJoypad;
        m_pInputJoypad = NULL;
    }

    // �L�[�{�[�h�j���iInit�Ő��������t���Ŕj������j
    if (m_pInputKeyboard != NULL)
    {
        // �L�[�{�[�h�I������
        m_pInputKeyboard->Uninit();

        // �L�[�{�[�h�̃������̊J��
        delete m_pInputKeyboard;
        m_pInputKeyboard = NULL;
    }

    // �����_���[�j��
    if (m_pRenderer != NULL)
    {
        // �����_���[�I������
        m_pRenderer->Uninit();

        // �����_���[�̃������̊J��
        delete m_pRenderer;
        m_pRenderer = NULL;
    }
}

//========================================
// �����̊Ǘ��̍X�V����
//========================================
void CManager::Update(void)
{
    // �L�[�{�[�h�X�V����(�ŏ��ɍs��)
    if (m_pInputKeyboard != NULL)
    {
        m_pInputKeyboard->Update();
    }

    // �R���g���[���X�V����
    if (m_pInputJoypad != NULL)
    {
        m_pInputJoypad->Update();
    }

    // �����_���[�X�V����
    if (m_pRenderer != NULL)
    {
        // ���[�h������Ȃ�
        if (m_pMode != NULL)
        {
            // �Q�[�����Ȃ�
            if (typeid(*m_pMode) == typeid(CGame))
            {
                // �ʏ�Ȃ�i�|�[�Y�łȂ��Ȃ�j
                if (CGame::GetState() == CGame::STATE_NORMAL)
                {
                    // �S�čX�V
                    m_pRenderer->Update();
                }
            }
            else
            {
                // �Q�[���ȊO�̏�ʂȂ�A��ɑS�čX�V
                m_pRenderer->Update();
            }
        }
    }

    // ���[�h�̍X�V����
    if (m_pMode != NULL)
    {
        m_pMode->Update();
    }

    // �t�F�[�h�̍X�V����
    if (m_pFade != NULL)
    {
        m_pFade->Update();
    }
}

//========================================
// �����̊Ǘ��̕`�揈��
//========================================
void CManager::Draw(void)
{
    // �`�揈��
    m_pRenderer->Draw();
}

//========================================
// ���[�h�̎擾
//========================================
CManager::MODE CManager::GetMode(void)
{
    // �Ԃ�l�Ɏg�����[�h
    MODE mode = MODE_NONE;

    // ���̃��[�h�������Ă��邩���āA�^�����Ƃɏꍇ����
    if (typeid(*m_pMode) == typeid(CTitle))
    {
        mode = MODE_TITLE;
    }
    else if (typeid(*m_pMode) == typeid(CManual))
    {
        mode = MODE_MANUAL;
    }
    else if (typeid(*m_pMode) == typeid(CGame))
    {
        mode = MODE_GAME;
    }
    else if (typeid(*m_pMode) == typeid(CResult))
    {
        mode = MODE_RESULT;
    }

    return mode;
}

//========================================
// ���[�h�̐ݒ�
// mode	:	�ݒ肷�郂�[�h
//========================================
void CManager::SetMode(MODE mode)
{
    // ���[�h�̒��g������Ȃ�
    if (m_pMode != NULL)
    {
        // �I������
        m_pMode->Uninit();

        // �������̔j��
        delete m_pMode;
        m_pMode = NULL;
    }

    // �V�[����̃I�u�W�F�N�g��S�ďI������
    CScene::ReleaseAll();

    // �󂯎�������[�h�ɉ�ʑJ��
    switch (mode)
    {
    case MODE_TITLE:
        m_pMode = new CTitle;
        break;

    case MODE_MANUAL:
        m_pMode = new CManual;
        break;

    case MODE_GAME:
        m_pMode = new CGame;
        break;

    case MODE_RESULT:
        m_pMode = new CResult;;
        break;
    }

    // �m�ۂ������[�h�̏�����
    m_pMode->Init();
}