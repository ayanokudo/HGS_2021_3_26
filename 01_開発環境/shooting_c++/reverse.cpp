//===============================================
//
// ���]�������� (reverse.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "reverse.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "library.h"
#include "player.h"
#include "bullet.h"
#include "game.h"

//=======================================
// �}�N����`
//=======================================

//=======================================
// �ÓI�����o�ϐ��錾
//=======================================
LPDIRECT3DTEXTURE9 CReverse::m_pTexture = NULL;

//========================================
// ���]�����̃R���X�g���N�^
//========================================
CReverse::CReverse() :CScene2D(OBJTYPE::OBJTYPE_REVERSE)
{
    m_move = DEFAULT_VECTOR;
    m_col = DEFAULT_COLOR;
}

//========================================
// ���]�����̃f�X�g���N�^
//========================================
CReverse::~CReverse()
{

}

//========================================
// ���]�����̏���������
//========================================
HRESULT CReverse::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ������
    CScene2D::Init(pos, size);

    // �e�N�X�`�������蓖��
    BindTexture(m_pTexture);

    return S_OK;
}

//========================================
// ���]�����̏I������
//========================================
void CReverse::Uninit(void)
{
    // �I������
    CScene2D::Uninit();
}

//========================================
// ���]�����̍X�V����
//========================================
void CReverse::Update(void)
{
    // �ϐ��錾
    D3DXVECTOR3 size = GetSize();   // �傫�����擾

    // �傫�����ő�܂Ŋg��
    if (size.x <= REVERSE_MAX_SIZE)
    {
        size.x += REVERSE_EXTEND_RATE;
        size.y += REVERSE_EXTEND_RATE;
    }
    // �傫�����ő�Ȃ�
    else
    {
        // �����x��������
        m_col.a -= REVERSE_FADE_OUT_RATE;
    }

    // �F��ύX
    CScene2D::SetColor(m_col);

    // �傫���𔽉f
    SetSize(size);

    // ���_���W��ύX
    SetVertex();

    // �����Ȃ����
    if (m_col.a < 0)
    {
        Uninit(); // �����艺�ɃR�[�h�͏����Ȃ�
    }
}

//========================================
// ���]�����̕`�揈��
//========================================
void CReverse::Draw(void)
{
    // ���]������
    CScene2D::SetNega();

    // �`�揈��
    CScene2D::Draw();
}

//========================================
// ���]�����̉摜���[�h����
//========================================
HRESULT CReverse::Load(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    //�e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/reverse000.png", &m_pTexture);	    // ���]����

    return S_OK;
}

//========================================
// ���]�����̉摜�j������
//========================================
void CReverse::Unload(void)
{
    // �e�N�X�`���̔j��
    if (m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}

//================================
// ���]�����̍쐬
//================================
CReverse *CReverse::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CReverse *pReverse = NULL;

    // ���������m��
    pReverse = new CReverse;

    // ������
    pReverse->Init(pos, size);

    // �F�����т���
    pReverse->m_col = DEFAULT_COLOR;

    return pReverse;
}