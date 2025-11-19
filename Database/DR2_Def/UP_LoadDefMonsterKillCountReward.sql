IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_LoadDefMonsterKillCountReward2]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[UP_LoadDefMonsterKillCountReward2]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_LoadDefMonsterKillCountReward2]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[UP_LoadDefMonsterKillCountReward]
GO

/****** Object:  StoredProcedure [dbo].[UP_LoadDefMonsterKillCountReward]    Script Date: 07/09/2009 11:25:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<À°Á¤¹ü>
-- Create date: <2008,09,09>
-- Description:	20080909 - »ý¼º
-- =============================================
CREATE PROCEDURE [dbo].[UP_LoadDefMonsterKillCountReward]
AS
BEGIN
	SET NOCOUNT ON;

	SELECT
		[Kill]
		,[MinLevel]
		,[MaxLevel]
		,[ItemNo]
		,[Count]
	FROM
		[dbo].[TB_DefMonsterKillCountReward]
END

GO