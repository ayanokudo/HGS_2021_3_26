//===============================================
//
// UI���� (ui.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "ui.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "library.h"
#include "player.h"
#include "game.h"
#include "sound.h"
#include "title.h"

//=======================================
// �ÓI�����o�ϐ��錾
//=======================================
LPDIRECT3DTEXTURE9 CUI::m_apTexture[CUI::TYPE_MAX] = {};
bool CUI::m_bChangeZoneTo�� = false;
bool CUI::m_bChangeZoneTo�� = false;

//========================================
// UI�̃R���X�g���N�^
//========================================
CUI::CUI() :CScene2D(OBJTYPE::OBJTYPE_UI)
{
    m_move = DEFAULT_VECTOR;
    m_col = DEFAULT_COLOR;
    m_type = CUI::TYPE_MAX;
    m_bFadeOut = false;
    m_bBlinking = false;
    m_nCntTime = 0;
}

//========================================
// UI�̃f�X�g���N�^
//========================================
CUI::~CUI()
{

}

//========================================
// UI�̏���������
//========================================
HRESULT CUI::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ������
    CScene2D::Init(pos, size);

    // �e�N�X�`�������蓖��
    BindTexture(m_apTexture[m_type]);

    return S_OK;
}

//========================================
// UI�̏I������
//========================================
void CUI::Uninit(void)
{
    // �I������
    CScene2D::Uninit();
}

//========================================
// UI�̍X�V����
//========================================
void CUI::Update(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos = GetPosition();        // �ʒu���擾
    D3DXVECTOR3 size = GetSize();           // �T�C�Y���擾
    int nPatternAnim = 0;                   // �p�^�[���A�j���̃J�E���^�𗘗p����Ƃ�
    bool bUse = true;                       // �g�����ǂ���

    // �v���C���[�֘A�̕ϐ��錾
    CPlayer *pPlayer = NULL;                // �v���C���[���擾
    CScene2D *pPlayerScene2D = NULL;        // �v���C���[���V�[��2D�ɃL���X�g
    D3DXVECTOR3 playerPos = DEFAULT_VECTOR; // �v���C���[�̈ʒu
    D3DXVECTOR3 playerSize = DEFAULT_VECTOR;// �v���C���[�̑傫��
    int nPlayerBarrier = 0;                 // �v���C���[�̃o���A��
    int nPlayerStcok = 0;                   // �v���C���[�̃X�g�b�N��
    int nPlayerSpeedRank = 0;               // �v���C���[�̃X�s�[�h�����N
    float fBarrierAlpha = 0.0f;             // �o���A�̔Z��
    float fPlayerShotAngle = 0.0f;          // ���̔��ˊp�x
    int nCnt = 0;                           // �J�E���^

    // �Q�[���Ȃ�
    if (CManager::GetMode() == CManager::MODE_GAME)
    {
        nPlayerStcok = CGame::GetStock();

        // �v���C���[�����݂��Ă���Ȃ�
        if (CGame::GetDispPlayer() == true)
        {
            // �v���C���[�̏����擾
            pPlayer = CGame::GetPlayer();
            pPlayerScene2D = (CScene2D*)pPlayer;
            playerPos = pPlayerScene2D->GetPosition();
            playerSize = pPlayerScene2D->GetSize();
            nPlayerBarrier = pPlayer->GetBarrier();
            nPlayerSpeedRank = pPlayer->GetSpeedRank();
            fPlayerShotAngle = pPlayer->GetShotAngle();
        }
    }

    //�L�[�{�[�h�̊m�ۂ������������擾
    CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

    // �R���g���[�����擾
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();
    DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_1);

    // �T�E���h���擾
    CSound *pSound = CManager::GetSound();

    //=========================================================
    // �v���C���[�̏����Q�Ƃ���AUI�̗���𐧌�
    if (nPlayerBarrier < 0)
    {
        nPlayerBarrier = 0;
    }
    else if (nPlayerBarrier > PLAYER_MAX_BARRIER)
    {
        nPlayerBarrier = PLAYER_MAX_BARRIER;
    }

    if (nPlayerStcok < 0)
    {
        nPlayerStcok = 0;
    }
    else if (nPlayerStcok > PLAYER_MAX_STOCK)
    {
        nPlayerStcok = PLAYER_MAX_STOCK;
    }

    if (nPlayerSpeedRank < 0)
    {
        nPlayerSpeedRank = 0;
    }
    else if (nPlayerSpeedRank > PLAYER_MAX_SPEED_RANK)
    {
        nPlayerSpeedRank = PLAYER_MAX_SPEED_RANK;
    }
    //=========================================================

    // �o���A�̔Z�����擾
    switch (nPlayerBarrier)
    {
    case 1:
        fBarrierAlpha = BARRIER_MAX_ALPHA_1;
        break;
    case 2:
        fBarrierAlpha = BARRIER_MAX_ALPHA_2;
        break;
    case 3:
        fBarrierAlpha = BARRIER_MAX_ALPHA_3;
        break;
    case 4:
        fBarrierAlpha = BARRIER_MAX_ALPHA_4;
        break;
    case 5:
        fBarrierAlpha = BARRIER_MAX_ALPHA_5;
        break;
    }

    // ��ނɉ������ꍇ����
    switch (m_type)
    {
        // ���
    case CUI::TYPE_ARROW_SYMBOL:

        // �ʒu�����@�̏�ɐݒ�
        pos = D3DXVECTOR3(playerPos.x, playerPos.y - (playerSize.y / 2), 0.0f);

        // ���񂾂񓧖���
        m_col.a -= 0.1f;

        // �E�X�e�B�b�N���|��Ă���Ȃ瓧���x���グ��
        if (Controller.lZ != 0 || Controller.lRz != 0)
        {
            // �����x��1.0f��
            m_col.a = 1.0f;
        }

        // ���X�e�B�b�N�������݂ŁA���ˊp�x���w�ʂɃ��Z�b�g���ꂽ���Ƃ�����
        if (pInputJoypad->GetJoypadPress(PLAYER_1, CInputJoypad::BUTTON_L3))
        {
            // �����x��1.0f��
            m_col.a = 1.0f;
        }

        // �E�X�e�B�b�N�������݂ŁA���ˊp�x�����ʂɃ��Z�b�g���ꂽ���Ƃ�����
        if (pInputJoypad->GetJoypadPress(PLAYER_1, CInputJoypad::BUTTON_R3))
        {
            // �����x��1.0f��
            m_col.a = 1.0f;
        }

        // �����x��0.0f�ȉ��ɂȂ�����
        if (m_col.a <= 0.0f)
        {
            // 0.0f�ŌŒ�
            m_col.a = 0.0f;
        }

        // �Ó]��ԂŁA�����x��0.0f��
        if (CGame::GetDarkening() == true)
        {
            // 0.0f�ŌŒ�
            m_col.a = 0.0f;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �X�g�b�N�̃o�[
    case CUI::TYPE_STOCK_BAR:

        // ���T�C�Y����
        size.x = STOCK_BAR_UI_SIZE_X / ((float)PLAYER_MAX_STOCK / (float)nPlayerStcok);

        // �摜�̕`��͈͂𒲐�
        SetTextureRange(nPlayerStcok, PLAYER_MAX_STOCK);

        break;

        // �o���A�̃o�[
    case CUI::TYPE_BARRIER_BAR:

        // ���T�C�Y����
        size.x = BARRIER_BAR_UI_SIZE_X / ((float)PLAYER_MAX_BARRIER / (float)nPlayerBarrier);

        // �摜�̕`��͈͂𒲐�
        SetTextureRange(nPlayerBarrier, PLAYER_MAX_BARRIER);

        break;

        // �X�s�[�h�̃o�[
    case CUI::TYPE_SPEED_BAR:

        // ���T�C�Y����
        size.x = SPEED_BAR_UI_SIZE_X / ((float)PLAYER_MAX_SPEED_RANK / (float)nPlayerSpeedRank);

        // �摜�̕`��͈͂𒲐�
        SetTextureRange(nPlayerSpeedRank, PLAYER_MAX_SPEED_RANK);

        // �V���b�N��ԂȂ�A�ԐF�ɂ���
        if (CGame::GetShockPlayer() == true)
        {
            m_col.g = 0.0f;
            m_col.b = 0.0f;
        }
        else
        {
            m_col.g = 1.0f;
            m_col.b = 1.0f;
        }

        // �F��ݒ�
        SetColor(m_col);

        break;

        // �]�[����
    case CUI::TYPE_ZONE��:

        // �]�[�����؂�ւ��Ȃ�
        if (m_bChangeZoneTo�� == true)
        {
            // ���g�p��
            bUse = false;

            // �t���O��߂�
            m_bChangeZoneTo�� = false;
        }

        break;

        // �]�[����
    case CUI::TYPE_ZONE��:

        // �]�[�����؂�ւ��Ȃ�
        if (m_bChangeZoneTo�� == true)
        {
            // ���g�p��
            bUse = false;

            // �t���O��߂�
            m_bChangeZoneTo�� = false;
        }

        break;

        // �]�[����
    case CUI::TYPE_ZONE��:


        break;

        // �X�e�[�W�J�n1
    case CUI::TYPE_START_STAGE1:

        // ���T�C�Y�g��
        size.x += STAGE_START_EXTEND_RATE_X;

        // �c�T�C�Y�g��
        size.y += STAGE_START_EXTEND_RATE_Y;

        // ���T�C�Y�̐���
        if (size.x >= STAGE_START_MAX_SIZE_X)
        {
            size.x = STAGE_START_MAX_SIZE_X;
        }

        // �c�T�C�Y�̐���
        if (size.y >= STAGE_START_MAX_SIZE_Y)
        {
            size.y = STAGE_START_MAX_SIZE_Y;
        }

        // �A�j���[�V�����̃J�E���^�𗘗p���āAUI�̃t�F�[�h�A�E�g�ɂȂ���
        nCnt = CountAnimation(1, MAX_ANIM_COUNTER);

        // �t�F�[�h�A�E�g���n�߂�J�E���g�𒴂�����A���l�������Ă���
        if (nCnt >= STAGE_START_FADE_OUT_COUNT)
        {
            m_col.a -= STAGE_START_FADE_OUT_RATE;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        // �����x��0�����������A����
        if (m_col.a <= 0.0f)
        {
            bUse = false;
        }

        break;

        // �X�e�[�W�J�n2
    case CUI::TYPE_START_STAGE2:

        // ���T�C�Y�g��
        size.x += STAGE_START_EXTEND_RATE_X;

        // �c�T�C�Y�g��
        size.y += STAGE_START_EXTEND_RATE_Y;

        // ���T�C�Y�̐���
        if (size.x >= STAGE_START_MAX_SIZE_X)
        {
            size.x = STAGE_START_MAX_SIZE_X;
        }

        // �c�T�C�Y�̐���
        if (size.y >= STAGE_START_MAX_SIZE_Y)
        {
            size.y = STAGE_START_MAX_SIZE_Y;
        }

        // �A�j���[�V�����̃J�E���^�𗘗p���āAUI�̃t�F�[�h�A�E�g�ɂȂ���
        nCnt = CountAnimation(1, MAX_ANIM_COUNTER);

        // �t�F�[�h�A�E�g���n�߂�J�E���g�𒴂�����A���l�������Ă���
        if (nCnt >= STAGE_START_FADE_OUT_COUNT)
        {
            m_col.a -= STAGE_START_FADE_OUT_RATE;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        // �����x��0�����������A����
        if (m_col.a <= 0.0f)
        {
            bUse = false;
        }

        break;

        // �X�e�[�W�J�n3
    case CUI::TYPE_START_STAGE3:

        // ���T�C�Y�g��
        size.x += STAGE_START_EXTEND_RATE_X;

        // �c�T�C�Y�g��
        size.y += STAGE_START_EXTEND_RATE_Y;

        // ���T�C�Y�̐���
        if (size.x >= STAGE_START_MAX_SIZE_X)
        {
            size.x = STAGE_START_MAX_SIZE_X;
        }

        // �c�T�C�Y�̐���
        if (size.y >= STAGE_START_MAX_SIZE_Y)
        {
            size.y = STAGE_START_MAX_SIZE_Y;
        }

        // �A�j���[�V�����̃J�E���^�𗘗p���āAUI�̃t�F�[�h�A�E�g�ɂȂ���
        nCnt = CountAnimation(1, MAX_ANIM_COUNTER);

        // �t�F�[�h�A�E�g���n�߂�J�E���g�𒴂�����A���l�������Ă���
        if (nCnt >= STAGE_START_FADE_OUT_COUNT)
        {
            m_col.a -= STAGE_START_FADE_OUT_RATE;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        // �����x��0�����������A����
        if (m_col.a <= 0.0f)
        {
            bUse = false;
        }

        break;

        // ���[�j���O
    case CUI::TYPE_WARNING:

        // �����x���グ�邩�����邩���ꍇ����
        if (m_col.a >= 1.0f)
        {
            m_bFadeOut = true;
        }
        else if (m_col.a <= 0.0f)
        {
            m_bFadeOut = false;
        }

        // �����x���A�t���O�ɂ���ĕς���
        if (m_bFadeOut == true)
        {
            m_col.a -= WARNING_FADE_RATE;
        }
        else
        {
            m_col.a += WARNING_FADE_RATE;
        }

        // �A�j���[�V�����̃J�E���^�𗘗p���āAUI�̃t�F�[�h�A�E�g�ɂȂ���
        nCnt = CountAnimation(1, MAX_ANIM_COUNTER);

        // �t�F�[�h�A�E�g���n�߂�J�E���g�𒴂�����
        if (nCnt >= WARNING_FADE_OUT_COUNT)
        {
            // �����̎��ɖ��g�p�ɂ���
            if (m_col.a <= 0.0f)
            {
                // ���[�j���O�����~�߂�
                pSound->Stop(CSound::LABEL_SE_WARNING);
                bUse = false;
            }
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �o���A���܂Ƃ�
    case CUI::TYPE_GET_BARRIER:

        // ���@�̈ʒu�ɕ\��
        pos = playerPos;

        // �o���A���Ȃ��Ȃ�
        if (nPlayerBarrier <= 0)
        {
            // ���񂾂񓧖���
            m_col.a -= BARRIER_FADE_RATE;
        }
        // �o���A������Ȃ�
        else
        {
            // ���񂾂�\��
            m_col.a += BARRIER_FADE_RATE;
        }

        // �Ó]��ԂŁA�o���A�̓����x��啝�ɉ�����
        if (CGame::GetDarkening() == true)
        {
            // �������猩����l�ŌŒ�
            m_col.a = 0.001f;
        }

        //�����x�̏���A������ݒ�
        if (m_col.a >= fBarrierAlpha)
        {
            m_col.a = fBarrierAlpha;
        }
        else if (m_col.a <= 0.0f)
        {
            m_col.a = 0.0f;
        }

        // �A�j���[�V����
        SetAnimation(3, 8);

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // 2P�Q���҂�
    case CUI::TYPE_2P_TO_START:

        // �w���p�[�����Ȃ��Ȃ�
        if (CGame::GetDispHelper() == false)
        {
            // �A�j���[�V����
            SetParagraphAnimation(1, 2, 60, 2);
        }
        // �w���p�[������Ȃ�
        else
        {
            // �Q����
            SetParagraphTexturePlace(1, 2, 2, 2);
        }

        break;

        // ���N���A
    case CUI::TYPE_��CLEAR:

        // ���񂾂񌩂���悤��
        m_col.a += CLEAR_FADE_RATE;

        // ���l�����ȏア���Ȃ�����
        if (m_col.a > 1.0f)
        {
            m_col.a = 1.0f;
        }

        // �A�j���[�V�����̃J�E���^�𗘗p���āAUI�̃t�F�[�h�A�E�g�ɂȂ���
        nCnt = CountAnimation(1, MAX_ANIM_COUNTER);

        // �t�F�[�h�A�E�g���n�߂�J�E���g�𒴂�����
        if (nCnt >= CLEAR_FADE_OUT_COUNT)
        {
            // �������g�p��
            bUse = false;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // ���N���A
    case CUI::TYPE_��CLEAR:

        // ���񂾂񌩂���悤��
        m_col.a += CLEAR_FADE_RATE;

        // ���l�����ȏア���Ȃ�����
        if (m_col.a > 1.0f)
        {
            m_col.a = 1.0f;
        }

        // �A�j���[�V�����̃J�E���^�𗘗p���āAUI�̃t�F�[�h�A�E�g�ɂȂ���
        nCnt = CountAnimation(1, MAX_ANIM_COUNTER);

        // �t�F�[�h�A�E�g���n�߂�J�E���g�𒴂�����
        if (nCnt >= CLEAR_FADE_OUT_COUNT)
        {
            // �������g�p��
            bUse = false;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // ���N���A
    case CUI::TYPE_��CLEAR:

        // ���񂾂񌩂���悤��
        m_col.a += CLEAR_FADE_RATE;

        // ���l�����ȏア���Ȃ�����
        if (m_col.a > 1.0f)
        {
            m_col.a = 1.0f;
        }

        // �A�j���[�V�����̃J�E���^�𗘗p���āAUI�̃t�F�[�h�A�E�g�ɂȂ���
        nCnt = CountAnimation(1, MAX_ANIM_COUNTER);

        // �t�F�[�h�A�E�g���n�߂�J�E���g�𒴂�����
        if (nCnt >= CLEAR_FADE_OUT_COUNT)
        {
            // �������g�p��
            bUse = false;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �Q�[���I�[�o�[
    case CUI::TYPE_GAMEOVER:

        // ���񂾂񌩂���悤��
        m_col.a += GAMEOVER_FADE_RATE;

        // ���l�����ȏア���Ȃ�����
        if (m_col.a > 1.0f)
        {
            m_col.a = 1.0f;
        }

        // �A�j���[�V�����̃J�E���^�𗘗p���āAUI�̃t�F�[�h�A�E�g�ɂȂ���
        nCnt = CountAnimation(1, MAX_ANIM_COUNTER);

        // �t�F�[�h�A�E�g���n�߂�J�E���g�𒴂�����
        if (nCnt >= CLEAR_FADE_OUT_COUNT)
        {
            // �������g�p��
            bUse = false;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

    case TYPE_TITLE_LOGO:

        // ���ꗎ����
        pos.y += TITLE_LOGO_FLOW_DOWN_SPEED;

        // ���̒l�Ŏ~�߂Ă���
        if (pos.y >= TITLE_LOGO_TARGET_POS_Y)
        {
            pos.y = TITLE_LOGO_TARGET_POS_Y;
        }

        // �G���^�[�A�܂��̓X�^�[�g�{�^������������
        if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START))
        {
            // �^�C�g�����S�������ɉ���
            pos.y = TITLE_LOGO_TARGET_POS_Y;
        }

        break;

    case TYPE_PRESS_START:

        // �^�C�g���̎��Ԃ��J�E���g
        m_nCntTime++;

        // �^�C�g���̍ő厞��
        if (m_nCntTime > TITLE_MAX_TIME)
        {
            m_nCntTime = TITLE_MAX_TIME;
        }

        // �F��ς���
        if (m_bFadeOut == true)
        {
            m_col.r -= PRESS_START_FADE_RATE;
            m_col.g -= PRESS_START_FADE_RATE;
            m_col.b -= PRESS_START_FADE_RATE;
        }
        else
        {
            m_col.r += PRESS_START_FADE_RATE;
            m_col.g += PRESS_START_FADE_RATE;
            m_col.b += PRESS_START_FADE_RATE;
        }
        if (m_col.r <= PRESS_START_FADE_OUT_MIN)
        {
            m_bFadeOut = false;
        }
        else if (m_col.r >= 1.0f)
        {
            m_bFadeOut = true;
        }

        // �G���^�[�A�܂��̓X�^�[�g�{�^������������
        if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START))
        {
            // ��莞�Ԍo�߂œ_�ŉ\��
            if (m_nCntTime >= TITLE_NEXT_SCENE)
            {
                // �_�ł̃t���O��true��
                m_bBlinking = true;
            }
            // ����ȊO�́A�J�E���^��J�ډ\�܂ň�C�ɐi�߂�
            else
            {
                m_nCntTime = TITLE_NEXT_SCENE;
            }
        }

        // �_�ł���Ȃ�
        if (m_bBlinking == true)
        {
            // �J�E���^�[��i�߂āA�p�^�[����؂�ւ���
            nPatternAnim = CountAnimation(2, 2);

            // �F��2�p�^�[���Ő؂�ւ���
            if (nPatternAnim == 1)
            {
                m_col.r = PRESS_START_FADE_OUT_MIN;
                m_col.g = PRESS_START_FADE_OUT_MIN;
                m_col.b = PRESS_START_FADE_OUT_MIN;
            }
            else
            {
                m_col.r = 1.0f;
                m_col.g = 1.0f;
                m_col.b = 1.0f;
            }
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

    case TYPE_CAREFUL_UPPER:

        bUse = Careful();

        break;

    case TYPE_CAREFUL_LEFT:

        bUse = Careful();

        break;

    case TYPE_CAREFUL_RIGHT:

        bUse = Careful();

        break;

    case TYPE_CAREFUL_DOWN:

        bUse = Careful();

        break;

    case TYPE_DANGER:

        bUse = Danger();

        break;
    }

    // �ʒu�𔽉f
    SetPosition(pos);

    // �T�C�Y�𔽉f
    SetSize(size);

    // ���̂݁A��]���钸�_���W
    if (m_type == CUI::TYPE_ARROW_SYMBOL)
    {
        // �v���C���[���E�X�e�B�b�N�œ|�����p�x�����ƂɁA���_���W��ύX
        SetRotVertex(fPlayerShotAngle);
    }
    else
    {
        // ���_���W��ύX
        SetVertex();
    }

    // �g�p����t���O��false�Ȃ����
    if (bUse == false)
    {
        Uninit();
    }
}

//========================================
// UI�̕`�揈��
//========================================
void CUI::Draw(void)
{
    // �`�揈��
    CScene2D::Draw();
}

//========================================
// UI�̉摜���[�h����
//========================================
HRESULT CUI::Load(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    //�e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui000.png", &m_apTexture[CUI::TYPE_ARROW_SYMBOL]);	    // ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui001.png", &m_apTexture[CUI::TYPE_PLAYER1]);	        // �v���C���[1
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui002.png", &m_apTexture[CUI::TYPE_STOCK]);	        // �X�g�b�N
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui003.png", &m_apTexture[CUI::TYPE_BARRIER]);	        // �o���A
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui004.png", &m_apTexture[CUI::TYPE_SPEED]);	        // �X�s�[�h
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui005.png", &m_apTexture[CUI::TYPE_STOCK_BAR]);	    // �X�g�b�N�̃o�[
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui005.png", &m_apTexture[CUI::TYPE_BARRIER_BAR]);	    // �o���A�̃o�[
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui006.png", &m_apTexture[CUI::TYPE_ZONE��]);	        // �]�[����
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui013.png", &m_apTexture[CUI::TYPE_ZONE��]);	        // �]�[����
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui014.png", &m_apTexture[CUI::TYPE_ZONE��]);	        // �]�[����
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui007.png", &m_apTexture[CUI::TYPE_SPEED_BAR]);	    // �X�s�[�h�̃o�[
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui019.png", &m_apTexture[CUI::TYPE_TITLE_LOGO]);       // �^�C�g���̃��S
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui020.png", &m_apTexture[CUI::TYPE_PRESS_START]);      // �X�^�[�g�{�^���������Ă�
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/result000.png", &m_apTexture[CUI::TYPE_RESULT_SOLO]);	// ���U���g(�\��)
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/result001.png", &m_apTexture[CUI::TYPE_RESULT_DUO]);	// ���U���g(�f���I)
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui008.png", &m_apTexture[CUI::TYPE_START_STAGE1]);	    // �X�e�[�W1�̊J�n
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui009.png", &m_apTexture[CUI::TYPE_WARNING]);	        // ���[�j���O
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui010.png", &m_apTexture[CUI::TYPE_GET_BARRIER]);	    // �o���A���܂Ƃ�
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui011.png", &m_apTexture[CUI::TYPE_2P_TO_START]);	    // 2P�Q���҂�
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/manual000.png", &m_apTexture[CUI::TYPE_MANUAL]);	    // �V�ѕ�
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui012.png", &m_apTexture[CUI::TYPE_��CLEAR]);	        // ���N���A
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui015.png", &m_apTexture[CUI::TYPE_START_STAGE2]);	    // �X�e�[�W2�̊J�n
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui016.png", &m_apTexture[CUI::TYPE_START_STAGE3]);	    // �X�e�[�W3�̊J�n
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui017.png", &m_apTexture[CUI::TYPE_��CLEAR]);	        // ���N���A
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui018.png", &m_apTexture[CUI::TYPE_��CLEAR]);	        // ���N���A
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui021.png", &m_apTexture[CUI::TYPE_GAMEOVER]);	        // �Q�[���I�[�o�[
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui022.png", &m_apTexture[CUI::TYPE_CAREFUL_UPPER]);	// �댯�I(��)
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui023.png", &m_apTexture[CUI::TYPE_CAREFUL_LEFT]);	    // �댯�I(��)
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui024.png", &m_apTexture[CUI::TYPE_CAREFUL_RIGHT]);	// �댯�I(�E)
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui025.png", &m_apTexture[CUI::TYPE_DANGER]);	        // �f���W���[
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui026.png", &m_apTexture[CUI::TYPE_CAREFUL_DOWN]);	    // �댯�I(��)

    return S_OK;
}

//========================================
// UI�̉摜�j������
//========================================
void CUI::Unload(void)
{
    // �e�N�X�`���̔j��
    for (int nCntTexture = 0; nCntTexture < CUI::TYPE_MAX; nCntTexture++)
    {
        if (m_apTexture[nCntTexture] != NULL)
        {
            m_apTexture[nCntTexture]->Release();
            m_apTexture[nCntTexture] = NULL;
        }
    }
}

//================================
// UI�̍쐬
//================================
CUI *CUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, CUI::TYPE type)
{
    CUI *pUI = NULL;

    // ���������m��
    pUI = new CUI;

    // �^�C�v�̂݁A�e�N�X�`�������蓖�Ă̂��߂Ɍ��т��Ă���
    pUI->m_type = type;

    // ������
    pUI->Init(pos, size);

    // �����o�ϐ������т���
    pUI->m_col = col;

    return pUI;
}

//================================
// ���ӊ��N�̏���
//================================
bool CUI::Careful(void)
{
    // �ϐ��錾
    bool bUse = true;

    // �J�E���^�[��i�߂āA�p�^�[����؂�ւ���
    int nPatternAnim = CountAnimation(2, 2);

    // �F��2�p�^�[���Ő؂�ւ���
    if (nPatternAnim == 1)
    {
        m_col.a = 0.1f;
    }
    else
    {
        m_col.a = 1.0f;
    }

    // ���Ԃ��J�E���g
    m_nCntTime++;

    // ��莞�Ԍo�߂ŏ���
    if (m_nCntTime > CAREFUL_FADE_OUT_COUNT)
    {
        m_col.a = -1.0f;

        bUse = false;
    }

    // �F��ύX
    CScene2D::SetColor(m_col);

    return bUse;
}

//================================
// �f���W���[�\�L�̏���
//================================
bool CUI::Danger(void)
{
    // �ϐ��錾
    bool bUse = true;

    // �J�E���^�[��i�߂āA�p�^�[����؂�ւ���
    int nPatternAnim = CountAnimation(2, 2);

    // �F��2�p�^�[���Ő؂�ւ���
    if (nPatternAnim == 1)
    {
        m_col.a = 0.1f;
    }
    else
    {
        m_col.a = 1.0f;
    }

    // ���Ԃ��J�E���g
    m_nCntTime++;

    // ��莞�Ԍo�߂ŏ���
    if (m_nCntTime > DANGER_FADE_OUT_COUNT)
    {
        m_col.a = -1.0f;

        bUse = false;
    }

    // �F��ύX
    CScene2D::SetColor(m_col);

    return bUse;
}
