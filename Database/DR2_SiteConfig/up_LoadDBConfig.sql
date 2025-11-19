USE [DR2_SiteConfig]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDBConfig]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDBConfig]
GO