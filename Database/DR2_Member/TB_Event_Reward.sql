USE DR2_Member
GO

/*
ALTER TABLE [dbo].[TB_Event_Reward] ADD
[f_Cash] [int] NULL
GO

ALTER TABLE [dbo].[TB_Event_Reward] ADD
[f_Title] [nvarchar](50) NULL
GO

ALTER TABLE [dbo].[TB_Event_Reward] ADD
[f_RewardItemNo5] [int] NULL,
[f_RewardItemCount5] [smallint] NULL,
[f_RewardTimeType5] [tinyint] NULL,
[f_RewardUseTime5] [smallint] NULL,
[f_RewardItemNo6] [int] NULL,
[f_RewardItemCount6] [smallint] NULL,
[f_RewardTimeType6] [tinyint] NULL,
[f_RewardUseTime6] [smallint] NULL,
[f_RewardItemNo7] [int] NULL,
[f_RewardItemCount7] [smallint] NULL,
[f_RewardTimeType7] [tinyint] NULL,
[f_RewardUseTime7] [smallint] NULL,
[f_RewardItemNo8] [int] NULL,
[f_RewardItemCount8] [smallint] NULL,
[f_RewardTimeType8] [tinyint] NULL,
[f_RewardUseTime8] [smallint] NULL
GO

IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_Event_Reward]') AND name = N'PK_TB_Event_Reward')
ALTER TABLE [dbo].[TB_Event_Reward] DROP CONSTRAINT [PK_TB_Event_Reward]
GO

ALTER TABLE [dbo].[TB_Event_Reward] ALTER COLUMN [f_IDX] [int] NOT NULL
GO

ALTER TABLE [dbo].[TB_Event_Reward] ADD  CONSTRAINT [PK_TB_Event_Reward] PRIMARY KEY CLUSTERED 
(
	[f_IDX] ASC
)WITH (SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF) ON [PRIMARY]
GO
*/

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.TB_Event_Reward') AND [Type] in (N'U'))
BEGIN
	/* To prevent any potential data loss issues, you should review this script in detail before running it outside the context of the database designer.*/
	BEGIN TRANSACTION
	SET QUOTED_IDENTIFIER ON
	SET ARITHABORT ON
	SET NUMERIC_ROUNDABORT OFF
	SET CONCAT_NULL_YIELDS_NULL ON
	SET ANSI_NULLS ON
	SET ANSI_PADDING ON
	SET ANSI_WARNINGS ON
	COMMIT
	BEGIN TRANSACTION
	
	CREATE TABLE dbo.Tmp_TB_Event_Reward
		(
		f_IDX int NOT NULL IDENTITY (1, 1),
		f_RewardKey int NULL,
		f_RewardItemNo1 int NULL,
		f_RewardItemCount1 smallint NULL,
		f_RewardItemNo2 int NULL,
		f_RewardItemCount2 smallint NULL,
		f_RewardItemNo3 int NULL,
		f_RewardItemCount3 smallint NULL,
		f_RewardItemNo4 int NULL,
		f_RewardItemCount4 smallint NULL,
		f_Money int NULL,
		f_RewardTimeType1 tinyint NULL,
		f_RewardUseTime1 smallint NULL,
		f_RewardTimeType2 tinyint NULL,
		f_RewardUseTime2 smallint NULL,
		f_RewardTimeType3 tinyint NULL,
		f_RewardUseTime3 smallint NULL,
		f_RewardTimeType4 tinyint NULL,
		f_RewardUseTime4 smallint NULL,
		f_Cash int NULL,
		f_Title nvarchar(50) NULL,
		f_RewardItemNo5 int NULL,
		f_RewardItemCount5 smallint NULL,
		f_RewardTimeType5 tinyint NULL,
		f_RewardUseTime5 smallint NULL,
		f_RewardItemNo6 int NULL,
		f_RewardItemCount6 smallint NULL,
		f_RewardTimeType6 tinyint NULL,
		f_RewardUseTime6 smallint NULL,
		f_RewardItemNo7 int NULL,
		f_RewardItemCount7 smallint NULL,
		f_RewardTimeType7 tinyint NULL,
		f_RewardUseTime7 smallint NULL,
		f_RewardItemNo8 int NULL,
		f_RewardItemCount8 smallint NULL,
		f_RewardTimeType8 tinyint NULL,
		f_RewardUseTime8 smallint NULL
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'쿠폰 보상 아이템, 게임 머니, 캐시 정보 정의 테이블'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_Event_Reward', NULL, NULL
	
	SET IDENTITY_INSERT dbo.Tmp_TB_Event_Reward ON
	
	IF EXISTS(SELECT * FROM dbo.TB_Event_Reward)
		 EXEC('INSERT INTO dbo.Tmp_TB_Event_Reward (f_IDX, f_RewardKey, f_RewardItemNo1, f_RewardItemCount1, f_RewardItemNo2, f_RewardItemCount2, f_RewardItemNo3, f_RewardItemCount3, f_RewardItemNo4, f_RewardItemCount4, f_Money, f_RewardTimeType1, f_RewardUseTime1, f_RewardTimeType2, f_RewardUseTime2, f_RewardTimeType3, f_RewardUseTime3, f_RewardTimeType4, f_RewardUseTime4, f_Cash, f_Title, f_RewardItemNo5, f_RewardItemCount5, f_RewardTimeType5, f_RewardUseTime5, f_RewardItemNo6, f_RewardItemCount6, f_RewardTimeType6, f_RewardUseTime6, f_RewardItemNo7, f_RewardItemCount7, f_RewardTimeType7, f_RewardUseTime7, f_RewardItemNo8, f_RewardItemCount8, f_RewardTimeType8, f_RewardUseTime8)
			SELECT f_IDX, f_RewardKey, f_RewardItemNo1, f_RewardItemCount1, f_RewardItemNo2, f_RewardItemCount2, f_RewardItemNo3, f_RewardItemCount3, f_RewardItemNo4, f_RewardItemCount4, f_Money, f_RewardTimeType1, f_RewardUseTime1, f_RewardTimeType2, f_RewardUseTime2, f_RewardTimeType3, f_RewardUseTime3, f_RewardTimeType4, f_RewardUseTime4, f_Cash, f_Title, f_RewardItemNo5, f_RewardItemCount5, f_RewardTimeType5, f_RewardUseTime5, f_RewardItemNo6, f_RewardItemCount6, f_RewardTimeType6, f_RewardUseTime6, f_RewardItemNo7, f_RewardItemCount7, f_RewardTimeType7, f_RewardUseTime7, f_RewardItemNo8, f_RewardItemCount8, f_RewardTimeType8, f_RewardUseTime8 FROM dbo.TB_Event_Reward WITH (HOLDLOCK TABLOCKX)')
	
	SET IDENTITY_INSERT dbo.Tmp_TB_Event_Reward OFF
	
	DROP TABLE dbo.TB_Event_Reward
	
	EXECUTE sp_rename N'dbo.Tmp_TB_Event_Reward', N'TB_Event_Reward', 'OBJECT' 
	
	ALTER TABLE dbo.TB_Event_Reward ADD CONSTRAINT
		PK_TB_Event_Reward PRIMARY KEY CLUSTERED 
		(
		f_IDX
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

	COMMIT
END



 

/****** Object:  Index [IX_TB_Event_Reward_RewardKey]    Script Date: 12/04/2012 12:01:24 ******/
IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_Event_Reward]') AND name = N'IX_TB_Event_Reward_RewardKey')
DROP INDEX [IX_TB_Event_Reward_RewardKey] ON [dbo].[TB_Event_Reward] WITH ( ONLINE = OFF )
GO

 
/****** Object:  Index [IX_TB_Event_Reward_RewardKey]    Script Date: 12/04/2012 12:01:24 ******/
CREATE NONCLUSTERED INDEX [IX_TB_Event_Reward_RewardKey] ON [dbo].[TB_Event_Reward] 
(
	[f_RewardKey] ASC
)WITH (PAD_INDEX  = ON, STATISTICS_NORECOMPUTE  = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
GO


