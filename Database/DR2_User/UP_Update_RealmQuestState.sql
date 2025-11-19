USE DR2_User
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_Update_RealmQuestState]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE [dbo].[UP_Update_RealmQuestState]
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
CREATE PROCEDURE [dbo].[UP_Update_RealmQuestState]
	@RealmQuestID nvarchar(100)
	,@RealmQuestCount int
AS
BEGIN
	SET NOCOUNT ON;

    IF NOT EXISTS(SELECT 1 FROM [dbo].[TB_RealmQuestStatus] WHERE [f_RealmQuestID] = @RealmQuestID)
		INSERT INTO [dbo].[TB_RealmQuestStatus] VALUES(@RealmQuestID, @RealmQuestCount)
	ELSE
		UPDATE [dbo].[TB_RealmQuestStatus] SET [f_RealmQuestCount] = @RealmQuestCount WHERE [f_RealmQuestID] = @RealmQuestID
END
GO
