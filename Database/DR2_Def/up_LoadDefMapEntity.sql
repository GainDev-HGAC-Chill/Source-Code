USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefMapEntity]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefMapEntity]
END
GO

/****** Object:  StoredProcedure [dbo].[up_LoadDefMapEntity]    Script Date: 01/17/2013 20:27:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[up_LoadDefMapEntity]
AS
SET Nocount On;
BEGIN
	SELECT  [IDX],[f_NationCodeStr], [GroundNo]	,[iClass]	,[iLevel]	,[iEffect]
		,[MinX]	,[MinY]	,[MinZ]	,[MaxX]	,[MaxY]	,[MaxZ], [OwnerPointGuid]
		FROM [dbo].[TB_DefMapEntity] WITH (NOLOCK) 		
END
GO
