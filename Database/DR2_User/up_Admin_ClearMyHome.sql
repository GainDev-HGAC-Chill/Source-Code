USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Admin_ClearMyHome]    Script Date: 08/14/2009 23:52:27 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Admin_ClearMyHome]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Admin_ClearMyHome]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Admin_ClearMyHome]
@TownNo SMALLINT
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	DELETE FROM dbo.TB_User_MyHome_Base WHERE StreetNo = CASE @TownNo WHEN 0 THEN StreetNo ELSE @TownNo END

END


