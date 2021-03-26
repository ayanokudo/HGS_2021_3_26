//===============================================
//
// �A�C�e������ (item.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "item.h"
#include "library.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"
#include "game.h"

//=======================================
// �ÓI�����o�ϐ��錾
//=======================================
LPDIRECT3DTEXTURE9 CItem::m_apTexture[CItem::TYPE_MAX] = {};

//========================================
// �A�C�e���̃R���X�g���N�^
//========================================
CItem::CItem() :CScene2D(OBJTYPE::OBJTYPE_ITEM)
{
    m_type = CItem::TYPE_MAX;
    m_fAngle = 0.0f;
    m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//========================================
// �A�C�e���̃f�X�g���N�^
//========================================
CItem::~CItem()
{
}

//========================================
// �A�C�e���̏���������
//========================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ������
    CScene2D::Init(pos, size);

    // �e�N�X�`�������蓖��
    BindTexture(m_apTexture[m_type]);

    return S_OK;
}

//========================================
// �A�C�e���̏I������
//========================================
void CItem::Uninit(void)
{
    // �I������
    CScene2D::Uninit();
}

//========================================
// �A�C�e���̍X�V����
//========================================
void CItem::Update(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos = GetPosition();    // �ʒu���擾
    D3DXVECTOR3 size = GetSize();       // �T�C�Y���擾
    bool bUse = true;                   // �g�p���邩�ǂ���

    // �^�C�v���Ƃɓ������ꍇ����
    switch (m_type)
    {
    case CItem::TYPE_BARRIER:

        // �G�t�F�N�g�𐶐�(�T�C�Y�͈���傫��)
        CEffect::Create(pos, size + ITEM_EFFECT_ADD_SIZE,
            BARRIER_COLOR, CEffect::TYPE_PARTICLE_JPG);

        // �p�x���Z
        m_fAngle += ITEM_ROT_ANGLE;

        // �ړ��ʂ��ʒu�ɉ��Z
        pos.x += sinf(m_fAngle) * ITEM_SPEED - ITEM_FLOWING_SPEED;
        pos.y += -cosf(m_fAngle) * ITEM_SPEED;

        break;

    case CItem::TYPE_STOCK:

        // �G�t�F�N�g�𐶐�(�T�C�Y�͈���傫��)
        CEffect::Create(pos, size + ITEM_EFFECT_ADD_SIZE,
            STOCK_COLOR, CEffect::TYPE_PARTICLE_JPG);

        // �d��(�y�߂ɐݒ�)
        m_move.y += GRAVITY / 4;
        pos.y += m_move.y;

        // ���Ƃ̓����蔻��
        if (CGame::GetFloor() == true)
        {
            // ���ɓ������Ă���Ȃ�
            if (pos.y + (size.y / 2) >= FLOOR_COLLISION)
            {
                // �C��Ȃ�
                if (CGame::GetStage() == CManager::STAGE_��)
                {
                    // ���ɂ߂荞�܂Ȃ�
                    pos.y = FLOOR_COLLISION - (size.y / 2);

                    // ���֗����
                    pos.x -= FLOWING_STAGE;

                    // �d�͂����Z�b�g
                    m_move.y = 0.0f;
                }
                // �ΎR�Ȃ�
                else if (CGame::GetStage() == CManager::STAGE_��)
                {
                    // �����G�t�F�N�g(�}�O�}�Ō����Â炢�̂ŁA�傫��)
                    CEffect::Create(pos, EXPLOSION_SIZE * 3,
                        DEFAULT_COLOR, CEffect::TYPE_EXPLOSION);

                    // ���g�p��
                    bUse = false;
                }
            }
        }

        break;
    }

    // �ʒu�𔽉f
    SetPosition(pos);

    // ���_���W��ύX
    SetVertex();

    // ��ʊO�ɏo���疢�g�p��
    if (OutGame2D(&pos, &size) == true)
    {
        bUse = false;
    }

    // �g�p���Ȃ��Ȃ�A�I������
    if (bUse == false)
    {
        Uninit(); // �����艺�ɃR�[�h�͏����Ȃ�
    }
}

//========================================
// �A�C�e���̕`�揈��
//========================================
void CItem::Draw(void)
{
    // �`�揈��
    CScene2D::Draw();
}

//========================================
// �A�C�e���̉摜���[�h����
//========================================
HRESULT CItem::Load(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // �e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/item000.png", &m_apTexture[CItem::TYPE_BARRIER]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/item001.png", &m_apTexture[CItem::TYPE_STOCK]);

    return S_OK;
}

//========================================
// �A�C�e���̉摜�j������
//========================================
void CItem::Unload(void)
{
    // �e�N�X�`���̔j��
    for (int nCntTexture = 0; nCntTexture < CItem::TYPE_MAX; nCntTexture++)
    {
        if (m_apTexture[nCntTexture] != NULL)
        {
            m_apTexture[nCntTexture]->Release();
            m_apTexture[nCntTexture] = NULL;
        }
    }
}

//================================
// �A�C�e���̐���
//================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
    CItem *pItem = NULL;

    // ���������m��
    pItem = new CItem;

    // �^�C�v�̂݁A�e�N�X�`�����蓖�Ă̂��߂Ɍ��т��Ă���
    pItem->m_type = type;

    // ������
    pItem->Init(pos, size);

    return pItem;
}
