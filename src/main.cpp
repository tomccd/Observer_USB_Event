#include "../header/USB_Manager.hpp"

std::string USB_Handle::_path = "/media/"+std::string(getlogin());
int main(){
    /*Listener*/
    Event_Listener_List_File var_1("H");
    Event_Listener_List_File var_2("Y");
    /*Handle Event*/
    USB_Handle Handle(new Event_Manager());
    //Subcribe
    Handle.event->subcribe("insert",&var_1);
    Handle.event->subcribe("remove",&var_2);

    /*Create a thread that manage checking that USB is inserted or not*/
    std::thread t1(USB_Handle::checkInsert,std::ref(Handle));
    std::thread t2(USB_Handle::checkRemove,std::ref(Handle));
    //T1 and T2 run as a daemon
    t1.detach();
    t2.detach();
    while(1){
        std::cout << "Waiting Listener Respond...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}