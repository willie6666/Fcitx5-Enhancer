#include <sdbus-c++/sdbus-c++.h>
#include <iostream>
#include "cn_xiaym_fcitx5_Fcitx5.h"

std::unique_ptr<sdbus::IConnection> connection;
std::unique_ptr<sdbus::IProxy> proxy;
std::string interface_name = "org.fcitx.Fcitx.Controller1";
std::string method_name = "CurrentInputMethod";
std::string service_name = "org.fcitx.Fcitx5";
std::string object_path = "/controller";
std::string call_dbus_method() {
    try {
        std::string output;
        proxy->callMethod(method_name).onInterface(interface_name).storeResultsTo(output);
        return output;
    } catch (const sdbus::Error& e) {
        return "";
    }
}

bool initConnection() {
    try {
        connection = sdbus::createSessionBusConnection();
        proxy = sdbus::createProxy(*connection, sdbus::ServiceName(service_name), sdbus::ObjectPath(object_path));
        return true;
    } catch (const sdbus::Error& e) {
        return false;
    }
}

extern "C" {
    JNIEXPORT jboolean JNICALL Java_cn_xiaym_fcitx5_Fcitx5_findWindow(JNIEnv *, jclass) {
        return initConnection();
    }

    JNIEXPORT jboolean JNICALL Java_cn_xiaym_fcitx5_Fcitx5_userTyping(JNIEnv *, jclass) {
        std::string result = call_dbus_method();
        return result != "keyboard-us";
    }
}
