USE [DR2_Def]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefMapMonsterBagControl2]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefMapMonsterBagControl2]
END
GO

/****** 개체:  StoredProcedure [dbo].[up_LoadDefMapMonsterBagControl2]    스크립트 날짜: 02/06/2010 15:22:47 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefMapMonsterBagControl2]

AS
BEGIN
	SELECT     ParentBagNo, DefaultBagNo, Level01BagNo, Level02BagNo, Level03BagNo, Level04BagNo, Level05BagNo, Level06BagNo, Level07BagNo, Level08BagNo, Level09BagNo
		FROM	TB_DefMonsterBagControl WITH(NOLOCK)
		order by ParentBagNo
END

GO
