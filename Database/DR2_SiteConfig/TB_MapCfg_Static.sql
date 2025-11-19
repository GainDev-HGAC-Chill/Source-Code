USE DR2_SiteConfig
GO
-- Action plan:
-- 0. Drop Constraint [PK_TB_MapCfg_Static], [DF_TB_MapCfg_Static_ServerNo]
-- 1. Create table [dbo].[TB_MapCfg_Static_tmp]
-- 2. INSERT [ServerNo], [GroundNo] INTO [TB_MapCfg_Static_tmp] FROM [TB_MapCfg_Static]
-- 3. Creating extended properties
-- 4. Update [TB_MapCfg_Static_Tmp] Set Memo Column
-- 5. Drop Table [TB_MapCfg_static]
-- 6. Create primary key [PK_TB_MapCfg_Static] on [dbo].[TB_MapCfg_Static_tmp]
-- 7. Rename Table [TB_MapCfg_Static_Tmp] -> [TB_MapCfg_Static]
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


-- Drop Constraint [PK_TB_MapCfg_Static], [DF_TB_MapCfg_Static_ServerNo]
PRINT N'Drop Constraint [PK_TB_MapCfg_Static], [DF_TB_MapCfg_Static_ServerNo]'
GO
ALTER TABLE [dbo].[TB_MapCfg_Static]
DROP CONSTRAINT PK_TB_MapCfg_Static, 
DF_TB_MapCfg_Static_ServerNo
GO
IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO

-- [TB_MapCfg_Static_tmp] 테이블 생성
PRINT N'CREATE TABLE [TB_MapCfg_Static_tmp]'
GO
CREATE TABLE [dbo].[TB_MapCfg_Static_tmp]
(
	[IDX] [smallint] IDENTITY(1,1) NOT NULL,
	[RealmNo] [smallint] NOT NULL CONSTRAINT [DF_TB_MapCfg_Static_RealmNo]  DEFAULT ((1)),
	[ChannelNo] [smallint] NOT NULL CONSTRAINT [DF_TB_MapCfg_Static_ChannelNo]  DEFAULT ((0)),
	[ServerNo] [smallint] NOT NULL CONSTRAINT [DF_TB_MapCfg_Static_ServerNo]  DEFAULT ((0)),
	[GroundNo] [int] NOT NULL,
	[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL
) ON [PRIMARY]
GO
IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO



-- [TB_MapCfg_Static_tmp] 테이블에 원본 [TB_MapCfg_Static] 테이블 데이터 복사
PRINT N'INSERT [ServerNo], [GroundNo] INTO [TB_MapCfg_Static_tmp] FROM [TB_MapCfg_Static]'
GO
INSERT INTO [dbo].[TB_MapCfg_Static_tmp]([ServerNo], [GroundNo])
SELECT DISTINCT [ServerNo], [GroundNo]
FROM [dbo].[TB_MapCfg_Static]
GO
IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO



PRINT N'Creating extended properties'
GO
EXEC sp_addextendedproperty N'MS_Description', N'Static map configuration
(Static map = village, field, some kinds boss map, tutorial map)', 'SCHEMA', N'dbo', 'TABLE', N'TB_MapCfg_Static_tmp', NULL, NULL
GO
IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO


EXEC sp_addextendedproperty N'MS_Description', N'map number', 'SCHEMA', N'dbo', 'TABLE', N'TB_MapCfg_Static_tmp', 'COLUMN', N'GroundNo'
GO
IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO


EXEC sp_addextendedproperty N'MS_Description', N'Server number', 'SCHEMA', N'dbo', 'TABLE', N'TB_MapCfg_Static_tmp', 'COLUMN', N'ServerNo'
GO
IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO


-- Memo 업데이트
PRINT N'Update Memo Columns'
GO
UPDATE A
SET A.[Memo] = B.Memo
FROM [DBO].[TB_MapCfg_Static_tmp] AS A
JOIN [DBO].[TB_MapCfg_Static] AS B ON A.GroundNo = B.GroundNo

IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO

UPDATE [dbo].[TB_MapCfg_Static_tmp]
   SET [RealmNo] = 1
      ,[ChannelNo] = 1
IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO


-- [TB_MapCfg_Static] 테이블 삭제
PRINT N'Drop Table [TB_MapCfg_Static]'
GO
DROP TABLE [dbo].[TB_MapCfg_Static]
GO
IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO



-- Primary Key 생성
PRINT N'Creating primary key [PK_TB_MapCfg_Static_tmp] on [dbo].[TB_MapCfg_Static_tmp]'
GO
ALTER TABLE [dbo].[TB_MapCfg_Static_tmp] ADD CONSTRAINT [PK_TB_MapCfg_Static] PRIMARY KEY CLUSTERED ([RealmNo], [ChannelNo], [ServerNo], [GroundNo]) ON [PRIMARY]
GO
IF @@ERROR<>0 AND @@TRANCOUNT>0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT=0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO


-- [TB_MapCfg_Static_tmp]테이블 이름 변경
PRINT N'Rename Table [TB_MapCfg_Static_tmp] -> [TB_MapCfg_Static]'
GO
EXECUTE sp_rename N'dbo.TB_MapCfg_Static_tmp', N'TB_MapCfg_Static', 'OBJECT' 
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
