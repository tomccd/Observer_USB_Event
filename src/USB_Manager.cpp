#ifndef __USB_MANAGER
#include "../header/USB_Manager.hpp"
#endif
/*Event_Manager*/
bool Event_Manager::checkIfExisted(std::string event_type, Event_Listener *new_listener){
    if(listeners.size()!=0){
        for(auto listener:listeners){
            if(listener.first == event_type && listener.second->name == new_listener->name){
                return true;
            }
        }
    }
    return false;
}

//Check if Existed
bool Event_Manager::checkIfExisted(std::string event_type, std::string name_listener){
    if(listeners.size()!=0){
        for(auto listener:listeners){
           if(listener.first == event_type && listener.second->name == name_listener){
                return true;
           } 
        }
    }
    return false;
}

//Subscribe
void Event_Manager::subcribe(std::string event_type, Event_Listener *new_listener){
   if(!checkIfExisted(event_type,new_listener)){
        listeners.push_back(std::pair<std::string,Event_Listener*>(event_type,new_listener));
   } 
   else{
        std::cout << new_listener->name << " with event name " << event_type << " existed\n"; 
   }
}

//Unsubscribe
bool Event_Manager::unsubcribe(std::string event_type, std::string name_listener){
   if(checkIfExisted(event_type,name_listener)){
        for(int i=0;i<listeners.size();i++){
            if(listeners[i].first == event_type && listeners[i].second->name == name_listener){
                listeners.erase(listeners.begin()+i);
                return true; 
            }
        }
   } 
   return false;
}

//Notify the subscribers
void Event_Manager::notify(std::string event_type,directory_entry entry){
    if(this->listeners.size()!=0){
        for(auto listener:listeners){
            if(listener.first == event_type){
                listener.second->updateState(event_type,entry);
            }
        }
    }
}

/*Event_Listener_List_File*/
void Event_Listener_List_File::updateState(std::string event_type, directory_entry entry){
    std::cout << this->name << " detected state : " << "USB: " << entry.path().filename() << " is " << event_type << std::endl;
}