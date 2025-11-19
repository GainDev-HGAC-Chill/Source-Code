USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefJobSkill_Skill]') AND [type] IN (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefJobSkill_Skill](
		[f_SkillNo] [int] NOT NULL,
		[f_Memo] nvarchar(50) NULL,
		[f_GatherType] [int] NOT NULL,
		[f_JobSkill_Type] [int] NOT NULL,
		[f_01NeedParent_JobSkill_No] [int] NOT NULL,
		[f_01NeedParent_JobSkill_Expertness] [int] NOT NULL,
		[f_02NeedParent_JobSkill_No] [int] NOT NULL,
		[f_02NeedParent_JobSkill_Expertness] [int] NOT NULL,
		[f_03NeedParent_JobSkill_No] [int] NOT NULL,
		[f_03NeedParent_JobSkill_Expertness] [int] NOT NULL,
	 CONSTRAINT [PK_TB_DefJobSkill_Skill] PRIMARY KEY CLUSTERED 
	(
		[f_SkillNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END