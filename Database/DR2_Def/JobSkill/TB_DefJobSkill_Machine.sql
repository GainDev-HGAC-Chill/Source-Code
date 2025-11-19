USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefJobSkill_Machine]') AND [type] IN (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefJobSkill_Machine](
		[f_ItemNo] [int] NOT NULL,
		[f_Memo] nvarchar(50) NULL,
		[f_GatherType] [int] NOT NULL,
		[f_01Need_JobSkill_No] [int] NOT NULL,
		[f_01Need_JotSkillExpertness] [int] NOT NULL,
		[f_02Need_JobSkill_No] [int] NOT NULL,
		[f_02Need_JotSkillExpertness] [int] NOT NULL,
		[f_03Need_JobSkill_No] [int] NOT NULL,
		[f_03Need_JotSkillExpertness] [int] NOT NULL,
		[f_Option_TurnTime] [int] NOT NULL,
	 CONSTRAINT [PK_TB_DefJobSkill_Machine] PRIMARY KEY CLUSTERED 
	(
		[f_ItemNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefJobSkill_Machine') AND [name] = N'f_01Need_JotSkillExpertness')
BEGIN
	EXECUTE sp_rename N'dbo.TB_DefJobSkill_Machine.f_01Need_JotSkillExpertness', N'Tmp_f_01Need_JobSkillExpertness_1', 'COLUMN' 
	EXECUTE sp_rename N'dbo.TB_DefJobSkill_Machine.f_02Need_JotSkillExpertness', N'Tmp_f_02Need_JobSkillExpertness_2', 'COLUMN' 
	EXECUTE sp_rename N'dbo.TB_DefJobSkill_Machine.f_03Need_JotSkillExpertness', N'Tmp_f_03Need_JobSkillExpertness_3', 'COLUMN' 
	EXECUTE sp_rename N'dbo.TB_DefJobSkill_Machine.Tmp_f_01Need_JobSkillExpertness_1', N'f_01Need_JobSkillExpertness', 'COLUMN' 
	EXECUTE sp_rename N'dbo.TB_DefJobSkill_Machine.Tmp_f_02Need_JobSkillExpertness_2', N'f_02Need_JobSkillExpertness', 'COLUMN' 
	EXECUTE sp_rename N'dbo.TB_DefJobSkill_Machine.Tmp_f_03Need_JobSkillExpertness_3', N'f_03Need_JobSkillExpertness', 'COLUMN' 
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefJobSkill_Machine') AND [name] = N'f_SlotCount')
BEGIN
	ALTER TABLE dbo.TB_DefJobSkill_Machine ADD f_SlotCount int NOT NULL
END


/****** Object:  Table [dbo].[TB_DefJobSkill_Machine]    Script Date: 11/29/2012 15:41:06 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefJobSkill_Machine]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DefJobSkill_Machine]
GO