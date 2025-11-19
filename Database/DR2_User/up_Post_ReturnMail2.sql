USE DR2_USER
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Post_ReturnMail2]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Post_ReturnMail2]
GO
