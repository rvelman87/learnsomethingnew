#include"supplied.hpp"
#include"derived.hpp"

/*set time and threshold for rate limit struct */
void set_threshold_time(rate_limit_window &rl, uint32_t threshold, uint32_t ms) {
    rl.threshold = threshold;
    rl.milliseconds  = ms;
}

/*set order id details for order_id struct, grp id is valid*/
void set_order_id_details(order_details & od, uint32_t order_id) {
    od.trading_group_id = order_id;
}

/*set order id details for order_id struct, grp id is valid*/
void set_timer(time_counter & at, uint32_t ms) {
    at.nanoseconds = ms*1000;
    cout<<"current Set timer  nanoseconds " << at.nanoseconds <<endl;
}



int main() {
    /*Derived class objects for helper */
    shared_ptr<d_new_order> dptr = make_shared<d_new_order>();
    /*local objects for setters*/
    time_counter at;
    rate_limit_window rl;
    order_details od; 


    /*Create a shared pointer to the base class */
    shared_ptr<i_new_order_watcher> watcher;
    watcher = dynamic_pointer_cast<i_new_order_watcher>(dptr); 

    /* Since the helpers functions are not part of base class,
     * use the derived class object for accessing setters */

    /*Test Case 1*/
    /*
     * Intialize the structures with different order id and time, thresholds.
     * Order grp id 1, time ms = 200, threshold 20 
     * Order grp id 2, time ms = 400, threshold 40
     * Order grp id 3, time ms = 600, threshold 60
     * Order grp id 20, time ms = 1000, threshold 300 */
#if 1
     cout << "Test Case 1" <<endl;
     set_order_id_details(od, 1);
     set_threshold_time(rl, 200, 20);
     dptr->helper_set_threshold(rl, od);

     set_order_id_details(od, 2);
     set_threshold_time(rl, 400, 40);
     dptr->helper_set_threshold(rl, od);

     set_order_id_details(od, 3);
     set_threshold_time(rl, 600, 60);
     dptr->helper_set_threshold(rl, od);

     set_order_id_details(od, 20);
     set_threshold_time(rl, 1000, 300);
     dptr->helper_set_threshold(rl, od);
      
     watcher->on_new_order(at, od);

      
#endif
#if 0
    watcher = dynamic_pointer_cast<i_new_order_watcher>(dptr); 
     /*Test Case 2,
      * Call the watcher for order id 20, when time is 10ms reduce 10 ms */
     cout<<"Test case 2 " <<endl;
     /*call the watcher at 10 ms later*/
     set_timer(at, 10);
     watcher->on_new_order(at, od);
//     set_threshold_time(rl, 10, 300);
  //   dptr->helper_set_threshold(rl, od);

     /*Test Case 3,
      * Call the watcher for order id 20, reduce 1 ms *
      * Set timer as 100 ms, threshold as 10, 
      * for every 1 ms call watcher, when threshold >10, report breach */
     cout<<"Test case 3" <<endl;
     set_order_id_details(od, 20);
     set_threshold_time(rl, 10, 300);
     cout <<"RL threshold " << rl.threshold << "  RL milli " << rl.milliseconds <<endl; 
     dptr->helper_set_threshold({10,300}, od);

    watcher = dynamic_pointer_cast<i_new_order_watcher>(dptr); 
     set_timer(at, 1);
     cout<<"Test case 3" <<endl;
     for (int i=0; i<20; i++)
         watcher->on_new_order(at, od);

#endif     

    return 0;
}



