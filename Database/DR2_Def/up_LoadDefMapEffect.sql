USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefMapEffect]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefMapEffect]
END
GO

/****** Object:  StoredProcedure [dbo].[up_LoadDefMapEffect]    Script Date: 07/09/2009 11:25:28 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE Proc [dbo].[up_LoadDefMapEffect]
AS

begin
	SELECT 	[f_NationCodeStr],[EffectID],[GroundNo]
		,[Type01] ,[Value01]
		,[Type02] ,[Value02]
		,[Type03] ,[Value03]
		,[Type04] ,[Value04]
		,[Type05] ,[Value05]
		,[Type06] ,[Value06]
		,[Type07] ,[Value07]
		,[Type08] ,[Value08]
		,[Type09] ,[Value09]
		,[Type10] ,[Value10]
		,[Type101] ,[Value101]
		FROM [dbo].[TB_DefMapEffect] WITH(NOLOCK)
end
GO