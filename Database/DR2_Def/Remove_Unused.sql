-- 2009.09.21 Eric Kim
-- 사용하지 않는 테이블 삭제 (TB_DefItemGroup)
USE [DR2_Def]
GO

/****** Object:  StoredProcedure [dbo].[up_LoadDefItemGroup]    Script Date: 09/21/2009 12:24:10 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefItemGroup]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefItemGroup]
GO

/****** Object:  Table [dbo].[TB_DefItemGroup]    Script Date: 09/21/2009 12:28:04 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefItemGroup]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DefItemGroup]
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefShopInGame]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DefShopInGame]
GO