USE DR2_Def
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_LoadDefQuest_Random]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[UP_LoadDefQuest_Random]
GO

/****** Object:  StoredProcedure [dbo].[UP_LoadDefQuest_Random]    Script Date: 07/09/2009 11:25:38 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: 2009. 2. 2
-- Description:	·£´ý Äù½ºÆ® Å×ÀÌºí ·Îµå »ý¼º
-- =============================================
CREATE PROCEDURE [dbo].[UP_LoadDefQuest_Random]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

    -- Insert statements for procedure here
	SELECT 
		--[Index],
		[Type],
		[MinLevel],
		[MaxLevel],
		[f_GroupNo],
		[StartID],
		[EndID],
		[DisplayCount]
	FROM [dbo].[TB_DefQuest_Random] with (nolock) order by [Index]
END

GO