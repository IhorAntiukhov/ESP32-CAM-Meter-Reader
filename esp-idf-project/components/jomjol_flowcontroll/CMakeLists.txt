FILE(GLOB_RECURSE app_sources ${CMAKE_CURRENT_SOURCE_DIR}/*.*)

idf_component_register(SRCS ${app_sources}
                    INCLUDE_DIRS "." "../../main"
                    REQUIRES jomjol_tfliteclass jomjol_helper jomjol_controlcamera jomjol_fileserver_ota jomjol_image_proc jomjol_wlan esp_firebase json_cpp jomjol_time_sntp)


