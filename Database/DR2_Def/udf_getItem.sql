USE [DR2_Def]
GO
/****** Object:  UserDefinedFunction [dbo].[udf_getItem]    Script Date: 01/29/2010 17:07:23 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[udf_getItem]') AND type in (N'FN', N'IF', N'TF', N'FS', N'FT'))
DROP FUNCTION [dbo].[udf_getItem]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date, ,>
-- Description:	<Description, ,>
-- =============================================
CREATE FUNCTION [dbo].[udf_getItem]
(
@ItemNo int
)
RETURNS nvarchar(50)
AS
BEGIN

	if @ItemNo = 0 OR @ITEMNO IS NULL
		return 'NONE'

	if exists(select * from dbo.tb_defitem where itemno = @itemno)
		return 'YES'
	if exists(select * from dbo.tb_defitem_HOME where itemno = @itemno)
		return 'YES'
	if exists(select * from dbo.tb_defitem_PET where itemno = @itemno)
		return 'YES'

	return 'NO'
END


