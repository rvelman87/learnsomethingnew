#pragma once

#include <memory>
#include <cstdint>

namespace psonic {

/**
 * Rate limit expressed as the threshold per window, and the window width in milliseconds.
 *
 * For example 1000 requests per second would be
 * { .threshold=1000, .milliseconds=1000 };
 */
struct rate_limit_window
{
    uint32_t threshold = 0;
    uint32_t milliseconds = 0;
};

/**
 * Representation of an order. For the purposes of this question, only the
 * trading_group_id is relevant.
 */
struct order_details
{
    uint32_t trading_group_id = 0;
    uint32_t symbol_id = 0;
    uint32_t order_id = 0;
    uint32_t volume = 0;
    uint32_t price_cents = 0;
};

/**
 * Time is in nanoseconds since an epoch.
 */
struct time_counter
{
    int64_t nanoseconds = 0;
};

/**
 * The system will call each registered watcher when it detects the arrival
 * of a new order. In addition, the system will call `on_periodic` every 5 seconds or so, allowing
 * your class to do additional work as appropriate
 */
struct i_new_order_watcher
{
    virtual void on_new_order(const time_counter& at, const order_details& order) = 0;
    virtual void on_periodic(const time_counter& at) = 0;
};

struct system
{
    /**
     * The system will provide a mechanism to get the rate threshold for
     * a valid trading group (returns nullptr for invalid groups).
     */
    static const rate_limit_window* get_new_order_rate_limit_for_trading_group(const uint32_t& trading_group_id);

    /**
     * When a trading group breaches a rate limit, notify that the limit has been breached immediately.
     */
    static void notify_rate_breaching_new_order(const uint32_t& trading_group_id, const rate_limit_window& limit,
                                                const time_counter& window_start_time, const order_details& breaching_order);

    /**
     * As soon as possible after a rate limit has been breached, notify also the total rate for the window that was 
     * breached. 
     */
    static void notify_breaching_rate(const uint32_t& trading_group_id, const rate_limit_window& limit,
                                      const time_counter& window_start_time, const uint32_t actual_count_for_window);

    /**
     * Your code can register to receive new order notification by calling the following
     * function.
     */
    static bool register_new_order_watcher(std::shared_ptr<i_new_order_watcher> watcher);

    /**
     * similarly it can deregister when appropriate.
     */
    static void deregister_new_order_watcher(std::shared_ptr<i_new_order_watcher> watcher);

    /**
     * After you have initialised your code base, call system::run(). This is a blocking call.
     * It starts processing orders and will callback to your code through the watcher interface.
     * When the system is finished doing what it does, it will return, and your program can exit.
     */
    static void run();
};

}
