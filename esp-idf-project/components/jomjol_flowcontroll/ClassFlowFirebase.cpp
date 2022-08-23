#include <sstream>
#include "ClassFlowFirebase.h"
#include "Helper.h"
#include "connect_wlan.h"

#include "server_main.h"
#include "server_tflite.h"
#include "server_file.h"
#include "server_ota.h"
#include "server_main.h"
#include "server_camera.h"

#include "time_sntp.h"
#include "ClassFlowPostProcessing.h"

#include <time.h>

#include "json_cpp/value.h"
#include "json_cpp/json.h"

#include "esp_firebase/esp_firebase.h"

std::string resultraw = "";
std::string email = "";
std::string password = "";

void ClassFlowFirebase::SetInitialParameter(void) {
    clientname = "MeterReader";
    OldValue = "";
    email = "";
    password = "";
    flowpostprocessing = NULL; 
    previousElement = NULL;
    ListFlowControll = NULL; 
    disabled = false;
}       

ClassFlowFirebase::ClassFlowFirebase() {
    SetInitialParameter();
}

ClassFlowFirebase::ClassFlowFirebase(std::vector<ClassFlow*>* lfc) {
    SetInitialParameter();

    ListFlowControll = lfc;
    for (int i = 0; i < ListFlowControll->size(); ++i) {
        if (((*ListFlowControll)[i])->name().compare("ClassFlowPostProcessing") == 0) {
            flowpostprocessing = (ClassFlowPostProcessing*) (*ListFlowControll)[i];
        }
    }
}

ClassFlowFirebase::ClassFlowFirebase(std::vector<ClassFlow*>* lfc, ClassFlow *_prev) {
    SetInitialParameter();

    previousElement = _prev;
    ListFlowControll = lfc;

    for (int i = 0; i < ListFlowControll->size(); ++i) {
        if (((*ListFlowControll)[i])->name().compare("ClassFlowPostProcessing") == 0) {
            flowpostprocessing = (ClassFlowPostProcessing*) (*ListFlowControll)[i];
        }
    }
}


bool ClassFlowFirebase::ReadParameter(FILE* pfile, string& aktparamgraph) {
    std::vector<string> zerlegt;

    aktparamgraph = trim(aktparamgraph);

    if (aktparamgraph.size() == 0)
        if (!this->GetNextParagraph(pfile, aktparamgraph))
            return false;

    if (toUpper(aktparamgraph).compare("[FIREBASE]") != 0)
        return false;

    while (this->getNextLine(pfile, &aktparamgraph) && !this->isNewParagraph(aktparamgraph)) {
        zerlegt = this->ZerlegeZeile(aktparamgraph);
        if ((toUpper(zerlegt[0]) == "EMAIL") && (zerlegt.size() > 1)) {
            email = zerlegt[1];
            
        }  
        if ((toUpper(zerlegt[0]) == "PASSWORD") && (zerlegt.size() > 1)) {
            password = zerlegt[1];
        }               
    }
    return true;
}
/*
void task_SendToFirebase(void *pvParameter) {
    ESPFirebase::config_t config = {"AIzaSyCi1ZNbZg0MhSlGzVRI1TV54rdB_TgnNKY", "https://esp32meterreader-default-rtdb.europe-west1.firebasedatabase.app/"};
    ESPFirebase::user_account_t account = {email.c_str(), password.c_str()};

    ESPFirebase::Firebase fb_client(config);
    
    fb_client.loginUserAccount(account);
    ESP_LOGI("FIREBASE", "UID=%s", (fb_client.getUid()).c_str());
    
    std::string currentTime = gettimestring("%H %M %d %m");
    printf("Time SNTP %s\n", currentTime.c_str());
    
    Json::Value new_data; 
    new_data[currentTime.c_str()] = resultraw;
    
    std::string slash = "/";
    std::string path = slash;
    path = path + (fb_client.getUid()).c_str();
    fb_client.patchData(path.c_str(), new_data);
    fb_client.disconnectFirebase();

    printf("starting server\n");

    server = start_webserver(80);
    register_server_camera_uri(server); 
    register_server_tflite_uri(server);
    register_server_file_uri(server, "/sdcard");
    register_server_ota_sdcard_uri(server);

    gpio_handler_create(server);

    printf("vor reg server main\n");
    register_server_main_uri(server, "/sdcard");
    
    vTaskDelete(NULL); //Delete this task if it exits from the loop above
}
*/
bool ClassFlowFirebase::doFlow(string zwtime) {
    std::string result;
    string zw = "";
    string namenumber = "";

    if (flowpostprocessing) {
        std::vector<NumberPost*>* NUMBERS = flowpostprocessing->GetNumbers();

        for (int i = 0; i < (*NUMBERS).size(); ++i) {
            result = (*NUMBERS)[i]->ReturnValue;
            resultraw = (*NUMBERS)[i]->ReturnRawValue;
        }
    }
    
    OldValue = result;
    
    stop_webserver(server);
    server = NULL;
    
    ESPFirebase::config_t config = {"AIzaSyCi1ZNbZg0MhSlGzVRI1TV54rdB_TgnNKY", "https://esp32meterreader-default-rtdb.europe-west1.firebasedatabase.app/"};
    ESPFirebase::user_account_t account = {email.c_str(), password.c_str()};

    ESPFirebase::Firebase fb_client(config);
    
    fb_client.loginUserAccount(account);
    ESP_LOGI("FIREBASE", "UID=%s", (fb_client.getUid()).c_str());
    
    std::string currentTime = gettimestring("%H %M %d %m");
    printf("Time SNTP %s\n", currentTime.c_str());
    
    Json::Value new_data; 
    new_data[currentTime.c_str()] = resultraw;
    
    std::string slash = "/";
    std::string path = slash;
    path = path + (fb_client.getUid()).c_str();
    fb_client.patchData(path.c_str(), new_data);
    fb_client.disconnectFirebase();
    
    server = start_webserver();
    register_server_camera_uri(server); 
    register_server_tflite_uri(server);
    register_server_file_uri(server, "/sdcard");
    register_server_ota_sdcard_uri(server);

    gpio_handler_create(server);

    printf("vor reg server main\n");
    register_server_main_uri(server, "/sdcard");
    
    return true;
}
