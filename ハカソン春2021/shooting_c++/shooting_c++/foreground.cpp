//===============================================
//
// �O�i���� (foreground.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "foreground.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "game.h"
#include "input.h"

//=======================================
// �}�N����`
//=======================================

#define COOL_TIME 12

//=======================================
// �ÓI�����o�ϐ��錾
//=======================================
LPDIRECT3DTEXTURE9 CForeground::m_apTexture[CForeground::TYPE_MAX] = {};

CForeground::DIRECT CForeground::direct1 = CForeground::DIRECT_LEFT;
CForeground::DIRECT CForeground::direct2 = CForeground::DIRECT_LEFT;
CForeground::DIRECT CForeground::direct3 = CForeground::DIRECT_LEFT;

//========================================
// �O�i�̃R���X�g���N�^
//========================================
CForeground::CForeground() :CScene2D(OBJTYPE::OBJTYPE_FOREGROUND)
{
    m_col = DEFAULT_COLOR;
    m_type = CForeground::TYPE_MAX;

    m_scroll = CForeground::SCROLL_1;
    m_nSelectCoolTime = 0;

    direct1 = DIRECT_LEFT;
    direct2 = DIRECT_LEFT;
    direct3 = DIRECT_LEFT;
}

//========================================
// �O�i�̃f�X�g���N�^
//========================================
CForeground::~CForeground()
{

}

//========================================
// �O�i�̏���������
//========================================
HRESULT CForeground::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ������
    CScene2D::Init(pos, size);

    // �e�N�X�`�������蓖��
    BindTexture(m_apTexture[m_type]);

    return S_OK;
}

//========================================
// �O�i�̏I������
//========================================
void CForeground::Uninit(void)
{
    // �I������
    CScene2D::Uninit();
}

//========================================
// �O�i�̍X�V����
//========================================
void CForeground::Update(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos = GetPosition();                   // �ʒu���擾
    D3DXVECTOR3 size = GetSize();                      // �T�C�Y���擾

    switch (m_type)
    {
    case TYPE_FOREST:

        // �{�X�o�g���̎��A����
        if (CGame::GetBossBattle() == true)
        {
            m_col.a -= FOREGROUND_FOREST_FADE_RATE;
        }

        // �e�N�X�`���̒��_���W��ύX
        //SetFlowingAnimation(1, FOREGROUND_FOREST_FLOWING_SPEED, true, CScene2D::DIRECT_HORIZON);

        Forest();

        switch (m_scroll)
        {
        case SCROLL_1:
            pos = SCROLL_POS_1;
            break;

        case SCROLL_2:
            pos = SCROLL_POS_2;
            break;

        case SCROLL_3:
            pos = SCROLL_POS_3;
            break;
        }

        break;

    case TYPE_CORAL:

        // �{�X�o�g���̎��ȊO�A����
        if (CGame::GetBossBattle() == false)
        {
            // �e�N�X�`���̒��_���W��ύX
            SetFlowingAnimation(1, FOREGROUND_CORAL_FLOWING_SPEED, true, CScene2D::DIRECT_HORIZON);
        }

        break;
    }

    // �F�𔽉f
    SetColor(m_col);

    // �ʒu�𔽉f
    SetPosition(pos);

    // �T�C�Y�𔽉f
    SetSize(size);

    // ���_���W��ݒ�
    SetVertex();

    // �����Ȃ����
    if (m_col.a < 0)
    {
        Uninit(); // �����艺�ɃR�[�h�͏����Ȃ�
    }
}

//========================================
// �O�i�̕`�揈��
//========================================
void CForeground::Draw(void)
{
    // �`�揈��
    CScene2D::Draw();
}

//========================================
// �O�i�̉摜���[�h����
//========================================
HRESULT CForeground::Load(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // �e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/foreground000.png", &m_apTexture[CForeground::TYPE_FOREST]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/foreground001.png", &m_apTexture[CForeground::TYPE_CORAL]);

    return S_OK;
}

//========================================
// �O�i�̉摜�j������
//========================================
void CForeground::Unload(void)
{
    // �e�N�X�`���̔j��
    for (int nCntTexture = 0; nCntTexture < CForeground::TYPE_MAX; nCntTexture++)
    {
        if (m_apTexture[nCntTexture] != NULL)
        {
            m_apTexture[nCntTexture]->Release();
            m_apTexture[nCntTexture] = NULL;
        }
    }
}

//================================
// �O�i�̍쐬
//================================
CForeground *CForeground::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, CForeground::TYPE type)
{
    CForeground *pForeground = NULL;

    // ���������m��
    pForeground = new CForeground;

    // �^�C�v�̂݁A�e�N�X�`�������蓖�Ă̂��߂Ɍ��т��Ă���
    pForeground->m_type = type;

    // ������
    pForeground->Init(pos, size);

    // �����o�ϐ������т���
    pForeground->m_col = col;

    return pForeground;
}

void CForeground::Forest(void)
{
    // �I���̃N�[���^�C���𐔂���
    if (m_nSelectCoolTime > 0)
    {
        m_nSelectCoolTime--;
    }

    // �R���g���[�����擾
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();
    DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_1);

    //��
    if (Controller.rgdwPOV[0] == BUTTON_LEFT)
    {
        switch (m_scroll)
        {
        case SCROLL_1:
            direct1 = DIRECT_LEFT;
            break;
        case SCROLL_2:
            direct2 = DIRECT_LEFT;
            break;
        case SCROLL_3:
            direct3 = DIRECT_LEFT;
            break;
        }
    }

    //�E
    if (Controller.rgdwPOV[0] == BUTTON_RIGHT)
    {
        switch (m_scroll)
        {
        case SCROLL_1:
            direct1 = DIRECT_RIGHT;
            break;
        case SCROLL_2:
            direct2 = DIRECT_RIGHT;
            break;
        case SCROLL_3:
            direct3 = DIRECT_RIGHT;
            break;
        }
    }

    
    if (m_nSelectCoolTime <= 0)
    {
        //��
        if (Controller.rgdwPOV[0] == BUTTON_UP)
        {
            if (m_scroll == SCROLL_2)
            {
                m_scroll = SCROLL_1;

                // �I���̃N�[���^�C����ݒ�
                m_nSelectCoolTime = COOL_TIME;
            }
            else if (m_scroll == SCROLL_3)
            {
                m_scroll = SCROLL_2;

                // �I���̃N�[���^�C����ݒ�
                m_nSelectCoolTime = COOL_TIME;
            }
        }

        //��
        if (Controller.rgdwPOV[0] == BUTTON_DOWN)
        {
            if (m_scroll == SCROLL_1)
            {
                m_scroll = SCROLL_2;

                // �I���̃N�[���^�C����ݒ�
                m_nSelectCoolTime = COOL_TIME;
            }
            else if (m_scroll == SCROLL_2)
            {
                m_scroll = SCROLL_3;

                // �I���̃N�[���^�C����ݒ�
                m_nSelectCoolTime = COOL_TIME;
            }
        }
    }

}
