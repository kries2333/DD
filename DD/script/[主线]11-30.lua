function OnMission_00001()
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

function OnMission_00002()
	local taskName = '���Ľ���'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '����ʦ', '����', 160, 156)
		return true
    end
    if task_IsTask(taskName) then
        lua_TaskSuccessEx(taskName)
		return true
    end
	return false
end

function OnMission_00003()
	local taskName = '�������'
	if task_IsAvailableTask(taskName) then
		lua_TaskAcceptEx(taskName)
		return true
	end
	if task_IsTask(taskName) then
		if task_IsTaskSuccess(taskName) then
			lua_TaskSuccessEx(taskName, 2)
			return true
		else
			lua_MoveName(206, 59, '����ɽ')
			return true
		end
	end
	return false
end

function OnMission_00004()
	if lua_ExecuteTaskKill('ƽϢɧ��', 2, 10, 'ɽ��') then
		return true
    end
	return false
end

function OnMission_00005()
    if lua_ExecuteTaskKill('������', 2, 10, '������') then
		AutoWearEquipment('')
		AutoDestroy('');
		return true
    end
	return false
end

function OnMission_00006()
    if lua_ExecuteTaskKill('����', 2, 10) then
		return true
    end
	return false
end

function OnMission_00007()
    if lua_ExecuteTaskKill('����С��', 2, 10, '����С��') then
		return true
    end
	return false
end

function OnMission_00008()
    if lua_ExecuteTask('��Ԯ') then
        return true
    end
	return false
end	

function OnMission_00009()
	if lua_ExecuteTaskKill('��ɱ��ʹ', 2, 10) then
		AutoWearEquipment('')
		AutoDestroy('');
        return true
    end
	return false
end

function OnMission_00010()
    if lua_ExecuteTaskKill('���籪��ɧ��', 2, 10, '���籪') then
		return true
    end
	return false
end

function OnMission_00011()
    if lua_ExecuteTask('�����ػ�') then
        return true
    end
	return false
end

function OnMission_00012()
    if lua_ExecuteTaskKill('��Ը', 2, 10) then
		AutoWearEquipment('')
        return true
    end
	return false
end

function OnMission_00013()
    if lua_ExecuteTask('΢��֮��') then
        return true
    end
	return false
end

function OnMission_00014()
    if lua_ExecuteTask('�ɳ�') then
        return true
    end
	return false
end

function OnMission_00015()
    if lua_ExecuteTask('Ӫ��') then
        return true
    end
	return false
end

function OnMission_00016()
    if lua_ExecuteTask('����') then
        return true
    end
	return false
end

function OnMission_00017()
    if lua_ExecuteTaskKill('��ٸ', 2, 10, '���Ʊ�ٸ') then
        return true
    end
	return false
end

function OnMission_00018()
    if lua_ExecuteTask('����') then
        return true
    end
	return false
end

function OnMission_00019()
    if lua_ExecuteTask('�ع�') then
        return true
    end
	return false
end

function OnMission_00020()
    if lua_ExecuteTaskKill('�л�', 2, 10, '���ع�', true) then
		AutoWearEquipment('');
		AutoDestroy('');
        return true
    end
	return false
end

function OnMission_00021()
    if lua_ExecuteTask('ս����') then
        return true
    end
	return false
end

function OnMission_00022()
    if lua_ExecuteTaskKill('��ԭ��', 2, 10, '��ԭ��') then
        return true
    end
	return false
end

function OnMission_00023()
    --===========================================================
    local taskName = '����������'
    if task_IsAvailableTask(taskName) then
        lua_TaskAcceptEx(taskName)
		return true
    end
    if task_IsTask(taskName) then
        lua_TaskSuccessEx(taskName)
        return true
    end
	return false
end

function OnMission_00024()
    --===========================================================
    local taskName = '���ĵ�����'
    if task_IsAvailableTask(taskName) then
        lua_TaskAcceptEx(taskName)
		return true
    end
    if task_IsTask(taskName) then
        lua_TaskSuccessEx(taskName)
        return true
    end
	return false
end

function OnMission_00025()
    --===========================================================
    local taskName = '�ǻ۵�����'
    if task_IsAvailableTask(taskName) then
        lua_TaskAcceptEx(taskName)
        return true
    end
    if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            local fx = role_GetPosX()
			local fy = role_GetPosY()
			System:Sleep(500)
            if math.abs(fx - 183) < 5 and math.abs(fy - 112) < 5 then		
                System:Sleep(500)
                skill_UseIDPos(0x22, 185, 104)
                System:Sleep(5000)
				return true
            elseif math.abs(fx - 185) < 5 and math.abs(fy - 104) < 5 then
                System:Sleep(500)
                skill_UseIDPos(0x22, 175, 99)
                System:Sleep(5000)
				return true
            elseif math.abs(fx - 175) < 5 and math.abs(fy - 99) < 5 then
                lua_TaskSuccess(taskName, '�����', '���ض�һ��', 175, 99)
				return true
            else
                lua_MoveName(183, 112, '���ض�һ��')
				return true
            end
        end
        System:Sleep(1000)
    end
	return false
end	
	
function OnMission_00026()
    -- --===========================================================
    local taskName = '���յ�����'
    if task_IsAvailableTask(taskName) then
        lua_TaskAcceptEx(taskName)
		return true
    end
    if task_IsTask(taskName) then
        if task_IsTaskSuccess(taskName) then
            lua_TaskSuccessEx(taskName)
			AutoWearEquipment('')
			return true
        else
            --���
            lua_AttackMonster(157, 91, '���ض�һ��', 10, '��ĹС��')
			return true
        end
    end
	return false
end

function OnMission_00027()
    -- --===========================================================
    local taskName = '���õ�����'
    if task_IsAvailableTask(taskName) then
        lua_TaskAcceptEx(taskName)
        return true
    end
    if task_IsTask(taskName) then
        if role_GetMapName() == '���ض�һ��' then
            skill_UseID(-1, 22)
            System:Sleep(25000) --�س�������Ҫ�ȴ�����
        end
        lua_TaskSuccessEx(taskName)

        System:Sleep(1000)
		return true
    end
	return false
end

function OnMission_00028()
	if lua_ExecuteTaskKill('����ľ��', 2, 10) then
		return true
	end
	return false
end

function OnMission_00029()
    if lua_ExecuteTaskKill('�׶', 2, 10) then
        return true
    end
	return false
end

function OnMission_00030()
    if lua_ExecuteTaskKill('�ˮ��', 2, 10) then
		return true
    end
	return false
end

function OnMission_00031()
    if lua_ExecuteTask('�Ӵ�') then
		return true
    end
	return false
end

function OnMission_00032()
    if lua_ExecuteTask('����ȥ��') then
		return true
    end
	return false
end

function OnMission_00033()
    if lua_ExecuteTask('����ҩ') then
		return true
    end
	return false
end

function OnMission_00034()
    if lua_ExecuteTask('�ؾ�') then
		return true
    end
	return false
end

function OnMission_00035()
    if lua_ExecuteTaskKill('������', 2, 10, '�Ŷ�') then
		return true
    end
	return false
end

function OnMission_00036()
	if lua_ExecuteTaskKill('��˿��', 2, 10, '¬��ͭ��', true, 'մѪ�ķ���|մѪ������|Ϩ�������') then
		return true
    end
	return false
end
	
function OnMission_00037()
	if lua_ExecuteTask('������ǽ') then
        return true
	end
	return false
end

function OnMission_00038()
    if lua_ExecuteTask('ѧ������') then
        return true
    end
	return false
end

function OnMission_00039()
    if lua_ExecuteTask('��˿����') then
		return true
    end
	return false
end

function OnMission_00040()
    if lua_ExecuteTaskKill('�����Գ', 2, 10) then
		return true
    end
	return false
end

function OnMission_00041()
    if lua_ExecuteTaskKill('����ͭ��', 2, 10) then
		return true
    end
	return false
end

function OnMission_00042()
    if lua_ExecuteTaskKill('�����ϳ���', 2, 10, 'ͭ��', true, '�����ϳ���') then --����
		return true
    end
	return false
end

function OnMission_00043()
    --��ɽǰ����������  2��һ����ȡ
    local taskName = '�����ҽ��'
    if task_IsAvailableTask(taskName) then
        lua_TaskAcceptEx(taskName)
        return true
    end
	return false
end

function OnMission_00044()
    if lua_ExecuteTask('������ȯ') then
        return true
    end
    if lua_ExecuteTask('�����ҽ��') then
        return true
    end
	return false
end

function OnMission_00045()
    if lua_ExecuteTask('�����о�') then
        return true
    end
    if lua_ExecuteTask('������') then
        return true
    end
	return false
end

function OnMission_00046()
    if lua_ExecuteTaskKill('���۶���', 2, 10, '���۶���') then
        return true
	end
    if lua_ExecuteTaskKill('ˮ��̽��', 2, 10, 'ˮ��̽��') then
		return true
	end
    if lua_ExecuteTaskKill('����ˮ��', 2, 10, '����ˮ��') then
        return true
    end
    if lua_ExecuteTaskKill('���Ż���', 2, 10, '���Ż���', true, '���з�ӡ��ʯƬ') then --����
        return true
    end
    if lua_ExecuteTaskKill('�׵�����', 2, 10, '�׵�����', true, '���з�ӡ����Ƥ') then --����
        return true
    end
    if lua_ExecuteTaskKill('���ׯ', 2, 10, '���ׯׯ��', true, '���з�ӡ��ľ��') then --���� �޷��õ���Ʒ����ʱ����
        return true
    end
    if lua_ExecuteTaskKill('�շɵ�����', 2, 10, '������') then
        return true
    end
    if lua_ExecuteTask('���Ƹ�ҥ') then
        return true
    end
    if lua_ExecuteTask('���ֵ�') then
        return true
    end
	return false
end

function OnMission_00047()
    local taskName = '�������'
    if task_IsAvailableTask(taskName) then
        lua_TaskAcceptEx(taskName)
        return true
    end
    if lua_ExecuteTask('�շɵ�����') then
        return true
    end
    if lua_ExecuteTask('�������') then
       return true
    end
	return false
end
    ---��������

    -- if lua_ExecuteTask('Ѱ�Ҳ�ҩ') then
    --     System:Sleep(1000)
    -- end
function OnMission_00048()
    if lua_ExecuteTaskKill('����Ұ��', 2, 10) then --����
        return true
    end
    -- Ѱ�Ҳ�ҩ|����Ұ��|�����߱�|�ո���|�ո�����|�ո������|�¶�����
    if lua_ExecuteTaskKill('�����߱�', 2, 10) then --����
        return true
    end
    if lua_ExecuteTask('�¶�����') then
        return true
    end
    if lua_ExecuteTask('ʮ����ʮ��') then
        return true
    end
	return false
end

function OnMission_00049()
    if lua_ExecuteTask('ѧϰ���') then
        return true
    end
	return false
end

function OnMission_00050()
    --===========================================================
    local taskName = 'Ϊʦ�Ŷ�ս'
    if task_IsAvailableTask(taskName) then
        lua_TaskAcceptEx(taskName)
        return true
    end
    if task_IsTask(taskName) then
        gMenPai = role_GetRaceName()
        if gMenPai == '��ң' then
            lua_TaskSuccess(taskName, '�ع�', '�貨��', 119, 149)
        elseif gMenPai == '����' then
            lua_TaskSuccess(taskName, '����', '����ɽ', 95, 86)
        end
        return true
    end
	return false
end

function OnMission_00051()
    if lua_ExecuteTask('Ԯ���ػ�') then
        return true
    end
    if lua_ExecuteTask('Ԯ����ɽ') then
        return true
    end
    if lua_ExecuteTask('Ԯ������') then
        return true
    end
    if lua_ExecuteTask('Ԯ������') then
        return true
    end
    if lua_ExecuteTask('��ʦ���ڴ�(1)') then
        return true
    end
	if lua_ExecuteTask('��ʦ���ڴ���1��') then
        return true
    end
	if lua_ExecuteTask('��ʦ���ڴ�(2)') then
        return true
    end
	if lua_ExecuteTask('��ʦ���ڴ���2��') then
        return true
    end
    if lua_ExecuteTask('������ʥ') then
        return true
    end
    if lua_ExecuteTask('������ʥ') then
        return true
    end
    if lua_ExecuteTask('������ʥ') then
        return true
    end
    if lua_ExecuteTaskKill('Ī�߿�', 2, 10) then
        return true
    end
    if lua_ExecuteTask('ս��') then
        return true
    end
	return false
end

function OnMission_00052()
    if lua_ExecuteTaskKill('�ո���', 2, 10) then
        return true
    end
    if lua_ExecuteTaskKill('�ո�����', 2, 10, '���徣��ʹ') then
        return true
    end
    if lua_ExecuteTaskKill('�ո������', 2, 10, '����սʿ') then
        return true
    end

    -- if lua_ExecuteTask('���������շ���') then --����
    --     System:Sleep(1000)
    -- end
    if lua_ExecuteTask('˭���ӵ�˭��Ժ') then
        return true
    end
    if lua_ExecuteTask('�ڰ�') then
        return true
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
		elseif OnMission_00005() then
		elseif OnMission_00006() then
		elseif OnMission_00007() then
		elseif OnMission_00008() then
		elseif OnMission_00009() then
		elseif OnMission_00010() then
		elseif OnMission_00011() then
		elseif OnMission_00012() then
		elseif OnMission_00013() then
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
		elseif OnMission_00025() then
		elseif OnMission_00026() then
		elseif OnMission_00027() then
		elseif OnMission_00028() then
		elseif OnMission_00029() then
		elseif OnMission_00030() then
		elseif OnMission_00031() then
		elseif OnMission_00032() then
		elseif OnMission_00033() then
		elseif OnMission_00034() then
		elseif OnMission_00035() then
		elseif OnMission_00036() then
		elseif OnMission_00037() then
		elseif OnMission_00038() then
		elseif OnMission_00039() then
		elseif OnMission_00040() then
		elseif OnMission_00041() then
		-- elseif OnMission_00042() then
		elseif OnMission_00043() then
		elseif OnMission_00044() then
		elseif OnMission_00045() then
		elseif OnMission_00046() then
		elseif OnMission_00047() then
		elseif OnMission_00048() then
		elseif OnMission_00049() then
		elseif OnMission_00050() then
		elseif OnMission_00051() then
		elseif OnMission_00052() then
		-- elseif OnMission_00053() then
		-- elseif OnMission_00054() then
		-- elseif OnMission_00055() then
		else
			break
		end
		
		lua_DeathResurrection();	--��������
		System:Sleep(1000)
	end
end

_SMain()