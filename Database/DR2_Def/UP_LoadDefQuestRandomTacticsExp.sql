USE DR2_Def
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_LoadDefQuestRandomTacticsExp]') AND type in (N'P'))
BEGIN
	DROP PROCEDURE [dbo].[UP_LoadDefQuestRandomTacticsExp]
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: 2009-10-20
-- Description:	
-- =============================================
CREATE PROCEDURE [dbo].[UP_LoadDefQuestRandomTacticsExp]
AS
BEGIN
	SET NOCOUNT ON;

    -- Insert statements for procedure here
	SELECT [f_Level]
		,[f_Exp1]
		,[f_Exp2]
		,[f_Exp3]
		,[f_Exp4]
		,[f_Exp5]
		,[f_Exp6]
		,[f_Exp7]
		,[f_Exp8]
		,[f_Exp9]
		,[f_Exp10]
		,[f_GuildExp1]
		,[f_GuildExp2]
		,[f_GuildExp3]
		,[f_GuildExp4]
		,[f_GuildExp5]
		,[f_GuildExp6]
		,[f_GuildExp7]
		,[f_GuildExp8]
		,[f_GuildExp9]
		,[f_GuildExp10]
	FROM [dbo].[TB_DefQuest_RandomTacticsExp]
END
GO
