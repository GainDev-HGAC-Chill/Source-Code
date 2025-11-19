 use dr2_user
 go
SET NOCOUNT ON
DECLARE @skills varchar(max)


 
SET @skills = '85000100850002008500030085000400850005008500060085000700850008008509160185091701850919018509200185092201'

DECLARE @len int    
SET @len = LEN(@skills)    

DECLARE @i int    
  
DECLARE @skillno int    
  
SET @i = 1    
 
DECLARE @targetChar table
(
    f_charguid uniqueidentifier 
)

 insert into @targetChar
  select distinct f_charguid from TB_UserJobSkill_Expertness
               where f_skillno in(
                           '85000100' , '85000200' , '85000300' , '85000400' ,  '85000500' , '85000600' , 
                           '85000700' , '85000800' ,  '85091601' , '85091701' ,  '85091901' , '85092001', 
						   '85092201'
                    )--END in

       DECLARE @c uniqueidentifier
BEGIN TRAN
BEGIN TRY
       while(@i<@len) BEGIN   
             select @skillno =CONVERT(int, SUBSTRING(@skills, @i, 8))    
              
             SET @i =@i+8   
             insert into dbo.TB_UserJobSkill_Expertness(f_charguid, f_skillno, f_expertness)
             (
             select f_charguid, @skillno , 1000000 from @targetChar where f_charguid not in(
                    select  a.f_charguid from dbo.TB_UserJobSkill_Expertness  as a
                    join @targetChar as b
                    on a.f_charguid= b.f_CharGuid 
                    where a.f_SkillNo  = @skillno 
             )
       )        
        
       END

COMMIT TRAN
print('succss')
END TRY
BEGIN CATCH
print('fail')
	ROLLBACK TRAN
END CATCH