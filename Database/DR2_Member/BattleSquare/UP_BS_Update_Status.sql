USE DR2_Member
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_BS_Update_Status]') AND type in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_BS_Update_Status]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: 2009-09-15
-- Description:	
-- =============================================
CREATE PROCEDURE dbo.[UP_BS_Update_Status]
	@GameIdx int
	,@RealmNo int
	,@ChannelNo int
	,@Status int
AS
BEGIN
	
	SET NOCOUNT ON;

	IF EXISTS(SELECT COUNT(*) FROM [dbo].[TB_BattleSquare_Status] WHERE [f_GameIDX] = @GameIdx AND [f_RealmNo] = @RealmNo AND [f_ChannelNo] = @ChannelNo)
		BEGIN
			UPDATE [dbo].[TB_BattleSquare_Status]
			SET [f_Status] = @Status, [f_LastUpdateDate] = GetDate()
			WHERE [f_GameIDX] = @GameIdx AND [f_RealmNo] = @RealmNo AND [f_ChannelNo] = @ChannelNo;
		END
	ELSE
		BEGIN
			INSERT INTO [dbo].[TB_BattleSquare_Status] ([f_GameIDX],[f_RealmNo],[f_ChannelNo],[f_Status],[f_LastUpdateDate])
			VALUES (@GameIDX, @RealmNo, @ChannelNo, @Status, GetDate());
		END
END
GO
