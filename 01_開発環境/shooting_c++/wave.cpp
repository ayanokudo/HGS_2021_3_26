//===============================================
//
// �g���� (wave.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "wave.h"
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
LPDIRECT3DTEXTURE9 CWave::m_apTexture[CWave::TYPE_MAX] = {};

//========================================
// �g�̃R���X�g���N�^
//========================================
CWave::CWave() :CScene2D(OBJTYPE::OBJTYPE_WAVE)
{
    m_bExtend = false;
    m_bToBlue = true;
    m_move = DEFAULT_VECTOR;
    m_col = DEFAULT_COLOR;
    m_type = CWave::TYPE_MAX;
}

//========================================
// �g�̃f�X�g���N�^
//========================================
CWave::~CWave()
{

}

//========================================
// �g�̏���������
//========================================
HRESULT CWave::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ������
    CScene2D::Init(pos, size);

    // �e�N�X�`�������蓖��
    BindTexture(m_apTexture[m_type]);

    return S_OK;
}

//========================================
// �g�̏I������
//========================================
void CWave::Uninit(void)
{
    // �I������
    CScene2D::Uninit();
}

//========================================
// �g�̍X�V����
//========================================
void CWave::Update(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos = GetPosition();                   // �ʒu���擾
    D3DXVECTOR3 size = GetSize();                      // �T�C�Y���擾
    float fAngle = 0.0f;                               // �p�x
    float fRadius = 0.0f;                              // ���a

    switch (m_type)
    {
    case TYPE_BIG_WAVE:

        // �ɋ߂Â��邩�A�������邩
        if (m_bToBlue == true)
        {
            m_col.r -= WAVE_FADE_RATE;
            m_col.g -= WAVE_FADE_RATE;
        }
        else
        {
            m_col.r += WAVE_FADE_RATE;
            m_col.g += WAVE_FADE_RATE;
        }

        // �g�傷�邩�A�k�����邩
        if (m_bExtend == true)
        {
            size.y += WAVE_EXTEND_RATE;
        }
        else
        {
            size.y -= WAVE_EXTEND_RATE;
        }

        // �e�N�X�`���̒��_���W��ύX
        SetFlowingAnimation(1, 400, true, CScene2D::DIRECT_RIGHT_DOWN);

        break;

    case TYPE_BIG_WAVE2:

        // �ɋ߂Â��邩�A�������邩
        if (m_bToBlue == true)
        {
            m_col.r -= WAVE_FADE_RATE2;
            m_col.g -= WAVE_FADE_RATE2;
        }
        else
        {
            m_col.r += WAVE_FADE_RATE2;
            m_col.g += WAVE_FADE_RATE2;
        }

        // �g�傷�邩�A�k�����邩
        if (m_bExtend == true)
        {
            size.y += WAVE_EXTEND_RATE2;
        }
        else
        {
            size.y -= WAVE_EXTEND_RATE2;
        }

        // �e�N�X�`���̒��_���W��ύX
        SetFlowingAnimation(1, 500, true, CScene2D::DIRECT_HORIZON);

        break;
    }

    // �T�C�Y��ς���
    if (m_col.r > 1.0f)
    {
        m_bToBlue = true;
    }
    else if (m_col.r < WAVE_MIN_COLOR)
    {
        m_bToBlue = false;
    }

    // �T�C�Y��ς���
    if (size.y > SCREEN_HEIGHT)
    {
        m_bExtend = false;
    }
    else if(size.y < WAVE_MIN_SIZE)
    {
        m_bExtend = true;
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
// �g�̕`�揈��
//========================================
void CWave::Draw(void)
{
    // �`�揈��
    CScene2D::Draw();
}

//========================================
// �g�̉摜���[�h����
//========================================
HRESULT CWave::Load(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // �e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/wave000.png", &m_apTexture[CWave::TYPE_BIG_WAVE]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/wave001.png", &m_apTexture[CWave::TYPE_BIG_WAVE2]);

    return S_OK;
}

//========================================
// �g�̉摜�j������
//========================================
void CWave::Unload(void)
{
    // �e�N�X�`���̔j��
    for (int nCntTexture = 0; nCntTexture < CWave::TYPE_MAX; nCntTexture++)
    {
        if (m_apTexture[nCntTexture] != NULL)
        {
            m_apTexture[nCntTexture]->Release();
            m_apTexture[nCntTexture] = NULL;
        }
    }
}

//================================
// �g�̍쐬
//================================
CWave *CWave::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, CWave::TYPE type)
{
    CWave *pWave = NULL;

    // ���������m��
    pWave = new CWave;

    // �^�C�v�̂݁A�e�N�X�`�������蓖�Ă̂��߂Ɍ��т��Ă���
    pWave->m_type = type;

    // ������
    pWave->Init(pos, size);

    // �����o�ϐ������т���
    pWave->m_col = col;

    // ��ނɉ������ꍇ����
    switch (type)
    {
    case TYPE_BIG_WAVE:

        pWave->m_bExtend = false;

        pWave->m_bToBlue = true;

        break;

    case TYPE_BIG_WAVE2:

        pWave->m_bExtend = true;

        pWave->m_bToBlue = false;

        break;
    }

    return pWave;
}