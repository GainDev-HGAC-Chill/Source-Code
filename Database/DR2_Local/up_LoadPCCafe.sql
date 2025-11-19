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
IF EXISTS ( SELECT * FROM sys.all_objects WHERE object_id = object_id( N'dbo.up_LoadPCCafe' ) )
BEGIN
	DROP PROCEDURE dbo.up_LoadPCCafe
END
GO

CREATE PROCEDURE dbo.up_LoadPCCafe
AS
BEGIN	
	SET NOCOUNT ON
	
	SELECT f_IP, f_Grade FROM dbo.TB_PCCafe
	
	SET NOCOUNT OFF
END
GO
