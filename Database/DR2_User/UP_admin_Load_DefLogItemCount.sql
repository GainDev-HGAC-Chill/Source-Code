USE [DR2_User]
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_admin_Load_DefLogItemCount]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE [dbo].[UP_admin_Load_DefLogItemCount]
END
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
CREATE PROCEDURE [dbo].[UP_admin_Load_DefLogItemCount]
AS
BEGIN
	SET NOCOUNT ON;

	SELECT
		[ItemNo],
		SUM(CONVERT(BIGINT,[Count])) AS [Count],
		SUM(CONVERT(BIGINT,1)) AS [RowCount]
	FROM [dbo].[TB_UserItem] WITH (nolock)
	WHERE [ItemNo] in (SELECT [f_ItemNo] FROM [dbo].[TB_admin_DefLogItemCount]) GROUP BY [ItemNo]
END
GO
