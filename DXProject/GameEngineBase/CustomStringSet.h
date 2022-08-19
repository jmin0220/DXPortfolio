#pragma once

#define ANIMATION_FRAME_DELAY 0.08f

// �÷��̾� ����Ű
#define PLAYER_KEY_LEFT "PlayerLeft"
#define PLAYER_KEY_RIGHT "PlayerRight"
#define PLAYER_KEY_JUMP "PlayerJump"
#define PLAYER_KEY_UP "PlayerUp"
#define PLAYER_KEY_DOWN "PlayerDown"

#define PLAYER_KEY_DEBUG_UP "PlayerDebugUp"
#define PLAYER_KEY_DEBUG_DOWN "PlayerDebugDown"

#define Player_KEY_SKILL1 "PlayerSkill1"
#define Player_KEY_SKILL2 "PlayerSkill2"
#define Player_KEY_SKILL3 "PlayerSkill3"
#define Player_KEY_SKILL4 "PlayerSkill4"

// �÷��̾� ��ġ��
#define Player_MOVE_SPEED 100.0f
#define Player_JUMP_SPEED -150.0f

// �÷��̾� FSM
#define PLAYER_STATE_IDLE "Idle"
#define PLAYER_STATE_MOVE "Move"
#define PLAYER_STATE_SKILL1 "Skill1"
#define PLAYER_STATE_SKILL2 "Skill2"
#define PLAYER_STATE_SKILL3 "Skill3"
#define PLAYER_STATE_SKILL4 "Skill4"
#define PLAYER_STATE_CLIMB "Climb"
#define PLAYER_STATE_DEATH "Death"

// ���� FSM
#define MONSTER_FSM_SPAWN "MonsterSpawn"
#define MONSTER_FSM_IDLE "MonsterIdle"
#define MONSTER_FSM_MOVE "MonsterMove"
#define MONSTER_FSM_CHASE "MonsterChase"
#define MONSTER_FSM_ATTACK "MonsterAttack"
#define MONSTER_FSM_DEATH "MonsterDeath"
#define MONSTER_FSM_HITTED "MonsterHitted"

// �÷��̾� �ִϸ��̼�
#define PLAYER_ANIM_IDLE "PlayerIdle"
#define PLAYER_ANIM_SKILL1 "PlayerSkill1"
#define PLAYER_ANIM_SKILL2 "PlayerSkill2"
#define PLAYER_ANIM_SKILL3 "PlayerSkill3"
#define PLAYER_ANIM_SKILL4 "PlayerSkill4"
#define PLAYER_ANIM_WALK "PlayerWalk"
#define PLAYER_ANIM_JUMP "PlayerJump"
#define PLAYER_ANIM_CLIMB "PlayerClimb"
#define PLAYER_ANIM_DEATH "PlayerDeath"

#define COMMANDO_ANIM_SELECT "CommandoSelect"
#define BANDIT_ANIM_SELECT "BanditSelect"

// ���� �ִϸ��̼�
// Lemurian
#define LEMURIAN_ANIM_IDLE "LemurianIdle"
#define LEMURIAN_ANIM_JUMP "LemurianJump"
#define LEMURIAN_ANIM_SHOOT "LemurianShoot"
#define LEMURIAN_ANIM_SPAWN "LemurianSpawn"
#define LEMURIAN_ANIM_WALK "LemurianWalk"
#define LEMURIAN_ANIM_DEATH "LemurianDeath"
#define LEMURIAN_ANIM_HITTED "LemurianHitted"


// ĳ���ͺ� Ư�� �ִϸ��̼�
#define PLAYER_ANIM_COMMANDO_SKILL4_1 "CommandoSkill4_1"
#define PLAYER_ANIM_COMMANDO_SKILL4_2 "CommandoSkill4_2"

#define PLAYER_ANIM_BANDIT_SKILL2_EXPLOSION "BanditSkill2Explosion"

// ����Ʈ �ִϸ��̼�
#define EFFECT_ANIM_NORMAL_SPARK "NormalSpark"

// ���丮
#define DIR_RESOURCE "Resources"
#define DIR_TEXTURE "Texture"
#define DIR_CHARACTERS "Characters"
#define DIR_MONSTER "Monster"
#define DIR_STAGE "Stage"
#define DIR_INTERFACE "Interface"
#define DIR_EFFECT "Effect"
#define DIR_OBJECT "Object"
#define DIR_FONT "Font"

// ����
#define LEVEL_TITLE "Title"
#define LEVEL_END "End"
#define LEVEL_SELECT "CharacterSelect"
#define LEVEL_STAGE1 "Stage1"

// �ؽ���
// ���
#define TEX_TITLE_BG "Title.png"
#define TEX_STAGE_ONE "stage1.png"
#define TEX_STAGE_ONE_COLLISION "stage1Collision.png"
#define TEX_BG_PURPLE_STARS "PurpleStars1.png"
// ����â
#define TEX_SELECTED_COMMANDO "CommandoSelected.png"
#define TEX_SELECTED_BANDIT "BanditSelected.png"
// Player
// Commando
#define TEX_PLAYER_ANIM_COMMANDO_IDLE "CommandoIdle"
#define TEX_PLAYER_ANIM_COMMANDO_SKILL1 "CommandoSkill1"
#define TEX_PLAYER_ANIM_COMMANDO_SKILL2 "CommandoSkill2"
#define TEX_PLAYER_ANIM_COMMANDO_SKILL3 "CommandoSkill3"
#define TEX_PLAYER_ANIM_COMMANDO_SKILL4_1 "CommandoSkill4_1"
#define TEX_PLAYER_ANIM_COMMANDO_SKILL4_2 "CommandoSkill4_2"
#define TEX_PLAYER_ANIM_COMMANDO_WALK "CommandoWalk"
#define TEX_PLAYER_ANIM_COMMANDO_JUMP "CommandoJump"
#define TEX_PLAYER_ANIM_COMMANDO_CLIMB "CommandoClimb"
#define TEX_PLAYER_ANIM_COMMANDO_DEATH "CommandoDeath"
#define TEX_PLAYER_ANIM_COMMANDO_SELECT "CommandoSelect"
// Bandit
#define TEX_PLAYER_ANIM_BANDIT_IDLE "BanditIdle"
#define TEX_PLAYER_ANIM_BANDIT_SKILL1 "BanditSkill1"
#define TEX_PLAYER_ANIM_BANDIT_SKILL2 "BanditSkill2"
#define TEX_PLAYER_ANIM_BANDIT_SKILL2_EXPLOSION "BanditSkill2Explosion"
#define TEX_PLAYER_ANIM_BANDIT_SKILL3 "BanditSkill3"
#define TEX_PLAYER_ANIM_BANDIT_SKILL4 "BanditSkill4"
#define TEX_PLAYER_ANIM_BANDIT_WALK "BanditWalk"
#define TEX_PLAYER_ANIM_BANDIT_JUMP "BanditJump"
#define TEX_PLAYER_ANIM_BANDIT_CLIMB "BanditClimb"
#define TEX_PLAYER_ANIM_BANDIT_DEATH "BanditDeath"
#define TEX_PLAYER_ANIM_BANDIT_SELECT "BanditSelect"

// Monster
// Lemurian
#define TEX_MONSTER_ANIM_LEMURIAN_IDLE "LemurianIdle"
#define TEX_MONSTER_ANIM_LEMURIAN_JUMP "LemurianJump"
#define TEX_MONSTER_ANIM_LEMURIAN_SHOOT "LemurianShoot"
#define TEX_MONSTER_ANIM_LEMURIAN_SPAWN "LemurianSpawn"
#define TEX_MONSTER_ANIM_LEMURIAN_WALK "LemurianWalk"
#define TEX_MONSTER_ANIM_LEMURIAN_DEATH "LumurianDeath"
#define TEX_MONSTER_ANIM_LEMURIAN_HITTED "LemurianHitted"

// �������̽�
#define TEX_INTERFACE_HUD "HUD.png"
#define TEX_INTERFACE_DIFFICULTY_HUD "DifficultyHUD.png"
#define TEX_INTERFACE_DIFFICULTY_TIMER "DifficultyTimer.png"
#define TEX_INTERFACE_TUTORIAL "Tutorial"
#define TEX_INTERFACE_TUTORIAL_USE "TutorialUse"
#define TEX_INTERFACE_MONEY_INTERFACE "sMoney_0.png"

// ��ų ������
#define TEX_SKILLICON_COMMANDO_0 "sGManSkills_0.png"
#define TEX_SKILLICON_COMMANDO_1 "sGManSkills_1.png"
#define TEX_SKILLICON_COMMANDO_2 "sGManSkills_2.png"
#define TEX_SKILLICON_COMMANDO_3 "sGManSkills_3.png"

#define TEX_SKILLICON_BANDIT_0 "sCowboySkills_0.png"
#define TEX_SKILLICON_BANDIT_1 "sCowboySkills_1.png"
#define TEX_SKILLICON_BANDIT_2 "sCowboySkills_2.png"
#define TEX_SKILLICON_BANDIT_3 "sCowboySkills_3.png"

// ����Ʈ
#define TEX_EFFECT_NORMAL_SPARK "NormalSpark"
// ����ġ
#define TEX_EFFECT_NORMAL_EXP "ExpNormal"
#define TEX_EFFECT_SMALL_EXP "ExpSmall"
#define TEX_EFFECT_DEATH_EXP "ExpDeath"
// ���
#define TEX_EFFECT_SMALL_GOLD "CoinSmall"
#define TEX_EFFECT_COIN "CoinNormal"

// ���� ����Ű
#define CHANGE_LEVEL_CHRACTER_SELECT "ChangeLevelToCharacterSelect"
#define CHANGE_LECEL_STAGE1 "ChangeLevelToStage1"

// ��Ʈ
#define FONT_RISKOFRAIN "riskofrainfont"