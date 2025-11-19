USE [DR2_Local]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefPvPTime]') AND type in (N'U'))
BEGIN

	CREATE TABLE [dbo].[TB_DefPvPTime](
		[TypeID] [INT]
	,	[Memo] [NVARCHAR](100)
	,	[BeginTime_Hour] [TINYINT]
	,	[BeginTime_Minute] [TINYINT]
	,	[EndTime_Hour] [TINYINT]
	,	[EndTime_Minute] [TINYINT]
	,	[LevelLimit] [SMALLINT] NULL
	,	[iValue01] [INT] NULL
	,	[iValue02] [INT] NULL
	,	[iBalanceLevelMin] [INT] NOT NULL CONSTRAINT [TB_DefPvPTime_BalanceLevelMin] DEFAULT ((1))
	,	[iBalanceLevelMax] [INT] NOT NULL CONSTRAINT [TB_DefPvPTime_BalanceLevelMax] DEFAULT ((1))
	) ON [PRIMARY]
	
	CREATE INDEX [IX_TB_DefPvPTime] ON [dbo].[TB_DefPvPTime]([TypeID] ASC)
END
GO

IF NOT EXISTS(SELECT * FROM SYS.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefPvPTime') and [name] = N'f_NationCodeStr')
BEGIN
	ALTER TABLE dbo.TB_DefPvPTime
		DROP CONSTRAINT TB_DefPvPTime_BalanceLevelMin

	ALTER TABLE dbo.TB_DefPvPTime
		DROP CONSTRAINT TB_DefPvPTime_BalanceLevelMax

	CREATE TABLE dbo.Tmp_TB_DefPvPTime
		(
		f_NationCodeStr nvarchar(50) NOT NULL,
		TypeID int NOT NULL,
		Memo nvarchar(100) NULL,
		BeginTime_Hour tinyint NULL,
		BeginTime_Minute tinyint NULL,
		EndTime_Hour tinyint NULL,
		EndTime_Minute tinyint NULL,
		LevelLimit smallint NULL,
		iValue01 int NULL,
		iValue02 int NULL,
		iBalanceLevelMin int NOT NULL,
		iBalanceLevelMax int NOT NULL
		)  ON [PRIMARY]

	IF NOT EXISTS (SELECT * FROM sys.extended_properties WHERE major_id = OBJECT_ID(N'dbo.TB_DefPvPTime') and [name] = N'MS_Description')
	BEGIN
		EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'PvP 오픈 시간을 설정 : 멀티로 등록가능
	 - TypeID( 2=연습모드, 3=랭킹모드, 5=하드코어던젼 )
	 - LevelLimit : 최소 입장 레벨 설정
	 - iValue01, iValue02 : 하드코어 던젼에서만 사용(맵번호, 보스맵번호)
	 - iBalanceLevelMin, iBalanceLevelMax : 랭킹모드에서만 사용 ( 방 생성자 레벨 기준으로 입장 가능한 최소/최대 레벨 )' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefPvPTime'
	END
	ELSE
	BEGIN
		EXEC sys.sp_updateextendedproperty @name=N'MS_Description', @value=N'PvP 오픈 시간을 설정 : 멀티로 등록가능
	 - TypeID( 2=연습모드, 3=랭킹모드, 5=하드코어던젼 )
	 - LevelLimit : 최소 입장 레벨 설정
	 - iValue01, iValue02 : 하드코어 던젼에서만 사용(맵번호, 보스맵번호)
	 - iBalanceLevelMin, iBalanceLevelMax : 랭킹모드에서만 사용 ( 방 생성자 레벨 기준으로 입장 가능한 최소/최대 레벨 )' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefPvPTime'
	END

	ALTER TABLE dbo.Tmp_TB_DefPvPTime ADD CONSTRAINT
		TB_DefPvPTime_BalanceLevelMin DEFAULT ((1)) FOR iBalanceLevelMin

	ALTER TABLE dbo.Tmp_TB_DefPvPTime ADD CONSTRAINT
		TB_DefPvPTime_BalanceLevelMax DEFAULT ((1)) FOR iBalanceLevelMax

	IF EXISTS(SELECT * FROM dbo.TB_DefPvPTime)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefPvPTime (f_NationCodeStr, TypeID, Memo, BeginTime_Hour, BeginTime_Minute, EndTime_Hour, EndTime_Minute, LevelLimit, iValue01, iValue02, iBalanceLevelMin, iBalanceLevelMax)
			SELECT 0, TypeID, Memo, BeginTime_Hour, BeginTime_Minute, EndTime_Hour, EndTime_Minute, LevelLimit, iValue01, iValue02, iBalanceLevelMin, iBalanceLevelMax FROM dbo.TB_DefPvPTime WITH (HOLDLOCK TABLOCKX)')

	DROP TABLE dbo.TB_DefPvPTime

	EXECUTE sp_rename N'dbo.Tmp_TB_DefPvPTime', N'TB_DefPvPTime', 'OBJECT' 

	CREATE NONCLUSTERED INDEX IX_TB_DefPvPTime ON dbo.TB_DefPvPTime
		(
		TypeID
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END
GO