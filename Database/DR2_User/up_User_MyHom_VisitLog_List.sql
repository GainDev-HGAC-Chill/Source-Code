USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_User_MyHom_VisitLog_List]    Script Date: 02/18/2010 16:55:49 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHom_VisitLog_List]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHom_VisitLog_List]