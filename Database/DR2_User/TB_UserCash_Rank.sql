USE [DR2_User]
IF NOT EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'TB_UserCash_Rank'))
BEGIN
	CREATE TABLE [dbo].[TB_UserCash_Rank](
		[CharGuId] [uniqueidentifier] NOT NULL,
		[IsVisable] [bit] NOT NULL,
		[UsedCash] [bigint] NOT NULL,
		[CharName] [nvarchar](50) NOT NULL,
		[ModifyDate] [datetime] NULL
	) ON [PRIMARY]

	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'캐시 사용 캐릭터 GUID' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_UserCash_Rank', @level2type=N'COLUMN',@level2name=N'CharGuId'
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'랭킹 공개 여부 정보 플레그 
	- 0 : 비공개
	- 1 : 공개' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_UserCash_Rank', @level2type=N'COLUMN',@level2name=N'IsVisable'
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'이 캐릭터가 게임에서 사용한 캐시량' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_UserCash_Rank', @level2type=N'COLUMN',@level2name=N'UsedCash'
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'캐릭터 이름' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_UserCash_Rank', @level2type=N'COLUMN',@level2name=N'CharName'
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'랭킹 공개 여부 플레그를 최종 수정한 시간
	- 비공개로 변경한후 특정 시간동안 다시 공개로 변경 할 수 없도록 하기 위해 사용한다.' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_UserCash_Rank', @level2type=N'COLUMN',@level2name=N'ModifyDate'
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'유저 캐시 사용량을 기록 하여 캐시샵에서 순위를 보여주기 위한 테이블' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_UserCash_Rank'
END

/* To prevent any potential data loss issues, you should review this script in detail before running it outside the context of the database designer.*/
BEGIN TRANSACTION
SET QUOTED_IDENTIFIER ON
SET ARITHABORT ON
SET NUMERIC_ROUNDABORT OFF
SET CONCAT_NULL_YIELDS_NULL ON
SET ANSI_NULLS ON
SET ANSI_PADDING ON
SET ANSI_WARNINGS ON
COMMIT
BEGIN TRANSACTION
GO
ALTER TABLE dbo.TB_UserCash_Rank
	DROP COLUMN CharName
GO
COMMIT
