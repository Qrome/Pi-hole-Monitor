/** The MIT License (MIT)

Copyright (c) 2018 David Payne

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "PiHoleClient.h"

PiHoleClient::PiHoleClient() {
  //Constructor
}

void PiHoleClient::getPiHoleData(String server, int port) {
  
  HTTPClient http;
  
  String apiGetData = "http://" + server + ":" + String(port) + "/admin/api.php?summary";

  Serial.println("Getting Pi-Hole Data");
  Serial.println(apiGetData);
  http.begin(apiGetData);
  int httpCode = http.GET();

  String result = "";
  errorMessage = "";

  if (httpCode > 0) {  // checks for connection
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    if(httpCode == HTTP_CODE_OK) {
      // get length of document (is -1 when Server sends no Content-Length header)
      int len = http.getSize();
      // create buffer for read
      char buff[128] = { 0 };
      // get tcp stream
      WiFiClient * stream = http.getStreamPtr();
      // read all data from server
      Serial.println("Start reading...");
      while(http.connected() && (len > 0 || len == -1)) {
        // get available data size
        size_t size = stream->available();
        if(size) {
          // read up to 128 byte
          int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
          for(int i=0;i<c;i++) {
            result += buff[i];
          }
            
          if(len > 0)
            len -= c;
          }
        delay(1);
      }
    }
    http.end();
  } else {
    errorMessage = "Connection for Pi-Hole data failed: " + String(apiGetData);
    Serial.println(errorMessage); //error message if no client connect
    Serial.println();
    return;
  }
  //Clean dirty results
  //result.remove(0, result.indexOf("{"));
  //result.remove(result.lastIndexOf("}") + 1);
  Serial.println("Results:");
  Serial.println(result);
  Serial.println("End");

  char jsonArray [result.length()+1];
  result.toCharArray(jsonArray,sizeof(jsonArray));
  //jsonArray[result.length() + 1] = '\0';
  DynamicJsonBuffer json_buf;
  JsonObject& root = json_buf.parseObject(jsonArray);

  if (!root.success()) {
    errorMessage = "Pi-Hole Data Parsing failed!";
    Serial.println(errorMessage);
    return;
  }
  
  piHoleData.domains_being_blocked = (const char*)root["domains_being_blocked"];
  piHoleData.dns_queries_today = (const char*)root["dns_queries_today"];
  piHoleData.ads_blocked_today = (const char*)root["ads_blocked_today"];
  piHoleData.ads_percentage_today = (const char*)root["ads_percentage_today"];
  piHoleData.unique_domains = (const char*)root["unique_domains"];
  piHoleData.queries_forwarded = (const char*)root["queries_forwarded"];
  piHoleData.queries_cached = (const char*)root["queries_cached"];
  piHoleData.clients_ever_seen = (const char*)root["clients_ever_seen"];
  piHoleData.unique_clients = (const char*)root["unique_clients"];
  piHoleData.dns_queries_all_types = (const char*)root["dns_queries_all_types"];
  piHoleData.reply_NODATA = (const char*)root["reply_NODATA"];
  piHoleData.reply_NXDOMAIN = (const char*)root["reply_NXDOMAIN"];
  piHoleData.reply_CNAME = (const char*)root["reply_CNAME"];
  piHoleData.reply_IP = (const char*)root["reply_IP"];
  piHoleData.privacy_level = (const char*)root["privacy_level"];
  piHoleData.piHoleStatus = (const char*)root["status"];

  Serial.println("Pi-Hole Status: " + piHoleData.piHoleStatus);
  Serial.println("Todays Percentage Blocked: " + piHoleData.ads_percentage_today);
  Serial.println();
}

String PiHoleClient::getDomainsBeingBlocked() {
  return piHoleData.domains_being_blocked;
}

String PiHoleClient::getDnsQueriesToday() {
  return piHoleData.dns_queries_today;
}

String PiHoleClient::getAdsBlockedToday() {
  return piHoleData.ads_blocked_today;
}

String PiHoleClient::getAdsPercentageToday() {
  return piHoleData.ads_percentage_today;
}

String PiHoleClient::getUniqueClients() {
  return piHoleData.unique_clients;
}

String PiHoleClient::getClientsEverSeen() {
  return piHoleData.clients_ever_seen;
}

/* //Need to add the following
  String getUniqueDomains();
  String getQueriesForwarded();
  String getQueriesCached();
  String getDnsQueriesAllTypes();
  String getReplyNODATA();
  String getReplyNXDOMAIN();
  String getReplyCNAME();
  String getReplyIP();
  String getPrivacyLevel();
 */


String PiHoleClient::getPiHoleStatus() {
  return piHoleData.piHoleStatus;
}

String PiHoleClient::getError() {
  return errorMessage;
}
