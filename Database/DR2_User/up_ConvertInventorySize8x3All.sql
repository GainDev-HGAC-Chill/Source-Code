USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_ConvertInventorySize8x3All]    Script Date: 02/03/2010 18:46:10 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_ConvertInventorySize8x3All]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_ConvertInventorySize8x3All]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_ConvertInventorySize8x3All]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	begin tran

	DECLARE	@charguid uniqueidentifier, @invextend varbinary(max), @extendidx varbinary(max), @error int

	DECLARE char_cursor CURSOR 
	FOR SELECT characterid, invextend, extendidx FROM dbo.tb_charactersub

	OPEN char_cursor

	FETCH NEXT FROM char_cursor INTO @charguid, @invextend, @extendidx

	WHILE @@FETCH_STATUS = 0
	BEGIN

		exec @error = [dbo].[up_ConvertInventorySize8x3] @charguid, @invextend, @extendidx
		if @error <> 0 OR @@ERROR <> 0
		begin 
			rollback tran
			return
		end

		FETCH NEXT FROM char_cursor INTO @charguid, @invextend, @extendidx

	END 

	CLOSE char_cursor
	DEALLOCATE char_cursor

	commit tran

END
