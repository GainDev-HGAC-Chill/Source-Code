USE [DR2_local]
GO 
 
 IF  not EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='TB_DefEvent_Race') begin
	CREATE TABLE [dbo].[TB_DefEvent_Race](
		[EventNo] [int] NOT NULL,
		[Memo] [nvarchar](50) NULL,
		[Start_Effect] [int] NULL,
		[Limit_Time] [smallint] NULL,
		[Speed_Value] [smallint] NULL,
		[Skill_Use] [tinyint] NULL,
		[Race_Type] [tinyint] NULL,
		[Track_Around] [smallint] NOT NULL,
		[MP_Max] [smallint] NOT NULL,
		[Reward_Group_No1] [int] NULL,
		[Reward_Item1_1] [int] NULL,
		[Reward_Item1_2] [int] NULL,
		[Reward_Item1_3] [int] NULL,
		[Reward_Item1_4] [int] NULL,
		[Reward_Group_No2] [int] NULL,
		[Reward_Item2_1] [int] NULL,
		[Reward_Item2_2] [int] NULL,
		[Reward_Item2_3] [int] NULL,
		[Reward_Item2_4] [int] NULL,
		[Reward_Group_No3] [int] NULL,
		[Reward_Item3_1] [int] NULL,
		[Reward_Item3_2] [int] NULL,
		[Reward_Item3_3] [int] NULL,
		[Reward_Item3_4] [int] NULL,
		[Reward_Group_No4] [int] NULL,
		[Reward_Item4_1] [int] NULL,
		[Reward_Item4_2] [int] NULL,
		[Reward_Item4_3] [int] NULL,
		[Reward_Item4_4] [int] NULL,
		[Reward_Group_No5] [int] NULL,
		[Reward_Item5_1] [int] NULL,
		[Reward_Item5_2] [int] NULL,
		[Reward_Item5_3] [int] NULL,
		[Reward_Item5_4] [int] NULL,
	 CONSTRAINT [PK_TB_DefEventRace] PRIMARY KEY CLUSTERED 
	(
		[EventNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
 
end 
	
go
IF  NOT  EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='TB_DefEvent_Race' AND COLUMN_NAME='Reward_Item1_1')
BEGIN
	BEGIN TRY
	BEGIN TRAN
	create table #temp(
		[EventNo] [int] NOT NULL,
		[Memo] [nvarchar](50) NULL,
		[Start_Effect] [int] NULL,
		[Limit_Time] [smallint] NULL,
		[Speed_Value] [smallint] NULL,
		[Skill_Use] [tinyint] NULL,
		[Race_Type] [tinyint] NULL,
		[Track_Around] [smallint] NOT NULL,
		[MP_Max] [smallint] NOT NULL,
		[Reward_Group_No1] [int] NULL,
		[Reward_Item1_1] [int] NULL,
		[Reward_Item1_2] [int] NULL,
		[Reward_Item1_3] [int] NULL,
		[Reward_Item1_4] [int] NULL,
		[Reward_Group_No2] [int] NULL,
		[Reward_Item2_1] [int] NULL,
		[Reward_Item2_2] [int] NULL,
		[Reward_Item2_3] [int] NULL,
		[Reward_Item2_4] [int] NULL,
		[Reward_Group_No3] [int] NULL,
		[Reward_Item3_1] [int] NULL,
		[Reward_Item3_2] [int] NULL,
		[Reward_Item3_3] [int] NULL,
		[Reward_Item3_4] [int] NULL,
		[Reward_Group_No4] [int] NULL,
		[Reward_Item4_1] [int] NULL,
		[Reward_Item4_2] [int] NULL,
		[Reward_Item4_3] [int] NULL,
		[Reward_Item4_4] [int] NULL,
		[Reward_Group_No5] [int] NULL,
		[Reward_Item5_1] [int] NULL,
		[Reward_Item5_2] [int] NULL,
		[Reward_Item5_3] [int] NULL,
		[Reward_Item5_4] [int] NULL
	)

	INSERT INTO #temp
	(
		EventNo,Memo,Start_Effect,Limit_Time,Speed_Value,
		Skill_Use,Race_Type,Track_Around,MP_Max,
		Reward_Group_No1,Reward_Item1_1,Reward_Item1_2,Reward_Item1_3,Reward_Item1_4,
		Reward_Group_No2,Reward_Item2_1,Reward_Item2_2,Reward_Item2_3,Reward_Item2_4,
		Reward_Group_No3,Reward_Item3_1,Reward_Item3_2,Reward_Item3_3,Reward_Item3_4,
		Reward_Group_No4,Reward_Item4_1,Reward_Item4_2,Reward_Item4_3,Reward_Item4_4,
		Reward_Group_No5,Reward_Item5_1,Reward_Item5_2,Reward_Item5_3,Reward_Item5_4
	)
	SELECT 
		EventNo,Memo,Start_Effect,Limit_Time,Speed_Value,
		Skill_Use,Race_Type,Track_Around,MP_Max,
		Reward_Group_No1,Reward_Item1,0,0,0,
		Reward_Group_No2,Reward_Item2,0,0,0,
		Reward_Group_No3,Reward_Item3,0,0,0,
		Reward_Group_No4,Reward_Item4,0,0,0,
		Reward_Group_No5,Reward_Item5,0,0,0
	FROM TB_DefEvent_Race
	
	DROP TABLE [dbo].[TB_DefEvent_Race]
	
	CREATE TABLE [dbo].[TB_DefEvent_Race](
		[EventNo] [int] NOT NULL,
		[Memo] [nvarchar](50) NULL,
		[Start_Effect] [int] NULL,
		[Limit_Time] [smallint] NULL,
		[Speed_Value] [smallint] NULL,
		[Skill_Use] [tinyint] NULL,
		[Race_Type] [tinyint] NULL,
		[Track_Around] [smallint] NOT NULL,
		[MP_Max] [smallint] NOT NULL,
		[Reward_Group_No1] [int] NULL,
		[Reward_Item1_1] [int] NULL,
		[Reward_Item1_2] [int] NULL,
		[Reward_Item1_3] [int] NULL,
		[Reward_Item1_4] [int] NULL,
		[Reward_Group_No2] [int] NULL,
		[Reward_Item2_1] [int] NULL,
		[Reward_Item2_2] [int] NULL,
		[Reward_Item2_3] [int] NULL,
		[Reward_Item2_4] [int] NULL,
		[Reward_Group_No3] [int] NULL,
		[Reward_Item3_1] [int] NULL,
		[Reward_Item3_2] [int] NULL,
		[Reward_Item3_3] [int] NULL,
		[Reward_Item3_4] [int] NULL,
		[Reward_Group_No4] [int] NULL,
		[Reward_Item4_1] [int] NULL,
		[Reward_Item4_2] [int] NULL,
		[Reward_Item4_3] [int] NULL,
		[Reward_Item4_4] [int] NULL,
		[Reward_Group_No5] [int] NULL,
		[Reward_Item5_1] [int] NULL,
		[Reward_Item5_2] [int] NULL,
		[Reward_Item5_3] [int] NULL,
		[Reward_Item5_4] [int] NULL,
	 CONSTRAINT [PK_TB_DefEventRace] PRIMARY KEY CLUSTERED 
	(
		[EventNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
 
  

	INSERT INTO TB_DefEvent_Race
		(
			EventNo,Memo,Start_Effect,Limit_Time,Speed_Value,
		Skill_Use,Race_Type,Track_Around,MP_Max,
		Reward_Group_No1,Reward_Item1_1,Reward_Item1_2,Reward_Item1_3,Reward_Item1_4,
		Reward_Group_No2,Reward_Item2_1,Reward_Item2_2,Reward_Item2_3,Reward_Item2_4,
		Reward_Group_No3,Reward_Item3_1,Reward_Item3_2,Reward_Item3_3,Reward_Item3_4,
		Reward_Group_No4,Reward_Item4_1,Reward_Item4_2,Reward_Item4_3,Reward_Item4_4,
		Reward_Group_No5,Reward_Item5_1,Reward_Item5_2,Reward_Item5_3,Reward_Item5_4
	)
	SELECT 
		EventNo,Memo,Start_Effect,Limit_Time,Speed_Value,
		Skill_Use,Race_Type,Track_Around,MP_Max,
		Reward_Group_No1,Reward_Item1_1,Reward_Item1_2,Reward_Item1_3,Reward_Item1_4,
		Reward_Group_No2,Reward_Item2_1,Reward_Item2_2,Reward_Item2_3,Reward_Item2_4,
		Reward_Group_No3,Reward_Item3_1,Reward_Item3_2,Reward_Item3_3,Reward_Item3_4,
		Reward_Group_No4,Reward_Item4_1,Reward_Item4_2,Reward_Item4_3,Reward_Item4_4,
		Reward_Group_No5,Reward_Item5_1,Reward_Item5_2,Reward_Item5_3,Reward_Item5_4
	FROM #temp
	
	drop table #temp
	print('commit')
	COMMIT TRAN
	print('commit')
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		
	 print('rollback')
	END CATCH
END --end IF
 
 
  