#ifndef WEAPON_VARIANT_BASIC_CONSTANT_DEFABILTYPE_H
#define WEAPON_VARIANT_BASIC_CONSTANT_DEFABILTYPE_H

//_C_ -> 최종
//_E_ -> 추가분(즉 기본값에+ 해줄 값들)
//_R_ -> 천분율값(기본값에 천분율로 더해줘야 할 값)
//...(없음) -> 기본값.

typedef enum eAbilType
{
	AT_NONE=0, 
// Unit Ability
	AT_LEVEL	= 1,
	AT_CLASS	= 2,
	AT_GENDER	= 3,
	AT_RACE		= 4,
	AT_FIVE_ELEMENT_TYPE_AT_BODY= 5,
	AT_SUCCESSRATE = 6,					// 성공확률 보정 어빌
	AT_CARD_BGNDNO	= 7,			// 캐릭터 카드 배경 이미지 리소스 번호
	AT_BATTLE_LEVEL	= 8,			// 전투레벨
	AT_STR_BASIC = 9,		// Class DEF 값
	AT_STR_ADD = 10,		// 추가된 STR
	AT_STR_ADD_LIMIT = 11,
	AT_INT_BASIC = 12,		// Class DEF 값
	AT_INT_ADD = 13,		// 추가된 STR
	AT_INT_ADD_LIMIT = 14,
	AT_CON_BASIC = 15,		// Class DEF 값
	AT_CON_ADD = 16,		// 추가된 STR
	AT_CON_ADD_LIMIT = 17,
	AT_DEX_BASIC = 18,		// Class DEF 값
	AT_DEX_ADD = 19,		// 추가된 STR
	AT_DEX_ADD_LIMIT = 20,
	AT_STATUS_BONUS			= 21,		// Status Bonus
	AT_ALL_STATUS			= 22,

	AT_CLASS_01				= 31,
	AT_CLASS_10				= 40,

	AT_LEVEL_RANK			= 49,
	AT_MILEAGE_TOTAL_CASH	= 50,
	AT_MILEAGE_100			= 51,
	AT_MILEAGE_1000			= 52,
	AT_BONUS_EXP_RATE_INVILLAGE = 53,		// (Ground abil) 마을에 있으면 얻게되는 휴식 경험치(현재 레벨 경험치에 대한 %) (백만분율 값)
	AT_BONUS_EXP_INTERVAL_INVILLAGE	= 54,	// (Ground abil) 마을에 있으면 얻게되는 휴식 경험치의 단l위시간(초) (AT_BONUS_EXP_INTERVAL_INVILLAGE second 마다 AT_BONUS_EXP_RATE_INVILLAGE 만큼 휴식경험치를 얻음)
	AT_BONUS_EXP_RATE_OFFLINE		= 55,	// (Ground abil) 마을에서 접속 끊으면 얻게되는 휴식 경험치 (백만분율 값)
	AT_BONUS_EXP_INTERVAL_OFFLINE	= 56,	// (Ground abil) 마을에서 접속 끊으면 얻게되는 휴식 경험치의 단위 시간(분)

	AT_EVENT_ITEM_CONTAINER = 57,// 이벤트 기간에 드랍될 아이템 컨테이너 번호

	AT_MAP_GROUP_NAME_NO	= 58,// 맵 그룹 네이밍 스트링 번호 ( 예) 미션1, 미션2, 미션3 -> 대표미션맵 )
	AT_EFFECT_GROUP_NO		= 59,	// Effect 중복되는것 방지 하기 위한 Group number
	AT_SUCCESSIONAL_DEATH_COUNT		= 60,	// 연속해서 죽은 카운트 (배틀스퀘어 에서만 카운트 되고 있음)
	AT_CHAT_BROADCAST_TYPE	= 61,	// 채팅메시지가 broadcasting 되는 방식 (0=zone에 한정, 1=ground 전체)

	AT_GMCMD_LIMIT_HP		= 70,	// 지정한 HP보다 밑으로 떨어지지 않도록

	AT_HPMP_BROADCAST		= 100,	// 이 어빌이 있으면 HP와 MP를 그라운드에 브로드캐스트 해주어야 한다.
	AT_HP					= 101,
	//AT_DP					= 102,	// DefencePoint Shiled
	AT_CP					= 103,	// ClassPoint(CP)
	AT_MP					= 105,
	AT_REFRESH_ABIL_INV		= 106,	// Abil이 아니고 Abil이 다시 계산되어야 한다고 알리는 값으로 사용된다.(Inven 어빌을 기준으로)
	AT_EVENT_LEVELUP		= 107,	// Abil아 아니고 Levelup이 되었으니 Abil을 다시 계산하라고 알리는 용도
	AT_HIT_COUNT			= 108,	// 실제로 공격한 회수 (도둑:DoubleAttack에 의해서 Hit수가 가변적으로 변경될 수가 있다.)
	AT_HP_RESERVED			= 109,	// 부활할때의 채워지게 될 HP양
	AT_MP_RESERVED			= 110,	// 부활할때의 채워지게 될 MP양
	AT_REVIVED_BY_OTHER		= 111,	// 다른 사람에 의해 부활되었는가?
	AT_COOLTIME_TYPE		= 112,	// Item CoolTime (EItemCoolTimeType value)
	AT_MUTE					= 113,	// 채팅금지
	AT_RECENT				= 114,	// 리센트 맵
	AT_LAST_VILLAGE			= 115,	// 마지막 마을
	//AT_HP_RECOVERY_ADD		= 116,	// Auto HP회복시 추가되는 절대값
	//AT_MP_RECOVERY_ADD		= 117,	// Auto HP회복시 추가되는 절대값
	AT_USE_ITEM_GROUP		= 118,	// 아이템 사용 그릅(쿨타임 적용 그릅)
	//AT_HP_RECOVERY_ADD_RATE = 119,	// AT_HP_RECOVERY_ADD 값에 Multiflier 곱해진 값
	//AT_MP_RECOVERY_ADD_RATE = 120,	// AT_MP_RECOVERY_ADD 값에 Multiflier 곱해진 값

	AT_DEC_TARGETDODGE_ABS	= 122,	// Target의 회피율 감소(절대값 감소 '500'이 값이라면 회피율 만분율에서 500을 차감)
	AT_DEC_TARGETDODGE_RATE = 123,	// Target의 회피율 감소(Rate 감소 '1000'이 값이라면 회피율 만분율에서 10%감소)
	AT_OFFENCE_ENCHANT_LEVEL = 124,	// 플레이어 무기 인챈트 레벨(무기 인첸트 레벨 그대로 사용)
	AT_DEFENCE_ENCHANT_LEVEL= 125,	// 플레이어 방어구 인챈트 레벨(공식으로 계산)

	AT_BONUS_EXP_RATE_EFFECT= 126,	// 이팩트에서 얻게될 휴식 경험치 

	AT_BONUS_EXP_LEVELLIMIT	= 127,	// 해당 레벨 이상은 경험치를 획득 불가능

	AT_MAX_EVADERATE_VALUE		= 140,  //최대 회피성공수치
	AT_MAX_BLOCKRATE_VALUE		= 141,	//최대 블록 성공수치
	AT_CRITICALRATE_VALUE		= 142,	//최대크리티컬성공수치
	AT_CRITICAL_DAMAGE_VALUE    = 143,	//최대크리티컬데미지
	AT_HIT_VALUE_CONSTANT		= 144,	//명중수치상수
	AT_EVADE_VALUE_CONSTANT		= 145,	//회피수치상수
	AT_CRITICALRATE_VALUE_CONSTANT = 146,	//크리티컬성공수치상수
		
	AT_ATTR_ATTACK			= 201,
	AT_ATTR_DEFENCE			= 202,
	AT_LOCK_HIDDEN_ATTACK	= 203,	// Hidden상태인데 Attack 하더라도 Hidden 상태가 풀리지 않는다.
	AT_UNLOCK_HIDDEN_MOVE	= 204,	// Hidden상태인데 Move 하면 Hidden상태가 풀린다.
	AT_GOALPOS_SET_TIME		= 205,	// AI : GoalPos() 값을 주기적으로 Update 시켜줘야 할 경우가 있는데 이것을 위해 GoalPos 변경된 시간(DWORD로 타입변경 필요)
	AT_BOLDNESS_RATE		= 206,	// AI : 얼마나 대담한가..즉 Target을 발견했을 때 공격하려 갈 확률(기본 60%)
	AT_PARENT_ITEM_NO		= 207,	// Item : Parent Item No (기능성 아이템에서 효과가 중복되지 않도록 하기 위해서 검사하는 ItemNo)
	AT_DURATION_TIME		= 208,	// Item : 기능 아이템이 효과를 유지하는 시간
	AT_DURATION_TIME_TYPE	= 209,	// Item : AT_DURATION_TIME 의 종류 (E_TIME_ELAPSED_TYPE)
	AT_SKILL_FILTER_TYPE	= 210,	// Effect : 스킬 사용을 제한 하기 위한 Filter type (ESkillFilterType)
	AT_FILTER_EXCEPT_01		= 211,	// Effect : Skill Filter 에서 예외항목 리스트
// 예약 : AT_FILTER_EXCEPT_01 - AT_FILTER_EXCEPT_10
	AT_NEED_EFFECT_01		= 221,	// Skill : 스킬을 사용하기 위해서 필요한 Effect
// 예약 : AT_NEED_EFFECT_01 - AT_NEED_EFFECT_10
	AT_NEED_SKILL_01		= 231,	// Skill : 스킬을 배우기 위해 미리 배워야 하는 스킬ID
// 예약 : AT_NEED_SKILL_01 - AT_NEED_SKILL_10
	AT_NEED_USE_SKILL_01	= 241,	// Skill : 스킬을 사용하기 전에 사용되어야 하는 스킬
	AT_CHILD_CAST_SKILL_NO = 250,	// Fire와 Cast로 나누어진 스킬일 경우 Cast와 연결되는 Fire 스킬의 No을 입력한다.(실제 사용되는 스킬 번호) - UI 툴팁에서 사용
	AT_PARENT_CAST_SKILL_NO = 251,	// Fire와 Cast로 나누어진 스킬일 경우 Fire와 연결되는 Cast 스킬의 No을 입력한다.
	AT_I_PHY_DEFENCE_ADD_RATE	= 252,	// Item : 해당Item의 AT_PHY_DEFENCE 값에 대해서만 증가치 Rate 값 (같은아이템만 적용)
	AT_I_MAGIC_DEFENCE_ADD_RATE	= 253,	// Item : 해당Item의 AT_MAGIC_DEFENCE 값에 대해서만  증가치 Rate 값 (같은 아이템만 적용)
	AT_PROJECTILE_SPEED_RATE	= 254,	// Client : 스킬발사체의 속도 증폭값(만분율, 10000 이상이면 속도 증가) 기본속도는 Client 발사체 XML에 있음.
	AT_I_PHY_ATTACK_ADD_RATE	= 255,	// Item : Inventory의 AT_PHY_ATTACK_MIN/AT_PHY_ATTACK_MAX 값을 Rate값으로 증폭
	AT_I_MAGIC_ATTACK_ADD_RATE	= 256,	// Item : Inventory의 AT_MAGIC_ATTACK_MIN/AT_MAGIC_ATTACK_MAX 값을 Rate값으로 증폭
	AT_INVEN_PHY_DEFENCE_ADD_RATE	= 257,	// Item : Inventory의 AT_PHY_DEFENCE 값을 Rate값으로 증폭 (모든방어구의 방어력 적용)
	AT_INVEN_MAGIC_DEFENCE_ADD_RATE	= 258,	// Item : Inventory의 AT_MAGIC_DEFENCE 값을 Rate값으로 증폭 (모든방어구의 방어력 적용)
	AT_UNIT_SIZE_XY	= 259,		// Unit Size (X,Y 크기)Attack Range 계산 할때, Unit의 크기를 고려 해 주어야 할 때가 있다. (Target이 Boss와 같이 클 경우)
	AT_UNIT_SIZE_Z = 260,		// Unit Size (Z 크기)Attack Range 계산 할때, Unit의 크기를 고려 해 주어야 할 때가 있다. (Target이 Boss와 같이 클 경우)
	AT_CREATE_SKILLACTOR_CNT		= 261,	// 스킬 액터를 만들 갯수. 단 0 이면 1개 생성함.
	AT_REST_EXP_ADD_MAX				= 262,	// 휴식 경험치 보너스 받을 수 있는 최대 경험치 값 (64bit)
	AT_DIE_TYPE						= 263,	// 죽을때 옵션
	AT_AMP_PHY_DEFENCE_ADD_RATE		= 264,
	AT_AMP_MAGIC_DEFENCE_ADD_RATE	= 265,

	AT_JOINT_COOLTIME_SKILL_NO_1	= 270,	// 쿨타임을 함께 적용할 스킬 번호들 AT_JOINT_COOLTIME_SKILL_NO - 270 ~ 280
	AT_JOINT_COOLTIME_SKILL_NO_2	= 271,
	AT_JOINT_COOLTIME_SKILL_NO_3	= 272,
	AT_JOINT_COOLTIME_SKILL_NO_4	= 273,
	AT_JOINT_COOLTIME_SKILL_NO_5	= 274,
	AT_JOINT_COOLTIME_SKILL_NO_6	= 275,
	AT_JOINT_COOLTIME_SKILL_NO_7	= 276,
	AT_JOINT_COOLTIME_SKILL_NO_8	= 277,
	AT_JOINT_COOLTIME_SKILL_NO_9	= 278,
	AT_JOINT_COOLTIME_SKILL_NO_10	= 279,
	AT_JOINT_COOLTIME_SKILL_NO_MAX	= 280,
	
	AT_JOINT_COOLTIME		= 281,			// 쿨타임을 함께 적용할때 사용한 스킬의 쿨타임이 아닌, 이 값의 쿨타임을 적용할때

	AT_SAVE_DB_SKILL_COOLTIME = 282,		//이 어빌을 가지는 스킬은 캐릭터 로그아웃할 때, 테이블에 저장된다.

	AT_CHARACTOR_SLOT = 283,				//캐릭터의 캐선창 슬롯 위치

	AT_FILTER_EXCEPT_EX_01	= 300,
// 예약 : 확장! AT_FILTER_EXCEPT_EX_01 - AT_FILTER_EXCEPT_100, 300 ~ 399

	AT_NOT_MOVE = 400,			//이동 불가
	AT_CALLER_LEVEL			= 501,	// Caller's Level
	AT_EXCEPT_GROUND_TYPE	= 502,	// EGndAttr value
	AT_CALLER_TYPE			= 503,	// Caller's Unit Type(IsTarget에서 사용해야 한다.)
	AT_HANDYCAP				= 504,
	AT_TEAM					= 505,
	AT_DELAY				= 506,
	AT_AI_TYPE				= 507,
	AT_DISTANCE				= 508,
	AT_NOTAPPLY_MAPATTR		= 509,	// 사용 불가능한 그라운드 속성(ex 포탈아이템은 미션에서 사용 못해야 하니까...)
	AT_BATTLEAREA_INDEX		= 510,	// 현재 속한 BattleArea
	AT_EFFECT_SIZE			= 511,
	AT_EXPERIENCE			= 512,
	AT_MONEY				= 513,
	AT_GENERATE_STYLE		= 514,
	AT_DISTANCE2			= 515, // Entity 소환할때 캐릭터의 오른쪽 방향으로 얼마만큼 이격된 위치에서 소환 할것인가
	AT_VOLUNTARILY_DIE		= 516,	//자의로 인한 사망을 나타냄
	AT_DIE_MOTION			= 517,	// 현재 Die 모션 중인지 체크
	AT_DAMAGE_PUSH_TYPE		= 518,	// Pushback by damage type
	AT_DEATH_EXP_PENALTY	= 519,	// Player 죽었을 때 깍이는 경험치 (Percentage)
	AT_LIFETIME				= 520,	// (DummyPlayer) Life time
	AT_SKILL_EXTENDED		= 521,	// 스킬이 버프를 받아서 더욱 강력해진 상태(발사체 개수 변화)
	AT_DMG_DELAY_TYPE		= 522,	// Damage 받았을 때 Delay값을 어디서 읽을 것인가? (공격Skill_Abil에 기록)(0=unit, 1=skill, 2=unit+skill)
	AT_MAX_HP_EXPAND_RATE	= 523,	// Class별로 MaxHP 증가치(만분율)
	AT_MAX_MP_EXPAND_RATE	= 524,	// Class별로 MaxMP 증가치(만분율)
	AT_DICE_VALUE			= 525,	// 투사:Roulette 스킬 결과값(주사위값)
	AT_REFLECTED_DAMAGE		= 526,	// Reflected Damage (Damage반사) 크기
	AT_1ST_ATTACK_ADDED_RATE	= 527,	// 첫번째 공격에 대해서만 추가적인 공격치(최종공격력에 대한 만분율)
	AT_INDEX				= 528,	// 그냥 Index값으로 쓰면 좋겠다.
	AT_PDMG_DEC_RATE_2ND	= 529,	// 물리Damage에 대해서 2차적으로 Damage 감소 Rate (마나쉴드 사용)
	AT_MDMG_DEC_RATE_2ND	= 530,	// 마법Damage에 대해서 2차적으로 Damage 감소 Rate (마나쉴드 사용)
	AT_APPLY_ATTACK_SPEED	= 531,	// 스킬 : 이 스킬이 공격속도에 영향을 받을 것인가(0:안받는다, 1:받는다)
	AT_CLAW_DBL_ATTK_RATE	= 532,	// 스킬 : Claw 평타 왼속 공격시에 더블어택 발동 확률(만분율)
	AT_ADD_MONEY_PER_LV		= 533,	// Monster Level에 따라 추가적인 추가지급 Money Rate량(만분율)
									// Unit : 도둑(소매치기) 스킬은 몬스터 잡을때 추가적인 Money를 지급해야 한다.
	AT_ADD_MONEY_RATE		= 534,	// 추가적인 Money Drop이 발생할 확률
	AT_MAP_NUM				= 535,	// 아이템 : 마을소환 스크롤일 경우 가야할 마을 Map번호
	AT_PORTAL_NUM			= 536,	// 아이템 : 마을소환 스크롤일 경우 가야할 Portal 번호
	AT_POSITION_X			= 537,	// 아이템 : 마을소환 스크롤일 경우 가야할 좌표값(X)
	AT_POSITION_Y			= 538,	// 아이템 : 마을소환 스크롤일 경우 가야할 좌표값(Y)
	AT_POSITION_Z			= 539,	// 아이템 : 마을소환 스크롤일 경우 가야할 좌표값(Z)
	AT_PARENT_SKILL_NUM		= 540,	// Skill : Parent Skill number
	AT_1ST_AREA_TYPE		= 541,	// Skill : 사정거리 : Target을 잡을때, 어떤 형태의 Target Area를 생성할 것인가?(ESkillArea) SkillFire 할때 Target을 잡기위한 값
	AT_2ND_AREA_TYPE		= 542,	// Skill : 효과거리 : Target을 잡을때, 어떤 형태의 Target Area를 생성할 것인가?(ESkillArea) 실제로 Damage를 줄 Target을 선택하기 위해 입력하는 값 AT_2ND_AREA_PARAM1 이 입력되지 않으면 Skill:AT_ATTACK_RANGE 값 사용 
	AT_1ST_AREA_PARAM1		= 543,	// Skill : 사정거리 : NOT USE(Skill:AT_ATTACK_RANGE 값을 사용하라. 의미 직육면체()
	AT_2ND_AREA_PARAM1		= 544,	// Skill : 효과거리 : 
	AT_1ST_AREA_PARAM2		= 545,	// Skill : 사정거리 : 직육면체(폭)/구(반지름)/원뿔(각도)
	AT_2ND_AREA_PARAM2		= 546,	// Skill : 효과거리 : 직육면체(폭)/구(반지름)/원뿔(각도)
	AT_1ST_AREA_PARAM3		= 547,	// Skill : 사정거리 : 예약
	AT_2ND_AREA_PARAM3		= 548,	// Skill : 효과거리 : 예약
	AT_1ST_AREA_PARAM4		= 549,	// Skill : 사정거리 : 예약
	AT_2ND_AREA_PARAM4		= 550,	// Skill : 효과거리 : 예약
	AT_GLOBAL_COOLTIME		= 551,	// Skill : 스킬사용 후에는 어떤 스킬도 해당 시간동안 사용 금지.
	AT_REFLECT_DMG_HP		= 552,	// Refeclted Damage 발생했을때, 맞은넘의 남은 HP 값
	//AT_ABS_ADDED_DMG		= 553,	// Unit : 공격할 때, 최종Dmg에 추가적으로 더해지는 Dmg
	AT_DMG_DEC_RATE_COUNT	= 554,	// AT_PDMG_DEC_RATE_2ND or AT_MDMG_DEC_RATE_2ND 능력 적용 남은 개수(-1:Unlimited)
	AT_AMOUNT				= 555,	// 량으로 사용
	AT_COLLISION_SKILL		= 556,	// 몬스터 충돌 되었을 때 데미지 줄 스킬 번호(<>0 이면 Damage를 주어야 하며, Abil값의 Skill로 계산)
	AT_TEMPLATE_SKILLNO		= 557,	// 스킬 : 스킬 함수 호출 될때, 이 어빌값의 스킬함수를 호출하도록 해 준다.
	AT_DEFAULT_DURATION		= 558,	// Item : 내구도 아이템 생성시에 초기설정되는 내구도값(0이면 AT_DEFAULT_AMOUNT 으로 세팅)
	AT_DIE_ANI_PLAYTIME		= 559,	// Monster : 죽을때 죽는 Ani 플레이 시간
	AT_CASTER_STATE			= 560,	// Skill : 스킬 시전자의 상태 제한 (ECaster_State)
	AT_FIRE_TYPE			= 561,	// Skill : Skill Fire 종류(언제 Damage를 줄 것인가 등의 정의) ESkillFireType
	AT_EXCEPT_GRADE			= 562,	// Effect : AddEffect 되지 않을 UnitType 정의
	AT_MAX_LEVELLIMIT		= 563,	// Item등에서 상위레벨제한 (이값보다 높은 레벨은 착용 불가)
	AT_EQUIP_MESSAGE		= 564,	// Item : 장착했을 때, 보여줄 안내 메시지(TextTable ID)
	AT_MONEY_MIN			= 565,	// Monster : Drop되는 Money 최소값 (GetAbil(AT_MONEY_MIN) ~ GetAbil(AT_MONEY) 의 Rand 값으로 떨어짐)
	AT_PROWLAREA_RANGE		= 566,	// Monster : Target 발견했을 때, 무조건 최단거리로 이 거리까지 다가가기
	AT_FRAN					= 567,  // Fran 경험치 보상
	AT_TACTICS_LEVEL		= 568,	// 용병 레벨
	AT_TACTICS_EXP			= 569,	// 용병 경험치
	AT_CASH					= 570,	// 캐쉬
	AT_REVERSION_ITEM		= 571,	// 
	AT_R_FRAN				= 572,	// 프랜 획득량 증가
	AT_WARP_SKILL_NO 		= 575,	// 순간이동 스킬번호
	AT_COLLISION_SKILL_FIRE	= 576,	// 충돌 데미지를 실제로 스킬로 사용할 것인가. 스킬어빌.
	AT_COLLISION_USE_FORCE	= 577,	// 클라이언트 CheckTouchDmg 함수에서 IsIgnoreEffect(ACTIONEFFECT_DMG) 옵션을 무시하고 함수가 강제로 발동 되도록 함. 클래스 어빌
	AT_CLAW_DBL_ATTK_DMG_RATE	= 579,	// 스킬 : 더블어택 발동시 데미지 %(만분율)
	AT_CHILD_SKILL_NUM_01	= 580,	// 스킬 쓸때 영향 받는 자식 스킬들 (Value = Child Skill의 레벨 2이상 일 경우 -> Base Skill No 입력)
	AT_CHILD_SKILL_NUM_02	= 581,	// 스킬 쓸때 영향 받는 자식 스킬들
	AT_CHILD_SKILL_NUM_03	= 582,	// 스킬 쓸때 영향 받는 자식 스킬들
	AT_CHILD_SKILL_NUM_04	= 583,	// 스킬 쓸때 영향 받는 자식 스킬들
	AT_CHILD_SKILL_NUM_05	= 584,	// 스킬 쓸때 영향 받는 자식 스킬들
	AT_CHILD_SKILL_NUM_06	= 585,	// 스킬 쓸때 영향 받는 자식 스킬들
	AT_CHILD_SKILL_NUM_07	= 586,	// 스킬 쓸때 영향 받는 자식 스킬들
	AT_CHILD_SKILL_NUM_08	= 587,	// 스킬 쓸때 영향 받는 자식 스킬들
	AT_CHILD_SKILL_NUM_09	= 588,	// 스킬 쓸때 영향 받는 자식 스킬들
	AT_CHILD_SKILL_NUM_10	= 589,	// 스킬 쓸때 영향 받는 자식 스킬들

	AT_PLAY_CONTENTS_TYPE	= 590,	// 컨텐츠 타입(EPlayContentsType)
	AT_SKILL_BACK_DISTANCE	= 591,	//타겟을 잡을 때 뒤로 약간 빼 줄 거리
	AT_SAVE_DB				= 592,	// SaveDB 할 것인가? (Effect/Item(Group))

	AT_ADD_ITEMDROP_RATE	= 593,	// 아이템 드랍 확률 상승(미션 맵 이동시에 적용된다. 이미 들어가 있는 맵에선 적용되지 않는다.)
	AT_ADD_ONCE_ITEMDROP_RATE = 594, //아이템 드랍 한번 더 할 확률

	AT_USE_INSURANCE_ITEM_NO		= 596,	// 구몬스터카드와 신소켓카드에서 적용 가능한 보험 아이템 번호
	AT_OLD_MONSTERCARD		= 597,	// 구몬스터카드와 신소켓카드의 구별을 위한 어빌(구몬스터카드에만 이 어빌을 등록한다.)

	AT_SOCKETCARD_INSERT	= 598,	// 소켓카드 적용 성공확률

	AT_MONSTER_CARD_ORDER	= 599,  // 몬스터 카드 번호(인덱스)

	AT_BONUS_CASH			= 600,	// 캐시 마일리지

	AT_MONSTER_CARD_NO		= 601,	// 몬스터 카드 번호

	AT_ENABLE_USE_GROUPNO	= 602,	// 사용 가능한 그라운드 번호

	AT_HOME_SIDEJOB			= 603,	// 마이홈 아르바이트 현황
	
	AT_VERTICAL_DISTANCE	= 608,	// AT_CREATE_SKILLACTOR_CNT가 2이상일때, 스킬 액터를 생성할 위치결정(위 아래로 이격시킬 거리)
	AT_CAN_GROUND_ATTR		= 609,	// 사용 가능한 맵 속성

	AT_CHILD_EFFECT_NUM_01	= 610,	// 이펙트가 Add 될 때 추가 어빌을 적용해야하는 자식 이펙트 (Value = Child Effect의 레벨 2이상 일 경우 -> Base Effect No 입력)
	AT_CHILD_EFFECT_NUM_02	= 611,	// 이펙트가 Add 될 때 추가 어빌을 적용해야하는 자식 이펙트 (AddEffect로 처리하지 않고 어빌만 가져와서 직접 넣고 빼준다.)
	AT_CHILD_EFFECT_NUM_03	= 612,	// 이펙트가 Add 될 때 추가 어빌을 적용해야하는 자식 이펙트
	AT_CHILD_EFFECT_NUM_04	= 613,	// 이펙트가 Add 될 때 추가 어빌을 적용해야하는 자식 이펙트
	AT_CHILD_EFFECT_NUM_05	= 614,	// 이펙트가 Add 될 때 추가 어빌을 적용해야하는 자식 이펙트
	AT_CHILD_EFFECT_NUM_06	= 615,	// 이펙트가 Add 될 때 추가 어빌을 적용해야하는 자식 이펙트
	AT_CHILD_EFFECT_NUM_07	= 616,	// 이펙트가 Add 될 때 추가 어빌을 적용해야하는 자식 이펙트
	AT_CHILD_EFFECT_NUM_08	= 617,	// 이펙트가 Add 될 때 추가 어빌을 적용해야하는 자식 이펙트
	AT_CHILD_EFFECT_NUM_09	= 618,	// 이펙트가 Add 될 때 추가 어빌을 적용해야하는 자식 이펙트
	AT_CHILD_EFFECT_NUM_10	= 619,	// 이펙트가 Add 될 때 추가 어빌을 적용해야하는 자식 이펙트
	
	AT_1ST_ATTACK_ADDED_RATE_APPLY_NUM = 627,	// 이 값은 AT_1ST_ATTACK_ADDED_RATE(527) 기능 적용 횟수가 된다. 0일 지라도 AT_1ST_ATTACK_ADDED_RATE가 존재 한다면 1타는 적용된다

	AT_SOCET_CARD_EXTRACTION_CASH_ITEM = 628, //소켓 카드 추출시 필요한 캐시 아이템 넘버
	AT_SOCET_CARD_EXTRACTION_CASH_ITEM_COUNT = 629, //소켓 카드 추출시 필요한 캐시 아이템 수량
	AT_SOCET_CARD_EXTRACTION_ITEM_NAME = 630, //소켓 카트 추출시 필요한 InGame 아이템 넘버
	AT_SOCET_CARD_EXTRACTION_ITEM_COUNT = 631, //소켓 카트 추출시 필요한 InGame 아이템 수량

	AT_IGNORE_MONSTER_REGEN_COUNT = 649,	//World XML에서 설정된 최대 리젠 몬스터수를 무시할 수 있는 어빌
	AT_IGNORE_MACRO_COUNT	= 650,	//매크로 체크 무시할 경험치 획득 카운트
	AT_CHAT_BALLOOON_TYPE	= 651,	// 채팅 말풍선 타입 어빌
	
	AT_SUB_PLAYER_ACTION	= 660, // 쌍둥이 보조캐릭터와 같은 Actor에 사용되는 액션일때

	AT_RESULT_WAIT_TIME		= 700, //보스전, 정예 결과창 나올때 딜레이 시간
	AT_NO_KILLCOUNT_MAP		= 701,	//killcount시스템을 사용하지 않는 맵. 맵어빌임

	AT_SKILL_EFFICIENCY		= 800,	// 스킬의 효율
	AT_AUTO_PET_SKILL		= 810,	// 펫 AI 토글을 위한 어빌
	AT_CALLER_IS_PET		= 811,	// 이 엔티티의 소환자는 펫(Caller에 Player를 넣을 수 밖에 없어서 다른 방법으로 표시)
	AT_CALLER_DELETE		= 812,	// 클라전용: 엔티티인 경우의 Caller 제거(서버가 엔티티 스킬 사용시 Caller가 있는 경우 정상적으로 애니메이션이 동작하지 않는 이유때문에 Caller를 제거해야함)
	AT_OWNER_TYPE			= 813,	// Caller의 최상위 Owner UnitType
	AT_LIFETIME_DELAY		= 814,
	AT_MOUNTED_PET_SKILL	= 815,	//펫에 탑승했는지를 나타냄.
	AT_TRANS_DC_PET_SKILL	= 816,	//순간이동 비용 감소 퍼센티지
	AT_REG_ADDUNIT_GUID_TYPE	= 817, //클라 AddUnit될때 GUID 저장시키기, lua - TBL_REQ_ADD_UNIT_GUID에 정의됨
	AT_PET_SKILL_FOR_AI		= 818, //DefSkillAbil_Pet에 이 값이 1을 가지면 AI에 사용될 스킬임을 의미한다.
	//(AI에 사용되는 스킬 선택 기준을 명확하게 하기 위해 사용. 스킬의 SkillType 또는 TargetType만으로 구분하기는 모호하다.)
	AT_PET_FREEUPGRADE		= 819, //펫 상인을 통한 전직 비용을 무료로 쓸 것인가?
	AT_PET_CANNOT_RIDING_ATTACK	= 820, //이 어빌이 0이 아니면 펫은 탑승공격시 타격을 하지 않는다.

	AT_MONSTER_FIRST_TARGET	= 900,	// 몬스터가 타겟을 먼저 잡을 타입을 선택
	AT_TARGET_SELECT_TYPE   = 901,  // 공격 타켓 선택(E_TARGETTING_TYPE)
	AT_TARGET_SELECT_VALUE  = 902,  // 0:내림차순(큰>작), 1:오름차순(작>큰)

	AT_INDUN_PARTICIPATION_RATE	= 998,	//인던 참여율
	AT_MONSTER_KILL_COUNT	= 999,	// 몬스터 킬 카운트
	AT_LAST_ATTACK_DAMAGE_RATE	= 1000, //마지막 데미지 계산할때 적용될 확률
	AT_SP					= 1001,
	AT_HIDE					= 1002, // 0: 캐릭터를 그림   1: 캐릭터를 그리지 않음(완전히 숨겨버림)
	AT_EVENTSCRIPT_HIDE		= 1003, // 이벤트 스크립트를 통한 연출에서 0: 캐릭터를 그림   1: 캐릭터를 그리지 않음(완전히 숨겨버림)
	AT_ADD_EXP_PER			= 1004, // Player가 얻는 Exp값(중복 불가한 어빌)2009.09.04 변경(50% 이면 50 입력해야 함) <-- (옛날값)100이 100%임 1.9배는 190으로 세팅
	AT_ADD_MONEY_PER		= 1005,
	AT_MAX_TARGETNUM		= 1007,
	AT_SKILLPOWER_RATE		= 1008,	// Skill의 공격력 Rate
	AT_SKILL_MIN_RANGE		= 1009,
	AT_MON_MIN_RANGE		= 1010, // 몬스터가 PC와 유지하는 최소 거리
	AT_MON_DROPITEM_ENFORCE	= 1011,	// 몬스터가 레벨차이 무시하고 아이템 강제로 드롭
	AT_ADD_EXP_CAN_DUPLICATE= 1012,	// Player가 얻는 Exp값(중복가능한 어빌)
	AT_ADDEXP_FINAL			= 1013,	// Player 가 최종적으로 얻는 Exp 증가값(기본=100) (AT_ADD_EXP_PER+AT_ADD_EXP_CAN_DUPLICATE)
	AT_MON_DROP_ALLITEM		= 1014, // 몬스터가 아이템을 모두 드랍

	AT_USED_SP				= 1015, // 사용한 SP.
	AT_MAX_LOOTNUM			= 1016, // 최대 줍기 갯수

	AT_OPTION_GROUP			= 1100,	// 아이템 옵션 타입
	AT_CLASSLIMIT_DISPLAY_FILTER	= 1101, // 직업제한 표시용 필터
	AT_SKILL_GOALPOS_COUNT	= 1102, // 스킬에서 목표위치 잡는 갯수
	AT_DUEL					= 1103, // 결투 중 (특정 플레이어 타격 가능)
	AT_DUEL_DIED_BY			= 1104, // 결투 중에 죽었다면, 누가 나를 죽였나 (UT_PLAYER, UT_MONSTER, ....)
	AT_DUEL_WINS			= 1105, // 결투 승리 횟수

	AT_DROPITEMGROUP		= 2008,		// Drop 하는 아이템 그룹 ID
	AT_EXCEPT_EFFECT_TYPE	= 2010,	//이 유닛이 걸리지 않을 이펙트 타입.
	AT_SKILL_ATT			= 2011,	// Skill 속성 (ESkillAttribute value, bitmask value)
	ATS_COOL_TIME			= 2012,	// Skill : Cooling Time (새로운 스킬을 사용할 수 있는 최소시간)
	AT_ADD_COOL_TIME		= 2013, // Skill의 전체적인 추가 쿨타임(스킬 기본 쿨타임 + 추가 쿨타임)
	AT_ADD_COOL_TIME_RATE	= 2014, // Skill의 전체적인 추가 쿨타임 상대값(스킬 기본 쿨타임 + 추가 쿨타임)
	AT_MAINSKILL			= 2016,	// passive skill의 Main이 되는 active skill
	AT_CASTTYPE				= 2018,	// ESkillCastType (Instant/Maintenance/CastShot)
	AT_CAST_TIME			= 2019,	// 주문을 외우는데 필요한 시간
	AT_ATT_DELAY			= 2020,	// 스킬쓰고 나서 Delay 시간
	AT_ADD_CAST_TIME		= 2021,	// 주문을 외우는데 필요한 추가 시간(캐스팅 타임 + 추가 캐스팅 타임)
	AT_TYPE					= 2022,	// Skill type
	AT_WEAPON_LIMIT			= 2023,	// Weapon limit
	AT_CLASSLIMIT			= 2024,
	AT_LEVELLIMIT			= 2025,
	AT_STATELIMIT			= 2026,
	AT_MAINTENANCE_TIME		= 2027,	// Skill : 일정시간 유지 하는 스킬의 경우 유지 시간
	AT_NEED_SP				= 2028,
	AT_MAINTENANCE_TIME2	= 2029,	// Skill : EFireType_TimeDelay 용 지연시간으로 사용. 값이 0이면 AT_MAINTENANCE_TIME으로 사용
	AT_NAMENO				= 2030,			// TB_DefRes 참조값
	//AT_ADDHEAL			= 2037,	// 응급치료 스킬 사용시 추가적인 HP 회복량
	//AT_S101200701_PARAM1	= 2038, // 스킬(101200701:찔러보기)에서 Critical 사용여부값
	AT_BLOW_ACTION_ID		= 2037, // BlowAction 동작시 등록
	AT_ANITIME_STANDUP		= 2038, // 스펜드업 애니 타임
	AT_ANIMATION_TIME		= 2039, // 스킬의 애니메이션이 타격할 때까지의 시간
	AT_BLOW_VALUE			= 2040,	// 뛰우는 힘 : Effect Abil
	AT_DMG_MAX_UNIT			= 2041,	// Skill : Damage를 입는 Unit의 최대수
	AT_DAMAGED_DELAY		= 2042, // Monster/Skill : Damage를 입은 뒤 딜레이
	AT_BLOW_DISTANCE		= 2043,	// 띄웠을 때 밀려나갈 거리(최대값)
	AT_EFFECT_NO_DUPLICATE	= 2050, // 같은 레벨의 이펙트가 있으면 다시 이펙트를 걸지 않음
	AT_EFFECTNUM1			= 2051,	// 스킬에 추가적인 Effect Number #1 (혹은 리젠시 추가될 이펙트)
	AT_EFFECTNUM2			= 2052,	// 스킬에 추가적인 Effect Number #2 (혹은 리젠시 추가될 이펙트)
	AT_EFFECTNUM3			= 2053,	// 스킬에 추가적인 Effect Number #3 (혹은 리젠시 추가될 이펙트)
	AT_EFFECTNUM4			= 2054,	// 스킬에 추가적인 Effect Number #4 (혹은 리젠시 추가될 이펙트)
	AT_EFFECTNUM5			= 2055,	// 스킬에 추가적인 Effect Number #5 (혹은 리젠시 추가될 이펙트)
	AT_EFFECTNUM6			= 2056,	// 스킬에 추가적인 Effect Number #6 (혹은 리젠시 추가될 이펙트)
	AT_EFFECTNUM7			= 2057,	// 스킬에 추가적인 Effect Number #7 (혹은 리젠시 추가될 이펙트)
	AT_EFFECTNUM8			= 2058,	// 스킬에 추가적인 Effect Number #8 (혹은 리젠시 추가될 이펙트)
	AT_EFFECTNUM9			= 2059,	// 스킬에 추가적인 Effect Number #9 (혹은 리젠시 추가될 이펙트)
	AT_EFFECTNUM10			= 2060,	// 스킬에 추가적인 Effect Number #10 (혹은 리젠시 추가될 이펙트)
	AT_CUSTOMDATA1			= 2061,	// Customized data #1
	AT_CUSTOMDATA2			= 2062,	// Customized data #2
	AT_CUSTOMDATA3			= 2063,	// Customized data #3
	AT_CUSTOMDATA4			= 2064,	// Customized data #4
	AT_CUSTOMDATA5			= 2065,	// Customized data #5
 	AT_CUSTOMDATA6			= 2066,	// Customized data #6
	AT_CUSTOMDATA7			= 2067,	// Customized data #7
	AT_CUSTOMDATA8			= 2068,	// Customized data #8
	AT_CUSTOMDATA9			= 2069,	// Customized data #9
	AT_DROPITEMRES			= 2071,	// Drop Item Icon Resource Number (TB_DefRes)
	AT_DAM_EFFECT_S			= 2072,	// Damage Motion Effect Num (Small Size)
	AT_DAM_EFFECT_M			= 2073,	// Damage Motion Effect Num (Middle Size)
	AT_DAM_EFFECT_L			= 2074,	// Damage Motion Effect Num (Large Size)
	AT_PERCENTAGE			= 2075,	// Percentage value
	AT_ADDVALUE				= 2076,	// 추가적인 값
	AT_PERCENTAGE2			= 2077,	// Percentage Value #2
	AT_MONSTER_SKILLTYPE	= 2078, // 몬스터 스킬 Type
	AT_SKILL_KIND			= 2079, // Skill 분류값 (ESkillKind)
	AT_PHY_DMG_PER			= 2080,	// Skill : Phyical Damage에 대한 Percentage 값
	AT_MAGIC_DMG_PER		= 2081, // Skill : Magic Damage에 대한 Percentage 값
	AT_RANGE_TYPE			= 2082,	// Skill : Range를 어떤것을 사용할 것인가? (EAttackRangeSource)
	AT_SPECIALABIL			= 2083,	// Skill or Effect : 부수적으로 생기는 특별한 능력 Ability Number (예:침묵하기)
	AT_MP_BURN				= 2084,	//
	AT_GOD_TIME				= 2085,	// Effect : 스킬맞고 나서 Effect되면 무적되는 시간
	AT_CASTER_MOVERANGE		= 2086,	// Skill : Caster가 전진하는 길이
	AT_TARGET_MOVERANGE		= 2087,	// Skill : Target이 밀리는 길이
	AT_DMG_CONSUME_MP		= 2088,	// Damage 받으면 HP대신 MP를 흡수하는 량(AT_C_MAGIC_DMG_DEC 값이 0이면 효과없음)
	AT_COUNT				= 2089,	// 개수를 나타낼때 사용하면 좋겠다.(Skill:최대 몇번까지 때릴 수 있는가)
	AT_ATTACK_UNIT_POS		= 2090,	// 스킬 : 공격할 수 있는 Target의 상태값(EAttackedUnitPos)(디폴트 0이 나오면 1로 처리)
	AT_COMBO_HIT_COUNT		= 2091,	// 스킬 : 공격할 수 있는 스킬의 공격이 적중시 몇 콤보가 증가 되는 가
	AT_SKILL_DIVIDE_TYPE	= 2092,	// 스킬 : 어떤 이유로 스킬을 가지게 되었는지 (기본, 길드, 등등)

// 속성 관련 추가(Old)
	AT_OFFENSE_PROPERTY			= 2093,	// 공격 속성
	AT_OFFENSE_PROPERTY_EXPAND	= 2094,	// 공격 확장 속성
	AT_DEFENCE_PROPERTY			= 2095,	// 방어 속성
	AT_DEFENCE_PROPERTY_EXPAND	= 2096, // 방어 확장 속성
	AT_OFFENSE_PROPERTY_LEVEL	= 2097,	// 공격 속성 레벨
	AT_DEFENCE_PROPERTY_LEVEL	= 2098,	// 방어 속성 레벨

	AT_COMBO_DELAY			= 2099, // 스킬 : 2092 스킬에 설정하면 강제로 콤보 리셋시간을 늘려준다 (2092 어빌이 설정된 스킬들을 위한 것)

	AT_SKILL_HP_CHECK_HIGH	= 2100,	// 스킬 : HP가 몇% 이상일 때만 이 스킬을 사용할 있음(만분율)
	AT_SKILL_HP_CHECK_LOW	= 2101,	// 스킬 : HP가 몇% 이하일 때만 이 스킬을 사용할 있음(만분율)
	AT_SKILL_MAP_DUMMY_NUM	= 2102,	// 스킬 : 맵의 더미를 찾을 때 사용할 번호. 몬스터 스킬에 사용
	AT_NEED_MAX_R_HP		= 2103,	// 스킬 : 스킬 사용시 소모되는 MaxHP의 %를 소모(만분률)
	AT_NEED_MAX_R_MP		= 2104,	// 스킬 : 스킬 사용시 소모되는 MaxMP의 %를 소모(만분률)
	AT_SKILL_RANGE_TYPE2	= 2105,	// 스킬 : 스킬 사용시 서버에서 범위검사를 할때 사용할 검사 타입. 0이 기본.

	AT_NEED_HP_MIN_VALUE	= 2106,	// 스킬 : 스킬 사용시 필요한 최소한의 HP
	AT_NEED_MP_MIN_VALUE	= 2107,	// 스킬 : 스킬 사용시 필요한 최소한의 MP

	AT_SKILL_SEND_ZONE_TYPE			= 2109, // 
	AT_SKILL_MAP_BLOCKCOUNT_X		= 2110, // 스킬 : 
	AT_SKILL_MAP_BLOCKCOUNT_Y		= 2111, // 스킬 : 
	AT_SKILL_MAP_SAFETY_ZONE_COUNT	= 2112, // 스킬 : 안전지역
	AT_SKILL_MAP_DUMMY_NUM1			= 2113, // 스킬 : 맵의 더미를 찾을 때 사용할 번호. 몬스터 스킬에 사용
	AT_SKILL_MAP_DUMMY_NUM2			= 2114, // 스킬 : 맵의 더미를 찾을 때 사용할 번호. 몬스터 스킬에 사용
	AT_SKILL_MAP_DUMMY_NUM3			= 2115, // 스킬 : 맵의 더미를 찾을 때 사용할 번호. 몬스터 스킬에 사용
	AT_SKILL_MAP_DUMMY_NUM4			= 2116, // 스킬 : 맵의 더미를 찾을 때 사용할 번호. 몬스터 스킬에 사용
	AT_SKILL_MAP_DUMMY_NUM5			= 2117, // 스킬 : 맵의 더미를 찾을 때 사용할 번호. 몬스터 스킬에 사용
	AT_SKILL_MAP_DUMMY_NUM6			= 2118, // 스킬 : 맵의 더미를 찾을 때 사용할 번호. 몬스터 스킬에 사용
	AT_SKILL_MAP_DUMMY_NUM7			= 2119, // 스킬 : 맵의 더미를 찾을 때 사용할 번호. 몬스터 스킬에 사용
	AT_SKILL_MAP_DUMMY_NUM8			= 2120, // 스킬 : 맵의 더미를 찾을 때 사용할 번호. 몬스터 스킬에 사용
	
	AT_EFFECT_TYPE_WHEN_HIT			= 2130, // 0 == 나에게 검(추가될 경우 타입 추가)
	AT_EFFECTNUM1_WHEN_HIT			= 2131, // 스킬에 추가적인 Effect Number #1 (혹은 리젠시 추가될 이펙트)
	AT_EFFECTNUM2_WHEN_HIT			= 2132,
	AT_EFFECTNUM3_WHEN_HIT			= 2133,
	AT_EFFECTNUM4_WHEN_HIT			= 2134,
	AT_EFFECTNUM5_WHEN_HIT			= 2135,
	AT_EFFECTNUM6_WHEN_HIT			= 2136,
	AT_EFFECTNUM7_WHEN_HIT			= 2137,
	AT_EFFECTNUM8_WHEN_HIT			= 2138,
	AT_EFFECTNUM9_WHEN_HIT			= 2139,
	AT_EFFECTNUM10_WHEN_HIT			= 2140,

	AT_SKILL_SUMMONED_PARENT_SKILL		= 2150, // 스킬 : 소환주가 소환체에게 지시한 스킬번호 (리게인/임팩트 언서먼용으로 사용)
	AT_SUMMONED_NOT_SHOW_UI				= 2151, // UI : 이 어빌이 포함된 소환체는 소환체 정보 UI에 띄우지 않는다.

	AT_TARGET_TYPE			= 2200, // 타겟팅 타입(Item의 TargetType을 설정) / Skill은 m_byTarget, GetTargetType()
	AT_SKILL_CHECK_NONE_EFFECT		= 2250, //이 어빌이 참이면 스킬 대상에게 스킬에 연결된 이펙트가 걸려있는지 찾아보고 걸려있지 않을 때만 캐스팅 성공시킨다 (클라이언트만 사용)

	AT_VISITOR_USE_ITEM		= 2300,	// 마이홈 아이템 방문자가 사용 가능한 아이템 이다.

	AT_TIME_TYPE			= 2301,	// 아이템 사용 시간 타입
	AT_USE_TIME				= 2302,	// 아이템 사용 시간
	
	AT_ITEM_OPTION_TIME		= 2303,	// 아이템 옵션을 사용할 기간(몬스터 카드 옵션 사용 시간용)

	AT_CAST_TIME_RATE		= 2304,	// 스킬 캐스트 타임 증감율 만분율
	
	AT_PHY_DMG_PER2			= 2480,	// AT_PHY_DMG_PER류가 패시브 스킬이나 버프로 들어갈때 사용
	AT_MAGIC_DMG_PER2		= 2481, // AT_MAGIC_DMG_PER류가 패시브 스킬이나 버프로 들어갈때 사용
	
	AT_PHY_DMG_PER2_SUB_PLAYER = 2482,	// AT_PHY_DMG_PER류가 패시브 스킬이나 버프로 들어갈때 사용(SUB_PLAYER에게만 적용)
	AT_MAGIC_DMG_PER2_SUB_PLAYER = 2483,// AT_MAGIC_DMG_PER류가 패시브 스킬이나 버프로 들어갈때 사용(SUB_PLAYER에게만 적용)

	AT_USE_PART_CHECK_COLLISION		= 2500, // 부분 충돌구 사용(터치데미지에서 활용)
	AT_PART_CHECK_COLLISION_01		= 2501, // 설정되면 충돌처리, ABVShapeIdx(XML순서)는 0이 나올수도 있어 Abil은 +1하여 등록
	AT_PART_CHECK_COLLISION_02		= 2502,
	AT_PART_CHECK_COLLISION_03		= 2503,
	AT_PART_CHECK_COLLISION_04		= 2504,
	AT_PART_CHECK_COLLISION_05		= 2505,
	AT_PART_CHECK_COLLISION_06		= 2506,
	AT_PART_CHECK_COLLISION_07		= 2507,
	AT_PART_CHECK_COLLISION_08		= 2508,
	AT_PART_CHECK_COLLISION_09		= 2509,
	AT_PART_CHECK_COLLISION_10		= 2510,

	AT_EFFECT_USE_MAPNO_01				= 2511,	//이펙트가 걸리는 것이 가능한 맵번호들
	AT_EFFECT_USE_MAPNO_10				= 2520,

	AT_IS_CHAIN_COMBO		= 2600,
	AT_IS_OLD_COMBO			= 2601,

// Monster Ability
	AT_WALK_TYPE			= 3001,
	AT_JOB					= 3002,
	AT_DETECT_RANGE			= 3003,
	AT_CHASE_RANGE			= 3004,
	AT_MAX_SKILL_NUM		= 3005,
	AT_NORMAL_SKILL_ID		= 3006, // 디폴트 공격
	AT_IDLE_TIME			= 3007,	// IDLE 유지 시간
	AT_SKILL_CHOOSE_TYPE	= 3008, // AI에서 Skill을 선택하는 방법
	AT_MOVE_RANGE			= 3009,
	AT_MON_SKILL_01			= 3010,	// AT_MON_SKILL_01 - AT_MON_SKILL_10 (예약)
	AT_MON_SKILL_02			= 3011,	
	AT_MON_SKILL_03			= 3012,	
	AT_MON_SKILL_04			= 3013,	
	AT_MON_SKILL_05			= 3014,	
	AT_MON_SKILL_06			= 3015,	
	AT_MON_SKILL_07			= 3016,	
	AT_MON_SKILL_08			= 3017,	
	AT_MON_SKILL_09			= 3018,	
	AT_MON_SKILL_10			= 3019,	
	AT_MON_SKILL_RATE_01	= 3020,
	AT_MON_SKILL_RATE_02	= 3021,
	AT_MON_SKILL_RATE_03	= 3022,
	AT_MON_SKILL_RATE_04	= 3023,
	AT_MON_SKILL_RATE_05	= 3024,
	AT_MON_SKILL_RATE_06	= 3025,
	AT_MON_SKILL_RATE_07	= 3026,
	AT_MON_SKILL_RATE_08	= 3027,
	AT_MON_SKILL_RATE_09	= 3028,
	AT_MON_SKILL_RATE_10	= 3029,
	//AT_MON_SKILL_FREQUENCY_01 = 3090,	// AT_MON_SKILL_FREQUENCY_01 - AT_MON_SKILL_FREQUENCY_10 (예약)
	AT_ENTITY_TYPE			= 3030, // EEntityType참고
	//AT_MONSTER_TYPE			= 3031,
	AT_PATROL_MIN_TIME		= 3031,	// Monster Patrol Min time
	AT_PATROL_MAX_TIME		= 3032,	// Monster Patrol Max time
	//AT_NORMAL_SKILL_RATE	= 3032,	// 삭제 예정
	AT_DIE_EXP				= 3033,
	AT_UNIT_SIZE			= 3034,	// 1:Small, 2:Middle, 3:Large// 몬스터 크기에 따라 Damage받는 모습을 다르게 하기 위한 값
	AT_WAYPOINT_INDEX		= 3035,	// 몬스터가 현재 가진 WayPoint의 index
	AT_WAYPOINT_GROUP		= 3036, // 몬스터가 현재 가진 WayPoint의 Group
	//AT_SUMMONCOMRADE_STATE	= 3037, // 몬스터가 동료를 소환한 적이 있냐?
	//AT_SUMMON_COMRADE		= 3038, // 이 몬스터는 소환된 놈이냐? 아니냐?
	AT_MAX_SUMMON_COUNT		= 3037,	//최대 소환가능한 수(몬스터가 자식으로 가질 수 있는 최대 몬스터수)
	AT_SKILL_SUMMON_MONBAGCONTROL	= 3038,	// 스킬로 소환할 몬스터 백
	AT_DAMAGEACTION_TYPE	= 3039,	// Monster:Damaged Action type (0 = normal, 1 = DamageAction without DamagedDelay, 101 = no damaged delay(boss), 111 = OnlyDamage And Not AddEffect,1001 = Parent Unit To Damage)// Effect : 0(normal), 1(Knock down)
	AT_IDLEACTION_TYPE		= 3040,	// Monster가 Idle 상태에서 앞을 보는것을 변경하고 싶을때 ( 0=앞을 본다, 101 = 앞을 보지 않는다)
	AT_ITEM_BAG_PRIMARY		= 3041,	// Monster Regen - Item Bag Primary
	AT_ITEM_BAG_SECONDARY	= 3042,	// Monster Regen - Item Bag Secondary
	AT_NOT_SEE_PLAYER		= 3043, // 0 : 맞았을 때 플레이어를 본다! 101 : 맞아도 플레이어를 쳐다보지 않는다.
	AT_MANUAL_DIEMOTION		= 3044, // 0 : 일반적인 죽음 101 : 특수하게 죽음(WorldAction등)
	AT_UNIT_SCALE			= 3045,	// 클라이언트에서 Unit을 만들때 사용하는 Scale 비율값(% 사용)
	AT_WAYPOINT_INDEX_FROM	= 3046,	// WayPoint 이동경로 시작 Index
	AT_RETREAT_MIN_TIME		= 3047,	// AI에서 도망가는 최소시간
	AT_RETREAT_MAX_TIME		= 3048,	// AI에서 도망가는 최대시간
	AT_RETREAT_MOVESPEED	= 3049,	// AI에서 도망가는 속도(보통속도에 대한 만분율)
	AT_R_RETREAT_HP			= 3050,	// 도망가야하는 HP값
	AT_CHASE_MOVESPEED		= 3051,	// AI에서 적을 쫒는 속도(보통속도에 대한 만분율)
	AT_HIDE_ANI_TIME		= 3052,	// AI : Hide하거나/나타날때 걸리는 Ani 시간
	AT_MONSTER_TYPE			= 3053,	// EMonsterType(0:Normal, 1:공중형)
	AT_HEIGHT				= 3054,	// Monster : 공중형몬스터가 나는 높이
	AT_MANUAL_OPENING		= 3055,	// 정예가 특별한 오프닝을 할 건지

	//AT_MAX_DROP_ITEM_COUNT	= 3055,
	AT_ITEM_BAG_SUCCESS_RATE_CONTROL= 3056,

	AT_CHASE_DONE			= 3057,	// 몬스터가 PC추적을 끝냈는가?
	AT_CHASE_PATTERN		= 3058,	// 추적 패턴 ( 1 : 앞을 잡는다, 그 외 : 뒤를 잡음)
	AT_CHASE_ELAPSED_TIME	= 3059,

//Skill /Effect Abil 3060 ~ 3999까지 사용 예정
	AT_NO_DAMAGE_USE_DAMAGEACTION	= 3060, //데미지는 없고 데미지 모션만을 취한다.
	AT_DELIVER_DAMAGE_BLOCK_RATE = 3061,	//대신 입는 데미지의 데미지 감소율
	
//우선순위 동시에 걸렸을 경우 AT_BARRIER_100PERECNT_COUNT > AT_BARRIER_AMOUNT - 100% 흡수 카운터가 사라진후 데미지 흡수가 소모
	AT_BARRIER_AMOUNT			= 3062,		//데미지를 흡수할 수 있는 양
	AT_BARRIER_100PERECNT_COUNT = 3063,		//100% 데미지를 흡수하는 베리어 카운터
	AT_PREV_BARRIER_100PERECNT_COUNT = 3064, //이전 베리어 카운터(값이 변하는것을 알기 위해서)
	AT_ATROPINE_USE_COUNT		= 3065,	//아트로핀을 사용한 횟수
	AT_ENABLE_AUTOHEAL_BACKUP	= 3066, //오토힐의 이전 상태를 백업해 둔다. //Autoheal기능이 디버프에 의해 사라졌다가 다시 복구 되야할때 사용
	AT_PENETRATION_COUNT		= 3067, //몇개를 관통할 것인가?
	AT_DOUBLE_JUMP_USE			= 3068, //더블 점프 사용	
	AT_NOT_SEE_TARGET		= 3069,	//0 : 타겟을 쳐다본다 101 : 타겟을 처다보지 않는다

	AT_DEFAULT_ATTACK_DELAY	= 3070,
	
	AT_NOT_FLY_TO_CAMERA	= 3071,	//죽었을 때 카메라로 날아오지 않는다. 클라이언트용
	AT_POSTURE_STATE		= 3072,	//누워있거나 공중에 떠 있거나

	AT_ADD_R_NEED_HP			= 3073, // 스킬 시전시 사용되는 HP를 %로 증감 시긴다.(만분률) AT_NEED_HP * AT_ADD_NEED_HP / ABILITY_RATE_VALUE_FLOAT
	AT_ADD_R_NEED_MP			= 3074, // 스킬 시전시 사용되는 MP를 %로 증감 시긴다.(만분률) AT_NEED_MP * AT_ADD_NEED_MP / ABILITY_RATE_VALUE_FLOAT

	AT_DELIVER_DAMAGE_CALLER = 3075, // Caller가 대신 데미지를 입어야 하는 경우 세팅(Entity가 사용)

	AT_DAMAGEACTION_FORCE	= 3076, // 스킬에 셋팅되어 있으면 무조건 데미지 액션을 취한다.
	AT_DAMAGECHECK_INTER	= 3077,	//CheckTagetVaild에서 사용. 연속적으로 데미지를 입을수 있는 시간간격. 0이면 100

	AT_ADD_R_NEED_HP_2			= 3078, // AT_ADD_R_NEED_HP 어빌이 중복이 되지 않는 것을 보완하여 어빌값이 중복되도록
	AT_ADD_R_NEED_MP_2			= 3079, // AT_ADD_R_NEED_MP 어빌이 중복이 되지 않는 것을 보완하여 어빌값이 중복되도록
	
	AT_MIN_DROP_ITEM_COUNT	= 3081,
	AT_MAX_DROP_ITEM_COUNT	= 3082,

	AT_MIN_DROP_MONEY_COUNT = 3083,
	AT_MAX_DROP_MONEY_COUNT = 3084,
	
	AT_SPREAD_RANGE			= 3085,
	AT_IS_DEATH_PENALTY		= 3086,

	AT_HP_BACKUP			= 3087,
	AT_MP_BACKUP			= 3088,

	AT_ADD_BARRIER_AMOUNT	= 3089, // 베리어의 추가적인 흡수량
	
	AT_SKILL_ON_DIE			= 3090,		//HP가 0일때 써야 할 스킬 번호
	AT_DAMAGE_EFFECT_DURATION	= 3091,		//몬스터의 데미지액션 시간 저장용
	AT_DAMAGEACTION_RATE	= 3092,		//몬스터 데미지 액션 할 확률. 10000분율. AT_DAMAGEACTION_TYPE(3039)어빌이 있어야 동작함
	AT_AI_TARGETTING_TYPE	= 3093,		//AI가 어떤 타겟팅 타입을 가질지 결정하는 어빌
	AT_AI_TARGETTING_SECOND_TYPE	= 3094,	//타겟팅 타입중 Hi/Low를 결정
	AT_AI_TARGETTING_THIRD_TYPE		= 3095,	//타겟팅 세번재 옵션
	AT_AI_TARGETTING_CHASE			= 3097,	//Chase할 때 사용할 타겟팅 옵션
	AT_AI_TARGETTING_RATE			= 3100,	//타겟팅을 할 확률. 만분률

	AT_CLASS_PARTY_BUFF_01	= 3101,		//클래스 별로 가지는 파티 버프 Def_Class에서 사용
	AT_CLASS_PARTY_BUFF_02	= 3102,
	AT_CLASS_PARTY_BUFF_03	= 3103,
	AT_CLASS_PARTY_BUFF_04	= 3104,
	AT_CLASS_PARTY_BUFF_05	= 3105,
	AT_CLASS_PARTY_BUFF_06	= 3106,
	AT_CLASS_PARTY_BUFF_07	= 3107,
	AT_CLASS_PARTY_BUFF_08	= 3108,
	AT_CLASS_PARTY_BUFF_09	= 3109,
	AT_CLASS_PARTY_BUFF_10	= 3110, //AT_CLASS_PARTY_BUFF_01 - 10 까지 사용

	AT_EXCEPT_EFFECT_TICK	= 3111, //해당 번호의 이펙트의 틱 효과를 막아준다.
	AT_EXCEPT_CHAOS_EFFECT_TICK	= 3112, //해당 번호의 이펙트의 카오스 버프를 막아준다.
	AT_NOT_DELETE_EFFECT = 3121, // 특정 조건에서 지워지지 않는 Effect Type인가?(0 : 죽으면 삭제 / 1 : Clear시에 사라지지 않음) / Duration및 직접적인 DeleteEffect 호출시에만 삭제
	AT_DAMAGE_RESETTICK_EFFECT = 3122, // 해당 이펙트가 걸려있는 상태에서 Damage를 입으면 TickTime이 초기화 됨
	AT_IGNORE_REQ_USER_DEL_EFFECT = 3123,	// 유저 요청으로 삭제 할 수 없는 이펙트
	AT_IGNORE_SKILLLV_TOOLTIP = 3124, // 스킬 툴팁 표시할때 LV표시 하지 않음

	AT_PENETRATION_USE_TYPE = 3125, // 관통을 사용하는 타입 0 : 사용하지 않음 / 1 : 관통을 사용
	AT_PROJECTILE_NUM = 3126,		// 발사체를 몇발을 쏘는지 세팅하는 어빌
	AT_IGNORE_GLOBAL_COOLTIME = 3127, // 글로벌 쿨타임을 무시하고 스킬 사용 가능( 1 이면 무시 )
	AT_IGNORE_REFLECTED_DAMAGE_SKILL = 3128, // 데미지 반사 스킬을 무시(1이면 무시)

	AT_CURE_NOT_DELETE = 3129, // 큐어 마법에 지워지지 않도록 하는 어빌( 0 : 지워짐 / 1 : 큐어에 안지워짐 <큐어는 디버프만 지움 : 디버프에 추가 하면 됨>)
	AT_ONDAMAGE_DEL_EFFECT = 3130, //데미지를 받게 되면 해당 이펙트를 제거함

	AT_HP_RECOVERY_TICK_ITEM_AMOUNT = 3131, // 아이템 먹을 시 틱동안 회복되는 최대량(UI표시용)
	AT_MP_RECOVERY_TICK_ITEM_AMOUNT = 3132, // 아이템 먹을 시 틱동안 회복되는 최대량(UI표시용)

	AT_NAME_COLOR						= 3133, // 이름표시 색깔(클라용), 디비에 int형으로 값을 넣어야 하기 때문에 레드이름을 표시하기 위해서 -65536(0xFFFF0000)로 설정해야 됨
	AT_CUSTOM_TARGET_DAMAGE_UNITTYPE	= 3134, // 먹는 데미지에 증감할 타켓 타입
	AT_CUSTOM_TARGET_DAMAGE_RATE		= 3135, // 먹는 데미지에 증감될 상대값

	AT_FIRESKILL_NO_DAMAGEACTION		= 3136, // 스킬 시전중에 데이미액션을 하는지 유무
	AT_FIRESKILL_NO_TARGET				= 3137, // 스킬 시전시 타켓 정보를 보내주지 않음(PgForceSequenseFireSkillFunction 발동시 두번째 스킬에 해당 어빌을 세팅하면 타겟을 상대로 스킬이 발동되지 않고 바라보는 방향으로 스킬이 시전됨)

	AT_EXCEPT_DAMAGE_FONT = 3139, // 예외적인 데미지 폰트 처리(이 어빌이 있는 타겟은 번호에 따라 다른 연출을 해주어야 한다.)

	AT_DEFAULT_EFFECT	= 3140,// Unit이 Add되자마자 걸려 있는 이펙트

	AT_SHOW_EFFECT_TIME	= 3141,			// 이 어빌이 0이 아니면 이펙트 시간을 화면에 보여주자
	AT_SHOW_EFFECT_TIME_ATTR = 3142,	// AT_SHOW_EFFECT_TIME어빌이 있는 이펙트가 사라질 때 화면 연출을 어떻할것인가.EBT_BAR_TWINKLE=1, EBT_SCREEN_BLINK=2 둘다는 3. 없으면 2

	AT_EFFECT_BEGIN_SEND_TTW_MSG = 3143,	// 이펙트에서 해당 번호의 TTW 번호가 있으면 클라이언트로 메시지를 보내준다.(이펙트 시작시에)
	AT_EFFECT_END_SEND_TTW_MSG = 3144,		// 이펙트에서 해당 번호의 TTW 번호가 있으면 클라이언트로 메시지를 보내준다.(이펙트 끝날시에)
	
	AT_HP_DEC_MAX_HP_RATE = 3145,	// HP를 MaxHP의 %만큼 감소 : MaxHP의 %만큼 감소(감소량을 입력해야한다. MaxHP의 10% 만큼 감소라면 -1000 입력)
	AT_MP_DEC_MAX_MP_RATE = 3146,	// MP를 MaxMP의 %만큼 감소 : MaxMP의 %만큼 감소(감소량을 입력해야한다. MaxMP의 10% 만큼 감소라면 -1000 입력)
	
	AT_UNABLE_EFFECT_PC				= 3147, // AddEffect 제한 조건(값: 비트연산)(참고: CUnit::AddEffect)
	AT_UNABLE_EFFECT_PC_INTERVAL	= 3148, // AddEffect 제한 조건(값: 비트연산)(참고: CUnit::AddEffect)

	AT_ATTACK_EFFECTNUM01 = 3150, // 공격시에 사용되는 이펙트( 특정 스킬 발동시 공격마다 이펙트를 거는 경우 )
	AT_ATTACK_EFFECTNUM02 = 3151, 
	AT_ATTACK_EFFECTNUM03 = 3152, 
	AT_ATTACK_EFFECTNUM04 = 3153, 
	AT_ATTACK_EFFECTNUM05 = 3154, 
	AT_ATTACK_EFFECTNUM06 = 3155, 
	AT_ATTACK_EFFECTNUM07 = 3156, 
	AT_ATTACK_EFFECTNUM08 = 3157, 
	AT_ATTACK_EFFECTNUM09 = 3158, 
	AT_ATTACK_EFFECTNUM10 = 3159, 

	AT_ATTACK_EFFECTNUM01_RATE = 3160, // AT_ATTACK_EFFECTNUM01가 걸릴 확률 없으면 100% ( 모든 등급에 동일하게 적용 되는 어빌 / 3940~3979 까지 등급에 따라 다르게 적용되는 확률 어빌임 )
	AT_ATTACK_EFFECTNUM02_RATE = 3161,
	AT_ATTACK_EFFECTNUM03_RATE = 3162,
	AT_ATTACK_EFFECTNUM04_RATE = 3163,
	AT_ATTACK_EFFECTNUM05_RATE = 3164,
	AT_ATTACK_EFFECTNUM06_RATE = 3165,
	AT_ATTACK_EFFECTNUM07_RATE = 3166,
	AT_ATTACK_EFFECTNUM08_RATE = 3167,
	AT_ATTACK_EFFECTNUM09_RATE = 3168,
	AT_ATTACK_EFFECTNUM10_RATE = 3169,

	AT_ATTACK_EFFECTNUM01_TARGET_TYPE_IS_ME = 3170, // 해당 번호의 이펙트를 자신에게 걸어주고 싶다면 1로 세팅
	AT_ATTACK_EFFECTNUM02_TARGET_TYPE_IS_ME = 3171,
	AT_ATTACK_EFFECTNUM03_TARGET_TYPE_IS_ME = 3172,
	AT_ATTACK_EFFECTNUM04_TARGET_TYPE_IS_ME = 3173,
	AT_ATTACK_EFFECTNUM05_TARGET_TYPE_IS_ME = 3174,
	AT_ATTACK_EFFECTNUM06_TARGET_TYPE_IS_ME = 3175,
	AT_ATTACK_EFFECTNUM07_TARGET_TYPE_IS_ME = 3176,
	AT_ATTACK_EFFECTNUM08_TARGET_TYPE_IS_ME = 3177,
	AT_ATTACK_EFFECTNUM09_TARGET_TYPE_IS_ME = 3178,
	AT_ATTACK_EFFECTNUM10_TARGET_TYPE_IS_ME = 3179,

	AT_MON_DEFAULT_ANGLE		= 3180,		//몬스터가 리젠되었을 때 바라볼 각도
	AT_MON_ANGLE_FIX			= 3181,		//몬스터가 리젠되었을 때 바라본 각도를 고정시킬것이냐
	AT_MON_OPENING_TIME			= 3182,		//몬스터 오프팅 시간. 없으면 3000ms

	AT_CREATE_ENTITY_RANGE		= 3183,		//기준으로 부터 소환체 소환 위치
	AT_GROWTH_SKILL_RANGE		= 3184,		//타켓을 찾을 때 범위증가를 할 것인지 유무
	AT_DETECT_RANGE_Z			= 3185,		//타겟을 찾을 때 사용할 Z좌표 차이. 0이면 AI_Z_LIMIT을 사용
	AT_ABV_SIZE_RATE			= 3186,		//클라에서 충돌구 수정될 위치
	AT_DETECT_RANGE_RATE		= 3187,		//스킬인식 범위 확장
	AT_ATTACK_RANGE_RATE		= 3188,		//
	AT_CREATE_SUMMON_DIR		= 3189,		//리젠되었을 때 바라볼 타입
	
	AT_PROJECTILE_IGNORE_DOT_TARGET	= 3190,		//타겟이 발사체 뒤에있어도, 자동적으로 발사체를 삭제 하지 않는다(직선으로 움직이지 않는 발사체 사용시 필요)
	AT_PROJECTILE_DAMAGE_ACTION_NO	= 3191,		//발사체의 액션 번호와 실제 데미지 액션 번호가 다른 경우

	AT_REVIVE_COUNT				= 3192,	//!소생 카운트
	AT_PREV_REVIVE_COUNT		= 3193, //@이전 소생 카운트(값이 변하는것을 알기 위해서)
	AT_REVIVE_EFFECT			= 3194, //@소생 상태 이펙트
	AT_ADD_EFFECT_DURATIONTIME	= 3195, //!이펙트 유지시간 증감
	AT_ADD_BLESSED_DURATIONTIME	= 3196, //@버프 이펙트 유지시간 증감
	AT_ADD_CURSED_DURATIONTIME	= 3197, //@디버프 이펙트 유지시간 증감

	AT_EQUIP_WEAPON_PHY_ATTACK_MIN = 3201, // 현재 장비한 무기의 물리 공격력 최소
	AT_EQUIP_WEAPON_PHY_ATTACK_MAX = 3202, // 현재 장비한 무기의 물리 공격력 최대
	AT_EQUIP_WEAPON_MAGIC_ATTACK_MIN = 3203, // 현재 장비한 무기의 마법 공격력 최소
	AT_EQUIP_WEAPON_MAGIC_ATTACK_MAX = 3204, // 현재 장비한 무기의 물리 공격력 최대

	AT_ITEM_ATTACK_ADD_RATE			= 3208, //!아이템 공격력 증폭
	AT_ITEM_DEFENCE_ADD_RATE		= 3209, //!아이템 방어력 증폭

	AT_ITEM_DROP_CONTAINER			 = 3210, // 이 어빌이 설정된 몬스터는 맵백, 몬스터백 모두 사용하지 않는다.
	AT_ITEM_DROP_CONTAINER_EXPENSION = 3211, // AT_ITEM_DROP_CONTAINER 외에 추가로 ITEM_CONTAINER가 필요한 몬스터

	AT_MIN_DROP_ITEM_COUNT_EXPENSION = 3212, // 원정대 보스가 몇개의 특별 보상 아이템을 드랍 하는지(최소).
	AT_MAX_DROP_ITEM_COUNT_EXPENSION = 3213, // 원정대 보스가 몇개의 특별 보상 아이템을 드랍 하는지(최대).

	AT_EVENT_MONSTER_DROP			 = 3214, // 이벤트 몬스터. 이 어빌이 적용되면 이벤트 몬스터 아이템 테이블 사용.
	AT_EVENT_PARENT_MONSTER			 = 3215, // 이벤트 몬스터. 자신을 소환한 최상위 몬스터 번호.
	AT_EVENT_MONSTER_DROP_GROUP_NO	 = 3216, // 리젠 정보가 없이 생성된 이벤트 몬스터가 드랍할 아이템 그룹 번호.
	AT_EVENT_MONSTER_DROP_ITEM_COUNT = 3217, // 리젠 정보가 없이 생성된 이벤트 몬스터가 드랍할 아이템 카운트.
	AT_EVENT_MONSTER_NO_HAVE_GENINFO = 3218, // 리젠 정보가 없는 이벤트 몬스터. 위 두개를 이용해서 아이템 드랍 정보를 구해야한다.

//OnEffectProc를 이용하여 처리
	AT_DMG_ADD_EFFECT_01		= 3220, // 피격시 이펙트를 걸어준다. (10개씩 예약 ~ 3229)
	AT_DMG_ADD_EFFECT_01_RATE	= 3230, // 피격시 이펙트를 걸어줄 확률. (10개씩 예약 ~ 3239)
	AT_DMG_ADD_EFFECT_01_TARGET_TYPE_IS_ME = 3240, // 피격시 이펙트를 거는 것이 자신인가?. (10개씩 예약 ~ 3249)

	AT_CRITICAL_HIT_ADD_EFFECT_01		= 3250, // 크리티컬 공격시 이펙트를 걸어준다. (10개씩 예약 ~ 3259)
	AT_CRITICAL_HIT_ADD_EFFECT_01_RATE	= 3260, // 크리티컬 공격시 이펙트를 걸어줄 확률. (10개씩 예약 ~3269)
	AT_CRITICAL_HIT_ADD_EFFECT_01_TARGET_TYPE_IS_ME = 3270, // 크리티컬 공격시 이펙트를 거는 것이 자신인가?. (10개씩 예약 ~ 3279)
	//
	AT_ROAD_MIN_TIME                = 3290, // Monster Road Min time
	AT_ROAD_MAX_TIME                = 3291, // Monster Road Min time
	AT_ROADPOINT_GROUP              = 3292, // 몬스터가 현재 가진 RoadPoint의 Group
	AT_ROADPOINT_INDEX              = 3293, // 몬스터가 현재 가진 RoadPoint의 index
	AT_ROADPOINT_INDEX_FROM         = 3294, // RoadPoint 이동경로 시작 Index
	AT_ROADPOINT_DELAY              = 3295, // RoadPoint 도착후 딜레이 시간
	AT_ROADPOINT_DELAY_RESERVED     = 3296, // RoadPoint 도착후 딜레이 시간 정의값
	AT_AI_ROAD_BREAKAWAY     		= 3297, // AI_Road를 타는 도중 적을 발견하면 더이상 AI_Road를 타지 않도록 하는 어빌

	AT_MARKET_HISTORY_POINT	= 3301,			// 마켓 역사 포인트
	AT_MARKET_ONLINE_TIME = 3302,			// 마켓 온라인 유지 시간
	AT_MARKET_OFFLINE_TIME = 3303,			// 마켓 오프라인 유지 시간
	AT_MARKET_OPEN_TYPE = 3304,				// 마켓 오픈 타입 (0: 마켓 오픈 티켓이 아님, 1: 좋은 상점, 2: 역사 깊은 상점)

	AT_MON_SKILL_SECOND_01			= 3310,	// AI가 직접 부르지 않는 스킬 목록
	AT_MON_SKILL_SECOND_02			= 3311,
	AT_MON_SKILL_SECOND_03			= 3312,
	AT_MON_SKILL_SECOND_04			= 3313,
	AT_MON_SKILL_SECOND_05			= 3314,
	AT_MON_SKILL_SECOND_06			= 3315,
	AT_MON_SKILL_SECOND_07			= 3316,
	AT_MON_SKILL_SECOND_08			= 3317,
	AT_MON_SKILL_SECOND_09			= 3318,
	AT_MON_SKILL_SECOND_10			= 3319,

	AT_MON_SKILL_CALLBY_SKILL		= 3320,	//이 번호에 해당하는 스킬을 강제로 부른다.
	AT_MON_SKILL_UNIT_TYPE			= 3321,	//스킬에서 유닛의 타입이 필요한 경우
	AT_MON_SKILL_MONSTER_NO			= 3322, //스킬에서 몬스터 번호가 필요한 경우
	AT_MON_SKILL_AFTER_DIE			= 3323, //스킬을 사용하고 나서 죽는다.
	AT_MON_SKILL_ON_FIRST			= 3324,	//몬스터가 가장 먼저 써야 하는 스킬. 강제로 스킬큐에 넣어준다
	AT_MON_SKILL_TARGET_NO			= 3325,	//스킬 적용 타켓 넘버(몬스터 or 클래스번호)
	AT_MON_SKILL_TARGET_NO_02		= 3326,	//스킬 적용 타켓 넘버(몬스터 or 클래스번호)
	AT_MON_SKILL_TARGET_NO_03		= 3327,	//스킬 적용 타켓 넘버(몬스터 or 클래스번호)
	AT_MON_SKILL_TARGET_TYPE		= 3328, // 3325~3327 까지의 타겟에게, 3328값이 0이면 그것들만 포함, 1보다 크면 그것 들만 제외(현재 소환사가 소환체 소환할때 버프걸때만 적용됨)

	AT_TARGET_ME_EFFECTNUM			= 3329, //자신에게 걸 이펙트 번호
	AT_MON_SKILL_FORCE_MOVE_DIR		= 3330, // 강제이동, 0:사용안함, 1:왼쪽(패스), 2:오른쪽

	AT_MON_ENTITY_NOT_TRANS_SKILL1	= 3331, // 엔터티가 add 될때 다음 액션을 skill1 으로 예약하는것을 방지(클라이언트)

	AT_MON_RESULT_KILL_ALL			= 3332,	// 정예 몬스터가 죽을때 강제로 잡몹들도 다 죽이자. 인던때문데
	AT_MON_RESULT_MOVE_MAP_NUM		= 3333, // 정예 몬스터가 죽은후 미동할 맵 번호
	AT_MON_RESULT_MOVE_MAP_TIME		= 3334, // 정예 몬스터가 죽은후 이동할 때 까지 대기 시간

	AT_MON_ADD_REMOVE				= 3335, // add : 0, remove : 1 : 가능하면 범용으로 사용
	AT_MON_EFFECT_REITERATE			= 3336, // 이펙트 중첩 횟수

	AT_MON_ADD_HP_RATE				= 3338, // HP 회복시 최대치 기준으로 회복되는 비율, 만분률

	AT_MON_CROSS_ATTACK_ANGLE		= 3339, // x 공격의 회전 각도, ( ~ 90도)

	AT_MON_CAN_TARGET_NO_DELAY		= 3340, // 타겟 판단시 딜레이를 무시하고 선택될수 있다.

	AT_MON_PROJECTILE_NUM			= 3341, // 발사하는 발사체 갯수
	AT_MON_PROJECTILE_RANDOM		= 3342, // 최대 발사체 갯수이하로 임의로 갯수가 변하는지 여부(0:변함없다, 1:변한다)
	
	AT_MON_PROJECTILE_ALREADY_SET	= 3343, // 발사체데이타를 이미 세팅했다.
	AT_MON_PROJECTILE_ANGLE			= 3344, // 발사체끼리의 각도

	AT_MON_TRANSFORM_COUNT			= 3350,	// 몬스터가 변신한 횟수
	AT_MON_TRANSFORM_CLASS_01		= 3351,	// 몬스터가 처음 변신한 클래스 번호
	AT_MON_TRANSFORM_CLASS_02		= 3352,	// 몬스터가 두번째 변신한 클래스 번호
	AT_MON_TRANSFORM_CLASS_03		= 3353,	// 
	AT_MON_TRANSFORM_CLASS_04		= 3354,	// 
	AT_MON_TRANSFORM_CLASS_05		= 3355,	// 
	AT_MON_TRANSFORM_CLASS_06		= 3356,	// 
	AT_MON_TRANSFORM_CLASS_07		= 3357,	// 
	AT_MON_TRANSFORM_CLASS_08		= 3358,	// 
	AT_MON_TRANSFORM_CLASS_09		= 3359,	// 
	AT_MON_TRANSFORM_CLASS_10		= 3360,	// 
	AT_MON_TRANSFORM_CLASS			= 3361,	//이펙트어빌. 변신할 클래스 번호.
	AT_ADJUST_PARTICLE_SCALE_BY_UNIT_SCALE	= 3370,	// 클라이언트에서 파티클을 붙일때 DB(3045어빌)로 인해 커진 사이즈만큼 파티클 크기를 조정함
	AT_SKILL_SUMMON_MONBAGCONTROL_01 = 3371, // 스킬로 소환할 몬스터 백 (3038 확장)
	AT_SKILL_SUMMON_MONBAGCONTROL_10 = 3380, // 10 개까지

	AT_GROGGY_MAX						= 3381,	//!분노/그로기 최대값
	AT_FRENZY_R_FIRE					= 3382,	//!분노발동 기준(만분률)(1000이면 최대체력의 10%에 분노상태로 전이)
	AT_FRENZY_RECOVERY					= 3383,	//!분노 자동감소 값
	AT_GROGGY_RECOVERY					= 3384,	//!그로기 자동감소 값
	//AT_INIT_EFFECT_NO					= 3385,	//!초기상태에서 발동되는 이펙트
	AT_NORMAL_SKILL_NO					= 3386,	//!일반상태로 전이 시 발동되는 이펙트
	AT_FRENZY_SKILL_NO					= 3387,	//!분노상태로 전이 시 발동되는 이펙트
	AT_GROGGY_SKILL_NO					= 3388,	//!그로기상태로 전이 시 발동되는 이펙트

	AT_SKILL_SUMMON_MONBAGCONTROL_TYPE		= 3389,
	AT_SKILL_SUMMON_MONBAGCONTROL_RATE		= 3390,
	AT_SKILL_SUMMON_MONBAGCONTROL_RATE_01	= 3391, // 스킬로 소환할 몬스터 백 (3038 확장)
	AT_SKILL_SUMMON_MONBAGCONTROL_RATE_10	= 3400, // 10 개까지

	AT_ADD_ATTACK_COOL_TIME = 3401,			// 공격 쿨타임 추가(천분률)
	AT_ADD_TICK_ATTACK_TIME = 3402,			// 클라이언트에서 Tick당 공격하는 스킬의 Tick 타임을 추가로 조절(천분률)
	AT_ADD_MOVESPEED_BY_DELAY = 3403,		// 네트웍 딜레이에 따른 이동속도 조절값. 클라이언트용

	AT_MON_REMOVE_EFFECT_FORCESKILL	= 3404, // 몬스터용, 이펙트(버프)가 해제 될때 강제 발동할 스킬(이펙트에 설정 되어있어야 함)
	AT_MON_BEGIN_EFFECT_FORCESKILL	= 3405, // 몬스터용, 이펙트(버프)가 시작 될때 강제 발동할 스킬(이펙트에 설정 되어있어야 함)
	AT_REMOVE_SKILL_FORCEEFFECT		= 3406, // 스킬종료후 시작될 강제이펙트
	AT_MON_ADD_FORCESKILL			= 3407, // 강제로 스킬 등록(타이밍은 각 함수에 따라 다름)
	AT_PAUSE_TELEPORT_TO_DUMMY_EFFECT	= 3408,	//PgTeleportToDummyEffect Tick 체크시 일시정지용 
	AT_AI_FIRE_ONENTER_ADDEFFECT	= 3409,	// 스킬시작 할때 적용될 이펙트

	AT_SKILL_AGGRO_RATE		= 3410,			// 스킬의 어그로율. 데미지에 곱할 만분률
	AT_IS_COUPLE_SKILL		= 3420,			// 커플스킬 종류인가?
	
	AT_R_COOLTIME_RATE_SKILL= 3421,			// 스킬 쿨타임 적용 천분율값
	AT_R_COOLTIME_RATE_ITEM	= 3422,			// 아이템 사용 쿨타임 적용 천분율값

	AT_USE_INV_SORT_TIME = 3423,	// 인벤토리 정렬을 사용한 시간( DOS 공격 방지 2초에 한번씩만 사용 할 수 있게 )
	
	AT_FORCESKILL_FLAG				= 3430,	//강제스킬의 Flag값
	AT_IGNORE_NOW_FIRESKILL_CANCEL	= 3431,	//강제스킬에 의해서 지금 스킬이 취소되는 것을 막음
	AT_MON_CHILD_DIE				= 3432,	//죽을때 자식으로 태어난 몬스터 같이 죽이기
	AT_AI_SKILL_FIRE_TIME			= 3433,	//스킬이 발동된 시간
	AT_AI_SKILL_FIRE_TERM			= 3434,	//스킬발동이 여러번 일어날때 딜레이 값

	AT_EFFECT_ESCAPE		= 3440,	// 키를 통해서 이펙트를 해제할 수 있는 이펙트 유무
	AT_EFFECT_ESCAPE_MIN	= 3441,	// 랜덤 최소값
	AT_EFFECT_ESCAPE_MAX	= 3442,	// 램덤 최대값
		
	AT_SKILL_CHOOSE_IS_IN_CLASS_NO		= 3445, //스킬선택시 해당 클래스가 없으면 발동되지 않도록 체크
	AT_SKILL_CHOOSE_IS_IN_CLASS_TYPE	= 3446,
	AT_USE_IS_ALLY_SKILL			= 3447,	//아군이 있어야 스킬이 발동
	AT_USE_NOT_PROJECTILE_SKILL		= 3448, //발사체 스킬인 경우 스킬이 발동되지 않도록 막음
	AT_USE_LOCK_SKILL 		= 3449, // 락 스킬 사용유무
	AT_LOCK_SKILLNO_01 		= 3450, // 락걸 스킬 번호
//AT_LOCK_SKILLNO 10개 사용(3450~3459)
	AT_LOCK_SKILLNO_10 		= 3459,

	AT_AI_SKILL_FIRE_TERM_00 		= 3460, //!스킬 발동 딜레이 카운드에 따른 확장 정보, 00은 사용하지 않음. 이유는 첫번째 텀은 무시되기 때문
//AT_AI_SKILL_FIRE_TERM_00 10개 사용(3460~3469)
	AT_AI_SKILL_FIRE_TERM_09 		= 3469,

// 각성기
	AT_ENABLE_AWAKE_SKILL	= 3500,	// 각성기 시스템을 활성화
	AT_AWAKE_STATE			= 3501,	// 각성기 게이지 상태(0 : 일반상태(스킬 사용시 채워지거나, 시간당 자동 감소), 1: 맥스 상태, 2: 소모 상태(게이지 회복X)
	AT_AWAKE_VALUE			= 3502,	// 각성기 게이지 값
	AT_AWAKE_TICK_DEC_VALUE	= 3503,	// Tick마다 감소하는 게이지 값
	AT_NEED_AWAKE			= 3504,	// 스킬 사용시 사용하는 각성기 게이지
	AT_NEED_MAX_R_AWAKE		= 3505,	// 스킬 사용시 사용하는 각성기 게이지 (Max의 %로 사용)(만분률).
	AT_ADD_NEED_R_AWAKE		= 3506, // 스킬 시전시 사용하는 각성기 게이지를 %로 증감 시긴다.(만분률) AT_NEED_AWAKE * AT_ADD_R_NEED_HP / ABILITY_RATE_VALUE_FLOAT
	AT_ALL_NEED_AWAKE		= 3507,	// 스킬 사용시 남아있는 모든 각성기 게이지 소모
	AT_R_INC_AWAKE_VALUE	= 3508, // 각성기 게이지 최대값에 %로 증가하는값(Max의 %로 증가)(만분률)

	AT_AWAKE_SKILL_FIRE_ADD_EFFECT			= 3510, // 각성기 스킬 사용시 걸어주는 이펙트(슈퍼아머 이펙트 번호를 넣어서 걸어준다) 어빌이 없으면 이펙트 삭제
	AT_MASTER_SKILL_FIRE_ADD_EFFECT			= 3511, // 궁극기 스킬 사용시 걸어주는 이펙트(무적 이펙트 번호를 넣어서 걸어준다) 어빌이 없으면 이펙트 삭제	
	
	AT_EMPTY_AWAKE_VALUE = 3520,	// 1이상이면 해당 스킬을 사용해도 각성치가 증가하지 않음

	AT_AWAKE_CHARGE_STATE				= 3550,
	AT_IS_DAMAGED_DURING_AWAKE_CHARGE	= 3551,

// 스킬 제약
	AT_CANT_USE_THIS_GATTR_FLAG = 3600,	// 이 그라운드에서는 스킬을 사용 할 수 없음(FLAG 값) 
	
	AT_CANT_SKILL_ALIVE_UNIT_NO	= 3601,	//해당유닛이 살아있으면 스킬을 발동할 수 없다
	AT_AI_SKILL_MAX_COUNT		= 3602, //AI에서 최대 몇번 스킬을 발동할 것인지 지정(기존의 AT_COUNT를 쓴 것이 있으면 찾아서 바꿔주어야 함)
	AT_AI_FIRE_LAST_SKILLNO		= 3603,	//AI Fire에서 발동된 스킬번호를 저장함
	AT_AI_SKILL_USE_COUNT		= 3604, //PgAIActFireSkill::OnEnter에서 초기화, PgGround::AI_SkillFire에서 카운트
	AT_DELETE_EFFECT_NO	= 3605,		// 이펙트 삭제

// 연계 효과
	AT_BEGINL_SKILL_LINKAGE		= 3606,				// 연계효과를 적용 받게 하는 시작 스킬
	AT_SKILL_LINKAGE_POINT		= 3607,				// 연계효과 점수
	AT_USE_SKILL_LINKAGE_POINT	= 3608,				// 연계효과 점수를 사용하는 스킬	
	AT_SKILL_LINKAGE_POINT_MAX	= 3608,				// 연계 포인트 최대 누적값
	AT_SKILL_LINKAGE_POINT_EFFECT_TARGET01 = 3610,	// 연계효과 적용 대상. ESkillTargetType 값과 같음(스킬에 타겟 대상을 비트연산 하는것과 같은 형식의 값을 씀)
	AT_SKILL_LINKAGE_POINT_EFFECT_TARGET02 = 3611,
	AT_SKILL_LINKAGE_POINT_EFFECT_TARGET03 = 3612,
	AT_SKILL_LINKAGE_POINT_EFFECT_TARGET04 = 3613,
	AT_SKILL_LINKAGE_POINT_EFFECT_TARGET05 = 3614,
	AT_SKILL_LINKAGE_POINT_EFFECT_TARGET06 = 3615,
	AT_SKILL_LINKAGE_POINT_EFFECT_TARGET07 = 3616,
	AT_SKILL_LINKAGE_POINT_EFFECT_TARGET08 = 3617,
	AT_SKILL_LINKAGE_POINT_EFFECT_TARGET09 = 3618,
	AT_SKILL_LINKAGE_POINT_EFFECT_TARGET10 = 3619,

	AT_SKILL_LINKAGE_POINT_EFFECT01 = 3620,	//	연계효과 이펙트
	AT_SKILL_LINKAGE_POINT_EFFECT02 = 3621,
	AT_SKILL_LINKAGE_POINT_EFFECT03 = 3622,
	AT_SKILL_LINKAGE_POINT_EFFECT04 = 3623,
	AT_SKILL_LINKAGE_POINT_EFFECT05 = 3624,
	AT_SKILL_LINKAGE_POINT_EFFECT06 = 3625,
	AT_SKILL_LINKAGE_POINT_EFFECT07 = 3626,
	AT_SKILL_LINKAGE_POINT_EFFECT08 = 3627,
	AT_SKILL_LINKAGE_POINT_EFFECT09 = 3628,
	AT_SKILL_LINKAGE_POINT_EFFECT10 = 3629,
	
	AT_SKILL_LINKAGE_FLAG		= 3630,				// 연계 Flag값 저장소( Unit에는 SetAbil64로 저장 )
	AT_SKILL_LINKAGE_CHECK_FLAG	= 3631,				// 연계 Flag값을 각인하기위해 체크할 값
	AT_SKILL_LINAKGE_POINT_CHECK_FLAG = 3632,		// 연계 포인트를 적용하기 위해 체크할 Flag값
	AT_SKILL_LINAKGE_FLAG_REMOVE = 3633,			// 스킬 사용후 Unit의 연계 flag값을 제거할값

	AT_ADD_HP_FROM_MAX_HP_RATE			= 3641,			// MAX HP의 비율로 HP를 회복
	AT_ADD_MP_FROM_MAX_MP_RATE			= 3642,			// MAX MP의 비율로 MP를 회복
	
	AT_DRAIN_HP_APPLY_TARGET			= 3643,			// 적용된 HP의 *-1을 한값을 적용할 대상 (1== 이펙트 건 대상,)
	AT_DRAIN_MP_APPLY_TARGET			= 3644,			// 적용된 MP의 *-1을 한값을 적용할 대상 (1== 이펙트 건 대상,)
	
	AT_DRAIN_HP_APPLY_RATE				= 3645,			// 대상에게 소진시킨 HP 값을 흡수할 비율
	AT_DRAIN_MP_APPLY_RATE				= 3646,			// 대상에게 소진시킨 MP 값을 흡수할 비율

// 스킬 연출 다양화
	AT_SKILL_CUSTOM_CHECK_LEARN_THIS_SKILL_NO	= 3650,	// 이 Value에 해당하는 스킬을 배웠다면(Parent SkillNo), 
	AT_SKILL_CUSTOM_VALUE						= 3651,	// (Skill용!) AT_CUSTOM_SKILL_CHECK_LEARN_THIS_SKILL_NO에 해당하는 스킬을 배웠다면, 이 값에 대한 어빌을 세팅해줌(unit에 세팅)
	AT_SKILL_CUSTOM_VALUE_STORAGE				= 3652,	// (Unit용!) 오직 클라에서만 이값을 사용하며 '비동기'값이다. 클라에서 받아서 처리하고 리셋 시킨다. 서버에서는 필요한 상황에 세팅해서 보내주기만 한다.
//***절대로 AT_SKILL_CUSTOM_VALUE_STORAGE값을 얻어서 서버에서 사용하지 않는다***
//Unit에 AT_CUSTOM_SKILL_CUSTOM_VALUE에 저장된 값을 저장해줄 저장소*/

// 입힌 데미지로 자신을 힐함 ( 어빌을 삭제한 것 같은데. 확인 후 이 주석을 삭제해 주세요 박인걸)

	//AT_ACTIVE_RATE_HP_RESTORE_FROM_DAMAGE	= 3670,			// 얼마만큼의 확률로 데미지를 통한 HP회복을 사용할것인가
	AT_R_HP_RESTORE_FROM_DAMAGE				= 3671,			// 입힌 데미지의 %로 HP 회복
	
	AT_CAN_NOT_BLOCK_BY_EFFECT			  = 3680,		// Effect에 의해서 블록을 할수 없는 상태 
	AT_CAN_NOT_BLOCK_BY_ACTION			  = 3681,		// 액션에 의해서 블록을 할수 없는 상태 
	AT_HIT_AFTER_TARGET_CHANGE_BLOCK_ABLE = 3682,	// 이 어빌이 있는 스킬에 피격후 상대는 블록을 할수 없는 상태가 됨( 1 = 블록 안됨
	AT_ACTION_AFTER_CHANGE_BLOCK_ABLE	  = 3683,	// 이 어빌이 있는 액션 후에 자신은 블록 불가이거나, 블록 가능 상태가 됨 (1 = 블록 안됨, 2 = 블록 가능) 
	AT_PUSH_DIST_WHEN_BLOCK				  = 3684,	// 블록시 밀릴거리
	AT_PUSH_SPEED_WHEN_BLOCK			  = 3685,	// 블록시 밀릴속력
	AT_PUSH_ACCEL_WHEN_BLOCK			  = 3686,	// 블록시 밀릴가속력

// 캐릭터 일부 능력치 임시 저장이 필요할때
	AT_MEMORIZED_HP				= 3701,
	AT_MEMORIZED_MAX_HP			= 3702,
	AT_MEMORIZED_MP				= 3703,
	AT_MEMORIZED_MAX_MP			= 3704,
	AT_PREV_ACTION_ID			= 3705, // 현재 액션 실행 전에 사용했던 액션 번호(서버에서만 씀)
	AT_SKILL_LINKAGE_POINT_SETED= 3706, // 스킬을 사용할때, 스킬에 설정된 연계포인트값을 이미 설정했다.
	
	AT_TARTGET_RE_POS = 3720,			// 타겟의 위치를 내위치로 설정한다(어빌 이름이 적절하지 않지만, 추후 기능이 수정될경우 이것은 위치 재설정의 타입으로 사용할 예정)
	AT_ADDITIONAL_SUMMON_SKILL_NO = 3721,				// 소환시 추가적으로 소환할 스킬 번호(소환스킬이어야함)
	AT_ADDITIONAL_SUMMON_MUST_LEARN_SKILL_NO = 3722,	// 소환시 추가적으로 소환하려고 할때 이 스킬을 배웠어야함

	AT_AI_FIRE_ONENTER_DELEFFECT	= 3727,	//스킬발동시 삭제할 이펙트
	AT_AI_RUN_ACTION_MOVESPEED	= 3728,	// PgAIActFollowCaller: 존 이동속도 적용정보, PgAIActChaseEnemy: 추가된 스피드정보 저장
	AT_FOLLOW_PATTERN			= 3729,	// 따라다닐 타입
	AT_RETURNZONE_RANGE			= 3730,	// 귀환존 크기
	AT_WALKINGZONE_RANGE		= 3731,	// 워킹존 크기
	AT_RUNNINGZONE_RANGE		= 3732,	// 대쉬존 크기(현재는 배틀존 크기도 동일하게 사용)
	AT_WALKINGZONE_SPEED_RATE	= 3733, //워킹존에 적용될 속도(만분율)
	AT_RUNNINGZONE_SPEED_RATE	= 3734, //런닝존에 적용될 속도(만분율)

	AT_RESTORE_WHEN_HIT_TYPE	= 3750, // 타격시 HP,MP 회복 어빌 적용대상(ESkillTargetType 활용)
	AT_RESTORE_WHEN_DAMAGE_TYPE	= 3751, // 타격시 HP,MP 회복 어빌 적용대상(ESkillTargetType 활용)

	AT_RESTORE_WHEN_DAMAGE_DAMAGE_EFFECT	= 3754, // 피격시(피격대상) 이펙트 효과
	AT_RESTORE_WHEN_DAMAGE_RESTORE_EFFECT	= 3755, // 피격시(회복대상) 이펙트 효과

// 이펙트가 주는 데미지가 반사 스킬에의해, 데미지 반사 되어야할 경우, 이 이펙트의 데미지 타입은?( 1=물리, 2=마법)
	AT_EFFECT_DMG_TYPE = 3800,
	AT_END_ACTION_WHEN_EFFECT_DELETED = 3801, //이펙트가 지워질때 종료 해야할 액션이 있다면
	AT_MUST_REFRASH_EFFECT = 3802,				// 이펙트가 유지상태인데, 다시 이펙트를 건다면 Begin()함수를 꼭 타게함

// 스킬이 종료될때 붙여주는 이펙트
	AT_ADD_EFFECT_WHEN_SKILL_END = 3810,
	AT_DEL_SUB_PLAYER			= 3811,	// SubPlayer를 삭제 시키는 어빌
	AT_WHEN_ACTION_END_THEN_TOGGLE_OFF = 3812, // 액션이 끝나면 토글을 종료하는 스킬
	AT_R_PROVOKE_MOVE_SPEED		= 3819,	//AT_PROVOKE_EFFECT_NO 이펙트가 걸린상태에서 쫓아갈 스피드
	AT_PROVOKE_EFFECT_NO		= 3820,	//Effect->Unit어빌. 이 어빌값의 번호에 해당하는 이펙트를 찾아서 이펙트의 캐스터를 우선타겟팅 함.

/// Effect에서 어떤 면역값을 체크 할것인가?(Effect에서 사용하며, DB의 Value에는 체크할 AbilType을 써줌)
/// 8000 ~ 9000 사이의 타입값들을 적어주면, Effect가 걸릴때 해당 값을 체크함
	AT_CHECK_IMMUNITY_TYPE				= 3890,
	AT_ADD_EFFECT_WHEN_SUCCESS_IMMUNITY	= 3891,

// 3900 ~ 3999 Monster Card 추가 효과 어빌들
	AT_MONSTER_CARD_ABIL_MIN = 3900,

	AT_HIT_HEAL_HP_RATE	= 3900,	// Target을 Hit 시에 HP를 회복할 확률 ( 만분률 )
	AT_HIT_HEAL_HP		= 3901,	// Target을 Hit 시에 회복하는 HP ( 절대값 )
	AT_HIT_HEAL_MP_RATE	= 3902,	// Target을 Hit 시에 MP를 회복할 확률 ( 만분률 )
	AT_HIT_HEAL_MP		= 3903,	// Target을 Hit 시에 회복하는 MP ( 절대값 )

	AT_KILL_HEAL_HP_RATE	= 3904,	// Target을 Kill 시에 HP를 회복할 확률 ( 만분률 )
	AT_KILL_HEAL_HP			= 3905,	// Target을 Kill 시에 회복하는 HP ( 절대값 )
	AT_KILL_HEAL_MP_RATE	= 3906,	// Target을 Kill 시에 MP를 회복할 확률 ( 만분률 )
	AT_KILL_HEAL_MP			= 3907,	// Target을 Kill 시에 회복하는 MP ( 절대값 )
	AT_ABS_ADDED_DMG_PHY_2		= 3908,	// Dmg 계산이후 절대값으로 넣어주는 추가 Dmg( 절대값 ) (Physical공격) Effect에 의해서 추가되는 값
	AT_ABS_ADDED_DMG_MAGIC_2	= 3909,	// Dmg 계산이후 절대값으로 넣어주는 추가 Dmg( 절대값 ) (Magic공격) Effect에 의해서 추가되는 값

	AT_PHY_DEFENCE_IGNORE_RATE		= 3910, // 상대방의 물리 방어력을 무시하고 공격 할 확률 ( 만분률 )
	AT_MAGIC_DEFENCE_IGNORE_RATE	= 3911, // 상대방의 마법 방어력을 무시하고 공격 할 확률 ( 만분률 )

	AT_100PERECNT_BLOCK_RATE	= 3912, // 상대방의 공격을 절대 방어할 확률 ( 만분률 ) 물리/마법 방어로 나뉘어질 경우 대비하여 한칸 비워둠

	AT_PHY_DMG_100PERECNT_REFLECT_RATE	= 3914,	// 물리 Damage 100% 반사 확률( 만분률 )
	AT_MAGIC_DMG_100PERECNT_REFLECT_RATE	= 3915,	// 마법 Damage 100% 반사 확률( 만분률 )

	AT_PHY_DMG_SUBTRACT		= 3916,	// 절대적인 물리 데미지 감소 ( 절대값 )
	AT_MAGIC_DMG_SUBTRACT	= 3917,	// 절대적인 물리 데미지 감소 ( 절대값 )
	AT_PROJECTILE_DMG_SUBTRACT	= 3918,	// 발사체일 경우 데미지 감소 ( 절대값 )

	AT_GRADE_NORMAL_DMG_ADD_RATE	= 3920, // 일반 몬스터 타격시 증가할 데미지 = 최종 데미지의 %증가( 만분률 )
	AT_GRADE_UPGRADED_DMG_ADD_RATE	= 3921, // 강화 몬스터 데미지 증가할 데미지 = 최종 데미지의 %증가( 만분률 )
	AT_GRADE_ELITE_DMG_ADD_RATE		= 3922, // 정예 몬스터 데미지 증가할 데미지 = 최종 데미지의 %증가( 만분률 )
	AT_GRADE_BOSS_DMG_ADD_RATE		= 3923, // 보스 몬스터 데미지 증가할 데미지 = 최종 데미지의 %증가( 만분률 )
	
	AT_ADD_ENCHANT_RATE		= 3930,			// 인첸트 성공 확률 증가
	AT_ADD_SOULCRAFT_RATE	= 3931,			// 소울크래프트 성공 확률 증가
	AT_DEC_SOUL_RATE		= 3932,			// 소울 소비 개수 감소
	AT_ADD_SOUL_RATE_REFUND = 3933,			// 아이템 파괴시 소울 환불 확률 증가 
	AT_ADD_REPAIR_COST_RATE		= 3934,			// 수리 비용 증가

// 아래 확률 은 AT_ATTACK_EFFECTNUM01_RATE ~ AT_ATTACK_EFFECTNUM10_RATE 값이 없어야 한다.
// AT_ATTACK_EFFECTNUM01_RATE~ AT_ATTACK_EFFECTNUM10_RATE or 아래 어빌들이 추가 되어야 한다.

	AT_ATTACK_EFFECTNUM01_GRADE_NORMAL_RATE = 3940, // AT_ATTACK_EFFECTNUM01가 Grade Normal 한테 걸릴 확률 없으면 100%
	AT_ATTACK_EFFECTNUM02_GRADE_NORMAL_RATE = 3941,
	AT_ATTACK_EFFECTNUM03_GRADE_NORMAL_RATE = 3942,
	AT_ATTACK_EFFECTNUM04_GRADE_NORMAL_RATE = 3943,
	AT_ATTACK_EFFECTNUM05_GRADE_NORMAL_RATE = 3944,
	AT_ATTACK_EFFECTNUM06_GRADE_NORMAL_RATE = 3945,
	AT_ATTACK_EFFECTNUM07_GRADE_NORMAL_RATE = 3946,
	AT_ATTACK_EFFECTNUM08_GRADE_NORMAL_RATE = 3947,
	AT_ATTACK_EFFECTNUM09_GRADE_NORMAL_RATE = 3948,
	AT_ATTACK_EFFECTNUM10_GRADE_NORMAL_RATE = 3949,

	AT_ATTACK_EFFECTNUM01_GRADE_UPGRADED_RATE = 3950, // AT_ATTACK_EFFECTNUM01가 Grade Upgraded 한테 걸릴 확률 없으면 100%
	AT_ATTACK_EFFECTNUM02_GRADE_UPGRADED_RATE = 3951,
	AT_ATTACK_EFFECTNUM03_GRADE_UPGRADED_RATE = 3952,
	AT_ATTACK_EFFECTNUM04_GRADE_UPGRADED_RATE = 3953,
	AT_ATTACK_EFFECTNUM05_GRADE_UPGRADED_RATE = 3954,
	AT_ATTACK_EFFECTNUM06_GRADE_UPGRADED_RATE = 3955,
	AT_ATTACK_EFFECTNUM07_GRADE_UPGRADED_RATE = 3956,
	AT_ATTACK_EFFECTNUM08_GRADE_UPGRADED_RATE = 3957,
	AT_ATTACK_EFFECTNUM09_GRADE_UPGRADED_RATE = 3958,
	AT_ATTACK_EFFECTNUM10_GRADE_UPGRADED_RATE = 3959,

	AT_ATTACK_EFFECTNUM01_GRADE_ELITE_RATE = 3960, // AT_ATTACK_EFFECTNUM01가 Grade Elite 한테 걸릴 확률 없으면 100%
	AT_ATTACK_EFFECTNUM02_GRADE_ELITE_RATE = 3961,
	AT_ATTACK_EFFECTNUM03_GRADE_ELITE_RATE = 3962,
	AT_ATTACK_EFFECTNUM04_GRADE_ELITE_RATE = 3963,
	AT_ATTACK_EFFECTNUM05_GRADE_ELITE_RATE = 3964,
	AT_ATTACK_EFFECTNUM06_GRADE_ELITE_RATE = 3965,
	AT_ATTACK_EFFECTNUM07_GRADE_ELITE_RATE = 3966,
	AT_ATTACK_EFFECTNUM08_GRADE_ELITE_RATE = 3967,
	AT_ATTACK_EFFECTNUM09_GRADE_ELITE_RATE = 3968,
	AT_ATTACK_EFFECTNUM10_GRADE_ELITE_RATE = 3969,

	AT_ATTACK_EFFECTNUM01_GRADE_BOSS_RATE = 3970, // AT_ATTACK_EFFECTNUM01가 Grade Boss 한테 걸릴 확률 없으면 100%
	AT_ATTACK_EFFECTNUM02_GRADE_BOSS_RATE = 3971,
	AT_ATTACK_EFFECTNUM03_GRADE_BOSS_RATE = 3972,
	AT_ATTACK_EFFECTNUM04_GRADE_BOSS_RATE = 3973,
	AT_ATTACK_EFFECTNUM05_GRADE_BOSS_RATE = 3974,
	AT_ATTACK_EFFECTNUM06_GRADE_BOSS_RATE = 3975,
	AT_ATTACK_EFFECTNUM07_GRADE_BOSS_RATE = 3976,
	AT_ATTACK_EFFECTNUM08_GRADE_BOSS_RATE = 3977,
	AT_ATTACK_EFFECTNUM09_GRADE_BOSS_RATE = 3978,
	AT_ATTACK_EFFECTNUM10_GRADE_BOSS_RATE = 3979,

	AT_GRADE_NORMAL_PHY_DMG_DEC_RATE	= 3980, // 일반 몬스터 피격시 감소할 데미지 % = 최종 물리 데미지의 %감소( 만분률 )
	AT_GRADE_UPGRADED_PHY_DMG_DEC_RATE	= 3981, // 강화 몬스터 피격시 감소할 데미지 % = 최종 물리 데미지의 %감소( 만분률 )
	AT_GRADE_ELITE_PHY_DMG_DEC_RATE		= 3982, // 정예 몬스터 피격시 감소할 데미지 % = 최종 물리 데미지의 %감소( 만분률 )
	AT_GRADE_BOSS_PHY_DMG_DEC_RATE		= 3983, // 보스 몬스터 피격시 감소할 데미지 % = 최종 물리 데미지의 %감소( 만분률 )

	AT_GRADE_NORMAL_MAGIC_DMG_DEC_RATE		= 3984, // 일반 몬스터 피격시 감소할 데미지 % = 최종 마법 데미지의 %감소( 만분률 )
	AT_GRADE_UPGRADED_MAGIC_DMG_DEC_RATE	= 3985, // 강화 몬스터 피격시 감소할 데미지 % = 최종 마법 데미지의 %감소( 만분률 )
	AT_GRADE_ELITE_MAGIC_DMG_DEC_RATE		= 3986, // 정예 몬스터 피격시 감소할 데미지 % = 최종 마법 데미지의 %감소( 만분률 )
	AT_GRADE_BOSS_MAGIC_DMG_DEC_RATE		= 3987, // 보스 몬스터 피격시 감소할 데미지 % = 최종 마법 데미지의 %감소( 만분률 )

	AT_SCREEN_EFFECT_COUNT	= 3998,	//화면에 이미지 붙이는 버프에 적용. 몇개나 뿌릴지. 클라이언트 전용 어빌
	AT_MONSTER_CARD_ABIL_MAX = 3999,

//Skill /Effect Abil 3060 ~ 3999까지 사용 예정 ~!!!!!!
		
	AT_APPLY_EFFECT_MSG		= 4000,	// 내 플레이어가 이펙트 걸릴때 이펙트의 메세지를 보여준다
	AT_USE_EFFECT_MSG_BY_STRINGNO	= 4001,	// 내 플레이어에게 이펙트 걸릴때, 이 값의 번호를 DefString에서 찾아 이름으로 사용한다
	AT_APPLY_EFFECT_MSG_TYPE		= 4002, //AT_APPLY_EFFECT_MSG 메시지타입(EEffectMsgType)
	AT_CHECK_OVERLAP_MSG	= 4003, //ECheckOverlapMsgType

	AT_GRADE				= 4007,	// Pet/Monster/Item 의 등급
	AT_USE_ENERGY_GAUGE_BIG	= 4008,//에너지 게이지 큰거 쓸건지

	AT_BASE_CLASS			= 4009,
	AT_NO_BOSS_HP_HIDE		= 4010, // 에너지 게이지 AliveTime 사용 안함
	AT_MON_ENCHANT_GRADE_NO	= 4011,	// 몬스터 인챈트 번호
	AT_MON_ENCHANT_LEVEL	= 4012, // 몬스터 인챈트 레벨
	AT_MON_ENCHANT_PROB_NO	= 4013,	// 몬스터 인챈트 확율 번호
	AT_NO_ENCHNAT_MONSTER	= 4014,	// 인챈트 몬스터화 하지 않음

	AT_USE_ACCUMULATE_DAMAGED	= 4030, //누적데미지 사용
	AT_ACCUMULATE_DAMAGED_NOW	= 4031, //현재 누적데미지
	AT_ACCUMULATE_DAMAGED_MAX	= 4032, //최대 누적데미지

// Pet의 특수한 타입
	AT_INVEN_PET_ADD_TIME_EXP_RATE		= 4060,	// 시간당 Pet 경험치 증가시에 추가 증가
	AT_INVEN_PET_ADD_HUNT_EXP_RATE		= 4061,	// 사냥으로 Pet 경험치 증가시에 추가 증가

	AT_PET_CHOOSE_RAND_COLOR_MAX = 4070, //펫 랜덤 염색 사용(N>0이면, 랜덤 최대값. N=0이면, 미사용)

	AT_TIME					= 4090,
	AT_EXPERIENCE_TIME		= 4091,//일정 시간당 얻는 경험치
    AT_ENTITY_SECOND_TYPE   = 4092,//엔티티 세컨드 타입 (EEntitySecondType참고)
	AT_COLOR_INDEX			= 4100,

// Pet Ability
	//AT_HUNGER				= 4101,
	AT_HEALTH				= 4102,
	AT_MENTAL				= 4103,

// Unit의 특수한 상태 정의의의의~~~
	AT_DAMAGE_IS_ONE_ALPHA 			= 4198, // AT_DAMAGE_IS_ONE + 추가 데미지
	AT_CANNOT_DAMAGE_BY_GUARDIAN	= 4199, // 가디언이 해당 유닛을 공격하지 못하게 하는 어빌
	AT_DAMAGE_IS_ONE				= 4200, // 데미지가 1씩 들어가도록 함
	AT_UNIT_HIDDEN			= 4201,	// 숨어있는 상태 (다른 Player에게 보이지 않는다)
	AT_ENABLE_AUTOHEAL		= 4202,	// AutoHeal 할 것인가? 0x01:HP, 0x02:MP, 0x04:DP
	AT_FIXED_MOVESPEED		= 4203,	// MoveSpeed 변경 금지~~
	AT_CANNOT_DAMAGE		= 4204,	// 공격 받지 않는다.
	AT_FROZEN				= 4205,	// 움직일 수 없다(그러나 한대라도 맞으면 움직일 수 있다)
	AT_CANNOT_ATTACK		= 4206, // 공격 할 수 없다.
	AT_FROZEN_DMG_WAKE		= 4207,	// Frozen 상태일 때 Damage를 받으면 Frozen 상태가 풀릴것인가? (>0:풀린다.)
	AT_CANNOT_USEITEM		= 4208,	// 아이템을 사용 할 수 없는 상태이다.
	AT_CANNOT_EQUIP			= 4209,	// 장비아이템(장착/해제) 금지된 상태
	AT_CANNOT_CASTSKILL		= 4210,	// Casting Type 스킬 사용 금지
	AT_CRITICAL_ONEHIT		= 4211,	// 다음 공격에 있어 무조건 Critical 공격이 된다.
	AT_CANNOT_SEE			= 4212,	// 주변을 볼수 없게 됨
	AT_QUEST_TALK			= 4213,	// 퀘스트 대화 중인 플레이어다 (0: IDLE, 1: Talking)
	//AT_LOOTED_ITEM			= 4214,	// 이미 주인이 결정된 그라운드 아이템이다 (0: None, 1: Looted)
	AT_FAKE_REMOVE_UNIT		= 4215, // 가상으로 맵에서 삭제된 플레이어이다.(실제로는 HIDE 와 CANNOT ATTACK 등으로 유저에게 보이지 않게 구현되어 있음)
	AT_EVENT_SCRIPT			= 4216,	// 클라이언트 측 이벤트 스크립트가 실행중이다
	AT_EVENT_SCRIPT_TIME	= 4217,	// 클라이언트 측 이벤트 스크립트가 실행한 시간.
	AT_INVINCIBLE			= 4218, // AT_CANNOT_DAMAGE은 타겟이 되지 않지만, AT_INVINCIBLE은 때릴수 있으나 데미지가 0이 된다.
	AT_INVINCIBLE2			= 4219,	// AT_INVINCIBLE와 틀린것은 헛침 처리가 되지 않고, 맞기까지 하나 HP만 안단다(현재 파괴오브젝트만  사용)
	AT_SKILL_SPECIFIC_IDLE	= 4220, // 특정 아이들을 한다.
	AT_ENABLE_CHECK_ATTACK	= 4221, // 타겟을 공격할 때 공격여부를 체크할지 결정
	AT_CHECK_ATTACK_COUNT	= 4222, // 공격을 했는지 체크( 공격할때마다 증가 )
	AT_DARKNESS				= 4223, // 암흑(카오스 맵 스팟 라이트)
	AT_TIME_LIMIT			= 4224,	// 몬스터(젠 될 시에, 해당 맵에 시간제한이 걸린다)
	AT_NOT_COUNT			= 4225,	// 슈퍼던젼에서 남은 몬스터 수량에 포함시키지 않는다
	AT_AI_SYNC				= 4226,	// AI 싱크 요청
	AT_AI_FIRE_ONLEAVE_NO_CLEAR_TARGETLIST = 4227, //맵서버에서 AI Fire::OnLeave될때 타켓리스트를 초기화 할 지 유무
	AT_AI_FIRESKILL_ENTER	= 4228,
	AT_AI_BLOWUP_EFFECT		= 4229,	// PgAIActBlowup::OnLeave 때 Unit에게 줄 이펙트

	AT_ENABLE_SUPER_AMMOR	= 4230, // 슈퍼 아머가 동작 중인가?(슈퍼 아머는 리액션 중 일부 리액션을 무시 하는 기능)
	AT_ENABLE_RATE_SUPER_AMMOR = 4231, // 슈퍼 아머가 발동할 확률(만분률)
	
	AT_SKILL_SPECIFIC_RUN = 4232,	//특정 런을 한다
	AT_SKILL_SPECIFIC_DASH = 4233,	// 특정 대시를 한다
	AT_SKILL_SPECIFIC_JUMP = 4234,	// 특정 점프를 한다

	AT_NEWCHARACTER			= 4301, // 이벤트 어빌 새로 생성한 캐릭 처음 접속 체크용

	AT_CALL_MARKET			= 4401,	// 마켓 강제 오픈(필드에서만)
	AT_CALL_SAFE			= 4402,	// 창고 강제 오픈(필드에서만)
	AT_PROTECTION_GALL		= 4403, // 내구도 소비 방지
	AT_CALL_STORE			= 4404,	// 상점 강제 오픈(필드에서만)

	AT_EQUIP_LEVELLIMIT_MIN	= 4405,	// 아이템 장착 레벨 증가
	
	// 이 영역은 예약되었음 영역 안에 있는 어빌 번호는 사용하지 말것!! (4406~4435)
	
	AT_EQUIP_LEVELLIMIT_MAX	= 4436,

	AT_CALL_SHARE_SAFE		= 4437,// 공유 창고 호출
	AT_CANNOT_EQUIP_ACHIEVEMENT				= 4438, //업적 해제 금지 기능
	
// 채집 3차 기능성 아이템 어빌(1차군 직업기술 적용 어빌) --> 캐릭터 착용 아이템류에 사용가능
	AT_JS_1ST_ADD_SKILL_TURNTIME			= 4500,	// 절대
	AT_JS_1ST_ADD_USE_EXHAUSTION			= 4501, // 절대
	AT_JS_1ST_ADD_TOOL_USE_DURATION_RATE	= 4502, // 확율 변동
	AT_JS_1ST_ADD_RESULT_ITEM_COUNT			= 4503, // 절대
	AT_JS_1ST_ADD_EXPERTNESS_RATE			= 4504, // 상대
	
// 보조 스킬 사용시
	AT_JS_1ST_SUB_ADD_SKILL_TURNTIME			= 4510,	// 절대
	AT_JS_1ST_SUB_ADD_USE_EXHAUSTION			= 4511, // 절대
	AT_JS_1ST_SUB_ADD_TOOL_USE_DURATION_RATE	= 4512, // 확율 변동
	AT_JS_1ST_SUB_ADD_RESULT_ITEM_COUNT			= 4513, // 절대
	AT_JS_1ST_SUB_ADD_EXPERTNESS_RATE			= 4514, // 상대

// 채집 3차 기능성 아이템 어빌(2차군 직업기술 적용 어빌) --> 설치 가구류에만 사용 가능
	AT_JS_2ND_ADD_UPGRADE_TURN_TIME			= 4550, // 상대
	AT_JS_2ND_NO_TROUBLE					= 4551,	// True or False (0 or != 0)
	AT_JS_2ND_ADD_EXPERTNESS				= 4552,	// 상대
	AT_JS_2ND_AUTO_COMPLETE_SEND_MAIL		= 4553, // True or False (0 or != 0)
	AT_JS_2ND_ADD_TOOL_USE_DURATION			= 4554, // 상대(변동량)

//소환 스킬 관련
	AT_SKILL_SUMMON_NEAR_BY_ENEMY			= 4701, //소환 스킬 사용시 적에 근접한 위치에 생성
// 전투 부활 
	AT_COMBAT_REVIVE_DEL_EFFECT_NO			= 4710, // 전투 부활시 삭제해야할 이펙트
	AT_COMBAT_REVIVE_ADD_EFFECT_NO			= 4720, // 전투 부활시 추가해줄 이펙트
// ITEM
	ATI_EXPLAINID			= 5001,	// Item Tooltip text id
	AT_EQUIP_LIMIT			= 5002,
	AT_CHARACTERFILTER		= 5003,
	AT_ITEMFILTER			= 5004,
	AT_GENDERLIMIT			= 5005,
	//AT_PRICE				= 5006,	//고정필드로 이동
	//AT_SELLPRICE			= 5007,	//고정필드로 이동
	AT_PVPSELL				= 5008,
	AT_ATTRIBUTE			= 5009,	// Item(EItemCantModifyEventType,거래제한), ObjUnit(EObjUnit_Attr,능력치)
	AT_MAX_LIMIT			= 5010,	// 인벤슬롯에 놓을수 있는 최대개수
	AT_WEAPON_TYPE			= 5011,
	AT_HAIR_COLOR			= 5012,
	AT_HAIRBRIGHTNESS		= 5013,
	AT_DEFAULT_AMOUNT		= 5014,	// 수량 사용. 억단위가 0->내구도(최대내구도값), 1 ->수량(아이템 드랍될 때 기본적으로 생성되는 개수)
	AT_PRIMARY_INV			= 5015,	// 메인인벤토리
	AT_VIRTUAL_ITEM			= 5016,	// 수량, 인벤에 들어가지 않는 가상 아이템.
	AT_ITEMMAKING_NO		= 5017, // 레시피 같은 아이템의 경우. 그 아이템이 할 수 있는 제조의 번호.
	AT_MAKING_TYPE			= 5018, // 제조의 타입, (요리, 조합, 분해 등...)
	AT_USE_ITEM_CUSTOM_TYPE		= 5019, // 사용하는 아이템이 특별하게 작업을 하는게 있는지.
	AT_USE_ITEM_CUSTOM_VALUE_1	= 5020, // 
	//AT_ITEM_CANT_EVENT			= 5021,	// 아이템이 행해질수 없는 이벤트 정의(거래, 판매 등)
	AT_ITEM_QUEST_CARD_GRADE	= 5022,
	AT_USE_ITEM_CUSTOM_VALUE_2	= 5023,
	AT_USE_ITEM_CUSTOM_VALUE_3	= 5024,
	AT_PET_INV				= 5025,	// 펫에 장착될 인벤토리
	AT_USE_ITEM_CUSTOM_VALUE_4	= 5026,

	AT_ITEM_SORT_ORDER1		= 5027,
	AT_ITEM_SORT_ORDER2		= 5028,
	AT_ITEM_SORT_ORDER3		= 5029,

	AT_DROP_TRANSFORM_TYPE	= 5030,	//드롭될 때의 SRT 타입
	AT_ITEM_USE_STATUS		= 5031, //아이템을 사용할수 있는 유저의 상태값 
	AT_ITEM_USE_CONFIRM_TXT	= 5032, //아이템을 사용할때 물어볼 텍스트 ID
	AT_ITEM_DISPLAY_GRADE	= 5033,
	AT_MISSIONITEM_LEVELTYPE    = 5034, //미션전용 아이템 레벨 체크
	AT_MISSIONITEM_MISSION_NO	= 5035, //미션전용 아이템 미션번호 체크
	AT_FURNITURE_TYPE		= 5040, //마이홈에 사용되는 아이템들의 타입.
	AT_HOME_WALL_SUB_NO		= 5041, //마이홈 내부 벽의 꺽어지는 부분의 아이템 번호

	AT_COSTUME_GRADE		= 5042,	// 커스튬 등급

	AT_ALWAYS_DROP_ITEM_1	= 5050,	// 몬스터로부터 반드시 드랍되야 하는 아이템(항상 카운트 1)
	AT_ALWAYS_DROP_ITEM_2	= 5051,	
	AT_ALWAYS_DROP_ITEM_3	= 5052,	
	AT_ALWAYS_DROP_ITEM_4	= 5053,	
	AT_ALWAYS_DROP_ITEM_5	= 5054,	
	AT_ALWAYS_DROP_CUSTOM_ITEM_1 = 5055,	//디비에서 입력하지 않고 코드에서 만들어서 입력하는 값
	AT_ALWAYS_DROP_CUSTOM_ITEM_2 = 5056,	//디비에서 입력하지 않고 코드에서 만들어서 입력하는 값
	AT_ALWAYS_DROP_CUSTOM_ITEM_3 = 5057,	//디비에서 입력하지 않고 코드에서 만들어서 입력하는 값
	AT_ALWAYS_DROP_CUSTOM_ITEM_4 = 5058,	//디비에서 입력하지 않고 코드에서 만들어서 입력하는 값
	AT_ALWAYS_DROP_CUSTOM_ITEM_5 = 5059,	//디비에서 입력하지 않고 코드에서 만들어서 입력하는 값

	AT_MAPMOVE_DELETE		= 5060, // 맵이동 하면 사라지는 아이템, 이펙트
	AT_PICKUP_USEITEM		= 5061,	// 아이템 PickUp시에 인벤으로 들어가지않고 자동으로 사용되어 지는 아이템
	AT_BREAKCOUPLE_DELETE_ITEM	= 5062, // 커플(부부) 해제시 사라지는 아이템들 정의

	AT_ALWAYS_DROP_CUSTOM_ITEM_COUNT_1 = 5100,	//디비에서 입력하지 않고 코드에서 만들어서 입력하는 값
	AT_ALWAYS_DROP_CUSTOM_ITEM_COUNT_2 = 5101,	//디비에서 입력하지 않고 코드에서 만들어서 입력하는 값
	AT_ALWAYS_DROP_CUSTOM_ITEM_COUNT_3 = 5102,	//디비에서 입력하지 않고 코드에서 만들어서 입력하는 값
	AT_ALWAYS_DROP_CUSTOM_ITEM_COUNT_4 = 5103,	//디비에서 입력하지 않고 코드에서 만들어서 입력하는 값
	AT_ALWAYS_DROP_CUSTOM_ITEM_COUNT_5 = 5104,	//디비에서 입력하지 않고 코드에서 만들어서 입력하는 값

	AT_SPEED_HACK_COUNT		= 5500,	//속도 해킹을 한 카운트.
	AT_SKILL_MAXIMUM_SPEED	= 5501,	//이 스킬의 최대 속도. 이 속도 이상이면 해킹임

	AT_CHECK_EXIST_ENDQUEST_MIN = 5600,	// 해당 퀘스트를 완료 해야 사용 가능 하다.
	AT_CHECK_EXIST_ENDQUEST_MAX = 5602,	// 해당 퀘스트를 완료 해야 사용 가능 하다.

	AT_CHECK_WANT_ENDQUEST_MIN = 5605,	// 해당 퀘스트가 완료 하지 않아야 사용 가능 하다.
	AT_CHECK_WANT_ENDQUEST_MAX = 5607,	// 해당 퀘스트가 완료 하지 않아야 사용 가능 하다.

	AT_CHECK_EXIST_INGQUEST_MIN = 5610, // 해당 퀘스트를 진행중이어야만 사용 가능 하다.
	AT_CHECK_EXIST_INGQUEST_MAX = 5612, // 해당 퀘스트를 진행중이어야만 사용 가능 하다.

	AT_CHECK_WANT_INGQUEST_MIN = 5615,	// 해당 퀘스트를 진행 중이면 사용 불가능 하다.
	AT_CHECK_WANT_INGQUEST_MAX = 5617,	// 해당 퀘스트를 진행 중이면 사용 불가능 하다.

	AT_GAMBLE_GRADE		= 5620,			// 겜블 아이템 등급

	//AT_RARE_OPTION_GROUP = 5621,		// 레어 아이템 옵션 등급(일반 : 0)
	AT_RARE_OPTION_MAGIC = 5622,		// 레어 아이템 옵션 마법 옵션
	AT_RARE_OPTION_SKILL = 5623,		// 레어 아이템 옵션 스킬 옵션

	AT_ENABLE_USE_START_TIME = 5624,	// 하루중 AT_ENABLE_USE_START_TIME <-> AT_ENABLE_USE_END_TIME 사이에 사용이 가능하다.
	AT_ENABLE_USE_END_TIME = 5625,		// 하루중 AT_ENABLE_USE_START_TIME <-> AT_ENABLE_USE_END_TIME 사이에 사용이 가능하다.

	AT_ENABLE_USE_TIMELIMIT = 5626,		// 기간제 설정이 가능한 소비 아이템이다.(장비의 경우는 기본적으로 사용기간 설정이 가능하다.)

	AT_HELP_END_QUEST1	= 5630,			// 완료 가능한 상태로 만들 퀘스트 #1 (해당 퀘스트가 반드시 진행 중이어야 한다) (Value = QuestID)
	AT_HELP_END_QUEST2	= 5631,			// 완료 가능한 상태로 만들 퀘스트 #2 (해당 퀘스트가 반드시 진행 중이어야 한다) (Value = QuestID)
	AT_HELP_END_QUEST3	= 5632,			// 완료 가능한 상태로 만들 퀘스트 #3 (해당 퀘스트가 반드시 진행 중이어야 한다) (Value = QuestID)
	AT_HELP_END_QUEST4	= 5633,			// 완료 가능한 상태로 만들 퀘스트 #4 (해당 퀘스트가 반드시 진행 중이어야 한다) (Value = QuestID)
	
// 포션 아이템에서 타격시 발생할 이펙트를 세팅
	AT_ATTACK_EFFECTNUM01_FROM_POTION					 = 5700, //5700~5749 공격시에 사용되는 이펙트 확장번호( 특정 스킬 발동시 공격마다 이펙트를 거는 경우 )
	AT_ATTACK_EFFECTNUM50_FROM_POTION					 = 5749,
	AT_ATTACK_EFFECTNUM01_RATE_FROM_POTION				 = 5750, //5750~5799 AT_ATTACK_EFFECTNUM01_FROM_POTION가 걸릴 확률 없으면 100% ( 모든 등급에 동일하게 적용 되는 어빌)
	AT_ATTACK_EFFECTNUM50_RATE_FROM_POTION				 = 5799,
	AT_ATTACK_EFFECTNUM01_TARGET_TYPE_IS_ME_FROM_POTION	 = 5800, //5800~5849 해당 번호의 이펙트를 자신에게 걸어주고 싶다면 1로 세팅
	AT_ATTACK_EFFECTNUM50_TARGET_TYPE_IS_ME_FROM_POTION	 = 5849,
	
// 장비 아이템에서 타격시 발생할 이펙트를 세팅
	AT_ATTACK_EFFECTNUM01_FROM_EQUIP					 = 5850, //5850~5899 공격시에 사용되는 이펙트 확장번호( 특정 스킬 발동시 공격마다 이펙트를 거는 경우 )
	AT_ATTACK_EFFECTNUM50_FROM_EQUIP					 = 5899,
	AT_ATTACK_EFFECTNUM01_RATE_FROM_EQUIP				 = 5900, //5900~5949 AT_ATTACK_EFFECTNUM01_FROM_EQUIP가 걸릴 확률 없으면 100% ( 모든 등급에 동일하게 적용 되는 어빌)
	AT_ATTACK_EFFECTNUM50_RATE_FROM_EQUIP				 = 5949,
	AT_ATTACK_EFFECTNUM01_TARGET_TYPE_IS_ME_FROM_EQUIP	 = 5950, //5950~5999 해당 번호의 이펙트를 자신에게 걸어주고 싶다면 1로 세팅
	AT_ATTACK_EFFECTNUM50_TARGET_TYPE_IS_ME_FROM_EQUIP	 = 5999,

// Boss Ability
	AT_AI_DELAY			= 6001,
	AT_HP_GAGE			= 6002,
	AT_C_HP_GAGE		= 6003,
	AT_CURRENT_ACTION	= 6004,
	AT_MONSTER_APPEAR	= 6005,
	AT_MONSTER_DEAD		= 6006,

// 특수한 타입
	AT_HP_GAUGE_TYPE		= 6010,
	AT_USENOT_SMALLAREA		= 6011,		// SmallArea를 사용하지 않음
	AT_ADDED_GAUGE_VALUE	= 6012,		// 특수 게이지 어빌
	AT_ADDED_GAUGE_GROUP	= 6013,		// 특수 게이지 그룹(이 그룹번호로 서로 영향을 준다)
	AT_HIDE_HP_GAGE			= 6014,		// HP 게이지를 감춘다
	AT_OPTION_HP_GAGE		= 6015,		// HP 게이지옵션(항상보임 등)
	AT_POT_PARTICLE_ACTION	= 6016,		// 세트아이템이나, 아이템등으로 특정 액션시에만 파티클이 붙는 액션
	AT_NOSHOWDAMAGENUM		= 6017,		// ApplyActionEffects()에서 ShowDamageNum 출력 유무(1:보이지않음)

// 희귀 몬스터 대사
	AT_TALK_IDLE			= 6020,		// 기본 상태
	AT_TALK_BIDLE			= 6021,		// 전투 기본 상태
	AT_TALK_ATTACK			= 6022,		// 공격 상태
	AT_TALK_HIT				= 6023,		// 데미지 상태
	AT_TALK_MOVE			= 6024,		// 이동 상태
	AT_MONBAGNO				= 6025,		// 몬스터 백 번호 저장 어빌

//마이홈 어빌
	AT_MYHOME_TODAYHIT		= 6101,		// 마이홈 당일 방문자수
	AT_MYHOME_TOTALHIT		= 6102,		// 마이홈 총 방만자 수
	AT_MYHOME_ROOM_X		= 6103,		// 마이홈 바닥 사이즈
	AT_MYHOME_ROOM_Y		= 6104,
	AT_MYHOME_VISITFLAG		= 6105,		// 마이홈 방문자 플레그
	AT_MYHOME_STATE			= 6106,		// 세금 못내서 잠긴 상태인가?
	AT_MYHOME_NAMEPLATE_NO	= 6107,		// 문패 아이템 번호
	AT_MYHOME_NPC_CLASS_NO	= 6108,		// 마이홈 NPC 클래스 번호
	AT_MYHOME_VISITLOGCOUNT	= 6109,		// 마이홈 방문록 기록 카운트

	AT_N_ATTACK_EFFECT_NO_MIN		= 6110,	// 일반 공격시 발생 이팩트 어빌 시작
	AT_N_ATTACK_EFFECT_NO_MAX		= 6119,	// 일반 공격시 발생 이팩트 어빌 마지막
	AT_N_ATTACK_EFFECT_RATE_MIN		= 6120,	// 일반 공격시 발생 이팩트 발생확률 어빌 시작
	AT_N_ATTACK_EFFECT_RATE_MAX		= 6129,	// 일반 공격시 발생 이팩트 발생확률 어빌 마지막
	AT_N_ATTACK_EFFECT_TARGET_MIN	= 6130,	// 일반 공격시 발생 이팩트 타겟 어빌 시작
	AT_N_ATTACK_EFFECT_TARGET_MAX	= 6139,	// 일반 공격시 발생 이팩트 타겟 어빌 마지막

	AT_C_ATTACK_EFFECT_NO_MIN		= 6140,	// 크리 공격시 발생 이팩트 어빌 시작
	AT_C_ATTACK_EFFECT_NO_MAX		= 6149,	// 크리 공격시 발생 이팩트 어빌 마지막
	AT_C_ATTACK_EFFECT_RATE_MIN		= 6150,	// 크리 공격시 발생 이팩트 발생확률 어빌 시작
	AT_C_ATTACK_EFFECT_RATE_MAX		= 6159,	// 크리 공격시 발생 이팩트 발생확률 어빌 마지막
	AT_C_ATTACK_EFFECT_TARGET_MIN	= 6160,	// 크리 공격시 발생 이팩트 타겟 어빌 시작
	AT_C_ATTACK_EFFECT_TARGET_MAX	= 6169,	// 크리 공격시 발생 이팩트 타겟 어빌 마지막

	AT_BEATTACKED_EFFECT_NO_MIN		= 6170,	// 피격시 발생 이팩트 어빌 시작
	AT_BEATTACKED_EFFECT_NO_MAX		= 6179,	// 피격시 발생 이팩트 어빌 마지막
	AT_BEATTACKED_EFFECT_RATE_MIN	= 6180,	// 피격시 발생 이팩트 발생확률 어빌 시작
	AT_BEATTACKED_EFFECT_RATE_MAX	= 6189,	// 피격시 발생 이팩트 발생확률 어빌 마지막
	AT_BEATTACKED_EFFECT_TARGET_MIN = 6190,	// 피격시 발생 이팩트 타겟 어빌 시작
	AT_BEATTACKED_EFFECT_TARGET_MAX = 6199,	// 피격시 발생 이팩트 타겟 어빌 마지막

	AT_BLOCKED_EFFECT_NO_MIN		= 6200,	// 공격 방어시 발생 이팩트 어빌 시작
	AT_BLOCKED_EFFECT_NO_MAX		= 6209,	// 공격 방어시 발생 이팩트 어빌 마지막
	AT_BLOCKED_EFFECT_RATE_MIN		= 6210,	// 공격 방어시 발생 이팩트 발생확률 어빌 시작
	AT_BLOCKED_EFFECT_RATE_MAX		= 6219,	// 공격 방어시 발생 이팩트 발생확률 어빌 마지막
	AT_BLOCKED_EFFECT_TARGET_MIN	= 6220,	// 공격 방어시 발생 이팩트 타겟 어빌 시작
	AT_BLOCKED_EFFECT_TARGET_MAX	= 6229,	// 공격 방어시 발생 이팩트 타겟 어빌 마지막

	AT_DEFAULT_ITEM_RARITY			= 6300,	// 아이템 생성시 기본으로 주어지는 레어도
	AT_DEFAULT_ITEM_ENCHANT_TYPE	= 6301,	// 아이템 생성시 기본으로 주어지는 인첸트 타입
	AT_DEFAULT_ITEM_ENCHANT_LEVEL	= 6302, // 아이템 생성시 기본으로 주어지는 인첸트 등급
	AT_DEFAULT_ITEM_OPTION_TYPE1	= 6303,	// 아이템 생성시 기본으로 주어지는 옵션 타입
	AT_DEFAULT_ITEM_OPTION_LEVEL1	= 6304, // 아이템 생성시 기본으로 주어지는 옵션 등급
	AT_DEFAULT_ITEM_OPTION_TYPE2	= 6305,	// 아이템 생성시 기본으로 주어지는 옵션 타입
	AT_DEFAULT_ITEM_OPTION_LEVEL2	= 6306, // 아이템 생성시 기본으로 주어지는 옵션 등급
	AT_DEFAULT_ITEM_OPTION_TYPE3	= 6307,	// 아이템 생성시 기본으로 주어지는 옵션 타입
	AT_DEFAULT_ITEM_OPTION_LEVEL3	= 6308, // 아이템 생성시 기본으로 주어지는 옵션 등급
	AT_DEFAULT_ITEM_OPTION_TYPE4	= 6309,	// 아이템 생성시 기본으로 주어지는 옵션 타입
	AT_DEFAULT_ITEM_OPTION_LEVEL4	= 6310, // 아이템 생성시 기본으로 주어지는 옵션 등급
	AT_DEFAULT_ITEM_CURSE			= 6311, // 아이템 생성시 저주 유무
	AT_DEFAULT_ITEM_SEAL			= 6312,	// 아이템 생성시 봉인 유무

	AT_HOME_SIDEJOB_GOLD			= 6320,
	AT_HOME_SIDEJOB_SOUL			= 6321,
	AT_HOME_SIDEJOB_RATE			= 6322,

	AT_ELITEPATTEN_STATE		= 6330,	// 정예 패턴 상태
	AT_GROGGY_NOW				= 6331,	// 분노/그로기 현재값(0이면 분노->분노상태 유지, 그로기->일반상태로 전환)
	AT_FRENZY_NOW_FIRE			= 6332,	// 누적된 분노발동 값
	AT_FRENZY_MAX_FIRE			= 6333,	// 분노발동 임계값(AT_C_MAX_HP * AT_FRENZY_R_FIRE)
	AT_GROGGY_RELAX_TIME		= 6334,	// 그로기 완화 유지시간
	AT_ELITEPATTEN_NEXTSTATE	= 6335, // 다음에 적용할 패턴 상태
	AT_FRENZY_TIME				= 6336,	// 분노유지시간(0이면 일반상태로 전이)(AT_GROGGY_MAX / AT_FRENZY_RECOVERY기준)
	AT_EP_USE_EFFECT_NO			= 6337, // 정예 패턴에서 현재상태에 걸린 이펙트번호
	AT_ELITEPATTEN_INITSTATE	= 6338, // 적용할 패턴 초기화상태
	AT_SEND_UNIT_STATE			= 6339, // 상태정보를 전송한 정보

	AT_CREATE_SUMMONED_HP_RATE		= 6400, // 소환자 기준으로 HP 적용률
	AT_CREATE_SUMMONED_ATTACK_RATE	= 6401, // 소환자 기준으로 공격력 적용률
	AT_CREATE_SUMMONED_SUPPLY		= 6410, // 소환체 필요 서플라이수
	AT_CREATE_UNIQUE_SUMMONED		= 6411, // 유일한 소환체 유무
	AT_CREATE_SUMMONED_IGNORE_SUMMON_EFFECT = 6412, // 소환체 소환시 종류 갯수에 따라 이펙트를 걸때(소유자에게), 이 어빌이 있는 소환체는 종류 갯수에 카운트 되지 않게 하는 어빌
	AT_SHARE_DMG_WITH_SUMMONED		= 6413, // 소환체와 데미지를 분산하여 받는 양 ( 만분률, ex) 1000 이라면, 소환자는  90%의 데미지를 받고, 소환수는 (10%의 데미지/소환체 총수) 만큼 나누어 받음
	AT_CREATE_SUMMONED_MAX_COUNT	= 6414, // 소환체 복수 소환 여부(0: 무제한, 1이상부터는 최대수)

	AT_SUMMONED_REGAIN_HP_RATE		= 6420, // 소환체 리 게인시 1체력당 회복할 체력량
	AT_SUMMONED_REGAIN_MP_RATE		= 6421, // 소환체 리 게인시 1체력당 회복할 마나량
	AT_SUMMONED_REGAIN_ENABLE		= 6422, // 소환체 리 게인시 적용될 타입(HP=0x01, MP=0x02)

	AT_SUMMON_EFFECT_LEARN_CHECK_SKILL_NO = 6430, // 소환체가 몇 종류 인가에 따라 이펙트를 거는(소유자에게) 동작을 하기위해 배웠는지 체크해야 하는 스킬 번호
	AT_SUMMON_EFFECT_BASE_EFFECT_NO		  = 6431, // AT_SUMMON_EFFECT_LEARN_CHECK_SKILL_NO를 배우면, 이 어빌의 이펙트 번호를 기준으로 이펙트를 건다
	AT_SUMMON_EFFECT_MAX_EFFECT_CNT		  = 6432, // AT_SUMMON_EFFECT_BASE_EFFECT_NO에 더 하는 최대값
	
	AT_CREATE_HP_TYPE			= 6440, // 유닛 생성시 HP 적용되는 타입(ECREATE_HP_TYPE)
	AT_ELGA_BONE_MON_HP			= 6441, // 엘가 보호 뼈에 적용할 HP
	AT_ELGA_EYE_MON_HP			= 6442, // 엘가 눈동자 몬스터 자폭시 HP 상태
	AT_ELGA_EYE_MON_HP_TIME		= 6443, // 엘가 눈동자 몬스터 자폭시 HP 등록시간
	AT_ELGA_EYE_MON_AUTO_HP		= 6444, // 초당빠지는 HP 값
	
	AT_ELGA_STONE_RATE			= 6500, // 엘가에서 스톤파괴시 하나당 보호뼈에 적용될 만분률
	AT_ELGA_SUMMOND_HEART_RATE	= 6501, // 엘가 HP에 따라서 심장의 방에 소환되는 몬스터를 다르게 하기 위한 용도

	AT_CALCUATEABIL_MIN			= 7000,
	AT_MAX_HP					= 7001, // 기본값 or 절대값 (+)해주는 값
	AT_R_MAX_HP					= 7002, // _R_ == 천분율값
	AT_C_MAX_HP					= 7003, // _C_ = 최종값
	AT_HP_RECOVERY_INTERVAL		= 7011,	// Auto Heal 되는 주기
	AT_R_HP_RECOVERY_INTERVAL	= 7012,
	AT_C_HP_RECOVERY_INTERVAL	= 7013,
	AT_MAX_MP					= 7021,
	AT_R_MAX_MP					= 7022,
	AT_C_MAX_MP					= 7023,
	AT_MP_RECOVERY_INTERVAL		= 7031,
	AT_R_MP_RECOVERY_INTERVAL	= 7032,
	AT_C_MP_RECOVERY_INTERVAL	= 7033,
	AT_STR						= 7041,
	AT_R_STR					= 7042,
	AT_C_STR					= 7043,
	AT_INT						= 7051,
	AT_R_INT					= 7052,
	AT_C_INT					= 7053,
	AT_CON						= 7061,
	AT_R_CON					= 7062,
	AT_C_CON					= 7063,
	AT_DEX						= 7071,
	AT_R_DEX					= 7072,
	AT_C_DEX					= 7073,
	AT_MOVESPEED				= 7081,
	AT_R_MOVESPEED				= 7082,
	AT_C_MOVESPEED				= 7083,
	AT_MOVESPEED_SAVED			= 7084,
	AT_PHY_DEFENCE				= 7091,
	AT_R_PHY_DEFENCE			= 7092,
	AT_C_PHY_DEFENCE			= 7093,
	AT_AMP_PHY_DEFENCE			= 7094,	// _AMP_ : 옵션 증폭 적용 되기 전 값.
	AT_MAGIC_DEFENCE			= 7101,
	AT_R_MAGIC_DEFENCE			= 7102,
	AT_C_MAGIC_DEFENCE			= 7103,
	AT_AMP_MAGIC_DEFENCE		= 7104,
	AT_ATTACK_SPEED				= 7111,
	AT_R_ATTACK_SPEED			= 7112,
	AT_C_ATTACK_SPEED			= 7113,
	AT_BLOCK_SUCCESS_VALUE				= 7121,
	AT_R_BLOCK_SUCCESS_VALUE				= 7122,
	AT_C_BLOCK_SUCCESS_VALUE				= 7123,
	AT_DODGE_SUCCESS_VALUE				= 7131,
	AT_R_DODGE_SUCCESS_VALUE				= 7132,
	AT_C_DODGE_SUCCESS_VALUE				= 7133,
	AT_CRITICAL_SUCCESS_VALUE			= 7141,
	AT_R_CRITICAL_SUCCESS_VALUE			= 7142,
	AT_C_CRITICAL_SUCCESS_VALUE			= 7143,
	AT_CRITICAL_POWER			= 7151,
	AT_R_CRITICAL_POWER			= 7152,
	AT_C_CRITICAL_POWER			= 7153,
	AT_INVEN_SIZE				= 7161,
	AT_R_INVEN_SIZE				= 7162,
	AT_C_INVEN_SIZE				= 7163,
	AT_EQUIPS_SIZE				= 7171,
	AT_R_EQUIPS_SIZE			= 7172,
	AT_C_EQUIPS_SIZE			= 7173,
	AT_ATTACK_RANGE				= 7181,	// Item, Skill
	AT_R_ATTACK_RANGE			= 7182,
	AT_C_ATTACK_RANGE			= 7183,
	AT_HP_RECOVERY				= 7191,	// Amount of Auto Heal
	AT_R_HP_RECOVERY			= 7192,
	AT_C_HP_RECOVERY			= 7193,
	AT_MP_RECOVERY				= 7201,
	AT_R_MP_RECOVERY			= 7202,
	AT_C_MP_RECOVERY			= 7203,
	AT_JUMP_HEIGHT				= 7211,
	AT_R_JUMP_HEIGHT			= 7212,
	AT_C_JUMP_HEIGHT			= 7213,
	AT_PHY_ATTACK_MAX			= 7221,	// Equip,Monster,NPC
	AT_R_PHY_ATTACK_MAX			= 7222,
	AT_C_PHY_ATTACK_MAX			= 7223,
	AT_AMP_PHY_ATTACK_MAX		= 7224,
	AT_PHY_ATTACK_MIN			= 7231, // Equip,Monster,NPC
	AT_R_PHY_ATTACK_MIN			= 7232,
	AT_C_PHY_ATTACK_MIN			= 7233,
	AT_AMP_PHY_ATTACK_MIN		= 7234,
	AT_TARGET_BACK_DISTANCE 	= 7241,//밀리는 길이
	AT_TARGET_FLY_DISTANCE		= 7251,//뜨는 높이.
	AT_NEED_MP					= 7261,	// Skill 사용 할 때 필요한 MP
	AT_R_NEED_MP				= 7262,
	AT_C_NEED_MP				= 7263,
	AT_NEED_HP					= 7271,
	AT_R_NEED_HP				= 7272,
	AT_C_NEED_HP				= 7273,
	AT_MAGIC_ATTACK				= 7281,
	AT_R_MAGIC_ATTACK			= 7282,
	AT_C_MAGIC_ATTACK			= 7283,
	AT_PHY_ATTACK				= 7291,
	AT_R_PHY_ATTACK				= 7292,
	AT_C_PHY_ATTACK				= 7293,
	AT_CRITICAL_MPOWER			= 7301,
	AT_R_CRITICAL_MPOWER		= 7302,
	AT_C_CRITICAL_MPOWER		= 7303,
	AT_HIT_SUCCESS_VALUE		= 7311, // 스킬 : Casting이 성공할 확률
	AT_R_HIT_SUCCESS_VALUE		= 7312,
	AT_C_HIT_SUCCESS_VALUE		= 7313,
	AT_WALK_SPEED				= 7321,	// 걷는 속도
	AT_R_WALK_SPEED				= 7322,
	AT_C_WALK_SPEED				= 7323,
	AT_MAGIC_ATTACK_MAX			= 7331,
	AT_R_MAGIC_ATTACK_MAX		= 7332,
	AT_C_MAGIC_ATTACK_MAX		= 7333,
	AT_AMP_MAGIC_ATTACK_MAX		= 7334,
	AT_MAGIC_ATTACK_MIN			= 7341,
	AT_R_MAGIC_ATTACK_MIN		= 7342,
	AT_C_MAGIC_ATTACK_MIN		= 7343,
	AT_AMP_MAGIC_ATTACK_MIN		= 7344,
	AT_PHY_DMG_DEC				= 7351,	// 물리Damage 감소율
	AT_R_PHY_DMG_DEC			= 7352,
	AT_C_PHY_DMG_DEC			= 7353,
	AT_MAGIC_DMG_DEC			= 7361,	// 마법Damage 감소율
	AT_R_MAGIC_DMG_DEC			= 7362,
	AT_C_MAGIC_DMG_DEC			= 7363,
	AT_CASTING_SPEED			= 7371,	// Casting Speed
	AT_R_CASTING_SPEED			= 7372,
	AT_C_CASTING_SPEED			= 7373,
	AT_RESIST_FIRE				= 7381,	// 속성저항(화)
	AT_R_RESIST_FIRE			= 7382,
	AT_C_RESIST_FIRE			= 7383,
	AT_RESIST_WATER				= 7391,	// 속성저항(수)
	AT_R_RESIST_WATER			= 7392,
	AT_C_RESIST_WATER			= 7393,
	AT_RESIST_TREE				= 7401,	// 속성저항(목)
	AT_R_RESIST_TREE			= 7402,
	AT_C_RESIST_TREE			= 7403,
	AT_RESIST_IRON				= 7411,	// 속성저항(금)
	AT_R_RESIST_IRON			= 7412,
	AT_C_RESIST_IRON			= 7413,
	AT_RESIST_EARTH				= 7421,	// 속성저항(토)
	AT_R_RESIST_EARTH			= 7422,
	AT_C_RESIST_EARTH			= 7423,
	AT_HP_POTION_ADD_RATE		= 7431,	//HP물약 사용시 추가적인 회복량
	AT_R_HP_POTION_ADD_RATE		= 7432,
	AT_C_HP_POTION_ADD_RATE		= 7433,
	AT_MP_POTION_ADD_RATE		= 7441,	//HP물약 사용시 추가적인 회복량
	AT_R_MP_POTION_ADD_RATE		= 7442,
	AT_C_MP_POTION_ADD_RATE		= 7443,
	AT_DMG_REFLECT_RATE			= 7451,	// Damage 반사할 때, 반사되는 양(Damage에 대한 만분율값)
	AT_R_DMG_REFLECT_RATE		= 7452,
	AT_C_DMG_REFLECT_RATE		= 7453,
	AT_DMG_REFLECT_HITRATE		= 7461,	// Damage 반사할 때, 반사가 일어날 확률
	AT_R_DMG_REFLECT_HITRATE	= 7462,
	AT_C_DMG_REFLECT_HITRATE	= 7463,
	AT_PENETRATION_RATE			= 7471,	// 관통할 확률
	AT_R_PENETRATION_RATE		= 7472,
	AT_C_PENETRATION_RATE		= 7473,
	AT_R_MAX_HP_DEAD			= 7481, // _R_ == 죽었을때 회복할 천분율값 
	AT_R_MAX_MP_DEAD			= 7482, // _R_ == 죽었을때 회복할 천분율값
	AT_ABS_ADDED_DMG_PHY		= 7491,	// Dmg 계산이후 절대값으로 넣어주는 추가 Dmg(Physical공격)
	AT_R_ABS_ADDED_DMG_PHY		= 7492,
	AT_C_ABS_ADDED_DMG_PHY		= 7493,
	AT_ABS_ADDED_DMG_MAGIC		= 7501,	// Dmg 계산이후 절대값으로 넣어주는 추가 Dmg(Magic공격)
	AT_R_ABS_ADDED_DMG_MAGIC	= 7502,
 	AT_C_ABS_ADDED_DMG_MAGIC	= 7503,
	// AT_MAX_DP					= 7511, // 기본값 or 절대값 (+)해주는 값
	// AT_R_MAX_DP					= 7512, // _R_ == 천분율값
	// AT_C_MAX_DP					= 7513, // _C_ = 최종값
	// AT_DP_RECOVERY_INTERVAL		= 7521,	// Auto Heal 되는 주기
	// AT_R_DP_RECOVERY_INTERVAL	= 7522,
	// AT_C_DP_RECOVERY_INTERVAL	= 7523,
	// AT_DP_RECOVERY				= 7531,	// Amount of Auto Heal
	// AT_R_DP_RECOVERY			= 7532,
	// AT_C_DP_RECOVERY			= 7533,
	AT_VILLAGE_MOVESPEED		= 7541,
	AT_R_VILLAGE_MOVESPEED		= 7542,
	AT_C_VILLAGE_MOVESPEED		= 7543,
	AT_VILLAGE_MOVESPEED_SAVED	= 7544,

	AT_PROJECTILE_REFLECT_DMG_RATE		= 7551,	// 발사체 반사 데미지%
	AT_R_PROJECTILE_REFLECT_DMG_RATE	= 7552,	
	AT_C_PROJECTILE_REFLECT_DMG_RATE	= 7553,	

	AT_PROJECTILE_REFLECT_RATE			= 7561,	// 발사체 데미지를 반사할 확률
	AT_R_PROJECTILE_REFLECT_RATE		= 7562,
	AT_C_PROJECTILE_REFLECT_RATE		= 7563,

	AT_PHY_REFLECT_DMG_RATE		= 7571,	// 물리 데미지를 몇%로 반사할 것인지(발사체도 반사)
	AT_R_PHY_REFLECT_DMG_RATE	= 7572,
	AT_C_PHY_REFLECT_DMG_RATE	= 7573,

	AT_PHY_REFLECT_RATE			= 7581,	// 물리 데미지를 반사할 확률(발사체도 반사)
	AT_R_PHY_REFLECT_RATE		= 7582,
	AT_C_PHY_REFLECT_RATE		= 7583,

	AT_MAGIC_REFLECT_DMG_RATE	= 7591,	// 마법 데미지를 몇%로 반사할 것인지(발사체도 반사)
	AT_R_MAGIC_REFLECT_DMG_RATE	= 7592,
	AT_C_MAGIC_REFLECT_DMG_RATE	= 7593,

	AT_MAGIC_REFLECT_RATE		= 7601,	// 마법 데미지를 반사할 확률(발사체도 반사)
	AT_R_MAGIC_REFLECT_RATE		= 7602,
	AT_C_MAGIC_REFLECT_RATE		= 7603,
	
	AT_HP_RESTORE_WHEN_HIT_RATE		= 7631,	//타격시 HP 회복시켜줄 확률
	AT_R_HP_RESTORE_WHEN_HIT_RATE	= 7632,
	AT_C_HP_RESTORE_WHEN_HIT_RATE	= 7633,

	AT_HP_RESTORE_WHEN_HIT		= 7641,	//타격시 HP 회복 시켜주는 값(절대값)
	AT_R_HP_RESTORE_WHEN_HIT	= 7642,
	AT_C_HP_RESTORE_WHEN_HIT	= 7643,
	
	AT_MP_RESTORE_WHEN_HIT_RATE		= 7661,	//타격시 MP 회복시켜줄 확률
	AT_R_MP_RESTORE_WHEN_HIT_RATE	= 7662,
	AT_C_MP_RESTORE_WHEN_HIT_RATE	= 7663,

	AT_MP_RESTORE_WHEN_HIT		= 7671,	//타격시 MP 회복 시켜주는 값(절대값)
	AT_R_MP_RESTORE_WHEN_HIT	= 7672,
	AT_C_MP_RESTORE_WHEN_HIT	= 7673,

	AT_ADD_GROGGYPOINT			= 7691, //!그로기 포인트 축적
	AT_R_ADD_GROGGYPOINT		= 7692,
	AT_C_ADD_GROGGYPOINT		= 7693,

	AT_DEC_GROGGYPOINT_RATE		= 7701, //!그로기 포인트 감소 속도(완화)
	AT_R_DEC_GROGGYPOINT_RATE	= 7702,
	AT_C_DEC_GROGGYPOINT_RATE	= 7703,

	AT_GROGGY_RECOVERY_INTERVAL		= 7711, //!Auto Groggy 되는 주기
	AT_R_GROGGY_RECOVERY_INTERVAL	= 7712,
	AT_C_GROGGY_RECOVERY_INTERVAL	= 7713,

	AT_SUMMONED_MAX_SUPPLY		= 7721, //!소환체 소환 용량
	AT_R_SUMMONED_MAX_SUPPLY	= 7722,
	AT_C_SUMMONED_MAX_SUPPLY	= 7723,

	AT_HP_RESTORE_WHEN_DAMAGE_RATE		= 7731,	//피격시(맞을때) HP 회복시켜줄 확률
	AT_R_HP_RESTORE_WHEN_DAMAGE_RATE	= 7732,
	AT_C_HP_RESTORE_WHEN_DAMAGE_RATE	= 7733,

	AT_HP_RESTORE_WHEN_DAMAGE			= 7741,	//피격시(맞을때) HP 회복 시켜주는 값(절대값)
	AT_R_HP_RESTORE_WHEN_DAMAGE			= 7742,
	AT_C_HP_RESTORE_WHEN_DAMAGE			= 7743,
	
	AT_MP_RESTORE_WHEN_DAMAGE_RATE		= 7751,	//피격시(맞을때) MP 회복시켜줄 확률
	AT_R_MP_RESTORE_WHEN_DAMAGE_RATE	= 7752,
	AT_C_MP_RESTORE_WHEN_DAMAGE_RATE	= 7753,

	AT_MP_RESTORE_WHEN_DAMAGE			= 7761,	//피격시(맞을때) MP 회복 시켜주는 값(절대값)
	AT_R_MP_RESTORE_WHEN_DAMAGE			= 7762,
	AT_C_MP_RESTORE_WHEN_DAMAGE			= 7763,
// 데미지 계산 이후 상대적 데미지 감소. 밑의 어빌 컨트롤은 TB_DefDefence7_Wave.DamageDecRate에서 함 ////
	AT_ABS_DEC_DMG_PHY			= 7771, // Dmg 계산 이후 물리데미지 감소율(10000 고정)
	AT_R_ABS_DEC_DMG_PHY		= 7772, // 위의 값에서 n/10000으로 % 재계산(이지만 역시 0으로 고정)
	AT_C_ABS_DEC_DMG_PHY		= 7773, // 이 값은 항상 0으로 초기화(자동으로 계산해서 값을 넣어줌)
	AT_ABS_DEC_DMG_MAGIC		= 7781, // Dmg 계산 이후 마법데미지 감소율(10000 고정)
	AT_R_ABS_DEC_DMG_MAGIC		= 7782, // 위의 값에서 n/10000으로 % 재계산(이지만 역시 0으로 고정)
	AT_C_ABS_DEC_DMG_MAGIC		= 7783, // 이 값은 항상 0으로 초기화(자동으로 계산해서 값을 넣어줌)
////////////////////////////////////////////////////////////////////////////////////////////////////////

	AT_OCCUPY_POINT				= 7791, //점령포인트
	AT_R_OCCUPY_POINT			= 7792,
	AT_C_OCCUPY_POINT			= 7793,	//플레이어는 _C_를 통해 점령포인트 증가 이펙트 효과를 보고, 가디언은 AT_OCCUPY_POINT만 사용한다.
	
	AT_ADD_HP_RESTORE_RATE	  = 7801,	// 스킬로 인한 HP 회복량 증가량(스킬 외에도 사용해도 상관없음. 단 현재는 처리가 없음)
	AT_R_ADD_HP_RESTORE_RATE = 7802,
	AT_C_ADD_HP_RESTORE_RATE = 7803,

	AT_ADD_MP_RESTORE_RATE	  = 7811,	// 스킬로 인한 MP 회복량 증가량(스킬 외에도 사용해도 상관없음. 단 현재는 처리가 없음)
	AT_R_ADD_MP_RESTORE_RATE = 7812,
	AT_C_ADD_MP_RESTORE_RATE = 7813,

	AT_BLOCK_DAMAGE_RATE	= 7821,		// 블록을 한후에 받을 데미지를 감소시킬 비율
	AT_R_BLOCK_DAMAGE_RATE	= 7822,
	AT_C_BLOCK_DAMAGE_RATE	= 7823,
/// 8000 ~ 9000 특정 이펙트 면역에 대한 값 
///(Effect에서 AT_CHECK_IMMUNITY_TYPE에 써주어야할 값이며, Unit에 세팅해줘야할값)
	AT_IMMUNITY_FREEZE_RATE		= 8001,	// 동빙 이펙트 등의 면역에 대한 수치(만분률)
	AT_R_IMMUNITY_FREEZE_RATE	= 8002,
	AT_C_IMMUNITY_FREEZE_RATE	= 8003,

	AT_IMMUNITY_COLD_RATE		= 8011,	// 결빙 이펙트 등의 면역에 대한 수치(만분률)
	AT_R_IMMUNITY_COLD_RATE		= 8012,
	AT_C_IMMUNITY_COLD_RATE		= 8013,

	AT_IMMUNITY_STUN_RATE		= 8021,	// 스턴 이펙트의 면역에 대한 수치(만분률)
	AT_R_IMMUNITY_STUN_RATE		= 8022,
	AT_C_IMMUNITY_STUN_RATE		= 8023,

	AT_IMMUNITY_POISON_RATE		= 8031,	// 중독 이펙트의 면역에 대한 수치(만분률)
	AT_R_IMMUNITY_POISON_RATE	= 8032,
	AT_C_IMMUNITY_POISON_RATE	= 8033,
	
	AT_FINAL_HIT_SUCCESS_RATE		= 9001,	// 최종 명중률
	AT_R_FINAL_HIT_SUCCESS_RATE		= 9002,	
	AT_C_FINAL_HIT_SUCCESS_RATE		= 9003,	

	AT_FINAL_DODGE_SUCCESS_RATE		= 9011,	// 최종 회피율
	AT_R_FINAL_DODGE_SUCCESS_RATE		= 9012,	
	AT_C_FINAL_DODGE_SUCCESS_RATE	= 9013,	

	AT_FINAL_BLOCK_SUCCESS_RATE		= 9021,	// 최종 블럭률
	AT_R_FINAL_BLOCK_SUCCESS_RATE		= 9022,	
	AT_C_FINAL_BLOCK_SUCCESS_RATE	= 9023,	

	AT_FINAL_CRITICAL_SUCCESS_RATE	= 9031,	// 최종 크리티컬 성공률
	AT_R_FINAL_CRITICAL_SUCCESS_RATE	= 9032,	
	AT_C_FINAL_CRITICAL_SUCCESS_RATE= 9033,	
	
	AT_FINAL_MAX_HP		= 9041, // AT_C_MAX_HP로 얻어오는 값을 증폭 시킴 (만분률)
	AT_R_FINAL_MAX_HP	= 9042,
	AT_C_FINAL_MAX_HP	= 9043,

	AT_FINAL_MAX_MP		= 9051,	// AT_C_MAX_MP로 얻어오는 값을 증폭 시킴 (만분률)
	AT_R_FINAL_MAX_MP	= 9052,
	AT_C_FINAL_MAX_MP	= 9053,
	
	AT_CRITICAL_POWER_DEC = 9061,					// 치명타방어력
	AT_R_CRITICAL_POWER_DEC = 9062,
	AT_C_CRITICAL_POWER_DEC = 9063,

	AT_FINAL_CRITICAL_SUCCESS_RATE_DEC = 9071,		// 치명타저항율
	AT_R_FINAL_CRITICAL_SUCCESS_RATE_DEC = 9072,
	AT_C_FINAL_CRITICAL_SUCCESS_RATE_DEC = 9073,

	AT_BLOCK_SUCCESS_RATE_DEC	= 9081,				// 블록관통률
	AT_R_BLOCK_SUCCESS_RATE_DEC = 9082,
	AT_C_BLOCK_SUCCESS_RATE_DEC = 9083,

	AT_RESIST_DEBUFF = 9091,						// 저주저항율	
	AT_R_RESIST_DEBUFF = 9092,
	AT_C_RESIST_DEBUFF= 9093,

	AT_SUCCESS_DEBUFF = 9101,						// 저주성공률
	AT_R_SUCCESS_DEBUFF = 9102,
	AT_C_SUCCESS_DEBUFF= 9103,	
	
	AT_DEBUFF_DURATION_DEC_RATE	= 9111,	// 디버프 이펙트 유지시간 감소 어빌(이펙트 걸리는자-Target)
	AT_R_DEBUFF_DURATION_DEC_RATE	= 9112,
	AT_C_DEBUFF_DURATION_DEC_RATE	= 9113,

	AT_DEBUFF_DURATION_ADD_RATE	= 9121,	// 디버프 이펙트 유지시간 증가 어빌(이펙트 거는자-Caster)
	AT_R_DEBUFF_DURATION_ADD_RATE	= 9122,
	AT_C_DEBUFF_DURATION_ADD_RATE	= 9123,

	AT_DEFENCE_IGNORE_RATE	= 9131,				// 방어 무시 어빌
	AT_R_DEFENCE_IGNORE_RATE	= 9132,
	AT_C_DEFENCE_IGNORE_RATE	= 9133,
	
	AT_CALCUATEABIL_MAX			= 10000,
// Reserve : 10001 - 11000
// AI Action type 값
//실제 Action type 값 = GetAbil(AT_AI_ACTIONTYPE_MIN+Action)
	AT_AI_ACTIONTYPE_MIN		= 10001,	// AI Action type 값
	AT_AI_TYPE_NO_DAMAGEACTION	= 10011,	// AI 각타입별 Enter될때 데미지액션을 유무, Leave될때 해제됨
	AT_AI_CHASE_MOVESPEED_SAVED	= 10012,	// AI Chase시 추가된 스피드 만분률
	AT_AI_CHASE_GOAL_POS		= 10013,	// AI Chase시 OnEnter에서 GoalPos를 사용하도록 함

	AT_HIT_DAMAGE_HP_RATE_ACTIVATE							= 10101,	// 공격시 적에게 추가 데미지(HP%)를 줄 확률
	AT_HIT_DAMAGE_HP_RATE									= 10102,	// 공격시 적에게 추가 데미지(HP%)
	AT_HIT_DECREASE_MP_RATE_ACTIVATE						= 10103,	// 공격시  적에게 추가로 MP를(%)로 감소시킬 확률
	AT_HIT_DECREASE_MP_RATE									= 10104,	// 공격시 적에게 추가로 MP를 감소(%)
	AT_CRITICAL_DAMAGE_RATE_ACTIVATE						= 10105,	// 크리티컬시 적에게 추가 데미지(HP%)를 줄 확률
	AT_CRITICAL_DAMAGE_RATE									= 10106,	// 크리티컬시 적에게 추가 데미지(HP%)
	AT_CRITICAL_DAMAGE_ACTIVATE								= 10107,	// 크리티컬시 적에게 추가 데미지를 확률
	AT_CRITICAL_DAMAGE										= 10108,	// 크리티컬시 적에게 추가 데미지
	AT_ATTACKED_DECREASE_DAMAGE_ACTIVATE_HP_RATE			= 10109,	// 피격시 HP가 일정 %이하면 데미지 감소
	AT_ATTACKED_DECREASE_DAMAGE_RATE						= 10110,	// 피격시 HP가 일정 %이하면 감소하는 데미지의 %
	AT_HIT_SUCKING_HPMP_RATE_ACTIVATE						= 10111,	// 공격시 HP나 MP를 흡수할 확률
	AT_HIT_SUCKING_HPMP										= 10112,	// 공격시 HP MP를 빠는양

// 추가적인 확률만 정의 하는곳(만분율) (Pet 관련 어빌들)
	AT_GIVE_TO_CALLER_ADD_EXP_RATE			= 11001,	// 나의 소환자에게 일정경험치를 준다
	AT_HUNTED_MON_ADD_DROPMONEY_RATE		= 11002,	// 몬스터를 잡을때 추가적인 DropMoney가 증가할 확률
	AT_HUNTED_MON_ADD_DROPMONEY_VALUE_RATE	= 11003,	// AT_HUNTED_MON_ADD_DROPMONEY_RATE가 발생했을때 증가하는 돈의 량(이름짓기 너무 힘들다-_-...)
	AT_GOLD_RUSH_DROPMONEY_VALUE_MIN		= 11004,	// 골드 러쉬 스킬 사용시 드랍하는 돈의 최소값
	AT_GOLD_RUSH_DROPMONEY_VALUE_MAX		= 11005,	// 골드 러쉬 스킬 사용시 드랍하는 돈의 최대값

//----------------------------------------------------
// 직업 생산 12000~13000 예약
//----------------------------------------------------
	AT_JOBSKILL_TOOL_TYPE = 12000, // 직업 생산/채집 도구 타입
	AT_JOBSKILL_FURNITURE_TYPE = 12100, // 2차 직업생산 아이템(가구)이 어떤 EGatherType을 갖는지 확인하는 값

	AT_JS_RECOVERY_EXHAUSTION_R = 12101,
	AT_JS_RECOVERY_EXHAUSTION_C = 12102,
	AT_JS_RECOVERY_BLESSPOINT_R = 12103,
	AT_JS_RECOVERY_BLESSPOINT_C = 12104,
	AT_JS_USE_ITEM_LIMIT_EXHAUSTION_R = 12105,
	AT_JS_USE_ITEM_LIMIT_BLESSPOINT_R = 12106,
	AT_JS_RECOVERY_PRODUCTPOINT_R = 12107,
	AT_JS_RECOVERY_PRODUCTPOINT_C = 12108,
	AT_JS_USE_ITEM_LIMIT_PRODUCTPOINT_R = 12109,
	AT_ADDITIONAL_INVEN_SIZE	= 12110,	//펫에 적용되는 어빌임

	AT_JS_IGNORE_EXP_PENALTY			= 12230,			//직업스킬의 패널티를 무시

	AT_JOBSKILL_SAVEIDX					= 12240,

	AT_LEARN_SKILL_EVENT				= 12400,			//아이템으로 스킬 배울때 발생되는 이벤트
//----------------------------------------------------
	
	AT_DMG_REFLECT_RATE_FROM_ITEM01			=  13001,	 // 아이템으로 인한 Damage 반사 확률 (AT_DMG_REFLECT_DMG_FROM_ITEM01과 한 묶음)
	AT_DMG_REFLECT_RATE_FROM_ITEM02			=  13002,
	AT_DMG_REFLECT_RATE_FROM_ITEM03			=  13003,
	AT_DMG_REFLECT_RATE_FROM_ITEM04			=  13004,
	AT_DMG_REFLECT_RATE_FROM_ITEM05			=  13005,
	AT_DMG_REFLECT_RATE_FROM_ITEM06			=  13006,
	AT_DMG_REFLECT_RATE_FROM_ITEM07			=  13007,
	AT_DMG_REFLECT_RATE_FROM_ITEM08			=  13008,
	AT_DMG_REFLECT_RATE_FROM_ITEM09			=  13009,
	AT_DMG_REFLECT_RATE_FROM_ITEM10			=  13010,

	AT_DMG_REFLECT_DMG_FROM_ITEM01			=  13011,	// 아이템으로 인한 Dmage 반사확률로 인해 반사될때 절대값
	AT_DMG_REFLECT_DMG_FROM_ITEM02			=  13012,
	AT_DMG_REFLECT_DMG_FROM_ITEM03			=  13013,
	AT_DMG_REFLECT_DMG_FROM_ITEM04			=  13014,
	AT_DMG_REFLECT_DMG_FROM_ITEM05			=  13015,
	AT_DMG_REFLECT_DMG_FROM_ITEM06			=  13016,
	AT_DMG_REFLECT_DMG_FROM_ITEM07			=  13017,
	AT_DMG_REFLECT_DMG_FROM_ITEM08			=  13018,
	AT_DMG_REFLECT_DMG_FROM_ITEM09			=  13019,
	AT_DMG_REFLECT_DMG_FROM_ITEM10			=  13020,


// 20000~30000사이는 패널티 어빌입니다.
	AT_PENALTY_HP_RATE			= 20000+AT_HP,			//20101
	AT_PENALTY_MP_RATE			= 20000+AT_MP,			//20105
	AT_ADD_EXPERIENCE_RATE		= 20000+AT_EXPERIENCE,	//20512

//30000~AT_ELEMENT_ABIL_MAX 속성 시스템 관련 어빌
	AT_ELEMENT_ABIL_NONE			= 30000,		//속성 어빌 시작
	AT_ATTACK_ADD_FIRE				= 30011,		//화염 추가 공격력(절대값)
	AT_ATTACK_ADD_ICE				= 30012,		//냉기 추가 공격력(절대값)
	AT_ATTACK_ADD_NATURE			= 30013,		//자연 추가 공격력(절대값)
	AT_ATTACK_ADD_CURSE				= 30014,		//저주 추가 공격력(절대값)
	AT_ATTACK_ADD_DESTROY			= 30015,		//파괴 추가 공격력(절대값)
	AT_C_ATTACK_ADD_FIRE			= 30016,		//화염 추가 공격력(절대값)(최종값)
	AT_C_ATTACK_ADD_ICE				= 30017,		//냉기 추가 공격력(절대값)(최종값)
	AT_C_ATTACK_ADD_NATURE			= 30018,		//자연 추가 공격력(절대값)(최종값)
	AT_C_ATTACK_ADD_CURSE			= 30019,		//저주 추가 공격력(절대값)(최종값)
	AT_C_ATTACK_ADD_DESTROY			= 30020,		//파괴 추가 공격력(절대값)(최종값)
	AT_R_ATTACK_ADD_FIRE			= 30021,		//화염 추가 공격력(상대값)
	AT_R_ATTACK_ADD_ICE				= 30022,		//냉기 추가 공격력(상대값)
	AT_R_ATTACK_ADD_NATURE			= 30023,		//자연 추가 공격력(상대값)
	AT_R_ATTACK_ADD_CURSE			= 30024,		//저주 추가 공격력(상대값)
	AT_R_ATTACK_ADD_DESTROY			= 30025,		//파괴 추가 공격력(상대값)
	AT_R_ATTACK_ADD_FIRE_PHY		= 30031,		//물리 전환 화염 공격력(상대값)
	AT_R_ATTACK_ADD_ICE_PHY			= 30032,		//물리 전환 냉기 공격력(상대값)
	AT_R_ATTACK_ADD_NATURE_PHY		= 30033,		//물리 전환 자연 공격력(상대값)
	AT_R_ATTACK_ADD_CURSE_PHY		= 30034,		//물리 전환 저주 공격력(상대값)
	AT_R_ATTACK_ADD_DESTROY_PHY		= 30035,		//물리 전환 파괴 공격력(상대값)
	AT_R_ATTACK_ADD_FIRE_MAGIC		= 30041,		//마법 전환 화염 공격력(상대값)
	AT_R_ATTACK_ADD_ICE_MAGIC		= 30042,		//마법 전환 냉기 공격력(상대값)
	AT_R_ATTACK_ADD_NATURE_MAGIC	= 30043,		//마법 전환 자연 공격력(상대값)
	AT_R_ATTACK_ADD_CURSE_MAGIC		= 30044,		//마법 전환 저주 공격력(상대값)
	AT_R_ATTACK_ADD_DESTROY_MAGIC	= 30045,		//마법 전환 파괴 공격력(상대값)
	AT_RESIST_ADD_FIRE				= 30051,		//화염 추가 저항력(절대값)
	AT_RESIST_ADD_ICE				= 30052,		//냉기 추가 저항력(절대값)
	AT_RESIST_ADD_NATURE			= 30053,		//자연 추가 저항력(절대값)
	AT_RESIST_ADD_CURSE				= 30054,		//저주 추가 저항력(절대값)
	AT_RESIST_ADD_DESTROY			= 30055,		//파괴 추가 저항력(절대값)
	AT_C_RESIST_ADD_FIRE			= 30056,		//화염 추가 저항력(절대값)(최종값)
	AT_C_RESIST_ADD_ICE				= 30057,		//냉기 추가 저항력(절대값)(최종값)
	AT_C_RESIST_ADD_NATURE			= 30058,		//자연 추가 저항력(절대값)(최종값)
	AT_C_RESIST_ADD_CURSE			= 30059,		//저주 추가 저항력(절대값)(최종값)
	AT_C_RESIST_ADD_DESTROY			= 30060,		//파괴 추가 저항력(절대값)(최종값)
	AT_R_RESIST_ADD_FIRE			= 30061,		//화염 추가 저항력(상대값)
	AT_R_RESIST_ADD_ICE				= 30062,		//냉기 추가 저항력(상대값)
	AT_R_RESIST_ADD_NATURE			= 30063,		//자연 추가 저항력(상대값)
	AT_R_RESIST_ADD_CURSE			= 30064,		//저주 추가 저항력(상대값)
	AT_R_RESIST_ADD_DESTROY			= 30065,		//파괴 추가 저항력(상대값)
	AT_R_RESIST_ADD_FIRE_PHY		= 30071,		//물리 전환 화염 저항력(상대값)
	AT_R_RESIST_ADD_ICE_PHY			= 30072,		//물리 전환 냉기 저항력(상대값)
	AT_R_RESIST_ADD_NATURE_PHY		= 30073,		//물리 전환 자연 저항력(상대값)
	AT_R_RESIST_ADD_CURSE_PHY		= 30074,		//물리 전환 저주 저항력(상대값)
	AT_R_RESIST_ADD_DESTROY_PHY		= 30075,		//물리 전환 파괴 저항력(상대값)
	AT_R_RESIST_ADD_FIRE_MAGIC		= 30081,		//마법 전환 화염 저항력(상대값)
	AT_R_RESIST_ADD_ICE_MAGIC		= 30082,		//마법 전환 냉기 저항력(상대값)
	AT_R_RESIST_ADD_NATURE_MAGIC	= 30083,		//마법 전환 자연 저항력(상대값)
	AT_R_RESIST_ADD_CURSE_MAGIC		= 30084,		//마법 전환 저주 저항력(상대값)
	AT_R_RESIST_ADD_DESTROY_MAGIC	= 30085,		//마법 전환 파괴 저항력(상대값)
	AT_EXTRACT_ELEMENT_FIRE			= 30110,		//화염원소 추출
	AT_EXTRACT_ELEMENT_ICE			= 30120,		//냉기원소 추출
	AT_EXTRACT_ELEMENT_NATURE		= 30130,		//자연원소 추출
	AT_EXTRACT_ELEMENT_CURSE		= 30140,		//저주원소 추출
	AT_EXTRACT_ELEMENT_DESTROY		= 30150,		//파괴원소 추출
	AT_EXTRACT_ELEMENT_RANDOM		= 30160,		//무작위원소 추출
	AT_ELEMENT_MONSTER				= 30170,		//몬스터 속성(1:화염,2:냉기,3:자연,4:저주,5:파괴)
	AT_ATTACK_ADD_4ELEMENT          = 30180,        //화염,냉기,자연,저주추가공격력(절대값)
	AT_ATTACK_ADD_5ELEMENT          = 30181,        //화염,냉기,자연,저주,파괴추가공격력(절대값)
	AT_R_ATTACK_ADD_4ELEMENT        = 30190,        //화염,냉기,자연,저주추가공격력(상대값)
	AT_R_ATTACK_ADD_5ELEMENT        = 30191,        //화염,냉기,자연,저주,파괴추가공격력(상대값)
	AT_R_ATTACK_ADD_4ELEMENT_PHY    = 30200,        //물리전환화염,냉기,자연,저주공격력(상대값)
	AT_R_ATTACK_ADD_5ELEMENT_PHY    = 30201,        //물리전환화염,냉기,자연,저주,파괴공격력(상대값)
	AT_R_ATTACK_ADD_4ELEMENT_MAGIC  = 30210,        //마법전환화염,냉기,자연,저주공격력(상대값)
	AT_R_ATTACK_ADD_5ELEMENT_MAGIC  = 30211,        //마법전환화염,냉기,자연,저주,파괴공격력(상대값)
	AT_RESIST_ADD_4ELEMENT          = 30220,        //화염,냉기,자연,저주추가저항력(절대값)
	AT_RESIST_ADD_5ELEMENT          = 30221,        //화염,냉기,자연,저주,파괴추가저항력(절대값)
	AT_R_RESIST_ADD_4ELEMENT        = 30230,        //화염,냉기,자연,저주추가저항력(상대값)
	AT_R_RESIST_ADD_5ELEMENT        = 30231,        //화염,냉기,자연,저주,파괴추가저항력(상대값)
	AT_R_RESIST_ADD_4ELEMENT_PHY    = 30240,        //물리전환화염,냉기,자연,저주저항력(상대값)
	AT_R_RESIST_ADD_5ELEMENT_PHY    = 30241,        //물리전환화염,냉기,자연,저주,파괴저항력(상대값)
	AT_R_RESIST_ADD_4ELEMENT_MAGIC  = 30250,        //마법전환화염,냉기,자연,저주저항력(상대값)
	AT_R_RESIST_ADD_5ELEMENT_MAGIC  = 30251,        //마법전환화염,냉기,자연,저주,파괴저항력(상대값)
	AT_RESIST_RATE_ADD_FIRE			= 30301,		//화염 추가 저항률(절대값.만분률)
	AT_RESIST_RATE_ADD_ICE			= 30302,		//냉기 추가 저항률(절대값.만분률)
	AT_RESIST_RATE_ADD_NATURE		= 30303,		//자연 추가 저항률(절대값.만분률)
	AT_RESIST_RATE_ADD_CURSE		= 30304,		//저주 추가 저항률(절대값.만분률)
	AT_RESIST_RATE_ADD_DESTROY		= 30305,		//파괴 추가 저항률(절대값.만분률)
	AT_RESIST_RATE_ADD_4ELEMENT		= 30311,		//4대속성 저항률 증가(절대값.만분률)
	AT_RESIST_RATE_ADD_5ELEMENT		= 30312,		//5대속성 저항률 증가(절대값.만분률)

	//클라이언트 툴팁용 어빌
	AT_BASE_ATTACK_ADD_FIRE			= 30331,		//화염 추가 공격력(Unit만 계산용)
	AT_BASE_ATTACK_ADD_ICE			= 30332,		//냉기 추가 공격력
	AT_BASE_ATTACK_ADD_NATURE		= 30333,		//자연 추가 공격력
	AT_BASE_ATTACK_ADD_CURSE		= 30334,		//저주 추가 공격력
	AT_BASE_ATTACK_ADD_DESTROY		= 30335,		//파괴 추가 공격력
	AT_BASE_RESIST_ADD_FIRE			= 30371,		//화염 추가 저항력
	AT_BASE_RESIST_ADD_ICE			= 30372,		//냉기 추가 저항력
	AT_BASE_RESIST_ADD_NATURE		= 30373,		//자연 추가 저항력
	AT_BASE_RESIST_ADD_CURSE		= 30374,		//저주 추가 저항력
	AT_BASE_RESIST_ADD_DESTROY		= 30375,		//파괴 추가 저항력

	AT_INV_ATTACK_ADD_FIRE			= 30341,		//화염 추가 공격력(Inven만 계산용)
	AT_INV_ATTACK_ADD_ICE			= 30342,		//냉기 추가 공격력
	AT_INV_ATTACK_ADD_NATURE		= 30343,		//자연 추가 공격력
	AT_INV_ATTACK_ADD_CURSE			= 30344,		//저주 추가 공격력
	AT_INV_ATTACK_ADD_DESTROY		= 30345,		//파괴 추가 공격력
	AT_INV_RESIST_ADD_FIRE			= 30381,		//화염 추가 저항력
	AT_INV_RESIST_ADD_ICE			= 30382,		//냉기 추가 저항력
	AT_INV_RESIST_ADD_NATURE		= 30383,		//자연 추가 저항력
	AT_INV_RESIST_ADD_CURSE			= 30384,		//저주 추가 저항력
	AT_INV_RESIST_ADD_DESTROY		= 30385,		//파괴 추가 저항력

	AT_ELEMENT_ABIL_MAX				= 30500,		//속성 어빌 예약 끝
	
// 이펙트를 유저가 컨트롤 한다. 
	AT_EFFCONTROL_DEL_MONEY		= 40001,	// 돈으로 삭제 가능(Value에 돈을 넣어줘야 합니다)
	AT_EFFCONTROL_DEL_MONEY_PERLEVEL = 40002,// 돈으로 삭제를 하는데 레벨별 가중치 적용(Value에 가중치를 넣어주어야 합니다.)
	AT_EFFCONTROL_DEL_ITEM		= 40003,	// 아이템으로 삭제 가능(Value에는 아이템 번호)
	AT_EFFCONTROL_DEL_BY_EFFECT = 40004,	// 이펙트가 이펙트를 삭제(길드전 : 버프삭제 진흙아이템)
	AT_WHEN_EFFECT_ACTIVATE_THEN_DELETE_THIS_EFFECTNO = 40100,	// 특정 이펙트가 발동될때, 여기에 담긴 이펙트를 삭제 할수 있게 한다

// 41000~43000 사이는 스킬 효율 조절 어빌입니다.
	AT_ADJUST_SKILL_CHECK_TYPE	= 41000,		// 스킬 체크 타입, EAdjustSkillCheckType 1:모든 스킬, 2:일부 스킬만, 3:일부 스킬 제외하고 모두
// 스킬 범위1(가로 길이 등)
	AT_E_ADJUST_SKILL_RANGE		= 41101,		// DefaultOnFindTarget 함수의 iSkillRange값 +
	AT_R_ADJUST_SKILL_RANGE		= 41102,		// DefaultOnFindTarget 함수의 iSkillRange값 만분률로 증가
	//AT_ADJUST_SKILL_C_RANGE		= 41103,
//스킬 범위2(육면체의폭, 원뿔의 각도 등)
	AT_E_ADJUST_SKILL_RANGE2	= 41111,		// DefaultOnFindTarget 함수의 iSkillRange2값 +
	AT_R_ADJUST_SKILL_RANGE2	= 41112,		// DefaultOnFindTarget 함수의 iSkillRange2값 만분률로 증가
	//	AT_ADJUST_SKILL_C_RANGE2	= 41113,
//스킬 데미지(최종 데미지 아님)
	AT_E_ADJUST_SKILL_DMG		= 41121,		// DoFinalDmg 함수의 스킬 데미지 값 +
	AT_R_ADJUST_SKILL_DMG		= 41122,		// DoFinalDmg 함수의 스킬 데미지 값 만분률로 증가
	//AT_ADJUST_SKILL_C_DMG		= 41123,
// 스킬 쿨타임(현재 기능 없음)
	//AT_ADJUST_SKILL_E_COOLTIME  = 41131,		// 쿨타임에 값 +	1000이면 1초
	//AT_ADJUST_SKILL_R_COOLTIME  = 41132,		// 쿨타임 값 만분률로 증가
	//AT_ADJUST_SKILL_C_COOLTIME  = 41133,
	
//체크 할 스킬들(1000개 예약)
	AT_ADJUST_SKILL_BEGIN		= 42001,		// AT_ADJUST_SKILL_CHECK_TYPE에 체크 되는 스킬들 번호(1번 타입 제외)
	AT_ADJUST_SKILL_END			= 42100,
	//AT_ADJUST_SKILL_END		= 43000,
	
	AT_ADJUST_SKILL_DMG_BY_PHASE_TIME	= 43100,	// T초
	
	AT_E_ADJUST_SKILL_RESULT_MIN_DMG_BY_PHASE		= 43101,	// min
	AT_R_ADJUST_SKILL_RESULT_MIN_DMG_BY_PHASE		= 43102,	// min
	//AT_ADJUST_SKILL_DMG_BY_PHASE_C_MIN		= 43103,	// min

	AT_E_ADJUST_SKILL_RESULT_MAX_DMG_BY_PHASE		= 43111,	// max
	AT_R_ADJUST_SKILL_RESULT_MAX_DMG_BY_PHASE		= 43112,	// max
	//AT_ADJUST_SKILL_DMG_BY_PHASE_C_MAX		= 43113,	// max

	AT_E_ADJUST_SKILL_INC_PHASE_DMG		= 43121,	// 데미지 증감량(DB)
	AT_R_ADJUST_SKILL_INC_PHASE_DMG		= 43122,	// 데미지 증감량(DB)
	//AT_ADJUST_SKILL_DMG_BY_PHASE_C_INC		= 43123,	// 데미지 증감량(DB)
	
	AT_ADJUST_SKILL_ACC_INC_PHASE_DMG	= 43200,	// 누적된 데미지 증감량(계산저장용)
	AT_ADJUST_SKILL_PHASE_DMG_IS_HIT	= 43201,	// 공격 했다는 표시를 effect에 전달하기 위한값

//기타 클라이언트에서 사용할 아이콘등의 어빌
	AT_DEF_RES_NO				= 50001,	
	AT_DONT_DISPLAY_LEVEL		= 50002, // 몬스터등의 레벨을 표시 하지 않는다.
	AT_DONT_DISPLAY_ALL			= 50003, // 몬스터등의 이름, 레벨등을 전부 표시 하지 않는다.
	AT_DISPLAY_LEVEL			= 50004, // 이름 왼쪽에 붙일 등급정보(가디언의 경우 계급)
	AT_DISPLAY_HEADBUFFICON		= 50005, // 버프 아이콘 머리에 표시
	AT_DISPLAY_GIF_TITLE		= 50006, // 머리 위에 GIF 표시
	AT_DISPLAY_EFFECT_COUNTDOWN	= 50007, // 머리 위에 이펙트 카운트 출력
	AT_DONT_DISPLAY_GRADE		= 50008, // 등급을 표시 하지 않는다.
	
	AT_CUSTOM_TOOLTIP_01 		= 50050, // 커스텀하게 표시할 툴팁정보

//랭킹과 관련된 어빌
	AT_MAX_COMBO				= 50101,

//미션 이벤트
	AT_MISSION_EVENT			= 50150,

//미션 반복 횟수
	AT_MISSION_NO				= 50151,
	AT_MISSION_COUNT			= 50152,
//전략포인터
	AT_STRATEGIC_POINT			= 50153,
	AT_STRATEGIC_MUL_POINT		= 50154,
	AT_AGGRO_POINT				= 50155,
	AT_MIN_OCCUPY_POINT			= 50156, //@AutoHeal에서 최소 점령포인트
	AT_MAX_OCCUPY_POINT			= 50157, //@

	AT_USE_SKILL_ON_DIE			= 50159, // 다이 스킬이 발동되면 세팅
	AT_ELGA_STONE_COUNT			= 50160, // 엘가 스톤 소환수량

	AT_RELEASE_DEL_EFFECT_TYPE	= 50161, //!EDelEffectType
	AT_RELEASE_DEL_EFFECT		= 50162, //@PgGround::ReleaseUnit될때 이펙트 중에서 타겟에게 적용된 이펙트를 지워야 하는 경우, 삭제하도록, CUnit: AddAbil, CEffect: SetAbil

//Client_Option
	AT_CLIENT_OPTION_SAVE		= 50201,	// 옵션 중 모든 유저가 공유해야하는 옵션들(Bit로 빼내서 봐야함)

//Penalty
	AT_MISSION_THROWUP_PENALTY	= 50501,	// 미션 포기

//특정 조건 만족하면 아이템 지급하는 어빌( 50600 ~ 50700 예약 )
	AT_SPECIFIC_REWARD_REVIVE_FEATHER_LOGIN		= 50600, // 접속 시 부활 깃털(100%) 포함된 상자 지급( 1일 1회 )
	AT_SPECIFICR_EWARD_REVIVE_FEATHER_LEVELUP	= 50601, // 레벨업 하면 분홍색 부활 깃털 지급
	AT_SPECIFIC_REWARD_EVENT					= 50602, // 일정 시간 접속 유지할 때마다 아이템 지급하는 이벤트.
/* 50700 까지 예약 */

//미니맵 아이콘 표시용 어빌
	AT_DISPLAY_MINIMAP_EFFECT	= 50701,	//이펙트가 걸렸을 때 미니맵에 아이콘을 그려준다. (값은 이펙트 미니맵 아이콘 번호)
	AT_DISPLAY_MINIMAP_INSITEM	= 50702, // 이 어빌이 있는 인스턴트아이템(예:러브러브모드 곰)은 미니맵에 표시된다. (값은 미니맵 아이콘 번호)
//미니맵 아이콘 표시용 어빌 끝

//러브러브 모드 용 어빌
	AT_BEAR_ITEM				= 50721, // 이 어빌이 있는 아이템은 러브러브 모드 곰 아이템.
	AT_BEAR_EFFECT_RED			= 50722, // 이 어빌이 있는 플레이어는 곰을 엎은 상태.( 빨간 곰 )
	AT_BEAR_EFFECT_BLUE			= 50723, // 이 어빌이 있는 플레이어는 곰을 엎은 상태.( 파란 곰 )
	AT_BEAR_EFFECT_SPEED_LOCK	= 50724, // 이 어빌이 있으면 인스턴스 아이템, 포인트 스킬 외에는 이속을 변경할 수 없다.
	AT_BEAR_EFFECT_ITEM_LOCK	= 50725, // 이 어빌이 있으면 아이템을 사용 할 수 없다.
//러브러브 모드 용 어빌 끝

	AT_EFFECT_DELETE_ALL_DEBUFF = 50790, // 이 어빌이 있는 이펙트는 모든 디버프를 삭제한다.

//TRANSLATE 사용 타입 스킬인가? (커맨드 입력 UI의 형태를 결정함)
	AT_TRANSLATE_SKILL_TYPE = 50800,
//전이할 스킬들( 전이스킬수 == 최소 커맨드 수, 성공률 체크 == 100/전이스킬수, 이것들을 기반으로 다음 전이할 스킬이 무엇인지 설정함)
	AT_TRANSLATE_SKILL01	= 50801,
	AT_TRANSLATE_SKILL10	= 50810,
//몇개의 커맨드 입력이 존재 하는가?(전이스킬 수보다 작으면, 전이 스킬수로 맞춰짐)
	AT_TRANSLATE_SKILL_CMD_CNT	= 50811,

//GM 전용 어빌(51000~52000 예약)
	AT_GM_GODHAND				= 51000,	// 이 어빌이 있으면 인첸트 확률 100%
	AT_GM_JOBSKILL_USE_SUBTOOL	= 51100,	// 이 어빌이 있으면 보조기술 발동 확률 100% 

	AT_ITEM_SKILL				= 53000,	// 스킬발동아이템에 들어가는 스킬번호용 어빌. 이 어빌 있으면 아이템으로 스킬 사용 가능
	AT_ITEM_SKILL_EXPLAIN_ID    = 53001,	// 스킬발동아이템용 스킬 전용 설명 ex>다크 블러드 방어구 세트 옵션

	AT_JS3_NOT_EQUIP_ITEM		= 53100,	// 이 어빌 가지고 있으면 툴팁의 허용레벨 -> 가능구간 으로 변경

	AT_MULTI_RES				= 59000,	// 멀티 리소스(남전 남법 여전 여법 가지고 검사)
	AT_NEW_MULTI_TRS			= 59001,    // 멀티 리소스(남자 여자 만 가지고 검사)
	AT_PARTY_MASTER_PROGRESS_POS	= 59100, // 파티장 던전 진행(트리거) 위치

	AT_SKILL_CUSTOM_DATA_01		= 60001,	// 사용자 데이터 저장용 ABIL 시작
											// 여기는 스킬 동작시 발생하는 임시 데이터 저장용으로 사용할것임
											// DEF 정의와 겹치지 않도록 사용할것
	AT_SKILL_CUSTOM_DATA_MAX	= 60201,	// 사용자 데이터 저장용 ABIL 마지막


	AT_ACHIEVEMENT_PVP_KILL			= 60901, // 휘장, 매달 관련 임시 보관 데이터 어빌들 저장되지 않는다.
	AT_ACHIEVEMENT_PVP_DEAD			= 60902,

	AT_ACHIEVEMENT_MISSION_KILL		= 60903,
	AT_ACHIEVEMENT_MISSION_DEAD		= 60904,
	AT_ACHIEVEMENT_MISSION_USEITEM	= 60905,
	AT_ACHIEVEMENT_MISSION_HIT		= 60906,
	AT_ACHIEVEMENT_MISSION_REVIVE	= 60907,

	AT_ACHIEVEMENT_MONSTER_TYPE = 61000,	// 업적 검사용 몬스터 타입 (사용 수치는 100 ~ 200 이 값이 0 이면 업적 검사용 몬스터가 아님)
	AT_ACHIEVEMENT_DATA_MIN		= 61001,	// 업적 검사용 데이터 선언 시작 

	AT_ACHIEVEMENT_LEVEL		= 61002,// 캐릭터 레벨 성장			

	AT_ACHIEVEMENT_ENCHANT9		= 61003,// 인첸트 아이템 성공 여부 (9)
	AT_ACHIEVEMENT_ENCHANT11	= 61004,// 인첸트 아이템 성공 여부 (11)
	AT_ACHIEVEMENT_ENCHANT13	= 61005,// 인첸트 아이템 성공 여부 (13)
	AT_ACHIEVEMENT_ENCHANT15	= 61006,// 인첸트 아이템 성공 여부 (15)

	AT_ACHIEVEMENT_SOULCRAFT3	= 61007,// 소울 크래프트 성공 횟수 아티팩트
	AT_ACHIEVEMENT_SOULCRAFT4	= 61008,// 소울 크래프트 성공 횟수 레전드

	AT_ACHIEVEMENT_CHANGE_CLASS	= 61009,// 전직	등급
	AT_ACHIEVEMENT_ITEM_BREAKER	= 61010,// 아이템 깨트리기(환혼 습득 갯수)
	AT_ACHIEVEMENT_COOKER		= 61011,// 요리 성공 횟수
	AT_ACHIEVEMENT_EATER		= 61012,// 요리 섭취 횟수
	AT_ACHIEVEMENT_CONQUEROR	= 61013,// 크리스탈 스톤 취득 횟수
	AT_ACHIEVEMENT_IMMORTALITY	= 61014,// 불사신(부활 횟수)
	AT_ACHIEVEMENT_ZOMBI		= 61015,// 좀비? (사망 횟수)
	AT_ACHIEVEMENT_THERICH		= 61016,// 부자? (게임 머니 획득)

	AT_ACHIEVEMENT_PVP_ENTRY_DM				= 61017,// 사투전 참가 횟수
	AT_ACHIEVEMENT_PVP_ENTRY_KTH			= 61018,// 점령전 참가 횟수
	AT_ACHIEVEMENT_PVP_ENTRY_ANNIHILATION	= 61019,// 섬멸전 참가 횟수
	AT_ACHIEVEMENT_PVP_ENTRY_DESTROY		= 61020,// 유물전 참가 횟수

	AT_ACHIEVEMENT_PVP_RESULT_CP			= 61021,// PVP 결과 CP
	AT_ACHIEVEMENT_PVP_RESULT_WIN			= 61022,// PVP 결과 승리 횟수
	AT_ACHIEVEMENT_PVP_RESULT_LOSE			= 61023,// PVP 결과 패배 횟수

	AT_ACHIEVEMENT_ENCHANT_SUCCESS			= 61024,// 인첸트 성공 횟수
	AT_ACHIEVEMENT_ENCHANT_FAIL				= 61025,// 인첸트 실패 횟수

	AT_ACHIEVEMENT_OPENMARKET_BUY_CASH		= 61026,// 오픈 마켓 구입 금액(캐시)
	AT_ACHIEVEMENT_OPENMARKET_BUY_GOLD		= 61027,// 오픈 마켓 구입 금액(골드)

	AT_ACHIEVEMENT_USE_PORTAL				= 61028,// 포탈 이동 횟수
	AT_ACHIEVEMENT_DESTROY_OBJECT			= 61029,// 파괴 오브젝트 파괴 횟수
	
	AT_ACHIEVEMENT_PVP_SLAYER				= 61030,// PVP 모드에서 죽기전까지 죽인 횟수
	AT_ACHIEVEMENT_PVP_IMMORTALITY			= 61031,// PVP 종료시까지 죽지 않음
	AT_ACHIEVEMENT_PVP_KILL_VS_DEAD			= 61032,// 죽은수 VS 죽인수

	AT_ACHIEVEMENT_NORMAL_QUEST_COMPLETE	= 61033,// 모험 퀘스트 완료 횟수
	AT_ACHIEVEMENT_SCENARIO_QUEST_COMPLETE	= 61034,// 영웅 퀘스트 완료 횟수
	AT_ACHIEVEMENT_LOOP_QUEST_COMPLETE		= 61035,// 반복 퀘스트 완료 횟수
	AT_ACHIEVEMENT_GUILD_QUEST_COMPLETE		= 61036,// 길드 퀘스트 완료 횟수

	AT_ACHIEVEMENT_MYHOME_HITCOUNT			= 61037,// 마이홈 방문 횟수

	AT_ACHIEVEMENT_USE_EMOTICON				= 61038,// 이모티콘 사용

	AT_ACHIEVEMENT_LONGTIMENOSEE			= 61039,// 오랜만이다.

	AT_ACHIEVEMENT_SELCHAR_COUNT			= 61040,// 캐릭터 선택 횟수 (캐릭터별 로그인 횟수라고 해야 하나...)

	AT_ACHIEVEMENT_EXPCARD_COUNT			= 61041,// 경험치 카드 사용 횟수
	AT_ACHIEVEMENT_EXPCARD_DATE				= 61042,// 경험치 카드 사용 일자

	AT_ACHIEVEMENT_ITEM						= 61045,// 아이템으로 습득하는 업적 이건 유저가 달성할 수 없다.

	AT_ACHIEVEMENT_LOGIN_0					= 61046,// 지정 시간대에 접속 카운트 0시
//사용하지 말것 (예약)
	AT_ACHIEVEMENT_LOGIN_23					= 61069,// 지정 시간대에 접속 카운트 23시

	AT_ACHIEVEMENT_CRAZYLEVELUP				= 61070,// 광랩의 기본

	AT_ACHIEVEMENT_FEARLESS					= 61071,// 겁 없는 사냥꾼

	AT_ACHIEVEMENT_CTRLOFGOD				= 61072,// 신들린 컨트롤

	AT_ACHIEVEMENT_FIGHTEROFWIND			= 61073,// 바람의 파이터

	AT_ACHIEVEMENT_60MILLIONMEN				= 61074,// 6억분에1 사나이?

	AT_ACHIEVEMENT_FAMOUS					= 61075,// 유명한넘 ㅡㅡ;;

	AT_ACHIEVEMENT_DEALKING					= 61076,// 일회 타격으로 나온 데미지 양에 따라 주는 업적

	AT_ACHIEVEMENT_COMBO					= 61077,// 콤보 업적

	AT_ACHIEVEMENT_USE_STYLEITEM_HAIR		= 61078,// 스타일 아이템 사용
	AT_ACHIEVEMENT_USE_STYLEITEM_FACE		= 61079,// 스타일 아이템 사용

	AT_ACHIEVEMENT_MYHOME_EQUIP				= 61080,// 마이홈 아이템 배치 횟수

	AT_ACHIEVEMENT_SEND_MAIL				= 61081,// 메일 전송 횟수

	AT_ACHIEVEMENT_SOULEATER				= 61082,// 소울 사용개수

	AT_ACHIEVEMENT_USE_SMS					= 61083,// 확성기 사용

	AT_ACHIEVEMENT_USE_POTION				= 61084,// 포션 사용

	AT_ACHIEVEMENT_CASH_BONUS				= 61085,// DP 소지량

	AT_ACHIEVEMENT_BESTSELLER				= 61086,// 판매왕??

	AT_ACHIEVEMENT_SPRINT					= 61087,// 대시

	AT_ACHIEVEMENT_EQUIP_ITEMGRADE0			= 61088,// 장착 아이템 등급별 개수
//사용하지 말것 (예약)
	AT_ACHIEVEMENT_EQUIP_ITEMGRADE4			= 61092,// 장착 아이템 등급별 개수

	AT_ACHIEVEMENT_USE_PARTYMOVE			= 61093,// 파티 이동 아이템 사용

	AT_ACHIEVEMENT_USE_COUPLEWARP			= 61094,// 커플 이동 아이템 사용

	AT_ACHIEVEMENT_MARRY					= 61095,// 결혼 횟수

	AT_ACHIEVEMENT_COUPLE					= 61096,// 커플 횟수

	AT_ACHIEVEMENT_1DAYCOUPLE				= 61097,// 일일 커플 횟수

	AT_ACHIEVEMENT_SINGLECLUB				= 61098,// 독신클럽

	AT_ACHIEVEMENT_FRIEND					= 61099,// 친구 카운트

	AT_ACHIEVEMENT_KILL_MONSTER_MIN			= 61100,// 몬스터 사냥 횟수	(여기는 AT_ACHIEVEMENT_MONSTER_TYPE 어빌을 사용 해야 함 방법이 없음 ㅠㅠ;;)
/**/
/**/
/**/
/**/
	AT_ACHIEVEMENT_KILL_MONSTER_MAX			= 62000,// 몬스터 사냥 타입 최대 

	AT_ACHIEVEMENT_MISSION_MIN				= 62001,// 미션 완료 횟수 시작 ( 여기는 약간의 계산이 필요 = (61201 + MissionKey * 10 + MissionLevel) 점점 어디로 가는건지...)
/**/
/**/
/**/
/**/
	AT_ACHIEVEMENT_MISSION_MAX				= 64000,// 미션 완료 횟수 마지막

	AT_ACHIEVEMENT_ENCHANT_NOFAIL9			= 64001,// 실패 없이 연속 인첸트 달성9
//사용하지 말것 (예약)
	AT_ACHIEVEMENT_ENCHANT_NOFAIL31			= 64023,// 실패 없이 연속 인첸트 달성31

	AT_ACHIEVEMENT_MAP_MONSTER_KILL_MIN		= 64031,// MAP KEY 가 설정된 맵에서 몬스터 사냥 횟수
// 사용하지 말것  (예약)
	AT_ACHIEVEMENT_MAP_MONSTER_KILL_MAX		= 64332,// MAP KEY 가 설정된 맵에서 몬스터 사냥 횟수

	AT_ACHIEVEMENT_PARTY_MASTER				= 64333,// 파티장 횟수

	AT_ACHIEVEMENT_COUPLE_START_DATE		= 64334,// 커플 시작 시간

	AT_ACHIEVEMENT_TEXTIME					= 64335,// 장기 채납자

	AT_ACHIEVEMENT_BIDDING					= 64336,// 공인 중계사

	AT_ACHIEVEMENT_ILLEGALVISITOR			= 64337,// 불법 거주자

	AT_ACHIEVEMENT_OPENMARKET_SELL_CASH		= 64338,// 오픈 마켓 캐시 판매

	AT_ACHIEVEMENT_OPENMARKET_SELL_GOLD		= 64339,// 오픈 마켓 골드 판매

	AT_ACHIEVEMENT_DIVORCE					= 64340,// 이혼 횟수

	AT_ACHIEVEMENT_INVITATION				= 64341,// 초대장 발급 횟수

	AT_ACHIEVEMENT_STALKER					= 64342,// 스토커

	AT_ACHIEVEMENT_BETRAYER					= 64343,// 배신자

	AT_ACHIEVEMENT_MARRYMONEY				= 64344,// 축의금

	AT_ACHIEVEMENT_CASHSHOPGIFT				= 64345,// 캐시샵 선물(산타)

	AT_ACHIEVEMENT_COMPLETE_FIRST			= 64346,// 업적 랠름 최초 달성

	AT_ACHIEVEMENT_NPC_TALK					= 64347,// NPC 대화 횟수

	AT_ACHIEVEMENT_MISSION_NO_HIT			= 64348,// 미션 피격 없이 클리어(자기 랩에 맞는 미션)

	AT_ACHIEVEMENT_CASHSHOPBUY_EQUIP		= 64349,// 꾸미기 아이템 구입 횟수

	AT_ACHIEVEMENT_CERTIFICATEOFHERO		= 64350,// 용자의 증표 사용 개수

	AT_ACHIEVEMENT_PET_DEAD					= 64351,// 2차 펫 사망 횟수

	AT_ACHIEVEMENT_PET_ALIVETIME			= 64352,// 2차 펫 생존 시간

	AT_ACHIEVEMENT_RANDOM_QUEST_COMPLETE	= 64353,// 랜덤 퀘스트(헌터G)

	AT_ACHIEVEMENT_POPULARPOINT				= 64354,// 인기도

	AT_ACHIEVEMENT_TODAYPOPULARPOINT		= 64355,// 오늘의 인기도
	
	AT_ACHIEVEMENT_CHEKCPLAYTIME			= 64356,// 플레이 타임

	AT_ACHIEVEMENT_RECOMMEND_POINT			= 64357,// 내가 다른 사람 추천한 회수에 따른 업적

	AT_ACHIEVEMENT_EMPORIA_VICTORY			= 64358,// 엠포리아 우승 업적(값은 BattleIndex, 1: 우승, 100: 1성, 101: 2성)

	AT_ACHIEVEMENT_PVP_LEAGUE_REWARD		= 64359,// PVP 리그 보상 업적( 16강, 8강, 4강, 준우승, 우승 )

	AT_ACHIEVEMENT_MISSION_HELPER			= 64360,// 자신보다 5~10레벨 낮은 유저와 미션 플레이 횟수( 상대방이 40레벨 이하면 3회로 인정, 그외는 1회 )

// 여기서 부터 접속 횟수 체크 이벤트 어빌 과연 얼마나 활용 할까....
	AT_EVENTFUNC_CONNECT_EVENT01			= 64501, // 이벤트 어빌 접속 횟수 보상 이벤트 번호
/**/
	AT_EVENTFUNC_CONNECT_EVENT10			= 64510, // 이벤트 어빌 접속 횟수 보상 이벤트 번호

	AT_EVENTFUNC_CONNECT_EVENT11			= 64511, // 하루 한번 접속 보상 이벤트 번호
	AT_EVENTFUNC_CONNECT_EVENT12			= 64512, // 일정 기간 내 한번만 주는 보상(인간 Classlimit 체크)
	AT_EVENTFUNC_CONNECT_EVENT13			= 64513, // 일정 기간 내 한번만 주는 보상(용족 DraClasslimit 체크)

	AT_GET_ITEM_MESSAGE						= 64514, //특정아이템 획득시 축하메시지 공지

	AT_EVENTFUNC_CONNECT_COUNT01			= 64521, // 접속 횟수 기록
/**/
	AT_EVENTFUNC_CONNECT_COUNT10			= 64530,	// 접속 횟수 기록
	AT_REST_EXP_ADD_MAX_LOW32				= 64531,	//  휴식 추가 경험치 제한 (LOW32)
	AT_REST_EXP_ADD_MAX_HIGH32				= 64532,	//  휴식 추가 경험치 제한 (HIGH32)
	AT_CHARACTER_LAST_LOGOUT_TIME			= 64533,	//  캐릭터가 최근 로그아웃한 시간	

	AT_ACHIEVEMENT_DURABLENESS_ZERO			= 64540,	// 착용한 장비(투구,어깨,상의,하의,장갑,신발,무기)가 모두 0이 되면 업적

	AT_ACHIEVEMENT_NORMAL_REPAIR			= 64550,	// "내구도 0"인 일반 장비 수리 회수
	AT_ACHIEVEMENT_RARE_REPAIR				= 64551,	// 고급
	AT_ACHIEVEMENT_UNIQUE_REPAIR			= 64552,	// 스페셜
	AT_ACHIEVEMENT_ARTIFACT_REPAIR			= 64553,	// 유물
	AT_ACHIEVEMENT_LEGEND_REPAIR			= 64554,	// 전설

	AT_ACHIEVEMENT_COLLECT_COUNT			= 64560,	// 업적 모은 개수

	AT_ACHIEVEMENT_INVINCIBLE 				= 64570,	// 한번도 죽지않고 20,40,60,80 레벨 달성

	AT_ACHIEVEMENT_USE_GADACOIN				= 64580,	// 가다코인 사용 개수
	AT_ACHIEVEMENT_USE_SOULSTONE			= 64590,	// 악마의 영혼석 사용 개수

	AT_ACHIEVEMENT_HIDDEN_PLAY_TIME			= 64600,	// 히든맵 플레이 시간

	AT_ACHIEVEMENT_EQUIP_SET30				= 64610,	// 30레벨 세트 장비 모두 착용시 획득 업적
	AT_ACHIEVEMENT_EQUIP_SET40				= 64611,	// 30레벨 세트 장비 모두 착용시 획득 업적
	AT_ACHIEVEMENT_EQUIP_SET50				= 64612,	// 50레벨 세트 장비 모두 착용시 획득 업적
	AT_ACHIEVEMENT_EQUIP_SET60				= 64613,	// 60레벨 세트 장비 모두 착용시 획득 업적
	
	AT_ACHIEVEMENT_RELATION_CLAER			= 64614,	// 연관된 업적(같은 GroupNo)을 모두 클리어 하면 달성되는 업적
	
	AT_ACHIEVEMENT_DUNGEON_ANYONE_DIE		= 64615,	// 파티단위 업적: 아무도 죽지 않고 던전 클리어( Value: 1, CustomValue: 보스몬스터 대표번호 )
	AT_ACHIEVEMENT_DUNGEON_ATTACKED_COUNT	= 64616,	// 일정 피격회수 이하로 던전 클리어( Value: 피격회수, CustomValue: 보스몬스터 번호 )
	AT_ACHIEVEMENT_DUNGEON_TIMEATTACK		= 64617,	// 일정 시간안에 던전 클리어( Value: 시간(초단위 입력), CustomValue: 보스몬스터번호 )

	AT_ACHIEVEMENT_ATTR_LOW_FIRE			= 64700, 	// 저급 화염속성 원소 아이템 모으기
	AT_ACHIEVEMENT_ATTR_HIGH_FIRE			= 64701,	// 고급 화염속성 원소 아이템 모으기
	AT_ACHIEVEMENT_ATTR_LOW_ICE				= 64702,	// 저급 냉기속성 원소 아이템 모으기
	AT_ACHIEVEMENT_ATTR_HIGH_ICE			= 64703,	// 고급 냉기속성 원소 아이템 모으기
	AT_ACHIEVEMENT_ATTR_LOW_NATURE			= 64704,	// 고급 냉기속성 원소 아이템 모으기
	AT_ACHIEVEMENT_ATTR_HIGH_NATURE			= 64705,	// 고급 자연속성 원소 아이템 모으기
	AT_ACHIEVEMENT_ATTR_LOW_CURSE			= 64706,	// 저급 저주속성 원소 아이템 모으기
	AT_ACHIEVEMENT_ATTR_HIGH_CURSE			= 64707,	// 고급 저주속성 원소 아이템 모으기
	AT_ACHIEVEMENT_ATTR_LOW_DESTROY			= 64708,	// 저급 파괴속성 원소 아이템 모으기

	AT_ACHIEVEMENT_ATTR_ATTACK_FIRE			= 64710,	// 화염 속성 공격력 일정수치 이상일 때
	AT_ACHIEVEMENT_ATTR_ATTACK_ICE			= 64711, 	// 냉기 속성 공격력 일정수치 이상일 때
	AT_ACHIEVEMENT_ATTR_ATTACK_NATURE		= 64712, 	// 자연 속성 공격력 일정수치 이상일 때
	AT_ACHIEVEMENT_ATTR_ATTACK_CURSE		= 64713,	// 저주 속성 공격력 일정수치 이상일 때
	AT_ACHIEVEMENT_ATTR_ATTACK_DESTORY		= 64714, 	// 파괴 속성 공격력 일정수치 이상일 때
	AT_ACHIEVEMENT_ATTR_ATTACK_5ELEMENT		= 64715, 	// 5대  속성 공격력 일정수치 이상일 때
	AT_ACHIEVEMENT_ATTR_RESIST_FIRE			= 64716, 	// 화염 속성 저항력 일정수치 이상일 때
	AT_ACHIEVEMENT_ATTR_RESIST_ICE			= 64717, 	// 냉기 속성 저항력 일정수치 이상일 때
	AT_ACHIEVEMENT_ATTR_RESIST_NATURE		= 64718, 	// 자연 속성 저항력 일정수치 이상일 때
	AT_ACHIEVEMENT_ATTR_RESIST_CURSE		= 64719, 	// 저주 속성 저항력 일정수치 이상일 때
	AT_ACHIEVEMENT_ATTR_RESIST_DESTORY		= 64720, 	// 파괴 속성 저항력 일정수치 이상일 때
	AT_ACHIEVEMENT_ATTR_RESIST_5ELEMENT		= 64721,	// 5대  속성 저항력 일정수치 이상일 때

//EMPORIA 기능과 관련된 어빌
//EMFUNC 관련 64901~65000 사용 예약.
	AT_EMFUNC_LAST_CONTRIBUTE_MINTIME		= 64901,
	//AT_EMFUNC_END							= 65000,
	
	AT_ACHIEVEMENT_DATA_MAX					= 65000,// 업적 검사용 데이터 선언 최대 ( 설마 업적 기록용 데이터 종류가 1000개를 넘기진 않것지 ㅡㅡ;;)

	AT_MONSTER_TUNNING_NO					= 65001,
	AT_MONSTER_TUNNING_GRADE				= 65002,
	AT_MONSTER_TUNNING_USER_LV				= 65003,
	AT_MONSTER_TUNNING_WEIGHT				= 65004,

	AT_SHARE_HP_RELATIONSHIP				= 65006,

	AT_STRATEGYSKILL_OPEN					= 65008,//전략스킬 오픈유무
	AT_STRATEGYSKILL_TABNO					= 65009,//사용중인 전략스킬 번호
	AT_SKILLSET_USE_COUNT					= 65010,//SkillSet CashItem 사용갯수

	AT_ACHIEVEMENT_TOTAL_POINT				= 65011, // 업적 달성 토탈 Point
	AT_ACHIEVEMENT_TOTAL_POINT_CATEGORY_1	= AT_ACHIEVEMENT_TOTAL_POINT + 1, // 65012, 카테고리 1, 성장 포인트
	AT_ACHIEVEMENT_TOTAL_POINT_CATEGORY_2	= AT_ACHIEVEMENT_TOTAL_POINT + 2, // 65013, 카테고리 2, 아이템 포인트
	AT_ACHIEVEMENT_TOTAL_POINT_CATEGORY_3	= AT_ACHIEVEMENT_TOTAL_POINT + 3, // 65014, 카테고리 3, 퀘스트 포인트
	AT_ACHIEVEMENT_TOTAL_POINT_CATEGORY_4	= AT_ACHIEVEMENT_TOTAL_POINT + 4, // 65015, 카테고리 4, 월드 포인트
	AT_ACHIEVEMENT_TOTAL_POINT_CATEGORY_5	= AT_ACHIEVEMENT_TOTAL_POINT + 5, // 65016, 카테고리 5, 미션 포인트
	AT_ACHIEVEMENT_TOTAL_POINT_CATEGORY_6	= AT_ACHIEVEMENT_TOTAL_POINT + 6, // 65017, 카테고리 6, 기타 포인트(대부분 0으로 셋팅됨)

	AT_STRATEGY_FATIGABILITY				= 65101, // 전략피로도. 전략디펜스(F7).
	AT_RECOVERY_STRATEGY_FATIGABILITY		= 65102, // 전략피로도 회복.

	AT_GUADIANDISCOUNT_TYPE					= 65201, // 가디언 설치비 할인 어빌.
	AT_GUADIANDISCOUNT_RATE					= 65202, // 가디언 설치비 할인율.

	AT_INSTANCE_ITEM						= 65301, // 인스턴스 아이템. 어빌이 1로 되있으면 인스턴스 아이템.

	AT_IGNORE_PVP_MODE_ABIL					= 65401, // PvP시에 옵션 증폭값을 제외해야하는데 PvP중인지 판단을 AT_TEAM어빌과 AT_DUEL어빌로함.
													 // 문제는 디펜스 모드에서 AT_TEAM Abil이 세팅되는데 PvP로 판단하여 옵션 증폭값을 제외하게 됨.
													 // 이 어빌이 세팅 되어있으면, AT_TEAM이나 AT_DUEL이 세팅 되어있어도 무시하고 PvP중이 아니라고 판단함.

// PvPLobby에서만 사용하는 어빌
	AT_PVP_ROOM_INDEX						= 65500,
	AT_PVP_CELL_INDEX						= 65501,

	AT_DEBUG_JOBSKILL						= 65530,
	AT_MAX_ABIL								= USHRT_MAX,//65535( 이값을 넘으면 안된다 )

}EAbilType;

#define AT_ACHIEVEMENT_MISSION_KEY(key,level) (AT_ACHIEVEMENT_MISSION_MIN + (key * 10) + level)

typedef enum eDamageActionType
{
	E_DMGACT_TYPE_DEFAULT			= 0,
	E_DMGACT_TYPE_NODELAY			= 1,// No Delay
	E_DMGACT_TYPE_ONLY_DAMAGE		= 10, // Only Damage
	E_DMGACT_TYPE_NO				= 101,
	E_DMGACT_AI_CHASE_ENEMY			= 0x40000000,
	E_DMGACT_AI_FIRESKILL			= 0x80000000,
	E_DMGACT_CHECK					= 0xF00000FF,

	E_DMGACT_TYPE_TRANSIT_PARENT	= 0x00000100, //(256)
	E_DMGACT_TYPE_PART_SUPERARMOUR	= 0x00000200, //(512)
}EDamageActionType;

enum eEffectControlType
{
	E_EFFCONTROL_NONE				= 0x00,
	E_EFFCONTROL_DEL_MONEY			= 0x01,
	E_EFFCONTROL_DEL_ITEM			= 0x02,
	E_EFFCONTROL_REQ_SERVER			= E_EFFCONTROL_DEL_MONEY|E_EFFCONTROL_DEL_ITEM,	// 서버한테 판단을 요청(BitFlag)
};
typedef BYTE EffectControlType;

typedef enum eDynamicAbilType
{
	// 몬스터가 주는 경험치
	DAT_NO_RC_TYPE_MIN				= 3000						,
	DAT_DIE_EXP						= 3030/*AT_DIE_EXP-3*/		,
	DAT_DIE_EXP_GRADE1											,
	DAT_DIE_EXP_GRADE2											,
	DAT_DIE_EXP_GRADE3											,
	DAT_DIE_EXP_GRADE4											,
	DAT_NO_RC_TYPE_MAX				= 4000						,

	DAT_RC_TYPE_MIN					= AT_CALCUATEABIL_MIN-1		,
	DAT_MAX_HP						= AT_MAX_HP-1				,
	DAT_MAX_HP_GRADE1											,
	DAT_MAX_HP_GRADE2											,
	DAT_MAX_HP_GRADE3											,
	DAT_MAX_HP_GRADE4											,
	DAT_HP_RECOVERY_INTERVAL		= AT_HP_RECOVERY_INTERVAL-1	,
	DAT_HP_RECOVERY_INTERVAL_GRADE1								,
	DAT_HP_RECOVERY_INTERVAL_GRADE2								,
	DAT_HP_RECOVERY_INTERVAL_GRADE3								,
	DAT_HP_RECOVERY_INTERVAL_GRADE4								,
	DAT_MAX_MP						= AT_MAX_MP-1				,
	DAT_MAX_MP_GRADE1											,
	DAT_MAX_MP_GRADE2											,
	DAT_MAX_MP_GRADE3											,
	DAT_MAX_MP_GRADE4											,
	DAT_MP_RECOVERY_INTERVAL		= AT_MP_RECOVERY_INTERVAL-1	,
	DAT_MP_RECOVERY_INTERVAL_GRADE1								,
	DAT_MP_RECOVERY_INTERVAL_GRADE2								,
	DAT_MP_RECOVERY_INTERVAL_GRADE3								,
	DAT_MP_RECOVERY_INTERVAL_GRADE4								,
	DAT_STR							= AT_STR-1					,
	DAT_STR_GRADE1												,
	DAT_STR_GRADE2												,
	DAT_STR_GRADE3												,
	DAT_STR_GRADE4												,
	DAT_INT							= AT_INT-1					,
	DAT_INT_GRADE1												,
	DAT_INT_GRADE2												,
	DAT_INT_GRADE3												,
	DAT_INT_GRADE4												,
	DAT_CON							= AT_CON-1					,
	DAT_CON_GRADE1												,
	DAT_CON_GRADE2												,
	DAT_CON_GRADE3												,
	DAT_CON_GRADE4												,
	DAT_DEX							= AT_DEX-1					,
	DAT_DEX_GRADE1												,
	DAT_DEX_GRADE2												,
	DAT_DEX_GRADE3												,
	DAT_DEX_GRADE4												,
	DAT_MOVESPEED					= AT_MOVESPEED-1			,
	DAT_MOVESPEED_GRADE1										,
	DAT_MOVESPEED_GRADE2										,
	DAT_MOVESPEED_GRADE3										,
	DAT_MOVESPEED_GRADE4										,
	DAT_PHY_DEFENCE					= AT_PHY_DEFENCE-1			,
	DAT_PHY_DEFENCE_GRADE1										,
	DAT_PHY_DEFENCE_GRADE2										,
	DAT_PHY_DEFENCE_GRADE3										,
	DAT_PHY_DEFENCE_GRADE4										,
	DAT_MAGIC_DEFENCE				= AT_MAGIC_DEFENCE-1		,
	DAT_MAGIC_DEFENCE_GRADE1									,
	DAT_MAGIC_DEFENCE_GRADE2									,
	DAT_MAGIC_DEFENCE_GRADE3									,
	DAT_MAGIC_DEFENCE_GRADE4									,
	DAT_ATTACK_SPEED				= AT_ATTACK_SPEED-1			,
	DAT_ATTACK_SPEED_GRADE1										,
	DAT_ATTACK_SPEED_GRADE2										,
	DAT_ATTACK_SPEED_GRADE3										,
	DAT_ATTACK_SPEED_GRADE4										,
	DAT_BLOCK_SUCCESS_VALUE					= AT_BLOCK_SUCCESS_VALUE-1			,
	DAT_BLOCK_SUCCESS_VALUE_GRADE1										,
	DAT_BLOCK_SUCCESS_VALUE_GRADE2										,
	DAT_BLOCK_SUCCESS_VALUE_GRADE3										,
	DAT_BLOCK_SUCCESS_VALUE_GRADE4										,
	DAT_DODGE_SUCCESS_VALUE					= AT_DODGE_SUCCESS_VALUE-1			,
	DAT_DODGE_SUCCESS_VALUE_GRADE1										,
	DAT_DODGE_SUCCESS_VALUE_GRADE2										,
	DAT_DODGE_SUCCESS_VALUE_GRADE3										,
	DAT_DODGE_SUCCESS_VALUE_GRADE4										,
	DAT_CRITICAL_SUCCESS_VALUE				= AT_CRITICAL_SUCCESS_VALUE-1		,
	DAT_CRITICAL_SUCCESS_VALUE_GRADE1									,
	DAT_CRITICAL_SUCCESS_VALUE_GRADE2									,
	DAT_CRITICAL_SUCCESS_VALUE_GRADE3									,
	DAT_CRITICAL_SUCCESS_VALUE_GRADE4									,
	DAT_CRITICAL_POWER				= AT_CRITICAL_POWER-1		,
	DAT_CRITICAL_POWER_GRADE1									,
	DAT_CRITICAL_POWER_GRADE2									,
	DAT_CRITICAL_POWER_GRADE3									,
	DAT_CRITICAL_POWER_GRADE4									,
	DAT_INVEN_SIZE					= AT_INVEN_SIZE-1			,
	DAT_INVEN_SIZE_GRADE1										,
	DAT_INVEN_SIZE_GRADE2										,
	DAT_INVEN_SIZE_GRADE3										,
	DAT_INVEN_SIZE_GRADE4										,
	DAT_EQUIPS_SIZE					= AT_EQUIPS_SIZE-1			,
	DAT_EQUIPS_SIZE_GRADE1										,
	DAT_EQUIPS_SIZE_GRADE2										,
	DAT_EQUIPS_SIZE_GRADE3										,
	DAT_EQUIPS_SIZE_GRADE4										,
	DAT_ATTACK_RANGE				= AT_ATTACK_RANGE-1			,
	DAT_ATTACK_RANGE_GRADE1										,
	DAT_ATTACK_RANGE_GRADE2										,
	DAT_ATTACK_RANGE_GRADE3										,
	DAT_ATTACK_RANGE_GRADE4										,
	DAT_HP_RECOVERY					= AT_HP_RECOVERY-1			,
	DAT_HP_RECOVERY_GRADE1										,
	DAT_HP_RECOVERY_GRADE2										,
	DAT_HP_RECOVERY_GRADE3										,
	DAT_HP_RECOVERY_GRADE4										,
	DAT_MP_RECOVERY					= AT_MP_RECOVERY-1			,
	DAT_MP_RECOVERY_GRADE1										,
	DAT_MP_RECOVERY_GRADE2										,
	DAT_MP_RECOVERY_GRADE3										,
	DAT_MP_RECOVERY_GRADE4										,
	DAT_JUMP_HEIGHT					= AT_JUMP_HEIGHT-1			,
	DAT_JUMP_HEIGHT_GRADE1										,
	DAT_JUMP_HEIGHT_GRADE2										,
	DAT_JUMP_HEIGHT_GRADE3										,
	DAT_JUMP_HEIGHT_GRADE4										,
	DAT_PHY_ATTACK_MAX				= AT_PHY_ATTACK_MAX-1		,
	DAT_PHY_ATTACK_MAX_GRADE1									,
	DAT_PHY_ATTACK_MAX_GRADE2									,
	DAT_PHY_ATTACK_MAX_GRADE3									,
	DAT_PHY_ATTACK_MAX_GRADE4									,
	DAT_PHY_ATTACK_MIN				= AT_PHY_ATTACK_MIN-1		,
	DAT_PHY_ATTACK_MIN_GRADE1									,
	DAT_PHY_ATTACK_MIN_GRADE2									,
	DAT_PHY_ATTACK_MIN_GRADE3									,
	DAT_PHY_ATTACK_MIN_GRADE4									,
	DAT_TARGET_BACK_DISTANCE		= AT_TARGET_BACK_DISTANCE-1	,
	DAT_TARGET_BACK_DISTANCE_GRADE1								,
	DAT_TARGET_BACK_DISTANCE_GRADE2								,
	DAT_TARGET_BACK_DISTANCE_GRADE3								,
	DAT_TARGET_BACK_DISTANCE_GRADE4								,
	DAT_TARGET_FLY_DISTANCE			= AT_TARGET_FLY_DISTANCE-1	,
	DAT_TARGET_FLY_DISTANCE_GRADE1								,
	DAT_TARGET_FLY_DISTANCE_GRADE2								,
	DAT_TARGET_FLY_DISTANCE_GRADE3								,
	DAT_TARGET_FLY_DISTANCE_GRADE4								,
	DAT_NEED_MP						= AT_NEED_MP-1				,
	DAT_NEED_MP_GRADE1											,
	DAT_NEED_MP_GRADE2											,
	DAT_NEED_MP_GRADE3											,
	DAT_NEED_MP_GRADE4											,
	DAT_NEED_HP						= AT_NEED_HP-1				,
	DAT_NEED_HP_GRADE1											,
	DAT_NEED_HP_GRADE2											,
	DAT_NEED_HP_GRADE3											,
	DAT_NEED_HP_GRADE4											,
	DAT_MAGIC_ATTACK				= AT_MAGIC_ATTACK-1			,
	DAT_MAGIC_ATTACK_GRADE1										,
	DAT_MAGIC_ATTACK_GRADE2										,
	DAT_MAGIC_ATTACK_GRADE3										,
	DAT_MAGIC_ATTACK_GRADE4										,
	DAT_PHY_ATTACK					= AT_PHY_ATTACK-1			,
	DAT_PHY_ATTACK_GRADE1										,
	DAT_PHY_ATTACK_GRADE2										,
	DAT_PHY_ATTACK_GRADE3										,
	DAT_PHY_ATTACK_GRADE4										,
	DAT_CRITICAL_MPOWER				= AT_CRITICAL_MPOWER-1		,
	DAT_CRITICAL_MPOWER_GRADE1									,
	DAT_CRITICAL_MPOWER_GRADE2									,
	DAT_CRITICAL_MPOWER_GRADE3									,
	DAT_CRITICAL_MPOWER_GRADE4									,
	DAT_HIT_SUCCESS_VALUE						= AT_HIT_SUCCESS_VALUE-1				,
	DAT_HIT_SUCCESS_VALUE_GRADE1											,
	DAT_HIT_SUCCESS_VALUE_GRADE2											,
	DAT_HIT_SUCCESS_VALUE_GRADE3											,
	DAT_HIT_SUCCESS_VALUE_GRADE4											,
	DAT_WALK_SPEED					= AT_WALK_SPEED-1			,
	DAT_WALK_SPEED_GRADE1										,
	DAT_WALK_SPEED_GRADE2										,
	DAT_WALK_SPEED_GRADE3										,
	DAT_WALK_SPEED_GRADE4										,
	DAT_MAGIC_ATTACK_MAX			= AT_MAGIC_ATTACK_MAX-1		,
	DAT_MAGIC_ATTACK_MAX_GRADE1									,
	DAT_MAGIC_ATTACK_MAX_GRADE2									,
	DAT_MAGIC_ATTACK_MAX_GRADE3									,
	DAT_MAGIC_ATTACK_MAX_GRADE4									,
	DAT_MAGIC_ATTACK_MIN			= AT_MAGIC_ATTACK_MIN-1		,
	DAT_MAGIC_ATTACK_MIN_GRADE1									,
	DAT_MAGIC_ATTACK_MIN_GRADE2									,
	DAT_MAGIC_ATTACK_MIN_GRADE3									,
	DAT_MAGIC_ATTACK_MIN_GRADE4									,
	DAT_PHY_DMG_DEC					= AT_PHY_DMG_DEC-1			,
	DAT_PHY_DMG_DEC_GRADE1										,
	DAT_PHY_DMG_DEC_GRADE2										,
	DAT_PHY_DMG_DEC_GRADE3										,
	DAT_PHY_DMG_DEC_GRADE4										,
	DAT_MAGIC_DMG_DEC				= AT_MAGIC_DMG_DEC-1		,
	DAT_MAGIC_DMG_DEC_GRADE1									,
	DAT_MAGIC_DMG_DEC_GRADE2									,
	DAT_MAGIC_DMG_DEC_GRADE3									,
	DAT_MAGIC_DMG_DEC_GRADE4									,
	DAT_CASTING_SPEED				= AT_CASTING_SPEED-1		,
	DAT_CASTING_SPEED_GRADE1									,
	DAT_CASTING_SPEED_GRADE2									,
	DAT_CASTING_SPEED_GRADE3									,
	DAT_CASTING_SPEED_GRADE4									,
	DAT_RESIST_FIRE					= AT_RESIST_FIRE-1			,
	DAT_RESIST_FIRE_GRADE1										,
	DAT_RESIST_FIRE_GRADE2										,
	DAT_RESIST_FIRE_GRADE3										,
	DAT_RESIST_FIRE_GRADE4										,
	DAT_RESIST_WATER				= AT_RESIST_WATER-1			,
	DAT_RESIST_WATER_GRADE1										,
	DAT_RESIST_WATER_GRADE2										,
	DAT_RESIST_WATER_GRADE3										,
	DAT_RESIST_WATER_GRADE4										,
	DAT_RESIST_TREE					= AT_RESIST_TREE-1			,
	DAT_RESIST_TREE_GRADE1										,
	DAT_RESIST_TREE_GRADE2										,
	DAT_RESIST_TREE_GRADE3										,
	DAT_RESIST_TREE_GRADE4										,
	DAT_RESIST_IRON					= AT_RESIST_IRON-1			,
	DAT_RESIST_IRON_GRADE1										,
	DAT_RESIST_IRON_GRADE2										,
	DAT_RESIST_IRON_GRADE3										,
	DAT_RESIST_IRON_GRADE4										,
	DAT_RESIST_EARTH				= AT_RESIST_EARTH-1			,
	DAT_RESIST_EARTH_GRADE1										,
	DAT_RESIST_EARTH_GRADE2										,
	DAT_RESIST_EARTH_GRADE3										,
	DAT_RESIST_EARTH_GRADE4										,
	DAT_HP_POTION_ADD_RATE			= AT_HP_POTION_ADD_RATE-1	,
	DAT_HP_POTION_ADD_RATE_GRADE1								,
	DAT_HP_POTION_ADD_RATE_GRADE2								,
	DAT_HP_POTION_ADD_RATE_GRADE3								,
	DAT_HP_POTION_ADD_RATE_GRADE4								,
	DAT_MP_POTION_ADD_RATE			= AT_MP_POTION_ADD_RATE-1	,
	DAT_MP_POTION_ADD_RATE_GRADE1								,
	DAT_MP_POTION_ADD_RATE_GRADE2								,
	DAT_MP_POTION_ADD_RATE_GRADE3								,
	DAT_MP_POTION_ADD_RATE_GRADE4								,
	DAT_DMG_REFLECT_RATE			= AT_DMG_REFLECT_RATE-1		,
	DAT_DMG_REFLECT_RATE_GRADE1									,
	DAT_DMG_REFLECT_RATE_GRADE2									,
	DAT_DMG_REFLECT_RATE_GRADE3									,
	DAT_DMG_REFLECT_RATE_GRADE4									,
	DAT_DMG_REFLECT_HITRATE			= AT_DMG_REFLECT_HITRATE-1	,
	DAT_DMG_REFLECT_HITRATE_GRADE1								,
	DAT_DMG_REFLECT_HITRATE_GRADE2								,
	DAT_DMG_REFLECT_HITRATE_GRADE3								,
	DAT_DMG_REFLECT_HITRATE_GRADE4								,
	DAT_PENETRATION_RATE			= AT_PENETRATION_RATE-1		,
	DAT_PENETRATION_RATE_GRADE1									,
	DAT_PENETRATION_RATE_GRADE2									,
	DAT_PENETRATION_RATE_GRADE3									,
	DAT_PENETRATION_RATE_GRADE4									,
// 	DAT_MAX_DP						= AT_MAX_DP-1				,
// 	DAT_MAX_DP_GRADE1											,
// 	DAT_MAX_DP_GRADE2											,
// 	DAT_MAX_DP_GRADE3											,
// 	DAT_MAX_DP_GRADE4											,
// 	DAT_DP_RECOVERY_INTERVAL		= AT_DP_RECOVERY_INTERVAL-1	,
// 	DAT_DP_RECOVERY_INTERVAL_GRADE1								,
// 	DAT_DP_RECOVERY_INTERVAL_GRADE2								,
// 	DAT_DP_RECOVERY_INTERVAL_GRADE3								,
// 	DAT_DP_RECOVERY_INTERVAL_GRADE4								,
	DAT_RC_TYPE_MAX					= AT_CALCUATEABIL_MAX		,
}EDynamicAbilType;

int const USE_AMOUNT_BASE_VALUE = 100000000;

int const ABILITY_RATE_VALUE = 10000;
__int64 const ABILITY_RATE_VALUE64 = 10000i64;
float const ABILITY_RATE_VALUE_FLOAT = 10000.0f;
float const ABILITY_FLOAT_MULTIFLY = 1000.0f;

#define MAKE_ABIL_RATE(value) ((value) * 100)

typedef enum eSkillAttribute
{
	SAT_MAINTENANCE_CAST = 0x00000001,	// 한번 발사로, 계속적으로 발사상태를 유지하는 스킬(체인라이트닝 같은 스킬)
	SAT_CLIENT_CTRL_PROJECTILE = 0x00000002,	// 클라이언트가 충돌체크하는 발사체 스킬
	SAT_SERVER_FIRE	= 0x00000004,	// Server에서 SAT_CLIENT_CTRL_PROJECTILE 속성과 상관없이 Fire 함수를 호출
	SAT_PHYSICS		= 0x01000000,	// 물리공격 Skill (16777216)
	SAT_MAGIC		= 0x02000000,	// 마법공격 skill (33554432)
	//SAT_CHARGING	= 0x04000000,	// Charging 공격인가? (67108864)
	SAT_DEFAULT		= 0x08000000,	// Default skill (배우지 않아도 기본으로 할 수 있는 스킬) (134217728)
} ESkillAttribute;	// AT_SKILL_ATT(2011)

typedef enum : int
{
	AUTOHEAL_NONE	= 0x00,
	AUTOHEAL_HP		= 0x01,
	AUTOHEAL_MP		= 0x02,
//	AUTOHEAL_DP		= 0x04,

	AUTOHEAL_PLAYER = AUTOHEAL_HP|AUTOHEAL_MP,
	AUTOHEAL_PET	= AUTOHEAL_MP,
	AUTOHEAL_MONSTER = AUTOHEAL_NONE,
} EAutoHealMode;

typedef enum eUnitGender
{
	UG_MALE = 1,
	UG_FEMALE = 2,
	UG_UNISEX = 3,
} EUnitGender;

typedef enum eAttackedUnitPos
{
	EAttacked_Pos_None = 0,
	EAttacked_Pos_Normal = (1<<0),
	EAttacked_Pos_ground = (1<<1),	// 바닥에 누워진 상태
	EAttacked_Pos_Blowup = (1<<2),	// 공중에 띄워진 상태
	EAttacked_Pos_Obstacle = (1<<3),	//캐릭터와 타겟 사이에 장애물이 있는지 검사
} EAttackedUnitPos;

typedef enum eAttackRangeSource
{
	EAttackRange_SkillRange	= 0,	// Skill:AT_ATTACK_RANGE 값을 읽는다.
	EAttackRange_SkillRange2 = 1,	// EAttackRange_SkillRange와 완전히 동일한 의미
	EAttackRange_ItemRange = 2,		// Weapon:AT_ATTACK_RANGE 값을 읽는다.
	EAttackRange_Skill_Item = 3,	// Skill+Item Range
	EAttackRange_UnitRange = 4,		// Unit:AT_ATTACK_RANGE 값을 사용한다.
} EAttackRangeSource;

typedef enum eSkillArea
{
	ESArea_Sphere = 0,	// Default : 구형태의 Skill Area
	ESArea_Cube = 1,	// 육면체 형태의 SkillArea
	ESArea_Cone = 2,	// 원뿔형의 SkillArea
	ESArea_Front_Sphere = 3, //내 앞 방향으로 일정거리 앞에서 다시 원으로 체크
	ESArea_Unit_Cube	= 4, //Unit을 기준으로 육면체 형태
	ESArea_Front_DoubleSphere = 5, //Unit앞쪽에 구형태의 2개 Area 생성
}ESkillArea;

typedef enum eUseItemCustomType
{
	UICT_NONE = 0,
	UICT_RESET_SKILL_POINT = 1,	
	UICT_SMS = 2,	
	UICT_LETTER = 3,
	UICT_PARTY = 4,
	UICT_COUPLE = 5,
	UICT_SEAL_REMOVE = 6,
	UICT_MARKET_MODIFY = 7,
	UICT_OPEN_CHEST = 8, //복주머니, 아이템 상자 등..
	UICT_BONUS_RATE_BUF = 9,	//추가 경험치 얻기.(%. 시간으로?) 경험치, 드랍율.
	UICT_ITEM_NAME_CHANGE = 10, //
//	UICT_AIG = 11,//아이템 보험 -> 번호 고정임. 이렇게 할 필요는 없음.
	UICT_INSURANCE = 12,//사망보험
	UICT_ELIXIR = 13,//HP, MP 엘릭서.
	UICT_SAFEMODE = 14,//안전거품
	UICT_RENTALSAFE = 15,// 캐시샵 창고
	UICT_USERMAPMOVE = 16,// 순간이동 카드
	UICT_MOVETOPARTYMEMBER = 17,// 파티원에게로 이동
	UICT_SUMMONPARTYMEMBER = 18,// 파티원 소환
	UICT_ADD_SP = 19,	// Add SkillPoint
	UICT_REST = 20,		// 휴식 아이템
	UICT_OPEN_PACK = 21,// 팩 아이템 
	UICT_REVIVE = 22,	// 부활 아이템
	UICT_CHAOS_PORTAL = 23, //카오스 포털
	UICT_HIDDEN_PORTAL = 24, //히든 포털
	UICT_GUILDMarkChange1 = 25, // 길드 마크 변경(캐쉬탬)
	UICT_BIND = 26,	// 바인딩 아이템(캐시탬) 자물통?
	UICT_UNBIND = 27,// 언바인드 아이템(캐시템) 열쇠?
	UICT_STYLEITEM = 28,// 얼굴/머리카락/머리색
	UICT_INVEXTEND = 29,// 인밴토리 칸 확장
	UICT_SAFEEXTEND = 30,// 창고 칸 확장
	UICT_CREATE_CARD = 31,// 캐릭터 카드 생성
	UICT_MODIFY_CARD = 32,// 캐릭터 카드 수정
	UICT_USER_PORTAL = 33,// 위치 저장 포탈
	UICT_MONEY_PACK	= 34,// 머니팩
	UICT_CASH_PACK	= 35,// 캐시팩
	UICT_SEAL		= 36,// 봉인
	UICT_MONSTERCARD = 37,// 몬스터 카드
	UICT_DESTROYCARD = 38,// 파괴 카드
	UICT_EMOTION	 = 39,// 이모션 카드 그룹
	UICT_ROLLBACK	= 40,// 인첸트 롤백 아이템
	UICT_SOCKET_SUCCESS = 41,// 소켓 생성 성공 확률 상승 아이템
	UICT_LOCKED_CHEST = 42,// 잠긴 상자
	UICT_CHEST_KEY	  = 43,// 상자 오픈용 키
	UICT_BLANK		  = 44,// 꽝 아이템
	UICT_ONECEMORE	  =	45,// 한번 더
	UICT_CHANGE_CLASS = 46,// 전직
	UICT_GAMBLE		  = 47,// 겜블 아이템
	UICT_SUPER_GIRL	  = 48,// 슈퍼걸 아이템
	UICT_ENCHANT_INSURANCE	= 49,// 인첸트 보험
	UICT_PLUSE_SUCCESS		= 50,// 인첸트 성공 확률 아이템
	UICT_RARITY_SUCCESS		= 51,// 소울 성공 확률 아이템
	UICT_PET_EGG			= 52,// Pet의 Egg
	UICT_PET				= 53,// Pet호출 아이템
	UICT_CALL_MARKET		= 54,// 마켓 호출
	UICT_CALL_SAFE			= 55,// 창고 호출
	UICT_PROTECTION_GALL	= 56,// 내구도 소모 방지
	UICT_HELP_END_QUEST		= 57,// 퀘스트 종료를 도와준다
	UICT_PET_FEED			= 58,// 펫 사료
	UICT_EXPCARD			= 59,// 경험치 카드
	UICT_EXPCARD_BREAKER	= 60,
	UICT_LEARNSKILL			= 61,// 스킬 배우기
	UICT_MAKING_SUCCESS		= 62,// 요리/조합 성공 확률 아이템
	UICT_EXTEND_MAX_IDX		= 63,// 인벤토리 최대 슬롯 확장 아이템
	UICT_SAFE_EXTEND_MAX_IDX= 64,// 창고 최대 슬롯 확장 아이템
	UICT_HOME_STYLEITEM		= 65,// 홈 외형 정보 변경 아이템
	UICT_COUPLE_ITEM		= 66,// 커플 일 때 사용

	UICT_HOME_POSTBOX		= 67,// 마이홈 우편함
	UICT_HOME_SAFEBOX		= 68,// 마이홈 창고

	UICT_GAMBLE_COIN		= 69,// 겜블용 코인
	UICT_ACHIEVEMENT		= 70,// 업적 달성용 아이템

	UICT_COOLTIME_RATE_SKILL= 71,// 스킬 쿨타임 천분율 적용 버프 아이템
	UICT_ADD_COOLTIME_SKILL	= 72,// 스킬 쿨타임 삭제 아이템

	UICT_PET_GROWTH			= 73,// Pet성장
	UICT_CALL_STORE			= 74,// 상점 호출
	UICT_FORCED_ENCHANT		= 75,// 강제로 인첸트 정보 변경
	UICT_EQUIP_LEVELLIMIT	= 76,// 장비 제한 렙 변경
	UICT_REPAIR_ITEM		= 77,// 장비 수리 아이템
	UICT_EXTEND_CHRACTERNUM	= 78,// 캐릭터 생성 슬롯 확장	
	UICT_TELEPORT			= 79,// 텔레포트 스크롤
	UICT_SHARE_RENTALSAFE_CASH = 80,// 랠름 계정 공유 창고(캐시) : 공유 금고1~4 확장 가능
	UICT_CALL_SHARE_SAFE	= 81,// 공유 창고 호출
	UICT_PET_EQUIP			= 82,// 펫용 장착 아이템
	UICT_STATUS_RESET		= 83,	// Status Reset (AT_STR_ADD, AT_INT_ADD, AT_CON_ADD, AT_DEX_ADD, AT_ALL_STATUS)

	UICT_COOLTIME_RATE_ITEM	= 84,// 아이템 쿨타임 천분율 적용 버프 아이템
	UICT_ADD_COOLTIME_ITEM	= 85,// 아이템 쿨타임 삭제 아이템

	UICT_REPAIR_MAX_DURATION= 86,// 아이템 최대 내구도 수리 아이템(깍여진 최대 내구도를 회복 시킨다.)
	UICT_AWAKE_INCREASE_ITEM = 87,// 각성값 증가 아이템

	UICT_EVENT_ITEM_REWARD	= 88,// 퍼블리셔 수정 가능한 아이템 지급 박스

	UICT_TRANSTOWER_DISCOUNT	= 89,// 전송타워 할인권
	UICT_TRANSTOWER_OPENMAP		= 90,// 전송타워 오픈맵

	UICT_CERTIFICATEOFHERO	= 91,	// 용자의 증표 

	UICT_PET_RENAME			= 92,
	UICT_PET_COLORCHANGE	= 93,

	UICT_HARDCORE_KEY		= 94,	// 하드코어 입장권

	UICT_HOME_SIDEJOB_NPC	= 95,	// 마이홈 소울크래프트 NPC

	UICT_HARDCORE_BOSSKEY	= 96,// 하드코어 보스 입장권

	UICT_CALL_HELP			= 97,	// 헬프 UI를 호출하는 아이템

	UICT_EVENT_ITEM_REWARD_GAMBLE = 98,// 퍼블리셔 수정 가능한 아이템 지급 박스 겜블 연출이 있는것

	UICT_ENCHANT_OFFENCE		= 99,	// 무기 강화 가루
	UICT_ENCHANT_DEFENCE		= 100,	// 방어구 강화 가루

	UICT2_CHECK_PLAYER_CONDITION = 101,// 이 값이 있으면 캐릭터의 상태를 검사해야 한다. 상태 검사가 필요한 아이템 보다 필요 없는 아이템이 더 많아서 변경함

	UICT_ACTIVATE_SKILL			= 102,

	UICT_HIDDEN_REWORD		= 103,//히든 맵에서 얻는 보상 상자아이템

	UICT_REDICE_ITEM_OPTION	= 104,//아이템 옵션 변경 아이템

	UICT_REDICE_PET_OPTION	= 105,//펫 옵션 변경 아이템

	UICT_UPGRADE_OPTION		= 106,// 옵션 강화 아이템
	UICT_SKILLSET_OPEN		= 107,//SkillSet
	UICT_MONSTER_CARD_TYPE2	= 108,
	UICT_REBUILD_RAND_QUEST			= 109,// 랜덤 퀘스트 다시 하기(기간제)
	UICT_REBUILD_RAND_QUEST_CONSUME	= 110,// 랜덤 퀘스트 다시 하기(소모)

	UICT_OPTION_AMP_ITEM	= 111,// 옵션 증폭 아이템
	
	UICT_MAKING_INSURANCE	= 113,// 요리 보험 (레시피 보호)

	UICT_MISSION_DEFENCE_CONSUME		= 114,// 미션 입장 아이템
	UICT_MISSION_DEFENCE_CONSUME_ALL	= 115,// 미션 입장 아이템
	UICT_SUPER_GROUND_FEATHER			= 116,// 슈퍼던젼 부활 깃털
	UICT_MISSION_DEFENCE_TIMEPLUS		= 117,// 미션 방어시간 증가
	UICT_SKILL_EXTEND					= 118,	// 스킬 레벨 확장 카드
	UICT_SKILLEXTEND_INSURANCE			= 119,// 스킬 확장 카드 보험
	UICT_REST_EXP						= 120,// 휴식 경험치 회복
	UICT_SUPER_GROUND_MOVE_FLOOR		= 121,// 슈퍼던젼 층 이동 아이템
	UICT_MISSION_DEFENCE_POTION			= 122,// 미션 수호석 회복 아이템
	UICT_STRATEGYSKILL_OPEN				= 123,// 전략스킬 활성화
	UICT_SUPER_GROUND_ENTER_FLOOR		= 124,// 슈퍼던젼 해당 층으로 바로 입장 아이템

	UICT_ENCHANTSHIFT_INSURANCE			= 125,//인챈트 전이 보험 스크롤	

	UICT_GUILD_INV_EXTEND_LINE			= 126,//길드금고 1라인(8칸) 확장
	UICT_GUILD_INV_EXTEND_TAB			= 127,//길드금고 1탭 확장

	UICT_MISSION_DEFENCE7_ITEM			= 128,//신규 디팬스 모드 아이템

	UICT_SHARE_RENTALSAFE_GOLD			= 130,// 랠름 계정 공유 창고(골드) : 공유 금고1만 확장 가능

	UICT_SCROLL_QUEST					= 140,// 퀘스트 스크롤 아이템(소비)

	UICT_RESET_ATTACHED					= 200,// 장착 귀속 해제

	UICT_ENCHANT_SHIFT					= 201,// 인첸트 전이 구슬

	UICT_REPAIR_ITEM_ALL				= 202,// 장비한 모든 아이템 수리

	UICT_NOT_DISPLAY_DURATION			= 203,// 내구도 표기하지 않는 아이템(AT_USE_ITEM_CUSTOM_VALUE_4 어빌에 저장된 값 사용)
	
	UICT_VENDOR			= 204,// 노점 열기
	UICT_JOBSKILL_SAVEIDX				= 205,
	UICT_OPEN_PACK2						= 206,

	UICT_REMOVE_SOCKET					= 207,// 소켓 막힌거 복원
	UICT_TREASURE_CHEST					= 208, // 보물상자
	UICT_TREASURE_CHEST_KEY				= 209, // 보물상자 열쇠
	UICT_DEFENCE7_RELAY					= 210, // 전략모드 이어하기 아이템

	UICT_REVIVE_PARTY					= 211,	//파티 부활 아이템
	UICT_REVIVE_EXPEDITION				= 212,	//원정대 부활 아이템

	UICT_RECOVERY_STRATEGYFATIGABILITY		= 213,	// 전략 피로도 회복 아이템(절대값).
	UICT_R_RECOVERY_STRATEGYFATIGABILITY	= 214,	// 전략 피로도 회복 아이템(상대값).

	UICT_PREMIUM_SERVICE				= 215,	//프리미엄 서비스
	
	UICT_DEFENCE7_POINT_COPY			= 216,	// 전략 디펜스모드 포인트 복제기 아이템.

	UICT_ELEMENT_ENTER_CONSUME			= 217,	// 정령 던전 입장 아이템.

	UICT_MANUFACTURE					= 218,	// 즉석 가공 아이템

	UICT_SUMMON_SKILL_ACTOR				= 219,	// 스킬액터 소환
	UICT_BUNDLE_MANUFACTURE				= 220,	// 즉석가공 대량생산(캐쉬) 아이템
	UICT_RAGNAROK_ENTER					= 222,	// 라그나로크 던전 입장 아이템

	UICT_JOBSKILL_LEARN					= 223,	// 직업스킬 습득 아이템
}EUseItemCustomType;

typedef enum
{
	PET_FEED_TYPE_1			= 0,	// 펫의 사료 아이템(1차펫)
	PET_FEED_TYPE_2			= 1,	// 펫의 사료 아이템(전투용)
	PET_FEED_TRAINING		= 2,	// 2차 펫 훈련
	PET_FEED_PLAYING		= 3,	// 2차 펫 놀기 아이템
//	PET_FEED_REVIVE			= 4,	// 2차 펫의 부활 아이템(삭제)
//	PET_FEED_OTHER			= 5,	// (삭제)
	PET_FEED_MP_DRINK		= 6,	// 2차 펫의 MP Drink
//	AT_USE_ITEM_CUSTOM_VALUE_2 어빌에 저장된 값 사용
}EUseItemPetFeedType;

typedef enum eUseItemServerCheckType
{
	UISCT_NONE		= 0,
	UISCT_SCROLL	= 1,//MapMove
}EUseItemServerCheckType;

typedef enum eItemUseStateType
{
	ITEM_USE_STATE_ALIVE = 0,
	ITEM_USE_STATE_DEAD = (1<<0),
}EItemUseStateType;

typedef enum eFurnitureType
{
	FURNITURE_TYPE_NONE				= 0,
	FURNITURE_TYPE_OBJECT			= 1,
	FURNITURE_TYPE_OBJECT_ATTACH	= 2,
	FURNITURE_TYPE_WALL				= 3,
	FURNITURE_TYPE_WALL_ATTACH		= 4,
	FURNITURE_TYPE_FLOOR			= 5,
	FURNITURE_TYPE_FLOOR_ATTACH		= 6,
	FURNITURE_TYPE_NPC				= 7,
	FURNITURE_TYPE_ETC				= 10,
} EFurnitureType;

typedef enum eCountAbilFlag
{
	AT_CF_NONE				= 0x00000000,
	AT_CF_EFFECT			= 0x00000001,// Effect에서 사용
	AT_CF_EFFECT_CHK		= 0x000000FF,
	AT_CF_QUEST				= 0x00000100,// Quest에서 사용
	AT_CF_QUEST_CHK			= 0x00000F00,
	AT_CF_EVENTSCRIPT		= 0x00001000,// EventScript에서 사용
	AT_CF_EVENTSCRIPT_CHK	= 0x0000F000,
	AT_CF_HYPERMOVE			= 0x00010000,// 대점프에서 사용
	AT_CF_HYPERMOVE_CHK		= 0x000F0000,
	AT_CF_BS				= 0x00100000,// 배틀스퀘어에서 사용
	AT_CF_BS_CHK			= 0x00F00000,
	
	// 한개씩만 사용
	AT_CF_FAKEREMOVE		= 0x01000000,
	AT_CF_FAKEREMOVE_CHK	= AT_CF_FAKEREMOVE,
	AT_CF_ELITEPATTEN		= 0x02000000,
	AT_CF_ELITEPATTEN_CHK	= AT_CF_ELITEPATTEN,
	AT_CF_GM				= 0x80000000,
	AT_CF_GM_CHK			= AT_CF_GM,

	AT_CF_ALL				= 0xFFFFFFFF,
}eCountAbilFlag;

typedef enum 
{
	EGG_NORMAL	= 0,// 일반
	EGG_BRONZE	= 1,// 청동
	EGG_SILVER	= 2,// 은
	EGG_GOLD	= 3,// 금
}E_GAMBLE_GRADE;

typedef enum eShareHpRelationship : int
{
	ESHR_NONE		= 0,
	ESHR_PARENT		= 1,
	ESHR_CHILDREN	= 2,
}EShareHpRelationship;

int const MAX_ENCHANT_SUCCESS_RATE = 100000;// 인첸트 성공확률 최대값
int const MAX_ITEM_EFFECT_ABIL_NUM = 10;// 아이템 이펙트 어빌 최대 개수(리뉴얼 어빌)

typedef enum eAdjustSkillCheckType
{// 스킬 조정하는 이펙트의 스킬 번호 검사 타입
	EASC_NONE						= 0,
	EASC_ALL						= 1,
	EASC_CHECK_SOME_SECTION			= 2,
	EASC_CHECK_EXCLUSIVE_SECTION	= 3,
}EAdjustSkillCheckType;

typedef enum eEffectDmgType
{
	EEDT_NONE		= 0,
	EEDT_PHY		= 1,
	EEDT_MAGIC		= 2,
}EEffectDmgType;

typedef enum eAwakeState
{
	EAS_NORMAL_GUAGE	= 0,
	EAS_MAX_GUAGE		= 1,
	EAS_PENALTY_GUAGE	= 2,
}EAwakeState;

typedef enum eAdjustSkillCalcType
{
	EASCT_NONE					= 0,	
	EASCT_RANGE					= 1,	// 스킬 범위1(가로 길이 등을 조정)
	EASCT_RANGE2				= 2,	// 스킬 범위2(육면체의폭, 원뿔의 각도 등을 조정)
	EASCT_DMG					= 3,	// 스킬 데미지(방어력과 계산되기 전 까지 데미지를 조정)

	// 단계별 데미지 증감
	EASCT_RESULT_MIN_DMG_BY_PHASE	= 4,	// 단계별 데미지증감에 따른 min 값
	EASCT_RESULT_MAX_DMG_BY_PHASE	= 5,	// 단계별 데미지증감에 따른 max 값
	EASCT_INC_PHASE_DMG				= 6,	// 단계별 데미지 증감 값
	//EASCT_ADJUST_SKILLCOOLTIME  = ?,	// 스킬 쿨타임(현재 기능 없음)
}EAdjustSkillCalcType;


int const DRAGONIAN_LSHIFT_VAL = 50;

typedef enum eSpecificIdleType
{// AT_SKILL_SPECIFIC_IDLE
	ESIT_NONE = 0,
	ESIT_BOSS_MONSTER_IDLE = 1,		// 보스몬스터 연출용 idle
}ESpecificIdleType;

typedef enum ePlayContentsType
{
	EPCT_NONE			= 0,
	EPCT_ELGA			= 1,
	EPCT_ELGA_BONE_MON	= 2,
	EPCT_ELGA_EYE_MON	= 3,
} EPlayContentsType;

typedef enum eUnitDieType
{
	EUDT_NONE				= 0x00,
	EUDT_NORMAL				= 0x01,
	EUDT_NOT_CHILD_DIE		= 0x02,	//자식유닛을 죽이지 않음
}EUnitDieType;

typedef enum eManufactureType
{
	EMANT_NONE			= 0,
	EMANT_SPELL			= 1,
	EMANT_COOK			= 2,
	EMANT_WORKMANSHIP	= 3,
	EMANT_AUTO			= 4,
}EManufactureType;

typedef enum eLearnSkillEvent
{
	ELSE_NONE				= 0,
	ELSE_MANUFACTURE_HELP	= 1,
}ELearnSkillEvent;

typedef enum eChangeBlockAble
{
	ECBA_NONE = 0,
	ECBA_MAKE_CAN_NOT_BLOCK = 1,
	ECBA_MAKE_CAN_BLOCK = 2,
}EChangeBlockAble;

typedef enum eEffectTypeWhenHit
{
	ETWH_DEFAULT = 0,
	ETWH_ME = 1,
}EEffectTypeWhenHit;

#endif // WEAPON_VARIANT_BASIC_CONSTANT_DEFABILTYPE_H