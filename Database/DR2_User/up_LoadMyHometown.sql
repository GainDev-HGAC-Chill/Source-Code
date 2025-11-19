USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadMyHometown]    Script Date: 02/06/2010 19:12:42 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadMyHometown]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadMyHometown]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



CREATE PROCEDURE [dbo].[up_LoadMyHometown]
@StreetNo smallint,
@HouseNo int = 0
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	EXEC [dbo].[up_User_MyHome_Base_Select] @StreetNo,@HouseNo
	EXEC [dbo].[up_User_MyHome_SideJob_Select] @StreetNo,@HouseNo

END










