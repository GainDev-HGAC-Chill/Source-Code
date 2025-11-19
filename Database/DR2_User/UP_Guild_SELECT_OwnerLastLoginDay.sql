USE DR2_User
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_Guild_SELECT_OwnerLastLoginDay]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE [dbo].[UP_Guild_SELECT_OwnerLastLoginDay]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: 2009-10-26
-- Description:	
-- =============================================
CREATE PROCEDURE [dbo].[UP_Guild_SELECT_OwnerLastLoginDay]
AS
BEGIN
	SET NOCOUNT ON;

    -- Insert statements for procedure here
	DECLARE @Now DATETIME
	SET @Now = GetDate();
	SELECT
		A.[GuildGuid]
		,B.[CurrentLevel]
		,DATEDIFF(day, [f_LastLoginDate], @Now) AS [f_LastLoginDay]
	FROM [dbo].[TB_Guild_Member] AS A
	INNER JOIN [dbo].[TB_Guild_Basic_Info] AS B ON A.[GuildGuid] = B.[GuildGuid]
	WHERE
		A.[MemberLevel] = 0
		--AND A.[GuildGuid] NOT IN(SELECT OwnerGuildID FROM dbo.TB_Emporia)
END
GO
