USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadOXQuizEventState]    Script Date: 06/22/2009 14:12:02 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadOXQuizEventState]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadOXQuizEventState]
GO

/****** Object:  StoredProcedure [dbo].[up_LoadOXQuizEventState]    Script Date: 06/22/2009 14:12:05 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadOXQuizEventState]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [EventID]
		  ,[State]
	  FROM [dbo].[TB_OXQuizEventState]
  
END
GO