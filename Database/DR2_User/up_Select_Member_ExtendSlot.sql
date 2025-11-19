USE [DR2_User]
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_select_member_ExtendSlot]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_select_member_ExtendSlot]

USE [DR2_User]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

-- =============================================
-- Author:		조현건
-- Create date: 2011-04-25
-- Description:	캐릭터 확장 슬롯 갯수 반환
-- =============================================
CREATE PROCEDURE [dbo].[up_select_member_ExtendSlot]
	@MemberGuid UNIQUEIDENTIFIER
AS
BEGIN	
	SELECT [MemberKey],
			[ExtendCharacterNum]
	FROM [dbo].[TB_Member_ShareData]
	WHERE [MemberKey] = @MemberGuid
END