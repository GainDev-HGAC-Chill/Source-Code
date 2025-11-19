USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Post_Get_UserMailInfo]    Script Date: 12/21/2009 14:33:57 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Post_Get_UserMailInfo]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Post_Get_UserMailInfo]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_Post_Get_UserMailInfo]

@mailguid uniqueidentifier

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT
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
	
	from dbo.TB_UserMail AS A
	LEFT JOIN [dbo].[TB_CharacterBasic] AS B ON A.FromGuid = B.CharacterID
	LEFT JOIN [dbo].[TB_UserItem] (NOLOCK) C ON A.ItemGuid = C.ItemGuid
	LEFT JOIN [dbo].[TB_Pet] (NOLOCK) D ON C.ItemGuid = D.PetID
	LEFT JOIN [dbo].[TB_ExpCard] (NOLOCK) E ON C.ItemGuid = E.ItemGuid
	LEFT JOIN [dbo].[TB_UserItem_Enchant] (NOLOCK) F ON C.ItemGuid = F.ItemGuid
	where mailguid = @mailguid
	
END



