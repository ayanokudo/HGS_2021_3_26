//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : �㓡�T�V��
//
//=============================================================================
#include "game.h"
#include <time.h>
#include "manager.h"
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
#include "bubble.h"
#include "block.h"
#include "afterimage.h"
#include "fade.h"
#include "light2d.h"
#include "pause.h"
#include "input.h"
#include "wave.h"
#include "helper.h"
#include "foreground.h"
#include "library.h"

//========================================
// �}�N����`
//========================================

// �E�F�[�u�̃J�E���^
#define STAGE_WAVE_STOP 10007           // �A�≊�Ŋ���؂�Ȃ��悤��(�f��)

// �X�e�[�W1
#define STAGE1_START 2
#define STAGE1_WAVE1 200
#define STAGE1_WAVE2 560
#define STAGE1_WAVE3 860
#define STAGE1_WAVE4 1500
#define STAGE1_WAVE5 2200
#define STAGE1_WAVE6 3000
#define STAGE1_WAVE_BOSS_START 3500 // ���[�j���O�J�n
#define STAGE1_WAVE_SET_FLOOR 3800  // ���ƃ{�X�̉��y�ƒ��ӕ\�L
#define STAGE1_WAVE_BLUE_BIRD 4500  // ����

// �X�e�[�W2
#define STAGE2_START 90
#define STAGE2_SET_BUBBLE_COUNT 20  // �A�𐶐�����J�E���^
#define STAGE2_WAVE1 200
#define STAGE2_WAVE2 500
#define STAGE2_WAVE3 920
#define STAGE2_WAVE4 1340
#define STAGE2_WAVE5 1760
#define STAGE2_WAVE6 2120
#define STAGE2_WAVE7 2520
#define STAGE2_WAVE8 3300
#define STAGE2_WAVE_BOSS_START 3700     // ���[�j���O�J�n
#define STAGE2_WAVE_DARKENING 3800      // �Ó]
#define STAGE2_WAVE_BOSS_SET 3820       // �{�X����
#define STAGE2_WAVE_STOP_FLOWING 3945   // �w�i�̗�����~�߂�
#define STAGE2_WAVE_PLAY_SOUND 4080     // �{�X�̉��y
#define STAGE2_WAVE_LIGHTNING 4200      // ���邭�Ȃ�

// �X�e�[�W3
#define STAGE3_START 90
#define STAGE3_SET_FIRE_COUNT 2         // ���𐶐�����J�E���^
#define STAGE3_SET_MAGMA_COUNT 2        // �}�O�}�𐶐�����
#define STAGE3_SET_CLOUD_COUNT 45       // �_�𐶐�����J�E���^
#define STAGE3_SET_CLOUD_COUNT_BOSS 75  // �{�X�펞�A�_�𐶐�����J�E���^
#define STAGE3_WAVE1 360
#define STAGE3_WAVE2 480
#define STAGE3_WAVE2_DANGER 700         // ���̒��̌x��
#define STAGE3_WAVE3 1200
#define STAGE3_WAVE4 1680
#define STAGE3_WAVE5 1980
#define STAGE3_WAVE6_DANGER 2205        // �R�E�����̐���̌x��
#define STAGE3_WAVE6 2400
#define STAGE3_WAVE7 2730
#define STAGE3_TAKE_OFF 2850            // ��ɔ�ї��t���[��(bg.cpp�ƒ���)
#define STAGE3_SET_CLOUD_START 2940     // �_��ݒu���n�߂�J�E���^
#define STAGE3_WAVE8 2970
#define STAGE3_WAVE9 3970
#define STAGE3_WAVE10 4570
#define STAGE3_WAVE_END_SKY_MODE 4850   // �󃂁[�h�̏I��
#define STAGE3_WAVE_BOSS_START 5420     // ���[�j���O�J�n
#define STAGE3_WAVE_PLAY_SOUND 5780     // �{�X�̉��y�J�n
#define STAGE3_WAVE_SET_FLOOR 5870      // ���̔����ݒ�

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CScore *CGame::m_pScore = NULL;
CPlayer *CGame::m_pPlayer = NULL;
CHelper *CGame::m_pHelper = NULL;
CPause *CGame::m_pPause = NULL;
CGame::STATE CGame::m_state = STATE_NORMAL;
CManager::STAGE CGame::m_stage = CManager::STAGE_NONE;
int CGame::m_nStock = PLAYER_START_STOCK;
int CGame::m_nCntGameTime = 0;
bool CGame::m_bCreatePlayer = false;
bool CGame::m_bDispPlayer = true;
bool CGame::m_bBossBattle = false;
bool CGame::m_bFloor = false;
bool CGame::m_bInvinciblePlayer = false;
bool CGame::m_bMovePlayer = true;
bool CGame::m_bShockPlayer = false;
bool CGame::m_bDarkening = false;
bool CGame::m_bCreateHelper = false;
bool CGame::m_bGameClear = false;
int CGame::m_nCntFinishGame = 0;
bool CGame::m_bFinishGame = false;

//=============================================================================
// �Q�[���̃R���X�g���N�^
//=============================================================================
CGame::CGame()
{
    m_nStock = PLAYER_START_STOCK;
    m_bCreatePlayer = false;
    m_bDispPlayer = true;   // �ŏ��̓v���C���[������
    m_pScore = NULL;
    m_pPlayer = NULL;
    m_pHelper = NULL;
    m_pPause = NULL;

    m_state = STATE_NORMAL;
    m_stage = CManager::STAGE_NONE;
    m_nCntGameTime = 0;
    m_nCntCreatePlayer = 0;
    m_nCntFinishGame = 0;
    m_bFinishGame = false;
    m_bBossBattle = false;
    m_bFloor = false;
    m_bInvinciblePlayer = false;
    m_bMovePlayer = true;
    m_bShockPlayer = false;
    m_bDarkening = false;
    m_bCreateHelper = false;
    m_bGameClear = false;
}

//=============================================================================
// �Q�[���̃f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(void)
{
    // �����̏�����
    srand((unsigned int)time(NULL));

    // �X�e�[�W�����ɐݒ�
    SetStage(CManager::GetSetStage());

    // �|�[�Y�̐���
    m_pPause = CPause::Create();

    // �v���C���[�̐���(�ŏ��̊p�x�A���G���Ԃ�0)
    m_pPlayer = CPlayer::Create(PLAYER_POS, PLAYER_SIZE, 0.0f, 0);
    CPlayer::Create(PLAYER_POS2, PLAYER_SIZE, 0.0f, 0);
    CPlayer::Create(PLAYER_POS3, PLAYER_SIZE, 0.0f, 0);

    // �X�R�A�̐���
    m_pScore = CScore::Create(SCORE_POS, SCORE_SIZE);

    //// UI�̐���
    //CUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), ARROW_SYMBOL_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CUI::TYPE_ARROW_SYMBOL);
    //CUI::Create(PLAYER1_UI_POS, PLAYER1_UI_SIZE, DEFAULT_COLOR, CUI::TYPE_PLAYER1);
    CUI::Create(STOCK_UI_POS, STOCK_UI_SIZE, DEFAULT_COLOR, CUI::TYPE_STOCK);
    //CUI::Create(BARRIER_UI_POS, BARRIER_UI_SIZE, DEFAULT_COLOR, CUI::TYPE_BARRIER);
    //CUI::Create(SPEED_UI_POS, SPEED_UI_SIZE, DEFAULT_COLOR, CUI::TYPE_SPEED);
    CUI::Create(STOCK_BAR_UI_POS, STOCK_BAR_UI_SIZE, DEFAULT_COLOR, CUI::TYPE_STOCK_BAR);
    //CUI::Create(BARRIER_BAR_UI_POS, BARRIER_BAR_UI_SIZE, DEFAULT_COLOR, CUI::TYPE_BARRIER_BAR);
    //CUI::Create(SPEED_BAR_UI_POS, SPEED_BAR_UI_SIZE, DEFAULT_COLOR, CUI::TYPE_SPEED_BAR);
    //CUI::Create(DEFAULT_VECTOR, BARRIER_SIZE, BARRIER_START_COLOR, CUI::TYPE_GET_BARRIER);
    //CUI::Create(TO_START_POS, TO_START_SIZE, DEFAULT_COLOR, CUI::TYPE_2P_TO_START);

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
    // BGM�⃋�[�v����SE���~
    CSound *pSound = CManager::GetSound();
    pSound->Stop(CSound::LABEL_BGM_GAME1);
    pSound->Stop(CSound::LABEL_BGM_BOSS1);
    pSound->Stop(CSound::LABEL_BGM_GAME2);
    pSound->Stop(CSound::LABEL_BGM_BOSS2);
    pSound->Stop(CSound::LABEL_BGM_GAME3);
    pSound->Stop(CSound::LABEL_BGM_BOSS3);
    pSound->Stop(CSound::LABEL_SE_WARNING);

    // �|�[�Y��j��
    if (m_pPause != NULL)
    {
        m_pPause->Uninit();
        delete m_pPause;
        m_pPause = NULL;
    }
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
    // �L�[�{�[�h���擾
    CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

    // �R���g���[�����擾
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();
    DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_1);
    DIJOYSTATE2 Controller2 = pInputJoypad->GetController(PLAYER_2);

    // �T�E���h���擾
    CSound *pSound = CManager::GetSound();

    // ��Ԃ��Ƃɏꍇ����
    switch (m_state)
    {
    case STATE_NORMAL:

        // �X�^�[�g�{�^���������ꂽ��
        if (pInputKeyboard->GetKeyboardTrigger(DIK_P) || pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START))
        {
            // �Q�[�����Ȃ�
            if (CGame::GetState() == CGame::STATE_NORMAL)
            {
                // �Q�[���������Ă���Ȃ�
                if (m_bFinishGame == false)
                {
                    // �|�[�Y��
                    pSound->Play(CSound::LABEL_SE_PAUSE);

                    // �|�[�Y��Ԃɂ���
                    CPause::SetState(CPause::STATE_PAUSE);
                    CGame::SetState(CGame::STATE_PAUSE);
                }
            }
        }

        // �v���C���[2�̃X�^�[�g�{�^���������ꂽ��
        if (pInputJoypad->GetJoypadTrigger(PLAYER_2, CInputJoypad::BUTTON_START))
        {
            // �w���p�[����������Ă��Ȃ��Ȃ�
            if (m_bCreateHelper == false)
            {
                // �Q�[�����Ȃ�
                if (CGame::GetState() == CGame::STATE_NORMAL)
                {
                    // �Q�[���������Ă���Ȃ�
                    if (m_bFinishGame == false)
                    {
                        // �|�[�Y��(�Q�퉹�̑���)
                        pSound->Play(CSound::LABEL_SE_PAUSE);

                        // �w���p�[�̐���(�����p�x��ς��Ĕz�u����̂́A�s���R�ɂ݂����̂ł�߂�)
                        m_pHelper = CHelper::Create(HELPER_POS, HELPER_SIZE, 0.0f, HELPER_INVINCIBLE_FRAME);

                        // �w���p�[�����邩�ǂ����̃t���O��true��
                        m_bCreateHelper = true;
                    }
                }
            }
        }

        // �Q�[�����Ԃ����Z
        m_nCntGameTime++;

        // �X�e�[�W���Ƃɐ؂�ւ�
        switch (m_stage)
        {
        case CManager::STAGE_A:
            Stage��();
            break;

        case CManager::STAGE_B:
            Stage��();
            break;

        case CManager::STAGE_C:
            Stage��();
            break;
        }

        // �v���C���[�����̃t���O��true�Ȃ�
        if (m_bCreatePlayer == true)
        {
            // �v���C���[�𐶐�����J�E���^
            m_nCntCreatePlayer++;

            // ��莞�Ԍo�߂�����
            if (m_nCntCreatePlayer >= CREATE_PLAYER_COUNT)
            {
                // �v���C���[�𐶐�����J�E���^�����Z�b�g
                m_nCntCreatePlayer = 0;

                // �v���C���[�̎c������A�v���C���[��z�u(�����p�x��ς��Ĕz�u����̂́A�s���R�ɂ݂����̂ł�߂�)
                CAfterimage::Create(AFTERIMAGE_PLAYER_DISP_POS, PLAYER_SIZE, 0.0f, DEFAULT_COLOR, CAfterimage::TYPE_PLAYER_DISP);

                // �v���C���[�����̃t���O��false��
                m_bCreatePlayer = false;
            }
        }

        // �Q�[���������Ă���Ȃ�
        if (m_bFinishGame == false)
        {
            // �R���e�B�j���[����(�X�g�b�N��0����)
            if (m_nStock <= 0)
            {
                // �A�C�e����
                pSound->Play(CSound::LABEL_SE_WARNING);

                //// �R���e�B�j���[��Ԃɂ���
                //CPause::SetState(CPause::STATE_CONTINUE);
                //CGame::SetState(CGame::STATE_PAUSE);
                // �Q�[���I���̃t���O��true��
                m_bFinishGame = true;

                // ���U���g�ɍs���܂ł̎��Ԃ�ݒ�
                m_nCntFinishGame = 180;

                // �Q�[���I�[�o�[���N���G�C�g
                CUI::Create(GAMEOVER_POS, GAMEOVER_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f), CUI::TYPE_GAMEOVER);
            }
            // �Q�[���N���A����
            else
            {
                // �Q�[���N���A�̔��肪true�Ȃ�
                if (m_bGameClear == true)
                {
                    // �Q�[���I���̃t���O��true��
                    m_bFinishGame = true;

                    // ���U���g�ɍs���܂ł̎��Ԃ�ݒ�
                    m_nCntFinishGame = COUNT_WAIT_GAME_CLEAR;
                }
            }
        }

        // ���U���g�ɍs���܂ł̃J�E���^
        if (m_nCntFinishGame > 0)
        {
            m_nCntFinishGame--;

            // 0�ɂȂ�������
            if (m_nCntFinishGame == 0)
            {
                // �t�F�[�h���Ă��Ȃ��Ȃ�
                if (CFade::GetFade() == CFade::FADE_NONE)
                {
                    // �X�R�A���}�l�[�W���ɓn��
                    CManager::SetScore(m_pScore->GetScore());

                    // �w���p�[�����邩�ǂ������}�l�[�W���ɓn��
                    if (m_pHelper == NULL)
                    {
                        CManager::SetUseHelper(false);
                    }
                    else
                    {
                        CManager::SetUseHelper(true);
                    }

                    // ���U���g���[�h�Ɉڍs
                    CFade::SetFade(CManager::MODE_RESULT);
                }
            }
        }

        break;

    case STATE_PAUSE:

        // �|�[�Y�̍X�V
        m_pPause->Update();

        break;
    }
}

//========================================
// �v���C���[���j����
//========================================
void CGame::DefeatPlayer(void)
{
    // �v���C���[�����邩�ǂ����̃t���O��true��
    m_bDispPlayer = false;

    // �X�g�b�N����������
    m_nStock--;

    //// 0�ȏ�̃X�g�b�N������Ȃ�
    //if (m_nStock >= 0)
    //{
    //    // �v���C���[�̐���
    //    m_bCreatePlayer = true;
    //}
}

//========================================
// �R���e�B�j���[
//========================================
void CGame::Continue(void)
{
    // �X�g�b�N���A�J�n���̂��̂ɂ���
    m_nStock = PLAYER_START_STOCK;

    // �v���C���[�̐����̃t���O��true��
    m_bCreatePlayer = true;

    //================================================
    // �X�R�A�𔼕��ɂ��鏈��
    // �ϐ��錾
    int nScore = 0;     // �X�R�A
    int nAnswer = 0;    // �ŏI�I�ȓ���

    // �X�R�A���擾
    if (m_pScore != NULL)
    {
        nScore = m_pScore->GetScore();
    }
    
    // 0�ȉ����A����ȊO�ŏꍇ����
    if (nScore > 0)
    {
        // �����Ȃ�
        if (nScore % 2 == 0)
        {
            if (m_pScore != NULL)
            {
                // ���̂܂ܔ����ɂ���
                nAnswer = nScore / 2;
                m_pScore->SetScore(nAnswer);
            }
        }
        // ��Ȃ�
        else
        {
            if (m_pScore != NULL)
            {
                // �����_�ȉ��؂�̂ĂŔ����ɂ���
                nAnswer = (nScore - 1) / 2;
                m_pScore->SetScore(nAnswer);
            }
        }
    }
    else
    {
        // 0�ȉ��́A0
        if (m_pScore != NULL)
        {
            nAnswer = 0;
            m_pScore->SetScore(nAnswer);
        }
    }
    //================================================
}

//========================================
// �X�g�b�N���Z����
//========================================
void CGame::AddStock(void)
{
    // �X�g�b�N�����Z
    m_nStock++;

    // �ő吔�𒴂�����A�ő吔�ɂ���
    if (m_nStock > PLAYER_MAX_STOCK)
    {
        m_nStock = PLAYER_MAX_STOCK;
    }
}

//========================================
// �Q�[���̃J�E���^���~�߂�
//========================================
void CGame::StopGameCount(void)
{
    m_nCntGameTime = STAGE_WAVE_STOP - 1;
}

//========================================
// �X�e�[�W��ݒ肷��
//========================================
void CGame::SetStage(CManager::STAGE stage)
{
    // �T�E���h���擾
    CSound *pSound = CManager::GetSound();

    // �X�e�[�W��ς���
    m_stage = stage;

    // �Q�[���̃J�E���^�����Z�b�g
    m_nCntGameTime = 0;

    // �{�X�o�g�����̃t���O�����Z�b�g
    m_bBossBattle = false;

    // �V���b�N��Ԃ����Z�b�g
    m_bShockPlayer = false;

    // �Ó]��Ԃ����Z�b�g
    m_bDarkening = false;

    // UI�ƁA�w�i�ƁA���̔����ݒ�
    switch (m_stage)
    {
    case CManager::STAGE_A:

        //// UI�̐���
        //CUI::Create(ZONE_POS, ZONE_SIZE, DEFAULT_COLOR, CUI::TYPE_ZONE_A);

        // �w�i�̐���
        CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
            D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),CBg::SET_A);

        // �O�i�̐���
        CForeground::Create(FOREGROUND_FOREST_POS, SCROLL_SIZE, DEFAULT_COLOR, CForeground::TYPE_FOREST);

        // BGM�Đ�
        pSound->Play(CSound::LABEL_BGM_GAME1);

        // ���͖��g�p
        m_bFloor = false;

        break;

    case CManager::STAGE_B:

        // UI�̐���
        CUI::Create(ZONE_POS, ZONE_SIZE, DEFAULT_COLOR, CUI::TYPE_ZONE_B);

        // �w�i�̐���
        CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
            D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CBg::SET_B);

        // �O�i�̐���
        CForeground::Create(FOREGROUND_CORAL_POS, FOREGROUND_CORAL_SIZE, DEFAULT_COLOR, CForeground::TYPE_CORAL);

        // �g�̐���
        CWave::Create(WAVE_POS, WAVE_SIZE, WAVE_COLOR, CWave::TYPE_BIG_WAVE);
        // �g�̐���
        CWave::Create(WAVE_POS, WAVE_SIZE2, WAVE_COLOR2, CWave::TYPE_BIG_WAVE2);

        // BGM�Đ�
        pSound->Play(CSound::LABEL_BGM_GAME2);

        // �����g�p
        m_bFloor = true;

        break;

    case CManager::STAGE_C:

        // UI�̐���
        CUI::Create(ZONE_POS, ZONE_SIZE, DEFAULT_COLOR, CUI::TYPE_ZONE_C);

        // �w�i�̐���
        CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
            D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CBg::SET_C);

        // BGM�Đ�
        pSound->Play(CSound::LABEL_BGM_GAME3);

        // �����g�p
        m_bFloor = true;

        break;
    }

    // �v���C���[�̖��G����
    m_bInvinciblePlayer = false;
}

//========================================
// �v���C���[�����X�|�[��
//========================================
void CGame::RespawnPlayer(void)
{
    // �v���C���[�̐���(�����p�x��ς��Ĕz�u����̂́A�s���R�ɂ݂����̂ł�߂�)
    m_pPlayer = CPlayer::Create(PLAYER_POS, PLAYER_SIZE, 0.0f, PLAYER_INVINCIBLE_FRAME);

    // �v���C���[�����邩�ǂ����̃t���O��true��
    m_bDispPlayer = true;
}

//========================================
// �v���C���[�������邩�ǂ�����ݒ�
//========================================
void CGame::SetMovePlayer(bool bMove)
{
    // �v���C���[�������邩�ǂ�����ݒ�
    m_bMovePlayer = bMove;

    // �v���C���[���������Ă���Ȃ�A�X�^�[�g�ʒu�ɂ���
    if (m_bDispPlayer == true)
    {
        m_pPlayer->SetStartPos();
    }

    // �w���p�[�����݂��Ă���Ȃ�A�X�^�[�g�ʒu�ɂ���
    if (m_bCreateHelper == true)
    {
        m_pHelper->SetStartPos();
    }
}

//========================================
// �X�e�[�W��
//========================================
void CGame::Stage��(void)
{
    int spawnRate = LEVEL1_SPAWN;
    float fSpeed = LEVEL1_SPEED;

    if (m_nCntGameTime > LEVEL2_START)
    {
        spawnRate = LEVEL2_SPAWN;
        fSpeed = LEVEL2_SPEED;
    }

    if (m_nCntGameTime > LEVEL3_START)
    {
        spawnRate = LEVEL3_SPAWN;
        fSpeed = LEVEL3_SPEED;
    }

    if (m_nCntGameTime > LEVEL4_START)
    {
        spawnRate = LEVEL4_SPAWN;
        fSpeed = LEVEL4_SPEED;
    }

    if (m_nCntGameTime > LEVEL5_START)
    {
        spawnRate = LEVEL5_SPAWN;
        fSpeed = LEVEL5_SPEED;
    }

    if (m_nCntGameTime % spawnRate == 0)
    {
        if (m_nCntGameTime > LEVEL2_START)
        {
            int nRandNum = GetRandNum(DOUBLE, 1);
            if (nRandNum == DOUBLE)
            {
                SetRandApple(fSpeed, true, true);
                SetRandApple(fSpeed, true, false);
            }
            else
            {
                SetRandApple(fSpeed, true, false);
            }
        }
        else
        {
            SetRandApple(fSpeed, false, false);
        }
    }
}

//========================================
// �����_���ȏꏊ�Ƀ����S�ݒu
//========================================
void CGame::SetRandApple(float fSpeed, bool bUsePoisn, bool bEx)
{
    float fPosX = (float)GetRandNum(1200, 80);
    float fPosY = -50.0f;

    if (bUsePoisn)
    {
        int nRandNum = GetRandNum(POISN, 1);

        if (bEx)
        {
            CEnemy::Create(D3DXVECTOR3(fPosX, fPosY, 0.0f), ENEMY_FLY_SIZE,
                fSpeed, false, CEnemy::TYPE_FLY);
        }
        else
        {
            if (nRandNum == POISN)
            {
                CEnemy::Create(D3DXVECTOR3(fPosX, fPosY, 0.0f), ENEMY_FLY_SIZE,
                    fSpeed, false, CEnemy::TYPE_FLY);
            }
            else
            {
                CEnemy::Create(D3DXVECTOR3(fPosX, fPosY, 0.0f), ENEMY_FLY_SIZE,
                    fSpeed, false, CEnemy::TYPE_SKELETON);
            }
        }
    }
    else
    {
        CEnemy::Create(D3DXVECTOR3(fPosX, fPosY, 0.0f), ENEMY_FLY_SIZE,
            fSpeed, false, CEnemy::TYPE_SKELETON);
    }
}

//========================================
// �X�e�[�W��
//========================================
void CGame::Stage��(void)
{

}

//========================================
// �X�e�[�W��
//========================================
void CGame::Stage��(void)
{

}

//========================================
// �����_���ɖA�𐶐����鏈��
//========================================
void CGame::SetRandBubble(void)
{
    // �A�𐶐�
    if (m_nCntGameTime % STAGE2_SET_BUBBLE_COUNT == 0)
    {
        // �A�𐶐�����ʒu
        D3DXVECTOR3 pos = DEFAULT_VECTOR;

        // �ʒuX�AY�������_���Ɏ擾(��ʓ��S�̂��͈�)
        int nMaxX = (SCREEN_WIDTH * 10);
        int nMaxY = (SCREEN_HEIGHT * 10);
        float fPosX = float(rand() % nMaxX) / 10.0f;
        float fPosY = float(rand() % nMaxY) / 10.0f;

        // �ʒu�𔽉f
        pos = D3DXVECTOR3(fPosX, fPosY, 0.0f);

        // 6�̖A�𐶐�
        CBubble::Create(pos, BUBBLE_MINIMUM_SIZE, CBubble::TYPE_MINIMUM);
        CBubble::Create(pos, BUBBLE_SMALL_SIZE, CBubble::TYPE_SMALL);
        CBubble::Create(pos, BUBBLE_NORMAL_SIZE, CBubble::TYPE_NORMAL);
        CBubble::Create(pos, BUBBLE_NORMAL2_SIZE, CBubble::TYPE_NORMAL2);
        CBubble::Create(pos, BUBBLE_BIG_SIZE, CBubble::TYPE_BIG);
        CBubble::Create(pos, BUBBLE_MAXIMUM_SIZE, CBubble::TYPE_MAXIMUM);
    }
}

//========================================
// �����_���ɉ��𐶐����鏈��
//========================================
void CGame::SetRandFire(void)
{
    // ���𐶐�����J�E���^
    if (m_nCntGameTime % STAGE3_SET_FIRE_COUNT == 0)
    {
        // ���𐶐�����ʒu
        D3DXVECTOR3 pos = DEFAULT_VECTOR;
        float fSize = 0.0f;
        int nMinX = (SCREEN_WIDTH - (m_nCntGameTime * 3)) * 10;    // �ŏ��l�i���񂾂�E����}�O�}���o�Ă��邽�߁j
        if (nMinX < 0)
        {
            nMinX = 0;  // �}�C�i�X�̒l�ɂ͂��Ȃ�
        }
        int nMaxX = (SCREEN_WIDTH * 10);            // �������̍ő�͈�
        float fPosX = 0.0f;                         // �����ʒuX
        float fPosY = 0.0f;                         // �����ʒuY
        float fPosAdjustY = 0.0f;                   // �����ʒuY�̒���

        // �������A���̏ォ�ŁA���̔����ʒu�̍�����ς���
        if (m_nCntGameTime < STAGE3_WAVE_SET_FLOOR)
        {
            // �����͍���
            fPosAdjustY = EFFECT_FIRE_START_POS_Y;
        }
        else
        {
            // ���̏�͒��
            fPosAdjustY = EFFECT_FIRE_START_POS_Y_BOSS;
        }

        // ��ʉE�[���甭�������邽�߂̈ʒuX
        float fRandPosX = 0.0f;

        // �G�t�F�N�g�p�ɁA�傫���ƍ��W�����߂�
        fSize = float(rand() % EFFECT_FIRE_MAX_SIZE + EFFECT_FIRE_MIN_SIZE) / 100.0f;
        fPosX = float(rand() % nMaxX - nMinX) / 10.0f;
        fRandPosX = SCREEN_WIDTH - fPosX;
        fPosY = (SCREEN_HEIGHT - fPosAdjustY) - float(rand() % 10000) / 100.0f;
        // �ʒu�𔽉f
        pos = D3DXVECTOR3(fRandPosX, fPosY, 0.0f);
        // ���𐶐�
        CEffect::Create(pos, D3DXVECTOR3(fSize, fSize, 0.0f), EFFECT_FIRE_FIRST_COLOR, CEffect::TYPE_FIRE);

        // �G�t�F�N�g�p�ɁA�傫���ƍ��W�����߂�
        fSize = float(rand() % EFFECT_FIRE_MAX_SIZE + EFFECT_FIRE_MIN_SIZE) / 100.0f;
        fPosX = float(rand() % nMaxX - nMinX) / 10.0f;
        fRandPosX = SCREEN_WIDTH - fPosX;
        fPosY = (SCREEN_HEIGHT - fPosAdjustY) - float(rand() % 10000) / 100.0f;
        // �ʒu�𔽉f
        pos = D3DXVECTOR3(fRandPosX, fPosY, 0.0f);
        // ���𐶐�
        CEffect::Create(pos, D3DXVECTOR3(fSize, fSize, 0.0f), EFFECT_FIRE_FIRST_COLOR, CEffect::TYPE_FIRE);

        // �G�t�F�N�g�p�ɁA�傫���ƍ��W�����߂�
        fSize = float(rand() % EFFECT_FIRE_MAX_SIZE + EFFECT_FIRE_MIN_SIZE) / 100.0f;
        fPosX = float(rand() % nMaxX - nMinX) / 10.0f;
        fRandPosX = SCREEN_WIDTH - fPosX;
        fPosY = (SCREEN_HEIGHT - fPosAdjustY) - float(rand() % 10000) / 100.0f;
        // �ʒu�𔽉f
        pos = D3DXVECTOR3(fRandPosX, fPosY, 0.0f);
        // ���𐶐�
        CEffect::Create(pos, D3DXVECTOR3(fSize, fSize, 0.0f), EFFECT_FIRE_FIRST_COLOR, CEffect::TYPE_FIRE);

        //=============================================================================================
        // �Q�[���̐i�s�ɉe�����y�ڂ��Ȃ�A����
        // �G�t�F�N�g�p�ɁA�傫���ƍ��W�����߂�
        fSize = float(rand() % EFFECT_FIRE_MAX_SIZE + EFFECT_FIRE_MIN_SIZE) / 100.0f;
        fPosX = float(rand() % nMaxX - nMinX) / 10.0f;
        fRandPosX = SCREEN_WIDTH - fPosX;
        fPosY = (SCREEN_HEIGHT - fPosAdjustY) - float(rand() % 10000) / 100.0f;
        // �ʒu�𔽉f
        pos = D3DXVECTOR3(fRandPosX, fPosY, 0.0f);
        // ���𐶐�
        CEffect::Create(pos, D3DXVECTOR3(fSize, fSize, 0.0f), EFFECT_FIRE_FIRST_COLOR, CEffect::TYPE_FIRE);
        //=============================================================================================
    }
}

//========================================
// �����_���Ƀ}�O�}�𐶐����鏈��
//========================================
void CGame::SetRandMagma(void)
{
    // �}�O�}�𐶐�����J�E���^
    if (m_nCntGameTime % STAGE3_SET_MAGMA_COUNT == 0)
    {
        // �ϐ��錾
        D3DXVECTOR3 pos = DEFAULT_VECTOR;
        int nMaxX = (SCREEN_WIDTH * 10 + 6400);
        float fPosX = 0.0f;
        float fPosY = 0.0f;
        float fSize = 0.0f;

        // �����_���Ɉʒu�ƃT�C�Y�𓾂�
        fPosX = float(rand() % nMaxX) / 10.0f;
        fPosY = (SCREEN_HEIGHT)-float(rand() % 5000) / 100.0f;
        fSize = float(rand() % EFFECT_MAGMA_MAX_SIZE + EFFECT_MAGMA_MIN_SIZE) / 100.0f;
        // �ʒu�𔽉f
        pos = D3DXVECTOR3(SCREEN_WIDTH + (fSize / 2) - 1, fPosY, 0.0f);
        // �}�O�}�𐶐�
        CEffect::Create(pos, D3DXVECTOR3(fSize, fSize, 0.0f), EFFECT_MAGMA_COLOR, CEffect::TYPE_MAGMA);

        // �}�O�}�̈�ԉ��̏�
        // �����_���ɃT�C�Y�𓾂�
        fSize = float(rand() % EFFECT_MAGMA_MAX_SIZE + EFFECT_MAGMA_MIN_SIZE) / 100.0f;
        // �ʒu�𔽉f
        pos = D3DXVECTOR3(SCREEN_WIDTH + (fSize / 2) - 1, SCREEN_HEIGHT - (fSize / 3), 0.0f);
        // �}�O�}�𐶐�
        CEffect::Create(pos, D3DXVECTOR3(fSize, fSize, 0.0f), EFFECT_MAGMA_COLOR, CEffect::TYPE_MAGMA);
    }
}

//========================================
// �����_���ɉ_�𐶐����鏈��
//========================================
void CGame::SetRandCloud(void)
{
    // �_��ݒu�ł���J�E���^�ȏ��
    if (m_nCntGameTime >= STAGE3_SET_CLOUD_START)
    {
        // �ϐ��錾
        int nCntSetCount = 0;   // �_��ݒu����J�E���^
        
        // �{�X�펞���ǂ����ŁA�_��ݒu����J�E���^��ς���
        if (m_bBossBattle == false)
        {
            // �ʏ펞
            nCntSetCount = STAGE3_SET_CLOUD_COUNT;
        }
        else
        {
            // �{�X�펞
            nCntSetCount = STAGE3_SET_CLOUD_COUNT_BOSS;
        }

        // �J�E���^�ɂ���āA�_�𐶐�
        if (m_nCntGameTime % nCntSetCount == 0)
        {
            // �ϐ��錾
            float fLocalPosX = 0.0f;            // �_�̗��̍��WX
            float fLocalPosY = 0.0f;            // �_�̗��̍��WY
            float fSize = 0.0f;                 // �_�̗��̑傫��
            float fGlobalPosX = 0.0f;           // �_���̂̍��WX
            float fGlobalPosY = 0.0f;           // �_���̂̍��WY
            float fAlpha = 0.0f;                // ���l
            D3DXVECTOR3 pos = DEFAULT_VECTOR;   // �����ʒu

            // ��̒����ǂ����ŁA�_���̂̐����n�_�����߂�
            if (m_nCntGameTime < STAGE3_WAVE_END_SKY_MODE)
            {
                // ��̒��̎��́A��ʉE�ォ��
                fGlobalPosX = float(rand() % 16000 + 6400) / 10.0f;
                fGlobalPosY = float(rand() % 2000 + 0) / 10.0f;

                // ��ʊO����o�������̂ŁAY�Ƀ}�C�i�X��������
                fGlobalPosY *= -1;
            }
            else if (m_nCntGameTime >= STAGE3_WAVE_END_SKY_MODE)
            {
                // ��̒��łȂ��Ƃ��́A�E����
                fGlobalPosX = float(rand() % 16000 + 15000) / 10.0f;
                fGlobalPosY = float(rand() % 6600 + 750) / 10.0f;
            }

            for (int nCnt = 0; nCnt < EFFECT_CLOUD_COUNT_LOOP; nCnt++)
            {
                // �_�̗��̐����n�_�����߂�
                fLocalPosX = float(rand() % EFFECT_CLOUD_SIZE_X) / 100.0f - float(rand() % EFFECT_CLOUD_SIZE_X) / 100.0f;
                fLocalPosY = float(rand() % EFFECT_CLOUD_SIZE_Y) / 100.0f - float(rand() % EFFECT_CLOUD_SIZE_Y) / 100.0f;
                pos = D3DXVECTOR3(fGlobalPosX + fLocalPosX, fGlobalPosY + fLocalPosY, 0.0f);

                // ���̐����n�_��X���W�ɂ���āA�_�̗��̑傫���ƃ��l�����߂�
                if (fabsf(fLocalPosX) < EFFECT_CLOUD_EDGE)
                {
                    // ���S�ɋ߂��Ȃ�A���͑傫��
                    fSize = float(rand() % EFFECT_CLOUD_PARTICLES_MAX_SIZE + EFFECT_CLOUD_PARTICLES_MID1_SIZE) / 100.0f;

                    // ���l���������߂�
                    fAlpha = float(rand() % EFFECT_CLOUD_PARTICLES_MAX_ALPHA + EFFECT_CLOUD_PARTICLES_MID_ALPHA) / 100.0f;
                }
                else
                {
                    // ���S���牓���Ȃ�A���͏�����
                    fSize = float(rand() % EFFECT_CLOUD_PARTICLES_MID2_SIZE + EFFECT_CLOUD_PARTICLES_MIN_SIZE) / 100.0f;

                    // ���l���߂�
                    fAlpha = float(rand() % EFFECT_CLOUD_PARTICLES_MID_ALPHA + EFFECT_CLOUD_PARTICLES_MIN_ALPHA) / 100.0f;
                }

                // �_�𐶐�
                CEffect::Create(pos, D3DXVECTOR3(fSize, fSize, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha), CEffect::TYPE_CLOUD);
            }
        }
    }
}
