USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHome_Buy]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHome_Buy]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_User_MyHome_Buy]
@OwnerGuid uniqueidentifier,
@BuildingNo smallint,
@HomePrice bigint
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	if exists(select 1 from [dbo].[TB_User_MyHome_Base] where [OwnerGuid] = @OwnerGuid)
	begin
		select 1
		return
	end

	begin tran

	declare @HouseNo int, @TexTime datetime

	select @HouseNo = isnull(max([HouseNo]),0)+1 from [dbo].[TB_User_MyHome_Base] where [StreetNo] = @BuildingNo
	set @TexTime = dateadd(day,7,getdate())

	INSERT INTO [dbo].[TB_User_MyHome_Base]
			   ([StreetNo]
			   ,[HouseNo]
			   ,[HomePrice]
			   ,[GroundNo]
			   ,[HomeInSideGuid]
			   ,[HomeOutSideGuid]
			   ,[OwnerGuid]
			   ,[PayTexTime]
			   ,[PayTexNotiTime]
			   ,[HomeStyle])
		 VALUES
			   (@BuildingNo
			   ,@HouseNo
			   ,@HomePrice
			   ,9991001
			   ,newid()
			   ,newid()
			   ,@OwnerGuid
			   ,@TexTime
			   ,@TexTime
			   ,70001560)

	if @@ERROR <> 0
	begin
		rollback tran
		SELECT 1
		return
	end

	commit tran

	SELECT 0, @OwnerGuid, @BuildingNo, [HouseNo] from [dbo].[TB_User_MyHome_Base] where OwnerGuid = @OwnerGuid
END




