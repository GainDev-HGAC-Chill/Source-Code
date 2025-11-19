USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefJobSkill_SkillExpertness]') AND [type] IN (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefJobSkill_SkillExpertness](
		[f_SkillNo] [int] NOT NULL,
		[f_Skill_Expertness_Min] [int] NOT NULL,
		[f_Skill_Expertness_Max] [int] NOT NULL,
		[f_Memo] nvarchar(50) NULL,
		[f_Expertness_Gain_Min] [int] NOT NULL,
		[f_Expertness_Gain_Max] [int] NOT NULL,
		[f_Expertness_Gain_Probability] [int] NOT NULL,
		[f_Expertness_Gain_TotalProbability] [int] NOT NULL,
		[f_Use_Duration] [int] NOT NULL,
		[f_Use_Duration_Probability] [int] NOT NULL,
		[f_Use_Duration_TotalProbability] [int] NOT NULL,
		[f_Basic_Turn_Time] [int] NOT NULL,
		[f_Max_Exgaustion] [int] NOT NULL,
		[f_Use_Exgaustion] [int] NOT NULL,
		[f_Max_Machine] [int] NOT NULL
	 CONSTRAINT [PK_TB_DefJobSkill_SkillExpertness] PRIMARY KEY CLUSTERED 
	(
		[f_SkillNo] ASC,
		[f_Skill_Expertness_Min] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefJobSkill_SkillExpertness]') and [name] = N'f_Need_CharLevel')
BEGIN
	ALTER TABLE [dbo].[TB_DefJobSkill_SkillExpertness] ADD [f_Need_CharLevel] [int] NOT NULL CONSTRAINT [DF_TB_DefJS_Expertness_f_Need_CharLevel] DEFAULT (0)
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefJobSkill_SkillExpertness') and [name] = N'f_Skill_Probaility')
BEGIN
	ALTER TABLE dbo.TB_DefJobSkill_SkillExpertness ADD f_Skill_Probaility int NOT NULL CONSTRAINT DF_TB_DefJobSkill_SkillExpertness_f_Skill_Probaility DEFAULT (0)
END
