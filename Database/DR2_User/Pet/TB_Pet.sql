USE [DR2_User]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_Pet]') AND type in (N'U'))
BEGIN

CREATE TABLE [dbo].[TB_Pet](
	[PetID] [uniqueidentifier] NOT NULL,
--		CONSTRAINT FK_TB_Pet_ID_REF_TB_UserItem_ItemGuid FOREIGN KEY REFERENCES TB_UserItem(ItemGuid)
--			ON UPDATE NO ACTION
--			ON DELETE CASCADE,
	[Name] [nvarchar](20) NOT NULL,
	[Class] [int] NOT NULL,
	[Lv] [smallint] NOT NULL,
	[Exp] [bigint] NOT NULL,
	[MP] [int] NOT NULL CONSTRAINT [DF_TB_Pet_MP] DEFAULT (0),
	[Health] [int] NOT NULL CONSTRAINT [DF_TB_Pet_Health] DEFAULT (0),
	[Mental] [int] NOT NULL CONSTRAINT [DF_TB_Pet_Mental] DEFAULT (0),
	[Color] [tinyint] NOT NULL CONSTRAINT [DF_TB_Pet_Color] DEFAULT (0),
	[Skill01] [int] NOT NULL CONSTRAINT [DF_TB_Pet_Skill01] DEFAULT(0),
	[Skill02] [int] NOT NULL CONSTRAINT [DF_TB_Pet_Skill02] DEFAULT(0),
	[Skill03] [int] NOT NULL CONSTRAINT [DF_TB_Pet_Skill03] DEFAULT(0)
 CONSTRAINT [PK_TB_Pet_ID] PRIMARY KEY NONCLUSTERED 
(
	[PetID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

END
GO

ALTER TABLE [dbo].[TB_Pet]
DROP COLUMN [Fatigue]
GO

-- Delete Skill
IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_Skill04]') AND type = 'D')
BEGIN
	ALTER TABLE [dbo].[TB_Pet] DROP CONSTRAINT [DF_TB_Pet_Skill04]
END
ELSE
BEGIN

	DECLARE @Name NVARCHAR(200)
	DECLARE tempCur CURSOR

	FOR 
	SELECT [name] FROM sysobjects
	WHERE [parent_obj] = OBJECT_ID('[dbo].[TB_Pet]') AND [xtype] = N'D'

	OPEN tempCur

	FETCH NEXT FROM tempCur INTO @Name
	WHILE @@FETCH_STATUS = 0
	BEGIN
		IF @Name LIKE '%Skill04%'
		BEGIN
	
			DECLARE @SQL NVARCHAR(1000)
			SET @SQL = N'ALTER TABLE [dbo].[TB_Pet] DROP CONSTRAINT [' + @Name + ']'
			EXEC sp_executesql @SQL
			BREAK
		END
	
		FETCH NEXT FROM tempCur INTO @Name
	END

	CLOSE tempCur
	DEALLOCATE tempCur
	
END
GO

ALTER TABLE [dbo].[TB_Pet] DROP COLUMN [Skill04]
GO


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_Skill05]') AND type = 'D')
BEGIN
	ALTER TABLE [dbo].[TB_Pet] DROP CONSTRAINT [DF_TB_Pet_Skill05]
END
ELSE
BEGIN

	DECLARE @Name NVARCHAR(200)
	DECLARE tempCur CURSOR

	FOR 
	SELECT [name] FROM sysobjects
	WHERE [parent_obj] = OBJECT_ID('[dbo].[TB_Pet]') AND [xtype] = N'D'

	OPEN tempCur

	FETCH NEXT FROM tempCur INTO @Name
	WHILE @@FETCH_STATUS = 0
	BEGIN
		IF @Name LIKE '%Skill05%'
		BEGIN
	
			DECLARE @SQL NVARCHAR(1000)
			SET @SQL = N'ALTER TABLE [dbo].[TB_Pet] DROP CONSTRAINT [' + @Name + ']'
			EXEC sp_executesql @SQL
			BREAK
		END
	
		FETCH NEXT FROM tempCur INTO @Name
	END

	CLOSE tempCur
	DEALLOCATE tempCur
	
END
GO

ALTER TABLE [dbo].[TB_Pet] DROP COLUMN [Skill05]
GO


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_Skill06]') AND type = 'D')
BEGIN
	ALTER TABLE [dbo].[TB_Pet] DROP CONSTRAINT [DF_TB_Pet_Skill06]
END
ELSE
BEGIN

	DECLARE @Name NVARCHAR(200)
	DECLARE tempCur CURSOR

	FOR 
	SELECT [name] FROM sysobjects
	WHERE [parent_obj] = OBJECT_ID('[dbo].[TB_Pet]') AND [xtype] = N'D'

	OPEN tempCur

	FETCH NEXT FROM tempCur INTO @Name
	WHILE @@FETCH_STATUS = 0
	BEGIN
		IF @Name LIKE '%Skill06%'
		BEGIN
	
			DECLARE @SQL NVARCHAR(1000)
			SET @SQL = N'ALTER TABLE [dbo].[TB_Pet] DROP CONSTRAINT [' + @Name + ']'
			EXEC sp_executesql @SQL
			BREAK
		END
	
		FETCH NEXT FROM tempCur INTO @Name
	END

	CLOSE tempCur
	DEALLOCATE tempCur
	
END
GO

ALTER TABLE [dbo].[TB_Pet] DROP COLUMN [Skill06]
GO


-- Delete TimeVar
IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_TimeVar]') AND type = 'D')
BEGIN
	ALTER TABLE [dbo].[TB_Pet] DROP CONSTRAINT [DF_TB_Pet_TimeVar]
END
ELSE
BEGIN

	DECLARE @Name NVARCHAR(200)
	DECLARE tempCur CURSOR

	FOR 
	SELECT [name] FROM sysobjects
	WHERE [parent_obj] = OBJECT_ID('[dbo].[TB_Pet]') AND [xtype] = N'D'

	OPEN tempCur

	FETCH NEXT FROM tempCur INTO @Name
	WHILE @@FETCH_STATUS = 0
	BEGIN
		IF @Name LIKE '%TimeVar%'
		BEGIN
	
			DECLARE @SQL NVARCHAR(1000)
			SET @SQL = N'ALTER TABLE [dbo].[TB_Pet] DROP CONSTRAINT [' + @Name + ']'
			EXEC sp_executesql @SQL
			BREAK
		END
	
		FETCH NEXT FROM tempCur INTO @Name
	END

	CLOSE tempCur
	DEALLOCATE tempCur
	
END
GO

ALTER TABLE [dbo].[TB_Pet] DROP COLUMN [TimeVar]
GO


-- Add MP
IF  NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_MP]') AND type = 'D')
BEGIN
	ALTER TABLE [dbo].[TB_Pet]
	ADD [MP] [int] NOT NULL CONSTRAINT [DF_TB_Pet_MP] DEFAULT (0)
END
GO

-- Delete Hunger
IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_Hunger]') AND type = 'D')
BEGIN
	ALTER TABLE [dbo].[TB_Pet] DROP CONSTRAINT [DF_TB_Pet_Hunger]
END
ELSE
BEGIN
	
	DECLARE @Name NVARCHAR(200)
	DECLARE tempCur CURSOR

	FOR 
	SELECT [name] FROM sysobjects
	WHERE [parent_obj] = OBJECT_ID('[dbo].[TB_Pet]') AND [xtype] = N'D'

	OPEN tempCur

	FETCH NEXT FROM tempCur INTO @Name
	WHILE @@FETCH_STATUS = 0
	BEGIN
		IF @Name LIKE '%Hunger%'
		BEGIN
	
			DECLARE @SQL NVARCHAR(1000)
			SET @SQL = N'ALTER TABLE [dbo].[TB_Pet] DROP CONSTRAINT [' + @Name + ']'
			EXEC sp_executesql @SQL
			BREAK
		END
	
		FETCH NEXT FROM tempCur INTO @Name
	END

	CLOSE tempCur
	DEALLOCATE tempCur
	
END
GO

ALTER TABLE [dbo].[TB_Pet] DROP COLUMN [Hunger]
GO


-- Add Health
IF  NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_Health]') AND type = 'D')
BEGIN

	ALTER TABLE [dbo].[TB_Pet]
	ADD [Health] [int] NOT NULL CONSTRAINT [DF_TB_Pet_Health] DEFAULT (0)
	
END
ELSE
BEGIN

	ALTER TABLE [dbo].[TB_Pet] ALTER COLUMN [Health] [int] NOT NULL
	ALTER TABLE [dbo].[TB_Pet] ADD CONSTRAINT [DF_TB_Pet_Health] DEFAULT (0) FOR [Health] 
	
END
GO

IF 0 <> @@ERROR
BEGIN
		
	DECLARE @Name NVARCHAR(200)
	DECLARE tempCur CURSOR

	FOR 
	SELECT [name] FROM sysobjects
	WHERE [parent_obj] = OBJECT_ID('[dbo].[TB_Pet]') AND [xtype] = N'D'

	OPEN tempCur

	FETCH NEXT FROM tempCur INTO @Name
	WHILE @@FETCH_STATUS = 0
	BEGIN
		IF @Name LIKE '%Health%'
		BEGIN
	
			DECLARE @SQL NVARCHAR(1000)
			SET @SQL = N'ALTER TABLE [dbo].[TB_Pet] DROP CONSTRAINT [' + @Name + ']'
			EXEC sp_executesql @SQL
			BREAK
		END
	
		FETCH NEXT FROM tempCur INTO @Name
	END

	CLOSE tempCur
	DEALLOCATE tempCur
		
	ALTER TABLE [dbo].[TB_Pet] ALTER COLUMN [Health] [int] NOT NULL
	ALTER TABLE [dbo].[TB_Pet] ADD CONSTRAINT [DF_TB_Pet_Health] DEFAULT (0) FOR [Health]

END
GO

-- Add Mental
IF  NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_Mental]') AND type = 'D')
BEGIN

	ALTER TABLE [dbo].[TB_Pet]
	ADD [Mental] [int] NOT NULL CONSTRAINT [DF_TB_Pet_Mental] DEFAULT (0)
	
END
ELSE
BEGIN

	ALTER TABLE [dbo].[TB_Pet] ALTER COLUMN [Mental] [int] NOT NULL
	ALTER TABLE [dbo].[TB_Pet] ADD CONSTRAINT [DF_TB_Pet_Mental] DEFAULT (0) FOR [Mental]
	
END
GO

IF 0 <> @@ERROR
BEGIN
		
	DECLARE @Name NVARCHAR(200)
	DECLARE tempCur CURSOR

	FOR 
	SELECT [name] FROM sysobjects
	WHERE [parent_obj] = OBJECT_ID('[dbo].[TB_Pet]') AND [xtype] = N'D'

	OPEN tempCur

	FETCH NEXT FROM tempCur INTO @Name
	WHILE @@FETCH_STATUS = 0
	BEGIN
		IF @Name LIKE '%Mental%'
		BEGIN
	
			DECLARE @SQL NVARCHAR(1000)
			SET @SQL = N'ALTER TABLE [dbo].[TB_Pet] DROP CONSTRAINT [' + @Name + ']'
			EXEC sp_executesql @SQL
			BREAK
		END
	
		FETCH NEXT FROM tempCur INTO @Name
	END

	CLOSE tempCur
	DEALLOCATE tempCur
		
	ALTER TABLE [dbo].[TB_Pet] ALTER COLUMN [Mental] [int] NOT NULL
	ALTER TABLE [dbo].[TB_Pet] ADD CONSTRAINT [DF_TB_Pet_Mental] DEFAULT (0) FOR [Mental]
	
END
GO


-- Add Color
IF  NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_Color]') AND type = 'D')
BEGIN
	ALTER TABLE [dbo].[TB_Pet]
	ADD [Color] [tinyint] NOT NULL CONSTRAINT [DF_TB_Pet_Color] DEFAULT (0)
END
GO

-- Delete SkillCoolTime
IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_SkillCoolTime]') AND type = 'D')
BEGIN
	ALTER TABLE [dbo].[TB_Pet] DROP CONSTRAINT [DF_TB_Pet_SkillCoolTime]
	ALTER TABLE [dbo].[TB_Pet] DROP COLUMN [SkillCoolTime]
END

-- Skill부분은 이전데이터 문제때문에 이렇게 정리하고 만들어야 한다.(함부로 수정하지 말것)
IF  NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_Skill01]') AND type = 'D')
BEGIN
	DECLARE @Name NVARCHAR(200)
	DECLARE tempCur CURSOR

	FOR 
	SELECT [name] FROM sysobjects
	WHERE [parent_obj] = OBJECT_ID('[dbo].[TB_Pet]') AND [xtype] = N'D'

	OPEN tempCur

	FETCH NEXT FROM tempCur INTO @Name
	WHILE @@FETCH_STATUS = 0
	BEGIN
		IF @Name LIKE '%Skill01%'
		BEGIN
	
			DECLARE @SQL NVARCHAR(1000)
			SET @SQL = N'ALTER TABLE [dbo].[TB_Pet] DROP CONSTRAINT [' + @Name + ']'
			EXEC sp_executesql @SQL
			BREAK
		END
	
		FETCH NEXT FROM tempCur INTO @Name
	END

	CLOSE tempCur
	DEALLOCATE tempCur	
END
GO

IF  NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_Skill02]') AND type = 'D')
BEGIN
	DECLARE @Name NVARCHAR(200)
	DECLARE tempCur CURSOR

	FOR 
	SELECT [name] FROM sysobjects
	WHERE [parent_obj] = OBJECT_ID('[dbo].[TB_Pet]') AND [xtype] = N'D'

	OPEN tempCur

	FETCH NEXT FROM tempCur INTO @Name
	WHILE @@FETCH_STATUS = 0
	BEGIN
		IF @Name LIKE '%Skill02%'
		BEGIN
	
			DECLARE @SQL NVARCHAR(1000)
			SET @SQL = N'ALTER TABLE [dbo].[TB_Pet] DROP CONSTRAINT [' + @Name + ']'
			EXEC sp_executesql @SQL
			BREAK
		END
	
		FETCH NEXT FROM tempCur INTO @Name
	END

	CLOSE tempCur
	DEALLOCATE tempCur
END
GO

IF  NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_Skill03]') AND type = 'D')
BEGIN
	DECLARE @Name NVARCHAR(200)
	DECLARE tempCur CURSOR

	FOR 
	SELECT [name] FROM sysobjects
	WHERE [parent_obj] = OBJECT_ID('[dbo].[TB_Pet]') AND [xtype] = N'D'

	OPEN tempCur

	FETCH NEXT FROM tempCur INTO @Name
	WHILE @@FETCH_STATUS = 0
	BEGIN
		IF @Name LIKE '%Skill03%'
		BEGIN
	
			DECLARE @SQL NVARCHAR(1000)
			SET @SQL = N'ALTER TABLE [dbo].[TB_Pet] DROP CONSTRAINT [' + @Name + ']'
			EXEC sp_executesql @SQL
			BREAK
		END
	
		FETCH NEXT FROM tempCur INTO @Name
	END

	CLOSE tempCur
	DEALLOCATE tempCur
END
GO

IF  NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_Skill01]') AND type = 'D')
BEGIN
	ALTER TABLE [dbo].[TB_Pet] DROP COLUMN [Skill01]
END
GO

IF  NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_Skill02]') AND type = 'D')
BEGIN
	ALTER TABLE [dbo].[TB_Pet] DROP COLUMN [Skill02]
END
GO

IF  NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_Skill03]') AND type = 'D')
BEGIN
	ALTER TABLE [dbo].[TB_Pet] DROP COLUMN [Skill03]
END
GO

IF  NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_Skill01]') AND type = 'D')
BEGIN
	ALTER TABLE [dbo].[TB_Pet]
	ADD [Skill01] [int] NOT NULL CONSTRAINT [DF_TB_Pet_Skill01] DEFAULT(0)
END
GO

IF  NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_Skill02]') AND type = 'D')
BEGIN
	ALTER TABLE [dbo].[TB_Pet]
	ADD [Skill02] [int] NOT NULL CONSTRAINT [DF_TB_Pet_Skill02] DEFAULT(0)
END
GO

IF  NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Pet_Skill03]') AND type = 'D')
BEGIN
	ALTER TABLE [dbo].[TB_Pet]
	ADD [Skill03] [int] NOT NULL CONSTRAINT [DF_TB_Pet_Skill03] DEFAULT(0)
END
GO

