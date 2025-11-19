USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_CreateCharacter]    Script Date: 07/28/2009 20:00:24 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/****** Object:  StoredProcedure [dbo].[up_CreateCharacter]    Script Date: 07/28/2009 20:10:59 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_CreateCharacter]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_CreateCharacter]
GO


CREATE PROC [dbo].[up_CreateCharacter]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명: 캐릭터생성
// 작성자: Richard Kim(tigerjune@barunsoninter.com)
// 작성일: 2008-10-02
// 최종수정자: YonMy
// 수정일: 2009-02-12
// 파일명: 
//	[PARAMETER]
//	@Mode : 캐릭터 이름 중복 검사 방법
//		0 == 삭제된 캐릭터명은 검사 안함.
//		2 == 삭제된 캐릭터명도 검사
// N O T E : 
//	2008-10-28 육정범, 생성시최근위치, 최근마을0값으로생성하도록수정
//	2008-11-14 김승현, 기본장비지급하는INSERT문에Column name 지정하도록수정
//	2008-12-09 : 육정범종료퀘스트저장공간늘림
//  2009-01-03 : 최연승, 리턴값에이름추가
//	2009-02-12 : YonMy, GMLevel 제거
//	2009-03-12 : 퀵슬롯 저장 사이즈 변경 241 -> 281
//	2009-03-12 : 인밴토리확장/축소정보추가
//	2009-03-30 : 생성시 이름 검사에, State가 0 인 캐릭터 들만 검사 하도록
//	2009-03-30 : 생성시 이름 검사에, State가 0, 100, 101 인 캐릭터 들만 검사 하도록
//	2009-04-22 : Eric Kim, 이름 중복 검사 할 때 @Mode 값으로, 삭제된 캐릭터도 검사 할 것인가 결정하기
//	2009-08-09 : Eric Kim,	아이템 여러개도 초기에 지급할 수 있도록 하기.
//	2012-01-10 : 심헌섭, 점핑 캐릭터 이벤트 정보를 받아서 캐릭 생성할 수 있도록 수정
////////////////////////////////////////////////////////////////////////
*/
(
	@Mode	TINYINT,	-- 캐릭터 생성 방법
	@MemberID	UNIQUEIDENTIFIER,	-- MemberGuid
	@Name		NVARCHAR(20),	-- 캐릭터이름
	@InGender	TINYINT,		-- 성별
	@InBaseClass	INT,		-- 클래스번호(기본)
	@InClass		INT,		-- 클래스번호(적용)
	@HairStyle	INT,			-- 머리모양
	@HairColor	INT,			-- 머리색깔
	@Face		INT,			-- 얼굴표정
	@Jacket		INT,			-- 상의
	@Gloves		INT,			-- 장갑
	@Pants		INT,			-- 하의
	@Shoes		INT,				-- 신발
	@FiveElementBody		TINYINT	,-- 5속성.
	@f_State TINYINT,
	@f_Race INT,
	@f_Lv SMALLINT,	
	@f_Exp BIGINT,	
	@f_Money BIGINT,
	@f_HP INT,
	@f_MP INT,
	@f_CP INT,
	@f_ExtraSkillPoint SMALLINT,
	@f_Skills BINARY(450),
	@f_QuickSlot BINARY(281),
	@f_IngQuest BINARY(300),
	@f_EndQuest BINARY(130),
	@f_EndQuest2 BINARY(130),
	@f_EndQuestExt BINARY(260),
	@f_EndQuestExt2 BINARY(480),
	@f_InvExtend BINARY(40),
	@JumpingEventNo INT,
	@JumpingMaxRewardCount INT,
	@JumpingCharEventItemGroupNo INT,
	@MapNo INT,
	@MaxCharacterNum INT		--	최대 캐릭터 생성 가능 개수
)
AS
SET NOCOUNT ON
SET XACT_ABORT ON

DECLARE @RegistDate DATETIME
DECLARE @CharacterID UNIQUEIDENTIFIER
DECLARE @Err INT
SET @Err = 0

--1. 캐릭터이름중복검사
IF @Mode = 2
BEGIN
	-- 삭제된 캐릭터에서도 중복 검사하기
	IF EXISTS (SELECT 1 FROM dbo.TB_CharacterBasic WHERE [Name] = @Name)
	BEGIN
		SET @Err = 100  -- 중복되는캐릭터이름이있음(C소스와에러번호같음CCR_OVERLAP_NAME)
		GOTO ErrorReturn
	END
END
ELSE -- @Mode = 0
BEGIN
	-- 삭제된 캐릭터는 중복검사 하지 않음.
	IF EXISTS (SELECT 1 FROM dbo.TB_CharacterBasic WHERE [Name] = @Name AND [State] <> 1 )
	BEGIN
		SET @Err = 100  -- 중복되는캐릭터이름이있음(C소스와에러번호같음CCR_OVERLAP_NAME)
		GOTO ErrorReturn
	END
END

-- 캐시 아이템으로 확장한 슬롯 개수
DECLARE @MAX_CHARACTER_NUM INT
SET @MAX_CHARACTER_NUM = @MaxCharacterNum
SELECT @MAX_CHARACTER_NUM = @MAX_CHARACTER_NUM + isnull(ExtendCharacterNum,0) FROM dbo.TB_Member_ShareData where MemberKey = @MemberID

DECLARE @CUR_CHARACTER_NUM INT
SELECT @CUR_CHARACTER_NUM = COUNT(*) FROM dbo.TB_CharacterBasic WHERE MemberID = @MemberID AND [State] <> 1

--2. 캐릭갯수3개초과체크
IF @MAX_CHARACTER_NUM <= @CUR_CHARACTER_NUM
BEGIN
	SET @Err = 200--캐릭터갯수제한을초과하였음(max : 5개) (C소스와에러번호같음CCR_MAX_LIMINT)
	GOTO ErrorReturn
END

--3. 캐릭데이터생성
SET @RegistDate = GETDATE()
SET @CharacterID = NEWID()

--점핑캐릭터 이벤트 검사
IF @JumpingEventNo > 0
BEGIN
	DECLARE @RemainRewardCount INT

	SELECT @RemainRewardCount = RewardCount
	FROM TB_JumpingCharEvent_State
	WHERE EventNo = @JumpingEventNo AND MemberID = @MemberID
	
	IF @JumpingMaxRewardCount<>0
	BEGIN
		IF @RemainRewardCount IS NULL
		BEGIN
			INSERT INTO TB_JumpingCharEvent_State
				   ([EventNo],[MemberID],[RewardCount])
			 VALUES
				   (@JumpingEventNo, @MemberID, @JumpingMaxRewardCount)
		END
		ELSE IF @RemainRewardCount <= 0
		BEGIN
			SET @Err = 401--점핑 이벤트 캐릭터를 더이상 만들 수 없습니다.
			GOTO ErrorReturn
		END
	END
END

BEGIN TRAN
	--점핑 이벤트 캐릭터 업데이트, 그냥 무조건 -1시킴
	IF @JumpingEventNo > 0 AND @JumpingMaxRewardCount > 0
	BEGIN
		UPDATE TB_JumpingCharEvent_State
		   SET [RewardCount] = [RewardCount]-1
		 WHERE [EventNo] = @JumpingEventNo AND [MemberID] = @MemberID
	END

	
	--기본캐릭정보
	INSERT dbo.TB_CharacterBasic  ([MemberID],[CharacterID],[State],[Name],[Gender],[Race],[FiveElementBody],[HairStyle]
           ,[HairColor],[Face],[Jacket],[Gloves],[Pants],[Shoes],[BirthDate])
	VALUES (@MemberID, @CharacterID, @f_State, @Name, @InGender,	@f_Race, @FiveElementBody, 
		@HairStyle, @HairColor, @Face, @Jacket, @Gloves, @Pants, @Shoes, @RegistDate)
	IF @@error <> 0
	BEGIN
		SET @Err = 300-- TB_CharacterUser 에insert 실패(C소스와에러번호같음CCR_DB_ERR_1)
		GOTO ErrorHandler
	END

	--서브정보
	INSERT INTO [dbo].[TB_CharacterSub]
           ([CharacterID],[Class],[Lv],[Exp],[Money],[HP],[MP],[CP],[ExtraSkillPoint],[Skills]
		   ,[RecentMap],[RecentLocX],[RecentLocY],[RecentLocZ]
           ,[LastVillage],[LastVillageLocX],[LastVillageLocY],[LastVillageLocZ]
           ,[QuickSlot],[IngQuest],[EndQuest],[EndQuest2],[f_EndQuestExt],[f_EndQuestExt2],[Cash],[TotalPlayTimeSec],[Fran],[TacticsLevel],[TacticsExp]
           ,[InvExtend])
	VALUES 
		(@CharacterID, @InClass, @f_Lv, @f_Exp, @f_Money, @f_HP, @f_MP, @f_CP, @f_ExtraSkillPoint, @f_Skills, 	
		@MapNo, 0, 0, 0, 0, 0, 0, 0,
		@f_QuickSlot, @f_IngQuest, @f_EndQuest, @f_EndQuest2, @f_EndQuestExt, @f_EndQuestExt2, 0, 0, 0, 1, 0,@f_InvExtend)
	IF @@error <> 0
	BEGIN
		SET @Err = 300-- TB_CharacterUser 에insert 실패(C소스와에러번호같음CCR_DB_ERR_1)
		GOTO ErrorHandler
	END

	-- Default Given Item
	DECLARE @ITEM_TABLE TABLE(InvType tinyint, InvPos tinyint, ItemNo int, [Count] smallint, Enchant_01 bigint, Enchant_02 bigint, Enchant_03 bigint, Enchant_04 bigint, [State] tinyint)
	INSERT INTO @ITEM_TABLE
	SELECT InvType, InvPos, ItemNo, [Count], Enchant_01, Enchant_02, Enchant_03, Enchant_04, [State] FROM TB_JumpingCharEvent_Item WHERE ItemGroupNo = @JumpingCharEventItemGroupNo

	INSERT INTO @ITEM_TABLE
	SELECT f_InvType, f_InvPos, f_ItemNo, f_Count, f_Enchant_01, f_Enchant_02, f_Enchant_03, f_Enchant_04, f_State FROM [dbo].[TB_DefBaseUserItem]
	 WHERE f_Class = @InBaseClass
		 AND NOT ((f_InvType in (SELECT InvType FROM @ITEM_TABLE)) AND (f_InvPos in (SELECT InvPos FROM @ITEM_TABLE)))

	DECLARE @item_InvType tinyint
	DECLARE @item_InvPos tinyint
	DECLARE @item_ItemNo int
	DECLARE @item_Count smallint
	DECLARE @item_Enchant_01 bigint
	DECLARE @item_Enchant_02 bigint
	DECLARE @item_Enchant_03 bigint
	DECLARE @item_Enchant_04 bigint
	DECLARE @item_State tinyint
	DECLARE @Item_GUID UNIQUEIDENTIFIER
	DECLARE Item_Cursor CURSOR FOR

	SELECT * FROM @ITEM_TABLE
	OPEN Item_Cursor
	FETCH NEXT FROM Item_Cursor
		INTO @item_InvType, @item_InvPos, @item_ItemNo, @item_Count, @item_Enchant_01, @item_Enchant_02, @item_Enchant_03, @item_Enchant_04, @item_State
	WHILE @@FETCH_STATUS = 0
	BEGIN
		SET @item_GUID = NEWID()
	INSERT [dbo].[TB_UserItem] 
		([ItemGuid] ,[OwnerGuid] ,[InvType]  ,[InvPos] ,[ItemNo]
		,[Count] ,[State] ,[CreateDate])
			VALUES (@item_GUID, @CharacterID, @item_InvType, @item_InvPos, @item_ItemNo
			,@item_Count, @item_State, @RegistDate)
	IF @@error <> 0
	BEGIN
		SET @Err = 300-- TB_CharacterUser 에insert 실패(C소스와에러번호같음CCR_DB_ERR_1)
			GOTO Error_UserItem
	END
		IF (@item_Enchant_01 <> 0 OR @item_Enchant_02 <> 0 OR @item_Enchant_03 <> 0 OR @item_Enchant_04 <> 0)
		BEGIN
	INSERT [dbo].[TB_UserItem_Enchant]
		([ItemGuid], [Enchant_01], [Enchant_02], [Enchant_03], [Enchant_04])
				VALUES (@item_GUID, @item_Enchant_01, @item_Enchant_02, @item_Enchant_03, @item_Enchant_04)
	IF @@error <> 0
	BEGIN
		SET @Err = 300-- TB_CharacterUser 에insert 실패(C소스와에러번호같음CCR_DB_ERR_1)
				GOTO Error_UserItem
			END
		END

		-- NEXT Fetch
		FETCH NEXT FROM Item_Cursor
			INTO @item_InvType, @item_InvPos, @item_ItemNo, @item_Count, @item_Enchant_01, @item_Enchant_02, @item_Enchant_03, @item_Enchant_04, @item_State
	END
Error_UserItem:
	CLOSE Item_Cursor;
	DEALLOCATE Item_Cursor;

	IF (@Err <> 0)
	BEGIN
		GOTO ErrorHandler
	END
	
	-- Extern
	INSERT INTO [dbo].[TB_UserCharacter_Extern]	(	[CharacterID], [LastUpdate] )	VALUES ( @CharacterID, @RegistDate )
	IF @@error <> 0
	BEGIN
		SET @Err = 300-- TB_CharacterUser 에insert 실패(C소스와에러번호같음CCR_DB_ERR_1)
		GOTO ErrorHandler
	END

	-- Point
	INSERT INTO [dbo].[TB_UserCharacter_Point] (	[CharacterID] )	VALUES ( @CharacterID )
	IF @@error <> 0
	BEGIN
		SET @Err = 300-- TB_CharacterUser 에insert 실패(C소스와에러번호같음CCR_DB_ERR_1)
		GOTO ErrorHandler
	END
		
	COMMIT TRAN
	SELECT @Err, @CharacterID, @InGender, @InClass, @Name, @JumpingEventNo
	RETURN


ErrorHandler:
BEGIN
	ROLLBACK TRAN
	SET @CharacterID = N'00000000-0000-0000-0000-000000000000'
	SET @InClass = 0;
	SET @InGender = 0;
	SELECT @Err, @CharacterID, @InGender, @InClass, @Name, @JumpingEventNo
	RETURN
END

ErrorReturn:
BEGIN
	SET @CharacterID = N'00000000-0000-0000-0000-000000000000'
	SET @InClass = 0;
	SET @InGender = 0;
	SELECT @Err, @CharacterID, @InGender, @InClass, @Name, @JumpingEventNo
	RETURN
END

GO

