USE DR2_Def
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		
-- Create date: 
-- Description:	
-- =============================================
IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_LoadDefNpcTalkMapMove]') and [type] in (N'P'))
BEGIN
	DROP PROCEDURE [dbo].[UP_LoadDefNpcTalkMapMove]
END
GO

CREATE PROCEDURE [dbo].[UP_LoadDefNpcTalkMapMove]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

    -- Insert statements for procedure here
	SELECT
		[f_GroundNo]
		,[f_NpcGuid]
		,[f_TargetGroundNo]
		,[f_TargetPortalNo]
	FROM [dbo].[TB_DefNpcTalkMapMove]
END
GO
