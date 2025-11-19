USE DR2_Def

set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefItemContainer2]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefItemContainer2]
END
GO

CREATE PROCEDURE  [dbo].[up_LoadDefItemContainer2]
AS

begin
	SELECT [f_NationCodeStr], [ContainerNo], [RewardItem], [SuccessRateControlNo], [BagGrpNo01], [BagGrpNo02], [BagGrpNo03], [BagGrpNo04], [BagGrpNo05],
		[BagGrpNo06], [BagGrpNo07], [BagGrpNo08], [BagGrpNo09], [BagGrpNo10]
		FROM [dbo].[TB_DefItemContainer] WITH(NOLOCK)

end
go