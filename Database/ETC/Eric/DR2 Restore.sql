
/*
drop database dr2_Def
drop database dr2_Local
drop database dr2_Member
drop database dr2_User
--drop database dr2_GM
--drop database dr2_Log
--drop database dr2_SiteConfig
*/

DECLARE @Bak_Path nvarchar(500)
DECLARE @DB_Output nvarchar(500)
DECLARE @Bak_File nvarchar(500)
DECLARE @Today nvarchar(100)
DECLARE @MyTag nvarchar(10)

SET @MyTag = N'Eric'
SET @Bak_Path = N'D:\temp\'
SET @DB_Output = N'E:\Project\DB\'
SET @Today = convert(nvarchar(20), getDate(), 112)

DECLARE @MDF_FILE nvarchar(500)
DECLARE @LDF_FILE nvarchar(500)

--/*
PRINT '[DR2_Def] Begin'
SET @MDF_FILE = @DB_Output + N'DR2_Def.mdf'
SET @LDF_FILE = @DB_Output + N'DR2_Def.ldf'
SET @Bak_File = @Bak_Path + @MyTag + N'_DR2_Def_' + @Today + N'.bak'
restore database DR2_Def from disk = @Bak_File with CHECKSUM, file = 1, move 'DR2_Def_dat' to @MDF_FILE ,move 'DR2_Def_log' to @LDF_FILE, stats =10
PRINT '  ..[DR2_Def] End'
--*/

--/*
PRINT '[DR2_Local] Begin'
SET @MDF_FILE = @DB_Output + N'DR2_Local.mdf'
SET @LDF_FILE = @DB_Output + N'DR2_Local.ldf'
SET @Bak_File = @Bak_Path + @MyTag + N'_DR2_Local_' + @Today + N'.bak'
restore database DR2_Local from disk = @Bak_File with CHECKSUM, file = 1, move 'DR2_Local' to @MDF_FILE ,move 'DR2_Local_log' to @LDF_FILE, stats =10
PRINT '  ..[DR2_Local] End'
--*/

--/*
PRINT '[DR2_Member] Begin'
SET @MDF_FILE = @DB_Output + N'DR2_Member.mdf'
SET @LDF_FILE = @DB_Output + N'DR2_Member.ldf'
SET @Bak_File = @Bak_Path + @MyTag + N'_DR2_Member_' + @Today + N'.bak'
restore database DR2_Member from disk = @Bak_File with CHECKSUM, file = 1, move 'DR2_Member_dat' to @MDF_FILE ,move 'DR2_Member_log' to @LDF_FILE, stats =10
PRINT '  ..[DR2_Member] End'
--*/

--/*
PRINT '[DR2_User] Begin'
SET @MDF_FILE = @DB_Output + N'DR2_User.mdf'
SET @LDF_FILE = @DB_Output + N'DR2_User.ldf'
SET @Bak_File = @Bak_Path + @MyTag + N'_DR2_User_' + @Today + N'.bak'
restore database DR2_User from disk = @Bak_File with CHECKSUM, file = 1, move 'DR2_User_dat' to @MDF_FILE ,move 'DR2_User_log' to @LDF_FILE, stats =10
PRINT '  ..[DR2_User] End'
--*/

/*
PRINT '[DR2_GM] Begin'
SET @MDF_FILE = @DB_Output + N'DR2_GM.mdf'
SET @LDF_FILE = @DB_Output + N'DR2_GM.ldf'
SET @Bak_File = @Bak_Path + @MyTag + N'_DR2_GM_' + @Today + N'.bak'
restore database DR2_GM from disk = @Bak_File with CHECKSUM, file = 1, move 'DR2_GM_dat' to @MDF_FILE ,move 'DR2_GM_log' to @LDF_FILE, stats =10
PRINT '  ..[DR2_GM] End'
*/

/*
PRINT '[DR2_Log] Begin'
SET @MDF_FILE = @DB_Output + N'DR2_Log.mdf'
SET @LDF_FILE = @DB_Output + N'DR2_Log.ldf'
SET @Bak_File = @Bak_Path + @MyTag + N'_DR2_Log_' + @Today + N'.bak'
restore database DR2_Log from disk = @Bak_File with CHECKSUM, file = 1, move 'DR2_Log_dat' to @MDF_FILE ,move 'DR2_Log_log' to @LDF_FILE, stats =10
PRINT '  ..[DR2_Log] End'
*/

/*
PRINT '[DR2_SiteConfig] Begin'
SET @MDF_FILE = @DB_Output + N'DR2_SiteConfig.mdf'
SET @LDF_FILE = @DB_Output + N'DR2_SiteConfig.ldf'
SET @Bak_File = @Bak_Path + + @MyTag + N'_DR2_SiteConfig_' + @Today + N'.bak'
restore database DR2_SiteConfig from disk = @Bak_File with CHECKSUM, file = 1, move 'DR2_SiteConfig_dat' to @MDF_FILE ,move 'DR2_SiteConfig_log' to @LDF_FILE, stats =10
PRINT '  ..[DR2_SiteConfig] End'
*/

WAITFOR DELAY '00:00:02'
GO

USE DR2_Def
GO
EXEC sp_change_users_login 'update_one', 'gameserver', 'gameserver'
EXEC sp_change_users_login 'update_one', 'gamedev', 'gamedev'

USE DR2_Local
GO
EXEC sp_change_users_login 'update_one', 'gameserver', 'gameserver'
EXEC sp_change_users_login 'update_one', 'gamedev', 'gamedev'

USE DR2_Member
GO
EXEC sp_change_users_login 'update_one', 'gameserver', 'gameserver'
EXEC sp_change_users_login 'update_one', 'gamedev', 'gamedev'

USE DR2_User
GO
EXEC sp_change_users_login 'update_one', 'gameserver', 'gameserver'
EXEC sp_change_users_login 'update_one', 'gamedev', 'gamedev'

USE DR2_GM
GO
EXEC sp_change_users_login 'update_one', 'gameserver', 'gameserver'
EXEC sp_change_users_login 'update_one', 'gamedev', 'gamedev'

USE DR2_Log
GO
EXEC sp_change_users_login 'update_one', 'gameserver', 'gameserver'
EXEC sp_change_users_login 'update_one', 'gamedev', 'gamedev'
EXEC sp_change_users_login 'update_one', 'gamelog', 'gamelog'

USE DR2_SiteConfig
GO
EXEC sp_change_users_login 'update_one', 'gameserver', 'gameserver'
EXEC sp_change_users_login 'update_one', 'gamedev', 'gamedev'
GO

PRINT ' ....... RESTORE Completed .............'
GO
