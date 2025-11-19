USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefItemBasicOptionAmp]    Script Date: 02/09/2010 12:26:10 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id=OBJECT_ID(N'[dbo].[TB_DefItemBasicOptionAmp]'))
BEGIN
	DROP TABLE dbo.TB_DefItemBasicOptionAmp
END
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id=OBJECT_ID(N'[dbo].[TB_DefItemAmplify]'))
BEGIN
CREATE TABLE [dbo].[TB_DefItemAmplify](
	[index] [int] IDENTITY(1,1) NOT FOR REPLICATION NOT NULL,
	[EquipPos] [int] NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[LevelLimit] [int] NOT NULL,
	[AmplifyOptValueLV] [int] NOT NULL,
	[SuccessRate] [int] NOT NULL,
	[SoulItemCount] [int] NOT NULL,
	[NeedMoney] [int] NOT NULL,
 	[AmplifyItemNo] [int] NOT NULL,
	[AmplifyItemCount] [int] NOT NULL,
	[InsuranceItemNo] [int] NOT NULL,
	[AmplifyRate] [int] NOT NULL,
	[Amplify_MaxValueLV] [int] NOT NULL,
 CONSTRAINT [PK_TB_DefItemAmplify] PRIMARY KEY CLUSTERED 
(
	[EquipPos] ASC,
	[LevelLimit] ASC,
	[AmplifyOptValueLV] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefItemAmplify]') and name = N'EquipPos')
BEGIN
	exec sp_rename N'[dbo].[TB_DefItemAmplify].[EquipPos]', N'EquipType', N'COLUMN'
END
GO
