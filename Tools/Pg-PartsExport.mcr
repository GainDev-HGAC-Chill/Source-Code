-- EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
--
-- This software is supplied under the terms of a license agreement or
-- nondisclosure agreement with Emergent Game Technologies and may not
-- be copied or disclosed except in accordance with the terms of that
-- agreement.
--
--      Copyright (c) 1996-2006 Emergent Game Technologies.
--      All Rights Reserved.
--
-- Emergent Game Technologies, Chapel Hill, North Carolina 27517
-- http://www.emergent.net
-----------------------------------------------------------------------------

macroscript PgPartExport category:"Gamebryo Tools" 
	buttonText:"Pg Parts Export" toolTip:"Pg Parts Export" Icon:#("Gamebryo", 11)
(
	function pg_select_grands child =
	(
		while child.name != "char_root" do
		(
			child = child.parent
			selectmore child
		)
	)

	function pg_select_bones obj =
	(
		bs = physiqueOps.GetBones obj
	
		for b in bs do
		(
			selectmore b
			pg_select_grands b
		)
	)
	
	on execute do
	(
		for o in selection do
		(
			for m in o.modifiers do
			(
				if m.name == "Physique" then
					pg_select_bones o
			)
		)
		
		max file export selected
	)
)
