USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefMapInsItemRegen_01]    Script Date: 03/26/2009 15:24:09 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[TB_DefMapInsItemRegen_01](
	[IDX] [int] IDENTITY(1,1) NOT NULL,
	[MapNo] [int] NOT NULL,
	[PointGuid] [uniqueidentifier] NOT NULL,
	[ParentBagType] [tinyint] NOT NULL,
	[ParentBagNo] [int] NOT NULL,
	[Memo] [nvarchar](max) NULL,
	[PointGroup] [int] NOT NULL,
	[RegenPeriod] [int] NOT NULL,
	[PosX] [float] NOT NULL,
	[PosY] [float] NOT NULL,
	[PosZ] [float] NOT NULL,
	[MoveRange] [int] NOT NULL,
 CONSTRAINT [PK_TB_DefMapInsItemRegen_01] PRIMARY KEY CLUSTERED 
(
	[PointGuid] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'instance item generation in the map' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefMapInsItemRegen_01'

/* Column Ãß°¡ DIRECTION */
IF NOT EXISTS (SELECT * FROM sys.all_objects WHERE NAME = 'DF_TB_DefMapInsItemRegen_01_Direction')
BEGIN
	ALTER TABLE [dbo].[TB_DefMapInsItemRegen_01] ADD [Direction] [tinyint] NOT NULL CONSTRAINT [DF_TB_DefMapInsItemRegen_01_Direction]  DEFAULT ((255))
END

