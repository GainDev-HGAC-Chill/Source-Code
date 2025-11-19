USE DR2_User

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Post_Create_UserMail5]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_Post_Create_UserMail5]
END 
GO