USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_LoadDefEmotionGroup]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[UP_LoadDefEmotionGroup]
END
GO

set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go

CREATE PROCEDURE [dbo].[UP_LoadDefEmotionGroup]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	SELECT [Type]
		  ,[GroupNo]
		  ,[NameNo]
	  FROM [dbo].[TB_DefEmotionGroup]
  	  
	SELECT 	 [ActionNo]
			,[Type]
			,[GroupNo]

	  FROM [dbo].[TB_DefEmotion]

END
