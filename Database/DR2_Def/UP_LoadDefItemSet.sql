USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefItemSet]    Script Date: 05/26/2010 17:51:19 ******/
IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefItemSet]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefItemSet]
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROC [dbo].[up_LoadDefItemSet]
as
begin

	SELECT f_NationCodeStr, SetNo, [Name], SetAbil01, SetAbil02, NeedItem01, NeedItem02,
		NeedItem03, NeedItem04, NeedItem05, NeedItem06, NeedItem07, NeedItem08, NeedItem09, NeedItem10
		from TB_DefItemSet WITH(NOLOCK)

end
