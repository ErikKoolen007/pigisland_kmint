#pragma once
#include "kmint/play/actor.hpp"

class state
{
protected:
	state() = default;

public:

	virtual ~state() = default;
	virtual void set_actor(kmint::play::actor& actor) = 0;
	virtual void on_enter() = 0;
	virtual void execute() = 0;
	virtual void on_exit() = 0;
};
