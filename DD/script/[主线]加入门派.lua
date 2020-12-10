menpaiList = {
    {
        '����',
        163,
        132,
        '��̰'
    },
    {
        '����',
        96,
        51,
        '����ɽ',
        '��ʮ����'
    },
    {
        'ؤ��',
        156,
        136,
        '����'
    },
    {
        '����',
        163,
        143,
        'ʯ��'
    },
    {
        '����',
        156,
        132,
        '����'
    },
    {
        '��ɽ',
        163,
        139,
        '����˪'
    },
    {
        '�䵱',
        156,
        129,
        '�Ż�'
    },
    {
        '��ң',
        124,
        144,
        '�貨��',
        '���Ǻ�'
    },
    {
        '����',
        163,
        136,
        '������'
    }
}

local g_Master = {
    [0] = { szNpcName = "����", fX = 89, fY = 72, nSceneID = 9 },
    [1] = { szNpcName = "��ʦ��", fX = 108, fY = 56, nSceneID = 11 },
    [2] = { szNpcName = "�¹���", fX = 91, fY = 98, nSceneID = 10 },
    [3] = { szNpcName = "������", fX = 77, fY = 85, nSceneID = 12 },
    [4] = { szNpcName = "��ʮ����", fX = 96, fY = 51, nSceneID = 15 },
    [5] = { szNpcName = "������", fX = 95, fY = 75, nSceneID = 16 },
    [6] = { szNpcName = "����", fX = 96, fY = 66, nSceneID = 13 },
    [7] = { szNpcName = "÷��", fX = 91, fY = 44, nSceneID = 17 },
    [8] = { szMenPai = "��ң��", szNpcName = "���Ǻ�", fX = 125, fY = 144, nSceneID = 14 },
    [9] = { szNpcName = "", fX = 0, fY = 0, nSceneID = 0 },
    [10] = { szNpcName = "Ľ�ݽ�", fX = 48, fY = 144, nSceneID = 284 },
    [11] = { szNpcName = "�����", fX = 78, fY = 35, nSceneID = 615 },
}


function OnMission_00001() 
	local taskName = '�Ŵ�����'
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
