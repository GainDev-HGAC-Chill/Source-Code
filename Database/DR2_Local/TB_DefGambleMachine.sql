USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_DefGambleMachine]    Script Date: 09/02/2009 13:34:14 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefGambleMachine]') )
BEGIN
	CREATE TABLE [dbo].[TB_DefGambleMachine](
		[Idx] [int] IDENTITY(1,1) NOT NULL,
		[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
		[Coin] [tinyint] NOT NULL,
		[ItemNo] [int] NULL,
		[Rate] [int] NULL,
		[Broadcast] [tinyint] NULL,
		[TimeType] [tinyint] NULL,
		[UseTime] [smallint] NULL
	 CONSTRAINT [PK_TB_DefGambleMachine] PRIMARY KEY CLUSTERED 
	(
		[Idx] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END


IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefGambleMachine') and [name] = N'Count')
BEGIN
	ALTER TABLE [dbo].[TB_DefGambleMachine] ADD
	[Count] [smallint] NULL CONSTRAINT [DF_TB_DefGambleMachine_Count] DEFAULT ((1))
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefGambleMachine') and [name] = N'GroupNo')
BEGIN
	ALTER TABLE [dbo].[TB_DefGambleMachine] ADD
	[GroupNo] [int] NULL
END


/********************************11/05/10 정정원********************************************
신종족 아이템 번호 컬럼 추가.
컬럼 변경: ItemNo → ItemNo1 (인간족)
컬럼 추가: ItemNo2 (신종족)
********************************************************************************************/
IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefGambleMachine') and [name] = N'ItemNo1' )
BEGIN
	CREATE TABLE [dbo].[Tmp_TB_DefGambleMachine]
	(
		[Idx] [int] IDENTITY(1,1) NOT NULL,
		[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
		[Coin] [tinyint] NOT NULL,
		[ItemNo1] [int] NULL,
		[ItemNo2] [int] NULL,
		[Rate] [int] NULL,
		[Broadcast] [tinyint] NULL,
		[TimeType] [tinyint] NULL,
		[UseTime] [smallint] NULL,
		[Count] [smallint] NULL,
		[GroupNo] [int] NULL
	)ON [PRIMARY]

	IF EXISTS(SELECT * FROM dbo.TB_DefGambleMachine)
		EXEC('INSERT INTO dbo.Tmp_TB_DefGambleMachine (Memo, Coin, ItemNo1, ItemNo2, Rate, Broadcast, TimeType, UseTime, Count, GroupNo)
			SELECT Memo, Coin, ItemNo, 0, Rate, Broadcast, TimeType, UseTime, Count, GroupNo FROM dbo.TB_DefGambleMachine WITH (HOLDLOCK TABLOCKX)')
	
	DROP TABLE dbo.TB_DefGambleMachine
	EXECUTE sp_rename N'dbo.Tmp_TB_DefGambleMachine', N'TB_DefGambleMachine', 'OBJECT' 

	ALTER TABLE dbo.TB_DefGambleMachine ADD CONSTRAINT DF_TB_DefGambleMachine_Count DEFAULT ((1)) FOR [Count]

	
	ALTER TABLE dbo.TB_DefGambleMachine ADD CONSTRAINT
		PK_TB_DefGambleMachine PRIMARY KEY CLUSTERED 
	(
		[Idx] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]


END