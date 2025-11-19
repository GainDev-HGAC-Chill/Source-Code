USE DR2_Def
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[up_LoadDefMapItemBag]') AND type IN (N'P'))
BEGIN
	DROP PROCEDURE dbo.[up_LoadDefMapItemBag]
END

/****** Object:  StoredProcedure [dbo].[up_LoadDefMapItemBag]    Script Date: 06/03/2010 15:53:41 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE Proc [dbo].[up_LoadDefMapItemBag]
AS
BEGIN
	select f_NationCodeStr, MapNo, SuccessRateNo,
		BagGrp01, BagGrp02, BagGrp03, BagGrp04, BagGrp05,
		BagGrp06, BagGrp07, BagGrp08, BagGrp09, BagGrp10
		from TB_DefMapItemBag WITH(NOLOCK)
END