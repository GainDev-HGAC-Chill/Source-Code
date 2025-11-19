USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Post_GetUserMail]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Post_GetUserMail]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



CREATE PROCEDURE [dbo].[up_Post_GetUserMail]

@charguid uniqueidentifier,
@startindex bigint = 0,
@count int

AS
SET nocount on 
SET XACT_ABORT ON

IF @startindex = 0 
BEGIN
	SELECT @startindex = isnull(max(mailindex)+1,0) from [dbo].[TB_UserMail] (NOLOCK) where toguid = @charguid  OPTION (KEEPFIXED PLAN)
ENd

SET nocount OFF

	SELECT count(*) FROM [dbo].[TB_UserMail] (NOLOCK) WHERE toguid = @charguid  OPTION (KEEPFIXED PLAN)
	SELECT count(*) FROM [dbo].[TB_UserMail] (NOLOCK) WHERE toguid = @charguid AND readbit = 0  OPTION (KEEPFIXED PLAN)
	
IF @count > 0
BEGIN

	SELECT TOP 8
	A.mailguid,
	A.mailindex,
	B.[Name],
	A.title,
	A.note,
	cast((A.ReadBit + (A.ReturnBit * 4) + (A.AnnexBit * 8) + (A.PaymentBit * 16)) as tinyint),
	A.paymenttype,
	A.[money],
	A.limittime,

	C.ItemGuid,
	C.OwnerGuid,
	C.ItemNo,
	C.[Count],
	ISNULL(F.Enchant_01, 0) AS Enchant_01,
	ISNULL(F.Enchant_02, 0) AS Enchant_02,
	ISNULL(F.Enchant_03, 0) AS Enchant_03,
	ISNULL(F.Enchant_04, 0) AS Enchant_04,
	C.State,
	C.CreateDate,
	A.FromName,

-- 펫
	D.[Class] 
,	D.[Lv]
,	D.[Name] 
,	D.[Exp] 
,	D.[MP]
,	D.[Health]
,	D.[Mental]
,	D.[Color]
,	D.[Skill01]
,	D.[Skill02]
,	D.[Skill03],

-- 경험치 카드
	E.CurExp,
	E.MaxExp,
	E.ExpPer
	
	FROM [dbo].[TB_UserMail] (NOLOCK) AS A
	LEFT JOIN [dbo].[TB_CharacterBasic] (NOLOCK) AS B ON A.FromGuid = B.CharacterID
	LEFT JOIN [dbo].[TB_UserItem] (NOLOCK) C ON A.ItemGuid = C.ItemGuid
	LEFT JOIN [dbo].[TB_Pet] (NOLOCK) D ON C.ItemGuid = D.PetID
	LEFT JOIN [dbo].[TB_ExpCard] (NOLOCK) E ON C.ItemGuid = E.ItemGuid
	LEFT JOIN [dbo].[TB_UserItem_Enchant] (NOLOCK) F ON C.ItemGuid = F.ItemGuid
	WHERE toguid = @charguid AND (mailindex > @startindex)
	ORDER BY mailindex DESC  OPTION (KEEPFIXED PLAN)
	
END
ELSE
BEGIN
	SELECT TOP 8
	A.mailguid,
	A.mailindex,
	B.[Name],
	A.title,
	A.note,
	cast((A.ReadBit + (A.ReturnBit * 4) + (A.AnnexBit * 8) + (A.PaymentBit * 16)) as tinyint),
	A.paymenttype,
	A.[money],
	A.limittime,

	C.ItemGuid,
	C.OwnerGuid,
	C.ItemNo,
	C.[Count],
	ISNULL(F.Enchant_01, 0) AS Enchant_01,
	ISNULL(F.Enchant_02, 0) AS Enchant_02,
	ISNULL(F.Enchant_03, 0) AS Enchant_03,
	ISNULL(F.Enchant_04, 0) AS Enchant_04,
	C.State,
	C.CreateDate,
	A.FromName,

-- 펫
	D.[Class] 
,	D.[Lv]
,	D.[Name] 
,	D.[Exp] 
,	D.[MP]
,	D.[Health]
,	D.[Mental]
,	D.[Color]
,	D.[Skill01]
,	D.[Skill02]
,	D.[Skill03],

-- 경험치 카드
	E.CurExp,
	E.MaxExp,
	E.ExpPer
	
	FROM [dbo].[TB_UserMail] (NOLOCK) AS A
	LEFT JOIN [dbo].[TB_CharacterBasic] (NOLOCK) AS B ON A.FromGuid = B.CharacterID
	LEFT JOIN [dbo].[TB_UserItem] (NOLOCK) C ON A.ItemGuid = C.ItemGuid
	LEFT JOIN [dbo].[TB_Pet] (NOLOCK) D ON C.ItemGuid = D.PetID
	LEFT JOIN [dbo].[TB_ExpCard] (NOLOCK) E ON C.ItemGuid = E.ItemGuid
	LEFT JOIN [dbo].[TB_UserItem_Enchant] (NOLOCK) F ON C.ItemGuid = F.ItemGuid
	where toguid = @charguid and (mailindex < @startindex)
	ORDER BY mailindex DESC	 OPTION (KEEPFIXED PLAN)
END





