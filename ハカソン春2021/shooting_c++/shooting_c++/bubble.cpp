//===============================================
//
// �A���� (bubble.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "bubble.h"
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
LPDIRECT3DTEXTURE9 CBubble::m_pTexture = NULL;

//========================================
// �A�̃R���X�g���N�^
//========================================
CBubble::CBubble() :CScene2D(OBJTYPE::OBJTYPE_BUBBLE)
{
    m_move = DEFAULT_VECTOR;
    m_posSet = DEFAULT_VECTOR;
    m_col = DEFAULT_COLOR;
    m_type = CBubble::TYPE_MAX;
}

//========================================
// �A�̃f�X�g���N�^
//========================================
CBubble::~CBubble()
{

}

//========================================
// �A�̏���������
//========================================
HRESULT CBubble::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ������
    CScene2D::Init(pos, size);

    // �e�N�X�`�������蓖��
    BindTexture(m_pTexture);

    return S_OK;
}

//========================================
// �A�̏I������
//========================================
void CBubble::Uninit(void)
{
    // �I������
    CScene2D::Uninit();
}

//========================================
// �A�̍X�V����
//========================================
void CBubble::Update(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos = GetPosition();                   // �ʒu���擾

    // �ړ��ʂ��ʒu�ɔ��f(�ߋ����玗�����̂�������������A������������x�����Ă���)
    pos += m_move / 3;

    // ���E�̈ړ��͈�
    if (pos.x < m_posSet.x - BUBBLE_RETURN_POS || 
        pos.x > m_posSet.x + BUBBLE_RETURN_POS)
    {
        // ���˕Ԃ�
        m_move.x *= -1;
    }

    // �����x��������
    m_col.a -= BUBBLE_FADE_OUT_RATE;

    // �F��ύX
    CScene2D::SetColor(m_col);

    // �ʒu�𔽉f
    SetPosition(pos);

    // ���_���W��ύX
    SetVertex();

    // �����Ȃ����
    if (m_col.a < 0)
    {
        Uninit(); // �����艺�ɃR�[�h�͏����Ȃ�
    }
}

//========================================
// �A�̕`�揈��
//========================================
void CBubble::Draw(void)
{
    // ���Z����
    SetAdditiveSynthesis();

    // �`�揈��
    CScene2D::Draw();
}

//========================================
// �A�̉摜���[�h����
//========================================
HRESULT CBubble::Load(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    //�e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &m_pTexture);	    // �A

    return S_OK;
}

//========================================
// �A�̉摜�j������
//========================================
void CBubble::Unload(void)
{
    // �e�N�X�`���̔j��
    if (m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}

//================================
// �A�̍쐬
//================================
CBubble *CBubble::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CBubble::TYPE type)
{
    CBubble *pBubble = NULL;

    // ���������m��
    pBubble = new CBubble;

    // �^�C�v�̂݁A�e�N�X�`�������蓖�Ă̂��߂Ɍ��т��Ă���
    pBubble->m_type = type;

    // ������
    pBubble->Init(pos, size);

    // �����ʒu�A�F�����т���
    pBubble->m_posSet = pos;
    pBubble->m_col = BUBBLE_COLOR;

    // ��ނɂ���āA�ړ��ʂ�ς���
    switch (pBubble->m_type)
    {
    case TYPE_MINIMUM:
        pBubble->m_move = BUBBLE_MINIMUM_MOVE;
        break;

    case TYPE_SMALL:
        pBubble->m_move = BUBBLE_SMALL_MOVE;
        break;

    case TYPE_NORMAL:
        pBubble->m_move = BUBBLE_NORMAL_MOVE;
        break;

    case TYPE_NORMAL2:
        pBubble->m_move = BUBBLE_NORMAL2_MOVE;
        break;

    case TYPE_BIG:
        pBubble->m_move = BUBBLE_BIG_MOVE;
        break;

    case TYPE_MAXIMUM:
        pBubble->m_move = BUBBLE_MAXIMUM_MOVE;
        break;
    }

    return pBubble;
}