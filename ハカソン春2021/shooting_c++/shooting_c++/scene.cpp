//===============================================
//
// �V�[����̃I�u�W�F�N�g���� (scene.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "scene.h"
#include "renderer.h"

//========================================
// �ÓI�����o�ϐ��錾
//========================================
int CScene::m_nNumAll = 0;
CScene *CScene::m_apScene[MAX_POLYGON] = {};

//========================================
// �V�[����̃I�u�W�F�N�g�̃f�t�H���g�R���X�g���N�^
//========================================
CScene::CScene()
{
    for (int nCntObject = 0; nCntObject < MAX_POLYGON; nCntObject++)
    {
        // ��Ȃ�
        if (m_apScene[nCntObject] == NULL)
        {
            // �z��ɓ����
            m_apScene[nCntObject] = this;    // static�Ȃ̂ŁA0����������Ă���Athis��Create��return���󂯎��

            // �������I�u�W�F�N�g���J�E���g
            m_nNumAll++;

            // �I�u�W�F�N�g��ID��ۑ�
            m_nID = nCntObject;

            // �I�u�W�F�N�g�̎�ނ�������
            m_objType = OBJTYPE_NULL;

            // �󂢂Ă��郁�����Ԓn���擾������for�𔲂���
            break;
        }
    }
}

//========================================
// �V�[����̃I�u�W�F�N�g�̃I�[�o�[���C�h���ꂽ�R���X�g���N�^
//========================================
CScene::CScene(OBJTYPE objType)
{
    for (int nCntObject = 0; nCntObject < MAX_POLYGON; nCntObject++)
    {
        // ��Ȃ�
        if (m_apScene[nCntObject] == NULL)
        {
            // �z��ɓ����
            m_apScene[nCntObject] = this;    // static�Ȃ̂ŁA0����������Ă���Athis��Create��return���󂯎��

            // �������I�u�W�F�N�g���J�E���g
            m_nNumAll++;

            // �I�u�W�F�N�g��ID��ۑ�
            m_nID = nCntObject;

            // �I�u�W�F�N�g�̎�ނ�ۑ�
            m_objType = objType;

            // �󂢂Ă��郁�����Ԓn���擾������for�𔲂���
            break;
        }
    }
}

//========================================
// �V�[����̃I�u�W�F�N�g�̃f�X�g���N�^
//========================================
CScene::~CScene()
{

}

//==============================================
// �V�[����̃I�u�W�F�N�g��S�čX�V
//==============================================
void CScene::UpdateAll(void)
{
    for (int nCntObject = 0; nCntObject < MAX_POLYGON; nCntObject++)
    {
        // ���g������Ȃ�
        if (m_apScene[nCntObject] != NULL)
        {
            // �X�V����
            m_apScene[nCntObject]->Update();
        }
    }
}

//==============================================
// �V�[����̃I�u�W�F�N�g��S�ĕ`��
//==============================================
void CScene::DrawAll(void)
{
    // �ϐ��錾
    CScene *apScene[MAX_POLYGON];   // �`��̏��Ԃ�ς��邽�߁A�z��̏����L��
    CScene *pScene;                 // �\�[�g���ɁA�Ⴂ�ԍ��̒l���L��

    // �z��̏�����
    for (int nCntObject = 0; nCntObject < MAX_POLYGON; nCntObject++)
    {
        // �V�[����̃I�u�W�F�N�g�̏����L��
        apScene[nCntObject] = m_apScene[nCntObject];
    }

    // �`�揇���\�[�g(�I��@)���g���āA�^�C�v���ɕ��ёւ���i�����j
    for (int nNum01 = 0; nNum01 < MAX_POLYGON - 1; nNum01++)
    {
        for (int nNum02 = nNum01 + 1; nNum02 < MAX_POLYGON; nNum02++)
        {
            // �ǂ�������g������Ȃ�
            if (apScene[nNum01] != NULL && apScene[nNum02] != NULL)
            {
                // �Ⴂ�ԍ��̃^�C�v�̂ق����傫���Ȃ�
                if (apScene[nNum01]->m_objType > apScene[nNum02]->m_objType)
                {
                    // �Ⴂ�ԍ����L��
                    pScene = apScene[nNum01];

                    // �Ⴂ�ԍ��Ɏ��̔ԍ�����
                    apScene[nNum01] = apScene[nNum02];

                    // ���̔ԍ��ɋL���������̂���
                    apScene[nNum02] = pScene;
                }
            }
        }
    }

    //// �f�o�b�O�p
    //int nCntAll = 0;    // �V�[����̂��ׂẴ|���S���̐����m�F

    // �`��
    for (int nCntObject = 0; nCntObject < MAX_POLYGON; nCntObject++)
    {
        // ���g������Ȃ�
        if (apScene[nCntObject] != NULL)
        {
            // �`�揈��
            apScene[nCntObject]->Draw();
        }
        //else
        //{
        //    nCntAll = nCntObject;
        //}
    }
}

//==============================================
// �V�[����̃I�u�W�F�N�g��S�ĊJ��
//==============================================
void CScene::ReleaseAll(void)
{
    // �I������
    for (int nCntData = 0; nCntData < MAX_POLYGON; nCntData++)
    {
        if (m_apScene[nCntData] != NULL)
        {
            m_apScene[nCntData]->Uninit();
        }
    }
}

//==============================================
// �V�[����̔w�i�A�G�A�e�A�G�t�F�N�g�A�u���b�N�A�A�C�e���A�g�A�O�i��S�ĊJ��
//==============================================
void CScene::ReleaseStage(void)
{
    // �S�G�l�~�[�I������
    for (int nCntData = 0; nCntData < MAX_POLYGON; nCntData++)
    {
        // ���g������Ȃ�
        if (m_apScene[nCntData] != NULL)
        {
            switch (m_apScene[nCntData]->m_objType)
            {
            case OBJTYPE_BG:
                m_apScene[nCntData]->Uninit();
                break;

            case OBJTYPE_ENEMY:
                m_apScene[nCntData]->Uninit();
                break;

            case OBJTYPE_BULLET:
                m_apScene[nCntData]->Uninit();
                break;

            case OBJTYPE_EFFECT:
                m_apScene[nCntData]->Uninit();
                break;

            case OBJTYPE_BLOCK:
                m_apScene[nCntData]->Uninit();
                break;

            case OBJTYPE_ITEM:
                m_apScene[nCntData]->Uninit();
                break;

            case OBJTYPE_WAVE:
                m_apScene[nCntData]->Uninit();
                break;

            case OBJTYPE_FOREGROUND:
                m_apScene[nCntData]->Uninit();
                break;
            }
        }
    }
}

//==============================================
// �V�[����̃I�u�W�F�N�g���擾
//==============================================
CScene * CScene::GetScene(int nCntScene)
{
    if (m_apScene[nCntScene] == NULL)
    {
        return NULL;
    }

    return m_apScene[nCntScene];
}

//==============================================
// �V�[����̃I�u�W�F�N�g��S�ĊJ��
//==============================================
void CScene::Release(void)
{
    // ���g������Ȃ�A
    if (m_apScene[m_nID] != NULL)
    {
        // �C���X�^���X���ƂɎ����Ă���ID��delete��������g���̂ŕۑ�
        int nID = m_nID;

        // �������̊J��
        delete m_apScene[nID];
        m_apScene[nID] = NULL;

        // ���������炷
        m_nNumAll--;
    }
}
