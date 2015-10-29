/*
 * =====================================================================================
 *
 *       Filename:  counter.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年10月23日 16时34分18秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  WangYao (fisherman), wangyao02@baidu.com
 *        Company:  Baidu, Inc
 *
 * =====================================================================================
 */
#ifndef PUBLIC_RAFT_EXAMPLE_COUNTER_H
#define PUBLIC_RAFT_EXAMPLE_COUNTER_H

#include <string>
#include <bthread.h>
#include <base/callback.h> //Closure
#include "raft/raft.h"

DECLARE_bool(enable_verify);

namespace counter {

class Counter : public raft::StateMachine {
public:
    Counter(const raft::GroupId& group_id, const raft::PeerId& peer_id);

    int init(const raft::NodeOptions& options);


    int shutdown(raft::Closure* done);

    base::EndPoint leader();

    // FSM method
    virtual void on_apply(const void* data, const int len);

    virtual int on_snapshot_save();

    virtual int on_snapshot_load();

    virtual void on_shutdown();

    virtual void on_state_change(raft::State old_state, raft::State new_state);

    // user logic method
    int add(int64_t value, raft::Closure* done);

    int get(int64_t* value_ptr);

private:
    virtual ~Counter();

    raft::Node _node;
    bthread_mutex_t _mutex;
    int64_t _value;
};

}


#endif //~PUBLIC_RAFT_EXAMPLE_COUNTER_H