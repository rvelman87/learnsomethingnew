#include"supplied.hpp"
#include<iostream>
#include<unordered_map>
#include<initializer_list>
#include<ctime>
#include <chrono>
using namespace psonic;

using namespace std;

struct d_new_order : public i_new_order_watcher {
private:
    /*Mapping for order id and running count map*/
    unordered_map <int, int> order_id_running_count_map;
    /*Mapping for order id and running time map*/
    unordered_map <int, int64_t> order_id_running_time_map;
    /*Mapping for order id and rate limit time map*/
    unordered_map <int, int64_t> order_id_rate_limit_time_map;
    /*Mapping for order id and rate limit threshold*/
    unordered_map <int, int> order_id_rate_limit_threshold_map;
    /*Mapping for order id and number of orders map*/
    unordered_map <int, int> order_id_and_orders_map;
public:
    void helper_set_threshold (const rate_limit_window &rl, const order_details& order);
    d_new_order(){
        this->order_id_running_time_map[-1]  = 0;
    }
    ~d_new_order() {}
    void on_new_order(const time_counter& at, const order_details& order);
    void on_periodic(const time_counter& at);
};
