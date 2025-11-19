USE [DR2_DEF]
GO
/****** Object:  Table [dbo].[TB_DefGemStore]    Script Date: 04/14/2010 15:33:16 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefGemStore]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefGemStore](
		[idx] [int] IDENTITY(1,1) NOT NULL,
		[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
		[NpcGuid] [uniqueidentifier] NOT NULL,
		[Menu] [int] NOT NULL,
		[OrderIndex] [int] NOT NULL,
		[ItemNo] [int] NOT NULL,
		[ItemCount] [int] NOT NULL,
		[Gem1] [int] NULL,
		[GemCount1] [smallint] NULL,
		[Gem2] [int] NULL,
		[GemCount2] [smallint] NULL,
		[Gem3] [int] NULL,
		[GemCount3] [smallint] NULL,
		[Gem4] [int] NULL,
		[GemCount4] [smallint] NULL,
		[Gem5] [int] NULL,
		[GemCount5] [smallint] NULL,
	 CONSTRAINT [PK_TB_DefGemStore] PRIMARY KEY CLUSTERED 
	(
		[idx] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END

IF EXISTS(SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'dbo.TB_DefGemStore') and [name] = N'PK_TB_DefGemStore')
BEGIN
	ALTER TABLE dbo.TB_DefGemStore DROP CONSTRAINT PK_TB_DefGemStore

	ALTER TABLE dbo.TB_DefGemStore ADD CONSTRAINT
	PK_TB_DefGemStore2 PRIMARY KEY CLUSTERED
	(
	NpcGuid,
	Menu,
	OrderIndex,
	ItemNo
	) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END
GO

IF NOT EXISTS (SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefGemStore]') AND [name] = N'NationCodeStr')
BEGIN
	
	CREATE TABLE dbo.Tmp_TB_DefGemStore(
		idx int IDENTITY(1,1) NOT NULL,
		NationCodeStr nvarchar(50) NOT NULL,
		Memo nvarchar(50) COLLATE Korean_Wansung_CI_AS NULL,
		NpcGuid uniqueidentifier NOT NULL,
		Menu int NOT NULL,
		OrderIndex int NOT NULL,
		ItemNo int NOT NULL,
		ItemCount int NOT NULL,
		Gem1 int NULL,
		GemCount1 smallint NULL,
		Gem2 int NULL,
		GemCount2 smallint NULL,
		Gem3 int NULL,
		GemCount3 smallint NULL,
		Gem4 int NULL,
		GemCount4 smallint NULL,
		Gem5 int NULL,
		GemCount5 smallint NULL,
	 CONSTRAINT PK_TB_DefGemStore5 PRIMARY KEY CLUSTERED 
	(
		[idx] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
	
	SET IDENTITY_INSERT Tmp_TB_DefGemStore ON
	
	IF EXISTS (SELECT * FROM dbo.TB_DefGemStore)
	EXEC('INSERT INTO dbo.Tmp_TB_DefGemStore (idx, NationCodeStr, Memo, NpcGuid, Menu, OrderIndex, ItemNo, ItemCount, Gem1, GemCount1, Gem2, GemCount2, Gem3, GemCount3, Gem4, GemCount4, Gem5, GemCount5)
		  SELECT idx, 0, Memo, NpcGuid, Menu, OrderIndex, ItemNo, ItemCount, Gem1, GemCount1, Gem2, GemCount2, Gem3, GemCount3, Gem4, GemCount4, Gem5, GemCount5
		  FROM dbo.TB_DefGemStore WITH (HOLDLOCK TABLOCKX)')
		  
	SET IDENTITY_INSERT Tmp_TB_DefGemStore OFF
		
	DROP TABLE TB_DefGemStore
		
	EXECUTE sp_rename N'dbo.Tmp_TB_DefGemStore', 'TB_DefGemStore', 'OBJECT'

END
GO

ALTER TABLE dbo.TB_DefGemStore
	DROP CONSTRAINT PK_TB_DefGemStore5
GO

ALTER TABLE dbo.TB_DefGemStore ADD CONSTRAINT
	PK_TB_DefGemStore5 PRIMARY KEY CLUSTERED 
	(
	NationCodeStr,
	NpcGuid,
	Menu,
	OrderIndex,
	ItemNo
	) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

GO