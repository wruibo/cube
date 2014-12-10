#include "cube/timer/timer.h"
namespace cube{
	namespace timer{
		int timer::_global_timer_id = 0;
		timer::timer()
		{
		}

		timer::~timer()
		{
			/*free the timer items*/
			std::list<item*>::iterator iter=_items.begin(), iterend=_items.end();
			while(iter != iterend)
			{
				delete *iter;
				iter++;
			}
		}
		
		int timer::init()
		{
			/*start timer thread*/
			int err = _thread.start(this);
			if(err != 0)
				return -1;

			return 0;
		}

		
		int timer::schedule(task *t, int delay, int interval/* =-1 */)
		{
			cube::thread::scope_lock<cube::thread::cond_mutex_t> lock(_mutex);
			
			/*generate unique timer id*/
			_global_timer_id++;

			/*compute the first expire time stamp & generate the timer item*/
			item *newitem = new item(_global_timer_id, t, delay, interval);

			/*add the new timer item into the right position in the timer list*/
			std::list<item*>::iterator iter=_items.begin(), iterend=_items.end();
			while(iter != iterend)
			{
				if((*iter)->expire() > newitem->expire())
					break;
				iter++;
			}
			_items.insert(iter, newitem);

			/*wake up the timer thread*/
			_condition.wake();

			return _global_timer_id;
		}

		
		int timer::cancel(int timerid)
		{
			cube::thread::scope_lock<cube::thread::cond_mutex_t> lock(_mutex);

			std::list<item*>::iterator iter=_items.begin(), iterend=_items.end();
			while(iter != iterend)
			{
				if((*iter)->id() == timerid)
				{
					delete *iter;
					_items.erase(iter);
					break;
				}

				iter++;
			}

			return 0;
		}

		
		int timer::reset(int timerid, int interval)
		{
			cube::thread::scope_lock<cube::thread::cond_mutex_t> lock(_mutex);

			std::list<item*>::iterator iter=_items.begin(), iterend=_items.end();
			while(iter != iterend)
			{
				if((*iter)->id() == timerid)
				{
					(*iter)->interval(interval);
					break;
				}

				iter++;
			}

			return 0;
		}

		
		int timer::destroy()
		{
			/*stop the timer thread first*/
			_thread.stop();

			/*wake up the timer thread if it is waiting the condition*/
			_condition.wakeall();

			/*wait until the timer thread to exit*/
			_thread.join();

			return 0;
		}

		
		int timer::wait()
		{
			cube::thread::scope_lock<cube::thread::cond_mutex_t> lock(_mutex);
			if(_items.empty())
				_condition.wait(_mutex);
			else
			{
				uint64_t now = mtime();
				uint64_t latest_expire_tm = _items.front()->expire();
				if(latest_expire_tm > now)
					_condition.wait(_mutex, (int)(latest_expire_tm-now));
			}

			return 0;
		}

		
		int timer::expire()
		{
			cube::thread::scope_lock<cube::thread::cond_mutex_t> lock(_mutex);

			/*current unix time in million seconds since 1970.01.01*/
			uint64_t now = mtime();

			/*timer task expires*/
			std::list<item*> expires;

			/*scan the timer list from header*/
			std::list<item*>::iterator iter=_items.begin(), iterend=_items.end();
			while(iter != iterend)
			{
				if((*iter)->expire() > now)
				{/*current timer task is not expired*/
					break;
				}
				else
				{/*current timer task has expired*/
					/*remove the expired timer task*/
					item* item = *iter;
					_items.erase(iter++);

					/*execute the timer task*/
					item->get_task()->run(now/1000);
					
					/*reset the item's next expire time*/
					if(item->is_repeat())
						item->expire(now+item->interval());

					 /*move the timer item to expires list*/
					expires.push_back(item);
				}
			}

			/*save the expired timer item number*/
			int nexpired = (int)expires.size();

			/*reschedule the expired repeat tasks*/
			std::list<item*>::iterator iter_expired=expires.begin(), iterend_expired=expires.end();
			while(iter_expired != iterend_expired)
			{
				if((*iter_expired)->is_repeat())
				{
					/*reschedule the repeat timer item*/
					iter=_items.begin(), iterend=_items.end();
					while(iter != iterend)
					{
						if((*iter)->expire() > (*iter_expired)->expire())
							break;
						iter++;
					}
					_items.insert(iter, *iter_expired);
				}
				else
				{
					/*release the not repeat timer item*/
					delete (*iter_expired);
				}

				iter_expired++;
			}
			expires.clear();

			return nexpired;
		}
		
		void timer::loop()
		{
			//first wait
			this->wait();

			//timer up or new timer task added
			this->expire();
		}

	}
}