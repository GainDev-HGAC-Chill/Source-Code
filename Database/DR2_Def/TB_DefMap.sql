USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF not  EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='TB_DefMap' AND COLUMN_NAME='f_NationCodeStr') BEGIN

--템프테이블 생성
CREATE TABLE #temp(

	[MapNo] [int] NOT NULL,
	[MapKey] [int] NOT NULL,
	[Attribute] [int] NOT NULL,
	[Memo] [nvarchar](200) NULL,
	[NameNo] [int] NOT NULL,
	[XmlPath] [nvarchar](100) NOT NULL,
	[ZoneCX] [smallint] NOT NULL,
	[ZoneCY] [smallint] NOT NULL,
	[ZoneCZ] [smallint] NOT NULL,
	[Continent] [smallint] NOT NULL,
	[HometownNo] [smallint] NULL,
	[Hidden_Index] [smallint] NOT NULL,
	[Abil01] [int] NOT NULL,
	[Abil02] [int] NOT NULL,
	[Abil03] [int] NOT NULL,
	[Abil04] [int] NOT NULL,
	[Abil05] [int] NOT NULL,
	[Recommend_Level] [tinyint] NOT NULL,
	[Recommend_Party] [tinyint] NOT NULL,
	[Group_TXT] [int] NOT NULL,
	[LevelLimit_Min] [tinyint] NOT NULL,
	[LevelLimit_Max] [tinyint] NOT NULL,
	[DESCRIPTION_TEXT] [int] NOT NULL,
	[PartyBreakIn] [tinyint] NOT NULL,
	)-- END CREATE TEMP TABLE
	
--템프에 기존테이블 복사	
	INSERT INTO #temp
           ([MapNo]           ,[MapKey]           ,[Attribute]           ,[Memo]
           ,[NameNo]           ,[XmlPath]           ,[ZoneCX]           ,[ZoneCY]
           ,[ZoneCZ]           ,[Continent]           ,[HometownNo]           ,[Hidden_Index]
           ,[Abil01]           ,[Abil02]           ,[Abil03]           ,[Abil04]
           ,[Abil05]           ,[Recommend_Level]           ,[Recommend_Party]           ,[Group_TXT]
           ,[LevelLimit_Min]           ,[LevelLimit_Max]           ,[DESCRIPTION_TEXT]
           ,[PartyBreakIn])
		SELECT   [MapNo]		  ,[MapKey]			  ,[Attribute]			  ,[Memo]
			  ,[NameNo]			  ,[XmlPath]			  ,[ZoneCX]			  ,[ZoneCY]			  ,[ZoneCZ]
			  ,[Continent]			  ,[HometownNo]			  ,[Hidden_Index]			  ,[Abil01]
			  ,[Abil02]			  ,[Abil03]			  ,[Abil04]			  ,[Abil05]			  ,[Recommend_Level]
			  ,[Recommend_Party]			  ,[Group_TXT]			  ,[LevelLimit_Min]
			  ,[LevelLimit_Max]			  ,[DESCRIPTION_TEXT]			  ,[PartyBreakIn]
		FROM  [TB_DefMap]


 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMap_Hidden_Index]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMap] DROP CONSTRAINT [DF_TB_DefMap_Hidden_Index]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMap_Abil01]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMap] DROP CONSTRAINT [DF_TB_DefMap_Abil01]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMap_Abil02]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMap] DROP CONSTRAINT [DF_TB_DefMap_Abil02]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMap_Abil03]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMap] DROP CONSTRAINT [DF_TB_DefMap_Abil03]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMap_Abil04]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMap] DROP CONSTRAINT [DF_TB_DefMap_Abil04]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMap_Abil05]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMap] DROP CONSTRAINT [DF_TB_DefMap_Abil05]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMap_Recommend_Level]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMap] DROP CONSTRAINT [DF_TB_DefMap_Recommend_Level]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMap_Recommend_Party]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMap] DROP CONSTRAINT [DF_TB_DefMap_Recommend_Party]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMap_Group_TXT]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMap] DROP CONSTRAINT [DF_TB_DefMap_Group_TXT]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMap_LevelLimit_Min]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMap] DROP CONSTRAINT [DF_TB_DefMap_LevelLimit_Min]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMap_LevelLimit_Max]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMap] DROP CONSTRAINT [DF_TB_DefMap_LevelLimit_Max]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMap_DESCRIPTION_TEXT]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMap] DROP CONSTRAINT [DF_TB_DefMap_DESCRIPTION_TEXT]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMap_PartyBreakIn]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMap] DROP CONSTRAINT [DF_TB_DefMap_PartyBreakIn]
END
  

/****** Object:  Table [dbo].[TB_DefMap]    Script Date: 01/07/2013 16:16:31 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefMap]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DefMap]



--새로만든다.
 

CREATE TABLE [dbo].[TB_DefMap](
	[IDX] [int] IDENTITY(1,1) NOT FOR REPLICATION NOT NULL,
	[f_NationCodeStr] [nvarchar](50)  DEFAULT '0',
	[MapNo] [int] NOT NULL,
	[MapKey] [int] NOT NULL,
	[Attribute] [int] NOT NULL,
	[Memo] [nvarchar](200) NULL,
	[NameNo] [int] NOT NULL,
	[XmlPath] [nvarchar](100) NOT NULL,
	[ZoneCX] [smallint] NOT NULL,
	[ZoneCY] [smallint] NOT NULL,
	[ZoneCZ] [smallint] NOT NULL,
	[Continent] [smallint] NOT NULL,
	[HometownNo] [smallint] NULL,
	[Hidden_Index] [smallint] NOT NULL,
	[Abil01] [int] NOT NULL,
	[Abil02] [int] NOT NULL,
	[Abil03] [int] NOT NULL,
	[Abil04] [int] NOT NULL,
	[Abil05] [int] NOT NULL,
	[Recommend_Level] [tinyint] NOT NULL,
	[Recommend_Party] [tinyint] NOT NULL,
	[Group_TXT] [int] NOT NULL,
	[LevelLimit_Min] [tinyint] NOT NULL,
	[LevelLimit_Max] [tinyint] NOT NULL,
	[DESCRIPTION_TEXT] [int] NOT NULL,
	[PartyBreakIn] [tinyint] NOT NULL,
 CONSTRAINT [PK_TB_DefMap] PRIMARY KEY CLUSTERED 
(
	[MapNo] ASC, [f_NationCodeStr] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]



EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Map(=World)  definition' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefMap'


ALTER TABLE [dbo].[TB_DefMap] ADD  CONSTRAINT [DF_TB_DefMap_Hidden_Index]  DEFAULT ((0)) FOR [Hidden_Index]


ALTER TABLE [dbo].[TB_DefMap] ADD  CONSTRAINT [DF_TB_DefMap_Abil01]  DEFAULT ((0)) FOR [Abil01]


ALTER TABLE [dbo].[TB_DefMap] ADD  CONSTRAINT [DF_TB_DefMap_Abil02]  DEFAULT ((0)) FOR [Abil02]


ALTER TABLE [dbo].[TB_DefMap] ADD  CONSTRAINT [DF_TB_DefMap_Abil03]  DEFAULT ((0)) FOR [Abil03]


ALTER TABLE [dbo].[TB_DefMap] ADD  CONSTRAINT [DF_TB_DefMap_Abil04]  DEFAULT ((0)) FOR [Abil04]


ALTER TABLE [dbo].[TB_DefMap] ADD  CONSTRAINT [DF_TB_DefMap_Abil05]  DEFAULT ((0)) FOR [Abil05]


ALTER TABLE [dbo].[TB_DefMap] ADD  CONSTRAINT [DF_TB_DefMap_Recommend_Level]  DEFAULT ((0)) FOR [Recommend_Level]


ALTER TABLE [dbo].[TB_DefMap] ADD  CONSTRAINT [DF_TB_DefMap_Recommend_Party]  DEFAULT ((0)) FOR [Recommend_Party]


ALTER TABLE [dbo].[TB_DefMap] ADD  CONSTRAINT [DF_TB_DefMap_Group_TXT]  DEFAULT ((0)) FOR [Group_TXT]


ALTER TABLE [dbo].[TB_DefMap] ADD  CONSTRAINT [DF_TB_DefMap_LevelLimit_Min]  DEFAULT ((0)) FOR [LevelLimit_Min]


ALTER TABLE [dbo].[TB_DefMap] ADD  CONSTRAINT [DF_TB_DefMap_LevelLimit_Max]  DEFAULT ((0)) FOR [LevelLimit_Max]


ALTER TABLE [dbo].[TB_DefMap] ADD  CONSTRAINT [DF_TB_DefMap_DESCRIPTION_TEXT]  DEFAULT ((0)) FOR [DESCRIPTION_TEXT]


ALTER TABLE [dbo].[TB_DefMap] ADD  CONSTRAINT [DF_TB_DefMap_PartyBreakIn]  DEFAULT ((0)) FOR [PartyBreakIn]



INSERT INTO [TB_DefMap]
           ([MapNo]   ,[f_NationCodeStr]      ,[MapKey]           ,[Attribute]           ,[Memo]
           ,[NameNo]           ,[XmlPath]           ,[ZoneCX]           ,[ZoneCY]
           ,[ZoneCZ]           ,[Continent]           ,[HometownNo]           ,[Hidden_Index]
           ,[Abil01]           ,[Abil02]           ,[Abil03]           ,[Abil04]
           ,[Abil05]           ,[Recommend_Level]           ,[Recommend_Party]           ,[Group_TXT]
           ,[LevelLimit_Min]           ,[LevelLimit_Max]           ,[DESCRIPTION_TEXT]
           ,[PartyBreakIn])
		SELECT   [MapNo]	,'0',	  [MapKey]			  ,[Attribute]			  ,[Memo]
			  ,[NameNo]			  ,[XmlPath]			  ,[ZoneCX]			  ,[ZoneCY]			  ,[ZoneCZ]
			  ,[Continent]			  ,[HometownNo]			  ,[Hidden_Index]			  ,[Abil01]
			  ,[Abil02]			  ,[Abil03]			  ,[Abil04]			  ,[Abil05]			  ,[Recommend_Level]
			  ,[Recommend_Party]			  ,[Group_TXT]			  ,[LevelLimit_Min]
			  ,[LevelLimit_Max]			  ,[DESCRIPTION_TEXT]			  ,[PartyBreakIn]
		FROM  #temp




DROP TABLE #TEMP



END --end if

IF not  EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='TB_DefMap' AND COLUMN_NAME='PartyBreakIn_Item') BEGIN
ALTER TABLE [dbo].[TB_DefMap] ADD
	[PartyBreakIn_Item] nvarchar(100) NOT NULL DEFAULT ((0))
END

IF not  EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='TB_DefMap' AND COLUMN_NAME='PartyBreakIn_CashItem') BEGIN
ALTER TABLE [dbo].[TB_DefMap] ADD
	[PartyBreakIn_CashItem] nvarchar(100) NOT NULL DEFAULT ((0))
END