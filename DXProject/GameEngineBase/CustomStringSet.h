#pragma once
// 플레이어 조작키
#define PLAYER_KEY_LEFT "PlayerLeft"
#define PLAYER_KEY_RIGHT "PlayerRight"
#define PLAYER_KEY_SHOOT "PlayerShoot"
#define PLAYER_KEY_JUMP "PlayerJump"
#define PLAYER_KEY_UP "PlayerUp"
#define PLAYER_KEY_DOWN "PlayerDown"

#define PLAYER_KEY_DEBUG_UP "PlayerDebugUp"
#define PLAYER_KEY_DEBUG_DOWN "PlayerDebugDown"

#define Player_KEY_SKILL1 "PlayerSkill1"
#define Player_KEY_SKILL2 "PlayerSkill2"
#define Player_KEY_SKILL3 "PlayerSkill3"

// 플레이어 FSM
#define PLAYER_STATE_IDLE "Idle"
#define PLAYER_STATE_MOVE "Move"
#define PLAYER_STATE_SHOOT "Shoot"
#define PLAYER_STATE_SKILL1 "Skill1"
#define PLAYER_STATE_SKILL2 "Skill2"
#define PLAYER_STATE_SKILL3 "Skill3"
#define PLAYER_STATE_SKILL4 "Skill4"
#define PLAYER_STATE_CLIMB "Climb"
#define PLAYER_STATE_DEATH "Death"

// 플레이어 애니메이션
#define PLAYER_ANIM_IDLE "PlayerIdle"
#define PLAYER_ANIM_SHOOT "PlayerShoot1"
#define PLAYER_ANIM_WALK "PlayerWalk"
#define PLAYER_ANIM_JUMP "PlayerJump"
#define PLAYER_ANIM_CLIMB "PlayerClimb"
#define PLAYER_ANIM_DEATH "PlayerDeath"

#define COMMANDO_ANIM_SELECT "CommandoSelect"
#define BANDIT_ANIM_SELECT "BanditSelect"

// 디렉토리
#define DIR_RESOURCE "Resources"
#define DIR_TEXTURE "Texture"
#define DIR_CHARACTERS "Characters"
#define DIR_STAGE "Stage"
#define DIR_INTERFACE "Interface"

// 레벨
#define LEVEL_TITLE "Title"
#define LEVEL_END "End"
#define LEVEL_SELECT "CharacterSelect"
#define LEVEL_STAGE1 "Stage1"

// 텍스쳐
#define TEX_TITLE_BG "Title.png"
#define TEX_STAGE_ONE "stage1.png"
#define TEX_STAGE_ONE_COLLISION "stage1Collision.png"

#define TEX_SELECTED_COMMANDO "CommandoSelected.png"
#define TEX_SELECTED_BANDIT "BanditSelected.png"

#define TEX_PLAYER_ANIM_COMMANDO_IDLE "CommandoIdle"
#define TEX_PLAYER_ANIM_COMMANDO_SHOOT "CommandoShoot1"
#define TEX_PLAYER_ANIM_COMMANDO_WALK "CommandoWalk"
#define TEX_PLAYER_ANIM_COMMANDO_JUMP "CommandoJump"
#define TEX_PLAYER_ANIM_COMMANDO_CLIMB "CommandoClimb"
#define TEX_PLAYER_ANIM_COMMANDO_DEATH "CommandoDeath"
#define TEX_PLAYER_ANIM_COMMANDO_SELECT "CommandoSelect"

#define TEX_PLAYER_ANIM_BANDIT_IDLE "BanditIdle"
#define TEX_PLAYER_ANIM_BANDIT_SHOOT "BanditShoot1"
#define TEX_PLAYER_ANIM_BANDIT_WALK "BanditWalk"
#define TEX_PLAYER_ANIM_BANDIT_JUMP "BanditJump"
#define TEX_PLAYER_ANIM_BANDIT_CLIMB "BanditClimb"
#define TEX_PLAYER_ANIM_BANDIT_DEATH "BanditDeath"
#define TEX_PLAYER_ANIM_BANDIT_SELECT "BanditSelect"

#define TEX_INTERFACE_HUD "HUD.png"

// 스킬 아이콘
#define TEX_SKILLICON_COMMANDO_0 "sGManSkills_0.png"
#define TEX_SKILLICON_COMMANDO_1 "sGManSkills_1.png"
#define TEX_SKILLICON_COMMANDO_2 "sGManSkills_2.png"
#define TEX_SKILLICON_COMMANDO_3 "sGManSkills_3.png"

#define TEX_SKILLICON_BANDIT_0 "sCowboySkills_0.png"
#define TEX_SKILLICON_BANDIT_1 "sCowboySkills_1.png"
#define TEX_SKILLICON_BANDIT_2 "sCowboySkills_2.png"
#define TEX_SKILLICON_BANDIT_3 "sCowboySkills_3.png"

// 레벨 조작키
#define CHANGE_LEVEL_CHRACTER_SELECT "ChangeLevelToCharacterSelect"
#define CHANGE_LECEL_STAGE1 "ChangeLevelToStage1"