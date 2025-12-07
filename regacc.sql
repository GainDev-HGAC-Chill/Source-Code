USE DR2_Member
GO

IF NOT EXISTS (SELECT 1 FROM dbo.Member WHERE [ID] = 'jx3qwe')
BEGIN
    EXEC [dbo].[up_Web_CreateMemberAccount]
        0,                  -- @UID
        'labubu',         -- @ID  
        '123123',           -- @PW
        0,                  -- @Gender (0 = unknown)
        '1990-01-01',       -- @Birthday
        'labubu@email.com', -- @Email
        '0'                 -- @Parrain
    
    PRINT 'Account jx3qwe created successfully!'
END
ELSE
BEGIN
    PRINT 'Account jx3qwe already exists!'
END

SELECT 
    [MemberKey],
    [ID] as Username,
    [Email],
    [CreateDate],
    [State] = CASE WHEN [Block] = 0 THEN 'Active' ELSE 'Blocked' END
FROM dbo.Member 
WHERE [ID] = 'jx3qwe'