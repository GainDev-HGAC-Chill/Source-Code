USE DR2_SiteConfig
-- Action plan:
-- 0. Drop Constraint [PK_TB_MapCfg_Static], [DF_TB_MapCfg_Static_ServerNo]
-- 1. Create table [dbo].[TB_MapCfg_Public_tmp]
-- 2. INSERT [ServerNo], [GroundNo] INTO [TB_MapCfg_Public_tmp] FROM [TB_MapCfg_Public]
-- 3. Creating extended properties
-- 4. Update [TB_MapCfg_Public_tmp] Set Memo Column
-- 5. Drop Table [TB_MapCfg_Public]
-- 6. Create primary key [PK_TB_MapCfg_Public] on [dbo].[TB_MapCfg_Public_tmp]
-- 7. Rename Table [TB_MapCfg_Public_tmp] -> [TB_MapCfg_Public]
--
-- No warnings
SET NUMERIC_ROUNDABORT OFF
GO
SET ANSI_PADDING, ANSI_WARNINGS, CONCAT_NULL_YIELDS_NULL, ARITHABORT, QUOTED_IDENTIFIER, ANSI_NULLS ON
GO


IF EXISTS (SELECT * FROM tempdb..sysobjects WHERE id=OBJECT_ID('tempdb..#tmpErrors')) DROP TABLE #tmpErrors
GO
CREATE TABLE #tmpErrors (Error int)
GO
SET XACT_ABORT ON
GO
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE
GO
BEGIN TRANSACTION
GO

-- Drop Constraint [TB_MapCfg_Mission], PK_TB_MapCfg_Mission
PRINT N'Drop Constraint [TB_MapCfg_Mission], PK_TB_MapCfg_Mission, DF_TB_MapCfg_Mission_ServerNo'
GO
ALTER TABLE [dbo].[TB_MapCfg_Mission]
DROP CONSTRAINT PK_TB_MapCfg_Mission, DF_TB_MapCfg_Mission_ServerNo
GO
IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO

-- TB_MapCfg_Mission_tmp 테이블 생성
PRINT N'Creating [dbo].[TB_MapCfg_Mission_tmp]'
GO

CREATE TABLE [dbo].[TB_MapCfg_Mission_tmp]
(
	[IDX] [smallint] IDENTITY(1,1) NOT NULL,
	[RealmNo] [smallint] NOT NULL CONSTRAINT [DF_TB_MapCfg_Mission_RealmNo]  DEFAULT ((1)),
	[ChannelNo] [smallint] NOT NULL CONSTRAINT [DF_TB_MapCfg_Mission_ChannelNo]  DEFAULT ((0)),
	[ServerNo] [smallint] NOT NULL CONSTRAINT [DF_TB_MapCfg_Mission_ServerNo]  DEFAULT ((0)),
	[MissionNo] [int] NOT NULL,
	[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL
) ON [PRIMARY]
GO

IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO


-- TB_MapCfg_Mission_tmp 테이블에 원본(TB_MapCfg_Mission)데이터 복사
PRINT N'INSERT INTO [dbo].[TB_MapCfg_Mission_tmp] FROM [dbo].[TB_MapCfg_Mission]'
GO
INSERT INTO [dbo].[TB_MapCfg_Mission_tmp]([ServerNo], [MissionNo])
SELECT DISTINCT [ServerNo], [MissionNo]
FROM [dbo].[TB_MapCfg_Mission]
GO

IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO



PRINT N'Creating extended properties'
GO
EXEC sp_addextendedproperty N'MS_Description', N'Mission Map configuration', 'SCHEMA', N'dbo', 'TABLE', N'TB_MapCfg_Mission_tmp', NULL, NULL
GO
IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO


EXEC sp_addextendedproperty N'MS_Description', N'Mission number (not map number)
same value with MissionNo in DR2_Def.dbo.[TB_Mission_LevelRoot]', 'SCHEMA', N'dbo', 'TABLE', N'TB_MapCfg_Mission_tmp', 'COLUMN', N'MissionNo'
GO
IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO


EXEC sp_addextendedproperty N'MS_Description', N'server number', 'SCHEMA', N'dbo', 'TABLE', N'TB_MapCfg_Mission_tmp', 'COLUMN', N'ServerNo'
GO
IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO



-- Memo 업데이트
PRINT N'Drop Table [TB_MapCfg_Mission]'
GO
UPDATE A
SET A.[Memo] = B.Memo
FROM [DBO].[TB_MapCfg_Mission_tmp] AS A
JOIN [DBO].[TB_MapCfg_Mission] AS B ON A.MissionNo = B.MissionNo

IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO

UPDATE [dbo].[TB_MapCfg_Mission_tmp]
   SET [RealmNo] = 1
      ,[ChannelNo] = 1
IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO



-- [TB_MapCfg_Mission] 테이블 삭제
PRINT N'Drop Table [TB_MapCfg_Mission]'
GO
DROP TABLE dbo.TB_MapCfg_Mission
GO
IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO


-- Primary Key 생성
PRINT N'Creating primary key [PK_TB_MapCfg_Mission] on [TB_MapCfg_Mission_tmp]'
GO
ALTER TABLE [dbo].[TB_MapCfg_Mission_tmp] 
ADD CONSTRAINT [PK_TB_MapCfg_Mission] 
PRIMARY KEY CLUSTERED ([RealmNo], [ChannelNo], [ServerNo], [MissionNo]) ON [PRIMARY]
GO

IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO



-- [TB_MapCfg_Mission_tmp]테이블 이름 변경
PRINT N'Rename Table [TB_MapCfg_Mission_tmp] -> [TB_MapCfg_Mission]'
GO
EXECUTE sp_rename N'dbo.TB_MapCfg_Mission_tmp', N'TB_MapCfg_Mission', 'OBJECT' 
GO
IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO



IF EXISTS (SELECT * FROM #tmpErrors) ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT>0 BEGIN
	PRINT 'The database update succeeded'
	COMMIT TRANSACTION
	END
ELSE PRINT 'The database update failed'
	GO
	DROP TABLE #tmpErrors
	GO