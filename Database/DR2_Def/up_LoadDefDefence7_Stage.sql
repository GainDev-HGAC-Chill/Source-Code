USE [DR2_Def]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefDefence7_Stage]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefDefence7_Stage]
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefDefence7_Stage]

AS
BEGIN
	SET NOCOUNT ON;
	
	SELECT [Mission_No],[Mission_Type],[Party_Number],[Stage_No],[Result_ItemNo],[Result_ItemCount], [Win_ItemNo], [Win_ItemCount],[Clear_StrategicPoint], [Result_No], [Result_Count], [UseCoin_StrategicPoint]

	FROM [dbo].[TB_DefDefence7_Stage]
END

GO
