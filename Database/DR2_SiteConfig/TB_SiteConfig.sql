USE [DR2_SiteConfig]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id=OBJECT_ID(N'[dbo].[TB_SiteConfig]')) 
BEGIN

CREATE TABLE [dbo].[TB_SiteConfig](
	[IDX] [int] NOT NULL,
	[RealmNo] [smallint] NULL,
	[RealmName] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NOT NULL,
	[RealmTblName] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NOT NULL,
	[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL
) ON [PRIMARY]
END

-- 2009-10-21 : Notice_TblName column 추가
--  by Eric Kim
ALTER TABLE [dbo].[TB_SiteConfig] ADD [Notice_TblName] [nvarchar](100) NULL
GO
UPDATE [dbo].[TB_SiteConfig] SET [Notice_TblName] = N'TB_Channel_Notice'
GO
-- 2009-10-29 : SiteConfig 수정 롤백 ( MapCfg_ column 삭제 )
ALTER TABLE [dbo].[TB_SiteConfig] 
DROP COLUMN [MapCfg_Mission_TblName],[MapCfg_Public_TblName],[MapCfg_Static_TblName]
GO