USE DR2_User
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Guild_Entrance_Request]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Guild_Entrance_Request]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	길드가입 신청
-- =============================================
CREATE PROCEDURE up_Guild_Entrance_Request
	@GuildGuid uniqueidentifier,
	@CharacterGuid uniqueidentifier,
	@Message nvarchar(100),
	@GuildEntranceFee BIGINT,
	@NowTime DATETIME
AS
BEGIN
	SET NOCOUNT ON;	
	
	DECLARE @Ret INT
	SET @Ret = 0
	
	IF EXISTS( SELECT 1 FROM dbo.TB_Guild_Basic_Info WHERE [GuildGuid] = @GuildGuid )
	BEGIN
		INSERT INTO dbo.TB_Guild_Applicant
		(
			GuildGuid, CharacterGuid, IsAcceptanceState, RequestTime, [Message], GuildEntranceFee
		)
		VALUES
		(
			@GuildGuid, @CharacterGuid, 0, @NowTime, @Message, @GuildEntranceFee
		)
		SELECT @Ret
	END
	ELSE -- 해체된 길드
	BEGIN
		SET @Ret = 1
		SELECT @Ret
	END
	SET NOCOUNT OFF;
END
GO
