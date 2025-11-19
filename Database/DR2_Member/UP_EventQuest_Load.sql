USE [DR2_Member]
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_EventQuest_Load]') AND Type in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_EventQuest_Load]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: 2009-08-25
-- Description:	ÀÌº¥Æ® Äù½ºÆ®
-- =============================================
CREATE PROCEDURE dbo.[UP_EventQuest_Load]
	@RealmNo INT
AS
BEGIN
	SET NOCOUNT ON;

SELECT [f_NoticeTime],[f_NoticeMessage] FROM [dbo].[TB_EventQuest_Notice]
SELECT [f_ItemNo],[f_ItemCount] FROM [dbo].[TB_EventQuest_Reward]
SELECT [f_TargetItemNo],[f_TargetItemCount] FROM [dbo].[TB_EventQuest_Target]
SELECT [f_StartTime]
,[f_EndTime]
,[f_Title]
,[f_Prolog]
,[f_Contents]
,[f_NpcTalk_Prolog]
,[f_NpcTalk_NotEnd]
,[f_NpcTalk_End]
,[f_RewardMailTitle]
,[f_RewardMailContents]
,[f_RewardGold]
FROM [dbo].[TB_EventQuest]
SELECT [f_Enable] FROM [dbo].[TB_EventQuest_Status] WHERE [f_RealmNo] = @RealmNo

END
GO
