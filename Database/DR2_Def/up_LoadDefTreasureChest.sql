USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefTreasureChest]    Script Date: 12/08/2010 11:16:06 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefTreasureChest]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefTreasureChest]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadDefTreasureChest]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

SELECT [f_NationCodeStr]
	  ,[BoxItemNo]
      ,[KeyItemNo]
      ,[ResultItemNo]
      ,[ResultItemCount]
      ,[TimeType]
      ,[UseTime]
      ,[Rarity]
      ,[EnchantType]
      ,[EnchantLevel]
      ,[Rate]
      ,[Broadcast]
  FROM [dbo].[TB_DefTreasureChest]

END
