//===============================================
//
// ���C�g2D���� (light2d.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "light2d.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "game.h"
#include "enemy.h"

//=======================================
// �}�N����`
//=======================================

//=======================================
// �ÓI�����o�ϐ��錾
//=======================================
LPDIRECT3DTEXTURE9 CLight2D::m_pTexture = NULL;

//========================================
// ���C�g2D�̃R���X�g���N�^
//========================================
CLight2D::CLight2D() :CScene2D(OBJTYPE::OBJTYPE_LIGHT2D)
{
    m_col = LIGHT_SET_COLOR;
    m_nStage = -1;
}

//========================================
// ���C�g2D�̃f�X�g���N�^
//========================================
CLight2D::~CLight2D()
{

}

//========================================
// ���C�g2D�̏���������
//========================================
HRESULT CLight2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ������
    CScene2D::Init(pos, size);

    // �e�N�X�`�������蓖��
    BindTexture(m_pTexture);

    return S_OK;
}

//========================================
// ���C�g2D�̏I������
//========================================
void CLight2D::Uninit(void)
{
    // �I������
    CScene2D::Uninit();
}

//========================================
// ���C�g2D�̍X�V����
//========================================
void CLight2D::Update(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos = GetPosition();    // �ʒu���擾
    D3DXVECTOR3 size = GetSize();       // �傫�����擾
    D3DXVECTOR3 move = DEFAULT_VECTOR;  // �ړ���
    float fTargetPosX = 0.0f;           // �ڕW��X���W
    float fTargetPosY = 0.0f;           // �ڕW��Y���W
    float fMyPosX = 0.0f;               // ���g��X���W
    float fMyPosY = 0.0f;               // ���g��Y���W
    float fAngle = 0.0f;                // ���߂�p�x
    float fDistance = 0.0f;             // ����
    
    if (m_nStage == 3)
    {
        // �ڕW�̍��W�Ǝ��g�̍��W
        fTargetPosX = ENEMY_BOSS_DRAGON_STOP_POS_X, fTargetPosY = ENEMY_BOSS_DRAGON_STOP_POS_Y;
        fMyPosX = pos.x, fMyPosY = pos.y;

        // �p�x�����߂�
        fAngle = atan2f((fMyPosX - fTargetPosX), (fMyPosY - fTargetPosY));

        // �ڕW�̈ʒu�Ƃ́A�����_�ł̋���
        float fDistance = sqrtf(
            powf((pos.x - fTargetPosX), 2) +
            powf((pos.y - fTargetPosY), 2));

        // �ړI�̈ʒu�Ƌ߂����ǂ���
        if (fDistance <= LIGHT_CONSIDER_CLOSE_DEST)
        {
            // ��C�ɉ������邭
            size.x += LIGHT_EXTEND_RATE_X;
            size.y += LIGHT_EXTEND_RATE_Y;
        }
        else
        {
            // �����Ȃ�߂Â��Ă���
            move = D3DXVECTOR3(-sinf(fAngle)*LIGHT_SPOT_SPEED_4, -cosf(fAngle)*LIGHT_SPOT_SPEED_4, 0.0f);
        }
    }
    else if (m_nStage == 2)
    {
        // �ڕW�̍��W�Ǝ��g�̍��W
        fTargetPosX = LIGHT_SPOT_POS_X_3, fTargetPosY = LIGHT_SPOT_POS_Y_3;
        fMyPosX = pos.x, fMyPosY = pos.y;

        // �p�x�����߂�
        fAngle = atan2f((fMyPosX - fTargetPosX), (fMyPosY - fTargetPosY));

        // �ڕW�̈ʒu�Ƃ́A�����_�ł̋���
        float fDistance = sqrtf(
            powf((pos.x - fTargetPosX), 2) +
            powf((pos.y - fTargetPosY), 2));

        // �ړI�̈ʒu�Ƌ߂����ǂ���
        if (fDistance <= LIGHT_CONSIDER_CLOSE_DEST)
        {
            // ���C�g�̏Ƃ炷�ꏊ��ς���
            m_nStage = 3;
        }
        else
        {
            // �����Ȃ�߂Â��Ă���
            move = D3DXVECTOR3(-sinf(fAngle)*LIGHT_SPOT_SPEED_3, -cosf(fAngle)*LIGHT_SPOT_SPEED_3, 0.0f);
        }
    }
    else if (m_nStage == 1)
    {
        // �ڕW�̍��W�Ǝ��g�̍��W
        fTargetPosX = LIGHT_SPOT_POS_X_2, fTargetPosY = LIGHT_SPOT_POS_Y_2;
        fMyPosX = pos.x, fMyPosY = pos.y;

        // �p�x�����߂�
        fAngle = atan2f((fMyPosX - fTargetPosX), (fMyPosY - fTargetPosY));

        // �ڕW�̈ʒu�Ƃ́A�����_�ł̋���
        float fDistance = sqrtf(
            powf((pos.x - fTargetPosX), 2) +
            powf((pos.y - fTargetPosY), 2));

        // �ړI�̈ʒu�Ƌ߂����ǂ���
        if (fDistance <= LIGHT_CONSIDER_CLOSE_DEST)
        {
            // ���C�g�̏Ƃ炷�ꏊ��ς���
            m_nStage = 2;
        }
        else
        {
            // �����Ȃ�߂Â��Ă���
            move = D3DXVECTOR3(-sinf(fAngle)*LIGHT_SPOT_SPEED_2, -cosf(fAngle)*LIGHT_SPOT_SPEED_2, 0.0f);
        }
    }
    else if (m_nStage == 0)
    {
        // �ڕW�̍��W�Ǝ��g�̍��W
        fTargetPosX = LIGHT_SPOT_POS_X_1, fTargetPosY = LIGHT_SPOT_POS_Y_1;
        fMyPosX = pos.x, fMyPosY = pos.y;

        // �p�x�����߂�
        fAngle = atan2f((fMyPosX - fTargetPosX), (fMyPosY - fTargetPosY));

        // �ڕW�̈ʒu�Ƃ́A�����_�ł̋���
        float fDistance = sqrtf(
            powf((pos.x - fTargetPosX), 2) +
            powf((pos.y - fTargetPosY), 2));

        // �ړI�̈ʒu�Ƌ߂����ǂ���
        if (fDistance <= LIGHT_CONSIDER_CLOSE_DEST)
        {
            // ���C�g�̏Ƃ炷�ꏊ��ς���
            m_nStage = 1;
        }
        else
        {
            // �����Ȃ�߂Â��Ă���
            move = D3DXVECTOR3(-sinf(fAngle)*LIGHT_SPOT_SPEED_1, -cosf(fAngle)*LIGHT_SPOT_SPEED_1, 0.0f);
        }
    }
    else if (m_nStage == -1)
    {
        // ���񂾂�Â�����
        m_col.a += LIGHT_FADE_OUT_RATE;

        // �ő�܂ňÂ�������
        if (m_col.a >= 1.0f)
        {
            // �ő�l�ŌŒ�
            m_col.a = 1.0f;

            // ���C�g�̏Ƃ炷�ꏊ��ς���
            m_nStage = 0;
        }
    }

    // �ړ��ʂ����Z
    pos += move;

    // �F��ύX
    CScene2D::SetColor(m_col);

    // �ʒu�𔽉f
    SetPosition(pos);

    // �T�C�Y�𔽉f
    SetSize(size);

    // ���_���W��ύX
    SetVertex();

    // ���̑傫���ŏ���
    if (size.x >= LIGHT_MAX_SIZE_X)
    {
        Uninit(); // �����艺�ɃR�[�h�͏����Ȃ�
    }
}

//========================================
// ���C�g2D�̕`�揈��
//========================================
void CLight2D::Draw(void)
{
    // �`�揈��
    CScene2D::Draw();
}

//========================================
// ���C�g2D�̉摜���[�h����
//========================================
HRESULT CLight2D::Load(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    //�e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/black.png", &m_pTexture);	    // ���C�g2D

    return S_OK;
}

//========================================
// ���C�g2D�̉摜�j������
//========================================
void CLight2D::Unload(void)
{
    // �e�N�X�`���̔j��
    if (m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}

//================================
// ���C�g2D�̍쐬
//================================
CLight2D *CLight2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CLight2D *pLight2D = NULL;

    // ���������m��
    pLight2D = new CLight2D;

    // ������
    pLight2D->Init(pos, size);

    return pLight2D;
}