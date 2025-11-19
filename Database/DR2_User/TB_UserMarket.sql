USE DR2_USER
GO

alter table TB_UserMarket
drop constraint DF_TB_UserMarket_ItemState
go
alter table TB_UserMarket
drop constraint DF_TB_UserMarket_ItemGenTime
go
--테이블TB_UserMarket 컬럼ItemNo, ItemNum, Enchant_01,Enchant_02, ItemState, ItemGenTime을제거
alter table TB_UserMarket
drop column ItemNo, ItemNum, Enchant_01,Enchant_02, ItemState, ItemGenTime
go