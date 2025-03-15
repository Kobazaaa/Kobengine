#pragma once
#include <unordered_set>
#include <functional>


namespace kob
{
	class BaseListener
	{
	public:
		virtual ~BaseListener() = default;
	};

	template<typename... Args>
	class Event;

	template<typename... Args>
	class EventListener : public BaseListener
	{
	public:
		virtual ~EventListener() override
		{
			m_isDestroying = true;
			for (Event<Args...>* pEvent : m_vEvents)
				(*pEvent) -= this;
		}
		virtual void Notify(Args... args) = 0;

	private:
		friend class Event<Args...>;

		// Does not Subscribe! Purely used to manipulate container
		void AddEvent(Event<Args...>* pEvent) { if (!m_isDestroying) m_vEvents.insert(pEvent); }
		// Does not Unsubscribe! Purely used to manipulate container
		void RemoveEvent(Event<Args...>* pEvent) { if (!m_isDestroying) m_vEvents.erase(pEvent); }

		bool m_isDestroying = false;
		std::unordered_set<Event<Args...>*> m_vEvents;
	};

	template<typename... Args>
	class EventCallback : public EventListener<Args...>
	{
	public:
		// Function
		EventCallback(const std::function<void(Args...)>& callback)
		{
			m_Callback = callback;
		}

		// Member Function
		template<typename ObjType>
		EventCallback(ObjType* object, void (ObjType::* memberFunction)(Args...))
		{
			if (object == nullptr)
				return;

			m_Callback = [object, memberFunction](Args... args)
				{
					(object->*memberFunction)(args...);
				};
		}
		// Const Member Function
		template<typename ObjType>
		EventCallback(ObjType* object, void (ObjType::* memberFunction)(Args...) const)
		{
			if (object == nullptr)
				return;

			m_Callback = [object, memberFunction](Args... args)
				{
					(object->*memberFunction)(args...);
				};
		}

		virtual void Notify(Args... args) override
		{
			m_Callback(args...);
		}
	private:
		std::function<void(Args...)> m_Callback;
	};
}
