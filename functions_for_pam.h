//
// Created by vasily on 25.09.23.
//

#ifndef SDK_FOR_TOKEN_FUNCTIONS_FOR_PAM_H
#define SDK_FOR_TOKEN_FUNCTIONS_FOR_PAM_H

#endif //SDK_FOR_TOKEN_FUNCTIONS_FOR_PAM_H
//#include <QNetworkAccessManager>
//#include <QNetworkProxy>
//#include <QNetworkReply>
//#include <QUrl>
//#include <QUrlQuery>
//#include <QJsonDocument>
//#include <boost/asio.hpp>
//#include <boost/asio/ssl.hpp>
//#include <boost/asio.hpp>
//#include <QtConcurrent/qtconcurrentrun.h>

#include <security/pam_modules.h>
#include <security/pam_appl.h>
#include <security/pam_ext.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <filesystem>
#include <pwd.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sys/types.h>
#include <csignal>
#include "httplib.h"
#include "SerialQt.h"
//#include "mongoose.h"
#include "gost_3410_2012.h"

PAM_EXTERN int pam_sm_authenticate( pam_handle_t *pamh, int flags,int argc, const char **argv );
PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv);
static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data);
static void disable_kbd_signals();
