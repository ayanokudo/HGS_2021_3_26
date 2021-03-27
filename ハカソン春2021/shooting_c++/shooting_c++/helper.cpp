//===============================================
//
// �w���p�[���� (helper.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "helper.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "renderer.h"
#include "library.h"
#include "sound.h"
#include "effect.h"
#include "item.h"
#include "game.h"
#include "enemy.h"
#include "block.h"
#include "afterimage.h"
#include "bg.h"

//=======================================
// �ÓI�����o�ϐ��錾
//=======================================
LPDIRECT3DTEXTURE9 CHelper::m_pTexture = NULL;

//========================================
// �w���p�[�̃R���X�g���N�^
//========================================
CHelper::CHelper() :CScene2D(OBJTYPE::OBJTYPE_HELPER)
{
    m_nAttackCoolTime = 0;
    m_fHelperAngle = 0.0f;
    m_move = DEFAULT_VECTOR;
    m_nCntInvincibleFrame = 0;
    m_fSpeed = HELPER_SPEED;
}

//========================================
// �w���p�[�̃f�X�g���N�^
//========================================
CHelper::~CHelper()
{

}

//========================================
// �w���p�[�̏���������
//========================================
HRESULT CHelper::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ������
    CScene2D::Init(pos, size);

    // �e�N�X�`�������蓖��
    BindTexture(m_pTexture);

    return S_OK;
}

//========================================
// �w���p�[�̏I������
//========================================
void CHelper::Uninit(void)
{
    // �I������
    CScene2D::Uninit();
}

//========================================
// �w���p�[�̍X�V����
//========================================
void CHelper::Update(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos;            // �ʒu
    D3DXVECTOR3 size;           // �T�C�Y
    float fHelperAngle = 0.0f;  // �w���p�[�̊p�x

    // �ʒu���擾
    pos = GetPosition();

    // �T�C�Y���擾
    size = GetSize();

    // ��̒��Ȃ�A�w���p�[�̊p�x�𒲐�
    if (CBg::GetInTheSky() == true)
    {
        // ���񂾂�X����
        m_fHelperAngle += HELPER_TILT_RATE;

        // 45�x�܂�
        if (m_fHelperAngle > (D3DX_PI / 4))
        {
            m_fHelperAngle = D3DX_PI / 4;
        }
    }
    else
    {
        // ���񂾂�X����
        m_fHelperAngle -= HELPER_TILT_RATE;

        // 0�x�܂�
        if (m_fHelperAngle < 0)
        {
            m_fHelperAngle = 0;
        }
    }

    //�m�b�N�o�b�N�𐧌�
    if (m_move.x != 0.0f || m_move.y != 0.0f)
    {
        m_move.x *= HELPER_KNOCKBACK_CONTROL;
        m_move.y *= HELPER_KNOCKBACK_CONTROL;
    }

    //�ړ��ʂƈʒu��R�Â�
    pos += m_move;

    // �w���p�[�̈ړ�����
    pos = ControlHelper(pos);

    // �e��������
    ShotBullet(pos, size);

    // �U���̃N�[���^�C��
    if (m_nAttackCoolTime > 0)
    {
        m_nAttackCoolTime--;
    }

    // ���G���Ԃ̃J�E���^
    if (m_nCntInvincibleFrame > 0)
    {
        // ���G���Ԃ𐔂���
        m_nCntInvincibleFrame--;

        // �J�E���^�[��i�߂āA�p�^�[����؂�ւ���
        int nPatternAnim = CountAnimation(2, 2);

        // �_��
        if (nPatternAnim == 1)
        {
            // �ʏ�
            CScene2D::SetColor(DEFAULT_COLOR);
        }
        else
        {
            // ����
            CScene2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
        }

        // �K�����̐F�ɖ߂�悤�ɂ���
        if (m_nCntInvincibleFrame == 0)
        {
            // �ʏ�
            CScene2D::SetColor(DEFAULT_COLOR);
        }
    }

    // UI�Ƃ̓����蔻��
    if (pos.y <= HELPER_MOVE_LIMITED_BY_UI)
    {
        pos.y = HELPER_MOVE_LIMITED_BY_UI;
    }

    // ���Ƃ̓����蔻��
    pos = HitFloor(pos, size);

    // ��ʊO�ɏo�Ȃ��悤�ɂ���
    SteyInScreen2D(&pos, &size);

    // �ʒu�𔽉f
    SetPosition(pos);

    // ���_���W��ύX
    fHelperAngle = m_fHelperAngle * (-1);   // -1�������邱�ƂŁA�p�x�����Z����قǍ��ɉ��悤��
    SetRotVertex(fHelperAngle);

    // �����蔻��
    for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
    {
        // �V�[�����擾
        CScene *pScene = GetScene(nCntScene);

        // ���g������Ȃ�
        if (pScene != NULL)
        {
            // �^�C�v���擾
            OBJTYPE objType = pScene->GetObjType();

            // �G�l�~�[�Ȃ�A
            if (objType == CScene::OBJTYPE_ENEMY)
            {
                // �w���p�[�̓����蔻������
                D3DXVECTOR3 helperCollisionSize = HELPER_COLLISION_SIZE;

                // �ʒu�ƏՓ˃T�C�Y�𓾂邽�߁A�G�l�~�[�ɃL���X�g
                CEnemy *pEnemy = (CEnemy*)pScene;

                // �����蔻��̐�����
                for (int nCntCollision = 0; nCntCollision < pEnemy->GetCntCollision(); nCntCollision++)
                {
                    D3DXVECTOR3 posCollision = pEnemy->GetPosition() + pEnemy->GetCollision(nCntCollision).posToShift;
                    D3DXVECTOR3 sizeCollision = pEnemy->GetCollision(nCntCollision).size;
                    D3DXVECTOR3 posOld = pEnemy->GetPosOld();

                    // �����蔻����v�Z
                    if (RectangleCollision2D(&pos, &posCollision,
                        &helperCollisionSize, &sizeCollision) == true)
                    {
                        // ������������
                        Hit(posOld);

                        // for�𔲂���
                        break;
                    }
                }
            }
            // �u���b�N�Ȃ�A
            else if (objType == CScene::OBJTYPE_BLOCK)
            {
                // �w���p�[�̓����蔻������
                D3DXVECTOR3 helperCollisionSize = HELPER_COLLISION_SIZE;

                // �ʒu�ƏՓ˃T�C�Y�𓾂邽�߁A�u���b�N�ɃL���X�g
                CBlock *pBlock = (CBlock*)pScene;

                // �����蔻����v�Z
                if (RectangleCollision2D(&pos, &pBlock->GetPosition(),
                    &helperCollisionSize, &pBlock->GetCollisionSize()) == true)
                {
                    // ������������
                    Hit(pBlock->GetPosOld());

                    // for�𔲂���
                    break;
                }
            }
        }
    }
}

//========================================
// �w���p�[�̕`�揈��
//========================================
void CHelper::Draw(void)
{
    // �`�揈��
    CScene2D::Draw();
}

//========================================
// �w���p�[�̈ړ�����ׂ̍��Ȋ֐�
//========================================
D3DXVECTOR3 CHelper::ControlHelper(D3DXVECTOR3 pos)
{
    // �ϐ��錾
    D3DXVECTOR3 movePos = pos;      // �ړ��̈ʒu

    // �R���g���[�����擾
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();
    DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_2);

    // ������Ȃ�
    if (CGame::GetMovePlayer() == true)
    {
        // �C��X�e�[�W�͏��X�ɉ�����
        if (CGame::GetStage() == CManager::STAGE_B)
        {
            movePos.y += HELPER_POS_Y_DOWN_IN_WATAR;
        }

        // �X�e�B�b�N���|��Ă���Ȃ�ړ�
        if (Controller.lY != 0 || Controller.lX != 0)
        {

            // �X�e�B�b�N�̊p�x�����߂�
            float fAngle = atan2(Controller.lX, Controller.lY * (-1));

            movePos.x += sinf(fAngle)* m_fSpeed;
            movePos.y += -cosf(fAngle)* m_fSpeed;
        }
    }

    return movePos;
}

//========================================
// �w���p�[�̒e��������
//========================================
void CHelper::ShotBullet(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �R���g���[�����擾
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();
    DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_2);

    // �T�E���h���擾
    CSound *pSound = CManager::GetSound();

    // �v���C���[�̃X�g�b�N��0�ȏ�Ȃ�
    if (CGame::GetStock() >= 0)
    {
        // ������Ȃ�
        if (CGame::GetMovePlayer() == true)
        {
            // ���G���Ԃ��l��
            if (m_nCntInvincibleFrame <= HELPER_ENABLE_SHOT_FRAME)
            {
                // B�������ꂽ(��)
                if (pInputJoypad->GetJoypadPress(PLAYER_2, CInputJoypad::BUTTON_B))
                {
                    // �N�[���^�C����0�Ȃ�A
                    if (m_nAttackCoolTime == 0)
                    {
                        // �V���b�g��
                        pSound->Play(CSound::LABEL_SE_SHOT_FIRE);

                        // �e�̐���
                        CBullet::Create(pos, HELPER_BULLET_SIZE, 
                            D3DXVECTOR3(cosf(m_fHelperAngle) * HELPER_BULLET_SPEED, sinf(m_fHelperAngle) * (-HELPER_BULLET_SPEED), 0.0f),
                            CBullet::TYPE_FIRE, TRIBE_PLAYER);

                        // ���̒e�̃N�[���^�C��
                        m_nAttackCoolTime = HELPER_BULLET_FIRE_COOL_TIME;
                    }
                }

                // X�������ꂽ(��)
                if (pInputJoypad->GetJoypadPress(PLAYER_2, CInputJoypad::BUTTON_X))
                {
                    // �N�[���^�C����0�Ȃ�A
                    if (m_nAttackCoolTime == 0)
                    {
                        // �V���b�g��
                        pSound->Play(CSound::LABEL_SE_SHOT_FIRE);

                        // �e�̐���
                        CBullet::Create(pos, HELPER_BULLET_SIZE, 
                            D3DXVECTOR3(cosf(m_fHelperAngle) * HELPER_BULLET_SPEED, sinf(m_fHelperAngle) * (-HELPER_BULLET_SPEED), 0.0f),
                            CBullet::TYPE_HELPER_WATER, TRIBE_PLAYER);

                        // ���̒e�̃N�[���^�C��
                        m_nAttackCoolTime = HELPER_BULLET_WATER_COOL_TIME;
                    }
                }

                // Y�������ꂽ(��)
                if (pInputJoypad->GetJoypadPress(PLAYER_2, CInputJoypad::BUTTON_Y))
                {
                    // �N�[���^�C����0�Ȃ�A
                    if (m_nAttackCoolTime == 0)
                    {
                        // �V���b�g��
                        pSound->Play(CSound::LABEL_SE_SHOT_FIRE);

                        // �e�̐���
                        CBullet::Create(pos, HELPER_BULLET_SIZE,
                            D3DXVECTOR3(cosf(m_fHelperAngle) * HELPER_BULLET_SPEED, sinf(m_fHelperAngle) * (-HELPER_BULLET_SPEED), 0.0f),
                            CBullet::TYPE_LIGHT, TRIBE_PLAYER);

                        // ���̒e�̃N�[���^�C��
                        m_nAttackCoolTime = HELPER_BULLET_LIGHT_COOL_TIME;
                    }
                }
            }
        }
        else
        {// �����Ȃ��Ƃ�

         // �N�[���^�C�����Z�b�g
            m_nAttackCoolTime = 0;
        }
    }
}

//========================================
// �w���p�[�̉摜���[�h����
//========================================
HRESULT CHelper::Load(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // �e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/helper000.png", &m_pTexture);

    return S_OK;
}

//========================================
// �w���p�[�̉摜�j������
//========================================
void CHelper::Unload(void)
{
    // �e�N�X�`���̔j��
    if (m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}

//================================
// �w���p�[�̍쐬
//================================
CHelper *CHelper::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fAngle, int nCntInvincibleFrame)
{
    CHelper *pHelper = NULL;

    // ���������m��
    // �R���X�g���N�^�Ŋe����R�Â�
    pHelper = new CHelper;

    // ������
    pHelper->Init(pos, size);

    // �����ƃ����o�ϐ������т���
    pHelper->m_nCntInvincibleFrame = nCntInvincibleFrame;
    pHelper->m_fHelperAngle = fAngle;

    return pHelper;
}

//====================================================
// �w���p�[�ɓG�̒e��G��u���b�N�����������Ƃ��̏���
//====================================================
void CHelper::Hit(D3DXVECTOR3 posOld)
{
    // �ϐ��錾
    D3DXVECTOR3 pos;    // �ʒu

    // �ʒu���擾
    pos = GetPosition();

    // ���G�łȂ��Ȃ�
    if (CGame::GetInvinciblePlayer() == false && m_nCntInvincibleFrame <= 0)
    {
        // �m�b�N�o�b�N
        float fKnockback = HELPER_KNOCKBACK_VALUE;
        m_move.x = pos.x - posOld.x;
        m_move.y = pos.y - posOld.y;
        D3DXVec3Normalize(&m_move, &m_move);  //�x�N�g���𐳋K��
        m_move.x = m_move.x*fKnockback;
        m_move.y = m_move.y*fKnockback;

        // ���G���Ԃ𓾂�
        m_nCntInvincibleFrame = HELPER_INVINCIBLE_FRAME;
    }
}

//====================================================
// ���ɓ����������̏���
//====================================================
D3DXVECTOR3 CHelper::HitFloor(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �ϐ��錾
    D3DXVECTOR3 posLimited = pos;   // ���ɓ����������̈ړ������̈ʒu

    // ���̔�����擾
    bool bFloor = false;
    bFloor = CGame::GetFloor();

    // ���Ƃ̓����蔻��
    if (bFloor == true)
    {
        if (pos.y + (size.y / 2) >= FLOOR_COLLISION)
        {
            // ���ɂ߂荞�܂Ȃ�
            posLimited.y = FLOOR_COLLISION - (size.y / 2);

            // �X�X�e�[�W�ȊO�͏��ɓ����蔻�肠��
            if (CGame::GetStage() != CManager::STAGE_A)
            {
                // ���G�łȂ��Ȃ�
                if (CGame::GetInvinciblePlayer() == false && m_nCntInvincibleFrame <= 0)
                {
                    // �m�b�N�o�b�N
                    m_move.y = -HELPER_KNOCKBACK_VALUE;

                    // ���G���Ԃ𓾂�
                    m_nCntInvincibleFrame = HELPER_INVINCIBLE_FRAME;
                }
            }
        }
    }

    return posLimited;
}

//====================================================
// �w���p�[���ŏ��̈ʒu�ɂ���
//====================================================
void CHelper::SetStartPos(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos;    // �ʒu

    // �ʒu���擾
    pos = GetPosition();

    // �ʒu�������ʒu�ɕύX
    pos = HELPER_POS;

    // �ړ��ʂ����Z�b�g
    m_move = DEFAULT_VECTOR;

    // �ʒu�𔽉f
    SetPosition(pos);

    // ���_���W��ύX
    SetVertex();
}
