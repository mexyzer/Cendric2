-- Dialogue for NPC "npc_luv"
loadDialogue = function(DL) 

	if (not (DL:isConditionFulfilled("npc_lee", "what_doing") and DL:isConditionFulfilled("npc_luv", "who_are_you"))) then 
		DL:setRoot(1) 
	elseif (not DL:isConditionFulfilled("npc_leeluv", "second_rant")) then 
		DL:setRoot(4) 
	elseif (DL:isConditionFulfilled("npc_luv", "thanks") and not DL:isConditionFulfilled("npc_leeluv", "thanks")) then 
		DL:setRoot(14) 
	else 
		DL:setRoot(7) 
	end 

	if (not (DL:isConditionFulfilled("npc_lee", "what_doing") and DL:isConditionFulfilled("npc_luv", "who_are_you"))) then 

		DL:createChoiceNode(1)
		if (not DL:isConditionFulfilled("npc_luv", "who_are_you")) then 
			DL:addChoice(2, "DL_Choice_WhoAreYou") -- Who are you?
		end
		DL:addChoice(-1, "") -- 
		DL:addNode()

		if (not DL:isConditionFulfilled("npc_luv", "who_are_you")) then 

			DL:createNPCNode(2, 3, "DL_Luv_WhoAreYou") -- I'm Luv, a sailor. Normally, I'd sail on the sea instead of sitting here.
			DL:addConditionProgress("npc_luv", "who_are_you")
			DL:addNode()


			DL:createNPCNode(3, -2, "DL_Luv_WhoAreYou2") -- And if it wasn't for that idiot Lee, I would still be with my crew on our ship.
			DL:addNode()

		end

	end

	if (not DL:isConditionFulfilled("npc_leeluv", "second_rant")) then 

		DL:createChoiceNode(4)
		if (not DL:isConditionFulfilled("npc_lee", "first_rant") and not DL:isConditionFulfilled("npc_luv", "first_rant")) then 
			DL:addChoice(5, "DL_Choice_FirstRant") -- Your mate told me you're the one to blame.
		end
		if (DL:isConditionFulfilled("npc_lee", "first_rant")) then 
			DL:addChoice(6, "DL_Choice_SecondRant") -- Your mate says you shouldn't have gotten drunk.
		end
		DL:addChoice(-1, "") -- 
		DL:addNode()

		if (not DL:isConditionFulfilled("npc_lee", "first_rant") and not DL:isConditionFulfilled("npc_luv", "first_rant")) then 

			DL:createNPCNode(5, -2, "DL_Luv_OtherSays") -- Oh yeah, did he? Well you can tell him that we would have made it if he wasn't drunk when our ship cast off.
			DL:addConditionProgress("npc_luv", "first_rant")
			DL:addNode()

		end

		if (DL:isConditionFulfilled("npc_lee", "first_rant")) then 

			DL:createNPCNode(6, -2, "DL_Luv_SecondRant") -- Pha! If he wouldn't have slept when our captain called our sailors back, we wouldn't have missed it either!
			DL:addConditionProgress("npc_leeluv", "second_rant")
			DL:addNode()

		end

	end

	if (DL:isConditionFulfilled("npc_luv", "thanks") and not DL:isConditionFulfilled("npc_leeluv", "thanks")) then 

		DL:createNPCNode(14, -1, "DL_Luv_Thanks") -- Thanks!
		DL:addConditionProgress("npc_leeluv", "thanks")
		DL:addNode()

	end


	DL:createChoiceNode(7)
	if (not DL:isConditionFulfilled("npc_leeluv", "calm_down")) then 
		DL:addChoice(8, "DL_Choice_CalmDown") -- I think you both should calm down.
	end
	if (DL:isConditionFulfilled("npc_leeluv", "calm_down") and DL:isQuestState("lee_and_luv", "void")) then 
		DL:addChoice(11, "DL_Choice_HelpYou") -- Maybe I could help you.
	end
	if (DL:isQuestState("lee_and_luv", "started") and DL:isQuestComplete("lee_and_luv")) then 
		DL:addChoice(12, "DL_Choice_QuestComplete") -- I got a compass for you.
	end
	DL:addChoice(-1, "") -- 
	DL:addNode()

	if (not DL:isConditionFulfilled("npc_leeluv", "calm_down")) then 

		DL:createNPCNode(8, 9, "DL_Luv_CalmDown") -- Yes maybe you're right. This doesn't bring us anywhere.
		DL:addNode()


		DL:createNPCNode(9, 10, "DL_Luv_CalmDown2") -- We know where our captain wanted to sail and we could buy a small boat here.
		DL:addNode()


		DL:createNPCNode(10, -2, "DL_Luv_CalmDown3") -- But to sail over the sea, we'd need a compass and nobody in this damn city seems to have one.
		DL:addConditionProgress("npc_leeluv", "calm_down")
		DL:addNode()

	end

	if (DL:isConditionFulfilled("npc_leeluv", "calm_down") and DL:isQuestState("lee_and_luv", "void")) then 

		DL:createNPCNode(11, -2, "DL_Luv_HelpYou") -- Yes maybe. If you could get us a working compass, we'd give you all we have left.
		DL:changeQuestState("lee_and_luv", "started")
		DL:addNode()

	end

	if (DL:isQuestState("lee_and_luv", "started") and DL:isQuestComplete("lee_and_luv")) then 

		DL:createNPCNode(12, 13, "DL_Luv_QuestComplete") -- Awesome! Thank you so much, I can't wait to set sails! 
		DL:changeQuestState("lee_and_luv", "completed")
		DL:addConditionProgress("npc_leeluv", "gone")
		DL:removeItem("qe_compass", 1)
		DL:addConditionProgress("npc_lee", "thanks")
		DL:addNode()


		DL:createNPCNode(13, -2, "DL_Luv_QuestComplete2") -- Here, take this pile of magical pearls we found, they are worth a lot here!
		DL:addItem("mi_pearlpile", 1)
		DL:addNode()

	end

end