#pragma once
#include "state.h"
#include <iostream>
#include "shark.hpp"

template <class entity_type>
class state_machine
{
	entity_type& owner_;

	state* current_state_;
	state* previous_state_;
	state* global_state_;


public:

	state_machine(entity_type& owner) :owner_(owner),
		current_state_(nullptr),
		previous_state_(nullptr),
		global_state_(nullptr)
	{}

	virtual ~state_machine() = default;

	void set_current_state(state* s) { current_state_ = s; }
	void set_global_state(state* s) { global_state_ = s; }
	void set_previous_state(state* s) { previous_state_ = s; }

	state* current_state() const { return current_state_; }
	state* global_state() const { return global_state_; }
	state* previous_state() const { return previous_state_; }

	void update()const
	{
		if (global_state_)   
			global_state_->execute();

		if (current_state_) 
			current_state_->execute();
	}

	void change_state(state* new_state)
	{
		if(new_state == nullptr)
		{
			std::cout << "Tried to change to nullptr state.\n";
			return;
		}

		previous_state_ = current_state_;

		current_state_->on_exit();
		current_state_ = new_state;
		current_state_->set_actor(owner_);
		current_state_->on_enter();
	}

	void revert_to_previous_state()
	{
		change_state(previous_state_);
	}

	//returns true if the current state's type is equal to the type of the class passed as a parameter. 
	bool is_in_state(const state& st)const
	{
		return typeid(*current_state_) == typeid(st);
	}
};
