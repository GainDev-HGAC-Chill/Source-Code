USE [DR2_Def]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefParty_Info]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefParty_Info]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefParty_Info]
AS

BEGIN
	SELECT 
			[Attribute]
		,	[Continent]
		,	[Sort]
		,	[Area_NameNo]
		,	[Use]
		,	[GroundNo]
	FROM [dbo].[TB_DefParty_Info]
	WITH(NOLOCK)
END

GO
