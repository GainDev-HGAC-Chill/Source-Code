DROP TABLE [TB_DefCheckIP]
go


USE [DR2_SiteConfig]
GO
/****** 개체:  Table [dbo].[TB_DefCheckIP]    스크립트 날짜: 06/05/2009 01:55:10 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefCheckIP](
	[IDX] [int] IDENTITY(1,1) NOT NULL,
	[StartIP] [nvarchar](32) NOT NULL,
	[EndIP] [nvarchar](32) NOT NULL,
	[NationKey] [nvarchar](32) NULL,
	[NationName] [nvarchar](50) NULL
) ON [PRIMARY]

GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'IP 권한 제한' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefCheckIP'


/* 2009-07-20 R9459 관련 */
/*
		IP Block 방식이 변경 되면서 더 이상 사용하지 않는 테이블 삭제
		R9559 관련인데, 나중에 스크립트 수정 한 것임.
*/
USE [DR2_SiteConfig]
GO
/****** Object:  Table [dbo].[TB_DefCheckIP]    Script Date: 07/20/2009 17:37:49 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefCheckIP]') AND type in (N'U'))
	DROP TABLE [dbo].[TB_DefCheckIP]
	GO