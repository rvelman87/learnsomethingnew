#define DEBUG 1

#include"derived.hpp"
/*Helper function -Set the threshold of group id*/
void d_new_order :: helper_set_threshold(const rate_limit_window &rl, const order_details& order) 
{
    cout << "Incoming timer milliseconds "<<rl.milliseconds << " Incoming thresholds " << rl.threshold <<endl;
    cout << "Existing value " << this->order_id_rate_limit_threshold_map[order.trading_group_id] <<endl;

    this->order_id_rate_limit_threshold_map.insert(pair<int, int>(order.trading_group_id, rl.threshold));  
    #if DEBUG
    cout<<"Incoming order id "<<order.trading_group_id<<" Threshold "<<
        this->order_id_rate_limit_threshold_map[order.trading_group_id] <<endl;
    #endif

    this->order_id_rate_limit_time_map.insert(pair<int, int64_t>(order.trading_group_id, rl.milliseconds*1000));  
    #if DEBUG
    cout << "Incoming timer milliseconds "<<rl.milliseconds <<endl;
    #endif
    #if DEBUG
    cout<<"Incoming order id "<<order.trading_group_id<<" Incoming time Nano seconds "<<
        this->order_id_rate_limit_time_map[order.trading_group_id] <<endl;
    #endif

    /*Set incoming time to running time */
    this->order_id_running_time_map.insert(pair<int, int64_t>(order.trading_group_id, rl.milliseconds*1000));
    #if DEBUG
    cout<<"Incoming order id "<<order.trading_group_id<<" Running time Nano seconds "<<
        this->order_id_running_time_map[order.trading_group_id] <<endl;
    #endif
};


/* Derived class on periodic implementation*/
void d_new_order:: on_new_order(const time_counter& at, const order_details& order) 
{
    int64_t  curr_time = 0;
    rate_limit_window rl;
    time_counter window_start_time;
    order_details breaching_order;
    
    /*Set the ongoing timer*/
    /* Every time the on_new_order function is called, reduce the timer*/
    
    curr_time = this->order_id_running_time_map[order.trading_group_id] - at.nanoseconds;
    #if DEBUG
    cout << "Order ID " << order.trading_group_id;
    cout << " Incoming time ns " << at.nanoseconds;
    cout << " Running time ns " << this->order_id_running_time_map[order.trading_group_id];
    cout << " Current time " << curr_time <<endl;
    #endif
   

    this->order_id_running_time_map.insert(pair<int, int64_t>(order.trading_group_id, curr_time));

    rl.threshold = this->order_id_rate_limit_threshold_map[order.trading_group_id];
    rl.milliseconds = this->order_id_rate_limit_time_map[order.trading_group_id];
    window_start_time.nanoseconds = curr_time;

    if(curr_time >= 0) 
    {
        /*For every call increment the orderid counter*/
        this->order_id_running_count_map[order.trading_group_id]++;
    #if 1 
        cout << "New Current running order count " << this->order_id_running_count_map[order.trading_group_id] <<endl;
    #endif
        /*Report the issue*/
        /*If current count is > threshold report breaching rate*/
        if (this->order_id_running_count_map[order.trading_group_id] > 
            this->order_id_rate_limit_threshold_map[order.trading_group_id]) {
            
            system::notify_rate_breaching_new_order(order.trading_group_id, rl,
                    window_start_time, order); 
        }
    } else {
        /*If the time reaches its limit, then current running counter is reset*/
        this->order_id_running_count_map[order.trading_group_id] = 0;
    } 
        
    
}

/* Derived class on periodic implementation*/
void d_new_order:: on_periodic(const time_counter& at) 
{
    /**/
    #if DEBUG
    cout << "New order called \n"<<endl;
    #endif
    
}



/**
 * When a trading group breaches a rate limit, notify that the limit has been breached immediately.
 */
void system:: notify_rate_breaching_new_order(const uint32_t& trading_group_id, const rate_limit_window& limit,
        const time_counter& window_start_time, const order_details& breaching_order) 
{
        cout<<"Notification breached for Order ID "<< trading_group_id << 
              " Rate Limit threshold "<<  limit.threshold << 
              " Rate Limit Milliseconds "<< limit.milliseconds <<
              " Start time of breach "   << window_start_time.nanoseconds <<  endl;
}

/**
 * As soon as possible after a rate limit has been breached, notify also the total rate for the window that was 
 * breached. 
 */
void system::notify_breaching_rate(const uint32_t& trading_group_id, const rate_limit_window& limit,
        const time_counter& window_start_time, const uint32_t actual_count_for_window) 
{

        cout<<"Notification breached for Order ID "<< trading_group_id << 
              " Rate Limit threshold "<<  limit.threshold << 
              " Rate Limit Milliseconds "<< limit.milliseconds <<
              " Start time of breach "   << window_start_time.nanoseconds <<  endl;
}

 
