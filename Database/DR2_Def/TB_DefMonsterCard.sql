USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefMonsterCard]    Script Date: 04/27/2009 14:21:52 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT 1 FROM sys.all_objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefMonsterCard]'))
BEGIN
	CREATE TABLE [dbo].[TB_DefMonsterCard](
		[Idx] [int] IDENTITY(1,1) NOT NULL,
		[CardNo] [int] NOT NULL,
		[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
		[ItemNo] [int] NOT NULL,
	 CONSTRAINT [PK_TB_DefMonsterCard] PRIMARY KEY CLUSTERED 
	(
		[Idx] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END

CREATE TABLE dbo.Tmp_TB_DefMonsterCard
	(
	Idx int NOT NULL IDENTITY (1, 1),
	OrderIndex int NOT NULL CONSTRAINT [DF_TB_DefMonsterCard_OrderIndex]  DEFAULT ((1)),
	CardNo int NOT NULL,
	Memo nvarchar(50) NULL,
	ItemNo int NOT NULL
	)  ON [PRIMARY]
GO

ALTER TABLE dbo.Tmp_TB_DefMonsterCard SET (LOCK_ESCALATION = TABLE)
GO
DECLARE @v sql_variant 
SET @v = N'몬스터 카드 <-> 아이템 변환 테이블
몬스터 카드 인덱스와 아이템 아이디 변환 정보 저장'
EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefMonsterCard', NULL, NULL
GO
SET IDENTITY_INSERT dbo.Tmp_TB_DefMonsterCard ON
GO
IF EXISTS(SELECT * FROM dbo.TB_DefMonsterCard)
	 EXEC('INSERT INTO dbo.Tmp_TB_DefMonsterCard (Idx, CardNo, Memo, ItemNo)
		SELECT Idx, CardNo, Memo, ItemNo FROM dbo.TB_DefMonsterCard WITH (HOLDLOCK TABLOCKX)')
GO
SET IDENTITY_INSERT dbo.Tmp_TB_DefMonsterCard OFF
GO
DROP TABLE dbo.TB_DefMonsterCard
GO
EXECUTE sp_rename N'dbo.Tmp_TB_DefMonsterCard', N'TB_DefMonsterCard', 'OBJECT' 
GO
ALTER TABLE dbo.TB_DefMonsterCard ADD CONSTRAINT
	PK_TB_DefMonsterCard PRIMARY KEY CLUSTERED 
	(
	Idx
	) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

GO

