function OnMission_00001()
	if lua_ExecuteTask('���潭��') then
		AutoWearEquipment('');
		return true
	end
	return false
end

function OnMission_00002()
	if lua_ExecuteTask('��һ������') then
		AutoWearEquipment('')
		return true
	end
	return false
end

function OnMission_00003()
	if lua_ExecuteTask('��һ������') then
		AutoWearEquipment('');
		return true
	end
	return false
end

function OnMission_00004()
	local taskName = '��һ��ɱ��'
	if task_IsAvailableTask(taskName) then
		lua_TaskAccept(taskName, '�ƹ���', '����', 238, 172)
		return true
	end
	if task_IsTask(taskName) then
		if task_IsTaskSuccess(taskName) then
			lua_TaskSuccessEx(taskName, 4)
			return true
		else
			lua_AttackMonster(87, 159, '����ɽ', 100, '��ɽ��Գ')
			return true
		end
	end
	return false
end

function OnMission_00006()
	if lua_ExecuteTask('�ط���ʦ') then
		return true
    end
	return false
end

function OnMission_00007()
	local taskName = '��������'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '����ʦ', '����', 160, 156)
		return true
    end
    if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccessEx(taskName, 3)
			return true
        else
            if not skill_IsSkillName('�ھ�����') then
                lua_TaskSuccess('ѧϰ�ھ�����', '�Ż�', '����', 156, 129)
            end
            if not skill_IsSkillName('��������') then
                lua_TaskSuccess('ѧϰ��������', '����˪', '����', 163, 139)
            end
			return true
        end
    end
	return false
end

function OnMission_00008()
	if lua_ExecuteTask('�鵤��ҩ') then
		return true
    end
	return false
end

function OnMission_00009()
	local taskName = '����ﻼ'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '¬����', '����', 103, 133)
        return true
    end
    if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccessEx(taskName, 4)
			return true
        else
            lua_AttackMonster(65, 252, '����', 100, '�����Գ')
			return true
        end
    end
	return false
end

function OnMission_00011()
	if lua_ExecuteTask('�������') then
        return true
    end
	return false
end

function OnMission_00012()
	local taskName = '��ν����'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '������', '����', 214, 284)
        return true
    end
	if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccess(taskName, '������', '����', 214, 284)
			return true
        else --С��ͷ,1|�·�,2|��ͷ,3|
            if pack_GetBagItemNum('��ͷ', 2) == 0 then
                lua_TaskAccept('��ȡ���������µĶ���', '�ƹ���', '����', 238, 172)
				return true
            else
                if pack_GetBagItemNum('С��ͷ', 2) == 1 then
                    lua_TaskAccept('��С��ؤ��ͷ', 'С��ؤ', '����', 199, 255)
                    System:Sleep(1000)
                end
                if pack_GetBagItemNum('�·�', 2) == 1 then
                    lua_TaskAccept('��С��ؤ�·�', 'С��ؤ', '����', 199, 255)
                    System:Sleep(1000)
                end
                if pack_GetBagItemNum('��ͷ', 2) == 1 then
                    lua_TaskAccept('��С��ؤ��ͷ', 'С��ؤ', '����', 199, 255)
                    System:Sleep(1000)
                end
				return true
            end
        end
    end
	return false
end

function OnMission_00014()
	if lua_ExecuteTask('�ٷ���ʦ') then
        return true
    end
	return false
end

function OnMission_00015()
    if lua_ExecuteTask('���޼���') then
        return true
    end
	return false
end

function OnMission_00016()
	local taskName = '��һֻ����'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '��ƮƮ', '����', 265, 129)
		return true
    end
    if task_IsTask(taskName) then
		GoFight(0)
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccessEx(taskName, 4)
			return true
        else
            lua_AttackMonster(50, 160, '����ɽ', 100, '��ɽ��Գ')
			return true
        end
    end
	return false
end

function OnMission_00017()
	local taskName = 'ץ����'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '��ƮƮ', '����', 265, 129)
		return true
    end
    if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccess(taskName, '��ƮƮ', '����', 265, 129)
			return true
        else
			if not PetCatch('ƮƮѼ') then
                if not task_IsTaskSuccess('taskName') then
                    lua_AttackMonster(90, 70, '��԰', 100, 'ƮƮѼ')
					return true
                end
            end
			return true
        end
    end
	return false
end

function OnMission_00018()
	local taskName = '������ʦ'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '��ƮƮ', '����', 265, 129)
		return true
    end
    if task_IsTask(taskName) then
        lua_TaskSuccess(taskName, '����ʦ', '����', 160, 156)
        return true
    end
	return false
end

function OnMission_00019()
    --===========================================================
    local taskName = 'ϲ�����'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '����ʦ', '����', 160, 156)
		return true
    end
    if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccess(taskName, '����ʦ', '����', 160, 156)
			return true
        else
            if pack_GetBagItemNum('ϲ�����') == 1 then
                if lua_MoveName(139, 169, '����') then
                    pack_UseBagItem('ϲ�����')
					return true
                end
            end
        end
    end
	return false
end

function OnMission_00020()
	local taskName = '������'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '����ʦ', '����', 160, 156)
		return true
    end
    if task_IsTask(taskName) then
        lua_TaskSuccess(taskName, 'Ǯ��', '����', 145, 138)
        return true
    end
	return false
end

function OnMission_00021()
	local taskName = '�����ʴ�'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, 'Ǯ��', '����', 145, 138)
		return true
    end
    if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccess(taskName, '����ʦ', '����', 160, 156)
			return true
        else
            --�����ʴ�
            if ui_IsQuizDiaLog() then
                task_Questions()
				return true
            else
                lua_TaskAccept(taskName, 'Ǯ��', '����', 145, 138)
				return true
            end
        end
    end
	return false
end

function OnMission_00022()
	local taskName = '��������'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '����ʦ', '����', 160, 156)
		return true
    end
    if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccess(taskName, '����ʦ', '����', 160, 156)
			return true
        else
            lua_AttackMonster(81, 69, 'Сľ����', 100, 'ľͷ��')
			return true
        end
    end
	return false
end

function OnMission_00023()
	local taskName = 'ʮ��'
    if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccess(taskName, '����ʦ', '����', 160, 156)
			AutoWearEquipment('')
			AutoDestroy('');
			return true
		end
    end
	return false
end

function OnMission_00024()
	local taskName = '�Ŵ�����'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '����ʦ', '����', 160, 156)
		return true
    end
    if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccess(taskName, '����ʦ', '����', 160, 156)
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
		
		lua_DeathResurrection();	--��������
		System:Sleep(1000)
	end
end

_SMain()