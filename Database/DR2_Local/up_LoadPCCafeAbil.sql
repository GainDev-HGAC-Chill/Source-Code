USE DR2_local
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================

IF EXISTS ( SELECT * FROM sys.all_objects WHERE object_id = object_id( N'dbo.up_LoadPCCafeAbil' ) )
BEGIN
	DROP PROCEDURE dbo.up_LoadPCCafeAbil
END
GO

CREATE PROCEDURE dbo.up_LoadPCCafeAbil	
AS
BEGIN	
	SET NOCOUNT ON

	SELECT f_Grade, f_AbilNo01, f_AbilNo02, f_AbilNo03, f_AbilNo04 FROM dbo.TB_PCCafeAbil

    SET NOCOUNT OFF
END
GO