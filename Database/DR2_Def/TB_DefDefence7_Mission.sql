USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefDefence7_Mission]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefDefence7_Mission](
		[Idx] [int] IDENTITY(1,1) NOT NULL,
		[Mission_No] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Mission_No] DEFAULT ((0)),
		[Mission_Type] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Mission_Type] DEFAULT ((0)),
		[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,		
		[Min_Level] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Min_Level] DEFAULT ((0)),
		[Max_Level] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Max_Level] DEFAULT ((0)),
		[Danger_Ranger] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Danger_Ranger] DEFAULT ((0)),
		[Win_ItemNo] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Win_ItemNo] DEFAULT ((0)),
		[Win_ItemCount] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Win_ItemCount] DEFAULT ((0)),
		[Draw_Stage] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Draw_Stage] DEFAULT ((0)),
		[Slot_F5] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Slot_F5] DEFAULT ((0)),
		[Slot_F6] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Slot_F6] DEFAULT ((0)),
		[Slot_F7] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Slot_F7] DEFAULT ((0)),
		[Slot_F8] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Slot_F8] DEFAULT ((0)),
		[Skill01] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Skill01] DEFAULT ((0)),
		[Skill02] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Skill02] DEFAULT ((0)),
		[Skill03] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Skill03] DEFAULT ((0)),
		[Skill04] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Skill04] DEFAULT ((0)),
		[Skill05] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Skill05] DEFAULT ((0)),
		[Skill06] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Skill06] DEFAULT ((0)),
		[Skill07] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Skill07] DEFAULT ((0)),
		[Skill08] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Skill08] DEFAULT ((0)),
		[Skill09] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Skill09] DEFAULT ((0)),
		[Skill10] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Skill10] DEFAULT ((0)),
		[Item01_F7] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Item01_F7] DEFAULT ((0)),
		[Item02_F7] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Item02_F7] DEFAULT ((0)),
		[Item03_F7] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Item03_F7] DEFAULT ((0)),
		[Item04_F7] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Item04_F7] DEFAULT ((0)),
		[Item05_F7] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Item05_F7] DEFAULT ((0)),
		[Item06_F7] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Item06_F7] DEFAULT ((0)),
		[Item07_F7] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Item07_F7] DEFAULT ((0)),
		[Item08_F7] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Item08_F7] DEFAULT ((0)),
		[Item09_F7] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Item09_F7] DEFAULT ((0)),
		[Item10_F7] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Item10_F7] DEFAULT ((0)),
		[Item11_F7] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Item11_F7] DEFAULT ((0)),
		[Item12_F7] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Item12_F7] DEFAULT ((0)),
		[Item13_F7] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Item13_F7] DEFAULT ((0)),
		[Item14_F7] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Item14_F7] DEFAULT ((0)),
		[Item15_F7] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Mission_Item15_F7] DEFAULT ((0))
	CONSTRAINT [PK_TB_DefDefence7_Mission] PRIMARY KEY CLUSTERED 
	(
		[Idx] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END
ELSE
BEGIN	
	IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefDefence7_Mission]') AND [name] = N'Item01_F8')
	BEGIN	
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP CONSTRAINT [DF_TB_DefDefence7_Mission_Item01_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP CONSTRAINT [DF_TB_DefDefence7_Mission_Item02_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP CONSTRAINT [DF_TB_DefDefence7_Mission_Item03_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP CONSTRAINT [DF_TB_DefDefence7_Mission_Item04_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP CONSTRAINT [DF_TB_DefDefence7_Mission_Item05_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP CONSTRAINT [DF_TB_DefDefence7_Mission_Item06_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP CONSTRAINT [DF_TB_DefDefence7_Mission_Item07_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP CONSTRAINT [DF_TB_DefDefence7_Mission_Item08_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP CONSTRAINT [DF_TB_DefDefence7_Mission_Item09_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP CONSTRAINT [DF_TB_DefDefence7_Mission_Item10_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP CONSTRAINT [DF_TB_DefDefence7_Mission_Item11_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP CONSTRAINT [DF_TB_DefDefence7_Mission_Item12_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP CONSTRAINT [DF_TB_DefDefence7_Mission_Item13_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP CONSTRAINT [DF_TB_DefDefence7_Mission_Item14_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP CONSTRAINT [DF_TB_DefDefence7_Mission_Item15_F8]

		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP COLUMN [Item01_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP COLUMN [Item02_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP COLUMN [Item03_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP COLUMN [Item04_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP COLUMN [Item05_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP COLUMN [Item06_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP COLUMN [Item07_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP COLUMN [Item08_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP COLUMN [Item09_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP COLUMN [Item10_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP COLUMN [Item11_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP COLUMN [Item12_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP COLUMN [Item13_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP COLUMN [Item14_F8]
		ALTER TABLE [dbo].[TB_DefDefence7_Mission] DROP COLUMN [Item15_F8]
	END
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefDefence7_Mission]') and [name] = N'Danger_Ranger')
BEGIN
	EXECUTE sp_rename N'[dbo].[TB_DefDefence7_Mission].[Danger_Ranger]', N'Danger_Range', 'column'
END

GO

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefDefence7_Mission]') and [name] = N'Danger_Range')
BEGIN
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Danger_Ranger
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Win_ItemNo
	ALTER TABLE dbo.TB_DefDefence7_Mission	
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Win_ItemCount
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Draw_Stage
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Skill09
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Skill10
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Item01_F7
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Item02_F7
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Item03_F7
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Item04_F7
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Item05_F7
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Item06_F7
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Item07_F7
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Item08_F7
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Item09_F7
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Item10_F7
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Item11_F7
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Item12_F7
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Item13_F7
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Item14_F7
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Item15_F7
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP COLUMN Danger_Range, Win_ItemNo, Win_ItemCount, Draw_Stage, Skill09, Skill10, Item01_F7, Item02_F7, Item03_F7, Item04_F7, Item05_F7, Item06_F7, Item07_F7, Item08_F7, Item09_F7, Item10_F7, Item11_F7, Item12_F7, Item13_F7, Item14_F7, Item15_F7
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefDefence7_Mission]') AND [name] = N'Slot_F1')
BEGIN
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Mission_No
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Mission_Type
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Min_Level
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Max_Level
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Slot_F5
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Slot_F6
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Slot_F7
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Slot_F8
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Skill01
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Skill02
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Skill03
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Skill04
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Skill05
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Skill06
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Skill07
	ALTER TABLE dbo.TB_DefDefence7_Mission
		DROP CONSTRAINT DF_TB_DefDefence7_Mission_Skill08
	CREATE TABLE dbo.Tmp_TB_DefDefence7_Mission
		(
		Idx int NOT NULL IDENTITY (1, 1),
		Mission_No int NOT NULL,
		Mission_Type int NOT NULL,
		Memo nvarchar(50) NULL,
		Min_Level int NOT NULL,
		Max_Level int NOT NULL,
		Slot_F1 int NOT NULL,
		Slot_F2 int NOT NULL,
		Slot_F3 int NOT NULL,
		Slot_F4 int NOT NULL,
		Slot_F5 int NOT NULL,
		Slot_F6 int NOT NULL,
		Slot_F7 int NOT NULL,
		Slot_F8 int NOT NULL,
		Skill01 int NOT NULL,
		Skill02 int NOT NULL,
		Skill03 int NOT NULL,
		Skill04 int NOT NULL,
		Skill05 int NOT NULL,
		Skill06 int NOT NULL,
		Skill07 int NOT NULL,
		Skill08 int NOT NULL
		)  ON [PRIMARY]
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Mission_No DEFAULT ((0)) FOR Mission_No
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Mission_Type DEFAULT ((0)) FOR Mission_Type
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Min_Level DEFAULT ((0)) FOR Min_Level
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Max_Level DEFAULT ((0)) FOR Max_Level
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Slot_F1 DEFAULT ((0)) FOR Slot_F1
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Slot_F2 DEFAULT ((0)) FOR Slot_F2
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Slot_F3 DEFAULT ((0)) FOR Slot_F3
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Slot_F4 DEFAULT ((0)) FOR Slot_F4		
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Slot_F5 DEFAULT ((0)) FOR Slot_F5
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Slot_F6 DEFAULT ((0)) FOR Slot_F6
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Slot_F7 DEFAULT ((0)) FOR Slot_F7
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Slot_F8 DEFAULT ((0)) FOR Slot_F8
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Skill01 DEFAULT ((0)) FOR Skill01
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Skill02 DEFAULT ((0)) FOR Skill02
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Skill03 DEFAULT ((0)) FOR Skill03
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Skill04 DEFAULT ((0)) FOR Skill04
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Skill05 DEFAULT ((0)) FOR Skill05
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Skill06 DEFAULT ((0)) FOR Skill06
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Skill07 DEFAULT ((0)) FOR Skill07
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Mission ADD CONSTRAINT
		DF_TB_DefDefence7_Mission_Skill08 DEFAULT ((0)) FOR Skill08
	SET IDENTITY_INSERT dbo.Tmp_TB_DefDefence7_Mission ON
	IF EXISTS(SELECT * FROM dbo.TB_DefDefence7_Mission)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefDefence7_Mission (Idx, Mission_No, Mission_Type, Memo, Min_Level, Max_Level, Slot_F5, Slot_F6, Slot_F7, Slot_F8, Skill01, Skill02, Skill03, Skill04, Skill05, Skill06, Skill07, Skill08)
			SELECT Idx, Mission_No, Mission_Type, Memo, Min_Level, Max_Level, Slot_F5, Slot_F6, Slot_F7, Slot_F8, Skill01, Skill02, Skill03, Skill04, Skill05, Skill06, Skill07, Skill08 FROM dbo.TB_DefDefence7_Mission WITH (HOLDLOCK TABLOCKX)')
	SET IDENTITY_INSERT dbo.Tmp_TB_DefDefence7_Mission OFF
	DROP TABLE dbo.TB_DefDefence7_Mission
	EXECUTE sp_rename N'dbo.Tmp_TB_DefDefence7_Mission', N'TB_DefDefence7_Mission', 'OBJECT' 
	ALTER TABLE dbo.TB_DefDefence7_Mission ADD CONSTRAINT
		PK_TB_DefDefence7_Mission PRIMARY KEY CLUSTERED 
		(
		Idx
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END
GO
