#include "utils.h"

void checkFileInfo(string filePath, ResultStatus& status) {
    if(access(filePath.c_str(), 0) == 0) {

        status.stauts = 0;
        status.mode = EXISTS;
        status.desc = "EXISTS";

        if(access(filePath.c_str(), 2) == 0) {
            status.stauts = 0;
            status.mode = WRITEABLE;
            status.desc = "WRITEABLE";
        }

        if(access(filePath.c_str(), 4) == 0) {
            status.stauts = 0;
            status.mode = READABLE;
            status.desc = "READABLE";
        }

        if(access(filePath.c_str(), 6) == 0) {
            status.stauts = 0;
            status.mode = RWABLE;
            status.desc = "RWABLE";
        }
    } else {
        status.stauts = -1;
        status.mode = NOTEXISTS;
        status.desc = "NOTEXISTS";
    }
}

bool isExistsFile(string filePath) {
    if(access(filePath.c_str(), 0) == 0) {
        return true;
    }
    return false;
}

void read_config_Json(string fileName, map<string, string> &argvMap) {
    Json::Reader reader;
    Json::Value root;
    ifstream in;
    in.open(fileName.c_str(), std::ios_base::binary);
    if(in.is_open() == false) {
        throw runtime_error("Read Configure Json File Error !");
        cerr << "Read Configure Json File Error !" << endl;
    }
    bool flag = reader.parse(in, root, false);
    if(flag == false) {
        throw runtime_error("Configure Json File Format Error !");
        cerr << "Configure Json File Format Error !" << endl;
    }
    argvMap["LOGPATH"] = root.get("LOGPATH", "NULL").asString();
    argvMap["FUSIONSerializePath"] = root.get("FUSIONSerializePath", "NULL").asString();
    argvMap["FUSIONSerializePathBak"] = root.get("FUSIONSerializePathBak", "NULL").asString();
    argvMap["SERVERIP"] = root.get("SERVERIP", "127.0.0.1").asString();
    argvMap["PORT"] = root.get("PORT", "9999").asString();
    argvMap["FUSIONIDENTITY"] = root.get("FUSIONIDENTITY", "NULL").asString();
    argvMap["QUALTYSerializePath"] = root.get("QUALTYSerializePath", "NULL").asString();
    argvMap["QUALTYSerializePathBak"] = root.get("QUALTYSerializePathBak", "NULL").asString();
    argvMap["SERIALIZETIME"] = root.get("SERIALIZETIME", "3600").asString();
    for(map<string, string>::iterator it=argvMap.begin(); it!=argvMap.end(); it++) {
        if(it->second == "NULL") {
            cerr << it->first << " is " << it->second << endl;
            throw runtime_error("Configure Json File Parameter Error !");
        }
    }
}

