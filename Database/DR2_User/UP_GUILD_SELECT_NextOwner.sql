USE DR2_User
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_GUILD_SELECT_NextOwner]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE [dbo].[UP_GUILD_SELECT_NextOwner]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		육정범
-- Create date: 2009-10-27
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[UP_GUILD_SELECT_NextOwner]
	@CmdType int
	,@GuildGuid UNIQUEIDENTIFIER
	,@GuildLevel int
AS
BEGIN
	SET NOCOUNT ON;

    DECLARE @Now DATETIME
	DECLARE @OldGuildOwner UNIQUEIDENTIFIER
	DECLARE @OldGuildOwnerName nvarchar(20)
	DECLARE @NewGuildOwner UNIQUEIDENTIFIER
	DECLARE @NewGuildOwnerName nvarchar(20)
	SET @Now = GetDate();

	-- 원래 길마
	SELECT
		@OldGuildOwner = A.[CharacterGuid]
		,@OldGuildOwnerName = B.[Name]
	FROM
		dbo.tb_guild_member AS A
		INNER JOIN dbo.tb_characterbasic AS B ON A.[CharacterGuid] = B.CharacterID
	WHERE
		[GuildGuid] = @GuildGuid
		AND MemberLevel = 0

	-- 대상자를 찾는다
	SELECT
		TOP 1
		@NewGuildOwner = TB_GuildMem.[CharacterGuid]
		, @NewGuildOwnerName = TB_User.[Name]
	FROM
		dbo.tb_guild_member AS TB_GuildMem
		INNER JOIN dbo.tb_charactersub AS TB_UserSub ON TB_GuildMem.CharacterGuid = TB_UserSub.CharacterID
		INNER JOIN dbo.tb_CharacterBasic AS TB_User ON TB_GuildMem.CharacterGuid = TB_User.CharacterID
	WHERE
		GuildGuid = @GuildGuid -- in guild
		AND [MemberLevel] > 0 -- not in guild owner
		AND DATEDIFF(day, [f_LastLoginDate], @Now) <= (7 * 4) -- in 4 week of day
	ORDER BY
		TB_UserSub.[Lv] DESC
		,TB_UserSub.[Exp] DESC

	IF @NewGuildOwner IS NULL
	BEGIN
		SELECT
			TOP 1
			@NewGuildOwner = TB_GuildMem.[CharacterGuid]
			, @NewGuildOwnerName = TB_User.[Name]
		FROM
			dbo.tb_guild_member AS TB_GuildMem
			INNER JOIN dbo.tb_charactersub AS TB_UserSub ON TB_GuildMem.CharacterGuid = TB_UserSub.CharacterID
			INNER JOIN dbo.tb_CharacterBasic AS TB_User ON TB_GuildMem.CharacterGuid = TB_User.CharacterID
		WHERE
			GuildGuid = @GuildGuid -- in guild
			AND [MemberLevel] > 0 -- not in guild owner
		ORDER BY
			TB_UserSub.[Lv] DESC
			,TB_UserSub.[Exp] DESC
	END

	SELECT
		@CmdType, @GuildLevel
		,ISNULL(@GuildGuid, N'00000000-0000-0000-0000-000000000000')
		,ISNULL(@OldGuildOwner, '00000000-0000-0000-0000-000000000000')
		,ISNULL(@NewGuildOwner, N'00000000-0000-0000-0000-000000000000')
		,ISNULL(@OldGuildOwnerName, N'')
		,ISNULL(@NewGuildOwnerName, N'')
END
GO
