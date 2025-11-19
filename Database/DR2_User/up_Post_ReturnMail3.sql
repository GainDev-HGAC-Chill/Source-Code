USE DR2_USER
GO

/****** 개체:  StoredProcedure [dbo].[up_Post_ReturnMail3]    스크립트 날짜: 07/17/2009 11:24:32 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Post_ReturnMail3]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Post_ReturnMail3]
GO
