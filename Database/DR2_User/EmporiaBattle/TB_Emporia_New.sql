SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

USE [DR2_User]
GO

-- Old Version 것은 지우기
IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Guild_Emporia_EmporiaNo]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_EmporiaPack] DROP CONSTRAINT [DF_TB_Guild_Emporia_EmporiaNo]
END
GO

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Guild_Emporia_Status]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_EmporiaPack] DROP CONSTRAINT [DF_TB_Guild_Emporia_Status]
END
GO

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Guild_Emporia_BattlePeriodsForWeeks]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_EmporiaPack] DROP CONSTRAINT [DF_TB_Guild_Emporia_BattlePeriodsForWeeks]
END
GO

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Guild_Emporia_BattleTimeMin]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_EmporiaPack] DROP CONSTRAINT [DF_TB_Guild_Emporia_BattleTimeMin]
END
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_Guild_Emporia]') AND type in (N'U'))
DROP TABLE [dbo].[TB_Guild_Emporia]
GO


IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_Guild_Emporia_ReserveBattle]') AND type in (N'U'))
DROP TABLE [dbo].[TB_Guild_Emporia_ReserveBattle]
GO


IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadGuildEmporia]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadGuildEmporia]
GO


IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_SaveGuildEmporia]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_SaveGuildEmporia]
GO


IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_SaveGuildEmporia_BattleDelete]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_SaveGuildEmporia_BattleDelete]
GO


IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_SaveGuildEmporia_BattleRefundExp]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_SaveGuildEmporia_BattleRefundExp]
GO


IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_SaveGuildEmporia_BattleReserve]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_SaveGuildEmporia_BattleReserve]
GO



-- New Version 만들기

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_EmporiaPack_State]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_EmporiaPack] DROP CONSTRAINT [DF_TB_EmporiaPack_State]
END
GO

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_EmporiaPack_BattlePeriodsForWeeks]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_EmporiaPack] DROP CONSTRAINT [DF_TB_EmporiaPack_BattlePeriodsForWeeks]
END
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_EmporiaPack]') AND type in (N'U'))
DROP TABLE [dbo].[TB_EmporiaPack]
GO

CREATE TABLE [dbo].[TB_EmporiaPack](
	[EmporiaID] [uniqueidentifier] NOT NULL,
	[State] [int] NOT NULL,
	[BattlePeriodsForWeeks] [tinyint] NOT NULL,
	[BattleID] [uniqueidentifier] NULL,
	[PrevBattleID] [uniqueidentifier] NULL,
	[BattleDate] [datetime] NULL,
	[RegistDate] [datetime] NOT NULL,
 CONSTRAINT [IX_UC_TB_EmporiaPack_EmporiaID] UNIQUE CLUSTERED 
(
	[EmporiaID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[TB_EmporiaPack] ADD  CONSTRAINT [DF_TB_EmporiaPack_State]  DEFAULT ((0)) FOR [State]
GO

ALTER TABLE [dbo].[TB_EmporiaPack] ADD  CONSTRAINT [DF_TB_EmporiaPack_BattlePeriodsForWeeks]  DEFAULT ((3)) FOR [BattlePeriodsForWeeks]
GO


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_Emporia_Status]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_Emporia] DROP CONSTRAINT [DF_TB_Emporia_Status]
END
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_Emporia]') AND type in (N'U'))
DROP TABLE [dbo].[TB_Emporia]
GO

CREATE TABLE [dbo].[TB_Emporia](
	[EmporiaID] [uniqueidentifier] NOT NULL,
	[Grade] [tinyint] NOT NULL,
	[State] [tinyint] NOT NULL,
	[OwnerGuildID] [uniqueidentifier] NULL,
	[HaveDate] [datetime] NULL,
 CONSTRAINT [IX_UC_TB_Emporia_EmporiaID] UNIQUE CLUSTERED 
(
	[EmporiaID] ASC,
	[Grade] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[TB_Emporia] ADD  CONSTRAINT [DF_TB_Emporia_State]  DEFAULT ((0)) FOR [State]
GO


IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_Emporia_ChallengeBattle]') AND type in (N'U'))
DROP TABLE [dbo].[TB_Emporia_ChallengeBattle]
GO

CREATE TABLE [dbo].[TB_Emporia_ChallengeBattle](
	[EmporiaID] [uniqueidentifier] NOT NULL,
	[BattleID] [uniqueidentifier] NOT NULL,
	[GuildID] [uniqueidentifier] NOT NULL,
	[Exp] [bigint] NOT NULL,
	[RegistDate] [datetime] NOT NULL,
	[State] [tinyint] NOT NULL,
 CONSTRAINT [IX_NC_TB_Emporia_ChallengeBattle] UNIQUE NONCLUSTERED 
(
	[EmporiaID] ASC,
	[BattleID] ASC,
	[GuildID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_Emporia_Tournament]') AND type in (N'U'))
DROP TABLE [dbo].[TB_Emporia_Tournament]
GO

CREATE TABLE [dbo].[TB_Emporia_Tournament](
	[EmporiaID] [uniqueidentifier] NOT NULL,
	[BattleID] [uniqueidentifier] NOT NULL,
	[Index] [smallint] NOT NULL,
	[BattleDate] [datetime] NOT NULL,
	[WinGuildID] [uniqueidentifier] NULL,
	[LoseGuildID] [uniqueidentifier] NULL,
 CONSTRAINT [IX_UC_TB_Emporia_Tournament] UNIQUE CLUSTERED 
(
	[EmporiaID] ASC,
	[BattleID] ASC,
	[Index] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_CreateEmporia]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_CreateEmporia]
GO

CREATE PROCEDURE [dbo].[up_CreateEmporia]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : DEF의 Emporia를 UserDB에 만드는 Procedure
// 작 성 자 : YonMy
// 작 성 일 : 2009-06-10
// 최종수정자 : 
// 수 정 일 : 
// 담 당 자 : YonMy
// N O T E : 
//
////////////////////////////////////////////////////////////////////////
*/
(
	@EmporiaID				uniqueidentifier,
	@BattlePeriodsForWeeks	tinyint
)
AS
Set Nocount on
Set Xact_Abort On

DECLARE @Err int
Set @Err = 0

BEGIN TRAN
	INSERT INTO [dbo].[TB_EmporiaPack]
	(
		[EmporiaID]
	,	[State]
	,	[BattlePeriodsForWeeks]
	,	[RegistDate]
	)
	VALUES
	(
		@EmporiaID
	,	0	-- Default값은 Close
	,	@BattlePeriodsForWeeks
	,	GetDate()
	)

	if @@ERROR <> 0
	BEGIN
		Set @Err = 1
		GOTO ErrorHandler		
	END
	ELSE
	BEGIN
		INSERT INTO [dbo].[TB_Emporia]( [EmporiaID], [Grade], [State] ) VALUES( @EmporiaID, 1, 0 )
		INSERT INTO [dbo].[TB_Emporia]( [EmporiaID], [Grade], [State] ) VALUES( @EmporiaID, 2, 0 )
		INSERT INTO [dbo].[TB_Emporia]( [EmporiaID], [Grade], [State] ) VALUES( @EmporiaID, 3, 0 )
		INSERT INTO [dbo].[TB_Emporia]( [EmporiaID], [Grade], [State] ) VALUES( @EmporiaID, 4, 0 )
		INSERT INTO [dbo].[TB_Emporia]( [EmporiaID], [Grade], [State] ) VALUES( @EmporiaID, 5, 0 )
	END

COMMIT TRAN
return @Err


ErrorHandler:
	rollback tran
	return @Err
GO


IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_SaveEmporiaPack]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_SaveEmporiaPack]
GO

CREATE PROCEDURE [dbo].[up_SaveEmporiaPack]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : up_SaveEmporiaPack
// 작 성 자 : YonMy
// 작 성 일 : 2009-06-10
// 최종수정자 : 
// 수 정 일 : 
// 담 당 자 : YonMy
// N O T E : 
//
////////////////////////////////////////////////////////////////////////
*/
(
	@EmporiaID				uniqueidentifier,
	@State					int,
	@BattlePeriodsForWeeks	tinyint,
	@BattleID				uniqueidentifier,
	@BattleDate				datetime,
	@PrevBattleID			uniqueidentifier
)
AS
SET Nocount ON
SET Xact_Abort ON

DECLARE @Err int
SET @Err = 0

UPDATE [dbo].[TB_EmporiaPack]
SET
	[State] = @State
,	[BattlePeriodsForWeeks] = @BattlePeriodsForWeeks
,	[BattleID] = @BattleID
,	[BattleDate] = @BattleDate
,	[PrevBattleID] = @PrevBattleID
WHERE [EmporiaID] = @EmporiaID

if @@ERROR <> 0
BEGIN
	SET @Err = 1		
END
	
SELECT @Err
RETURN @Err
GO


IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_SaveEmporia]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_SaveEmporia]
GO

CREATE PROCEDURE [dbo].[up_SaveEmporia]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : up_SaveEmporia
// 작 성 자 : YonMy
// 작 성 일 : 2009-06-10
// 최종수정자 : 
// 수 정 일 : 
// 담 당 자 : YonMy
// N O T E : 
//
////////////////////////////////////////////////////////////////////////
*/
(
	@EmporiaID				uniqueidentifier,
	@Grade					tinyint,
	@State					tinyint,
	@OwnerGuildID			uniqueidentifier,
	@HaveDate				datetime
)
AS
SET Nocount ON
SET Xact_Abort ON

DECLARE @Err int
SET @Err = 0

UPDATE [dbo].[TB_Emporia]
SET
	[State] = @State
,	[OwnerGuildID] = @OwnerGuildID
,	[HaveDate] = @HaveDate
WHERE [EmporiaID] = @EmporiaID AND [Grade] = @Grade

if @@ERROR <> 0
BEGIN
	SET @Err = 99	
END
	
SELECT @Err, @Grade

IF @Err = 0
BEGIN
	SELECT	[GuildGuid]
		,	[GuildName]
		,	[Emblem]
	FROM	[dbo].[TB_Guild_Basic_Info]
	WHERE	[GuildGuid] = @OwnerGuildID					
END
RETURN @Err
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_SaveEmporia_ChallengeBattle]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_SaveEmporia_ChallengeBattle]
GO

CREATE PROCEDURE [dbo].[up_SaveEmporia_ChallengeBattle]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : 엠포리아 쟁탈전 신청
// 작 성 자 : YonMy
// 작 성 일 : 2009-06-10
// 최종수정자 :
// 수 정 일 : 
// 담 당 자 : 
// N O T E : 
//
////////////////////////////////////////////////////////////////////////
*/
(
	@EmporiaID uniqueidentifier,
	@BattleID uniqueidentifier,
	@GuildID uniqueidentifier,
	@UseExp bigint,
	@RegistDate datetime,
	@State tinyint
)
AS
SET XACT_ABORT ON
SET NOCOUNT ON
SET LOCK_TIMEOUT 3000

DECLARE @Err int
Set @Err = 0

BEGIN TRAN
	DECLARE @CurrentExp BIGINT
	
	SELECT	@CurrentExp = [CurrentExp]
	FROM	[dbo].[TB_Guild_Basic_Info]
	WHERE [GuildGuid] = @GuildID
	
	IF @@ROWCOUNT = 0
	BEGIN
		SET @Err = 100
		GOTO ErrorHandler
	END
	
	IF @UseExp > @CurrentExp
	BEGIN
		SET @Err = 101
		GOTO ErrorHandler
	END
		
	INSERT INTO [dbo].[TB_Emporia_ChallengeBattle]
	(
		[EmporiaID]
	,	[BattleID]
	,	[GuildID]
	,	[Exp]
	,	[RegistDate]
	,	[State]
	)
	values
	(
		@EmporiaID
	,	@BattleID
	,	@GuildID
	,	@UseExp
	,	@RegistDate
	,	@State
	)

	if @@ERROR <> 0
	BEGIN
		Set @Err = 99
		GOTO ErrorHandler		
	END

	SET @CurrentExp = @CurrentExp - @UseExp
	
	UPDATE [dbo].[TB_Guild_Basic_Info]
	SET	[CurrentExp] = @CurrentExp
	WHERE [GuildGuid] = @GuildID

COMMIT TRAN
SELECT @Err, @CurrentExp
RETURN @Err

ErrorHandler:
ROLLBACK TRAN
SELECT @Err
RETURN @Err
GO


IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_SaveEmporia_BattleRefundExp]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_SaveEmporia_BattleRefundExp]
GO

CREATE PROCEDURE [dbo].[up_SaveEmporia_BattleRefundExp]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : 쟁탈전 경험치 환불
// 작 성 자 : YonMy
// 작 성 일 : 2009-06-10
// 최종수정자 :
// 수 정 일 :
// 담 당 자 : 
// N O T E : 
//
////////////////////////////////////////////////////////////////////////
*/
(
	@BattleID uniqueidentifier,
	@GuildID uniqueidentifier
)
AS
SET XACT_ABORT ON
SET NOCOUNT ON
SET LOCK_TIMEOUT 3000

DECLARE @Err int
Set @Err = 0

BEGIN TRAN
	DECLARE @RefundExp BIGINT
	
	SELECT	@RefundExp = [Exp]
	FROM	[dbo].[TB_Emporia_ChallengeBattle]
	WHERE	[GuildID] = @GuildID AND [BattleID] = @BattleID
	
	IF @@ERROR <> 0
	BEGIN
		SET @Err = 99
		GOTO ErrorHandler		
	END
	
	DELETE	[dbo].[TB_Emporia_ChallengeBattle]
	WHERE	[GuildID] = @GuildID AND [BattleID] = @BattleID
	
	IF @RefundExp > 0
	BEGIN
		UPDATE [dbo].[TB_Guild_Basic_Info]
		SET	[CurrentExp] = [CurrentExp] + @RefundExp
		WHERE [GuildGuid] = @GuildID
	END
	
COMMIT TRAN
SELECT	@Err, [CurrentExp]
FROM	[dbo].[TB_Guild_Basic_Info]
WHERE	[GuildGuid] = @GuildID
RETURN @Err

ErrorHandler:
ROLLBACK TRAN
SELECT @Err
RETURN @Err
GO


IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_SaveEmporia_BattleState]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_SaveEmporia_BattleState]
GO

CREATE PROCEDURE [dbo].[up_SaveEmporia_BattleState]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [up_SaveEmporia_BattleState]
// 작 성 자 : YonMy
// 작 성 일 : 2009-06-10
// 최종수정자 :
// 수 정 일 :
// 담 당 자 : 
// N O T E : 
//
////////////////////////////////////////////////////////////////////////
*/
(
	@BattleID uniqueidentifier,
	@GuildID uniqueidentifier,
	@State tinyint
)
AS
SET XACT_ABORT ON
SET NOCOUNT ON
SET LOCK_TIMEOUT 3000

DECLARE @Err int
SET @Err = 0

BEGIN
	UPDATE	[dbo].[TB_Emporia_ChallengeBattle]
	SET		[State] = @State
	WHERE	[GuildID] = @GuildID AND [BattleID] = @BattleID
	
	IF	@@ERROR <> 0
	BEGIN
		SET @Err = 99
	END
END
RETURN @Err
GO


IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_CreateEmporia_Tournament]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_CreateEmporia_Tournament]
GO

CREATE PROCEDURE [dbo].[up_CreateEmporia_Tournament]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [up_CreateEmporia_Tournament]
// 작 성 자 : YonMy
// 작 성 일 : 2009-06-10
// 최종수정자 :
// 수 정 일 :
// 담 당 자 : 
// N O T E : 
//
////////////////////////////////////////////////////////////////////////
*/
(
	@EmporiaID uniqueidentifier,
	@BattleID uniqueidentifier,
	@Index smallint,
	@BattleDate datetime
)
AS
SET XACT_ABORT ON
SET NOCOUNT ON
SET LOCK_TIMEOUT 3000

DECLARE @Err int
SET @Err = 0

BEGIN
	INSERT INTO [dbo].[TB_Emporia_Tournament]
	(
		[EmporiaID]
	,	[BattleID]
	,	[Index]
	,	[BattleDate]
	)
	VALUES
	(
		@EmporiaID
	,	@BattleID
	,	@Index
	,	@BattleDate
	)
	
	IF @@ERROR <> 0 
	BEGIN
		SET @Err = 99
	END
END
RETURN @Err
GO


IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_SaveEmporia_TournamentTime]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_SaveEmporia_TournamentTime]
GO

CREATE PROCEDURE [dbo].[up_SaveEmporia_TournamentTime]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [up_SaveEmporia_TournamentTime]
// 작 성 자 : YonMy
// 작 성 일 : 2009-06-10
// 최종수정자 :
// 수 정 일 :
// 담 당 자 : 
// N O T E : 
//
////////////////////////////////////////////////////////////////////////
*/
(
	@EmporiaID uniqueidentifier,
	@BattleID uniqueidentifier,
	@Index smallint,
	@BattleDate datetime
)
AS
SET XACT_ABORT ON
SET NOCOUNT ON
SET LOCK_TIMEOUT 3000

DECLARE @Err int
SET @Err = 0

BEGIN
	
	UPDATE	[dbo].[TB_Emporia_Tournament]
	SET		[BattleDate] = @BattleDate
	WHERE	[EmporiaID] = @EmporiaID AND [BattleID] = @BattleID AND [Index] = @Index
	
	IF @@ERROR <> 0
	BEGIN
		SET @Err = 99
	END
END
RETURN @Err
GO


IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_SaveEmporia_Tournament]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_SaveEmporia_Tournament]
GO

CREATE PROCEDURE [dbo].[up_SaveEmporia_Tournament]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [up_SaveEmporia_Tournament]
// 작 성 자 : YonMy
// 작 성 일 : 2009-06-10
// 최종수정자 :
// 수 정 일 :
// 담 당 자 : 
// N O T E : 
//
////////////////////////////////////////////////////////////////////////
*/
(
	@EmporiaID uniqueidentifier,
	@BattleID uniqueidentifier,
	@Index smallint,
	@WinGuildID uniqueidentifier,
	@LoseGuildID uniqueidentifier
)
AS
SET XACT_ABORT ON
SET NOCOUNT ON
SET LOCK_TIMEOUT 3000

DECLARE @Err int
SET @Err = 0

BEGIN
	
	UPDATE	[dbo].[TB_Emporia_Tournament]
	SET
		[WinGuildID] = @WinGuildID
	,	[LoseGuildID] = @LoseGuildID
	WHERE	[EmporiaID] = @EmporiaID AND [BattleID] = @BattleID AND [Index] = @Index
	
	IF @@ERROR <> 0
	BEGIN
		SET @Err = 99
	END
END
RETURN @Err
GO
