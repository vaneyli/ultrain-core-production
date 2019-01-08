const http = require('http');
var querystring = require('querystring');
const axios = require('axios')
var logger = require("../config/logconfig");
var IniFile = require('../common/util/iniFile');
var Constants = require('../common/constant/constants');

/**
 * nod相关交互类
 */
class NodUltrain {
}

/**
 * 更新nod配置文件
 * @param filepath
 * @param monitorServer
 * @returns {boolean}
 */
NodUltrain.updateConfig = function (filepath, monitorServer) {
    try {
        var iniFile = new IniFile(filepath, Constants.encodingConstants.UTF8);
        iniFile.setValue("monitor-server-endpoint", monitorServer);
        iniFile.writefile(filepath, Constants.encodingConstants.UTF8);
        return true;
    } catch (e) {
        logger.error("update nodultrain config file error: ", e)
        return false;
    }
}



module.exports = NodUltrain;