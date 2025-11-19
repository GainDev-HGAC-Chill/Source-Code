USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF not EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='TB_DefMapEffect' AND COLUMN_NAME='f_NationCodeStr')BEGIN

CREATE TABLE #temp(
	[EffectID] [int] NOT NULL,
	[GroundNo] [int] NOT NULL,
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
	[Type101] [int] NOT NULL,
	[Value101] [bigint] NOT NULL,
	)
	INSERT INTO #temp 
			   ([EffectID]           ,[GroundNo]           ,[Memo]
			   ,[Type01]           ,[Value01]           ,[Type02]           ,[Value02]
			   ,[Type03]           ,[Value03]           ,[Type04]           ,[Value04]
			   ,[Type05]           ,[Value05]          ,[Type06]           ,[Value06]
			   ,[Type07]           ,[Value07]           ,[Type08]           ,[Value08]
			   ,[Type09]           ,[Value09]           ,[Type10]           ,[Value10]
			   ,[Type101]           ,[Value101])

	SELECT [EffectID]      ,[GroundNo]      ,[Memo]      ,[Type01]
      ,[Value01]      ,[Type02]      ,[Value02]      ,[Type03]
      ,[Value03]      ,[Type04]      ,[Value04]      ,[Type05]
      ,[Value05]      ,[Type06]      ,[Value06]      ,[Type07]
      ,[Value07]      ,[Type08]      ,[Value08]      ,[Type09]
      ,[Value09]      ,[Type10]      ,[Value10]      ,[Type101]
      ,[Value101]
  FROM [TB_DefMapEffect]

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Type01]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Type01]
END

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Value01]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Value01]
END

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Type02]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Type02]
END

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Value02]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Value02]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Type03]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Type03]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Value03]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Value03]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Type04]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Type04]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Value04]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Value04]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Type05]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Type05]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Value05]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Value05]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Type06]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Type06]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Value06]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Value06]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Type07]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Type07]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Value07]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Value07]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Type08]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Type08]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Value08]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Value08]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Type09]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Type09]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Value09]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Value09]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Type10]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Type10]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Value10]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Value10]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Type101]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Type101]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefMapEffect_Value101]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefMapEffect] DROP CONSTRAINT [DF_TB_DefMapEffect_Value101]
END

/****** Object:  Table [dbo].[TB_DefMapEffect]    Script Date: 01/07/2013 22:27:50 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefMapEffect]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DefMapEffect]

CREATE TABLE [dbo].[TB_DefMapEffect](
	[Idx] [int] IDENTITY(1,1) NOT NULL,
	[f_NationCodeStr] [nvarchar](50)  DEFAULT '0',
	[EffectID] [int] NOT NULL,
	[GroundNo] [int] NOT NULL,
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
	[Type101] [int] NOT NULL,
	[Value101] [bigint] NOT NULL,
 CONSTRAINT [PK_TB_DefMapEffect] PRIMARY KEY CLUSTERED 
(
	[Idx] ASC,
	[f_NationCodeStr] ASC,
	[EffectID] ASC,
	[GroundNo] ASC
	
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Map effect (buf/debuf) definition
detail :
some maps have a special effect  like poison in its world' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefMapEffect'

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Type01]  DEFAULT ((0)) FOR [Type01]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Value01]  DEFAULT ((0)) FOR [Value01]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Type02]  DEFAULT ((0)) FOR [Type02]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Value02]  DEFAULT ((0)) FOR [Value02]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Type03]  DEFAULT ((0)) FOR [Type03]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Value03]  DEFAULT ((0)) FOR [Value03]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Type04]  DEFAULT ((0)) FOR [Type04]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Value04]  DEFAULT ((0)) FOR [Value04]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Type05]  DEFAULT ((0)) FOR [Type05]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Value05]  DEFAULT ((0)) FOR [Value05]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Type06]  DEFAULT ((0)) FOR [Type06]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Value06]  DEFAULT ((0)) FOR [Value06]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Type07]  DEFAULT ((0)) FOR [Type07]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Value07]  DEFAULT ((0)) FOR [Value07]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Type08]  DEFAULT ((0)) FOR [Type08]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Value08]  DEFAULT ((0)) FOR [Value08]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Type09]  DEFAULT ((0)) FOR [Type09]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Value09]  DEFAULT ((0)) FOR [Value09]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Type10]  DEFAULT ((0)) FOR [Type10]

ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Value10]  DEFAULT ((0)) FOR [Value10]


ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Type101]  DEFAULT ((0)) FOR [Type101]


ALTER TABLE [dbo].[TB_DefMapEffect] ADD  CONSTRAINT [DF_TB_DefMapEffect_Value101]  DEFAULT ((0)) FOR [Value101]

INSERT INTO [TB_DefMapEffect]
           ([f_NationCodeStr]          ,[EffectID]           ,[GroundNo]           ,[Memo]
           ,[Type01]           ,[Value01]           ,[Type02]           ,[Value02]
           ,[Type03]           ,[Value03]           ,[Type04]           ,[Value04]
           ,[Type05]           ,[Value05]           ,[Type06]           ,[Value06]
           ,[Type07]           ,[Value07]           ,[Type08]           ,[Value08]
           ,[Type09]           ,[Value09]           ,[Type10]           ,[Value10]
           ,[Type101]           ,[Value101])
   SELECT '0'     ,[EffectID]   ,[GroundNo]      ,[Memo]      ,[Type01]
      ,[Value01]      ,[Type02]      ,[Value02]      ,[Type03]      ,[Value03]      ,[Type04]
      ,[Value04]      ,[Type05]      ,[Value05]      ,[Type06]      ,[Value06]      ,[Type07]
      ,[Value07]      ,[Type08]      ,[Value08]      ,[Type09]      ,[Value09]      ,[Type10]
      ,[Value10]      ,[Type101]      ,[Value101]
  FROM #temp
DROP TABLE #temp

END