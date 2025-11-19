USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadEvent]    Script Date: 05/18/2009 18:48:18 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadEvent]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadEvent]
GO

/****** Object:  StoredProcedure [dbo].[up_LoadEvent]    Script Date: 05/18/2009 18:47:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/*
////////////////////////////////////////////////////////////////////////
// Description : 
// [PARAMETER] : 
// [RETURN] : 
// [REMARK]
//	2008-10-07 : Eric Kim, Table 이름앞에 [dbo]. 추가
////////////////////////////////////////////////////////////////////////
*/
CREATE proc [dbo].[up_LoadEvent]
as
BEGIN

	SELECT 
		EventNo,
		EventType,
		Title,
		Description,
		StartDate,
		EndDate,
		Period,
		intData01,
		intData02,
		intData03,
		bigintData01,
		bigintData02,
		bigintData03,
		guidData01,
		guidData02,
		guidData03,
		stringData01,
		stringData02,
		stringData03
		from [dbo].[TB_Event] WITH(NOLOCK)

END

