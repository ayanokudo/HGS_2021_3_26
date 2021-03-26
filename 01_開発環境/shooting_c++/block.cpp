//===============================================
//
// �u���b�N���� (block.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "block.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "game.h"
#include "effect.h"
#include "sound.h"

//=======================================
// �ÓI�����o�ϐ��錾
//=======================================
LPDIRECT3DTEXTURE9 CBlock::m_apTexture[CBlock::TYPE_MAX] = {};

//========================================
// �u���b�N�̃R���X�g���N�^
//========================================
CBlock::CBlock() :CScene2D(OBJTYPE::OBJTYPE_BLOCK)
{
    m_posOld = DEFAULT_VECTOR;
    m_collisionSize = DEFAULT_VECTOR;
    m_move = DEFAULT_VECTOR;
    m_nCntChangeMove = 0;
    m_fRotAngle = 0.0f;
    m_bRotRight = false;
    m_type = CBlock::TYPE_MAX;
}

//========================================
// �u���b�N�̃f�X�g���N�^
//========================================
CBlock::~CBlock()
{

}

//========================================
// �u���b�N�̏���������
//========================================
HRESULT CBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ������
    CScene2D::Init(pos, size);

    // �e�N�X�`�������蓖��
    BindTexture(m_apTexture[m_type]);

    return S_OK;
}

//========================================
// �u���b�N�̏I������
//========================================
void CBlock::Uninit(void)
{
    // �I������
    CScene2D::Uninit();
}

//========================================
// �u���b�N�̍X�V����
//========================================
void CBlock::Update(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos = GetPosition();    // �ʒu���擾
    D3DXVECTOR3 size = GetSize();       // �T�C�Y���擾
    bool bUse = true;                   // �g�p���邩�ǂ���

    // 1F�O�̈ʒu���L��
    m_posOld = pos;

    // ��ނɉ������ꍇ����
    switch (m_type)
    {
    case CBlock::TYPE_APPLE:

        // �ړ����ς�肾���܂ł̃J�E���^�𐔂���
        m_nCntChangeMove++;

        // �������J�n����܂ł̃J�E���^
        if (m_nCntChangeMove >= BLOCK_APPLE_FALL_COUNT)
        {
            // �ʏ�F
            CScene2D::SetColor(DEFAULT_COLOR);

            // �d�͂������y�߂ɐݒ�
            m_move.y += GRAVITY / 4;

            // �t���O�ɂ���āA�Eor����]
            if (m_bRotRight == true)
            {
                // �E��]
                m_fRotAngle += BLOCK_APPLE_ROT_SPEED;
            }
            else
            {
                // ����]
                m_fRotAngle -= BLOCK_APPLE_ROT_SPEED;
            }
        }
        // ��������O�͓_��
        else
        {
            // �J�E���^�[��i�߂āA�p�^�[����؂�ւ���
            int nPatternAnim = CountAnimation(2, 2);

            // �_��
            if (nPatternAnim == 1)
            {
                // �ʏ�F
                CScene2D::SetColor(DEFAULT_COLOR);
            }
            else
            {
                // ����
                CScene2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
            }
        }

        break;

    case CBlock::TYPE_ROCK:

        // �t���O�ɂ���ĉ�]
        if (m_bRotRight == true)
        {
            // �d�͂������y�߂ɐݒ�
            m_move.y += GRAVITY / 8;

            // �����̍ō����x�����߂�
            if (m_move.y >= BLOCK_ROCK_MAX_FALL_SPEED)
            {
                m_move.y = BLOCK_ROCK_MAX_FALL_SPEED;
            }

            // �ǂ���ɉ���Ă��邩�ŏꍇ����
            if (m_fRotAngle > 0.0f)
            {
                // �E��]
                m_fRotAngle += BLOCK_ROCK_ROT_SPEED;
            }
            else
            {
                // ����]
                m_fRotAngle -= BLOCK_ROCK_ROT_SPEED;
            }
        }

        break;

    case TYPE_METEO:

        // 覐΂̏Փˏ���
        bUse = MeteoInpact(pos, size);

        // ����]
        m_fRotAngle -= BLOCK_METEO_ROT_SPEED;

        // �G�t�F�N�g�𐶐�(�T�C�Y�͈���傫��)
        CEffect::Create(pos, size + D3DXVECTOR3(25.0f, 25.0f, 0.0f),
            EFFECT_PURPLE_FIRE_FIRST_COLOR, CEffect::TYPE_PURPLE_FIRE);

        break;
    }

    // �ړ��ʂ��ʒu�ɉ��Z
    pos += m_move;

    // �o�E���h
    pos = Bound(pos, size);

    // �ʒu�𔽉f
    SetPosition(pos);

    // ���_���W��ύX
    SetRotVertex(m_fRotAngle);

    // ��ʂ̒[����2�{�̏ꏊ����o����
    if (OutGame2D(&pos, &size) == true)
    {
        // �g�p�t���O��false��
        bUse = false;
    }

    // �g�p�t���O��false�Ȃ�
    if (bUse == false)
    {
        // ���g�p��
        Uninit();
    }
}

//========================================
// �u���b�N�̕`�揈��
//========================================
void CBlock::Draw(void)
{
    // �`�揈��
    CScene2D::Draw();
}

//========================================
// �u���b�N�̉摜���[�h����
//========================================
HRESULT CBlock::Load(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // �e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block000.png", &m_apTexture[CBlock::TYPE_APPLE]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block001.png", &m_apTexture[CBlock::TYPE_ROCK]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block002.png", &m_apTexture[CBlock::TYPE_METEO]);

    return S_OK;
}

//========================================
// �u���b�N�̉摜�j������
//========================================
void CBlock::Unload(void)
{
    // �e�N�X�`���̔j��
    for (int nCntTexture = 0; nCntTexture < CBlock::TYPE_MAX; nCntTexture++)
    {
        if (m_apTexture[nCntTexture] != NULL)
        {
            m_apTexture[nCntTexture]->Release();
            m_apTexture[nCntTexture] = NULL;
        }
    }
}

//================================
// �u���b�N�̍쐬
//================================
CBlock *CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, bool bRotRight, CBlock::TYPE type)
{
    CBlock *pBlock = NULL;

    // ���������m��
    pBlock = new CBlock;

    // �^�C�v�̂݁A�e�N�X�`�����蓖�Ă̂��߂Ɍ��т��Ă���
    pBlock->m_type = type;

    // ������
    pBlock->Init(pos, size);

    // �����o�ϐ������т���
    pBlock->m_posOld = pos;
    pBlock->m_bRotRight = bRotRight;

    // �u���b�N�̎�ނɂ���āA�Œ�̒l�����т���
    int nRandNum = 0;       // �����_���Ȓl
    float fAngle = 0.0f;    // �p�x
    switch (pBlock->m_type)
    {
    case CBlock::TYPE_APPLE:

        pBlock->m_collisionSize = BLOCK_APPLE_COLLISION_SIZE;
        pBlock->m_move = DEFAULT_VECTOR;

        break;

    case CBlock::TYPE_ROCK:

        pBlock->m_collisionSize = BLOCK_ROCK_COLLISION_SIZE;
        pBlock->m_move.x = -FLOWING_STAGE;

        // ���������������
        if (pos.y < SCREEN_HEIGHT / 2)
        {
            // ������
            pBlock->m_fRotAngle = D3DX_PI;
        }
        else
        {
            // �����
            pBlock->m_fRotAngle = 0.0f;
        }

        // ��]����Ȃ�
        if (bRotRight == true)
        {
            // ���ړ����Ȃ�
            pBlock->m_move.x = 0.0f;

            // �����_���ɉE��]������]���𓾂�
            nRandNum = rand() % 2 + 1;
            switch (nRandNum)
            {
            case 1:

                pBlock->m_fRotAngle = BLOCK_ROCK_ROT_SPEED;

                break;

            case 2:

                pBlock->m_fRotAngle = -BLOCK_ROCK_ROT_SPEED;

                break;
            }
        }

        break;

    case CBlock::TYPE_METEO:

        pBlock->m_collisionSize = BLOCK_METEO_COLLISION_SIZE;
        pBlock->m_fRotAngle = -BLOCK_METEO_ROT_SPEED;

        // ���@�̈ʒu�ɔ��ł���
        fAngle = pBlock->GetAngleToPlayer(pos);
        if (CGame::GetDispPlayer() == true)
        {
            // ���@������Ȃ�A���@�̂ق���
            pBlock->m_move = D3DXVECTOR3(-sinf(fAngle)*BLOCK_METEO_FALL_SPEED, -cosf(fAngle)*BLOCK_METEO_FALL_SPEED, 0.0f);
        }
        else
        {
            // ���@�����Ȃ��Ȃ�A������
            pBlock->m_move = D3DXVECTOR3(-sinf(D3DX_PI / 4)*BLOCK_METEO_FALL_SPEED, cosf(D3DX_PI / 4)*BLOCK_METEO_FALL_SPEED, 0.0f);
        }

        break;
    }

    return pBlock;
}

//====================================================
// ���ɓ����������̃o�E���h
//====================================================
D3DXVECTOR3 CBlock::Bound(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �ϐ��錾
    D3DXVECTOR3 posBound = pos; // �o�E���h�����ۂ̈ʒu

    // ���̔�����擾
    bool bFloor = false;
    bFloor = CGame::GetFloor();

    // ���Ƃ̓����蔻��
    if (bFloor == true)
    {
        // ���ɓ���������
        if (pos.y + (size.y / 2) > FLOOR_COLLISION)
        {
            switch (m_type)
            {
            case TYPE_APPLE:

                // ���ɂ߂荞�܂Ȃ�
                posBound.y = FLOOR_COLLISION - (size.y / 2);

                // �o�E���h�̕������ꍇ����
                if (m_bRotRight == true)
                {
                    // �E�փo�E���h
                    m_move = BLOCK_APPLE_RIGHT_BOUND;
                }
                else
                {
                    // ���փo�E���h
                    m_move = BLOCK_APPLE_LEFT_BOUND;
                }

                break;

            case TYPE_ROCK:

                // ��]���Ă���Ȃ�
                if (m_bRotRight == true)
                {
                    // ���ɂ߂荞�܂Ȃ�
                    posBound.y = FLOOR_COLLISION - (size.y / 2);

                    if (m_fRotAngle > 0.0f)
                    {
                        // �E�փo�E���h
                        m_move = BLOCK_ROCK_RIGHT_BOUND;
                    }
                    else
                    {
                        // ���փo�E���h
                        m_move = BLOCK_ROCK_LEFT_BOUND;
                    }
                }

                break;
            }     
        }
    }

    return posBound;
}

//====================================================
// 覐΂��猩�����@�ւ̊p�x
//====================================================
float CBlock::GetAngleToPlayer(D3DXVECTOR3 pos)
{
    // �ϐ��錾
    CPlayer *pPlayer = NULL;                   // �v���C���[���擾
    CScene2D *pPlayerScene2D = NULL;           // �v���C���[���V�[��2D�ɃL���X�g
    D3DXVECTOR3 playerPos = DEFAULT_VECTOR;    // �v���C���[�̈ʒu
    float fTargetPosX = 0.0f;                  // �ڕW��X���W
    float fTargetPosY = 0.0f;                  // �ڕW��Y���W
    float fMyPosX = 0.0f;                      // ���g��X���W
    float fMyPosY = 0.0f;                      // ���g��Y���W
    float fAngle = 0.0f;                       // ���߂�p�x

    // �v���C���[�����݂��Ă���Ȃ�
    if (CGame::GetDispPlayer() == true)
    {
        // �v���C���[�̏����擾
        pPlayer = CGame::GetPlayer();
        pPlayerScene2D = (CScene2D*)pPlayer;
        playerPos = pPlayerScene2D->GetPosition();
    }

    // �ڕW�̍��W�Ǝ��g�̍��W
    fTargetPosX = playerPos.x, fTargetPosY = playerPos.y;
    fMyPosX = pos.x, fMyPosY = pos.y;

    // �p�x�����߂�
    fAngle = atan2f((fMyPosX - fTargetPosX), (fMyPosY - fTargetPosY));

    return fAngle;
}

//====================================================
// 覐΂̏Փ�
//====================================================
bool CBlock::MeteoInpact(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �ϐ��錾
    bool bUse = true;   // �g�p�t���O

    // ���̔�����擾
    bool bFloor = false;
    bFloor = CGame::GetFloor();

    // ���Ƃ̓����蔻��
    if (bFloor == true)
    {
        // ���ɓ���������
        if (pos.y + (size.y / 2) > FLOOR_COLLISION)
        {
            // �g�p�t���O��false��
            bUse = false;

            // �������Đ�
            CSound *pSound = CManager::GetSound();
            pSound->Play(CSound::LABEL_SE_EXPLOSION);

            // �G�t�F�N�g�p�̕ϐ��錾
            float fAngle = 0.0f;                // �p�x
            float fRadius = 0.0f;               // ���a
            float fSize = 0.0f;                 // �傫��

            // �����̃p�[�e�B�N������x�ɏo��
            for (int nCnt = 0; nCnt < EFFECT_EXPLOSION_COUNT_LOOP; nCnt++)
            {
                // �����_���Ȋp�x�Ɣ��a���擾
                fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
                fRadius = float(rand() % 20000) / 100.0f;
                fSize = float(rand() % EFFECT_EXPLOSION_MAX_SIZE + EFFECT_EXPLOSION_MIN_SIZE) / 100.0f;

                // �����G�t�F�N�g
                CEffect::Create(D3DXVECTOR3(pos.x - sinf(fAngle)*fRadius, pos.y - cosf(fAngle)*fRadius, 0.0f),
                    D3DXVECTOR3(fSize, fSize, 0.0f), EFFECT_EXPLOSION_FIRST_COLOR, CEffect::TYPE_PART_EXPLOSION);
            }
        }
    }

    return bUse;
}
