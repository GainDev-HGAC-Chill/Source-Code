USE DR2_LOCAL
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF EXISTS ( SELECT 1 FROM sys.all_objects WHERE OBJECT_ID = OBJECT_ID( N'dbo.up_LoadChannelEffect' ) AND TYPE IN( N'P', N'PC' ) )
BEGIN
	DROP PROCEDURE dbo.up_LoadChannelEffect
END
GO

CREATE PROCEDURE dbo.up_LoadChannelEffect
AS
BEGIN	
	SET NOCOUNT ON
    
	SELECT f_EffectId, f_Realm, f_Channel, f_Min_Lv, f_Max_Lv
	FROM dbo.TB_ChannelEffect
	
	SET NOCOUNT OFF
END
GO