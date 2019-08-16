#pragma once

namespace utility
{
    namespace detail
    {
        template<typename _Type>
            class SingletonWrapper: public _Type
        {
            public:
                SingletonWrapper()
                {
                }

                ~SingletonWrapper()
                {
                }
        };

    } /* detail */ 


    template<typename _Type>
        class Singleton
        {
            struct CreateObj
            {
                CreateObj()
                {
                    Singleton<_Type>::instance();
                }

                void doNothing()const{ }
            };

            public:
            static _Type& instance()
            {
                //use wapper to call protected constructor
                static detail::SingletonWrapper<_Type> instance_;
                // code below is to sure call before call main
                create_obj_.doNothing();
                return instance_;
            }

            private:
            static CreateObj create_obj_;

            Singleton() = delete;
            Singleton(Singleton const&) = delete;
        };

    template<typename _Type>
        typename Singleton<_Type>::CreateObj Singleton<_Type>::create_obj_;

}
