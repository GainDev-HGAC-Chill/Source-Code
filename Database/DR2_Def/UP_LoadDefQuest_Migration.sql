USE DR2_Def
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_LoadDefQuest_Migration]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_LoadDefQuest_Migration]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: 2009-11-05
-- Description:	
-- =============================================
CREATE PROCEDURE dbo.[UP_LoadDefQuest_Migration]
AS
BEGIN
	SET NOCOUNT ON;

    -- Insert statements for procedure here
	SELECT [f_Revision]
		,[f_QuestID]
		,[f_MigrationRule]
		,[f_TargetValue]
	FROM [dbo].[TB_DefQuest_Migration]
	ORDER BY [f_Revision], [f_QuestID]
END
GO
