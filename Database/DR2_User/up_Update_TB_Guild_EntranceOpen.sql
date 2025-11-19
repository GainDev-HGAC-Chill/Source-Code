USE DR2_User
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_TB_Guild_EntranceOpen]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Update_TB_Guild_EntranceOpen]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		김동환
-- Create date: 2010.04.21
-- Description:	길드가입 설정 세팅 DB에 저장
-- =============================================
CREATE PROCEDURE [dbo].[up_Update_TB_Guild_EntranceOpen]	
	@GuildGuid uniqueidentifier,
	@IsGuildEntrance tinyint,
	@GuildEntranceLevel smallint,
	@GuildEntranceClass bigint,
	@GuildEntranceFee bigint,
	@GuildPR nvarchar(20)	
AS
BEGIN	
	SET NOCOUNT ON;
	
	-- 최근 3개월간의 길드전 승수를 넣어준다.(up_Load_Entrance_OpenGuild 에서 이 값을 DESC 순으로 SELECT 해서 순위로 사용)
	DECLARE @EmporiaWinCount INT
	SELECT @EmporiaWinCount = (SELECT COUNT(*) FROM dbo.TB_Emporia_Tournament WITH(NOLOCK)
	WHERE [WinGuildID] = @GuildGuid AND [BattleDate] > DATEADD(m,-3,GETDATE()))
	
	IF NOT EXISTS (SELECT 1 FROM dbo.TB_Guild_EntranceOpen WHERE GuildGuid = @GuildGuid)
	BEGIN
		INSERT INTO dbo.TB_Guild_EntranceOpen
		(
			[GuildGuid], [EmporiaWinCount], [IsGuildEntrance], [GuildEntranceLevel], [GuildEntranceClass], [GuildEntranceFee], [GuildPR]
		)
		VALUES
		(
			@GuildGuid, @EmporiaWinCount, @IsGuildEntrance, @GuildEntranceLevel, @GuildEntranceClass, @GuildEntranceFee, @GuildPR
		)
	END
	ELSE
	BEGIN
		UPDATE dbo.TB_Guild_EntranceOpen
		SET
			[EmporiaWinCount] = @EmporiaWinCount,
			[IsGuildEntrance] = @IsGuildEntrance,
			[GuildEntranceLevel] = @GuildEntranceLevel,
			[GuildEntranceClass] = @GuildEntranceClass,
			[GuildEntranceFee] = @GuildEntranceFee,
			[GuildPR] = @GuildPR
		WHERE [GuildGuid] = @GuildGuid
	END	
END
GO