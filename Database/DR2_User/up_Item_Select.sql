USE [DR2_User]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
go

IF EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Item_Select]'))
BEGIN
	DROP PROCEDURE [dbo].[up_Item_Select]
END
GO

CREATE PROCEDURE [dbo].[up_Item_Select]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : 아이템 프로세스
// 작 성 자 : YonMy(yonmy@barunsoninter.com)
// 작 성 일 : 2009-08-25
// 최종수정자 : 
// 수 정 일 :
// 파 일 명 : 
// N O T E : 
// 2009-09-22, YonMy, Pet Skill CoolTime 추가
// 2010-02-17, YonMy, Pet 정보 변경
////////////////////////////////////////////////////////////////////////
*/ 
	@OwnerGuid	uniqueidentifier
AS
SET Nocount ON
SET Xact_Abort ON

-- 1. 아이템 베이스
SELECT	A.[ItemGuid]
	,	A.[OwnerGuid]
	,	A.[InvType]
	,	A.[InvPos]
	,	A.[ItemNo]
	,	A.[Count]
	,	ISNULL(B.[Enchant_01],0) AS Enchant_01
	,	ISNULL(B.[Enchant_02],0) AS Enchant_02
	,	ISNULL(B.[Enchant_03],0) AS Enchant_03
	,	ISNULL(B.[Enchant_04],0) AS Enchant_04
	,	A.[State]
	,	A.[CreateDate]
FROM	[dbo].[TB_UserItem]	AS A
	LEFT JOIN [dbo].[TB_UserItem_Enchant] AS B
		ON A.[ItemGuid] = B.[ItemGuid]
WHERE OwnerGuid = @OwnerGuid

-- 2. 아이템언바인드기간리스트
SELECT 	[ItemGuid]
,		[UnbindDate]
FROM 	[dbo].[TB_UserItem_UnbindDate]
WHERE	[CharacterGuid] = @OwnerGuid

-- 3. 아이템 추가 데이터 (경험치 카드)
SELECT	A.[ITEMGUID]
	,	A.[CUREXP]
	,	A.[MAXEXP]
	,	A.[ExpPer]
FROM [dbo].[TB_ExpCard] AS A
	LEFT JOIN dbo.TB_UserItem B
		ON A.ItemGuid = B.ItemGuid
WHERE B.[OwnerGuid] = @OwnerGuid

-- 4.펫
SELECT	A.[PetID]
	, 	A.[Class]
	,	A.[Lv]
	,	A.[Name]
	,	A.[Exp]
	,	A.[MP]
	,	A.[Health]
	,	A.[Mental]
	,	A.[Color]
	,	A.[Skill01]
	,	A.[Skill02]
	,	A.[Skill03]
FROM [dbo].[TB_Pet] AS A
	LEFT JOIN [dbo].[TB_UserItem] AS B
		ON A.[PetID] = B.[ItemGuid]
WHERE B.[OwnerGuid] = @OwnerGuid 
	AND B.[State] = 1

-- 5. 기간제 몬스터 카드 정보
SELECT	A.[ITEMGUID]
	,	A.[LimitTime]
FROM [dbo].[TB_UserItem_MonsterCard] AS A
	LEFT JOIN dbo.TB_UserItem B
		ON A.ItemGuid = B.ItemGuid
WHERE B.[OwnerGuid] = @OwnerGuid
