//===============================================
//
// �v���C���[���� (player.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "player.h"
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
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//========================================
// �v���C���[�̃R���X�g���N�^
//========================================
CPlayer::CPlayer() :CScene2D(OBJTYPE::OBJTYPE_PLAYER)
{
    m_nAttackCoolTime = 0;
    m_fShotAngle = D3DX_PI / 4; // �ŏ��͉E�΂ߏ�̊p�x
    m_fPlayerAngle = 0.0f;      // �ŏ��̎��@�̊p�x��0.0f
    m_nChargeTime = 0;
    m_nBarrier = 0;             // �J�n���̃o���A��0��
    m_nCntInvincibleFrame = 0;
    m_fSpeed = 0.0f;
    m_bUse = true;
    m_nSpeedRank = PLAYER_FIRST_SPEED_RANK;
}

//========================================
// �v���C���[�̃f�X�g���N�^
//========================================
CPlayer::~CPlayer()
{

}

//========================================
// �v���C���[�̏���������
//========================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ������
    CScene2D::Init(pos, size);

    // �e�N�X�`�������蓖��
    BindTexture(m_pTexture);

    return S_OK;
}

//========================================
// �v���C���[�̏I������
//========================================
void CPlayer::Uninit(void)
{
    // �I������
    CScene2D::Uninit();
}

//========================================
// �v���C���[�̍X�V����
//========================================
void CPlayer::Update(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos;            // �ʒu
    D3DXVECTOR3 size;           // �T�C�Y
    float fPlayerAngle = 0.0f;  // �v���C���[�̊p�x

    // �ʒu���擾
    pos = GetPosition();

    // �T�C�Y���擾
    size = GetSize();

    // ��̒��Ȃ�A�v���C���[�̊p�x�𒲐�
    if (CBg::GetInTheSky() == true)
    {
        // ���񂾂�X����
        m_fPlayerAngle += PLAYER_TILT_RATE;

        // 45�x�܂�
        if (m_fPlayerAngle > (D3DX_PI / 4))
        {
            m_fPlayerAngle = D3DX_PI / 4;
        }
    }
    else
    {
        // ���񂾂�X����
        m_fPlayerAngle -= PLAYER_TILT_RATE;

        // 0�x�܂�
        if (m_fPlayerAngle < 0)
        {
            m_fPlayerAngle = 0;
        }
    }

    // �X�s�[�h�����N��ς���
    ChangeSpeed();

    // �v���C���[�̈ړ�����
    pos = ControlPlayer(pos);

    // ���̔��ˊp�x����
    ChangeShotAngle();

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
    if (pos.y <= PLAYER_MOVE_LIMITED_BY_UI)
    {
        pos.y = PLAYER_MOVE_LIMITED_BY_UI;
    }

    // ���Ƃ̓����蔻��
    pos = HitFloor(pos, size);

    // ��ʊO�ɏo�Ȃ��悤�ɂ���
    SteyInScreen2D(&pos, &size);

    // �ʒu�𔽉f
    SetPosition(pos);

    // ���_���W��ύX
    fPlayerAngle = m_fPlayerAngle * (-1);   // -1�������邱�ƂŁA�p�x�����Z����قǍ��ɉ��悤��
    SetRotVertex(fPlayerAngle);

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
                // �v���C���[�̓����蔻������
                D3DXVECTOR3 playerCollisionSize = PLAYER_COLLISION_SIZE;

                // �ʒu�ƏՓ˃T�C�Y�𓾂邽�߁A�G�l�~�[�ɃL���X�g
                CEnemy *pEnemy = (CEnemy*)pScene;

                // �����蔻��̐�����
                for (int nCntCollision = 0; nCntCollision < pEnemy->GetCntCollision(); nCntCollision++)
                {
                    D3DXVECTOR3 posCollision = pEnemy->GetPosition() + pEnemy->GetCollision(nCntCollision).posToShift;
                    D3DXVECTOR3 sizeCollision = pEnemy->GetCollision(nCntCollision).size;

                    // �����蔻����v�Z
                    if (RectangleCollision2D(&pos, &posCollision,
                        &playerCollisionSize, &sizeCollision) == true)
                    {
                        // ������������
                        Hit();

                        // for�𔲂���
                        break;
                    }
                }
            }
            // �A�C�e���Ȃ�A
            else if (objType == CScene::OBJTYPE_ITEM)
            {
                // �V�[��2D�ɃL���X�g
                CScene2D *pScene2D = (CScene2D*)pScene;

                // �v���C���[�̓����蔻������(�A�C�e���p)
                D3DXVECTOR3 playerCollisionSize = PLAYER_COLLISION_ITEM_SIZE;

                // �����蔻����v�Z
                if (RectangleCollision2D(&pos, &pScene2D->GetPosition(),
                    &playerCollisionSize, &pScene2D->GetSize()) == true)
                {
                    // �T�E���h���擾
                    CSound *pSound = CManager::GetSound();

                    // �A�C�e����
                    pSound->Play(CSound::LABEL_SE_ITEM);

                    // �A�C�e���ɃL���X�g
                    CItem *pItem = (CItem*)pScene;

                    // �A�C�e���̃^�C�v���Ƃɏ�����ς���
                    switch (pItem->GetType())
                    {
                    case CItem::TYPE_BARRIER:

                        // �o���A�����Z
                        m_nBarrier++;

                        // �ő吔�𒴂�����A�ő吔�ɂ���
                        if (m_nBarrier > PLAYER_MAX_BARRIER)
                        {
                            m_nBarrier = PLAYER_MAX_BARRIER;
                        }

                        // �Ռ��g
                        CEffect::Create(pos, EFFECT_DOUBLE_WAVE_ITEM_SIZE,
                            EFFECT_DOUBLE_WAVE_ITEM_BARRIER_COLOR, CEffect::TYPE_DOUBLE_WAVE);

                        break;

                    case CItem::TYPE_STOCK:

                        // �X�g�b�N�����Z
                        CGame::AddStock();

                        // �Ռ��g
                        CEffect::Create(pos, EFFECT_DOUBLE_WAVE_ITEM_SIZE,
                            EFFECT_DOUBLE_WAVE_ITEM_STOCK_COLOR, CEffect::TYPE_DOUBLE_WAVE);

                        break;
                    }

                    // �A�C�e��������
                    pItem->Uninit();

                    // for�𔲂���
                    break;
                }
            }
            // �u���b�N�Ȃ�A
            else if (objType == CScene::OBJTYPE_BLOCK)
            {
                // �v���C���[�̓����蔻������
                D3DXVECTOR3 playerCollisionSize = PLAYER_COLLISION_SIZE;

                // �ʒu�ƏՓ˃T�C�Y�𓾂邽�߁A�u���b�N�ɃL���X�g
                CBlock *pBlock = (CBlock*)pScene;

                // �����蔻����v�Z
                if (RectangleCollision2D(&pos, &pBlock->GetPosition(),
                    &playerCollisionSize, &pBlock->GetCollisionSize()) == true)
                {
                    // ������������
                    Hit();

                    // for�𔲂���
                    break;
                }
            }
        }
    }

    // �g�p�t���O��false�Ȃ�
    if (m_bUse == false)
    {
        // �v���C���[�����ꂽ��X�g�b�N�����炷
        CGame::DefeatPlayer();

        // �I������
        Uninit();
    }
}

//========================================
// �v���C���[�̕`�揈��
//========================================
void CPlayer::Draw(void)
{
    // �`�揈��
    CScene2D::Draw();
}

//========================================
// �v���C���[�̐��e�̔��ˊp�x����
//========================================
void CPlayer::ChangeShotAngle(void)
{
    // �R���g���[�����擾
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();
    DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_1);

    // ���̔��ˊp�x��ς���
    if (Controller.lZ != 0 || Controller.lRz != 0)
    {
        // ���ɓ|������������
        if (Controller.lRz > 0)
        {
            // �E�ŌŒ�
            Controller.lZ = 3000;
            Controller.lRz = 0;
        }

        // �X�e�B�b�N�̊p�x�����߂�
        m_fShotAngle = atan2(Controller.lZ, Controller.lRz * (-1));
    }

    // ���X�e�B�b�N�������݂ŁA���ˊp�x��w�ʂɃ��Z�b�g
    if (pInputJoypad->GetJoypadPress(PLAYER_1, CInputJoypad::BUTTON_L3))
    {
        m_fShotAngle = -D3DX_PI / 4;
    }

    // �E�X�e�B�b�N�������݂ŁA���ˊp�x�𐳖ʂɃ��Z�b�g
    if (pInputJoypad->GetJoypadPress(PLAYER_1, CInputJoypad::BUTTON_R3))
    {
        m_fShotAngle = D3DX_PI / 4;
    }
}

//========================================
// �v���C���[�̈ړ����x��ς���
//========================================
void CPlayer::ChangeSpeed(void)
{
    // �L�[�{�[�h���擾
    CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

    // �R���g���[�����擾
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();
    DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_1);

    // �V���b�N��ԂłȂ��Ȃ�
    if (CGame::GetShockPlayer() == false)
    {
        // L�������ꂽ(����)
        if (pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_L1) ||
            pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_L2) ||
            pInputKeyboard->GetKeyboardTrigger(DIK_U))
        {
            m_nSpeedRank--;
        }

        // R�������ꂽ(����)
        if (pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_R1) ||
            pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_R2) ||
            pInputKeyboard->GetKeyboardTrigger(DIK_I))
        {
            m_nSpeedRank++;
        }
    }
    // �V���b�N��ԂȂ�
    else
    {
        // �X�s�[�h�����N�����1
        m_nSpeedRank = 1;
    }

    // �X�s�[�h�����N��1�������Ȃ����ő������Ȃ�
    if (m_nSpeedRank < 1)
    {
        m_nSpeedRank = 1;
    }
    else if (m_nSpeedRank > PLAYER_MAX_SPEED_RANK)
    {
        m_nSpeedRank = PLAYER_MAX_SPEED_RANK;
    }

    // �X�s�[�h�����N�ɂ���āA�����𓾂�
    switch (m_nSpeedRank)
    {
    case 1:
        m_fSpeed = PLAYER_SPEED_1;
        break;

    case 2:
        m_fSpeed = PLAYER_SPEED_2;
        break;

    case 3:
        m_fSpeed = PLAYER_SPEED_3;
        break;

    case 4:
        m_fSpeed = PLAYER_SPEED_4;
        break;
    }
}

//========================================
// �v���C���[�̈ړ�����ׂ̍��Ȋ֐�
//========================================
D3DXVECTOR3 CPlayer::ControlPlayer(D3DXVECTOR3 pos)
{
    // �ϐ��錾
    D3DXVECTOR3 movePos = pos;      // �ړ��̈ʒu

    // �L�[�{�[�h���擾
    CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

    // �R���g���[�����擾
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();
    DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_1);

    // ������Ȃ�
    if (CGame::GetMovePlayer() == true)
    {
        // �C��X�e�[�W�͏��X�ɉ�����
        if (CGame::GetStage() == CManager::STAGE_��)
        {
            movePos.y += PLAYER_POS_Y_DOWN_IN_WATAR;
        }

        if (Controller.lY != 0 || Controller.lX != 0)
        {// �X�e�B�b�N���|��Ă���Ȃ�ړ�

         // �X�e�B�b�N�̊p�x�����߂�
            float fAngle = atan2(Controller.lX, Controller.lY * (-1));

            movePos.x += sinf(fAngle)* m_fSpeed;
            movePos.y += -cosf(fAngle)* m_fSpeed;

            // �ō����x�Ȃ�
            if (m_nSpeedRank == PLAYER_MAX_SPEED_RANK)
            {
                // �c�����c��
                CAfterimage::Create(pos, PLAYER_SIZE, m_fPlayerAngle, AFTERIMAGE_PLAYER_COLOR,CAfterimage::TYPE_PLAYER);
            }
        }
        else
        {// �L�[�{�[�h����

         // A�L�[�������ꂽ(���ړ�)
            if (pInputKeyboard->GetKeyboardPress(DIK_A))
            {
                if (pInputKeyboard->GetKeyboardPress(DIK_W))// A��W�������ɉ����ꂽ
                {
                    movePos.x -= sinf(D3DX_PI / 4) * m_fSpeed;
                    movePos.y -= cosf(D3DX_PI / 4) * m_fSpeed;
                }
                else if (pInputKeyboard->GetKeyboardPress(DIK_S))// A��S�������ɉ����ꂽ
                {
                    movePos.x -= sinf(D3DX_PI / 4) * m_fSpeed;
                    movePos.y += cosf(D3DX_PI / 4) * m_fSpeed;
                }
                else				// ������������
                {
                    movePos.x -= m_fSpeed;
                }

                // �ō����x�Ȃ�
                if (m_nSpeedRank == PLAYER_MAX_SPEED_RANK)
                {
                    // �c�����c��
                    CAfterimage::Create(pos, PLAYER_SIZE, m_fPlayerAngle, AFTERIMAGE_PLAYER_COLOR, CAfterimage::TYPE_PLAYER);
                }
            }

            // D�L�[�������ꂽ(�E�ړ�)
            else if (pInputKeyboard->GetKeyboardPress(DIK_D))
            {
                if (pInputKeyboard->GetKeyboardPress(DIK_W))// D��W�������ɉ����ꂽ
                {
                    movePos.x += sinf(D3DX_PI / 4) * m_fSpeed;
                    movePos.y -= cosf(D3DX_PI / 4) * m_fSpeed;
                }
                else if (pInputKeyboard->GetKeyboardPress(DIK_S))// D��S�������ɉ����ꂽ
                {
                    movePos.x += sinf(D3DX_PI / 4) * m_fSpeed;
                    movePos.y += cosf(D3DX_PI / 4) * m_fSpeed;
                }
                else				// �E����������
                {
                    movePos.x += m_fSpeed;
                }

                // �ō����x�Ȃ�
                if (m_nSpeedRank == PLAYER_MAX_SPEED_RANK)
                {
                    // �c�����c��
                    CAfterimage::Create(pos, PLAYER_SIZE, m_fPlayerAngle, AFTERIMAGE_PLAYER_COLOR, CAfterimage::TYPE_PLAYER);
                }
            }

            // W�L�[�������ꂽ(��ړ�)
            else if (pInputKeyboard->GetKeyboardPress(DIK_W))
            {
                movePos.y -= m_fSpeed;

                // �ō����x�Ȃ�
                if (m_nSpeedRank == PLAYER_MAX_SPEED_RANK)
                {
                    // �c�����c��
                    CAfterimage::Create(pos, PLAYER_SIZE, m_fPlayerAngle, AFTERIMAGE_PLAYER_COLOR, CAfterimage::TYPE_PLAYER);
                }
            }

            // S�L�[�������ꂽ(���ړ�)
            else if (pInputKeyboard->GetKeyboardPress(DIK_S))
            {
                movePos.y += m_fSpeed;

                // �ō����x�Ȃ�
                if (m_nSpeedRank == PLAYER_MAX_SPEED_RANK)
                {
                    // �c�����c��
                    CAfterimage::Create(pos, PLAYER_SIZE, m_fPlayerAngle, AFTERIMAGE_PLAYER_COLOR, CAfterimage::TYPE_PLAYER);
                }
            }
        }
    }

    return movePos;
}

//========================================
// �v���C���[�̒e��������
//========================================
void CPlayer::ShotBullet(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �L�[�{�[�h���擾
    CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

    // �R���g���[�����擾
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();
    DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_1);

    // �T�E���h���擾
    CSound *pSound = CManager::GetSound();

    // ������Ȃ�
    if (CGame::GetMovePlayer() == true)
    {
        // Y�������ꂽ(��)
        if (pInputKeyboard->GetKeyboardPress(DIK_B) || pInputJoypad->GetJoypadPress(PLAYER_1, CInputJoypad::BUTTON_Y))
        {
            // �N�[���^�C����0�Ȃ�A
            if (m_nAttackCoolTime == 0)
            {
                // ���̍U���������Ȃ����߂̒l
                m_nAttackCoolTime++;

                // �`���[�W����
                m_nChargeTime++;
            }
        }

        // �ő�`���[�W�𒴂�����A���̒l�ŌŒ�
        if (m_nChargeTime > MAX_CHARGE_TIME)
        {
            m_nChargeTime = MAX_CHARGE_TIME;
        }

        // ���U���̃`���[�W����
        if (m_nChargeTime > 0)
        {
            // �G�t�F�N�g��ݒ�
            if (m_nChargeTime == 1)
            {
                // �`���[�W�G�t�F�N�g
                CEffect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                    CHARGE_COLOR, CEffect::TYPE_CHARGE);

                // ���̒e(�G�t�F�N�g)
                CEffect::Create(D3DXVECTOR3(pos.x + size.x, pos.y, 0.0f), D3DXVECTOR3(BULLET_LIGHT_MIN_SIZE, BULLET_LIGHT_MIN_SIZE,
                    0.0f), DEFAULT_COLOR, CEffect::TYPE_LIGHT_BULLET);
            }

            // �ő�܂ł́A�p�[�e�B�N�������@�ɋz��
            if (m_nChargeTime < MAX_CHARGE_TIME)
            {
                //0�`3.14���o��*(0 or 1)*-1�Ő��������߂�
                float fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
                float fRadius = float(rand() % 20000 + 0) / 100.0f;
                D3DXVECTOR3 particlePos = D3DXVECTOR3(pos.x - sinf(fAngle)*fRadius, pos.y - cosf(fAngle)*fRadius, 0.0f);

                // �`���[�W�̃p�[�e�B�N��
                CEffect::Create(particlePos, D3DXVECTOR3(CHARGE_PART_SIZE, CHARGE_PART_SIZE,
                    0.0f), BULLET_LIGHT_COLOR, CEffect::TYPE_CHARGE_PART);
            }

            // �������甭��(�|�[�Y�{�^���ł�����)
            if (pInputKeyboard->GetKeyboardRelease(DIK_B) || pInputJoypad->GetJoypadRelease(PLAYER_1, CInputJoypad::BUTTON_Y)
                || pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START))
            {
                // �ő�`���[�W���ǂ����ŁA�V���b�g���𕪂���
                if (m_nChargeTime == MAX_CHARGE_TIME)
                {
                    // �V���b�g��
                    pSound->Play(CSound::LABEL_SE_SHOT_LIGHT2);

                    // �Ռ��g
                    CEffect::Create(pos, EFFECT_DOUBLE_WAVE_SHOT_SIZE, 
                        EFFECT_DOUBLE_WAVE_SHOT_COLOR, CEffect::TYPE_DOUBLE_WAVE);
                    // �Ռ��g
                    CEffect::Create(pos, EFFECT_DOUBLE_WAVE_SHOT_SIZE,
                        D3DXCOLOR(0.0f,1.0f,0.0f,0.6f), CEffect::TYPE_DOUBLE_WAVE);
                }
                else
                {
                    // �V���b�g��
                    pSound->Play(CSound::LABEL_SE_SHOT_LIGHT1);
                }

                // �`���[�W�^�C�������Z�b�g
                m_nChargeTime = 0;

                // ���̒e�̃N�[���^�C��
                m_nAttackCoolTime = BULLET_LIGHT_COOL_TIME;
            }
        }

        // ���Ɛ��̒e�́A���G���Ԃ��l��
        if (m_nCntInvincibleFrame <= PLAYER_ENABLE_SHOT_FRAME)
        {
            // B�������ꂽ(��)
            if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) || pInputJoypad->GetJoypadPress(PLAYER_1, CInputJoypad::BUTTON_B))
            {
                // �N�[���^�C����0�Ȃ�A
                if (m_nAttackCoolTime == 0)
                {
                    // �V���b�g��
                    pSound->Play(CSound::LABEL_SE_SHOT_FIRE);

                    // �e�̐���
                    CBullet::Create(pos, BULLET_FIRE_SIZE, 
                        D3DXVECTOR3(cosf(m_fPlayerAngle) * BULLET_FIRE_SPEED, sinf(m_fPlayerAngle) * (-BULLET_FIRE_SPEED), 0.0f),
                        CBullet::TYPE_FIRE, TRIBE_PLAYER);

                    // ���̒e�̃N�[���^�C��
                    m_nAttackCoolTime = BULLET_FIRE_COOL_TIME;

                    // �O�̂��߁A���̃`���[�W���Ȃ���
                    m_nChargeTime = 0;
                }
            }

            // X�������ꂽ(��)
            if (pInputKeyboard->GetKeyboardPress(DIK_N) || pInputJoypad->GetJoypadPress(PLAYER_1, CInputJoypad::BUTTON_X))
            {
                // �N�[���^�C����0�Ȃ�A
                if (m_nAttackCoolTime == 0)
                {
                    // �V���b�g��
                    pSound->Play(CSound::LABEL_SE_SHOT_WATER);

                    // �e�̐���
                    CBullet::Create(D3DXVECTOR3(pos.x, pos.y + PLAYER_ADD_WATAR_POS, pos.z), BULLET_WATER_SIZE,
                        D3DXVECTOR3(sinf(m_fShotAngle) * BULLET_WATER_SPEED, cosf(m_fShotAngle) * (-BULLET_WATER_SPEED), 0.0f),
                        CBullet::TYPE_WATER, TRIBE_PLAYER);

                    // ���̒e�̃N�[���^�C��
                    m_nAttackCoolTime = BULLET_WATER_COOL_TIME;

                    // �O�̂��߁A���̃`���[�W���Ȃ���
                    m_nChargeTime = 0;
                }
            }
        }
    }
    else
    {// �����Ȃ��Ƃ�

        // �`���[�W�^�C�������Z�b�g
        m_nChargeTime = 0;

        // �N�[���^�C�����Z�b�g
        m_nAttackCoolTime = 0;
    }
}

//========================================
// �v���C���[�̉摜���[�h����
//========================================
HRESULT CPlayer::Load(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // �e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player000.png", &m_pTexture);

    return S_OK;
}

//========================================
// �v���C���[�̉摜�j������
//========================================
void CPlayer::Unload(void)
{
    // �e�N�X�`���̔j��
    if (m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}

//================================
// �v���C���[�̍쐬
//================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fAngle, int nCntInvincibleFrame)
{
    CPlayer *pPlayer = NULL;

    // ���������m��
    // �R���X�g���N�^�Ŋe����R�Â�
    pPlayer = new CPlayer;

    // ������
    pPlayer->Init(pos, size);

    // �����ƃ����o�ϐ������т���
    pPlayer->m_nCntInvincibleFrame = nCntInvincibleFrame;
    pPlayer->m_fPlayerAngle = fAngle;

    return pPlayer;
}

//====================================================
// �v���C���[�ɓG�̒e��G�����������Ƃ��̏���
//====================================================
void CPlayer::Hit(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos;    // �ʒu
    D3DXVECTOR3 size;   // �T�C�Y

    // �ʒu���擾
    pos = GetPosition();

    // �T�C�Y���擾
    size = GetSize();

    // ���G�łȂ��Ȃ�
    if (CGame::GetInvinciblePlayer() == false && m_nCntInvincibleFrame <= 0)
    {
        // �o���A�̗L���ŏꍇ����
        if (m_nBarrier > 0)
        {// �o���A�L��

            // �o���A��1������
            m_nBarrier--;

            // ���G���Ԃ𓾂�
            m_nCntInvincibleFrame = PLAYER_INVINCIBLE_FRAME;
        }
        else
        {// �o���A����

            // �������Đ�
            CSound *pSound = CManager::GetSound();
            pSound->Play(CSound::LABEL_SE_EXPLOSION);

            // �唚���G�t�F�N�g (�T�C�Y�͔{)
            CEffect::Create(pos, size + size,
                DEFAULT_COLOR, CEffect::TYPE_BIG_EXPLOSION);

            // ���ΉԃG�t�F�N�g (�ʒu�͂�����Ɖ��A�T�C�Y��1.5�{)
            CEffect::Create(pos + D3DXVECTOR3(size.x / 2, -(size.y / 4), 0.0f), size + size / 2,
                DEFAULT_COLOR, CEffect::TYPE_BLACK_SPARK);

            // �v���C���[�̎g�p�t���O��false��
            m_bUse = false;
        }
    }
}

//====================================================
// ���ɓ����������̏���
//====================================================
D3DXVECTOR3 CPlayer::HitFloor(D3DXVECTOR3 pos, D3DXVECTOR3 size)
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
            if (CGame::GetStage() != CManager::STAGE_��)
            {
                // ���G�łȂ��Ȃ�
                if (CGame::GetInvinciblePlayer() == false && m_nCntInvincibleFrame <= 0)
                {
                    // �o���A�̗L���ŏꍇ����
                    if (m_nBarrier > 0)
                    {// �o���A�L��

                     // �o���A��1������
                        m_nBarrier--;

                        // ���G���Ԃ𓾂�
                        m_nCntInvincibleFrame = PLAYER_INVINCIBLE_FRAME;
                    }
                    else
                    {// �o���A����

                     // �������Đ�
                        CSound *pSound = CManager::GetSound();
                        pSound->Play(CSound::LABEL_SE_EXPLOSION);

                        // �唚���G�t�F�N�g (�T�C�Y�͔{)
                        CEffect::Create(pos, size + size,
                            DEFAULT_COLOR, CEffect::TYPE_BIG_EXPLOSION);

                        // ���ΉԃG�t�F�N�g (�ʒu�͂�����Ɖ��A�T�C�Y��1.5�{)
                        CEffect::Create(pos + D3DXVECTOR3(size.x / 2, -(size.y / 4), 0.0f), size + size / 2,
                            DEFAULT_COLOR, CEffect::TYPE_BLACK_SPARK);

                        // �v���C���[�̎g�p�t���O��false��
                        m_bUse = false;
                    }
                }
            }
        }
    }

    return posLimited;
}

//====================================================
// �v���C���[���ŏ��̈ʒu�ɂ���
//====================================================
void CPlayer::SetStartPos(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos;    // �ʒu

    // �ʒu���擾
    pos = GetPosition();

    // �ʒu�������ʒu�ɕύX
    pos = PLAYER_POS;

    // �ʒu�𔽉f
    SetPosition(pos);

    // ���_���W��ύX
    SetVertex();
}
