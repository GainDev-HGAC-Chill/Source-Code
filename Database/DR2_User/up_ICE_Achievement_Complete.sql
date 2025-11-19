USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_ICE_Achievement_Complete]    Script Date: 11/06/2009 17:13:39 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_ICE_Achievement_Complete]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_ICE_Achievement_Complete]
GO
