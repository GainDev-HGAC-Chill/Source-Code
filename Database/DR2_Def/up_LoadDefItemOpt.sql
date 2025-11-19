USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefItemOpt]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefItemOpt]
END
GO

USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefItemOpt]
AS
BEGIN
	SELECT 
		[f_NationCodeStr]
		,[OptionType]
		,[OptionGroup]
		,[AbleEquipPos]
		,[OutRate]
		,[NameNo]
		,[AbilType]
		,[ValueLv1]
		,[ValueLv2]
		,[ValueLv3]
		,[ValueLv4]
		,[ValueLv5]
		,[ValueLv6]
		,[ValueLv7]
		,[ValueLv8]
		,[ValueLv9]
		,[ValueLv10]
		,[ValueLv11]
		,[ValueLv12]
		,[ValueLv13]
		,[ValueLv14]
		,[ValueLv15]
		,[ValueLv16]
		,[ValueLv17]
		,[ValueLv18]
		,[ValueLv19]
		,[ValueLv20]
		,[ValueLv21]
		,[ValueLv22]
		,[ValueLv23]
		,[ValueLv24]
		,[ValueLv25]
		,[ValueLv26]
		,[ValueLv27]
		,[ValueLv28]
		,[ValueLv29]
		,[ValueLv30]
		,[ValueLv31]
	FROM [dbo].[TB_DefItemOpt2] with (nolock)
END
GO
