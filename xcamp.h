#include <WiFi.h>
#include <PubSubClient.h>
#include <vector>
#include <ArduinoJson.h>
//
//  linkList.h
//
//  Created by Kiarash on 12/2/17.
//  Edited by Sepehr on 12/17/17.
//  Copyright © 2017 Kiarash. All rights reserved.
//

#ifndef linkList_h
#define linkList_h

using namespace std;
// typedef bitset<8> byte;

template <typename T>
struct node
{
    T data;
    node *next;
    
    ~node(){
        data = NULL;
    }
};

template <class T>
class list
{
private:
    node<T> *head, *tail;
public:
    list();
    ~list();

    void append(T value);
    // void display();
    void insertStart(T value);
    void addNewValueAtIndex(int pos, T value);
    void setValueForIndex(int index, T value);
    void deleteFirst();
    void deleteLast();
    void deleteValueAtIndex(int pos);
    T valueForIndex(int index);
    int length();
};





template <class T>
list<T>::list(){
    head=NULL;
    tail=NULL;
}

template <class T>
list<T>::~list(){
    node<T> *current;
    node<T> *previous;
    current=head;
    while(current!=NULL)
    {
        previous=current;
        current=current->next;
        delete previous;
    }
    current = NULL;
    previous = NULL;
    head = NULL;
    tail = NULL;
}

template <class T>
void list<T>::append(T value){
    node<T> *temp=new node<T>;
    temp->data=value;
    temp->next=NULL;
    
    if(head==NULL){
        head=temp;
        tail=temp;
        temp=NULL;
    }
    else{
        tail->next=temp;
        tail=temp;
    }
}

// template <class T>
// void list<T>::display(){
//     node<T> *temp=new node<T>;
//     temp=head;
//     while(temp!=NULL)
//     {
//         cout<<temp->data<<"\t";
//         //        Serial.print(temp->data);
//         //        Serial.print(" ");
//         temp=temp->next;
//     }
//     //    Serial.print("\n");
//     temp = NULL;
// }

template <class T>
void list<T>::insertStart(T value){
    node<T> *temp=new node<T>;
    temp->data=value;
    temp->next=head;
    head=temp;
}


template <class T>
void list<T>::addNewValueAtIndex(int pos, T value){
    
    /// in case of insert start
    if (pos == 0){
        insertStart(value);
        return;
    }
    
    node<T> *pre=NULL;
    node<T> *cur;
    node<T> *temp=new node<T>;
    cur=head;
    for(int i=0;i<pos;i++)
    {
        pre=cur;
        cur=cur->next;
    }
    temp->data=value;
    pre->next=temp;
    temp->next=cur;
}

template <class T>
void list<T>::setValueForIndex(int index, T value){
    
    node<T> *pre;
    node<T> *cur;
    cur=head;
    
    for(int i=0;i<index;i++){
        pre=cur;
        cur=cur->next;
    }
    
    
    cur->data = value;
}

template <class T>
void list<T>::deleteFirst(){
    node<T> *temp;
    temp=head;
    head=head->next;
    delete temp;
}

template <class T>
void list<T>::deleteLast(){
    node<T> *current;
    node<T> *previous=NULL;
    current=head;
    while(current->next!=NULL)
    {
        previous=current;
        current=current->next;
    }
    tail=previous;
    previous->next=NULL;
    delete current;
}

template <class T>
void list<T>::deleteValueAtIndex(int pos){
    node<T> *current;
    node<T> *previous=NULL;
    current=head;
    for(int i=0;i<pos;i++)
    {
        previous=current;
        current=current->next;
    }
    previous->next=current->next;
    delete current;
}

template <class T>
T list<T>::valueForIndex(int index){
    node<T> *temp=new node<T>;
    temp=head;
    
    for(int i=0;i<index;i++){
        temp=temp->next;
    }
    
    return temp->data;
}

template <class T>
int list<T>::length(){
    node<T> *current;
    current=head;
    int count = 0;
    while(current!=NULL)
    {
        count++;
        current=current->next;
    }
    current = NULL;
    return count;
}


#endif /* linkList_h */

class WidgetString{
      String _label;
      String _value;
   public:
      
      String getLabel(){
         return _label;
      }
      String getvalue(){
         return _value;
      }
      WidgetString* setLabel(String label){
         _label = label;
         return this;
      }
      WidgetString* setValue(String value){
         _value = value;
         return this;
      }
};

class WidgetDouble{
      String _label;
      double _value;
   public:
      String getLabel(){
         return _label;
      }
      double getvalue(){
         return _value;
      }
      WidgetDouble* setLabel(String label){
         _label = label;
         return this;
      }
      WidgetDouble* setValue(double value){
         _value = value;
         return this;
      }
};


class WidgetService{
   protected:
       list<WidgetString*> _widgetStrings;
       list<WidgetDouble*> _widgetDoubles;

   public:
      WidgetString* newWidgetString(String label){
         WidgetString* widgetStringPtr = new WidgetString();
         widgetStringPtr->setLabel(label);
         _widgetStrings.append(widgetStringPtr);
         return widgetStringPtr;
      }
      WidgetDouble* newWidgetDouble(String label){
         WidgetDouble* widgetDoublePtr = new WidgetDouble();
         widgetDoublePtr->setLabel(label);
         _widgetDoubles.append(widgetDoublePtr);
         return widgetDoublePtr;
      }

      void JsonWidgetString(DynamicJsonDocument &doc){
         for (size_t i = 0; i < _widgetStrings.length(); i++)
         { 
            doc[_widgetStrings.valueForIndex(i)->getLabel()] = _widgetStrings.valueForIndex(i)->getvalue();
         }
      }
      void JsonWidgetDouble(DynamicJsonDocument &doc){
         for (size_t i = 0; i < _widgetDoubles.length(); i++)
         { 
            doc[_widgetDoubles.valueForIndex(i)->getLabel()] = _widgetStrings.valueForIndex(i)->getvalue();
         }
      }

      // void getDatas(){
      //    for (size_t i = 0; i < _displayWidgets.length(); i++)
      //    {
      //       Serial.print(_displayWidgets.valueForIndex(i)->_label);
      //       Serial.print("  =  ");
      //       Serial.println(_displayWidgets.valueForIndex(i)->_value);
      //       Serial.println("");
      //    }
      //    Serial.println("end get datas\n");
      // }


      
};

WiFiClient wificlient;
PubSubClient client(wificlient);

class Xcamp : public WidgetService{
   private:
      char* _server;
      int _port;
      char* _mac;
      char* _username;
      char* _password;
      char* _eventName;
      char* _eventTopic;
      char* _actionTopic;
      char* _actionResTopic;
      
      char* _ssid;
      char* _wifiPass;
      
      String _message;

   public:
      Xcamp(char* server, int port, char* mac, char* eventName,char* username, char* password);
      void connectWiFi(char* ssid, char* password);
      void connect();
      void addEventTopic(char* eventTopic);
      void addActionTopic(char* eventTopic);
      void addActionResponseTopic(char* eventTopic);
      void reconnect();
      void publish( String message);
      void loop();
      String getJson();
};

Xcamp::Xcamp(char* server, int port, char* mac, char* eventName,char* username, char* password){
   _server = server;
   _port = port;
   _mac = mac;
   _eventName = eventName;
   _username = username;
   _password = password;
}



void Xcamp::connect(){
   client.setServer(_server, _port);
   Serial.println(client.state());
}

void Xcamp::addEventTopic(char* eventTopic){
   _eventTopic=eventTopic;
}

void Xcamp::addActionTopic(char* actionTopic){
   _actionTopic=actionTopic;
}

void Xcamp::addActionResponseTopic(char* actionResTopic){
   _actionResTopic=actionResTopic;
}


void Xcamp::reconnect(){
   while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");
      String clientId = "ESP32Client-";
      clientId += _mac;

      if (client.connect(clientId.c_str(),_username,_password)) {
         Serial.println("connected");
      } else {
         Serial.print("failed, rc=");
         Serial.print(client.state());
         Serial.println(" try again in 5 seconds");
         delay(5000);
      }
   }
}

void Xcamp::publish( String message){
   char* msg = (char*)message.c_str();
   client.publish(_eventTopic, msg);

   //test doang
   delay(500);
}


void Xcamp::loop(){
   if (WiFi.status() != WL_CONNECTED){
      connectWiFi(_ssid,_password);
   }
   if (WiFi.status()== WL_CONNECTED && !client.connected()) {
      reconnect();
   }
   client.loop();
   _message = getJson();
   publish(_message);
}

//set wifi connection
void Xcamp::connectWiFi(char* ssid, char* password){
   _ssid = ssid;
   _wifiPass = password;
   delay(100);
   Serial.print("\nConnecting to ");
   Serial.println(ssid);
   WiFi.begin(ssid, password);
   
   while (WiFi.status()!=WL_CONNECTED){
      delay(100);
      Serial.print("...");
   }
   Serial.print("WiFi connected :");
   Serial.println(ssid);
   Serial.print("IP address: ");
   Serial.println(WiFi.localIP());
}

String Xcamp::getJson(){
   String output;
   DynamicJsonDocument doc(2048);

   doc["eventName"] = _eventName;
   doc["status"] = "active";
   doc["mac"] = _mac;
   int i;
   for (size_t i = 0; i < _widgetStrings.length(); i++)
   { 
      doc[_widgetStrings.valueForIndex(i)->getLabel()] = _widgetStrings.valueForIndex(i)->getvalue();
   }
   for (i = 0; i < _widgetDoubles.length(); i++)
   { 
      doc[_widgetDoubles.valueForIndex(i)->getLabel()] = _widgetDoubles.valueForIndex(i)->getvalue();
   }
   serializeJsonPretty(doc, output);
   Serial.println(output);
   return output;
}
