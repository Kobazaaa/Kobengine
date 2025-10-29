#ifndef KOBENGINE_EVENT_H
#define KOBENGINE_EVENT_H

// -- Standard Library --
#include <functional>
#include <algorithm>
#include <vector>

namespace kobengine
{
    template<typename... Args>
    class Event final
    {
        // -- Using Typedefs --
        using FuncPtr = void(*)(Args...);
        template<typename T> using MemFuncPtr = void(T::*)(Args...);
        template<typename T> using ConstMemFuncPtr = void(T::*)(Args...) const;

        // -- Structs --
        struct IListener
        {
            virtual ~IListener() = default;
            virtual void Invoke(Args... args) const = 0;
        };
        struct GeneralListener : IListener
        {
            FuncPtr func;
            GeneralListener(FuncPtr f)
                : func(f) {}
            void Invoke(Args... args) const override { func(std::forward<Args>(args)...); }
        };
        template<typename T, typename MemFuncType>
        struct MemberListener : IListener
        {
            T* obj;
            MemFuncType func;
            MemberListener(T* o, MemFuncType f)
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
        template<typename T>
        void AddListener(T* obj, const MemFuncPtr<T>& func)
        {
            m_vListeners.emplace_back(std::make_unique<MemberListener<T, MemFuncPtr<T>>>(obj, func));
        }
        template<typename T>
        void RemoveListener(T* obj, const MemFuncPtr<T>& func)
        {
            std::erase_if(m_vListeners, [obj, func](const std::unique_ptr<IListener>& p)
                {
                    if (auto* cast = dynamic_cast<MemberListener<T, MemFuncPtr<T>>*>(p.get()))
                        return cast->obj == obj && cast->func == func;
                    return false;
                });
        }

        //--------------------------------------------------
        //    Const Member Function Listeners
        //--------------------------------------------------
        template<typename T>
        void AddListener(T* obj, const ConstMemFuncPtr<T>& func)
        {
            m_vListeners.emplace_back(std::make_unique<MemberListener<T, ConstMemFuncPtr<T>>>(obj, func));
        }
        template<typename T>
        void RemoveListener(T* obj, const ConstMemFuncPtr<T>& func)
        {
            std::erase_if(m_vListeners, [obj, func](const std::unique_ptr<IListener>& p)
                {
                    if (auto* cast = dynamic_cast<MemberListener<T, ConstMemFuncPtr<T>>*>(p.get()))
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
        template<typename T>
        void operator+=(std::pair<T*, MemFuncPtr<T>> memFunc)
    		{ AddListener(memFunc.first, memFunc.second); }
        template<typename T>
        void operator+=(std::pair<T*, ConstMemFuncPtr<T>> memFunc)
    		{ AddListener(memFunc.first, memFunc.second); }

        // -- Remove Listener --
        void operator-=(const FuncPtr& func)
			{ RemoveListener(func); }
        template<typename T>
        void operator-=(std::pair<T*, MemFuncPtr<T>> memFunc)
			{ RemoveListener(memFunc.first, memFunc.second); }
        template<typename T>
        void operator-=(std::pair<T*, ConstMemFuncPtr<T>> memFunc)
			{ RemoveListener(memFunc.first, memFunc.second); }

        // -- Invoke Listener --
        void operator()(Args... args)
    		{ Invoke(std::forward<Args>(args)...); }

    private:
        std::vector<std::unique_ptr<IListener>> m_vListeners;
    };
}

#endif // KOBENGINE_EVENT_H