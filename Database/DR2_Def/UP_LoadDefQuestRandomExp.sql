USE DR2_Def
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_LoadDefQuestRandomExp]') AND type in (N'P'))
BEGIN
	DROP PROCEDURE [dbo].[UP_LoadDefQuestRandomExp]
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
CREATE PROCEDURE [dbo].[UP_LoadDefQuestRandomExp]
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
	FROM [dbo].[TB_DefQuest_RandomExp]
END
GO
