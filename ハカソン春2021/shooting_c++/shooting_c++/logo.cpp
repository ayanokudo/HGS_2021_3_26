//===============================================
//
// ���S���� (logo.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "logo.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "library.h"
#include "game.h"
#include "effect.h"
#include "sound.h"
#include "whiteFade.h"
#include "player.h"

//=======================================
// �}�N����`
//=======================================

//=======================================
// �ÓI�����o�ϐ��錾
//=======================================
LPDIRECT3DTEXTURE9 CLogo::m_apTexture[CLogo::TYPE_MAX] = {};

//========================================
// ���S�̃R���X�g���N�^
//========================================
CLogo::CLogo() :CScene2D(OBJTYPE::OBJTYPE_LOGO)
{
    m_col = DEFAULT_COLOR;
    m_type = CLogo::TYPE_MAX;
}

//========================================
// ���S�̃f�X�g���N�^
//========================================
CLogo::~CLogo()
{

}

//========================================
// ���S�̏���������
//========================================
HRESULT CLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ������
    CScene2D::Init(pos, size);

    // �e�N�X�`�������蓖��
    BindTexture(m_apTexture[m_type]);

    return S_OK;
}

//========================================
// ���S�̏I������
//========================================
void CLogo::Uninit(void)
{
    // �I������
    CScene2D::Uninit();
}

//========================================
// ���S�̍X�V����
//========================================
void CLogo::Update(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos = GetPosition();                   // �ʒu���擾
    D3DXVECTOR3 size = GetSize();                      // �T�C�Y���擾

    switch (m_type)
    {
    case TYPE_TITLE_BG:

        // �e�N�X�`���̒��_���W��ύX
        SetAnimation(10, 5);

        break;

    case TYPE_RESULT_BG:

        // �e�N�X�`���̒��_���W��ύX
        //SetFlowingAnimation(1, 400, true, CScene2D::DIRECT_RIGHT_DOWN);

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
}

//========================================
// ���S�̕`�揈��
//========================================
void CLogo::Draw(void)
{
    // �`�揈��
    CScene2D::Draw();
}

//========================================
// ���S�̉摜���[�h����
//========================================
HRESULT CLogo::Load(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // �e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title000.png", &m_apTexture[CLogo::TYPE_TITLE_BG]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/logo000.png", &m_apTexture[CLogo::TYPE_RESULT_BG]);

    return S_OK;
}

//========================================
// ���S�̉摜�j������
//========================================
void CLogo::Unload(void)
{
    // �e�N�X�`���̔j��
    for (int nCntTexture = 0; nCntTexture < CLogo::TYPE_MAX; nCntTexture++)
    {
        if (m_apTexture[nCntTexture] != NULL)
        {
            m_apTexture[nCntTexture]->Release();
            m_apTexture[nCntTexture] = NULL;
        }
    }
}

//================================
// ���S�̍쐬
//================================
CLogo *CLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, CLogo::TYPE type)
{
    CLogo *pLogo = NULL;

    // ���������m��
    pLogo = new CLogo;

    // �^�C�v�̂݁A�e�N�X�`�������蓖�Ă̂��߂Ɍ��т��Ă���
    pLogo->m_type = type;

    // ������
    pLogo->Init(pos, size);

    // �����o�ϐ������т���
    pLogo->m_col = col;

    return pLogo;
}