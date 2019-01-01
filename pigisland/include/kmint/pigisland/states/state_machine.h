#pragma once
#include "state.h"
#include <iostream>

namespace kmint
{
	namespace pigisland
	{
		namespace states
		{
			template <class entity_type>
			class state_machine
			{
				entity_type& owner_;

				std::string current_state_;
				std::string previous_state_;
				std::string global_state_;

				std::unordered_map<std::string, std::unique_ptr<state<entity_type>>> states_{};

			public:

				state_machine(entity_type& owner) :owner_(owner){}

				virtual ~state_machine() = default;

				void set_current_state(std::string s) { current_state_ = s; }
				void set_global_state(std::string s) { global_state_ = s; }
				void set_previous_state(std::string s) { previous_state_ = s; }

				std::string current_state() const { return current_state_; }
				std::string global_state() const { return global_state_; }
				std::string previous_state() const { return previous_state_; }

				void update()const
				{
					if (!global_state_.empty())
						states_.at(global_state_)->execute(owner_);

					if (!current_state_.empty())
						states_.at(current_state_)->execute(owner_);
				}

				void change_state(const std::string new_state)
				{
					if (states_.find(new_state) == states_.end())
					{
						std::cout << "Tried to change to undefined state.\n";
						return;
					}
					previous_state_ = current_state_;

					states_.at(current_state_)->on_exit(owner_);
					current_state_ = new_state;
					states_.at(current_state_)->on_enter(owner_);
				}

				void addState(std::unique_ptr<state<entity_type>> state)
				{
					states_[state->name()] = std::move(state);
				}

				void revert_to_previous_state()
				{
					change_state(previous_state_);
				}

				//returns true if the current state's type is equal to the type of the class passed as a parameter. 
				bool is_in_state(const std::string& st)const
				{
					return current_state_ == st;
				}
			};
		}
	}
}
