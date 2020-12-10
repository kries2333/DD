function OnMission_00001()
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

function OnMission_00002()
	local taskName = '宏大的江湖'
    if task_IsAvailableTask(taskName) then
        lua_TaskAccept(taskName, '赵天师', '大理', 160, 156)
		return true
    end
    if task_IsTask(taskName) then
        lua_TaskSuccessEx(taskName)
		return true
    end
	return false
end

function OnMission_00003()
	local taskName = '无量玉壁'
	if task_IsAvailableTask(taskName) then
		lua_TaskAcceptEx(taskName)
		return true
	end
	if task_IsTask(taskName) then
		if task_IsTaskSuccess(taskName) then
			lua_TaskSuccessEx(taskName, 2)
			return true
		else
			lua_MoveName(206, 59, '无量山')
			return true
		end
	end
	return false
end

function OnMission_00004()
	if lua_ExecuteTaskKill('平息骚乱', 2, 10, '山蛛') then
		return true
    end
	return false
end

function OnMission_00005()
    if lua_ExecuteTaskKill('大铁网', 2, 10, '大铁网') then
		AutoWearEquipment('')
		AutoDestroy('');
		return true
    end
	return false
end

function OnMission_00006()
    if lua_ExecuteTaskKill('炖肉', 2, 10) then
		return true
    end
	return false
end

function OnMission_00007()
    if lua_ExecuteTaskKill('修罗小鬼', 2, 10, '修罗小鬼') then
		return true
    end
	return false
end

function OnMission_00008()
    if lua_ExecuteTask('求援') then
        return true
    end
	return false
end	

function OnMission_00009()
	if lua_ExecuteTaskKill('刺杀特使', 2, 10) then
		AutoWearEquipment('')
		AutoDestroy('');
        return true
    end
	return false
end

function OnMission_00010()
    if lua_ExecuteTaskKill('闪电豹的骚扰', 2, 10, '闪电豹') then
		return true
    end
	return false
end

function OnMission_00011()
    if lua_ExecuteTask('封锁敦煌') then
        return true
    end
	return false
end

function OnMission_00012()
    if lua_ExecuteTaskKill('心愿', 2, 10) then
		AutoWearEquipment('')
        return true
    end
	return false
end

function OnMission_00013()
    if lua_ExecuteTask('微薄之力') then
        return true
    end
	return false
end

function OnMission_00014()
    if lua_ExecuteTask('蒙尘') then
        return true
    end
	return false
end

function OnMission_00015()
    if lua_ExecuteTask('营救') then
        return true
    end
	return false
end

function OnMission_00016()
    if lua_ExecuteTask('艺术') then
        return true
    end
	return false
end

function OnMission_00017()
    if lua_ExecuteTaskKill('兵俑', 2, 10, '残破兵俑') then
        return true
    end
	return false
end

function OnMission_00018()
    if lua_ExecuteTask('湮灭') then
        return true
    end
	return false
end

function OnMission_00019()
    if lua_ExecuteTask('回归') then
        return true
    end
	return false
end

function OnMission_00020()
    if lua_ExecuteTaskKill('夹击', 2, 10, '李重贵', true) then
		AutoWearEquipment('');
		AutoDestroy('');
        return true
    end
	return false
end

function OnMission_00021()
    if lua_ExecuteTask('战斗力') then
        return true
    end
	return false
end

function OnMission_00022()
    if lua_ExecuteTaskKill('荒原豹', 2, 10, '荒原豹') then
        return true
    end
	return false
end

function OnMission_00023()
    --===========================================================
    local taskName = '毅力的试炼'
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
    local taskName = '耐心的试炼'
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
    local taskName = '智慧的试炼'
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
                lua_TaskSuccess(taskName, '孙德龙', '宝藏洞一层', 175, 99)
				return true
            else
                lua_MoveName(183, 112, '宝藏洞一层')
				return true
            end
        end
        System:Sleep(1000)
    end
	return false
end	
	
function OnMission_00026()
    -- --===========================================================
    local taskName = '武艺的试炼'
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
            --打怪
            lua_AttackMonster(157, 91, '宝藏洞一层', 10, '盗墓小贼')
			return true
        end
    end
	return false
end

function OnMission_00027()
    -- --===========================================================
    local taskName = '信用的试炼'
    if task_IsAvailableTask(taskName) then
        lua_TaskAcceptEx(taskName)
        return true
    end
    if task_IsTask(taskName) then
        if role_GetMapName() == '宝藏洞一层' then
            skill_UseID(-1, 22)
            System:Sleep(25000) --回车技能需要等待长点
        end
        lua_TaskSuccessEx(taskName)

        System:Sleep(1000)
		return true
    end
	return false
end

function OnMission_00028()
	if lua_ExecuteTaskKill('遗弃木人', 2, 10) then
		return true
	end
	return false
end

function OnMission_00029()
    if lua_ExecuteTaskKill('白额虎', 2, 10) then
        return true
    end
	return false
end

function OnMission_00030()
    if lua_ExecuteTaskKill('颍水狼', 2, 10) then
		return true
    end
	return false
end

function OnMission_00031()
    if lua_ExecuteTask('接待') then
		return true
    end
	return false
end

function OnMission_00032()
    if lua_ExecuteTask('来龙去脉') then
		return true
    end
	return false
end

function OnMission_00033()
    if lua_ExecuteTask('安神药') then
		return true
    end
	return false
end

function OnMission_00034()
    if lua_ExecuteTask('回绝') then
		return true
    end
	return false
end

function OnMission_00035()
    if lua_ExecuteTaskKill('解铃人', 2, 10, '门墩') then
		return true
    end
	return false
end

function OnMission_00036()
	if lua_ExecuteTaskKill('蛛丝马迹', 2, 10, '卢崖铜人', true, '沾血的拂尘|沾血的笤帚|熄灭的蜡烛') then
		return true
    end
	return false
end
	
function OnMission_00037()
	if lua_ExecuteTask('祸起萧墙') then
        return true
	end
	return false
end

function OnMission_00038()
    if lua_ExecuteTask('学海无涯') then
        return true
    end
	return false
end

function OnMission_00039()
    if lua_ExecuteTask('金丝香囊') then
		return true
    end
	return false
end

function OnMission_00040()
    if lua_ExecuteTaskKill('驱逐恶猿', 2, 10) then
		return true
    end
	return false
end

function OnMission_00041()
    if lua_ExecuteTaskKill('驱逐铜人', 2, 10) then
		return true
    end
	return false
end

function OnMission_00042()
    if lua_ExecuteTaskKill('嵩阳断肠草', 2, 10, '铜轨', true, '嵩阳断肠草') then --捡物
		return true
    end
	return false
end

function OnMission_00043()
    --嵩山前往西湖任务  2个一起领取
    local taskName = '西域的医术'
    if task_IsAvailableTask(taskName) then
        lua_TaskAcceptEx(taskName)
        return true
    end
	return false
end

function OnMission_00044()
    if lua_ExecuteTask('丹书铁券') then
        return true
    end
    if lua_ExecuteTask('西域的医术') then
        return true
    end
	return false
end

function OnMission_00045()
    if lua_ExecuteTask('傀儡研究') then
        return true
    end
    if lua_ExecuteTask('修罗术') then
        return true
    end
	return false
end

function OnMission_00046()
    if lua_ExecuteTaskKill('花港毒蜂', 2, 10, '花港毒蜂') then
        return true
	end
    if lua_ExecuteTaskKill('水鬼探子', 2, 10, '水鬼探子') then
		return true
	end
    if lua_ExecuteTaskKill('龙井水贼', 2, 10, '龙井水贼') then
        return true
    end
    if lua_ExecuteTaskKill('断桥花妖', 2, 10, '断桥花妖', true, '刻有符印的石片') then --捡物
        return true
    end
    if lua_ExecuteTaskKill('白堤柳鬼', 2, 10, '白堤柳鬼', true, '刻有符印的树皮') then --捡物
        return true
    end
    if lua_ExecuteTaskKill('归风庄', 2, 10, '归风庄庄客', true, '刻有符印的木牌') then --捡物 无法得到物品，临时屏蔽
        return true
    end
    if lua_ExecuteTaskKill('苏飞的世界', 2, 10, '麦友仁') then
        return true
    end
    if lua_ExecuteTask('美酒歌谣') then
        return true
    end
    if lua_ExecuteTask('好兄弟') then
        return true
    end
	return false
end

function OnMission_00047()
    local taskName = '白手起家'
    if task_IsAvailableTask(taskName) then
        lua_TaskAcceptEx(taskName)
        return true
    end
    if lua_ExecuteTask('苏飞的镰刀') then
        return true
    end
    if lua_ExecuteTask('白手起家') then
       return true
    end
	return false
end
    ---洱海任务

    -- if lua_ExecuteTask('寻找草药') then
    --     System:Sleep(1000)
    -- end
function OnMission_00048()
    if lua_ExecuteTaskKill('清理野人', 2, 10) then --捡物
        return true
    end
    -- 寻找草药|清理野人|清理花斑豹|收复矿洞|收复坝子|收复茶马道|舐犊情深
    if lua_ExecuteTaskKill('清理花斑豹', 2, 10) then --捡物
        return true
    end
    if lua_ExecuteTask('舐犊情深') then
        return true
    end
    if lua_ExecuteTask('十年又十年') then
        return true
    end
	return false
end

function OnMission_00049()
    if lua_ExecuteTask('学习组队') then
        return true
    end
	return false
end

function OnMission_00050()
    --===========================================================
    local taskName = '为师门而战'
    if task_IsAvailableTask(taskName) then
        lua_TaskAcceptEx(taskName)
        return true
    end
    if task_IsTask(taskName) then
        gMenPai = role_GetRaceName()
        if gMenPai == '逍遥' then
            lua_TaskSuccess(taskName, '秦观', '凌波洞', 119, 149)
        elseif gMenPai == '峨嵋' then
            lua_TaskSuccess(taskName, '孟龙', '峨嵋山', 95, 86)
        end
        return true
    end
	return false
end

function OnMission_00051()
    if lua_ExecuteTask('援助敦煌') then
        return true
    end
    if lua_ExecuteTask('援助嵩山') then
        return true
    end
    if lua_ExecuteTask('援助西湖') then
        return true
    end
    if lua_ExecuteTask('援助洱海') then
        return true
    end
    if lua_ExecuteTask('天师的期待(1)') then
        return true
    end
	if lua_ExecuteTask('天师的期待（1）') then
        return true
    end
	if lua_ExecuteTask('天师的期待(2)') then
        return true
    end
	if lua_ExecuteTask('天师的期待（2）') then
        return true
    end
    if lua_ExecuteTask('洛阳棋圣') then
        return true
    end
    if lua_ExecuteTask('大理棋圣') then
        return true
    end
    if lua_ExecuteTask('苏州棋圣') then
        return true
    end
    if lua_ExecuteTaskKill('莫高窟', 2, 10) then
        return true
    end
    if lua_ExecuteTask('战火') then
        return true
    end
	return false
end

function OnMission_00052()
    if lua_ExecuteTaskKill('收复矿洞', 2, 10) then
        return true
    end
    if lua_ExecuteTaskKill('收复坝子', 2, 10, '狼族荆棘使') then
        return true
    end
    if lua_ExecuteTaskKill('收复茶马道', 2, 10, '狼族战士') then
        return true
    end

    -- if lua_ExecuteTask('青衫磊落险峰行') then --副本
    --     System:Sleep(1000)
    -- end
    if lua_ExecuteTask('谁家子弟谁家院') then
        return true
    end
    if lua_ExecuteTask('黑白') then
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
		
		lua_DeathResurrection();	--死亡复活
		System:Sleep(1000)
	end
end

_SMain()