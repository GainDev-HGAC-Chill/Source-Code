USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHome_Sell]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHome_Sell]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_User_MyHome_Sell]
@OwnerGuid uniqueidentifier,
@BuildingNo smallint,
@HouseNo	int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	delete from [dbo].[TB_User_MyHome_Base] where streetno = @BuildingNo and HouseNo = @HouseNo and [OwnerGuid] = @OwnerGuid
	delete from dbo.TB_User_MyHome_Invitation where streetno = @BuildingNo and houseno = @HouseNo
	delete from dbo.TB_User_MyHome_TodayVisitors where townno = @buildingno and houseno = @houseno
	delete from dbo.TB_User_MyHome_VisitLog where ownerguid = @ownerguid
	delete from dbo.TB_User_MyHome_Visitors where streetno = @buildingno and houseno = @houseno
	delete from dbo.TB_User_MyHome_WriteLog_Visitors where homeownerguid = @ownerguid

END