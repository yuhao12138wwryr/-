-- 主菜单功能
function showMenu()
    -- 弹窗选项
    local choice = gg.choice({
        '1. 搜索并修改数值 (800042→4000, 10→99999)',
        '2. 退出脚本'
    }, nil, '请选择操作:')

    if choice == 1 then
        -- 执行搜索和修改
        searchAndModify()
        -- 5秒后自动恢复
        gg.sleep(5000)
        restoreValues()
    elseif choice == 2 then
        os.exit() -- 退出脚本
    end
end

-- 搜索和修改数值
function searchAndModify()
    gg.clearResults()
    gg.setRanges(gg.REGION_C_ALLOC)
    gg.searchNumber("800042;10", gg.TYPE_DOUBLE)
    local results = gg.getResults(1000)

    -- 备份原始值
    backupValues = {}
    for i, v in ipairs(results) do
        backupValues[i] = {
            address = v.address,
            value = v.value,
            flags = v.flags
        }
        -- 修改数值
        if v.value == 800042 then
            v.value = 4000
        elseif v.value == 10 then
            v.value = 99999
        end
    end

    -- 应用修改
    gg.setValues(results)
    gg.toast("数值已修改，5秒后将自动恢复")
end

-- 恢复数值
function restoreValues()
    if backupValues and #backupValues > 0 then
        gg.setValues(backupValues)
        gg.toast("数值已恢复: 4000→800042, 99999→10")
    else
        gg.toast("错误: 没有备份数据可恢复")
    end
end


-- 初始化 HTTP 请求的通用设置
function initServer(url)
    return {
        url = url,
        headers = {['Content-Type'] = 'application/json'}
    }
end
function writeData(value1, value2,path)
    local key = "mao"  -- 固定键名
    local jsonData = '{"' .. key .. '": {"x": ' .. tostring(value1) .. ', "y": ' .. tostring(value2) .. '}}'
    local response = gg.makeRequest(serverConfig.url, serverConfig.headers, jsonData)
end
function writeData2(value1, value2,path)
    local key = "yingshen"  -- 固定键名
    local jsonData = '{"' .. key .. '": {"x": ' .. tostring(value1) .. ', "y": ' .. tostring(value2) .. '}}'
    local response = gg.makeRequest(serverConfig.url, serverConfig.headers, jsonData)
end
function writeData3(value1, value2,path)
    local key = "yellow_triangle"  -- 固定键名
    local jsonData = '{"' .. key .. '": {"x": ' .. tostring(value1) .. ', "y": ' .. tostring(value2) .. '}}'
    local response = gg.makeRequest(serverConfig.url, serverConfig.headers, jsonData)
end
serverConfig = initServer('http://101.35.50.189:5000/') -- 替换为实际地址
writeData(25000,-3700,2)

-- 定义变量
local qian = 0
local hou = 0

-- 弹窗选择
local options = {
  "大模型",  -- 按钮 1
  "小模型"   -- 按钮 2
}

-- 创建弹窗
local choice = gg.choice(options, nil, "请选择模型类型")

-- 根据选择修改变量值
if choice == 1 then
    -- 大模型
    qian = 4865013498594459648
    hou = 4575657223555907584
    gg.alert("已选择大模型，qian = " .. qian .. "，hou = " .. hou)
elseif choice == 2 then
    -- 小模型
    qian = 4850658274778546176
    hou = 4575657223555907584
    gg.alert("已选择小模型，qian = " .. qian .. "，hou = " .. hou)
else
    gg.alert("未选择任何选项")
end






gg.clearResults()
-- 搜索隐身
local ysAddresses = {}
local nlAddresses = {}
-- 清除之前的搜索结果
gg.clearResults()
gg.searchNumber("4797178029190676480", gg.TYPE_QWORD, false, gg.SIGN_EQUAL, 0, -1, 0)
gg.processResume()
local results = gg.getResults(gg.getResultsCount())  -- 获取所有搜索结果
for _, result in ipairs(results) do
    -- 计算下一个地址，float 类型通常是 4 字节
    local nextAddress = result.address + 4

    -- 读取下一个地址的float值
    local nextValue = gg.getValues({{address = nextAddress, flags = gg.TYPE_FLOAT}})[1].value

    -- 判断该值是否为73.5
    if nextValue == 73.5 then
        table.insert(ysAddresses, result.address)
    end
end
-- 清除之前的搜索结果,搜素奶酪
gg.clearResults()
gg.searchNumber("4796333604261986304", gg.TYPE_QWORD, false, gg.SIGN_EQUAL, 0, -1, 0)
gg.processResume()
local results = gg.getResults(gg.getResultsCount())  -- 获取所有搜索结果
for _, result in ipairs(results) do
    -- 计算下一个地址，float 类型通常是 4 字节
    local nextAddress = result.address + 4

    -- 读取下一个地址的float值
    local nextValue = gg.getValues({{address = nextAddress, flags = gg.TYPE_FLOAT}})[1].value

    -- 判断该值是否为52.0
    if nextValue == 72 then
        table.insert(nlAddresses, result.address)
    end
end



-- 清除之前的搜索结果
gg.clearResults()

-- 执行搜索
gg.searchNumber(tostring(qian), gg.TYPE_QWORD, false, gg.SIGN_EQUAL, 0, -1, 0)
gg.processResume()
gg.refineNumber("0", gg.TYPE_QWORD, false, gg.SIGN_NOT_EQUAL, 0, -1, 0)
gg.processResume()
-- 获取搜索结果
local results = gg.getResults(9999) -- 最大获取1000个结果

-- 存储值为4865013498594459648且下一位为264的地址
local validAddresses = {}

local yuanshiAddresses = {}
local suijiAddresses = {}
local languanAddresses = {}
local huiguanAddresses = {}
-- 检查搜索结果
if #results > 0 then
    for i, result in ipairs(results) do
        -- 查找所有值为4865013498594459648的地址
        if result.value == qian then
            -- 计算下一位的地址
            local nextAddress = result.address + 88 -- 假设浮点数占4字节
            local nextAddress2 = result.address + 88 -- 假设浮点数占4字节

            -- 读取下一位的值
            local nextValue = gg.getValues{{address = nextAddress, flags = gg.TYPE_QWORD}}[1].value
            local nextValue2 = gg.getValues{{address = nextAddress2, flags = gg.TYPE_QWORD}}[1].value

            -- 判断下一位的值是否为264
            if nextValue == hou then
                -- 存储符合条件的地址
                 if nextValue2 ~= 1512.943359375 then
                    table.insert(validAddresses, result.address)
                end
            end
        end
    end
end


local file_path1 = "/storage/emulated/0/Notes/a.txt"  -- 文件路径
local file_path2 = "/storage/emulated/0/Notes/b.txt"  -- 文件路径
local file_path3 = "/storage/emulated/0/Notes/c.txt"  -- 文件路径
local file_path_yinshen = "/storage/emulated/0/Notes/yinshen.txt"  -- 文件路径
local file_path_yuanshi = "/storage/emulated/0/Notes/yuanshi.txt"  -- 文件路径
local file_path_suiji = "/storage/emulated/0/Notes/suiji.txt"  -- 文件路径
local file_path_languan = "/storage/emulated/0/Notes/languan.txt"  -- 文件路径
local file_path_huiguan = "/storage/emulated/0/Notes/huiguan.txt"  -- 文件路径



 -- 更新隐身药水坐标

for i, address_yingshen1 in ipairs(ysAddresses) do

    local yinshen_x = gg.getValues{{address = address_yingshen1-20, flags = gg.TYPE_FLOAT}}[1].value
    local yinshen_y = gg.getValues{{address = address_yingshen1 -16, flags = gg.TYPE_FLOAT}}[1].value
    writeData2(yinshen_x, yinshen_y,file_path_yinshen)
    gg.sleep(200)
    gg.sleep(50)
end
 -- 更新奶酪坐标
for i, address_nailao1 in ipairs(nlAddresses) do

    local nailao_x = gg.getValues{{address = address_nailao1-20, flags = gg.TYPE_FLOAT}}[1].value
    local nailao_y = gg.getValues{{address = address_nailao1 -16, flags = gg.TYPE_FLOAT}}[1].value
    writeData3(nailao_x, nailao_y,file_path_yinshen)
    gg.sleep(200)
    gg.sleep(50)
end

    -- 打印结果
    if #validAddresses > 2 then
    local address11=validAddresses[1]
    local address12=validAddresses[2]
    local address13=validAddresses[3]
        while true do
             local nextValue1 = gg.getValues{{address = address11 - 36, flags = gg.TYPE_FLOAT}}[1].value
             local nextValue2 = gg.getValues{{address = address11 - 32, flags = gg.TYPE_FLOAT}}[1].value
             writeData(nextValue1, nextValue2,file_path1)
             gg.sleep(100)
             local nextValue1 = gg.getValues{{address = address12 - 36, flags = gg.TYPE_FLOAT}}[1].value
             local nextValue2 = gg.getValues{{address = address12 - 32, flags = gg.TYPE_FLOAT}}[1].value
             writeData(nextValue1, nextValue2,file_path2)
             gg.sleep(100)
             local nextValue1 = gg.getValues{{address = address13 - 36, flags = gg.TYPE_FLOAT}}[1].value
             local nextValue2 = gg.getValues{{address = address13 - 32, flags = gg.TYPE_FLOAT}}[1].value
             writeData(nextValue1, nextValue2,file_path3)
             gg.sleep(100)
        end
    end
    if #validAddresses > 1 then
    local address11=validAddresses[1]
    local address12=validAddresses[2]
        while true do
              if gg.isVisible() then
                        gg.setVisible(false) -- 必须先隐藏界面
                        showMenu() -- 显示菜单
               end
             local nextValue1 = gg.getValues{{address = address11 - 36, flags = gg.TYPE_FLOAT}}[1].value
             local nextValue2 = gg.getValues{{address = address11 - 32, flags = gg.TYPE_FLOAT}}[1].value
             writeData(nextValue1, nextValue2,file_path1)
             gg.sleep(150)
             local nextValue1 = gg.getValues{{address = address12 - 36, flags = gg.TYPE_FLOAT}}[1].value
             local nextValue2 = gg.getValues{{address = address12 - 32, flags = gg.TYPE_FLOAT}}[1].value
             writeData(nextValue1, nextValue2,file_path2)
             gg.sleep(150)
        end
    end

        if #validAddresses > 0 then
        local address11=validAddresses[1]
            while true do
                    if gg.isVisible() then
                        gg.setVisible(false) -- 必须先隐藏界面
                        showMenu() -- 显示菜单
                    end
                 local nextValue1 = gg.getValues{{address = address11 - 36, flags = gg.TYPE_FLOAT}}[1].value
                 local nextValue2 = gg.getValues{{address = address11 - 32, flags = gg.TYPE_FLOAT}}[1].value
                 writeData(nextValue1, nextValue2,file_path1)


                 gg.sleep(180)
        end
    end
    if #validAddresses > 0 then
        print("Addresses where 4865013498594459648 is followed by 264:")
        for _, address in ipairs(validAddresses) do
            local nextValue1 = gg.getValues{{address = address - 36, flags = gg.TYPE_FLOAT}}[1].value
            local nextValue2 = gg.getValues{{address = address - 32, flags = gg.TYPE_FLOAT}}[1].value
            print("0x" .. string.format("%f", nextValue1))
            writeData(nextValue1, nextValue2,file_path1)
            while true do
             if gg.isVisible() then
                        gg.setVisible(false) -- 必须先隐藏界面
                        showMenu() -- 显示菜单
                    end
              local nextValue1 = gg.getValues{{address = address - 36, flags = gg.TYPE_FLOAT}}[1].value
              local nextValue2 = gg.getValues{{address = address - 32, flags = gg.TYPE_FLOAT}}[1].value
              gg.sleep(180)
              writeData(nextValue1, nextValue2,file_path1)

            end
        end
    else
        print("No matching addresses found.")
    end
