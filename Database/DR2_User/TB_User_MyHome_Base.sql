USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_User_MyHome_Base]    Script Date: 08/12/2009 13:30:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_User_MyHome_Base](
	[StreetNo] [smallint] NOT NULL,
	[HouseNo] [smallint] NOT NULL,
	[HomePrice] [bigint] NOT NULL,
	[GroundNo] [int] NOT NULL,
	[HomeInSideGuid] [uniqueidentifier] NOT NULL,
	[HomeOutSideGuid] [uniqueidentifier] NOT NULL,
	[OwnerGuid] [uniqueidentifier] NULL,
	[EanbleVisitorBit] [tinyint] NULL,
	[x] [float] NULL,
	[y] [float] NULL,
	[z] [float] NULL,
	[AuctionTime] [datetime] NULL,
	[AuctionState] [tinyint] NULL,
	[BidderGuid] [uniqueidentifier] NULL,
	[FirstBiddingCost] [bigint] NULL,
	[LastBiddingCost] [bigint] NULL,
	[PayTexTime] [datetime] NULL,
	[PayTexNotiTime] [datetime] NULL,
	[HomeColor] [int] NULL,
	[HomeStyle] [int] NULL,
	[HomeFence] [int] NULL,
	[HomeGarden] [int] NULL,
	[TodayDay] [tinyint] NULL,
	[ToDayHitCount] [int] NULL,
	[TotalHitCount] [int] NULL,
 CONSTRAINT [PK_TB_User_MyHome_Base_1] PRIMARY KEY NONCLUSTERED 
(
	[StreetNo] ASC,
	[HouseNo] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[TB_User_MyHome_Base] ADD
[RoomWall] [int] NULL,
[RoomFloor] [int] NULL,
[AuctionLvLimitMin] [int] NULL,
[AuctionLvLimitMax] [int] NULL
GO

ALTER TABLE [dbo].[TB_User_MyHome_Base] DROP
COLUMN [x],
COLUMN [y],
COLUMN [z]
GO

CREATE CLUSTERED INDEX [IX_TB_User_MyHome_Base] ON [dbo].[TB_User_MyHome_Base] ([OwnerGuid])
GO
CREATE NONCLUSTERED INDEX [IX_TB_User_MyHome_Base_1] ON [dbo].[TB_User_MyHome_Base] ([HomeInSideGuid])
GO
CREATE NONCLUSTERED INDEX [IX_TB_User_MyHome_Base_2] ON [dbo].[TB_User_MyHome_Base] ([HomeOutSideGuid])
GO

ALTER TABLE [dbo].[TB_User_MyHome_Base] ADD
[AuctionLvLimitMin] [int] NULL,
[AuctionLvLimitMax] [int] NULL
GO

ALTER TABLE [dbo].[TB_User_MyHome_Base] DROP CONSTRAINT [PK_TB_User_MyHome_Base_1]
go
ALTER TABLE [dbo].[TB_User_MyHome_Base] ALTER COLUMN [HouseNo] [int] NOT NULL
go
ALTER TABLE [dbo].[TB_User_MyHome_Base] ADD CONSTRAINT [PK_TB_User_MyHome_Base_1] PRIMARY KEY ([StreetNo], [HouseNo])
GO

ALTER TABLE [dbo].[TB_User_MyHome_Base] ADD
[TotalVisitLogCount] [int] NULL
GO
