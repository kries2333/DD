function OnMission_00001()
	if lua_ExecuteTask('初涉江湖') then
		AutoWearEquipment('');
		return true
	end
	return false
end

function OnMission_00002()
	if lua_ExecuteTask('第一把武器') then
		AutoWearEquipment('')
		return true
	end
	return false
end

function OnMission_00003()
	if lua_ExecuteTask('第一件防具') then
		AutoWearEquipment('');
		return true
	end
	return false
end

function OnMission_00004()
	local taskName = '第一次杀怪'
	if task_IsAvailableTask(taskName) then
		lua_TaskAccept(taskName, '黄公道', '大理', 238, 172)
		return true
	end
	if task_IsTask(taskName) then
		if task_IsTaskSuccess(taskName) then
			lua_TaskSuccessEx(taskName, 4)
			return true
		else
			lua_AttackMonster(87, 159, '无量山', 100, '高山白猿')
			return true
		end
	end
	return false
end

function OnMission_00006()
	if lua_ExecuteTask('回访天师') then
		return true
    end
	return false
end

function OnMission_00007()
	local taskName = '初级技能'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '赵天师', '大理', 160, 156)
		return true
    end
    if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccessEx(taskName, 3)
			return true
        else
            if not skill_IsSkillName('内劲攻击') then
                lua_TaskSuccess('学习内劲攻击', '张获', '大理', 156, 129)
            end
            if not skill_IsSkillName('初级隐遁') then
                lua_TaskSuccess('学习初级隐遁', '程青霜', '大理', 163, 139)
            end
			return true
        end
    end
	return false
end

function OnMission_00008()
	if lua_ExecuteTask('灵丹妙药') then
		return true
    end
	return false
end

function OnMission_00009()
	local taskName = '剑阁猴患'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '卢三七', '大理', 103, 133)
        return true
    end
    if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccessEx(taskName, 4)
			return true
        else
            lua_AttackMonster(65, 252, '剑阁', 100, '蜀道白猿')
			return true
        end
    end
	return false
end

function OnMission_00011()
	if lua_ExecuteTask('大理怪人') then
        return true
    end
	return false
end

function OnMission_00012()
	local taskName = '何谓行善'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '段延庆', '大理', 214, 284)
        return true
    end
	if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccess(taskName, '段延庆', '大理', 214, 284)
			return true
        else --小馒头,1|衣服,2|锄头,3|
            if pack_GetBagItemNum('锄头', 2) == 0 then
                lua_TaskAccept('领取段延庆留下的东西', '黄公道', '大理', 238, 172)
				return true
            else
                if pack_GetBagItemNum('小馒头', 2) == 1 then
                    lua_TaskAccept('给小乞丐馒头', '小乞丐', '大理', 199, 255)
                    System:Sleep(1000)
                end
                if pack_GetBagItemNum('衣服', 2) == 1 then
                    lua_TaskAccept('给小乞丐衣服', '小乞丐', '大理', 199, 255)
                    System:Sleep(1000)
                end
                if pack_GetBagItemNum('锄头', 2) == 1 then
                    lua_TaskAccept('给小乞丐锄头', '小乞丐', '大理', 199, 255)
                    System:Sleep(1000)
                end
				return true
            end
        end
    end
	return false
end

function OnMission_00014()
	if lua_ExecuteTask('再访天师') then
        return true
    end
	return false
end

function OnMission_00015()
    if lua_ExecuteTask('珍兽家族') then
        return true
    end
	return false
end

function OnMission_00016()
	local taskName = '第一只珍兽'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '云飘飘', '大理', 265, 129)
		return true
    end
    if task_IsTask(taskName) then
		GoFight(0)
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccessEx(taskName, 4)
			return true
        else
            lua_AttackMonster(50, 160, '无量山', 100, '高山白猿')
			return true
        end
    end
	return false
end

function OnMission_00017()
	local taskName = '抓珍兽'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '云飘飘', '大理', 265, 129)
		return true
    end
    if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccess(taskName, '云飘飘', '大理', 265, 129)
			return true
        else
			if not PetCatch('飘飘鸭') then
                if not task_IsTaskSuccess('taskName') then
                    lua_AttackMonster(90, 70, '后花园', 100, '飘飘鸭')
					return true
                end
            end
			return true
        end
    end
	return false
end

function OnMission_00018()
	local taskName = '三访天师'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '云飘飘', '大理', 265, 129)
		return true
    end
    if task_IsTask(taskName) then
        lua_TaskSuccess(taskName, '赵天师', '大理', 160, 156)
        return true
    end
	return false
end

function OnMission_00019()
    --===========================================================
    local taskName = '喜庆焰火'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '赵天师', '大理', 160, 156)
		return true
    end
    if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccess(taskName, '赵天师', '大理', 160, 156)
			return true
        else
            if pack_GetBagItemNum('喜庆焰火') == 1 then
                if lua_MoveName(139, 169, '大理') then
                    pack_UseBagItem('喜庆焰火')
					return true
                end
            end
        end
    end
	return false
end

function OnMission_00020()
	local taskName = '大善人'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '赵天师', '大理', 160, 156)
		return true
    end
    if task_IsTask(taskName) then
        lua_TaskSuccess(taskName, '钱龙', '大理', 145, 138)
        return true
    end
	return false
end

function OnMission_00021()
	local taskName = '江湖问答'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '钱龙', '大理', 145, 138)
		return true
    end
    if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccess(taskName, '赵天师', '大理', 160, 156)
			return true
        else
            --江湖问答
            if ui_IsQuizDiaLog() then
                task_Questions()
				return true
            else
                lua_TaskAccept(taskName, '钱龙', '大理', 145, 138)
				return true
            end
        end
    end
	return false
end

function OnMission_00022()
	local taskName = '最后的试炼'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '赵天师', '大理', 160, 156)
		return true
    end
    if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccess(taskName, '赵天师', '大理', 160, 156)
			return true
        else
            lua_AttackMonster(81, 69, '小木人巷', 100, '木头人')
			return true
        end
    end
	return false
end

function OnMission_00023()
	local taskName = '十年'
    if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccess(taskName, '赵天师', '大理', 160, 156)
			AutoWearEquipment('')
			AutoDestroy('');
			return true
		end
    end
	return false
end

function OnMission_00024()
	local taskName = '九大门派'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '赵天师', '大理', 160, 156)
		return true
    end
    if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccess(taskName, '赵天师', '大理', 160, 156)
			return true
        end
    end
	return false
end

function _SMain()
	while true do
		if Stop() == false then return end
		
		if OnMission_00001() then
		elseif OnMission_00002() then
		elseif OnMission_00003() then
		elseif OnMission_00004() then
		elseif OnMission_00006() then
		elseif OnMission_00007() then
		elseif OnMission_00008() then
		elseif OnMission_00009() then
		elseif OnMission_00011() then
		elseif OnMission_00012() then
		elseif OnMission_00014() then
		elseif OnMission_00015() then
		elseif OnMission_00016() then
		elseif OnMission_00017() then
		elseif OnMission_00018() then
		elseif OnMission_00019() then
		elseif OnMission_00020() then
		elseif OnMission_00021() then
		elseif OnMission_00022() then
		elseif OnMission_00023() then
		elseif OnMission_00024() then
		else
			break
		end
		
		lua_DeathResurrection();	--死亡复活
		System:Sleep(1000)
	end
end

_SMain()