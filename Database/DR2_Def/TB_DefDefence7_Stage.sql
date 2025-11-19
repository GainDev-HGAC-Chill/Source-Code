USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefDefence7_Stage]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefDefence7_Stage](
		[Idx] [int] IDENTITY(1,1) NOT NULL,
		[Mission_No] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Stage_Mission_No] DEFAULT ((0)),
		[Mission_Type] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Stage_Mission_Type] DEFAULT ((0)),
		[Party_Number] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Stage_Party_Number] DEFAULT ((0)),
		[Stage_No] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Stage_Stage_No] DEFAULT ((0)),
		[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,		
		[Result_ItemNo] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Stage_Result_ItemNo] DEFAULT ((0)),
		[Result_ItemCount] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Stage_Result_ItemCount] DEFAULT ((0)),
		[Clear_StategicPoint] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Stage_Clear_StategicPoint] DEFAULT ((0)),
		[Winning_Point] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Stage_Winning_Point] DEFAULT ((0))
	CONSTRAINT [PK_TB_DefDefence7_Stage] PRIMARY KEY CLUSTERED 
	(
		[Idx] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

GO

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefDefence7_Stage]') AND [name] = N'Winning_Point')
BEGIN
	ALTER TABLE dbo.TB_DefDefence7_Stage
		DROP CONSTRAINT DF_TB_DefDefence7_Stage_Winning_Point
	ALTER TABLE dbo.TB_DefDefence7_Stage
		DROP COLUMN Winning_Point		
END	

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefDefence7_Stage]') and [name] = N'Clear_StategicPoint')
BEGIN
	EXECUTE sp_rename N'dbo.TB_DefDefence7_Stage.Clear_StategicPoint', N'Clear_StrategicPoint', 'COLUMN' 
END


IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefDefence7_Stage]') AND [name] = N'Win_ItemNo')
BEGIN
	ALTER TABLE dbo.TB_DefDefence7_Stage
		DROP CONSTRAINT DF_TB_DefDefence7_Stage_Mission_No
	ALTER TABLE dbo.TB_DefDefence7_Stage
		DROP CONSTRAINT DF_TB_DefDefence7_Stage_Mission_Type
	ALTER TABLE dbo.TB_DefDefence7_Stage
		DROP CONSTRAINT DF_TB_DefDefence7_Stage_Party_Number
	ALTER TABLE dbo.TB_DefDefence7_Stage
		DROP CONSTRAINT DF_TB_DefDefence7_Stage_Stage_No
	ALTER TABLE dbo.TB_DefDefence7_Stage
		DROP CONSTRAINT DF_TB_DefDefence7_Stage_Result_ItemNo
	ALTER TABLE dbo.TB_DefDefence7_Stage
		DROP CONSTRAINT DF_TB_DefDefence7_Stage_Result_ItemCount
	ALTER TABLE dbo.TB_DefDefence7_Stage
		DROP CONSTRAINT DF_TB_DefDefence7_Stage_Clear_StategicPoint
	CREATE TABLE dbo.Tmp_TB_DefDefence7_Stage
		(
		Idx int NOT NULL IDENTITY (1, 1),
		Mission_No int NOT NULL,
		Mission_Type int NOT NULL,
		Party_Number int NOT NULL,
		Stage_No int NOT NULL,
		Memo nvarchar(50) NULL,
		Result_ItemNo int NOT NULL,
		Result_ItemCount int NOT NULL,
		Win_ItemNo int NOT NULL,
		Win_ItemCount int NOT NULL,
		Clear_StrategicPoint int NOT NULL
		)  ON [PRIMARY]
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Stage ADD CONSTRAINT
		DF_TB_DefDefence7_Stage_Mission_No DEFAULT ((0)) FOR Mission_No
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Stage ADD CONSTRAINT
		DF_TB_DefDefence7_Stage_Mission_Type DEFAULT ((0)) FOR Mission_Type
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Stage ADD CONSTRAINT
		DF_TB_DefDefence7_Stage_Party_Number DEFAULT ((0)) FOR Party_Number
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Stage ADD CONSTRAINT
		DF_TB_DefDefence7_Stage_Stage_No DEFAULT ((0)) FOR Stage_No
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Stage ADD CONSTRAINT
		DF_TB_DefDefence7_Stage_Result_ItemNo DEFAULT ((0)) FOR Result_ItemNo
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Stage ADD CONSTRAINT
		DF_TB_DefDefence7_Stage_Result_ItemCount DEFAULT ((0)) FOR Result_ItemCount		
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Stage ADD CONSTRAINT
		DF_TB_DefDefence7_Stage_Win_ItemNo DEFAULT ((0)) FOR Win_ItemNo
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Stage ADD CONSTRAINT
		DF_TB_DefDefence7_Stage_Win_ItemCount DEFAULT ((0)) FOR Win_ItemCount		
	ALTER TABLE dbo.Tmp_TB_DefDefence7_Stage ADD CONSTRAINT
		DF_TB_DefDefence7_Stage_Clear_StrategicPoint DEFAULT ((0)) FOR Clear_StrategicPoint
	SET IDENTITY_INSERT dbo.Tmp_TB_DefDefence7_Stage ON
	IF EXISTS(SELECT * FROM dbo.TB_DefDefence7_Stage)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefDefence7_Stage (Idx, Mission_No, Mission_Type, Party_Number, Stage_No, Memo, Result_ItemNo, Result_ItemCount, Clear_StrategicPoint)
			SELECT Idx, Mission_No, Mission_Type, Party_Number, Stage_No, Memo, Result_ItemNo, Result_ItemCount, Clear_StrategicPoint FROM dbo.TB_DefDefence7_Stage WITH (HOLDLOCK TABLOCKX)')
	SET IDENTITY_INSERT dbo.Tmp_TB_DefDefence7_Stage OFF
	DROP TABLE dbo.TB_DefDefence7_Stage
	EXECUTE sp_rename N'dbo.Tmp_TB_DefDefence7_Stage', N'TB_DefDefence7_Stage', 'OBJECT' 
	ALTER TABLE dbo.TB_DefDefence7_Stage ADD CONSTRAINT
		PK_TB_DefDefence7_Stage PRIMARY KEY CLUSTERED 
		(
		Idx
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefDefence7_Stage') AND [name] = N'Result_No')
BEGIN
	ALTER TABLE [dbo].[TB_DefDefence7_Stage] ADD
		[Result_No] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Stage_Result_No]  DEFAULT ((0))	
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefDefence7_Stage') AND [name] = N'Result_Count')
BEGIN
	ALTER TABLE [dbo].[TB_DefDefence7_Stage] ADD
		[Result_Count] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Stage_Result_Count]  DEFAULT ((0))	
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefDefence7_Stage') AND [name] = N'UseCoin_StrategicPoint')
BEGIN
	ALTER TABLE [dbo].[TB_DefDefence7_Stage] ADD
		[UseCoin_StrategicPoint] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_UseCoin_StrategicPoint]  DEFAULT ((0))	
END

GO
	
