#ifndef InputHandlerBase_HPP
#define InputHandlerBase_HPP

#include <functional>
#include <map>
#include <vector>

#include <Module/Logger/OneLogger.hpp>
#include <Helpers\Enum\InputEnum.hpp>
#include <Module\EngineModuleManager.hpp>

#include "Callback.hpp"

namespace Input
{

	template <class T, class T2 >
	class InputHandlerBase
	{
		typedef std::vector<Callback::Callback<T2, T>> callbackVector;

	protected:

		void insertIntoHolder(const Callback::Callback<T2, T> callback, std::unordered_map<T, callbackVector>& holder, const T input)
		{
			std::unordered_map<T, callbackVector>::iterator it = holder.find(input);
			if (it == holder.end())
			{
				callbackVector tempVector;
				tempVector.push_back(callback);
				holder.insert(std::pair<T, callbackVector>(input, tempVector));
			}
			else
				it->second.push_back(callback);
		}

		bool removeFromHolder(const Core::String& callbackToRemove, std::unordered_map<T, callbackVector>& holder, const T& input)
		{
			std::unordered_map<T, callbackVector>::iterator it = holder.find(input);
			if (it == holder.end())
			{
				//Engine::Get<OneLogger>().Warning("Trying to remove callback [" + (Core::String)callbackToRemove + "] from holder [" + "TMP" +
				//	"] when input type is not even registered.");
			}
			else
			{
				std::vector<Callback::Callback<T2, T>>::iterator iit = std::find(it->second.begin(), it->second.end(), Callback::Callback<T2, T > (callbackToRemove));
				if (iit == it->second.end())
				{
					//Engine::Get<OneLogger>().Warning("Trying to remove callback [" + (Core::String)callbackToRemove + "] from [" + "TMP" + "] with input value["
					//+ input + "] but it was not found in the vector for that input value.");
				}
				else
				{
					if (iit->callIfRemoved)
					{
						const T2 value = checkInput(input);
						if (value)
						{
							Callback::Callback<T2, T>& c = *iit;
							c(value, input, 0.f);
						}
					}
					it->second.erase(iit);
					if (it->second.empty())
						holder.erase(it);
					return true;
				}
			}
			return false;
		}


	public:
		std::function<T2(T)> checkInput;
		inline void update(const float& fElapsedTime)
		{
			std::unordered_map<T, callbackVector>::iterator it = binds.begin();
			std::unordered_map<T, callbackVector>::iterator eit = binds.end();

			for (; it != eit; ++it)
			{
				T2 value = checkInput(it->first);
				if (value)
				{
					for (size_t i = 0; i < it->second.size(); ++i)
						it->second[i](value, it->first, fElapsedTime);
				}
			}
		}

		InputHandlerBase(std::function<T2(T)> functionToCheckIfInputIsPressed) : binds(),
			checkInput(functionToCheckIfInputIsPressed)
		{
		}

		inline void RegisterCallback(Callback::Callback<T2, T> callback, T input)
		{
			insertIntoHolder(callback, binds, input);
		}

		inline bool RemoveCallback(T input, Core::String callbackToRemove)
		{
			return removeFromHolder(callbackToRemove, binds, input);
		}

		std::unordered_map<T, callbackVector> binds;

	};
}

#endif