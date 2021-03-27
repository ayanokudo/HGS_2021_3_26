//====================================================================
//
// �V�[����̃I�u�W�F�N�g���� (scene.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"

//================================================
// �}�N����`
//================================================
#define MAX_POLYGON 2048   // �|���S���̍ő吔

//================================================
// �N���X�錾
//================================================

// �I�u�W�F�N�g�̃N���X
class CScene
{
public:
    // �I�u�W�F�N�g�̎��(�`�揇)
    typedef enum
    {
        OBJTYPE_NULL,      // �Ȃ�
        OBJTYPE_BG,        // �w�i
        OBJTYPE_LOGO,      // ���S
        OBJTYPE_RANKING,   // �����L���O
        OBJTYPE_BLOCK,     // �u���b�N
        OBJTYPE_AFTERIMAGE,// �c��
        OBJTYPE_PLAYER,    // �v���C���[
        OBJTYPE_ENEMY,     // �G�l�~�[
        OBJTYPE_HELPER,    // �w���p�[
        OBJTYPE_BULLET,    // �e
        OBJTYPE_EFFECT,    // �G�t�F�N�g
        OBJTYPE_ITEM,      // �A�C�e��
        OBJTYPE_FOREGROUND,// �O�i
        OBJTYPE_BUBBLE,    // �A
        OBJTYPE_LIGHT2D,   // ���C�g2D
        OBJTYPE_WAVE,      // �g
        OBJTYPE_UI,        // UI
        OBJTYPE_SCORE,     // �X�R�A
        OBJTYPE_REVERSE,   // ���]����
        OBJTYPE_WHITEFADE, // ���t�F�[�h
        OBJTYPE_MAX        // �I�u�W�F�N�g�̎�ނ̍ő吔
    }OBJTYPE;

    CScene();
    CScene(OBJTYPE objType);    // �C�j�V�����C�U�ŃI�u�W�F�N�g�^�C�v��R�Â�
    virtual ~CScene();  // �e�N���X�̃f�X�g���N�^��virtual�����邱�ƂŁA���������[�N��}����
    virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;
    virtual void Uninit(void) = 0;
    virtual void Update(void) = 0;
    virtual void Draw(void) = 0;
    static void UpdateAll(void);        // �S�čX�V
    static void DrawAll(void);          // �S�ĕ`��
    static void ReleaseAll(void);       // �S�ĊJ��
    static void ReleaseStage(void);     // �S�Ă̔w�i�A�G�A�u���b�N�A�A�C�e�����J��
    OBJTYPE GetObjType(void) { return m_objType; }  // �I�u�W�F�N�g�^�C�v���擾
    static CScene *GetScene(int nCntScene);         // �V�[�����擾

protected:
    void Release(void);                 // �P�̂��J��

private:
    static CScene *m_apScene[MAX_POLYGON];  // �V�[����̃I�u�W�F�N�g���
    static int m_nNumAll;                   // �V�[����̃I�u�W�F�N�g�̍ő吔
    int m_nID;   // �J������ԍ����L��(static�̓C���X�^���X�֌W�Ȃ������Ă��邪�A���ʂ̂̓C���X�^���X���ƂɃ����o�ϐ��������Ă���)
    OBJTYPE m_objType;                      // �I�u�W�F�N�g�̎��
};

#endif