USE [DR2_Local]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEventMonsterGroup]') )
BEGIN
	CREATE TABLE [dbo].[TB_DefEventMonsterGroup](
		[IDX] [int] IDENTITY(1,1) NOT NULL,
		[MonsterGroup] [int] NOT NULL,
		[MapNo] [int] NOT NULL,
		[MonsterNo] [int] NOT NULL,
		[PosX] [float] NOT NULL,
		[PosY] [float] NOT NULL,
		[PosZ] [float] NOT NULL,
		[RewardItemGroup] [int] NOT NULL,
		[RewardItemCount] [int] NOT NULL
	 CONSTRAINT [PK_TB_DefEventMonsterGroup] PRIMARY KEY CLUSTERED 
	(
		[IDX] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefEventMonsterGroup') and [name] = N'Order' )
BEGIN

	ALTER TABLE [dbo].[TB_DefEventMonsterGroup]
		DROP CONSTRAINT PK_TB_DefEventMonsterGroup

	CREATE TABLE [dbo].[Tmp_TB_DefEventMonsterGroup] (
		[IDX] [int] IDENTITY(1,1) NOT NULL,
		[MonsterGroup] [int] NOT NULL,
		[MapNo] [int] NOT NULL,
		[MonsterNo] [int] NOT NULL,
		[Order] [int] NOT NULL,
		[GenDelay] [int] NOT NULL,
		[MonsterLevel] [int] NOT NULL,
		[DifficultyHP] [int] NOT NULL,
		[DifficultyDamage] [int] NOT NULL,
		[DifficultyDefence] [int] NOT NULL,
		[DifficultyExp] [int] NOT NULL,
		[DifficultyAttackSpeed] [int] NOT NULL,
		[DifficultyEvade] [int] NOT NULL,
		[DifficultyHitRate] [int] NOT NULL,
		[PosX] [float] NOT NULL,
		[PosY] [float] NOT NULL,
		[PosZ] [float] NOT NULL,
		[RewardItemGroup] [int] NOT NULL,
		[RewardItemCount] [int] NOT NULL
	 CONSTRAINT [PK_TB_DefEventMonsterGroup] PRIMARY KEY CLUSTERED 
	 (
		[IDX] ASC
	 )
	 )ON [PRIMARY]
	 
	 SET IDENTITY_INSERT [dbo].[Tmp_TB_DefEventMonsterGroup] ON
	 
	 IF EXISTS (SELECT * FROM [dbo].[TB_DefEventMonsterGroup])
	 EXEC ('INSERT INTO dbo.Tmp_TB_DefEventMonsterGroup ([IDX], [MonsterGroup], [MapNo], [MonsterNo], [Order], [GenDelay], [MonsterLevel], [DifficultyHP], [DifficultyDamage], [DifficultyDefence],
														[DifficultyExp], [DifficultyAttackSpeed], [DifficultyEvade], [DifficultyHitRate], [PosX], [PosY], [PosZ], [RewardItemGroup], [RewardItemCount])
					SELECT [IDX], [MonsterGroup], [MapNo], [MonsterNo], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, [PosX], [PosY], [PosZ], [RewardItemGroup], [RewardItemCount]
					FROM dbo.TB_DefEventMonsterGroup WITH (HOLDLOCK TABLOCKX)')
	 
	 SET IDENTITY_INSERT [dbo].[Tmp_TB_DefEventMonsterGroup] OFF
	 
	 DROP TABLE TB_DefEventMonsterGroup
	 
	 EXECUTE sp_rename N'Tmp_TB_DefEventMonsterGroup', 'TB_DefEventMonsterGroup', 'OBJECT'
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefEventMonsterGroup') and [name] = N'Gen_Delay' )
BEGIN

	ALTER TABLE [dbo].[TB_DefEventMonsterGroup]
		DROP CONSTRAINT PK_TB_DefEventMonsterGroup
		
	CREATE TABLE [dbo].[Tmp_TB_DefEventMonsterGroup] (
		[IDX] [int] IDENTITY(1,1) NOT NULL,
		[MonsterGroup] [int] DEFAULT(0) NOT NULL,
		[MapNo] [int] DEFAULT(0) NOT NULL,
		[MonsterNo] [int] DEFAULT(0) NOT NULL,
		[Gen_Delay] [int] DEFAULT(0) NOT NULL,
		[Order] [int] DEFAULT(0) NOT NULL,
		[Monster_Level] [int] DEFAULT(0) NOT NULL,
		[Difficulty_HP] [int] DEFAULT(0) NOT NULL,
		[Difficulty_Damage] [int] DEFAULT(0) NOT NULL,
		[Difficulty_Defence] [int] DEFAULT(0) NOT NULL,
		[Difficulty_Exp] [int] DEFAULT(0) NOT NULL,
		[Difficulty_AttackSpeed] [int] DEFAULT(0) NOT NULL,
		[Difficulty_Evade] [int] DEFAULT(0) NOT NULL,
		[Difficulty_Hitrate] [int] DEFAULT(0) NOT NULL,
		[PosX] [float] DEFAULT(0) NOT NULL,
		[PosY] [float] DEFAULT(0) NOT NULL,
		[PosZ] [float] DEFAULT(0) NOT NULL,
		[RewardItemGroup] [int] DEFAULT(0) NOT NULL,
		[RewardItemCount] [int] DEFAULT(0) NOT NULL
	CONSTRAINT [PK_TB_DefEventMonsterGroup] PRIMARY KEY CLUSTERED
	(
		[IDX] ASC
	) 
	)ON [PRIMARY]
	 
	 SET IDENTITY_INSERT [dbo].[Tmp_TB_DefEventMonsterGroup] ON
	 
	 IF EXISTS (SELECT * FROM [dbo].[TB_DefEventMonsterGroup])
	 EXEC ('INSERT INTO dbo.Tmp_TB_DefEventMonsterGroup ([IDX], [MonsterGroup], [MapNo], [MonsterNo], [Gen_Delay], [Order], [Monster_Level], [Difficulty_HP], [Difficulty_Damage], [Difficulty_Defence],
														[Difficulty_Exp], [Difficulty_AttackSpeed], [Difficulty_Evade], [Difficulty_Hitrate], [PosX], [PosY], [PosZ], [RewardItemGroup], [RewardItemCount])
					SELECT [IDX], [MonsterGroup], [MapNo], [MonsterNo], 0, 0, 0,0, 0,0, 0, 0, 0, 0, [PosX], [PosY], [PosZ], [RewardItemGroup], [RewardItemCount]
					FROM dbo.TB_DefEventMonsterGroup WITH (HOLDLOCK TABLOCKX)')
	 
	 SET IDENTITY_INSERT [dbo].[Tmp_TB_DefEventMonsterGroup] OFF
	 
	 DROP TABLE TB_DefEventMonsterGroup
	 
	 EXECUTE sp_rename N'Tmp_TB_DefEventMonsterGroup', 'TB_DefEventMonsterGroup', 'OBJECT'
END