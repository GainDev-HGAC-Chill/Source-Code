USE [DR2_User]
GO

/****** Object:  Table [dbo].[TB_UserJobSkill_WB_OfflineHistory]    Script Date: 10/25/2010 15:42:03 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserJobSkill_WB_OffilneHistory]') and type in (N'U'))
BEGIN
	exec sp_rename N'TB_UserJobSkill_WB_OffilneHistory', N'TB_UserJobSkill_WB_OfflineHistory'
END

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserJobSkill_WB_OfflineHistory]') and type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_UserJobSkill_WB_OfflineHistory](
		[f_CharGuid] [uniqueidentifier] NOT NULL,
		[f_Type] [int] NOT NULL,
		[f_WorkBenchItemNo] [int] NOT NULL,
		[f_ItemNo] [int] NOT NULL
	) ON [PRIMARY]

	CREATE CLUSTERED INDEX IX_TB_UserJobSkill_WB_OfflineHistory ON dbo.TB_UserJobSkill_WB_OfflineHistory
	(
	f_CharGuid
	) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END
ELSE
IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.[TB_UserJobSkill_WB_OfflineHistory]') and name = N'[f_Type]')
BEGIN
	exec sp_rename N'TB_UserJobSkill_WB_OfflineHistory', N'Tmp_TB_UserJobSkill_WB_OfflineHistory'
	
	CREATE TABLE [dbo].[TB_UserJobSkill_WB_OfflineHistory](
		[f_CharGuid] [uniqueidentifier] NOT NULL,
		[f_Type] [int] NOT NULL,
		[f_WorkBenchItemNo] [int] NOT NULL,
		[f_ItemNo] [int] NOT NULL
	) ON [PRIMARY]

	CREATE CLUSTERED INDEX IX_TB_UserJobSkill_WB_OfflineHistory ON dbo.TB_UserJobSkill_WB_OfflineHistory
	(
	f_CharGuid
	) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
	
	INSERT INTO [dbo].[TB_UserJobSkill_WB_OfflineHistory]
		SELECT [f_CharGuid], 0, [f_WorkBenchItemNo], [f_ItemNo] FROM dbo.Tmp_TB_UserJobSkill_WB_OfflineHistory
		
	DROP TABLE [dbo].Tmp_TB_UserJobSkill_WB_OfflineHistory
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.[TB_UserJobSkill_WB_OfflineHistory]') and name = N'[f_AddExtertnessRate]')
BEGIN
	ALTER TABLE dbo.TB_UserJobSkill_WB_OfflineHistory ADD f_AddExpertnessRate int NOT NULL DEFAULT (0)
END
GO
