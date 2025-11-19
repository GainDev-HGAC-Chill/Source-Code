USE [DR2_Local]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadPCRoom]    Script Date: 05/18/2009 18:46:33 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadPCRoom]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadPCRoom]
GO

/****** Object:  StoredProcedure [dbo].[up_LoadPCRoom]    Script Date: 05/18/2009 18:46:44 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadPCRoom]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;


	SELECT [IP],[PCRoomGuid] FROM [dbo].[TB_PCRoomIP]
	
END
