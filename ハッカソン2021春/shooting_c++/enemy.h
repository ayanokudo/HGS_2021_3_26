//====================================================================
//
// �G�l�~�[�̏��� (enemy.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene2d.h"

//================================================
// �}�N����`
//================================================

#define DONT_CHANGE_MOVE 1000               // �����Ŏg���A�ړ���ς��Ȃ����߂̐��l
#define ENEMY_COUNTERATTACK_COOL_TIME 5     // �����̃N�[���^�C��
#define MAX_ENEMY_COLLISION 3               // �G��̂ɑ΂���A�����蔻��̍ő吔
#define WEAK_HIT_DAMAGE_UP_RATE 1.15f        // ��_���ʂŏオ��_���[�W����

// �n�G�̊e�ݒ�
#define ENEMY_FLY_SIZE D3DXVECTOR3(80.0f, 80.0f, 0.0f)
#define ENEMY_FLY_COLLISION_SIZE D3DXVECTOR3(50.0f, 50.0f, 0.0f)
#define ENEMY_FLY_LIFE 70
#define ENEMY_FLY_SPEED 6.0f
#define ENEMY_FLY_SCORE 500

// �[���̊e�ݒ�
#define ENEMY_SKELETON_SIZE D3DXVECTOR3(75.0f, 90.0f, 0.0f)
#define ENEMY_SKELETON_COLLISION_POS D3DXVECTOR3(0.0f, 7.5f, 0.0f)
#define ENEMY_SKELETON_COLLISION_SIZE D3DXVECTOR3(45.0f, 45.0f, 0.0f)
#define ENEMY_SKELETON_LIFE 150
#define ENEMY_SKELETON_SPEED 3.0f
#define ENEMY_SKELETON_SCORE 1000

// �Β��̊e�ݒ�
#define ENEMY_GREEN_BIRD_SIZE D3DXVECTOR3(120.0f, 120.0f, 0.0f)
#define ENEMY_GREEN_BIRD_COLLISION_SIZE D3DXVECTOR3(45.0f, 50.0f, 0.0f)
#define ENEMY_GREEN_BIRD_LIFE 350
#define ENEMY_GREEN_BIRD_SPEED 1.5f
#define ENEMY_GREEN_BIRD_SCORE 3000
#define ENEMY_GREEN_BIRD_STOP 300                                       // �~�܂�܂ł̃J�E���^
#define ENEMY_GREEN_BIRD_DANGER 510                                     // �f���W���[�x���̃J�E���^
#define ENEMY_GREEN_BIRD_GOD 600                                        // �S�b�h�o�[�h����܂ł̃J�E���^
#define ENEMY_GREEN_BIRD_GOD_SPEED 15.0f                                // �S�b�h�o�[�h���̑���
#define ENEMY_GREEN_BIRD_ATTACK_COUNTER 61                              // �e�����J�E���^
#define ENEMY_GREEN_BIRD_BULLET_SIZE D3DXVECTOR3(35.0f, 35.0f, 0.0f)    // �e�̑傫��
#define ENEMY_GREEN_BIRD_BULLET_SPEED 7.5f                              // �e�̑���
#define ENEMY_GREEN_BIRD_SET_EFFECT_COUNT 3                             // �����Z�b�g����J�E���^

// ���J���X�̐ݒ�
#define ENEMY_CROW_SIZE D3DXVECTOR3(85.0f, 85.0f, 0.0f)
#define ENEMY_CROW_COLLISION_SIZE D3DXVECTOR3(55.0f, 55.0f, 0.0f)
#define ENEMY_CROW_LIFE 1
#define ENEMY_CROW_SPEED 9.0f
#define ENEMY_CROW_SCORE 10000

// �{�X�X�̊e�ݒ�
#define ENEMY_BOSS_FOREST_SIZE D3DXVECTOR3(600.0f, 600.0f, 0.0f)
#define ENEMY_BOSS_FOREST_COLLISION_POS_1 D3DXVECTOR3(0.0f, 50.0f, 0.0f)        // ��
#define ENEMY_BOSS_FOREST_COLLISION_SIZE_1 D3DXVECTOR3(125.0f, 380.0f, 0.0f)    // ��
#define ENEMY_BOSS_FOREST_COLLISION_POS_2 D3DXVECTOR3(0.0f, -75.0f, 0.0f)       // �t����
#define ENEMY_BOSS_FOREST_COLLISION_SIZE_2 D3DXVECTOR3(300.0f, 150.0f, 0.0f)    // �t����
#define ENEMY_BOSS_FOREST_LIFE 6000
#define ENEMY_BOSS_FOREST_SPEED_X 2.75f
#define ENEMY_BOSS_FOREST_SPEED_Y 1.75f
#define ENEMY_BOSS_FOREST_SCORE 50000
#define ENEMY_BOSS_FOREST_STOP_X 330                                            // X�����~�܂�܂ł̃J�E���^
#define ENEMY_BOSS_FOREST_STOP_Y 150                                            // Y�����~�܂�܂ł̃J�E���^
#define ENEMY_BOSS_FOREST_ATTACK_COUNTER 100                                    // �U���̃J�E���^
#define ENEMY_BOSS_FOREST_SET_ATTACK_POS_Y 135.0f                               // �U���̐ݒu�ʒuY
#define ENEMY_BOSS_FOREST_CHANGE_ATTACK 2400                                    // �U�����@��ς���J�E���^
#define ENEMY_BOSS_FOREST_SCATTER 12                                            // �t���ς�}���o���܂��J�E���^
#define ENEMY_BOSS_FOREST_SCATTER_LEAF_POS_Y -150.0f                            // �t���ς��o���܂��ہA���S���炸�炷�l
#define ENEMY_BOSS_FOREST_SHAKE_POS_X 3.5f                                      // ���ɗh���l
#define ENEMY_BOSS_FOREST_WEEKNESS 0                                            // ��_���ʂ͊�
#define ENEMY_BOSS_FOREST_WEEKNESS_ADD_SCORE 10000                              // ��_���ʂœ|�������̉��Z�X�R�A

// ���̊e�ݒ�
#define ENEMY_BLUE_BIRD_SIZE D3DXVECTOR3(120.0f, 120.0f, 0.0f)
#define ENEMY_BLUE_BIRD_COLLISION_SIZE D3DXVECTOR3(45.0f, 50.0f, 0.0f)
#define ENEMY_BLUE_BIRD_LIFE 150                                        // 1�ʂ̃{�X�펞�̃��C�t
#define ENEMY_BLUE_BIRD_WAY_LIFE 400                                    // �����̃��C�t
#define ENEMY_BLUE_BIRD_SPEED 2.0f
#define ENEMY_BLUE_BIRD_SCORE 4000
#define ENEMY_BLUE_BIRD_STOP 280                                        // �~�܂�܂ł̃J�E���^
#define ENEMY_BLUE_BIRD_LEAVE 2400                                      // ����܂ł̃J�E���^
#define ENEMY_BLUE_BIRD_WAY_LEAVE (720)                                 // �����ŋ���܂ł̃J�E���^
#define ENEMY_BLUE_BIRD_ATTACK_COUNTER 180                              // �e�����J�E���^
#define ENEMY_BLUE_BIRD_BULLET_SIZE D3DXVECTOR3(40.0f, 40.0f, 0.0f)     // �e�̑傫��
#define ENEMY_BLUE_BIRD_BULLET_SPEED 5.0f                               // �e�̑���

// �C�����V�̊e�ݒ�
#define ENEMY_CATERPILLAR_SIZE D3DXVECTOR3(90.0f, 80.0f, 0.0f)
#define ENEMY_CATERPILLAR_COLLISION_SIZE D3DXVECTOR3(60.0f, 50.0f, 0.0f)
#define ENEMY_CATERPILLAR_LIFE 60
#define ENEMY_CATERPILLAR_SCORE 250
#define ENEMY_CATERPILLAR_ROT_SPEED 0.2f                                // ��]�X�s�[�h
#define ENEMY_CATERPILLAR_FALL_COUNT 90                                 // ��������܂ł̃J�E���^
#define ENEMY_CATERPILLAR_RIGHT_BOUND D3DXVECTOR3(3.0f, -7.5f, 0.0f)    // �E�Ƀo�E���h
#define ENEMY_CATERPILLAR_LEFT_BOUND D3DXVECTOR3(-3.0f, -7.5f, 0.0f)    // ���Ƀo�E���h

// �O�\�N���V�̊e�ݒ�
#define ENEMY_GUSOKU_SIZE D3DXVECTOR3(85.0f, 85.0f, 0.0f)
#define ENEMY_GUSOKU_COLLISION_SIZE D3DXVECTOR3(55.0f, 55.0f, 0.0f)
#define ENEMY_GUSOKU_LIFE 1
#define ENEMY_GUSOKU_SPEED 9.0f
#define ENEMY_GUSOKU_SCORE 10000

// �T�[�f�B���̊e�ݒ�
#define ENEMY_SARDINE_SIZE D3DXVECTOR3(120.0f, 55.0f, 0.0f)
#define ENEMY_SARDINE_COLLISION_SIZE D3DXVECTOR3(90.0f, 25.0f, 0.0f)
#define ENEMY_SARDINE_LIFE 100
#define ENEMY_SARDINE_MOVE D3DXVECTOR3(5.0f, 2.5f, 0.0f)
#define ENEMY_SARDINE_SCORE 1800
#define ENEMY_SARDINE_ATTACK_COUNTER 90                             // �e�����J�E���^
#define ENEMY_SARDINE_BULLET_SIZE D3DXVECTOR3(40.0f, 40.0f, 0.0f)   // �e�̑傫��
#define ENEMY_SARDINE_BULLET_SPEED 7.0f                             // �e�̑���
#define ENEMY_SARDINE_DONT_SHOT_POS_X 475.0f                        // ����X���ŁA�e�������Ȃ�����
#define ENEMY_SARDINE_STRAIGHT_SPEED 5.5f                           // �����Ői�ނƂ��̑���
// �T�[�f�B���̈ړ��̈�
#define ENEMY_SARDINE_INVERSIO_POS_Y_1 140.0f
#define ENEMY_SARDINE_INVERSIO_POS_Y_2 250.0f
#define ENEMY_SARDINE_INVERSIO_POS_Y_3 340.0f
#define ENEMY_SARDINE_INVERSIO_POS_Y_4 450.0f
#define ENEMY_SARDINE_INVERSIO_POS_Y_5 540.0f
#define ENEMY_SARDINE_INVERSIO_POS_Y_6 650.0f

// �L���m���̊e�ݒ�
#define ENEMY_CANNON_SIZE D3DXVECTOR3(120.0f, 120.0f, 0.0f)
#define ENEMY_CANNON_COLLISION_SIZE D3DXVECTOR3(60.0f, 60.0f, 0.0f)
#define ENEMY_CANNON_LIFE 75
#define ENEMY_CANNON_SCORE 5000
#define ENEMY_CANNON_ATTACK_COUNTER 100                             // �e�����J�E���^
#define ENEMY_CANNON_BULLET_SIZE D3DXVECTOR3(40.0f, 40.0f, 0.0f)    // �e�̑傫��
#define ENEMY_CANNON_BULLET_SPEED 6.0f                              // �e�̑���
#define ENEMY_CANNON_TURN_SPEED 0.035f                              // �U��������x

// �g�[�s�[�h�̊e�ݒ�
#define ENEMY_TORPEDO_SIZE D3DXVECTOR3(100.0f, 100.0f, 0.0f)
#define ENEMY_TORPEDO_COLLISION_SIZE D3DXVECTOR3(60.0f, 60.0f, 0.0f)
#define ENEMY_TORPEDO_LIFE 30
#define ENEMY_TORPEDO_SCORE 2800
#define ENEMY_TORPEDO_SCORE_IN_BOSS 1200                            // �{�X�펞�̃X�R�A
#define ENEMY_TORPEDO_FALLING_SPEED 1.5f                            // �������x
#define ENEMY_TORPEDO_FALLING_SPEED_IN_BOSS 4.5f                    // �{�X�펞�̗������x
#define ENEMY_TORPEDO_BULLET_SIZE D3DXVECTOR3(25.0f, 25.0f, 0.0f)   // �e�̑傫��
#define ENEMY_TORPEDO_BULLET_SPEED 3.5f                             // �e�̑���

// �h���S���̊e�ݒ�
#define ENEMY_BOSS_DRAGON_SIZE D3DXVECTOR3(500.0f, 400.0f, 0.0f)
#define ENEMY_BOSS_DRAGON_COLLISION_POS_1 D3DXVECTOR3(-67.5f, -8.75f, 0.0f)     // ��
#define ENEMY_BOSS_DRAGON_COLLISION_SIZE_1 D3DXVECTOR3(200.0f, 22.5f, 0.0f)     // ��
#define ENEMY_BOSS_DRAGON_COLLISION_POS_2 D3DXVECTOR3(50.0f, 70.0f, 0.0f)       // ����
#define ENEMY_BOSS_DRAGON_COLLISION_SIZE_2 D3DXVECTOR3(200.0f, 150.0f, 0.0f)    // ����
#define ENEMY_BOSS_DRAGON_COLLISION_POS_3 D3DXVECTOR3(50.0f, 0.0f, 0.0f)        // ��
#define ENEMY_BOSS_DRAGON_COLLISION_SIZE_3 D3DXVECTOR3(60.0f, 210.0f, 0.0f)     // ��
#define ENEMY_BOSS_DRAGON_LIFE 8500
#define ENEMY_BOSS_DRAGON_SCORE 60000
#define ENEMY_BOSS_DRAGON_STOP_POS_X 1188.0f                                    // �~�܂�X���W
#define ENEMY_BOSS_DRAGON_STOP_POS_Y 490.0f                                     // �~�܂�Y���W
#define ENEMY_BOSS_DRAGON_AURA_COLOR D3DXCOLOR(1.0f,0.99f,0.0f,1.0f)            // �I�[���̃G�t�F�N�g�̐F
#define ENEMY_BOSS_DRAGON_AURA_SET_POS_Y 150.0f                                 // �I�[���̐ݒu�ʒuY
#define ENEMY_BOSS_DRAGON_WEEKNESS 0                                            // ��_���ʂ͊�
#define ENEMY_BOSS_DRAGON_WEEKNESS_ADD_SCORE 20000                              // ��_���ʂœ|�������̉��Z�X�R�A
#define ENEMY_BOSS_DRAGON_FIRST_ATTACK_COUNTER 330                              // �ŏ��̍U��������J�E���^

// �}�C���X�C�[�v
#define MINE_SWEEP_COUNTER 300 // �U���̑S�̃t���[��
#define MINE_SWEEP_CREATE 240  // �N���G�C�g�t���[��
#define MINE_SWEEP_CHANCE 160  // ���t���[��

// ���C�j�[�o���b�g
#define RAINY_BULLET_SET_POS_Y -14.0f                              // �U���̐ݒu�ʒuY
#define RAINY_BULLET_SIZE (D3DXVECTOR3(30.0f,30.0f,0.0f))          // ���C�j�[�o���b�g�̑傫��
#define RAINY_BULLET_LIGHT_SIZE (D3DXVECTOR3(45.0f,45.0f,0.0f))    // ���̃��C�j�[�o���b�g�̑傫��
#define RAINY_BULLET_COUNTER 240                                   // �U���̑S�̃t���[��
#define RAINY_BULLET_CREATE 180                                    // �N���G�C�g�t���[��
#define RAINY_BULLET_CHANCE 160                                    // ���t���[��

// �z�[�~���O�V���b�g
#define HOMING_SHOT_SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))            // �z�[�~���O�V���b�g�̑傫��
#define HOMING_SHOT_LIGHT_SIZE (D3DXVECTOR3(100.0f,100.0f,0.0f))    // ���̃z�[�~���O�V���b�g�̑傫��
#define HOMING_SHOT_SHIFT_POS 75.0f                                 // �z�[�~���O�V���b�g��������o���Ă���悤�ɂ��炷
#define HOMING_SHOT_COUNTER 120                                     // �U���̑S�̃t���[��
#define HOMING_SHOT_CREATE 45                                       // �N���G�C�g�t���[��
#define HOMING_SHOT_CHANCE 90                                       // ���t���[��

// ��Η��Ƃ�
#define ROCK_SLIDE_SET_POS_Y -200.0f // �U���̐ݒu�ʒuY
#define ROCK_SLIDE_COUNTER 180       // �U���̑S�̃t���[��
#define ROCK_SLIDE_CREATE 60         // �N���G�C�g�t���[��
#define ROCK_SLIDE_CHANCE 180        // ���t���[��

// �h���S���`���[�W
#define DRAGON_CHARGE_SIZE (D3DXVECTOR3(75.0f,75.0f,0.0f))    // �h���S���`���[�W�̑傫��
#define DRAGON_CHARGE_STAGE_1 25.0f                           // �`���[�W�̐i�s�x1
#define DRAGON_CHARGE_STAGE_2 50.0f                           // �`���[�W�̐i�s�x2
#define DRAGON_CHARGE_STAGE_3 75.0f                           // �`���[�W�̐i�s�x3
#define DRAGON_CHARGE_FULL 100.0f                             // �`���[�W�̐i�s�x4
#define DRAGON_CHARGE_TIME_1 1500.0f                          // �`���[�W����1
#define DRAGON_CHARGE_TIME_2 3000.0f                          // �`���[�W����2
#define DRAGON_CHARGE_TIME_3 4500.0f                          // �`���[�W����3
#define DRAGON_CHARGE_TIME_4 6000.0f                          // �`���[�W����4
#define DRAGON_CHARGE_STOP 10000.0f                           // �`���[�W���ԃX�g�b�v
#define DRAGON_CHARGE_HEAL1 2000                              // �`���[�W��HP��1
#define DRAGON_CHARGE_HEAL2 1000                              // �`���[�W��HP��2
#define DRAGON_CHARGE_HEAL3 500                               // �`���[�W��HP��3
#define DRAGON_CHARGE_HEAL4 250                               // �`���[�W��HP��4
#define DRAGON_CHARGE_COUNTER 300                             // �U���̑S�̃t���[��
#define DRAGON_CHARGE_CREATE 30                               // �N���G�C�g�t���[��
#define DRAGON_CHARGE_CHANCE 90                               // ���t���[��

// �����̊e�ݒ�
#define ENEMY_RED_BIRD_SIZE D3DXVECTOR3(120.0f, 120.0f, 0.0f)
#define ENEMY_RED_BIRD_COLLISION_SIZE D3DXVECTOR3(45.0f, 50.0f, 0.0f)
#define ENEMY_RED_BIRD_LIFE 800
#define ENEMY_RED_BIRD_SPEED 1.5f
#define ENEMY_RED_BIRD_SCORE 5000
#define ENEMY_RED_BIRD_STOP 500                                       // �~�܂�܂ł̃J�E���^
#define ENEMY_RED_BIRD_DANGER 770                                     // �f���W���[�x���̃J�E���^
#define ENEMY_RED_BIRD_GOD 860                                        // �S�b�h�o�[�h����܂ł̃J�E���^
#define ENEMY_RED_BIRD_GOD_SPEED 15.0f                                // �S�b�h�o�[�h���̑���
#define ENEMY_RED_BIRD_ATTACK_COUNTER 149                             // �e�����J�E���^
#define ENEMY_RED_BIRD_BULLET_SIZE D3DXVECTOR3(50.0f, 50.0f, 0.0f)    // �e�̑傫��
#define ENEMY_RED_BIRD_BULLET_SPEED 8.75f                             // �e�̑���
#define ENEMY_RED_BIRD_SET_EFFECT_COUNT 3                             // �����Z�b�g����J�E���^

// �R�E�����̊e�ݒ�
#define ENEMY_BAT_SIZE D3DXVECTOR3(80.0f, 80.0f, 0.0f)
#define ENEMY_BAT_COLLISION_SIZE D3DXVECTOR3(50.0f, 50.0f, 0.0f)
#define ENEMY_BAT_LIFE 50
#define ENEMY_BAT_SPEED 7.0f
#define ENEMY_BAT_SCORE 2500
#define ENEMY_BAT_STOP_HOMING 270                                     // �z�[�~���O����߂�J�E���^
#define ENEMY_BAT_SET_EFFECT_COUNT 5                                  // �����Z�b�g����J�E���^

// �}���`�o�[�h�̊e�ݒ�
#define ENEMY_MULTI_BIRD_SIZE D3DXVECTOR3(180.0f, 180.0f, 0.0f)
#define ENEMY_MULTI_BIRD_COLLISION_SIZE D3DXVECTOR3(67.5f, 65.0f, 0.0f)
#define ENEMY_MULTI_BIRD_LIFE 1950
#define ENEMY_MULTI_BIRD_SPEED 2.0f
#define ENEMY_MULTI_BIRD_SCORE 77770
#define ENEMY_MULTI_BIRD_CHANGE_MOVE 275                                 // �ړ���ς���܂ł̃J�E���^
#define ENEMY_MULTI_BIRD_RETURN_X 100                                    // ���ړ���܂�Ԃ��J�E���^
#define ENEMY_MULTI_BIRD_LEAVE (1850)                                    // ����܂ł̃J�E���^
#define ENEMY_MULTI_BIRD_ATTACK_COUNTER 130                              // �e�����J�E���^
#define ENEMY_MULTI_BIRD_BULLET_SIZE D3DXVECTOR3(50.0f, 50.0f, 0.0f)     // �e�̑傫��
#define ENEMY_MULTI_BIRD_BULLET_FIRE_SPEED 7.0f                          // �}���`�o�[�h�̉��e��
#define ENEMY_MULTI_BIRD_BULLET_WATER_SPEED 7.75f                        // �}���`�o�[�h�̐��e��
#define ENEMY_MULTI_BIRD_BULLET_GRASS_SPEED 6.5f                         // �}���`�o�[�h�̑��e��

// �u���C�Y�̊e�ݒ�
#define ENEMY_BOSS_BLAZE_SIZE D3DXVECTOR3(400.0f, 400.0f, 0.0f)
#define ENEMY_BOSS_BLAZE_COLLISION_POS_1 D3DXVECTOR3(-50.0f, -10.0f, 0.0f)     // ��
#define ENEMY_BOSS_BLAZE_COLLISION_SIZE_1 D3DXVECTOR3(25.0f, 60.0f, 0.0f)      // ��
#define ENEMY_BOSS_BLAZE_COLLISION_POS_2 D3DXVECTOR3(-10.0f, 82.5f, 0.0f)      // ����
#define ENEMY_BOSS_BLAZE_COLLISION_SIZE_2 D3DXVECTOR3(102.5f, 85.0f, 0.0f)     // ����
#define ENEMY_BOSS_BLAZE_LIFE 13000
#define ENEMY_BOSS_BLAZE_SCORE 50000
#define ENEMY_BOSS_BLAZE_SCORE_ADD_STOCK_RATE 100000                           // 1�X�g�b�N�ɑ΂��āA�X�R�A�����Z���銄��
#define ENEMY_BOSS_BLAZE_SCORE_ADD_BARRIER_RATE 50000                          // 1�o���A�ɑ΂��āA�X�R�A�����Z���銄��
#define ENEMY_BOSS_BLAZE_STOP_POS_X 1160.0f                                    // �~�܂�X���W
#define ENEMY_BOSS_BLAZE_STOP_POS_Y 330.0f                                     // �~�܂�Y���W
#define ENEMY_BOSS_BLAZE_WEEKNESS 0                                            // ��_���ʂ͊�
#define ENEMY_BOSS_BLAZE_WEEKNESS_ADD_SCORE 25000                              // ��_���ʂœ|�������̉��Z�X�R�A
#define ENEMY_BOSS_BLAZE_FIRST_ATTACK_COUNTER 150                              // �ŏ��̍U��������J�E���^
#define ENEMY_BOSS_BLAZE_SPEED 2.77f                                           // �ړ����x
#define ENEMY_BOSS_BLAZE_AURA_SIZE D3DXVECTOR3(30.0f, 30.0f, 0.0f)             // �I�[���̑傫��
#define ENEMY_BOSS_BLAZE_AURA_SET_POS_Y 100.0f                                 // �I�[���̐ݒu�ʒuY
#define ENEMY_BOSS_BLAZE_AURA_SET_COUNT 2                                      // �I�[�����Z�b�g����J�E���^

// �o�[�j���O�o���b�g
#define BURNING_BULLET_SET_POS_Y -13.0f                              // �U���̐ݒu�ʒuY
#define BURNING_BULLET_SET_POS_LEFT -13.0f                           // �U���̐ݒu�ʒu��
#define BURNING_BULLET_SET_POS_RIGHT (SCREEN_WIDTH + 13.0f)          // �U���̐ݒu�ʒu�E
#define BURNING_BULLET_SIZE (D3DXVECTOR3(27.5f,27.5f,0.0f))          // �o���b�g�̑傫��
#define BURNING_BULLET_COUNTER 210                                   // �U���̑S�̃t���[��
#define BURNING_BULLET_CREATE 150                                    // �N���G�C�g�t���[��
#define BURNING_BULLET_CHANCE 140                                    // ���t���[��

// �E�B���h�o���b�g
#define WIND_BULLET_SET_POS_RIGHT (SCREEN_WIDTH + 13.0f)          // �U���̐ݒu�ʒu�E
#define WIND_BULLET_SIZE (D3DXVECTOR3(27.5f,27.5f,0.0f))          // �o���b�g�̑傫��
#define WIND_BULLET_COUNTER 180                                   // �U���̑S�̃t���[��
#define WIND_BULLET_CREATE 150                                    // �N���G�C�g�t���[��
#define WIND_BULLET_CHANCE 140                                    // ���t���[��

// �S�b�h�o�[�h
#define GOD_BIRD_COUNTER 210                                                        // �U���̑S�̃t���[��
#define GOD_BIRD_DANGER 150                                                         // �f���W���[�x���̃J�E���^
#define GOD_BIRD_DANGER_SIZE D3DXVECTOR3(375.0f,187.5f,0.0f)                        // �f���W���[�x���̑傫��
#define GOD_BIRD_CREATE 60                                                          // �N���G�C�g�t���[��
#define GOD_BIRD_CHANCE 150                                                         // ���t���[��
#define GOD_BIRD_FIRST_SPEED 6.0f                                                   // ����
#define GOD_BIRD_ACCEL_SPEED 27.5f                                                  // ������
#define GOD_BIRD_WARP_POS D3DXVECTOR3(ENEMY_BOSS_BLAZE_STOP_POS_X, -225.0f, 0.0f)   // ���[�v���Ė߂��Ă���ʒu

// ���e�I�X�g���C�N
#define METEO_STRIKE_SET_POS_X 1480.0f // �U���̐ݒu�ʒuX
#define METEO_STRIKE_SET_POS_Y -200.0f // �U���̐ݒu�ʒuY
#define METEO_STRIKE_COUNTER 180       // �U���̑S�̃t���[��
#define METEO_STRIKE_CREATE 60         // �N���G�C�g�t���[��
#define METEO_STRIKE_CHANCE 140        // ���t���[��

// �_�����[�h
#define GOD_FIRE_STOP_COUNTERATTACK 1000                 // ��������߂�
#define GOD_FIRE_SIZE (D3DXVECTOR3(70.0f,70.0f,0.0f))    // �_���̑傫��
#define GOD_FIRE_STAGE_1 25.0f                           // �`���[�W�̐i�s�x1
#define GOD_FIRE_STAGE_2 50.0f                           // �`���[�W�̐i�s�x2
#define GOD_FIRE_STAGE_3 75.0f                           // �`���[�W�̐i�s�x3
#define GOD_FIRE_FULL 100.0f                             // �`���[�W�̐i�s�x4
#define GOD_FIRE_VALUE_FOR_ONE_CHARGE 45.0f              // ��i�K�`���[�W����̂ɕK�v�Ȓl
#define GOD_FIRE_BLAZE_ATTACK_VALUE 15.0f                // �u���C�Y�̍U���ɂ��A�����l�̏㏸��
#define GOD_FIRE_PLAYER_FIRE_ATTACK_VALUE 1.0f           // �v���C���[�̉��U���ɂ��A�����l�̏㏸��

//================================================
// �N���X�錾
//================================================

// �G�l�~�[�N���X
class CEnemy : public CScene2D
{
public:

    // �G�l�~�[�̎��
    typedef enum
    {
        TYPE_FLY,           // �n�G(��)
        TYPE_SKELETON,      // �[��(��)
        TYPE_GREEN_BIRD,    // �Β�(��)
        TYPE_CROW,          // ���J���X(�}���`)
        TYPE_BLUE_BIRD,     // ��(��)
        TYPE_BOSS_FOREST,   // �{�X�X(��)
        TYPE_CATERPILLAR,   // �C�����V(��)
        TYPE_GUSOKU,        // �O�\�N���V(�}���`)
        TYPE_SARDINE,       // �T�[�f�B��(��)
        TYPE_CANNON,        // �L���m��(��)
        TYPE_TORPEDO,       // �g�[�s�[�h(��)
        TYPE_BOSS_DRAGON,   // �h���S��(��)
        TYPE_RED_BIRD,      // �Ԓ�(��)
        TYPE_BAT,           // �R�E����(��)
        TYPE_MULTI_BIRD,    // �}���`�o�[�h(�}���`)
        TYPE_BOSS_BLAZE,    // �u���C�Y(��)
        TYPE_MAX            // ��ނ̍ő吔
    }TYPE;

    // �����蔻��̏��
    typedef struct
    {
        D3DXVECTOR3 posToShift;     // ���S���炸�炷�ʒu
        D3DXVECTOR3 size;           // ��`�̃T�C�Y
    }COLLISION;

    // �T�[�f�B���̈ړ��̈�
    typedef enum
    {
        SARDINE_MOVE_UPPER,         // ��i
        SARDINE_MOVE_MIDDLE,        // ���i
        SARDINE_MOVE_LOWER,         // ���i
        SARDINE_MOVE_STRAIGHT,      // �^������
        SARDINE_MOVE_MAX            // ��ނ̍ő吔
    }SARDINE_MOVE;

    // �h���S���̍U��
    typedef enum
    {
        DRAGON_ATTACK_NONE = 0,       // �ҋ@��
        DRAGON_ATTACK_MINE_SWEEP,     // �}�C���X�C�[�v
        DRAGON_ATTACK_RAINY_BULLET,   // ���C�j�[�o���b�g
        DRAGON_ATTACK_HOMING_SHOT,    // �z�[�~���O�V���b�g
        DRAGON_ATTACK_ROCK_SLIDE,     // ��Η��Ƃ�
        DRAGON_ATTACK_CHARGE,         // �`���[�W
        DRAGON_ATTACK_MAX             // ��ނ̍ő吔
    }DRAGON_ATTACK;

    // �u���C�Y�̍U��
    typedef enum
    {
        BLAZE_ATTACK_NONE = 0,       // �ҋ@��
        BLAZE_ATTACK_BURNING_BULLET, // �o�[�j���O�o���b�g
        BLAZE_ATTACK_WIND_BULLET,    // �E�B���h�o���b�g
        BLAZE_ATTACK_GOD_BIRD,       // �S�b�h�o�[�h
        BLAZE_ATTACK_METEO_STRIKE,   // ���e�I�X�g���C�N
        BLAZE_ATTACK_MAX             // ��ނ̍ő吔
    }BLAZE_ATTACK;

    CEnemy();
    ~CEnemy();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static HRESULT Load(void);
    static void Unload(void);
    static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nCntChangeMove, bool bMoveUp, TYPE type);
    void Hit(D3DXVECTOR3 posBullet, const int nCounterState, int nDamage, const int nWhereHit, const ELEMENT element);
    void DamageCalculation(D3DXVECTOR3 pos, const ELEMENT element, int nDamage);
    bool DefeatEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void CounterAttack(void);
    float GetAngleToPlayer(void);
    int GetCountHitWater(void) { return m_nCounterHitWater; }           // ���̃q�b�g�J�E���^��Ԃ�
    int GetCountHitLight(void) { return m_nCounterHitLight; }           // ���̃q�b�g�J�E���^��Ԃ�
    COLLISION GetCollision(int nCnt) { return m_aCollision[nCnt]; }     // �Փ˂Ɋւ������Ԃ�
    int GetCntCollision(void) { return m_nCntCollision; }               // �����蔻��̐���Ԃ�
    D3DXVECTOR3 GetPosOld(void) { return m_posOld; }                    // 1F�O�̈ʒu��Ԃ�

    D3DXVECTOR3 Bound(D3DXVECTOR3 pos, D3DXVECTOR3 size);               // ���ɓ��������ۂ̃o�E���h
    void ForestMovement(D3DXVECTOR3 playerPos);                         // �{�X�X�̓���
    bool TorpedoExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 size);           // �g�[�s�[�h�̔���
    D3DXVECTOR3 DragonMovement(D3DXVECTOR3 pos, D3DXVECTOR3 size);      // �h���S���̍s��
    void DragonSetChance(int nChanceFrame);                             // �h���S���̌��t���[��
    void DragonSetAura(D3DXVECTOR3 pos);                                // �h���S���I�[��
    void MultiBird(D3DXVECTOR3 pos);                                    // �}���`�o�[�h
    D3DXVECTOR3 BlazeMovement(D3DXVECTOR3 pos, D3DXVECTOR3 size);       // �u���C�Y�̍s��
    void BlazeSetChance(int nChanceFrame);                              // �u���C�Y�̌��t���[��
    void BlazeSetAura(D3DXVECTOR3 pos, ELEMENT element);                // �u���C�Y�I�[��
    void BurningBullet(void);                                           // �o�[�j���O�o���b�g
    void WindBullet(void);                                              // �E�B���h�o���b�g

private:
    static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];      // �ǂݍ��񂾃e�N�X�`����ۑ�����
    D3DXVECTOR3 m_posOld;                                 // 1F�O�̈ʒu
    D3DXVECTOR3 m_move;                                   // �ړ���
    COLLISION m_aCollision[MAX_ENEMY_COLLISION];          // �����蔻��̏��
    int m_nCntCollision;                                  // �����蔻��̐�
    int m_nWhereHit;                                      // �ǂ��ɓ���������

    float m_fMoveAngle;     // �ړ��̊p�x
    int m_nCntChangeMove;   // �ړ��ʂ��ς�肾���܂ł̃J�E���g
    bool m_bMoveUp;         // ��ɍs�����ǂ���

    int m_nBound;           // �o�E���h��

    float m_fDestAngle;     // �ړI�̊p�x
    float m_fMinAngle;      // �ŏ��̐U������p�x

    int m_nLife;                    // ���C�t
    int m_nMaxLife;                 // �ő僉�C�t
    int m_nCounterState;            // ��ԃJ�E���^
    int m_nCounterHitWater;         // ���̃q�b�g�J�E���^
    int m_nCounterHitLight;         // ���̃q�b�g�J�E���^
    int m_nCounterAttackCoolTime;   // �����܂ł̃J�E���^
    bool m_bDefeatWithWeak;         // ��_�œ|�������ǂ���
    bool m_bDefeatOneHit;           // �ꔭ�œ|�������ǂ���
    TYPE m_type;                    // �G�l�~�[�̎��
    ELEMENT m_element;              // �G�l�~�[�̑���
};

#endif