USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_UM_MarketRemove]    Script Date: 07/17/2009 12:05:47 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UM_MarketRemove]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_UM_MarketRemove]