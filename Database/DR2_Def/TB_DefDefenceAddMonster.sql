

USE [DR2_Def]
go
IF not  EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='TB_DefDefenceAddMonster' AND COLUMN_NAME='ItemCount')
BEGIN

CREATE TABLE #temp(
	[f_NationCodeStr] [nvarchar](50) NOT NULL,
	[AddMonster_GroupNo] [int] NOT NULL,
	[Success_Count] [int] NOT NULL,
	[Memo] [nvarchar](100) NULL,
	[Add_StageTime] [int] NOT NULL,
	[MonsterNo] [int] NOT NULL,
	[Enchant_Probability] [int] NOT NULL,
	[ExpRate] [int] NOT NULL,
	[ItemNo] [int] NOT NULL,
	[ItemCount] [int] NOT NULL default 0,
	[DropRate] [int] NOT NULL,
	[MonRes] [nvarchar](100) NULL
	)
 
	INSERT INTO #temp
           ([f_NationCodeStr]
           ,[AddMonster_GroupNo]
           ,[Success_Count]
           ,[Memo]
           ,[Add_StageTime]
           ,[MonsterNo]
           ,[Enchant_Probability]
           ,[ExpRate]
           ,[ItemNo]
           ,[ItemCount]
           ,[DropRate]
           ,[MonRes])
     SELECT [f_NationCodeStr]
      ,[AddMonster_GroupNo]
      ,[Success_Count]
      ,[Memo]
      ,[Add_StageTime]
      ,[MonsterNo]
      ,[Enchant_Probability]
      ,[ExpRate]
      ,[ItemNo]
      , 0
      ,[DropRate]
      ,[MonRes]
  FROM  [TB_DefDefenceAddMonster]
 






IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_DefDefenceAddMonster_f_NationCodeStr]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefDefenceAddMonster] DROP CONSTRAINT [DF_DefDefenceAddMonster_f_NationCodeStr]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_DefDefenceAddMonster_Add_StageTime]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefDefenceAddMonster] DROP CONSTRAINT [DF_DefDefenceAddMonster_Add_StageTime]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_DefDefenceAddMonster_MonsterNo]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefDefenceAddMonster] DROP CONSTRAINT [DF_DefDefenceAddMonster_MonsterNo]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_DefDefenceAddMonster_Enchant_Probability]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefDefenceAddMonster] DROP CONSTRAINT [DF_DefDefenceAddMonster_Enchant_Probability]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_DefDefenceAddMonster_ExpRate]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefDefenceAddMonster] DROP CONSTRAINT [DF_DefDefenceAddMonster_ExpRate]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_DefDefenceAddMonster_ItemNo]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefDefenceAddMonster] DROP CONSTRAINT [DF_DefDefenceAddMonster_ItemNo]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_DefDefenceAddMonster_DropRate]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefDefenceAddMonster] DROP CONSTRAINT [DF_DefDefenceAddMonster_DropRate]
END

 

/****** Object:  Table [dbo].[TB_DefDefenceAddMonster]    Script Date: 11/20/2012 11:15:14 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefDefenceAddMonster]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DefDefenceAddMonster]

 


/****** Object:  Table [dbo].[TB_DefDefenceAddMonster]    Script Date: 11/20/2012 11:15:14 ******/
SET ANSI_NULLS ON


SET QUOTED_IDENTIFIER ON


CREATE TABLE [dbo].[TB_DefDefenceAddMonster](
	[f_NationCodeStr] [nvarchar](50) NOT NULL,
	[AddMonster_GroupNo] [int] NOT NULL,
	[Success_Count] [int] NOT NULL,
	[Memo] [nvarchar](100) NULL,
	[Add_StageTime] [int] NOT NULL,
	[MonsterNo] [int] NOT NULL,
	[Enchant_Probability] [int] NOT NULL,
	[ExpRate] [int] NOT NULL,
	[ItemNo] [int] NOT NULL,
	[ItemCount] [int] NOT NULL default 0,
	[DropRate] [int] NOT NULL,
	[MonRes] [nvarchar](100) NULL,
 CONSTRAINT [PK_TB_DefDefenceAddMonster] PRIMARY KEY CLUSTERED 
(
	[f_NationCodeStr] ASC,
	[AddMonster_GroupNo] ASC,
	[Success_Count] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]



EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'디팬스 모드에서 나오는 몬스터들을 설정하는 테이블' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefDefenceAddMonster'


ALTER TABLE [dbo].[TB_DefDefenceAddMonster] ADD  CONSTRAINT [DF_DefDefenceAddMonster_f_NationCodeStr]  DEFAULT ((0)) FOR [f_NationCodeStr]


ALTER TABLE [dbo].[TB_DefDefenceAddMonster] ADD  CONSTRAINT [DF_DefDefenceAddMonster_Add_StageTime]  DEFAULT ((0)) FOR [Add_StageTime]


ALTER TABLE [dbo].[TB_DefDefenceAddMonster] ADD  CONSTRAINT [DF_DefDefenceAddMonster_MonsterNo]  DEFAULT ((0)) FOR [MonsterNo]


ALTER TABLE [dbo].[TB_DefDefenceAddMonster] ADD  CONSTRAINT [DF_DefDefenceAddMonster_Enchant_Probability]  DEFAULT ((0)) FOR [Enchant_Probability]


ALTER TABLE [dbo].[TB_DefDefenceAddMonster] ADD  CONSTRAINT [DF_DefDefenceAddMonster_ExpRate]  DEFAULT ((0)) FOR [ExpRate]


ALTER TABLE [dbo].[TB_DefDefenceAddMonster] ADD  CONSTRAINT [DF_DefDefenceAddMonster_ItemNo]  DEFAULT ((0)) FOR [ItemNo]


ALTER TABLE [dbo].[TB_DefDefenceAddMonster] ADD  CONSTRAINT [DF_DefDefenceAddMonster_DropRate]  DEFAULT ((0)) FOR [DropRate]



	INSERT INTO [TB_DefDefenceAddMonster]
           ([f_NationCodeStr]
           ,[AddMonster_GroupNo]
           ,[Success_Count]
           ,[Memo]
           ,[Add_StageTime]
           ,[MonsterNo]
           ,[Enchant_Probability]
           ,[ExpRate]
           ,[ItemNo]
           ,[ItemCount]
           ,[DropRate]
           ,[MonRes])
     SELECT [f_NationCodeStr]
      ,[AddMonster_GroupNo]
      ,[Success_Count]
      ,[Memo]
      ,[Add_StageTime]
      ,[MonsterNo]
      ,[Enchant_Probability]
      ,[ExpRate]
      ,[ItemNo]
      ,[ItemCount]
      ,[DropRate]
      ,[MonRes]
  FROM  #temp
 
 drop table #temp
 END
 