USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF not  EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='TB_DefMapAbil' AND COLUMN_NAME='f_NationCodeStr')BEGIN

CREATE TABLE #temp(
	[AbilNo] [int] NOT NULL,
	[Memo] [nvarchar](100) NULL,
	[Type01] [int] NOT NULL,
	[Value01] [int] NOT NULL,
	[Type02] [int] NOT NULL,
	[Value02] [int] NOT NULL,
	[Type03] [int] NOT NULL,
	[Value03] [int] NOT NULL,
	[Type04] [int] NOT NULL,
	[Value04] [int] NOT NULL,
	[Type05] [int] NOT NULL,
	[Value05] [int] NOT NULL,
	[Type06] [int] NOT NULL,
	[Value06] [int] NOT NULL,
	[Type07] [int] NOT NULL,
	[Value07] [int] NOT NULL,
	[Type08] [int] NOT NULL,
	[Value08] [int] NOT NULL,
	[Type09] [int] NOT NULL,
	[Value09] [int] NOT NULL,
	[Type10] [int] NOT NULL,
	[Value10] [int] NOT NULL,
	)
	
	INSERT INTO #temp
           ([AbilNo]           ,[Memo]           ,[Type01]           ,[Value01]
           ,[Type02]           ,[Value02]           ,[Type03]           ,[Value03]
           ,[Type04]           ,[Value04]           ,[Type05]           ,[Value05]
           ,[Type06]           ,[Value06]           ,[Type07]           ,[Value07]
           ,[Type08]           ,[Value08]           ,[Type09]           ,[Value09]
           ,[Type10]           ,[Value10])
           
    SELECT [AbilNo]      ,[Memo]      ,[Type01]      ,[Value01]
      ,[Type02]      ,[Value02]      ,[Type03]      ,[Value03]
      ,[Type04]      ,[Value04]      ,[Type05]      ,[Value05]
      ,[Type06]      ,[Value06]      ,[Type07]      ,[Value07]
      ,[Type08]      ,[Value08]      ,[Type09]      ,[Value09]
      ,[Type10]      ,[Value10]
      
  FROM [TB_DefMapAbil]


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapAbil_Type01]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_TB_DefMapAbil_Type01]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapAbil_Value01]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_TB_DefMapAbil_Value01]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_Table_1_Type011]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_Table_1_Type011]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_Table_1_Value011]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_Table_1_Value011]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_Table_1_Type011_1]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_Table_1_Type011_1]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_Table_1_Value011_1]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_Table_1_Value011_1]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_Table_1_Type011_2]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_Table_1_Type011_2]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_Table_1_Value011_2]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_Table_1_Value011_2]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_Table_1_Type011_3]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_Table_1_Type011_3]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_Table_1_Value011_3]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_Table_1_Value011_3]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_Table_1_Type051]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_Table_1_Type051]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_Table_1_Value051]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_Table_1_Value051]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_Table_1_Type051_1]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_Table_1_Type051_1]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_Table_1_Value051_1]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_Table_1_Value051_1]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_Table_1_Type051_2]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_Table_1_Type051_2]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_Table_1_Value051_2]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_Table_1_Value051_2]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_Table_1_Type051_3]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_Table_1_Type051_3]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_Table_1_Value051_3]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_Table_1_Value051_3]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_Table_1_Type051_4]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_Table_1_Type051_4]
END



IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_Table_1_Value051_4]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapAbil] DROP CONSTRAINT [DF_Table_1_Value051_4]
END



/****** Object:  Table [dbo].[TB_DefMapAbil]    Script Date: 01/07/2013 16:42:02 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefMapAbil]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DefMapAbil]

CREATE TABLE [dbo].[TB_DefMapAbil](
	[f_NationCodeStr] [nvarchar](50)  DEFAULT '0',
	[AbilNo] [int] NOT NULL,
	[Memo] [nvarchar](100) NULL,
	[Type01] [int] NOT NULL,
	[Value01] [int] NOT NULL,
	[Type02] [int] NOT NULL,
	[Value02] [int] NOT NULL,
	[Type03] [int] NOT NULL,
	[Value03] [int] NOT NULL,
	[Type04] [int] NOT NULL,
	[Value04] [int] NOT NULL,
	[Type05] [int] NOT NULL,
	[Value05] [int] NOT NULL,
	[Type06] [int] NOT NULL,
	[Value06] [int] NOT NULL,
	[Type07] [int] NOT NULL,
	[Value07] [int] NOT NULL,
	[Type08] [int] NOT NULL,
	[Value08] [int] NOT NULL,
	[Type09] [int] NOT NULL,
	[Value09] [int] NOT NULL,
	[Type10] [int] NOT NULL,
	[Value10] [int] NOT NULL,
 CONSTRAINT [PK_TB_DefMapAbil] PRIMARY KEY CLUSTERED 
(
	[AbilNo] ASC,[f_NationCodeStr] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]



EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'맵의 능력치 설정 (휴식 경험치 받을 수 있는 맵등을 정의)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefMapAbil'


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_TB_DefMapAbil_Type01]  DEFAULT ((0)) FOR [Type01]


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_TB_DefMapAbil_Value01]  DEFAULT ((0)) FOR [Value01]


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_Table_1_Type011]  DEFAULT ((0)) FOR [Type02]


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_Table_1_Value011]  DEFAULT ((0)) FOR [Value02]


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_Table_1_Type011_1]  DEFAULT ((0)) FOR [Type03]


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_Table_1_Value011_1]  DEFAULT ((0)) FOR [Value03]


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_Table_1_Type011_2]  DEFAULT ((0)) FOR [Type04]


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_Table_1_Value011_2]  DEFAULT ((0)) FOR [Value04]


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_Table_1_Type011_3]  DEFAULT ((0)) FOR [Type05]


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_Table_1_Value011_3]  DEFAULT ((0)) FOR [Value05]


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_Table_1_Type051]  DEFAULT ((0)) FOR [Type06]


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_Table_1_Value051]  DEFAULT ((0)) FOR [Value06]


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_Table_1_Type051_1]  DEFAULT ((0)) FOR [Type07]


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_Table_1_Value051_1]  DEFAULT ((0)) FOR [Value07]


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_Table_1_Type051_2]  DEFAULT ((0)) FOR [Type08]


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_Table_1_Value051_2]  DEFAULT ((0)) FOR [Value08]


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_Table_1_Type051_3]  DEFAULT ((0)) FOR [Type09]


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_Table_1_Value051_3]  DEFAULT ((0)) FOR [Value09]

ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_Table_1_Type051_4]  DEFAULT ((0)) FOR [Type10]


ALTER TABLE [dbo].[TB_DefMapAbil] ADD  CONSTRAINT [DF_Table_1_Value051_4]  DEFAULT ((0)) FOR [Value10]

INSERT INTO [TB_DefMapAbil]
           ([f_NationCodeStr] ,[AbilNo]           ,[Memo]           ,[Type01]
           ,[Value01]           ,[Type02]           ,[Value02]           ,[Type03]
           ,[Value03]           ,[Type04]           ,[Value04]           ,[Type05]
           ,[Value05]           ,[Type06]           ,[Value06]           ,[Type07]
           ,[Value07]           ,[Type08]           ,[Value08]           ,[Type09]
           ,[Value09]           ,[Type10]           ,[Value10])
    
SELECT '0', [AbilNo]      ,[Memo]      ,[Type01]      ,[Value01]
      ,[Type02]      ,[Value02]      ,[Type03]      ,[Value03]
      ,[Type04]      ,[Value04]      ,[Type05]      ,[Value05]
      ,[Type06]      ,[Value06]      ,[Type07]      ,[Value07]
      ,[Type08]      ,[Value08]      ,[Type09]      ,[Value09]
      ,[Type10]      ,[Value10]
  FROM #temp 

DROP TABLE #TEMP

END --end if






