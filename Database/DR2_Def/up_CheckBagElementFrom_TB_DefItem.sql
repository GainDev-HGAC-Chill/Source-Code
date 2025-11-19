USE [DR2_Def]
GO
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_CheckBagElementFrom_TB_DefItem]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_CheckBagElementFrom_TB_DefItem]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_CheckBagElementFrom_TB_DefItem]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	select * from tb_defitembagelements
	where 
	dbo.udf_getItem(ItemNo01) = 'NO' or
	dbo.udf_getItem(ItemNo02) = 'NO' or
	dbo.udf_getItem(ItemNo03) = 'NO' or
	dbo.udf_getItem(ItemNo04) = 'NO' or
	dbo.udf_getItem(ItemNo05) = 'NO' or
	dbo.udf_getItem(ItemNo06) = 'NO' or
	dbo.udf_getItem(ItemNo07) = 'NO' or
	dbo.udf_getItem(ItemNo08) = 'NO' or
	dbo.udf_getItem(ItemNo09) = 'NO' or
	dbo.udf_getItem(ItemNo10) = 'NO'
END
