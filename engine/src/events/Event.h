#ifndef KOBENGINE_EVENT_H
#define KOBENGINE_EVENT_H

// -- Standard Library --
#include <functional>
#include <vector>

namespace kobengine
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~	  Event
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	template<typename... Args>
	class Event final
	{
        // -- Using Typedefs --
        using FuncPtr = void(*)(Args...);
        template<typename ObjectType>
        using MemFuncPtr = void(ObjectType::*)(Args...);
        template<typename ObjectType>
        using ConstMemFuncPtr = void(ObjectType::*)(Args...) const;


        // -- Structs --
        struct IListener
        {
            virtual ~IListener() = default;
            virtual void Invoke(Args... args) const = 0;
        };
        struct GeneralListener : IListener
        {
            FuncPtr func;
            GeneralListener(const FuncPtr& f)
                : func(f) {}
            void Invoke(Args... args) const override { func(std::forward<Args>(args)...); }
        };
        template<typename ObjectType, typename MemFuncType>
        struct MemberListener : IListener
        {
            ObjectType* obj;
            MemFuncType func;
            MemberListener(ObjectType* o, const MemFuncType& f)
                : obj(o), func(f) {}
            void Invoke(Args... args) const override { (obj->*func)(std::forward<Args>(args)...); }
        };


    public:
        //--------------------------------------------------
        //    Constructor & Destructor
        //--------------------------------------------------
        Event() = default;
        ~Event() { RemoveAllListeners(); }

        Event(const Event& other) = delete;
        Event(Event&& other) noexcept = delete;
        Event& operator=(const Event& other) = delete;
        Event& operator=(Event&& other) noexcept = delete;


        //--------------------------------------------------
        //    General Function Listeners
        //--------------------------------------------------
        void AddListener(const FuncPtr& func)
        {
            m_vListeners.push_back(std::make_unique<GeneralListener>(func));
        }
        void RemoveListener(const FuncPtr& func)
        {
            std::erase_if(m_vListeners, [func](const std::unique_ptr<IListener>& p)
                {
                    if (auto* cast = dynamic_cast<GeneralListener*>(p.get()))
                        return cast->func == func;
                    return false;
                });
        }

        //--------------------------------------------------
        //    Member Function Listeners
        //--------------------------------------------------
        template<typename ObjectType>
        void AddListener(ObjectType* obj, const MemFuncPtr<ObjectType>& func)
        {
            m_vListeners.emplace_back(std::make_unique<MemberListener<ObjectType, MemFuncPtr<ObjectType>>>(obj, func));
        }
        template<typename ObjectType>
        void RemoveListener(ObjectType* obj, const MemFuncPtr<ObjectType>& func)
        {
            std::erase_if(m_vListeners, [obj, func](const std::unique_ptr<IListener>& p)
                {
                    if (auto* cast = dynamic_cast<MemberListener<ObjectType, MemFuncPtr<ObjectType>>*>(p.get()))
                        return cast->obj == obj && cast->func == func;
                    return false;
                });
        }

        //--------------------------------------------------
        //    Const Member Function Listeners
        //--------------------------------------------------
        template<typename ObjectType>
        void AddListener(ObjectType* obj, const ConstMemFuncPtr<ObjectType>& func)
        {
            m_vListeners.emplace_back(std::make_unique<MemberListener<ObjectType, ConstMemFuncPtr<ObjectType>>>(obj, func));
        }
        template<typename ObjectType>
        void RemoveListener(ObjectType* obj, const ConstMemFuncPtr<ObjectType>& func)
        {
            std::erase_if(m_vListeners, [obj, func](const std::unique_ptr<IListener>& p)
                {
                    if (auto* cast = dynamic_cast<MemberListener<ObjectType, ConstMemFuncPtr<ObjectType>>*>(p.get()))
                        return cast->obj == obj && cast->func == func;
                    return false;
                });
        }

        //--------------------------------------------------
        // General
        //--------------------------------------------------
        void RemoveAllListeners()
        {
            m_vListeners.clear();
        }
        void Invoke(Args... args) const
        {
            for (const auto& l : m_vListeners)
                l->Invoke(std::forward<Args>(args)...);
        }

        //--------------------------------------------------
        //    Operator Overloading
        //--------------------------------------------------
        // -- Add Listener --
        void operator+=(const FuncPtr& func)
    		{ AddListener(func); }
        template<typename ObjectType>
        void operator+=(std::pair<ObjectType*, MemFuncPtr<ObjectType>> memFunc)
    		{ AddListener(memFunc.first, memFunc.second); }
        template<typename ObjectType>
        void operator+=(std::pair<ObjectType*, ConstMemFuncPtr<ObjectType>> memFunc)
    		{ AddListener(memFunc.first, memFunc.second); }

        // -- Remove Listener --
        void operator-=(const FuncPtr& func)
			{ RemoveListener(func); }
        template<typename ObjectType>
        void operator-=(std::pair<ObjectType*, MemFuncPtr<ObjectType>> memFunc)
			{ RemoveListener(memFunc.first, memFunc.second); }
        template<typename ObjectType>
        void operator-=(std::pair<ObjectType*, ConstMemFuncPtr<ObjectType>> memFunc)
			{ RemoveListener(memFunc.first, memFunc.second); }

        // -- Invoke Listener --
        void operator()(Args... args)
    		{ Invoke(std::forward<Args>(args)...); }

    private:
        std::vector<std::unique_ptr<IListener>> m_vListeners;
    };
}

#endif // KOBENGINE_EVENT_H