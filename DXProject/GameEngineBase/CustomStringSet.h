#pragma once

#define ANIMATION_FRAME_DELAY 0.08f
#define BOUNCER_JUMP_SPEED -400.0f
#define BOSS_HP_MAX_SCALE 1576.0f

// 플레이어 조작키
#define PLAYER_KEY_LEFT "PlayerLeft"
#define PLAYER_KEY_RIGHT "PlayerRight"
#define PLAYER_KEY_JUMP "PlayerJump"
#define PLAYER_KEY_UP "PlayerUp"
#define PLAYER_KEY_DOWN "PlayerDown"
#define Player_KEY_INTERACTIVE "PlayerInteravtive"

#define PLAYER_KEY_DEBUG_UP "PlayerDebugUp"
#define PLAYER_KEY_DEBUG_DOWN "PlayerDebugDown"

#define Player_KEY_SKILL1 "PlayerSkill1"
#define Player_KEY_SKILL2 "PlayerSkill2"
#define Player_KEY_SKILL3 "PlayerSkill3"
#define Player_KEY_SKILL4 "PlayerSkill4"

#define Player_KEY_USE_ITEMS "UseItems"

// 플레이어 수치값
#define Player_MOVE_SPEED 150.0f
#define Player_JUMP_SPEED -210.0f

// 플레이어 FSM
#define PLAYER_STATE_IDLE "Idle"
#define PLAYER_STATE_MOVE "Move"
#define PLAYER_STATE_SKILL1 "Skill1"
#define PLAYER_STATE_SKILL2 "Skill2"
#define PLAYER_STATE_SKILL3 "Skill3"
#define PLAYER_STATE_SKILL4 "Skill4"
#define PLAYER_STATE_CLIMB "Climb"
#define PLAYER_STATE_DEATH "Death"

// 몬스터 FSM
#define MONSTER_FSM_SPAWN "MonsterSpawn"
#define MONSTER_FSM_IDLE "MonsterIdle"
#define MONSTER_FSM_MOVE "MonsterMove"
#define MONSTER_FSM_CHASE "MonsterChase"
#define MONSTER_FSM_ATTACK "MonsterAttack"
#define MONSTER_FSM_ATTACK2 "MonsterAttack2"
#define MONSTER_FSM_DEATH "MonsterDeath"
#define MONSTER_FSM_HITTED "MonsterHitted"

// 드론 FSM
#define DRONE_FSM_IDLE "DroneIdle"
#define DRONE_FSM_ACTION "DroneAction"

// 플레이어 애니메이션
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

// 몬스터 애니메이션
// Lemurian
#define LEMURIAN_ANIM_IDLE "LemurianIdle"
#define LEMURIAN_ANIM_JUMP "LemurianJump"
#define LEMURIAN_ANIM_SHOOT "LemurianShoot"
#define LEMURIAN_ANIM_SPAWN "LemurianSpawn"
#define LEMURIAN_ANIM_WALK "LemurianWalk"
#define LEMURIAN_ANIM_DEATH "LemurianDeath"
#define LEMURIAN_ANIM_HITTED "LemurianHitted"

// Colossus
#define COLOSSUS_ANIM_IDLE "ColossusIdle"
#define COLOSSUS_ANIM_DEATH "ColossusDeath"
#define COLOSSUS_ANIM_SHOOT1 "ColossusShoot1"
#define COLOSSUS_ANIM_SHOOT2 "ColossusShoot2"
#define COLOSSUS_ANIM_WALK "ColossusWalk"

// MagmaWorm
#define MAGMAWORM_ANIM_HEAD "WormHead"
#define MAGMAWORM_ANIM_HEAD_DEAD "WormHeadDead"
#define MAGMAWORM_ANIM_BODY "WormBody"
#define MAGMAWORM_ANIM_BODY_DEAD "WormBodyDead"
#define MAGMAWORM_ANIM_WARNING "WormWarning"

// Child
#define CHILD_ANIM_IDLE   "ChildIdle"
#define CHILD_ANIM_SHOOT  "ChildShoot"
#define CHILD_ANIM_SPAWN  "ChildSpawn"
#define CHILD_ANIM_WALK   "ChildWalk"
#define CHILD_ANIM_DEATH  "ChildDeath"
#define CHILD_ANIM_HITTED "ChildHitted"

// Parent
#define PARENT_ANIM_IDLE   "ParentIdle"
#define PARENT_ANIM_SHOOT  "ParentShoot"
#define PARENT_ANIM_SPAWN  "ParentSpawn"
#define PARENT_ANIM_WALK   "ParentWalk"
#define PARENT_ANIM_DEATH  "ParentDeath"

// RockGolem
#define ROCKGOLEM_ANIM_IDLE   "RockGolemIdle"
#define ROCKGOLEM_ANIM_SHOOT  "RockGolemShoot"
#define ROCKGOLEM_ANIM_SPAWN  "RockGolemSpawn"
#define ROCKGOLEM_ANIM_WALK   "RockGolemWalk"
#define ROCKGOLEM_ANIM_DEATH  "RockGolemDeath"

// Crab
#define CRAB_ANIM_IDLE   "CrabIdle"
#define CRAB_ANIM_SHOOT  "CrabShoot"
#define CRAB_ANIM_SPAWN  "CrabSpawn"
#define CRAB_ANIM_WALK   "CrabWalk"
#define CRAB_ANIM_DEATH  "CrabDeath"

// Wisp
#define WISP_ANIM_IDLE   "WispIdle"
#define WISP_ANIM_SHOOT  "WispShoot"
#define WISP_ANIM_SPAWN  "WispSpawn"
#define WISP_ANIM_DEATH  "WispDeath"
#define WISP_ANIM_SPARK  "WispSpark"


// 캐릭터별 특수 애니메이션
#define PLAYER_ANIM_COMMANDO_SKILL4_1 "CommandoSkill4_1"
#define PLAYER_ANIM_COMMANDO_SKILL4_2 "CommandoSkill4_2"

#define PLAYER_ANIM_BANDIT_SKILL2_GRENADE "BanditSkill2Grenade"
#define PLAYER_ANIM_BANDIT_SKILL2_EXPLOSION "BanditSkill2Explosion"

// 이펙트 애니메이션
#define EFFECT_ANIM_NORMAL_SPARK "NormalSpark"

// 디렉토리
#define DIR_RESOURCE "Resources"
#define DIR_TEXTURE "Texture"
#define DIR_SOUND "Sound"
#define DIR_CHARACTERS "Characters"
#define DIR_MONSTER "Monster"
#define DIR_STAGE "Stage"
#define DIR_INTERFACE "Interface"
#define DIR_DRONE "Drone"
#define DIR_EFFECT "Effect"
#define DIR_OBJECT "Object"
#define DIR_FONT "Font"
#define DIR_ITEM "Item"
#define DIR_ITEMICON "ItemIcon"
#define DIR_ITEMUSEICON "ItemUseIcon"
#define DIR_ITEMANIMATION "ItemAnimation"

// 레벨
#define LEVEL_TITLE "Title"
#define LEVEL_END "End"
#define LEVEL_SELECT "CharacterSelect"
#define LEVEL_STAGE1 "Stage1"
#define LEVEL_STAGE2 "Stage2"

// 텍스쳐
// 배경
#define TEX_TITLE_BG "Title.png"
#define TEX_STAGE_ONE "stage1.png"
#define TEX_STAGE_ONE_COLLISION "stage1Collision.png"
#define TEX_STAGE_TWO "stage2.png"
#define TEX_STAGE_TWO_COLLISION "stage2Collision.png"
#define TEX_BG_PURPLE_STARS "PurpleStars1.png"
#define TEX_BG_BLUE_STARTS "bStars1_2_0.png"
// 선택창
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

// Drone
#define DRONE_ATTACK_IDLE  "AttackDroneIdle"
#define DRONE_ATTACK_ITEM  "AttackDroneItem"
#define DRONE_ATTACK_SHOOT "AttackDroneShoot"

#define DRONE_MISSILE_IDLE  "MissileDroneIdle"
#define DRONE_MISSILE_ITEM  "MissileDroneItem"
#define DRONE_MISSILE_SHOOT "MissileDroneShoot"


// 인터페이스
#define TEX_INTERFACE_HUD "HUD.png"
#define TEX_INTERFACE_DIFFICULTY_HUD "DifficultyHUD.png"
#define TEX_INTERFACE_DIFFICULTY_TIMER "DifficultyTimer.png"
#define TEX_INTERFACE_DIFFUCULTY_ICON "DifficultyIcon"
#define TEX_INTERFACE_TUTORIAL "Tutorial"
#define TEX_INTERFACE_TUTORIAL_USE "TutorialUse"
#define TEX_INTERFACE_LEVELUP_START "LevelUpStart"
#define TEX_INTERFACE_LEVELUP_END "LevelUpEnd"
#define TEX_INTERFACE_MONEY_INTERFACE "sMoney_0.png"
#define TEX_INTERFACE_BOSS_HPBAR "BossHpBar.png"

// 폰트
#define FontName "sDamage"

#define TEX_FONT_NORMAL_0 "sDamage_0.png"
#define TEX_FONT_NORMAL_1 "sDamage_1.png"
#define TEX_FONT_NORMAL_2 "sDamage_2.png"
#define TEX_FONT_NORMAL_3 "sDamage_3.png"
#define TEX_FONT_NORMAL_4 "sDamage_4.png"
#define TEX_FONT_NORMAL_5 "sDamage_5.png"
#define TEX_FONT_NORMAL_6 "sDamage_6.png"
#define TEX_FONT_NORMAL_7 "sDamage_7.png"
#define TEX_FONT_NORMAL_8 "sDamage_8.png"
#define TEX_FONT_NORMAL_9 "sDamage_9.png"
#define TEX_FONT_NORMAL_10 "sDamage_10.png"
#define TEX_FONT_NORMAL_11 "sDamage_11.png"
#define TEX_FONT_NORMAL_12 "sDamage_12.png"

#define TEX_FONT_LARGE_0 "sDamageLarge_0.png"
#define TEX_FONT_LARGE_1 "sDamageLarge_1.png"
#define TEX_FONT_LARGE_2 "sDamageLarge_2.png"
#define TEX_FONT_LARGE_3 "sDamageLarge_3.png"
#define TEX_FONT_LARGE_4 "sDamageLarge_4.png"
#define TEX_FONT_LARGE_5 "sDamageLarge_5.png"
#define TEX_FONT_LARGE_6 "sDamageLarge_6.png"
#define TEX_FONT_LARGE_7 "sDamageLarge_7.png"
#define TEX_FONT_LARGE_8 "sDamageLarge_8.png"
#define TEX_FONT_LARGE_9 "sDamageLarge_9.png"

#define TEX_FONT_CRIT_0 "sDamageCrit_0.png"
#define TEX_FONT_CRIT_1 "sDamageCrit_1.png"
#define TEX_FONT_CRIT_2 "sDamageCrit_2.png"
#define TEX_FONT_CRIT_3 "sDamageCrit_3.png"
#define TEX_FONT_CRIT_4 "sDamageCrit_4.png"
#define TEX_FONT_CRIT_5 "sDamageCrit_5.png"
#define TEX_FONT_CRIT_6 "sDamageCrit_6.png"
#define TEX_FONT_CRIT_7 "sDamageCrit_7.png"
#define TEX_FONT_CRIT_8 "sDamageCrit_8.png"
#define TEX_FONT_CRIT_9 "sDamageCrit_9.png"
#define TEX_FONT_CRIT_10 "sDamageCrit_10.png"

// 스킬 아이콘
#define TEX_SKILLICON_COMMANDO_0 "sGManSkills_0.png"
#define TEX_SKILLICON_COMMANDO_1 "sGManSkills_1.png"
#define TEX_SKILLICON_COMMANDO_2 "sGManSkills_2.png"
#define TEX_SKILLICON_COMMANDO_3 "sGManSkills_3.png"

#define TEX_SKILLICON_BANDIT_0 "sCowboySkills_0.png"
#define TEX_SKILLICON_BANDIT_1 "sCowboySkills_1.png"
#define TEX_SKILLICON_BANDIT_2 "sCowboySkills_2.png"
#define TEX_SKILLICON_BANDIT_3 "sCowboySkills_3.png"

// 이펙트
#define TEX_EFFECT_NORMAL_SPARK "NormalSpark"
#define TEX_EFFECT_MISSILE "Missile"
#define TEX_EFFECT_MISSILE_EXPLOSION "MissileExplosion"
#define TEX_EFFECT_BARBEDWIRE_THORN "Thorns"
// 경험치
#define TEX_EFFECT_NORMAL_EXP "ExpNormal"
#define TEX_EFFECT_SMALL_EXP "ExpSmall"
#define TEX_EFFECT_DEATH_EXP "ExpDeath"
// 골드
#define TEX_EFFECT_SMALL_GOLD "CoinSmall"
#define TEX_EFFECT_COIN "CoinNormal"

// 오브젝트
#define TEX_OBJECT_BOUNCER "Bouncer"
#define TEX_OBJECT_TELEPORTAL "TelePortal"

// 상자
#define TEX_OBJECT_CHEST_NORMAL_IDLE "CheckNormalIdle"
#define TEX_OBJECT_CHEST_NORMAL_OPEN "ChestNormalOpen"
#define TEX_OBJECT_CHEST_BIG_IDLE "ChestBigIdle"
#define TEX_OBJECT_CHEST_BIG_OPEN "ChestBigOpen"
#define TEX_OBJECT_CHEST_LONG_IDLE "ChestLongIdle"
#define TEX_OBJECT_CHEST_LONG_OPEN "ChestLongOpen"

// 레벨 조작키
#define CHANGE_LEVEL_CHRACTER_SELECT "ChangeLevelToCharacterSelect"
#define CHANGE_LEVEL_STAGE1 "ChangeLevelToStage1"

// 폰트
#define FONT_RISKOFRAIN "riskofrainfont"

// 아이템
#define ITEM_NAME_BARBEDWIRE "BarbedWire.png"
#define ITEM_NAME_MEATNUGGET "MeatNugget.png"
#define ITEM_NAME_WARBANNER "Warbanner.png"
#define ITEM_NAME_REDWHIP "RedWhip.png"
#define ITEM_NAME_HARVESTERSCYTHE "HarvesterScythe.png"
#define ITEM_NAME_SAWMERANG "sSawmerang_0.png"
#define ITEM_NAME_SAWMERAN_INVENTORY "sSawmerang_1.png"
#define ITEM_NAME_AtGMISSILE_MK1 "AtGMissileMk1.png"
#define ITEM_NAME_AtGMISSILE_MK2 "AtGMissileMk2.png"
#define ITEM_NAME_MISSILE_LAUNCHER "sMissileBox_0.png"
#define ITEM_NAME_MISSILE_LAUNCHER_INVENTORY "sMissileBox_1.png"


// 아이템 애니메이션
#define ITEM_ANIMATION_MEATNUGGET_IDLE "MeatNuggetIdle"
#define ITEM_ANIMATION_MEATNUGGET_JUMP "MeatNuggetJump"
#define ITEM_ANIMATION_WARBANNER_FLAG "WarbannerFlag"
#define ITEM_ANIMATION_WARBANNER_CIRCLE "WarbannerCircle"
#define ITEM_ANIMATION_THORN_EFFECT "ThornEffect"
#define ITEM_ANIMATION_SAWMERANG_EFFECT "SawmerangEffect"