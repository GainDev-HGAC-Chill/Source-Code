USE [DR2_Def]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefHiddenRewordItem]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefHiddenRewordItem]
END
GO

/****** 개체:  StoredProcedure [dbo].[up_LoadDefHiddenRewordItem]    스크립트 날짜: 01/05/2010 11:22:47 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefHiddenRewordItem]

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	SELECT [ItemCount],[MinLevel],[MaxLevel],[ItemNo] FROM [dbo].[TB_DefHiddenRewordItem]

END

GO
