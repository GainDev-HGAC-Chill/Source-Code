USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[udf_MakeClearAchievementHexString]') AND type in (N'FN', N'IF', N'TF', N'FS', N'FT'))
DROP FUNCTION [dbo].[udf_MakeClearAchievementHexString]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE FUNCTION [dbo].[udf_MakeClearAchievementHexString]
(
	@idx int,
	@hex nvarchar(max)
)
RETURNS nvarchar(max)
AS
BEGIN

	DECLARE @Return nvarchar(max)
	DECLARE @BytePos int, @BitOffset int, @ByteValue tinyint, @BitPos int, @ReturnValue tinyint
	set @BitPos = (@idx*2)
	set @BytePos = ((@BitPos/8)+1)*2+1
	set @BitOffset = (@BitPos%8)
	set @ByteValue = power(2,@BitOffset)

	select @ReturnValue = 
	case substring(@hex,@BytePos+1,1)
	when '0' then 0x00
	when '1' then 0x01
	when '2' then 0x02
	when '3' then 0x03
	when '4' then 0x04
	when '5' then 0x05
	when '6' then 0x06
	when '7' then 0x07
	when '8' then 0x08
	when '9' then 0x09
	when 'A' then 0x0A
	when 'B' then 0x0B
	when 'C' then 0x0C
	when 'D' then 0x0D
	when 'E' then 0x0E
	when 'F' then 0x0F
	end

	select @ReturnValue = @ReturnValue + 
	case substring(@hex,@BytePos,1)
	when '0' then 0x00
	when '1' then 0x10
	when '2' then 0x20
	when '3' then 0x30
	when '4' then 0x40
	when '5' then 0x50
	when '6' then 0x60
	when '7' then 0x70
	when '8' then 0x80
	when '9' then 0x90
	when 'A' then 0xA0
	when 'B' then 0xB0
	when 'C' then 0xC0
	when 'D' then 0xD0
	when 'E' then 0xE0
	when 'F' then 0xF0
	end

	if (@ReturnValue & @ByteValue) = @ByteValue
	begin
		set @ReturnValue = @ReturnValue - @ByteValue
	end

	declare @Len int
	set @Len = len(@hex)
	set @Return = substring(@hex,1,@BytePos-1)
	set @Return = @Return + sys.fn_varbintohexsubstring(0,@ReturnValue,1,1)
	declare @nowlen int
	set @nowlen = len(@Return)
	set @Return = @Return + substring(@hex, @nowlen+1, @len-@nowlen)

	return @Return

END


