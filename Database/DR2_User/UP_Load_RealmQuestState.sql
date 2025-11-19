USE DR2_User
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_Load_RealmQuestState]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE [dbo].[UP_Load_RealmQuestState]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: 2009-11-24
-- Description:	
-- =============================================
CREATE PROCEDURE [dbo].[UP_Load_RealmQuestState]
	@RealmQuestID nvarchar(100)
AS
BEGIN
	SET NOCOUNT ON;

    -- Insert statements for procedure here
	SELECT 
		[f_RealmQuestID]
		,[f_RealmQuestCount]
	FROM [dbo].[TB_RealmQuestStatus]
	WHERE [f_RealmQuestID] = @RealmQuestID
END
GO
