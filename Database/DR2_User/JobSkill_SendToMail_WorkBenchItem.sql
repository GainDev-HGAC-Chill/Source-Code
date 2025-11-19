-- 유저 마이홈에 등록된 작업대와 작업대에 등록중인 아이템들 메일로 보내기.
USE DR2_User
GO

CREATE TABLE #temp
(
	ownerguid uniqueidentifier,
	itemno int,
	itemguid uniqueidentifier,
	cnt int
)

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_JobSkill_WorkBench_Status]') AND type in (N'U'))
BEGIN

insert  into #temp (ownerguid, itemno,itemguid, cnt)  
select ownerguid,  itemno, itemguid, cnt
	   from (
	select   h.ownerguid as ownerguid, f_itemno as itemno,newid() as itemguid, count as cnt
		from dbo.TB_JobSkill_WorkBench_Status as wb
		join TB_UserItem as ui
		on wb.f_workbenchguid = ui.itemguid
		join TB_User_MyHome_Base as h
		on ui.ownerguid = h.HomeInSideGuid
		
		union all

	select   h.ownerguid as ownerguid, f_01SlotItemno as itemno, newid() as itemguid, 1 as cnt
		from dbo.TB_JobSkill_WorkBench_Status as wb
		join TB_UserItem as ui
		on wb.f_workbenchguid = ui.itemguid
		join TB_User_MyHome_Base as h
		on ui.ownerguid = h.HomeInSideGuid
		
			union all

	select   h.ownerguid as ownerguid, f_02SlotItemno as itemno, newid() as itemguid, 1 as cnt
		from dbo.TB_JobSkill_WorkBench_Status as wb
		join TB_UserItem as ui
		on wb.f_workbenchguid = ui.itemguid
		join TB_User_MyHome_Base as h
		on ui.ownerguid = h.HomeInSideGuid
		
			union all

	select   h.ownerguid as ownerguid, f_03SlotItemno as itemno, newid() as itemguid, 1 as cnt
		from dbo.TB_JobSkill_WorkBench_Status as wb
		join TB_UserItem as ui
		on wb.f_workbenchguid = ui.itemguid
		join TB_User_MyHome_Base as h
		on ui.ownerguid = h.HomeInSideGuid
		
			union all

	select   h.ownerguid as ownerguid, f_04SlotItemno as itemno, newid() as itemguid, 1 as cnt
		from dbo.TB_JobSkill_WorkBench_Status as wb
		join TB_UserItem as ui
		on wb.f_workbenchguid = ui.itemguid
		join TB_User_MyHome_Base as h
		on ui.ownerguid = h.HomeInSideGuid
		
			union all

	select   h.ownerguid as ownerguid, f_05SlotItemno as itemno, newid() as itemguid, 1 as cnt
		from dbo.TB_JobSkill_WorkBench_Status as wb
		join TB_UserItem as ui
		on wb.f_workbenchguid = ui.itemguid
		join TB_User_MyHome_Base as h
		on ui.ownerguid = h.HomeInSideGuid
		
			union all

	select   h.ownerguid as ownerguid, f_06SlotItemno as itemno, newid() as itemguid, 1 as cnt
		from dbo.TB_JobSkill_WorkBench_Status as wb
		join TB_UserItem as ui
		on wb.f_workbenchguid = ui.itemguid
		join TB_User_MyHome_Base as h
		on ui.ownerguid = h.HomeInSideGuid
		
			union all

	select   h.ownerguid as ownerguid, f_07SlotItemno as itemno, newid() as itemguid, 1 as cnt
		from dbo.TB_JobSkill_WorkBench_Status as wb
		join TB_UserItem as ui
		on wb.f_workbenchguid = ui.itemguid
		join TB_User_MyHome_Base as h
		on ui.ownerguid = h.HomeInSideGuid
		
			union all

	select   h.ownerguid as ownerguid, f_08SlotItemno as itemno, newid() as itemguid, 1 as cnt
		from dbo.TB_JobSkill_WorkBench_Status as wb
		join TB_UserItem as ui
		on wb.f_workbenchguid = ui.itemguid
		join TB_User_MyHome_Base as h
		on ui.ownerguid = h.HomeInSideGuid
		
			union all

	select   h.ownerguid as ownerguid, f_09SlotItemno as itemno, newid() as itemguid, 1 as cnt
		from dbo.TB_JobSkill_WorkBench_Status as wb
		join TB_UserItem as ui
		on wb.f_workbenchguid = ui.itemguid
		join TB_User_MyHome_Base as h
		on ui.ownerguid = h.HomeInSideGuid
		
			union all

	select   h.ownerguid as ownerguid, f_10SlotItemno as itemno, newid() as itemguid, 1 as cnt
		from dbo.TB_JobSkill_WorkBench_Status as wb
		join TB_UserItem as ui
		on wb.f_workbenchguid = ui.itemguid
		join TB_User_MyHome_Base as h
		on ui.ownerguid = h.HomeInSideGuid
		
 ) as T
 where T.itemno>0

END


Declare @title nvarchar(50)
Declare @note nvarchar(200)
SET @title = 'return my home item'
SET @note = 'return my home item note'
 
 --메일
 INSERT INTO  [dbo].[TB_UserMail]
           ([MailGuid]
           ,[FromGuid]
           ,[ToGuid]
           ,[Title]
           ,[Note]
           ,[PaymentType]
           ,[ItemGuid]
           ,[Money]
           ,[SendTime]
           ,[LimitTime]
           ,[ReadBit]
           ,[ReturnBit]
           ,[AnnexBit]
           ,[PaymentBit]
           ,[FromName])
 SELECT
	newid() as mailid
	, ownerguid as fromid
	, ownerguid as toid
	, @title as title
	, @note as note
	, 0 as ptype
	, itemguid 
	, 0 as money
	, getdate()as stime
	, dateadd(yy, 10, getdate()) as ltime
	, 0, 0, 0, 0, null
 FROM #temp
 
 
 
 --아이템
 
 INSERT INTO [dbo].[TB_UserItem]
           ([ItemGuid]
           ,[OwnerGuid]
           ,[InvType]
           ,[InvPos]
           ,[ItemNo]
           ,[Count]
           ,[State]
           ,[CreateDate])
	SELECT 
		itemguid
		,ownerguid
		,9
		,0
		,itemno
		,cnt
		,0
 		,getdate()
 FROM #temp
   
 
 DROP TABLE #temp
  
   
-- 유저 마이홈에 등록되어 있는 가구들 삭제   
 delete TB_User_MyHome_EquipItem
 from TB_User_MyHome_EquipItem as e join dbo.TB_JobSkill_WorkBench_Status as wb
 on e.itemguid = wb.f_WorkBenchGuid
  
 delete tb_useritem
 from tb_useritem as e join dbo.TB_JobSkill_WorkBench_Status as wb
 on e.itemguid = wb.f_WorkBenchGuid
 
 truncate table TB_JobSkill_WorkBench_Status
 
 truncate table TB_JobSkill_WorkBench_Log
 
-- 추후 빌드에 테이블 제거 예정
--/****** Object:  Table [dbo].[TB_JobSkill_WorkBench_Log]    Script Date: 11/29/2012 15:51:01 ******/
--IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_JobSkill_WorkBench_Log]') AND type in (N'U'))
--DROP TABLE [dbo].[TB_JobSkill_WorkBench_Log]
--GO
--
--
--/****** Object:  Table [dbo].[TB_JobSkill_WorkBench_Status]    Script Date: 11/29/2012 15:51:45 ******/
--IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_JobSkill_WorkBench_Status]') AND type in (N'U'))
--DROP TABLE [dbo].[TB_JobSkill_WorkBench_Status]
--GO
--
--/****** Object:  Table [dbo].[TB_UserJobSkill_WB_OfflineHistory]    Script Date: 11/29/2012 16:16:22 ******/
--IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserJobSkill_WB_OfflineHistory]') AND type in (N'U'))
--DROP TABLE [dbo].[TB_UserJobSkill_WB_OfflineHistory]

GO