USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefJobSkill_SaveIdx]') AND [type] IN (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefJobSkill_SaveIdx](
		[f_SaveIdx] [int] NOT NULL,
		[f_Memo] nvarchar(50) NULL,
		[f_Recipe_ItemNo] [int] NOT NULL,
		[f_Resource_GroupNo] [int] NOT NULL,
		[f_01Need_SkillNo] [int] NOT NULL,
		[f_01Need_Expertness] [int] NOT NULL,
		[f_02Need_SkillNo] [int] NOT NULL,
		[f_02Need_Expertness] [int] NOT NULL,
		[f_03Need_SkillNo] [int] NOT NULL,
		[f_03Need_Expertness] [int] NOT NULL,
		[f_Recipe_Price] [int] NOT NULL,
	 CONSTRAINT [PK_TB_DefJobSkill_SaveIdx] PRIMARY KEY CLUSTERED 
	(
		[f_SaveIdx] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefJobSkill_SaveIdx]') AND [name] = N'f_Book_ItemNo')
BEGIN
	ALTER TABLE dbo.[TB_DefJobSkill_SaveIdx] ADD f_Book_ItemNo int NOT NULL CONSTRAINT DF_TB_DefJobSkill_SaveIdx_f_Book_ItemNo DEFAULT 0
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefJobSkill_SaveIdx]') AND [name] = N'f_AlreadyLearn')
BEGIN
	ALTER TABLE dbo.[TB_DefJobSkill_SaveIdx] ADD f_AlreadyLearn int NOT NULL CONSTRAINT DF_TB_DefJobSkill_SaveIdx_f_AlreadyLearn DEFAULT 0
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefJobSkill_SaveIdx]') AND [name] = N'f_ShowUser')
BEGIN
	ALTER TABLE dbo.[TB_DefJobSkill_SaveIdx] ADD f_ShowUser int NOT NULL CONSTRAINT DF_TB_DefJobSkill_SaveIdx_f_ShowUser DEFAULT 1
END
GO