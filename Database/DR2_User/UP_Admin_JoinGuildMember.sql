USE dr2_user
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_Admin_JoinGuildMember]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_Admin_JoinGuildMember]
END
GO

CREATE PROCEDURE dbo.[UP_Admin_JoinGuildMember]
	@GuildName nvarchar(100),
	@CharName nvarchar(100)
AS
DECLARE @CharGuid UNIQUEIDENTIFIER
DECLARE @GuildGuid UNIQUEIDENTIFIER
SELECT @CharGuid = [CharacterID] FROM dbo.tb_Characterbasic WHERE [name] = @CharName
IF @@ROWCOUNT <> 1
BEGIN
	SELECT 'WRONG character['+@CharName+'] name'
	return 
END

SELECT @GuildGuid = [GuildGuid] FROM dbo.tb_guild_basic_info WHERE [GuildName] = @GuildName
IF @@ROWCOUNT <> 1
BEGIN
	SELECT 'WRONG GuildName['+@GuildName+'] name'
	return 
END

DECLARE @AnotherGuildName NVARCHAR(100)
SELECT @AnotherGuildName = B.GuildName FROM dbo.tb_Guild_Member AS A LEFT JOIN dbo.tb_guild_basic_info AS B ON A.GuildGuid = B.GuildGuid WHERE [CharacterGuid] = @CharGuid 
IF @@ROWCOUNT <> 0
BEGIN
	SELECT 'WRONG Character['+@CharName+'] is has another guild ['+@AnotherGuildName+']'
	return 
END
INSERT INTO dbo.tb_guild_member([CharacterGuid], [GuildGuid], [MemberLevel]) VALUES (@CharGuid, @GuildGuid, 255)
SELECT 'Success process. character['+@CharName+'] join to guild['+@GuildName+']'
GO