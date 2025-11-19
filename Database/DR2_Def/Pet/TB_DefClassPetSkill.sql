USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefClassPetSkill]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DefClassPetSkill]
GO
