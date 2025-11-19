IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefItemRarityUpgradeCostRate]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_LoadDefItemRarityUpgradeCostRate]
GO

/****** Object:  StoredProcedure [dbo].[up_LoadDefItemRarityUpgradeCostRate]    Script Date: 07/09/2009 11:25:26 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadDefItemRarityUpgradeCostRate]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [EquipPos]
		  ,[CostRate]
	  FROM [dbo].[TB_DefItemRarityUpgradeCostRate] with(nolock)

END

GO