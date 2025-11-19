USE [DR2_Local]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadCreateCharacterEventReward]    Script Date: 06/30/2009 17:05:03 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadCreateCharacterEventReward]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadCreateCharacterEventReward]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadCreateCharacterEventReward]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;


SELECT [EventRewardKey]
      ,[ItemNo01]
      ,[ItemCount01]
      ,[TimeType01]
      ,[UseTime01]
      ,[RarityControl01]
      ,[ItemNo02]
      ,[ItemCount02]
      ,[TimeType02]
      ,[UseTime02]
      ,[RarityControl02]
      ,[ItemNo03]
      ,[ItemCount03]
      ,[TimeType03]
      ,[UseTime03]
      ,[RarityControl03]
      ,[ItemNo04]
      ,[ItemCount04]
      ,[TimeType04]
      ,[UseTime04]
      ,[RarityControl04]
      ,[ItemNo05]
      ,[ItemCount05]
      ,[TimeType05]
      ,[UseTime05]
      ,[RarityControl05]
      ,[ItemNo06]
      ,[ItemCount06]
      ,[TimeType06]
      ,[UseTime06]
      ,[RarityControl06]
      ,[ItemNo07]
      ,[ItemCount07]
      ,[TimeType07]
      ,[UseTime07]
      ,[RarityControl07]
      ,[ItemNo08]
      ,[ItemCount08]
      ,[TimeType08]
      ,[UseTime08]
      ,[RarityControl08]
      ,[ItemNo09]
      ,[ItemCount09]
      ,[TimeType09]
      ,[UseTime09]
      ,[RarityControl09]
      ,[ItemNo010]
      ,[ItemCount010]
      ,[TimeType010]
      ,[UseTime010]
      ,[RarityControl010]
  FROM [dbo].[TB_Create_Character_Event_Reward]
  
END
GO
