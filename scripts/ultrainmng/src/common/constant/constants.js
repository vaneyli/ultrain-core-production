/**
 * 命令相关常量
 *
 * @type {{KILL_NODULTRAIN: string, KILL_WORLDSTATE: string}}
 */
var cmdConstants = {

    KILL_NODULTRAIN: "killall 'nodultrain'",//关闭nodultrain
    KILL_WORLDSTATE: "killall 'wss'", //关闭世界状态进程
    KILL_PM2: "killall 'pm2'",//关闭pm2
    PM2_LIST: "/usr/local/bin/pm2 list",//pm2 list
    CLEAR_BLOCK_DATA: "rm -rf /root/.local/share/ultrainio/nodultrain/data/blocks/",//清空本地块数据
    CLEAR_SHARED_MEMORY_DATA: "rm -rf /root/.local/share/ultrainio/nodultrain/data/state/",//清空memory.bin数据
    CLEAR_WORLD_STATE_FILE: "rm -rf /root/.local/share/ultrainio/nodultrain/data/worldstate/data/", //清空ws下文件
    START_WORLDSTATE : "/root/workspace/ultrain-core/build/programs/wssultrain/wssultrain --http-server-address 127.0.0.1:7777 --p2p-listen-endpoint 0.0.0.0:7272",//启动世界状态程序
    START_NODULTRAIN: "sh /root/workspace/ultrain-core/scripts/_runultrain.sh /root/workspace",//启动nod程序
}

//编码常量
var encodingConstants = {
    UTF8: "UTF-8",
    GBK: "GBK",
}


module.exports = {
    cmdConstants,
    encodingConstants
}