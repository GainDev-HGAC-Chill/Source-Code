USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Post_Create_GroupMail]    Script Date: 11/24/2009 16:53:51 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Post_Create_GroupMail]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Post_Create_GroupMail]
GO

