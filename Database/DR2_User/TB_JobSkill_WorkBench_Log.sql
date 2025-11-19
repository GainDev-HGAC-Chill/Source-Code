USE [DR2_User]
GO

/****** Object:  Table [dbo].[TB_JobSkill_WorkBench_Log]    Script Date: 10/19/2010 00:55:51 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_JobSkill_WorkBench_Log]') AND [type] IN (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_JobSkill_WorkBench_Log](
		[f_DateTime] [datetime] NOT NULL,
		[f_ItemGuid] [uniqueidentifier] NOT NULL,
		[f_EventType] [tinyint] NOT NULL,
		[f_Data] [binary](50) NOT NULL,
		[f_WhoName] [nvarchar](20) NOT NULL
	) ON [PRIMARY]

	CREATE CLUSTERED INDEX [IX_TB_JobSkill_WorkBench_Log_f_DateTime] ON [dbo].[TB_JobSkill_WorkBench_Log] ([f_ItemGuid], [f_DateTime] ASC)	
	CREATE NONCLUSTERED INDEX [IX_TB_JobSkill_WorkBench_Log_f_ItemGuid] ON [dbo].[TB_JobSkill_WorkBench_Log] ([f_ItemGuid] ASC)
END