#pragma once

namespace kmint
{
	namespace pigisland
	{
		namespace signals
		{
			template<typename... Args>
			class pigisland_signal
			{
				typedef std::function<void(Args...)> Listener;
				std::vector<Listener> signalListeners;

			public:
				pigisland_signal() = default;
				void addListener(const Listener listener)
				{
					signalListeners.push_back(listener);
				}

				void removeListener(Listener listener)
				{
					std::vector<int>::iterator position = std::find(signalListeners.begin(), signalListeners.end(), listener);
					if (position != signalListeners.end())
						signalListeners.erase(position);
				}

				void popListener() {
					signalListeners.pop_back();
				}

				void dispatch(Args... args) const
				{
					for (auto signalListener : signalListeners)
					{
						signalListener(args...);
					}
				}
			};
		}
	}
}