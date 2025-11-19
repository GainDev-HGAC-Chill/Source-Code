USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Post_GetMailItemInfo]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Post_GetMailItemInfo]

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Post_GetMailItemInfo]
(
	@MailGuid uniqueidentifier
)
AS
BEGIN

SET NOCOUNT ON;
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED

select
cast(A.[paymentbit] as tinyint),
A.[PaymentType],
A.[money],
A.[ItemGuid],
B.[OwnerGuid],
B.[InvType],
B.[InvPos],
B.[ItemNo],
B.[Count],
ISNULL(E.[Enchant_01], 0) AS Enchant_01,
ISNULL(E.[Enchant_02], 0) AS Enchant_02,
ISNULL(E.[Enchant_03], 0) AS Enchant_03,
ISNULL(E.[Enchant_04], 0) AS Enchant_04,
B.[State],
B.[CreateDate],
cast(A.[AnnexBit] as tinyint),
A.[ToGuid],

-- 펫
	C.[Class] 
,	C.[Lv]
,	C.[Name] 
,	C.[Exp] 
,	C.[MP]
,	C.[Health]
,	C.[Mental]
,	C.[Color]
,	C.[Skill01]
,	C.[Skill02]
,	C.[Skill03],

D.CurExp,
D.MaxExp,
D.ExpPer 

-- 5. 기간제 몬스터 카드 정보
,F.[LimitTime]

from dbo.TB_UserMail (nolock) A LEFT JOIN dbo.TB_UserItem (nolock) B ON A.ItemGuid = B.ItemGuid AND B.invtype = 9
LEFT JOIN [dbo].[TB_Pet] (nolock) C ON A.ItemGuid = C.PetID
LEFT JOIN dbo.tb_expcard (nolock) D ON A.ItemGuid = D.ItemGuid
LEFT JOIN [dbo].[TB_UserItem_Enchant] E ON A.ItemGuid = E.ItemGuid
LEFT JOIN [dbo].[TB_UserItem_MonsterCard] AS F ON A.ItemGuid = F.ItemGuid
WHERE A.MailGuid = @MailGuid

END