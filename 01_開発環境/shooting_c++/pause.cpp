//===============================================
//
// �|�[�Y���� (pause.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "pause.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "library.h"
#include "game.h"
#include "sound.h"
#include "fade.h"
#include "ui.h"

//=======================================
// �}�N����`
//=======================================

//=======================================
// �ÓI�����o�ϐ��錾
//=======================================
LPDIRECT3DTEXTURE9 CPause::m_apTexture[CPause::TYPE_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 CPause::m_pVtxBuff = NULL;
CPause::STATE CPause::m_state = CPause::STATE_NONE;

//========================================
// �|�[�Y�̃R���X�g���N�^
//========================================
CPause::CPause()
{
    m_pVtxBuff = NULL;
    m_state = STATE_NONE;
    m_typePauseSelect = TYPE_CONTINUE;
    m_typeContinueSelect = TYPE_YES;
    m_colSelect = DEFAULT_COLOR;
    m_bAlphaDown = true;
    m_nSelectCoolTime = 0;
}

//========================================
// �|�[�Y�̃f�X�g���N�^
//========================================
CPause::~CPause()
{

}

//========================================
// �|�[�Y�̏���������
//========================================
HRESULT CPause::Init(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // ���_�o�b�t�@����
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*TYPE_MAX, 
        D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
    VERTEX_2D *pVtx = NULL;	//���_���ւ̃|�C���^

    // ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//���̏����͕ς��Ȃ�����

    // ���_���W�̐ݒ�i�E���Őݒ肷��j
    // �w�i
    pVtx[0].pos = PAUSE_BG_POS + D3DXVECTOR3(-(SCREEN_WIDTH / 2), -(SCREEN_HEIGHT / 2), 0.0f);
    pVtx[1].pos = PAUSE_BG_POS + D3DXVECTOR3(+(SCREEN_WIDTH / 2), -(SCREEN_HEIGHT / 2), 0.0f);
    pVtx[2].pos = PAUSE_BG_POS + D3DXVECTOR3(-(SCREEN_WIDTH / 2), +(SCREEN_HEIGHT / 2), 0.0f);
    pVtx[3].pos = PAUSE_BG_POS + D3DXVECTOR3(+(SCREEN_WIDTH / 2), +(SCREEN_HEIGHT / 2), 0.0f);

    // �R���e�B�j���[
    pVtx[4].pos = PAUSE_CONTINUE_POS + D3DXVECTOR3(-(PAUSE_MENU_SIZE_X / 2), -(PAUSE_MENU_SIZE_Y / 2), 0.0f);
    pVtx[5].pos = PAUSE_CONTINUE_POS + D3DXVECTOR3(+(PAUSE_MENU_SIZE_X / 2), -(PAUSE_MENU_SIZE_Y / 2), 0.0f);
    pVtx[6].pos = PAUSE_CONTINUE_POS + D3DXVECTOR3(-(PAUSE_MENU_SIZE_X / 2), +(PAUSE_MENU_SIZE_Y / 2), 0.0f);
    pVtx[7].pos = PAUSE_CONTINUE_POS + D3DXVECTOR3(+(PAUSE_MENU_SIZE_X / 2), +(PAUSE_MENU_SIZE_Y / 2), 0.0f);

    // ���g���C
    pVtx[8].pos = PAUSE_RETRY_POS + D3DXVECTOR3(-(PAUSE_MENU_SIZE_X / 2), -(PAUSE_MENU_SIZE_Y / 2), 0.0f);
    pVtx[9].pos = PAUSE_RETRY_POS + D3DXVECTOR3(+(PAUSE_MENU_SIZE_X / 2), -(PAUSE_MENU_SIZE_Y / 2), 0.0f);
    pVtx[10].pos = PAUSE_RETRY_POS + D3DXVECTOR3(-(PAUSE_MENU_SIZE_X / 2), +(PAUSE_MENU_SIZE_Y / 2), 0.0f);
    pVtx[11].pos = PAUSE_RETRY_POS + D3DXVECTOR3(+(PAUSE_MENU_SIZE_X / 2), +(PAUSE_MENU_SIZE_Y / 2), 0.0f);

    // ��߂�
    pVtx[12].pos = PAUSE_QUIT_POS + D3DXVECTOR3(-(PAUSE_MENU_SIZE_X / 2), -(PAUSE_MENU_SIZE_Y / 2), 0.0f);
    pVtx[13].pos = PAUSE_QUIT_POS + D3DXVECTOR3(+(PAUSE_MENU_SIZE_X / 2), -(PAUSE_MENU_SIZE_Y / 2), 0.0f);
    pVtx[14].pos = PAUSE_QUIT_POS + D3DXVECTOR3(-(PAUSE_MENU_SIZE_X / 2), +(PAUSE_MENU_SIZE_Y / 2), 0.0f);
    pVtx[15].pos = PAUSE_QUIT_POS + D3DXVECTOR3(+(PAUSE_MENU_SIZE_X / 2), +(PAUSE_MENU_SIZE_Y / 2), 0.0f);

    // �R���e�B�j���[�̔w�i(�\��)
    pVtx[16].pos = PAUSE_BG_POS + D3DXVECTOR3(-(SCREEN_WIDTH / 2), -(SCREEN_HEIGHT / 2), 0.0f);
    pVtx[17].pos = PAUSE_BG_POS + D3DXVECTOR3(+(SCREEN_WIDTH / 2), -(SCREEN_HEIGHT / 2), 0.0f);
    pVtx[18].pos = PAUSE_BG_POS + D3DXVECTOR3(-(SCREEN_WIDTH / 2), +(SCREEN_HEIGHT / 2), 0.0f);
    pVtx[19].pos = PAUSE_BG_POS + D3DXVECTOR3(+(SCREEN_WIDTH / 2), +(SCREEN_HEIGHT / 2), 0.0f);

    // �R���e�B�j���[�̔w�i(�f���I)
    pVtx[20].pos = PAUSE_BG_POS + D3DXVECTOR3(-(SCREEN_WIDTH / 2), -(SCREEN_HEIGHT / 2), 0.0f);
    pVtx[21].pos = PAUSE_BG_POS + D3DXVECTOR3(+(SCREEN_WIDTH / 2), -(SCREEN_HEIGHT / 2), 0.0f);
    pVtx[22].pos = PAUSE_BG_POS + D3DXVECTOR3(-(SCREEN_WIDTH / 2), +(SCREEN_HEIGHT / 2), 0.0f);
    pVtx[23].pos = PAUSE_BG_POS + D3DXVECTOR3(+(SCREEN_WIDTH / 2), +(SCREEN_HEIGHT / 2), 0.0f);

    // YES
    pVtx[24].pos = PAUSE_YES_POS + D3DXVECTOR3(-(PAUSE_MENU_SIZE_X / 2), -(PAUSE_MENU_SIZE_Y / 2), 0.0f);
    pVtx[25].pos = PAUSE_YES_POS + D3DXVECTOR3(+(PAUSE_MENU_SIZE_X / 2), -(PAUSE_MENU_SIZE_Y / 2), 0.0f);
    pVtx[26].pos = PAUSE_YES_POS + D3DXVECTOR3(-(PAUSE_MENU_SIZE_X / 2), +(PAUSE_MENU_SIZE_Y / 2), 0.0f);
    pVtx[27].pos = PAUSE_YES_POS + D3DXVECTOR3(+(PAUSE_MENU_SIZE_X / 2), +(PAUSE_MENU_SIZE_Y / 2), 0.0f);

    // NO
    pVtx[28].pos = PAUSE_NO_POS + D3DXVECTOR3(-(PAUSE_MENU_SIZE_X / 2), -(PAUSE_MENU_SIZE_Y / 2), 0.0f);
    pVtx[29].pos = PAUSE_NO_POS + D3DXVECTOR3(+(PAUSE_MENU_SIZE_X / 2), -(PAUSE_MENU_SIZE_Y / 2), 0.0f);
    pVtx[30].pos = PAUSE_NO_POS + D3DXVECTOR3(-(PAUSE_MENU_SIZE_X / 2), +(PAUSE_MENU_SIZE_Y / 2), 0.0f);
    pVtx[31].pos = PAUSE_NO_POS + D3DXVECTOR3(+(PAUSE_MENU_SIZE_X / 2), +(PAUSE_MENU_SIZE_Y / 2), 0.0f);

    for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
    {
        // �F(�S�ē����ɂ���)
        pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
        pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
        pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
        pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

        // rhw�̐ݒ�i�l��1.0�Őݒ肷��j
        pVtx[0].rhw = 1.0f;
        pVtx[1].rhw = 1.0f;
        pVtx[2].rhw = 1.0f;
        pVtx[3].rhw = 1.0f;

        // �e�N�X�`�����W�̐ݒ�
        pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
        pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
        pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
        pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

        pVtx += 4;
    }

    //���_�f�[�^���A�����b�N����
    m_pVtxBuff->Unlock();

    return S_OK;
}

//========================================
// �|�[�Y�̏I������
//========================================
void CPause::Uninit(void)
{
    // ���_�o�b�t�@�̔j��
    if (m_pVtxBuff != NULL)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = NULL;
    }
}

//========================================
// �|�[�Y�̍X�V����
//========================================
void CPause::Update(void)
{
    // �L�[�{�[�h���擾
    CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

    // �R���g���[�����擾
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();
    DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_1);

    // �I�����Ă�����̂́A�F��ς���
    if (m_bAlphaDown == true)
    {
        m_colSelect.r -= PAUSE_MENU_FADE_RATE;
        m_colSelect.g -= PAUSE_MENU_FADE_RATE;
        m_colSelect.b -= PAUSE_MENU_FADE_RATE;
    }
    else
    {
        m_colSelect.r += PAUSE_MENU_FADE_RATE;
        m_colSelect.g += PAUSE_MENU_FADE_RATE;
        m_colSelect.b += PAUSE_MENU_FADE_RATE;
    }
    if (m_colSelect.r <= PAUSE_MENU_FADE_OUT_MIN)
    {
        m_bAlphaDown = false;
    }
    else if (m_colSelect.r >= 1.0f)
    {
        m_bAlphaDown = true;
    }

    // �I���̃N�[���^�C���𐔂���
    if (m_nSelectCoolTime > 0)
    {
        m_nSelectCoolTime--;
    }


    // �ϐ��錾
    // ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
    VERTEX_2D *pVtx = NULL;
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
    D3DXCOLOR inactive = PAUSE_MENU_INACTIVE_COLOR; // ��A�N�e�B�u�F

    // �|�[�Y���R���e�j���[�ŏꍇ����
    switch (m_state)
    {
    case STATE_PAUSE:

        // �X�^�[�g�{�^���������ꂽ��
        if (pInputKeyboard->GetKeyboardTrigger(DIK_P) || pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START))
        {
            // �|�[�Y�����ɂ���
            CGame::SetState(CGame::STATE_NORMAL);

            // �I�������R���e�B�j���[�֖߂�
            m_typePauseSelect = TYPE_CONTINUE;

            // ��Ԃ����Z�b�g
            m_state = STATE_NONE;
        }
        else
        {
            // �|�[�Y���j���[��I������
            SelectPauseMenu();
        }

        // �|�[�Y�̔w�i��������悤��
        pVtx[0].col = DEFAULT_COLOR;
        pVtx[1].col = DEFAULT_COLOR;
        pVtx[2].col = DEFAULT_COLOR;
        pVtx[3].col = DEFAULT_COLOR;

        // �I���ɂ���āA�F��ς���
        switch (m_typePauseSelect)
        {
        case TYPE_CONTINUE:

            // �R���e�B�j���[
            pVtx[4].col = m_colSelect;
            pVtx[5].col = m_colSelect;
            pVtx[6].col = m_colSelect;
            pVtx[7].col = m_colSelect;

            // ���g���C
            pVtx[8].col = inactive;
            pVtx[9].col = inactive;
            pVtx[10].col = inactive;
            pVtx[11].col = inactive;

            // ��߂�
            pVtx[12].col = inactive;
            pVtx[13].col = inactive;
            pVtx[14].col = inactive;
            pVtx[15].col = inactive;

            break;

        case TYPE_RETRY:

            // �R���e�B�j���[
            pVtx[4].col = inactive;
            pVtx[5].col = inactive;
            pVtx[6].col = inactive;
            pVtx[7].col = inactive;

            // ���g���C
            pVtx[8].col = m_colSelect;
            pVtx[9].col = m_colSelect;
            pVtx[10].col = m_colSelect;
            pVtx[11].col = m_colSelect;

            // ��߂�
            pVtx[12].col = inactive;
            pVtx[13].col = inactive;
            pVtx[14].col = inactive;
            pVtx[15].col = inactive;

            break;

        case TYPE_QUIT:

            // �R���e�B�j���[
            pVtx[4].col = inactive;
            pVtx[5].col = inactive;
            pVtx[6].col = inactive;
            pVtx[7].col = inactive;

            // ���g���C
            pVtx[8].col = inactive;
            pVtx[9].col = inactive;
            pVtx[10].col = inactive;
            pVtx[11].col = inactive;

            // ��߂�
            pVtx[12].col = m_colSelect;
            pVtx[13].col = m_colSelect;
            pVtx[14].col = m_colSelect;
            pVtx[15].col = m_colSelect;

            break;
        }

        break;

    case STATE_CONTINUE:

        // �R���e�B�j���[���j���[��I������
        SelectContinueMenu();

        if (CGame::GetDispHelper() == false)
        {
            // �\���̃R���e�B�j���[�̔w�i��������悤��
            pVtx[16].col = DEFAULT_COLOR;
            pVtx[17].col = DEFAULT_COLOR;
            pVtx[18].col = DEFAULT_COLOR;
            pVtx[19].col = DEFAULT_COLOR;
        }
        else
        {
            // �f���I�̃R���e�B�j���[�̔w�i��������悤��
            pVtx[20].col = DEFAULT_COLOR;
            pVtx[21].col = DEFAULT_COLOR;
            pVtx[22].col = DEFAULT_COLOR;
            pVtx[23].col = DEFAULT_COLOR;
        }

        switch (m_typeContinueSelect)
        {
        case TYPE_YES:

            // YES
            pVtx[24].col = m_colSelect;
            pVtx[25].col = m_colSelect;
            pVtx[26].col = m_colSelect;
            pVtx[27].col = m_colSelect;

            // NO
            pVtx[28].col = inactive;
            pVtx[29].col = inactive;
            pVtx[30].col = inactive;
            pVtx[31].col = inactive;

            break;

        case TYPE_NO:

            // YES
            pVtx[24].col = inactive;
            pVtx[25].col = inactive;
            pVtx[26].col = inactive;
            pVtx[27].col = inactive;

            // NO
            pVtx[28].col = m_colSelect;
            pVtx[29].col = m_colSelect;
            pVtx[30].col = m_colSelect;
            pVtx[31].col = m_colSelect;

            break;
        }

        break;
    }

    // ��Ԃ��Ȃ��Ȃ�����A�F�����Z�b�g
    if (m_state == STATE_NONE)
    {
        for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
        {
            // �F(�S�ē����ɂ���)
            pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
            pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
            pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
            pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

            pVtx += 4;
        }
    }

    //���_�f�[�^���A�����b�N����
    m_pVtxBuff->Unlock();
}

//========================================
// �|�[�Y�̕`�揈��
//========================================
void CPause::Draw(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

    // ���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_2D);

    for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
    {
        // �e�N�X�`���̐ݒ�
        pDevice->SetTexture(0, m_apTexture[nCnt]);

        // �|���S���̕`��
        pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, NUM_VERTEX * nCnt, NUM_POLYGON);
    }

    // �e�N�X�`���̐ݒ�̉���
    pDevice->SetTexture(0, NULL);
}

//========================================
// �|�[�Y�̉摜���[�h����
//========================================
HRESULT CPause::Load(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // �e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause100.png", &m_apTexture[CPause::TYPE_BG]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause000.png", &m_apTexture[CPause::TYPE_CONTINUE]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause001.png", &m_apTexture[CPause::TYPE_RETRY]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause002.png", &m_apTexture[CPause::TYPE_QUIT]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause102.png", &m_apTexture[CPause::TYPE_CONTINUE_BG_SOLO]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause101.png", &m_apTexture[CPause::TYPE_CONTINUE_BG_DUO]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause003.png", &m_apTexture[CPause::TYPE_YES]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause004.png", &m_apTexture[CPause::TYPE_NO]);

    return S_OK;
}

//========================================
// �|�[�Y�̉摜�j������
//========================================
void CPause::Unload(void)
{
    // �e�N�X�`���̔j��
    for (int nCntTexture = 0; nCntTexture < CPause::TYPE_MAX; nCntTexture++)
    {
        if (m_apTexture[nCntTexture] != NULL)
        {
            m_apTexture[nCntTexture]->Release();
            m_apTexture[nCntTexture] = NULL;
        }
    }
}

//=======================================
// �|�[�Y�̍쐬
//=======================================
CPause *CPause::Create(void)
{
    CPause *pPause = NULL;

    // ���������m��
    pPause = new CPause;

    // ������
    pPause->Init();

    return pPause;
}

//=======================================
// �|�[�Y�̃��j���[�I��
//=======================================
void CPause::SelectPauseMenu(void)
{
    // �L�[�{�[�h���擾
    CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

    // �R���g���[�����擾
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();
    DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_1);

    // �����擾
    CSound *pSound = CManager::GetSound();

    // �t�F�[�h���Ă��Ȃ��Ȃ�A�I���\
    if (CFade::GetFade() == CFade::FADE_NONE)
    {
        switch (m_typePauseSelect)
        {
        case TYPE_CONTINUE:

            // B�������ꂽ(����)
            if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_B))
            {
                // �|�[�Y�����ɂ���
                CGame::SetState(CGame::STATE_NORMAL);

                // ��Ԃ����Z�b�g
                m_state = STATE_NONE;
            }
            else
            {
                // ���ړ�
                if (pInputKeyboard->GetKeyboardTrigger(DIK_S) || Controller.lY > 0 && m_nSelectCoolTime <= 0)
                {
                    // �I����
                    pSound->Play(CSound::LABEL_SE_SELECT);

                    // ���̑I������
                    m_typePauseSelect = TYPE_RETRY;

                    // �I���̃N�[���^�C����ݒ�
                    m_nSelectCoolTime = PAUSE_MENU_SELECT_COOL_TIME;
                }
            }

            break;

        case TYPE_RETRY:

            // B�������ꂽ(����)
            if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_B))
            {
                // ���݂̃Q�[�����[�h���A����Ɍ��т���
                CManager::SetSetStage(CGame::GetStage());

                // ���g���C
                CFade::SetFade(CManager::MODE_GAME);

                // ��Ԃ����Z�b�g
                m_state = STATE_NONE;
            }
            else
            {
                // ��ړ�
                if (pInputKeyboard->GetKeyboardTrigger(DIK_W) || Controller.lY < 0 && m_nSelectCoolTime <= 0)
                {
                    // �I����
                    pSound->Play(CSound::LABEL_SE_SELECT);

                    // ��̑I������
                    m_typePauseSelect = TYPE_CONTINUE;

                    // �I���̃N�[���^�C����ݒ�
                    m_nSelectCoolTime = PAUSE_MENU_SELECT_COOL_TIME;
                }

                // ���ړ�
                if (pInputKeyboard->GetKeyboardTrigger(DIK_S) || Controller.lY > 0 && m_nSelectCoolTime <= 0)
                {
                    // �I����
                    pSound->Play(CSound::LABEL_SE_SELECT);

                    // ���̑I������
                    m_typePauseSelect = TYPE_QUIT;

                    // �I���̃N�[���^�C����ݒ�
                    m_nSelectCoolTime = PAUSE_MENU_SELECT_COOL_TIME;
                }
            }

            break;

        case TYPE_QUIT:

            // B�������ꂽ(����)
            if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_B))
            {
                // ��߂�(�^�C�g����)
                CFade::SetFade(CManager::MODE_TITLE);

                // ��Ԃ����Z�b�g
                m_state = STATE_NONE;
            }
            else
            {
                // ��ړ�
                if (pInputKeyboard->GetKeyboardTrigger(DIK_W) || Controller.lY < 0 && m_nSelectCoolTime <= 0)
                {
                    // �I����
                    pSound->Play(CSound::LABEL_SE_SELECT);

                    // ��̑I������
                    m_typePauseSelect = TYPE_RETRY;

                    // �I���̃N�[���^�C����ݒ�
                    m_nSelectCoolTime = PAUSE_MENU_SELECT_COOL_TIME;
                }
            }

            break;
        }
    }
}

//=======================================
// �R���e�B�j���[�̃��j���[�I��
//=======================================
void CPause::SelectContinueMenu(void)
{
    // �L�[�{�[�h���擾
    CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

    // �R���g���[�����擾
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();
    DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_1);

    // �����擾
    CSound *pSound = CManager::GetSound();

    // �t�F�[�h���Ă��Ȃ��Ȃ�A�I���\
    if (CFade::GetFade() == CFade::FADE_NONE)
    {
        switch (m_typeContinueSelect)
        {
        case TYPE_YES:

            // B�������ꂽ(����)
            if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_B))
            {
                // �\���ƃf���I�ŁA�R���e�B�j���[�̎d�l��ς���
                if (CGame::GetDispHelper() == false)
                {
                    // ���݂̃Q�[�����[�h���A����Ɍ��т���
                    CManager::SetSetStage(CGame::GetStage());

                    // �\���́A�������g���C
                    CFade::SetFade(CManager::MODE_GAME);
                }
                else
                {
                    // ���̏�ŃR���e�B�j���[
                    CGame::Continue();
                }

                // �|�[�Y�����ɂ���
                CGame::SetState(CGame::STATE_NORMAL);

                // ��Ԃ����Z�b�g
                m_state = STATE_NONE;
            }
            else
            {
                // �E�ړ�
                if (pInputKeyboard->GetKeyboardTrigger(DIK_D) || Controller.lX > 0 && m_nSelectCoolTime <= 0)
                {
                    // �I����
                    pSound->Play(CSound::LABEL_SE_SELECT);

                    // �E�̑I������
                    m_typeContinueSelect = TYPE_NO;

                    // �I���̃N�[���^�C����ݒ�
                    m_nSelectCoolTime = PAUSE_MENU_SELECT_COOL_TIME;
                }
            }

            break;

        case TYPE_NO:

            // B�������ꂽ(����)
            if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_B))
            {
                // �Q�[���I�[�o�[
                CGame::SetGameOver();

                // �Q�[���I�[�o�[���N���G�C�g
                CUI::Create(GAMEOVER_POS, GAMEOVER_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f), CUI::TYPE_GAMEOVER);

                // �|�[�Y�����ɂ���
                CGame::SetState(CGame::STATE_NORMAL);

                // ��Ԃ����Z�b�g
                m_state = STATE_NONE;
            }
            else
            {
                // ���ړ�
                if (pInputKeyboard->GetKeyboardTrigger(DIK_A) || Controller.lX < 0 && m_nSelectCoolTime <= 0)
                {
                    // �I����
                    pSound->Play(CSound::LABEL_SE_SELECT);

                    // ���̑I������
                    m_typeContinueSelect = TYPE_YES;

                    // �I���̃N�[���^�C����ݒ�
                    m_nSelectCoolTime = PAUSE_MENU_SELECT_COOL_TIME;
                }
            }

            break;
        }
    }
}
