-- 2009.08.21 Eric Kim
-- Limit item 작업 변경 되면서 사용하지 않는 것 삭제
USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_LimitedItem_SyncToRecord]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[UP_LimitedItem_SyncToRecord]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_UpdateLimitedItemRecord_Limit]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[UP_UpdateLimitedItemRecord_Limit]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_UpdateLimitedItemRecord_Limit_Pop]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[UP_UpdateLimitedItemRecord_Limit_Pop]
GO

/****** Object:  StoredProcedure [dbo].[UP_UpdateLimitedItemRecord_Safe]    Script Date: 05/21/2009 14:47:59 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_UpdateLimitedItemRecord_Safe]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[UP_UpdateLimitedItemRecord_Safe]
GO

/****** Object:  StoredProcedure [dbo].[UP_UpdateLimitedItemRecord]    Script Date: 08/20/2009 18:15:58 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_UpdateLimitedItemRecord]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[UP_UpdateLimitedItemRecord]
GO

/****** Object:  Table [dbo].[TB_LimitedItemRecord]    Script Date: 08/21/2009 10:20:11 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_LimitedItemRecord]') AND type in (N'U'))
	DROP TABLE [dbo].[TB_LimitedItemRecord]
GO
