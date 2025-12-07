use [DR2_SiteConfig]

update TB_Realm set MachineIP = 'replace-with-server-lan-ip' where MachineIP = 'old-ip'
update TB_Realm set ServerBindIP = 'replace-with-server-lan-ip' where ServerBindIP = 'old-ip'
update TB_Realm set UserBindIP = 'replace-with-server-lan-ip' where UserBindIP = 'old-ip'

update TB_SiteServer set MachineIP = 'replace-with-server-lan-ip' where MachineIP = 'old-ip'
update TB_SiteServer set ServerBindIP = 'replace-with-server-lan-ip' where ServerBindIP = 'old-ip'
update TB_SiteServer set UserBindIP = 'replace-with-server-lan-ip' where UserBindIP = 'old-ip'
