USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefJobSkill_MachineStatus]') AND [type] IN (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefJobSkill_MachineStatus](
		[f_GatherType] [int] NOT NULL,
		[f_Item_Grade] [int] NOT NULL,
		[f_Memo] nvarchar(50) NULL,
		[f_Machine_Status] [int] NOT NULL,
		[f_Machine_FromStatus] [int] NOT NULL,
		[f_Status_Probability] [int] NOT NULL,
		[f_Status_TotalProbability] [int] NOT NULL,
		[f_Status_TickTime] [int] NOT NULL,
		[f_Status_ModelXmlPath] [int] NOT NULL,
		[f_UnCommon_Txt] [int] NOT NULL,
		[f_Repair_Txt] [int] NOT NULL,
	 CONSTRAINT [PK_TB_DefJobSkill_MachineStatus] PRIMARY KEY CLUSTERED 
	(
		[f_GatherType] ASC,
		[f_Item_Grade] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

/****** Object:  Table [dbo].[TB_DefJobSkill_MachineStatus]    Script Date: 11/29/2012 15:44:09 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefJobSkill_MachineStatus]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DefJobSkill_MachineStatus]
GO
