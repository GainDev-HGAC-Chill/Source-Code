USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_ConvertInventorySize8x3]    Script Date: 02/03/2010 18:44:25 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_ConvertInventorySize8x3]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_ConvertInventorySize8x3]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_ConvertInventorySize8x3]
@charguid uniqueidentifier,
@binextend varbinary(max),
@binmaxidx varbinary(max)
AS
BEGIN

	SET NOCOUNT ON;

	declare 
	@invtype_e nvarchar(max),
	@extend_e nvarchar(max),
	@invtype_m nvarchar(max),
	@extend_m nvarchar(max),
	@idx int,
	@len int,
	@invextend nvarchar(max),
	@extendidx nvarchar(max),
	@new_invextend nvarchar(max),
	@new_extendidx nvarchar(max)

	select	@invextend = sys.fn_varbintohexstr( @binextend ),
			@extendidx = sys.fn_varbintohexstr( @binmaxidx ),
			@new_invextend = 'update dbo.tb_charactersub set invextend = 0x',
			@new_extendidx = 'update dbo.tb_charactersub set extendidx = 0x',
			@idx = 3,
			@len = len(@invextend)
	
	while @idx <= @len
	begin
		select @invtype_e = substring(@invextend,@idx,2)
		select @extend_e = substring(@invextend,@idx+2,2)

		select @invtype_m = substring(@extendidx,@idx,2)
		select @extend_m = substring(@extendidx,@idx+2,2)

		set @idx = @idx + 4

		set @new_invextend = @new_invextend + @invtype_e
		set @new_extendidx = @new_extendidx + @invtype_e

		if @invtype_e = '01' or @invtype_e = '02' or @invtype_e = '03' or @invtype_e = '04'
		begin
			if @extend_e = '12' or @extend_e = '0c'
			begin
				set @new_invextend = @new_invextend + '0c'
				set @new_extendidx = @new_extendidx + @extend_m
			end
			else if @extend_e = '06'
			begin
				set @new_invextend = @new_invextend + '0c'
				set @new_extendidx = @new_extendidx + '08'
			end
			else if @extend_e = '00'
			begin
				set @new_invextend = @new_invextend + '0c'
				if  @extend_m = '24'
					set @new_extendidx = @new_extendidx + '30'
				else
				begin
					set @new_extendidx = @new_extendidx + '10'
				end
			end
		end
		else
		begin
			set @new_invextend = @new_invextend + @extend_e
			set @new_extendidx = @new_extendidx + @extend_m
		end
	end

	set @new_invextend = @new_invextend + ' where characterid = @charguid'
	set @new_extendidx = @new_extendidx + ' where characterid = @charguid'

	EXEC sp_executesql @new_invextend,N'@charguid uniqueidentifier',@charguid
	EXEC sp_executesql @new_extendidx,N'@charguid uniqueidentifier',@charguid

END
