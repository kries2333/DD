menpaiList = {
    {
        '天龙',
        163,
        132,
        '破贪'
    },
    {
        '峨嵋',
        96,
        51,
        '峨嵋山',
        '李十二娘'
    },
    {
        '丐帮',
        156,
        136,
        '简宁'
    },
    {
        '明教',
        163,
        143,
        '石宝'
    },
    {
        '少林',
        156,
        132,
        '慧易'
    },
    {
        '天山',
        163,
        139,
        '程青霜'
    },
    {
        '武当',
        156,
        129,
        '张获'
    },
    {
        '逍遥',
        124,
        144,
        '凌波洞',
        '苏星河'
    },
    {
        '星宿',
        163,
        136,
        '海风子'
    }
}

local g_Master = {
    [0] = { szNpcName = "玄寂", fX = 89, fY = 72, nSceneID = 9 },
    [1] = { szNpcName = "吕师襄", fX = 108, fY = 56, nSceneID = 11 },
    [2] = { szNpcName = "陈孤雁", fX = 91, fY = 98, nSceneID = 10 },
    [3] = { szNpcName = "张玄素", fX = 77, fY = 85, nSceneID = 12 },
    [4] = { szNpcName = "李十二娘", fX = 96, fY = 51, nSceneID = 15 },
    [5] = { szNpcName = "韩世忠", fX = 95, fY = 75, nSceneID = 16 },
    [6] = { szNpcName = "本因", fX = 96, fY = 66, nSceneID = 13 },
    [7] = { szNpcName = "梅剑", fX = 91, fY = 44, nSceneID = 17 },
    [8] = { szMenPai = "逍遥派", szNpcName = "苏星河", fX = 125, fY = 144, nSceneID = 14 },
    [9] = { szNpcName = "", fX = 0, fY = 0, nSceneID = 0 },
    [10] = { szNpcName = "慕容杰", fX = 48, fY = 144, nSceneID = 284 },
    [11] = { szNpcName = "唐亦风", fX = 78, fY = 35, nSceneID = 615 },
}


function OnMission_00001() 
	local taskName = '九大门派'
	local nMenPai = 8
	
	if task_IsTask(taskName) then
		if task_IsTaskSuccess(taskName) then
			lua_TaskSuccessEx(taskName, 1)
			return true
		else
			if g_Master[nMenPai] == nil or nMenPai == 9 then
				return false
			end
			lua_JoinMenPai(g_Master[nMenPai].szMenPai);
			return true
		end
	end
end

function _SMain()
	while true do
		if Stop() == false then return end
		
		if OnMission_00001() then
		else
			break
		end
		
		System:Sleep(1000)
	end
end

_SMain()
