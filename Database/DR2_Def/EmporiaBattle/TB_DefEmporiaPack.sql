SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

USE [DR2_Def]
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEmporiaPack]') AND type in (N'U'))
BEGIN

	CREATE TABLE [dbo].[TB_DefEmporiaPack](
		[EmporiaID] [UNIQUEIDENTIFIER] NOT NULL,
		[BaseMapNo]	[int] NOT NULL,
		[Memo] [nvarchar](200) NULL,
		[Grade1_GroundNo] [int] NOT NULL,
		[Grade2_GroundNo] [int] NOT NULL,
		[Grade3_GroundNo] [int] NOT NULL,
		[Grade4_GroundNo] [int] NOT NULL,
		[Grade5_GroundNo] [int] NOT NULL,
		[Challenge_BattleGroundNo] [int] NOT NULL CONSTRAINT [DF_TB_DefEmporiaPack_Challenge_BattleGroundNo] DEFAULT ((9930100)),
		[Grade1_BattleGroundNo] [int] NOT NULL CONSTRAINT [DF_TB_DefEmporiaPack_Grade1_BattleGroundNo] DEFAULT ((9930200)),
		[Grade2_BattleGroundNo] [int] NOT NULL CONSTRAINT [DF_TB_DefEmporiaPack_Grade2_BattleGroundNo] DEFAULT ((9930210)),
		[Grade3_BattleGroundNo] [int] NOT NULL CONSTRAINT [DF_TB_DefEmporiaPack_Grade3_BattleGroundNo] DEFAULT ((9930220)),
		[Grade4_BattleGroundNo] [int] NOT NULL CONSTRAINT [DF_TB_DefEmporiaPack_Grade4_BattleGroundNo] DEFAULT ((9930230)),
		[Grade5_BattleGroundNo] [int] NOT NULL CONSTRAINT [DF_TB_DefEmporiaPack_Grade5_BattleGroundNo] DEFAULT ((9930240)),
		CONSTRAINT [IX_TB_DefEmporiaPack] UNIQUE CLUSTERED 
		(
			[EmporiaID] ASC
		)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
	
	INSERT INTO [dbo].[TB_DefEmporiaPack]
	(	
		[EmporiaID],[BaseMapNo],[Grade1_GroundNo],[Grade2_GroundNo],[Grade3_GroundNo],[Grade4_GroundNo],[Grade5_GroundNo]
	)
	VALUES
	(
		'08d22596-2500-46be-ac82-8e50c6e9391b',	9018100, 9018251, 9018252, 9018253, 9018254, 9018255
	)
END

IF NOT EXISTS (SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefEmporiaPack') AND [name] = N'Challenge_BattleGroundNo')
BEGIN
	ALTER TABLE [dbo].[TB_DefEmporiaPack] ADD [Challenge_BattleGroundNo] [int] NOT NULL CONSTRAINT [DF_TB_DefEmporiaPack_Challenge_BattleGroundNo] DEFAULT ((9930100))
	ALTER TABLE [dbo].[TB_DefEmporiaPack] ADD [Grade1_BattleGroundNo] [int] NOT NULL CONSTRAINT [DF_TB_DefEmporiaPack_Grade1_BattleGroundNo] DEFAULT ((9930200))
	ALTER TABLE [dbo].[TB_DefEmporiaPack] ADD [Grade2_BattleGroundNo] [int] NOT NULL CONSTRAINT [DF_TB_DefEmporiaPack_Grade2_BattleGroundNo] DEFAULT ((9930210))
	ALTER TABLE [dbo].[TB_DefEmporiaPack] ADD [Grade3_BattleGroundNo] [int] NOT NULL CONSTRAINT [DF_TB_DefEmporiaPack_Grade3_BattleGroundNo] DEFAULT ((9930220))
	ALTER TABLE [dbo].[TB_DefEmporiaPack] ADD [Grade4_BattleGroundNo] [int] NOT NULL CONSTRAINT [DF_TB_DefEmporiaPack_Grade4_BattleGroundNo] DEFAULT ((9930230))
	ALTER TABLE [dbo].[TB_DefEmporiaPack] ADD [Grade5_BattleGroundNo] [int] NOT NULL CONSTRAINT [DF_TB_DefEmporiaPack_Grade5_BattleGroundNo] DEFAULT ((9930240))
END
GO

IF NOT EXISTS (SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefEmporiaPack') AND [name] = N'LimitCost')
BEGIN
	ALTER TABLE [dbo].[TB_DefEmporiaPack] ADD [LimitCost] [int] NOT NULL CONSTRAINT [DF_TB_DefEmporiaPack_LimitCost] DEFAULT ((1000000))
END
GO
