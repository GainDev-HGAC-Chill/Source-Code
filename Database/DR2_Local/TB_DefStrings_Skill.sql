USE [DR2_Local]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefStrings_Skill]') AND [name] = N'NationCodeStr')
BEGIN
	CREATE TABLE [dbo].[Tmp_TB_DefStrings_Skill](
	[NationCodeStr] [nvarchar](50) NOT NULL,
	[StringNo] [int] NOT NULL,
	[Text] [nvarchar](500) NOT NULL,
	[TextEng] [nvarchar](500) NULL,
	[Memo] [nvarchar](100) NULL,
	[MemoLocal] [nvarchar](100) NULL,
	 CONSTRAINT [PK_TB_DefStrings_Skill_StringNo2] PRIMARY KEY CLUSTERED 
	(
		[StringNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
	
	IF EXISTS (SELECT * FROM dbo.TB_DefStrings_Skill)
	EXEC('INSERT INTO dbo.Tmp_TB_DefStrings_Skill (NationCodeStr, StringNo, Text, TextEng, Memo, MemoLocal)
		  SELECT 0, StringNo, Text, TextEng, Memo, MemoLocal
		  FROM dbo.TB_DefStrings_Skill WITH (HOLDLOCK TABLOCKX)')
		  
	DROP TABLE TB_DefStrings_Skill
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefStrings_Skill', 'TB_DefStrings_Skill', 'OBJECT'
	
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'게임에서 사용하는 TEXT 정의(스킬)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefStrings_Skill'
END
GO

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefStrings_Skill]') AND [name] = N'NationCodeStr')
BEGIN
	ALTER TABLE dbo.TB_DefStrings_Skill
		DROP CONSTRAINT PK_TB_DefStrings_Skill_StringNo2

	ALTER TABLE dbo.TB_DefStrings_Skill ADD CONSTRAINT
		PK_TB_DefStrings_Skill_StringNo2 PRIMARY KEY CLUSTERED 
		(
		NationCodeStr,
		StringNo
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
	END
GO

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefStrings_Skill]') AND [name] = N'NationCodeStr')
BEGIN
	ALTER TABLE dbo.TB_DefStrings_Skill
		DROP CONSTRAINT PK_TB_DefStrings_Skill_StringNo2
		
	ALTER TABLE dbo.TB_DefStrings_Skill
		DROP COLUMN [NationCodeStr]
	
	ALTER TABLE dbo.TB_DefStrings_Skill ADD CONSTRAINT
		PK_TB_DefStrings_Skill_StringNo2 PRIMARY KEY CLUSTERED 
		(
		StringNo
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END