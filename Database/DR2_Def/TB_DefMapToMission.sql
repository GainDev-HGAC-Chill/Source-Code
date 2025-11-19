USE [DR2_Def]
GO

IF NOT EXISTS(SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'dbo.TB_DefMapToMission') AND [name] = N'PK_TB_DefMapToMission')
BEGIN

	ALTER TABLE dbo.TB_DefMapToMission ADD CONSTRAINT
		PK_TB_DefMapToMission PRIMARY KEY CLUSTERED 
		(
		MapNo,
		MissionNo
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefMapToMission]') AND [Name] = 'ConnetedMapNo01')
BEGIN
	ALTER TABLE [dbo].[TB_DefMapToMission] ADD ConnetedMapNo01 [int] NOT NULL CONSTRAINT [DF_TB_DefMapToMission_ConnetedMapNo01] DEFAULT (0)
	ALTER TABLE [dbo].[TB_DefMapToMission] ADD ConnetedMapNo02 [int] NOT NULL CONSTRAINT [DF_TB_DefMapToMission_ConnetedMapNo02] DEFAULT (0)
	ALTER TABLE [dbo].[TB_DefMapToMission] ADD ConnetedMapNo03 [int] NOT NULL CONSTRAINT [DF_TB_DefMapToMission_ConnetedMapNo03] DEFAULT (0)
	ALTER TABLE [dbo].[TB_DefMapToMission] ADD ConnetedMapNo04 [int] NOT NULL CONSTRAINT [DF_TB_DefMapToMission_ConnetedMapNo04] DEFAULT (0)
	ALTER TABLE [dbo].[TB_DefMapToMission] ADD ConnetedMapNo05 [int] NOT NULL CONSTRAINT [DF_TB_DefMapToMission_ConnetedMapNo05] DEFAULT (0)
END