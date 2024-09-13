#ifndef __USB_MANAGER
#define __USB_MANAGER
#include <experimental/filesystem>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <unistd.h>
namespace fs=std::experimental::filesystem;
typedef std::experimental::filesystem::__cxx11::directory_entry directory_entry;

/*Event_Listener*/
class Event_Listener{
    public:
        std::string name;
        virtual void updateState(std::string event,directory_entry entry) = 0;
        virtual ~Event_Listener(){

        }
};

/*Event_Listener_List_File*/
class Event_Listener_List_File:public Event_Listener{
    public:
        Event_Listener_List_File(std::string _name){
            this->name = _name;
        }
        void updateState(std::string event,directory_entry entry);
        ~Event_Listener_List_File(){

        }
};

/*Event_Manager*/
class Event_Manager{
    private:
        bool checkIfExisted(std::string event_type, Event_Listener* new_listener);
        bool checkIfExisted(std::string event_type, std::string name_listener);
    public:
        std::vector<std::pair<std::string, Event_Listener*>>listeners; 
        Event_Manager(){

        }
        //Subcribe new Listener with event type
        void subcribe(std::string event_type, Event_Listener *new_listener);
        //Unsubcriber using name event and event_type
        bool unsubcribe(std::string event_type, std::string name_listener);
        //Notify event_type with suitable listener
        void notify(std::string event_type, directory_entry entry);

};

/*USB_Handle*/
class USB_Handle{
    private:
        static std::string _path;
    public:
        std::vector<directory_entry>listUSB;
        Event_Manager *event = nullptr;         
        USB_Handle(Event_Manager *_event){
            this->event = _event;
        }
        static void checkInsert(USB_Handle &other){
           while(1){
                std::vector<directory_entry> previous_Path = other.listUSB;
                //delete current_list
                other.listUSB.clear();
                //Update list of USB again
                if(fs::is_directory(USB_Handle::_path)){
                    if(!fs::is_empty(USB_Handle::_path)){
                        for(auto &entry:fs::directory_iterator(_path)){
                            //Check if this is USB
                            if(fs::is_directory(entry)){
                                other.listUSB.push_back(entry);    
                            }
                        }
                        //Condition
                        if(other.listUSB.size() > previous_Path.size()){
                            other.event->notify("insert",other.listUSB[other.listUSB.size()-1]);
                        }
                    }
                }
                else{
                    throw std::invalid_argument("Invalid Directory\n");
                    exit(0);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            } 
        }
        static void checkRemove(USB_Handle &other){
            while(1){
                std::vector<directory_entry> previous_Path = other.listUSB;
                //delete current_list
                other.listUSB.clear();
                //Update list of USB again
                if(fs::is_directory(USB_Handle::_path)){
                    if(!fs::is_empty(USB_Handle::_path)){
                        for(auto &entry:fs::directory_iterator(USB_Handle::_path)){
                            //Check if this is USB
                            if(fs::is_directory(entry)){
                                other.listUSB.push_back(entry);    
                            }
                        }
                    }
                    //Condition
                    if(other.listUSB.size() < previous_Path.size()){
                        other.event->notify("remove",previous_Path[previous_Path.size()-1]);
                    }
                }
                else{
                    throw std::invalid_argument("Invalid Directory\n");
                    exit(0);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
};

#endif