USE [DR2_Local]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadOXQuizEvent]    Script Date: 04/20/2009 15:53:31 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadOXQuizEvent]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadOXQuizEvent]
END
GO

CREATE PROC [dbo].[up_LoadOXQuizEvent]
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

SELECT [EventId]
      ,[QuizMin]
      ,[QuizMax]
      ,[UserLimit]
      ,[StartDate]
      ,[EndDate]
      ,[MaxStep]
      ,[EventNotiClose]
      ,[AnsTime]
      ,[SaveLimit]
      ,[EventState]
      ,[Repeat]
      ,[MailTitle]
      ,[MailText]
      ,[EventNoti1]
      ,[EventNotiTime1]
      ,[EventNoti2]
      ,[EventNotiTime2]
      ,[EventNoti3]
      ,[EventNotiTime3]
      ,[EventNoti4]
      ,[EventNotiTime4]
      ,[EventNoti5]
      ,[EventNotiTime5]
      ,[EventNoti6]
      ,[EventNotiTime6]
      ,[EventNoti7]
      ,[EventNotiTime7]
      ,[EventNoti8]
      ,[EventNotiTime8]
      ,[EventNoti9]
      ,[EventNotiTime9]
      ,[EventNoti10]
      ,[EventNotiTime10]
  FROM [dbo].[TB_OXQuizEvent]
    
 SELECT [EventId]
      ,[Step]
      ,[Money]
      ,[ItemNo1]
      ,[ItemCount1]
      ,[ItemNo2]
      ,[ItemCount2]
      ,[ItemNo3]
      ,[ItemCount3]
      ,[ItemNo4]
      ,[ItemCount4]
      ,[ItemNo5]
      ,[ItemCount5]
  FROM [dbo].[TB_OXQuizReward] 
  
  SELECT [QuizNo]
      ,[QuizText]
      ,[QuizResult]
      ,[QuizDiscription]
  FROM [dbo].[TB_OXQuizTable]
  
END
GO
