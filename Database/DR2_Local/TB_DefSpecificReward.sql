USE [DR2_Def]
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefSpecificReward]') AND type in (N'U'))
BEGIN
	DROP TABLE [dbo].[TB_DefSpecificReward]
END

USE [DR2_Local]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefSpecificReward]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefSpecificReward](
		[Type] [int] NOT NULL,
		[SubType][int] NOT NULL,
		[RewardItemNo] [int] NOT NULL,
		[RewardCount] [bigint] NOT NULL,
		[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
	 CONSTRAINT [PK_TB_DefSpecificReward] PRIMARY KEY CLUSTERED 
	(
		[Type] ASC,
		[SubType] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END
GO

IF NOT EXISTS(SELECT * FROM SYS.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefSpecificReward') and [name] = N'f_NationCodeStr')
BEGIN
	CREATE TABLE dbo.Tmp_TB_DefSpecificReward
		(
		f_NationCodeStr nvarchar(50) NOT NULL,
		Type int NOT NULL,
		SubType int NOT NULL,
		RewardItemNo int NOT NULL,
		RewardCount bigint NOT NULL,
		Memo nvarchar(100) NULL
		)  ON [PRIMARY]

	IF EXISTS(SELECT * FROM dbo.TB_DefSpecificReward)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefSpecificReward (f_NationCodeStr, Type, SubType, RewardItemNo, RewardCount, Memo)
			SELECT 0, Type, SubType, RewardItemNo, RewardCount, Memo FROM dbo.TB_DefSpecificReward WITH (HOLDLOCK TABLOCKX)')

	DROP TABLE dbo.TB_DefSpecificReward

	EXECUTE sp_rename N'dbo.Tmp_TB_DefSpecificReward', N'TB_DefSpecificReward', 'OBJECT' 

	ALTER TABLE dbo.TB_DefSpecificReward ADD CONSTRAINT
		PK_TB_DefSpecificReward PRIMARY KEY CLUSTERED 
		(
		[f_NationCodeStr],
		[Type],
		[SubType]
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END
GO