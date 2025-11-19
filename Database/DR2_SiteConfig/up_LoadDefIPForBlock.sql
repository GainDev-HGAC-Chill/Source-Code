USE DR2_SiteConfig
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


/****** Object:  StoredProcedure [dbo].[up_LoadDefIPForBlock]    Script Date: 06/23/2009 17:54:26 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefIPForBlock]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefIPForBlock]
GO

CREATE PROCEDURE [dbo].[up_LoadDefIPForBlock]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	SELECT 
	StartIP, 
	EndIP, 
	NationKey, 
	NationName
	FROM [dbo].[TB_IP_ForBlock] with(nolock)
END
GO