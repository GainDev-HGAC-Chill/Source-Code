USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[UP_LoadDefQuest_Wanted]    Script Date: 02/06/2010 20:04:57 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_LoadDefQuest_Wanted]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[UP_LoadDefQuest_Wanted]
END
GO

-- =============================================
-- Author:		김동환
-- Create date: 2010. 2. 6
-- Description:	현상수배 퀘스트 테이블 로드 생성
-- =============================================
CREATE PROCEDURE [dbo].[UP_LoadDefQuest_Wanted]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

    -- Insert statements for procedure here
	SELECT 		
		[QuestID],
		[ClearCount],		
		[ItemNo],
		[ItemCount],
		[CoolTime]
	FROM [dbo].[TB_DefQuest_Wanted] with (nolock) order by [QuestID]
END

