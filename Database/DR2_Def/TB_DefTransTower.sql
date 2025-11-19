USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO
	
IF  NOT EXISTS (SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'TB_DefTransTower'))
BEGIN
	
	CREATE TABLE [dbo].[TB_DefTransTower](
		[ID] [uniqueidentifier] NOT NULL,
		[Sort] [smallint] NOT NULL CONSTRAINT [DF_TB_DefTransTower_Sort]  DEFAULT ((0)),
		[GroundNo] [int] NOT NULL,
		[Spawn] [smallint] NOT NULL,
		[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
		[Price] [bigint] NOT NULL,
		[NameNo] [int] NOT NULL,
	 CONSTRAINT [PK_TB_DefTransTower] PRIMARY KEY CLUSTERED 
	(
		[ID] ASC,
		[Sort] ASC,
		[GroundNo] ASC,
		[Spawn] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
	
END
ELSE
BEGIN
	
	IF  NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefTransTower_Sort]') AND type = 'D')
	BEGIN
	
		ALTER TABLE [dbo].[TB_DefTransTower]
		ADD [Sort] [smallint] NOT NULL CONSTRAINT [DF_TB_DefTransTower_Sort] DEFAULT ((0))
	
		ALTER TABLE [dbo].[TB_DefTransTower]
		DROP CONSTRAINT [PK_TB_DefTransTower]
	
		ALTER TABLE [dbo].[TB_DefTransTower]
		ADD CONSTRAINT [PK_TB_DefTransTower] PRIMARY KEY CLUSTERED([ID] ASC, [Sort] ASC, [GroundNo] ASC, [Spawn] ASC)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
		
	END
END
GO
