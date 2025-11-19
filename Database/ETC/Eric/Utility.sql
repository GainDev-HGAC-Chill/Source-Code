-- SiteConfig IP 변경하기
SELECT * FROM [DR2_SiteConfig].[dbo].[TB_Eric_SiteServer]
UPDATE [DR2_SiteConfig].[dbo].[TB_Eric_SiteServer] SET MachineIP = N'211.231.162.178'
UPDATE [DR2_SiteConfig].[dbo].[TB_Eric_SiteServer] SET ServerBindIP = N'211.231.162.178' WHERE ServerBindIP is not NULL
UPDATE [DR2_SiteConfig].[dbo].[TB_Eric_SiteServer] SET UserBindIP = N'211.231.162.178' WHERE UserBindIP is not NULL
SELECT * FROM [DR2_SiteConfig].[dbo].[TB_Eric_Realm]
UPDATE [DR2_SiteConfig].[dbo].[TB_Eric_Realm] SET MachineIP = N'211.231.162.178'
UPDATE [DR2_SiteConfig].[dbo].[TB_Eric_Realm] SET ServerBindIP = N'211.231.162.178' WHERE ServerBindIP is not NULL
UPDATE [DR2_SiteConfig].[dbo].[TB_Eric_Realm] SET UserBindIP = N'211.231.162.178' WHERE UserBindIP is not NULL