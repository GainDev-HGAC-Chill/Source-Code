USE [DR2_User]
IF EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'UP_UM_UserMarketOpen2'))
BEGIN
	DROP PROCEDURE [dbo].[UP_UM_UserMarketOpen2]
END

/****** Object:  StoredProcedure [dbo].[UP_UM_UserMarketOpen2]    Script Date: 03/31/2009 14:05:04 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[UP_UM_UserMarketOpen2]
@CharGuId UNIQUEIDENTIFIER,
@MarketName NVARCHAR(50),
@OnlineTime BIGINT,
@OfflineTime BIGINT,
@MarketGrade TINYINT

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.

	SET NOCOUNT ON;

	DECLARE @CURTIME DATETIME
	SET @CURTIME = GETDATE()

	INSERT INTO [dbo].[TB_UserMarketInfo2]
			   ([CharGuid]
			   ,[MarketName]
			   ,[Grade]
			   ,[State]
			   ,[GenTime]
			   ,[OfflineCloseTime]
			   ,[OnlineCloseTime]
			   ,[MarketClosetime]
			   ,[MarketHP])
		 VALUES
			   (@charguid
			   ,@marketname
			   ,@marketgrade
			   ,1
			   ,@CURTIME
			   ,@offlinetime
			   ,@onlinetime
			   ,@CURTIME
			   ,0)

	SELECT @@error

END




GO