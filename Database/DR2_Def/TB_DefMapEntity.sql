USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF not EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='TB_DefMapEntity' AND COLUMN_NAME='f_NationCodeStr') BEGIN

CREATE TABLE #temp(
	[GroundNo] [int] NOT NULL,
	[Memo] [nvarchar](max) NULL,
	[iClass] [int] NOT NULL,
	[iLevel] [smallint] NOT NULL,
	[iEffect] [int] NOT NULL,
	[MinX] [real] NOT NULL,
	[MinY] [real] NOT NULL,
	[MinZ] [real] NOT NULL,
	[MaxX] [real] NOT NULL,
	[MaxY] [real] NOT NULL,
	[MaxZ] [real] NOT NULL,
	[OwnerPointGuid] [uniqueidentifier] NULL,
)

INSERT INTO #temp
           ([GroundNo]           ,[Memo]           ,[iClass]           ,[iLevel]
           ,[iEffect]           ,[MinX]           ,[MinY]           ,[MinZ]
           ,[MaxX]           ,[MaxY]           ,[MaxZ]           ,[OwnerPointGuid])
   SELECT [GroundNo]      ,[Memo]      ,[iClass]      ,[iLevel]      ,[iEffect]
      ,[MinX]      ,[MinY]      ,[MinZ]      ,[MaxX]      ,[MaxY]      ,[MaxZ]
      ,[OwnerPointGuid]
      
  FROM [TB_DefMapEntity]

/****** Object:  Table [dbo].[TB_DefMapEntity]    Script Date: 01/07/2013 17:18:12 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefMapEntity]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DefMapEntity]


CREATE TABLE [dbo].[TB_DefMapEntity](
	[IDX] [int] IDENTITY(1,1) NOT NULL,
	[f_NationCodeStr] [nvarchar](50)  DEFAULT '0',
	[GroundNo] [int] NOT NULL,
	[Memo] [nvarchar](max) NULL,
	[iClass] [int] NOT NULL,
	[iLevel] [smallint] NOT NULL,
	[iEffect] [int] NOT NULL,
	[MinX] [real] NOT NULL,
	[MinY] [real] NOT NULL,
	[MinZ] [real] NOT NULL,
	[MaxX] [real] NOT NULL,
	[MaxY] [real] NOT NULL,
	[MaxZ] [real] NOT NULL,
	[OwnerPointGuid] [uniqueidentifier] NULL,
 CONSTRAINT [PK_TB_DefMapEntity] PRIMARY KEY CLUSTERED 
(
	[IDX] ASC,
	[f_NationCodeStr] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]


EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Map entity definition
Detail :
Some maps have special area which have special effect like poision' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefMapEntity'

INSERT INTO [TB_DefMapEntity]
           ([f_NationCodeStr] ,   [GroundNo]           ,[Memo]           ,[iClass]
           ,[iLevel]           ,[iEffect]           ,[MinX]           ,[MinY]
           ,[MinZ]           ,[MaxX]           ,[MaxY]           ,[MaxZ]
           ,[OwnerPointGuid])
             
SELECT '0'      ,[GroundNo]      ,[Memo]      ,[iClass]      ,[iLevel]
      ,[iEffect]      ,[MinX]      ,[MinY]      ,[MinZ]      ,[MaxX]
      ,[MaxY]      ,[MaxZ]      ,[OwnerPointGuid]
  FROM #temp 

DROP TABLE #TEMP

END --end if